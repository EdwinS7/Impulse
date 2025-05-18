#include "DirectX 11.hpp"
#include "../../Win32/Win32.hpp"

#define SAFE_RELEASE(p) if (p) { p->Release(); p = nullptr; }

bool CGraphics::Initiate(
    HWND hwnd,
    DXGI_SWAP_CHAIN_DESC swap_chain_description,
    D3D11_BUFFER_DESC buffer_description,
    D3D11_RASTERIZER_DESC rasterizer_description,
    D3D11_DEPTH_STENCIL_DESC depth_stencil_description,
    D3D11_SAMPLER_DESC sampler_description,
    D3D11_BLEND_DESC blend_description,
    const char* vertex_shader_source,
    const char* pixel_shader_source )
{
    m_TargetWindow = hwnd;

    auto Result = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        nullptr, 0, D3D11_SDK_VERSION,
        &swap_chain_description, &m_pSwapChain,
        &m_pDevice, nullptr, &m_pDeviceContext
    );
    if ( FAILED( Result ) )
        return false;

    if ( !CreateRenderTargetView( ) )
        return false;

    ID3DBlob* VertexShaderBlob = nullptr;
    Result = D3DCompile(
        vertex_shader_source, strlen( vertex_shader_source ),
        nullptr, nullptr, nullptr,
        "main", "vs_4_0", 0, 0,
        &VertexShaderBlob, nullptr
    );
    if ( FAILED( Result ) )
        return false;

    Result = m_pDevice->CreateVertexShader(
        VertexShaderBlob->GetBufferPointer( ),
        VertexShaderBlob->GetBufferSize( ),
        nullptr, &m_pVertexShader
    );
    if ( FAILED( Result ) ) {
        SAFE_RELEASE( VertexShaderBlob );
        return false;
    }

    const D3D11_INPUT_ELEMENT_DESC LocalLayout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    Result = m_pDevice->CreateInputLayout(
        LocalLayout, ARRAYSIZE( LocalLayout ),
        VertexShaderBlob->GetBufferPointer( ),
        VertexShaderBlob->GetBufferSize( ),
        &m_pInputLayout
    );
    SAFE_RELEASE( VertexShaderBlob );
    if ( FAILED( Result ) )
        return false;

    ID3DBlob* PixelShaderBlob = nullptr;
    Result = D3DCompile(
        pixel_shader_source, strlen( pixel_shader_source ),
        nullptr, nullptr, nullptr,
        "main", "ps_4_0", 0, 0,
        &PixelShaderBlob, nullptr
    );
    if ( FAILED( Result ) )
        return false;

    Result = m_pDevice->CreatePixelShader(
        PixelShaderBlob->GetBufferPointer( ),
        PixelShaderBlob->GetBufferSize( ),
        nullptr, &m_pPixelShader
    );
    SAFE_RELEASE( PixelShaderBlob );
    if ( FAILED( Result ) )
        return false;

    const unsigned char White[ 4 ] = { 255, 255, 255, 255 };

    D3D11_TEXTURE2D_DESC TextureDesc = {};
    TextureDesc.Width = TextureDesc.Height = TextureDesc.MipLevels = TextureDesc.ArraySize = 1;
    TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    TextureDesc.SampleDesc.Count = 1;
    TextureDesc.Usage = D3D11_USAGE_DEFAULT;
    TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA InitData = { White, sizeof( White ), 0 };
    m_pDevice->CreateTexture2D( &TextureDesc, &InitData, &m_pTexture );
    m_pDevice->CreateShaderResourceView( m_pTexture, nullptr, &m_pTextureSRV );
    SAFE_RELEASE( m_pTexture );

    FT_Error Error = FT_Init_FreeType( &m_FT );
    if ( Error != 0 )
        return false;

    m_pDevice->CreateBuffer( &buffer_description, nullptr, &m_pVertexConstantBuffer );
    m_pDevice->CreateRasterizerState( &rasterizer_description, &m_pRasterizerState );
    m_pDevice->CreateDepthStencilState( &depth_stencil_description, &m_pDepthStencilState );
    m_pDevice->CreateSamplerState( &sampler_description, &m_pSamplerState );
    m_pDevice->CreateBlendState( &blend_description, &m_pBlendState );

    return true;
}

void CGraphics::Cleanup( ) {
    SAFE_RELEASE( m_pSwapChain );
    SAFE_RELEASE( m_pDevice );
    SAFE_RELEASE( m_pDeviceContext );
    SAFE_RELEASE( m_pRenderTargetView );
    SAFE_RELEASE( m_pVertexBuffer );
    SAFE_RELEASE( m_pIndexBuffer );
    SAFE_RELEASE( m_pVertexShader );
    SAFE_RELEASE( m_pInputLayout );
    SAFE_RELEASE( m_pVertexConstantBuffer );
    SAFE_RELEASE( m_pPixelShader );
    SAFE_RELEASE( m_pSamplerState );
    SAFE_RELEASE( m_pBlendState );
    SAFE_RELEASE( m_pRasterizerState );
    SAFE_RELEASE( m_pDepthStencilState );
}

bool CGraphics::CreateRenderTargetView( ) {
    ID3D11Texture2D* pBackBuffer = nullptr;

    HRESULT Result = m_pSwapChain->GetBuffer( 0, IID_PPV_ARGS( &pBackBuffer ) );
    if ( FAILED( Result ) )
        return false;

    Result = m_pDevice->CreateRenderTargetView( pBackBuffer, nullptr, &m_pRenderTargetView );
    SAFE_RELEASE( pBackBuffer );

    return SUCCEEDED( Result );
}

bool CGraphics::ResizeSwapChainBuffers( int width, int height ) {
    if ( !m_pRenderTargetView )
        return false;

    SAFE_RELEASE( m_pRenderTargetView );

    auto Result = m_pSwapChain->ResizeBuffers( 0, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0 );
    if ( FAILED( Result ) )
        return false;

    if ( !CreateRenderTargetView( ) )
        return false;

    return true;
}

bool CGraphics::RenderDrawData( ) {
    int TotalVerticesCount{ 0 }, TotalIndicesCount{ 0 };

    for ( const auto& draw_command : DrawCommands ) {
        TotalVerticesCount += static_cast< int >( draw_command->vertices.size( ) );
        TotalIndicesCount += static_cast< int >( draw_command->indices.size( ) );
    }

    if ( !m_pVertexBuffer || m_VertexBufferSize < TotalVerticesCount ) {
        if ( m_pVertexBuffer ) SAFE_RELEASE( m_pVertexBuffer );

        m_VertexBufferSize = TotalVerticesCount + 5000;

        D3D11_BUFFER_DESC BufferDescription;
        BufferDescription.Usage = D3D11_USAGE_DYNAMIC;
        BufferDescription.ByteWidth = m_VertexBufferSize * sizeof( Vertex );
        BufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        BufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        BufferDescription.MiscFlags = 0;

        if ( m_pDevice->CreateBuffer( &BufferDescription, nullptr, &m_pVertexBuffer ) < S_OK ) {
            std::cerr << "Failed to setup VertexBuffer" << std::endl;
            return false;
        }
    }

    if ( !m_pIndexBuffer || m_IndexBufferSize < TotalIndicesCount ) {
        if ( m_pIndexBuffer ) SAFE_RELEASE( m_pIndexBuffer );

        m_IndexBufferSize = TotalIndicesCount + 5000;

        D3D11_BUFFER_DESC BufferDescription;
        BufferDescription.Usage = D3D11_USAGE_DYNAMIC;
        BufferDescription.ByteWidth = m_IndexBufferSize * sizeof( std::int32_t );
        BufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
        BufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        BufferDescription.MiscFlags = 0;

        if ( m_pDevice->CreateBuffer( &BufferDescription, nullptr, &m_pIndexBuffer ) < S_OK ) {
            std::cerr << "Failed to setup IndexBuffer" << std::endl;
            return false;
        }
    }

    D3D11_MAPPED_SUBRESOURCE VertexResource;
    if ( m_pDeviceContext->Map( m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &VertexResource ) != S_OK ) {
        std::cerr << "Failed to map VertexBuffer" << std::endl;
        return false;
    }

    D3D11_MAPPED_SUBRESOURCE IndexResource;
    if ( m_pDeviceContext->Map( m_pIndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &IndexResource ) != S_OK ) {
        std::cerr << "Failed to map IndexBuffer" << std::endl;
        return false;
    }

    Vertex* VertexDst = ( Vertex* ) VertexResource.pData;
    std::int32_t* IndexDst = ( std::int32_t* ) IndexResource.pData;
    for ( const auto& draw_command : DrawCommands ) {
        memcpy( VertexDst, draw_command->vertices.data( ), draw_command->vertices.size( ) * sizeof( Vertex ) );
        memcpy( IndexDst, draw_command->indices.data( ), draw_command->indices.size( ) * sizeof( std::int32_t ) );

        VertexDst += draw_command->vertices.size( );
        IndexDst += draw_command->indices.size( );
    }

    m_pDeviceContext->Unmap( m_pVertexBuffer, 0 );
    m_pDeviceContext->Unmap( m_pIndexBuffer, 0 );

    SetupRenderState( m_pDeviceContext );

    int VertexOffset{ 0 }, IndexOffset{ 0 };
    for ( const auto& draw_command : DrawCommands ) {
        m_pDeviceContext->IASetPrimitiveTopology( draw_command->primitive_topology );
        m_pDeviceContext->PSSetShaderResources( 0, 1, ( draw_command->texture ? &draw_command->texture->pTextureSRV : &m_pTextureSRV ) );

        m_pDeviceContext->DrawIndexed( static_cast< UINT >( draw_command->indices.size( ) ), IndexOffset, VertexOffset );

        VertexOffset += static_cast< int >( draw_command->vertices.size( ) );
        IndexOffset += static_cast< int >( draw_command->indices.size( ) );
    }

    return true;
}

bool CGraphics::Present( ) {
    if ( Win32.IsResizing( m_TargetWindow ) )
        return false;

    if ( !RenderDrawData( ) )
        return false;

    auto Result = m_pSwapChain->Present( static_cast< int >( m_VSync ), 0 );

    if ( FAILED( Result ) )
        return false;

    return true;
}

void CGraphics::SetupRenderState( ID3D11DeviceContext* device_context ) {
    m_pDeviceContext->OMSetRenderTargets( 1, &m_pRenderTargetView, nullptr );

    float ClearColor[ 4 ] = {
        static_cast< float >( m_ClearColor.r ),
        static_cast< float >( m_ClearColor.g ),
        static_cast< float >( m_ClearColor.b ),
        static_cast< float >( m_ClearColor.a )
    };
    m_pDeviceContext->ClearRenderTargetView( m_pRenderTargetView, ClearColor );

    UINT Stride = sizeof( Vertex );
    UINT Offset = 0;
    device_context->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &Stride, &Offset );
    device_context->IASetIndexBuffer(
        m_pIndexBuffer,
        sizeof( std::int32_t ) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT,
        0
    );

    device_context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    device_context->IASetInputLayout( m_pInputLayout );

    device_context->VSSetShader( m_pVertexShader, nullptr, 0 );
    device_context->VSSetConstantBuffers( 0, 1, &m_pVertexConstantBuffer );
    device_context->PSSetShader( m_pPixelShader, nullptr, 0 );
    device_context->PSSetSamplers( 0, 1, &m_pSamplerState );

    device_context->GSSetShader( nullptr, nullptr, 0 );
    device_context->HSSetShader( nullptr, nullptr, 0 );
    device_context->DSSetShader( nullptr, nullptr, 0 );
    device_context->CSSetShader( nullptr, nullptr, 0 );

    device_context->OMSetDepthStencilState( m_pDepthStencilState, 0 );
    device_context->RSSetState( m_pRasterizerState );

    const float BlendFactor[ 4 ] = { 0.f, 0.f, 0.f, 0.f };
    device_context->OMSetBlendState( m_pBlendState, BlendFactor, 0xffffffff );

    RECT ClientRect;
    GetClientRect( m_TargetWindow, &ClientRect );

    D3D11_VIEWPORT Viewport = {};
    Viewport.Width = static_cast< FLOAT >( ClientRect.right - ClientRect.left );
    Viewport.Height = static_cast< FLOAT >( ClientRect.bottom - ClientRect.top );
    Viewport.MinDepth = 0.0f;
    Viewport.MaxDepth = 1.0f;
    device_context->RSSetViewports( 1, &Viewport );

    float ProjectionMatrix[ 4 ][ 4 ] = {
        {  2.0f / static_cast< float >( ClientRect.right - ClientRect.left ),         0.0f,  0.0f, 0.0f },
        {  0.0f,  2.0f / -static_cast< float >( ClientRect.bottom - ClientRect.top ), 0.0f, 0.0f },
        {  0.0f,  0.0f,  0.5f, 0.0f },
        { -1.0f,  1.0f,  0.5f, 1.0f }
    };
    SetProjectionMatrix( ProjectionMatrix );
}

struct D3D11_VERTEX_CONSTANT_BUFFER {
    float mvp[ 4 ][ 4 ];
};

void CGraphics::SetProjectionMatrix( const float matrix[ 4 ][ 4 ] ) {
    D3D11_MAPPED_SUBRESOURCE MappedResource;

    if ( m_pDeviceContext->Map( m_pVertexConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource ) == S_OK ) {
        D3D11_VERTEX_CONSTANT_BUFFER* ConstantBuffer = static_cast< D3D11_VERTEX_CONSTANT_BUFFER* >(
            MappedResource.pData
        );

        memcpy( &ConstantBuffer->mvp, matrix, sizeof( float ) * 4 * 4 );
        m_pDeviceContext->Unmap( m_pVertexConstantBuffer, 0 );
    }
}

void CGraphics::SetViewport( Vector2 position, Vector2 size, float min_depth, float max_depth ) {
    if ( !m_pDeviceContext )
        return;

    if ( size.x <= 0 || size.y <= 0 ) {
        RECT ClientRectangle;
        GetClientRect( m_TargetWindow, &ClientRectangle );

        if ( size.x <= 0 )
            size.x = static_cast< float >( ClientRectangle.right - ClientRectangle.left );

        if ( size.y <= 0 )
            size.y = static_cast< float >( ClientRectangle.bottom - ClientRectangle.top );
    }

    D3D11_VIEWPORT Viewport = {
        position.x, position.y,
        size.x, size.y,
        min_depth, max_depth
    };
    m_pDeviceContext->RSSetViewports( 1, &Viewport );
}

__forceinline ID3D11Device* CGraphics::GetDevice( ) const {
    return m_pDevice;
}

Texture* CGraphics::CreateTexture(
    const char* texture_name, D3D11_TEXTURE2D_DESC texture_description,
    D3D11_SUBRESOURCE_DATA sub_resource_data, D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_description )
{
    ID3D11Texture2D* pTexture = nullptr;
    auto Result = Graphics.GetDevice( )->CreateTexture2D( &texture_description, &sub_resource_data, &pTexture );
    if ( FAILED( Result ) ) {
#ifdef _DEBUG
        std::cout << "Failed to create pTexture for '" + std::string( texture_name ) << "'\n";
#endif
        return nullptr;
    }

    ID3D11ShaderResourceView* pTextureSRV = nullptr;
    Result = Graphics.GetDevice( )->CreateShaderResourceView( pTexture, &shader_resource_view_description, &pTextureSRV );
    if ( FAILED( Result ) ) {
#ifdef _DEBUG
        std::cout << "Failed to create pTextureSRV for '" + std::string( texture_name ) << "'\n";
#endif
        pTexture->Release( );
        return nullptr;
    }

    return new Texture( std::string( texture_name ), pTexture, pTextureSRV );
}

void CGraphics::DestroyTexture( Texture* texture ) {
    SAFE_RELEASE( texture->pTexture );
    SAFE_RELEASE( texture->pTextureSRV );

    texture = nullptr;
}

Font* CGraphics::_CreateFont( const char* font_path, int size ) {
    auto Error = FT_New_Face( m_FT, font_path, 0, &m_FTFace );
    if ( Error )
        return nullptr;

    Error = FT_Set_Pixel_Sizes( m_FTFace, 0, size );
    if ( Error )
        return nullptr;

    std::string FontName = std::filesystem::path( font_path ).stem( ).string( );
    auto _Font = new Font( FontName, size );

    // ASCII - 128
    // Extended ASCII - 256
    // Unicode - > 143,000
    for ( int i = 0; i < 128; i++ ) {
        if ( !isprint( i ) )
            continue;

        Error = FT_Load_Char( m_FTFace, i, FT_LOAD_RENDER );
        if ( Error ) {
            continue;
        }

        FT_GlyphSlot GlyphSlot = m_FTFace->glyph;
        if ( GlyphSlot->bitmap.width == 0 || GlyphSlot->bitmap.rows == 0 || GlyphSlot->bitmap.buffer == nullptr ) {
            continue;
        }

        const unsigned int width = GlyphSlot->bitmap.width;
        const unsigned int height = GlyphSlot->bitmap.rows;
        std::vector<unsigned char> Color( width * height * 4 );
        for ( unsigned int y = 0; y < height; y++ ) {
            for ( unsigned int x = 0; x < width; x++ ) {
                unsigned char gray = GlyphSlot->bitmap.buffer[ y * GlyphSlot->bitmap.pitch + x ];
                unsigned int rgbaIdx = ( y * width + x ) * 4;
                Color[ rgbaIdx + 0 ] = gray; // R
                Color[ rgbaIdx + 1 ] = gray; // G
                Color[ rgbaIdx + 2 ] = gray; // B
                Color[ rgbaIdx + 3 ] = gray; // A
            }
        }

        D3D11_TEXTURE2D_DESC TextureDesc = {};
        TextureDesc.Width = width;
        TextureDesc.Height = height;
        TextureDesc.MipLevels = 1;
        TextureDesc.ArraySize = 1;
        TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        TextureDesc.Usage = D3D11_USAGE_DEFAULT;
        TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        TextureDesc.CPUAccessFlags = 0;
        TextureDesc.SampleDesc.Count = 1;

        D3D11_SUBRESOURCE_DATA ResourceData = {};
        ResourceData.pSysMem = Color.data( );
        ResourceData.SysMemPitch = width * 4;

        D3D11_SHADER_RESOURCE_VIEW_DESC SRVDescription = {};
        SRVDescription.Format = TextureDesc.Format;
        SRVDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        SRVDescription.Texture2D.MipLevels = 1;

        std::string TextureName = FontName + "_" + std::string( 1, static_cast< char >( i ) );
        Texture* _Texture = CreateTexture( TextureName.c_str( ), TextureDesc, ResourceData, SRVDescription );

        _Font->Glyphs[ static_cast< char >( i ) ] = Glyph(
            static_cast< float >( GlyphSlot->advance.x ) / 64.0f,
            static_cast< float >( GlyphSlot->bitmap_left ),
            static_cast< float >( GlyphSlot->bitmap_top ),
            static_cast< float >( GlyphSlot->bitmap.width ),
            static_cast< float >( GlyphSlot->bitmap.rows ),
            0.f, 0.f, 1.f, 1.f, _Texture
        );
    }

    return _Font;
}

void CGraphics::DestroyFont( Font* font ) {
    for ( auto& [Char, GlyphPtr] : font->Glyphs ) {
        if ( !GlyphPtr._Texture )
            continue;

        GlyphPtr._Texture->pTexture->Release( );
        GlyphPtr._Texture->pTextureSRV->Release( );
        GlyphPtr._Texture = nullptr;
    }

    font = nullptr;
}

CGraphics Graphics;