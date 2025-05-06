#include "DirectX 11.hpp"
#include "../../Win32/Win32.hpp"

bool CGraphics::Initiate( 
    HWND hwnd, DXGI_SWAP_CHAIN_DESC swap_chain_description, D3D11_BUFFER_DESC buffer_description, 
    D3D11_RASTERIZER_DESC rasterizer_description, D3D11_DEPTH_STENCIL_DESC depth_stencil_description, 
    D3D11_SAMPLER_DESC sampler_description, D3D11_BLEND_DESC blend_description, 
    const char* vertex_shader_source, const char* pixel_shader_source )
{
    if ( D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swap_chain_description, &m_pSwapChain, &m_pDevice, nullptr, &m_pDeviceContext ) < S_OK )
        return false;
    
    { // Create back buffer
        ID3D11Texture2D* pBackBuffer;

        m_pSwapChain->GetBuffer( 0, IID_PPV_ARGS( &pBackBuffer ) );

        if ( m_pDevice->CreateRenderTargetView( pBackBuffer, nullptr, &m_pRenderTargetView ) < S_OK ) {
            SAFE_RELEASE( pBackBuffer );
            return false;
        }

        SAFE_RELEASE( pBackBuffer );
    }

    { // Compile and create vertex shader
        ID3DBlob* VertexShaderBlob;

        if ( FAILED( D3DCompile( vertex_shader_source, strlen( vertex_shader_source ), nullptr, nullptr, nullptr, "main", "vs_4_0", 0, 0, &VertexShaderBlob, nullptr ) ) )
            return false;

        if ( m_pDevice->CreateVertexShader( VertexShaderBlob->GetBufferPointer( ), VertexShaderBlob->GetBufferSize( ), nullptr, &m_pVertexShader ) != S_OK ) {
            SAFE_RELEASE( VertexShaderBlob );
            return false;
        }

        D3D11_INPUT_ELEMENT_DESC LocalLayout[] = {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },  // x, y, z, rhw
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },  // u, v
            { "COLOR", 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }   // color
        };

        if ( m_pDevice->CreateInputLayout( LocalLayout, 3, VertexShaderBlob->GetBufferPointer( ), VertexShaderBlob->GetBufferSize( ), &m_pInputLayout ) != S_OK ) {
            SAFE_RELEASE( VertexShaderBlob );
            return false;
        }

        SAFE_RELEASE( VertexShaderBlob );
    }

    { // Compile and create pixel shader
        ID3DBlob* PixelShaderBlob;

        if ( FAILED( D3DCompile( pixel_shader_source, strlen( pixel_shader_source ), nullptr, nullptr, nullptr, "main", "ps_4_0", 0, 0, &PixelShaderBlob, nullptr ) ) )
            return false;

        if ( m_pDevice->CreatePixelShader( PixelShaderBlob->GetBufferPointer( ), PixelShaderBlob->GetBufferSize( ), nullptr, &m_pPixelShader ) != S_OK ) {
            SAFE_RELEASE( PixelShaderBlob );
            return false;
        }

        SAFE_RELEASE( PixelShaderBlob );
    }

    { // Create white texture / back buffer ig? idfk what to call it lmao
        unsigned char WhitePixel[ 4 ] = { 255, 255, 255, 255 };

        D3D11_TEXTURE2D_DESC TextureDescription;
        ZeroMemory( &TextureDescription, sizeof( TextureDescription ) );

        TextureDescription.Width = TextureDescription.Height = 1;
        TextureDescription.MipLevels = 1;
        TextureDescription.ArraySize = 1;
        TextureDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        TextureDescription.SampleDesc.Count = 1;
        TextureDescription.Usage = D3D11_USAGE_DEFAULT;
        TextureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        TextureDescription.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA ResourceData{ WhitePixel, sizeof( WhitePixel ), 0 };

        m_pDevice->CreateTexture2D( &TextureDescription, &ResourceData, &m_pTexture );
        m_pDevice->CreateShaderResourceView( m_pTexture, nullptr, &m_pTextureSRV );

        m_pTexture->Release( );
    }

    m_pDevice->CreateBuffer( &buffer_description, nullptr, &m_pVertexConstantBuffer );
    m_pDevice->CreateRasterizerState( &rasterizer_description, &m_pRasterizerState );
    m_pDevice->CreateDepthStencilState( &depth_stencil_description, &m_pDepthStencilState );
    m_pDevice->CreateSamplerState( &sampler_description, &m_pSamplerState );
    m_pDevice->CreateBlendState( &blend_description, &m_pBlendState );

    m_TargetWindow = hwnd;

    return true;
}

bool CGraphics::IsDeviceInitialized( ) const {
    return m_pDevice != nullptr;
}

void CGraphics::ResizeSwapChainBuffers( int width, int height ) {
    if ( !m_pRenderTargetView )
        return;

    SAFE_RELEASE( m_pRenderTargetView );

    m_pSwapChain->ResizeBuffers( 0, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0 );

    ID3D11Texture2D* pBackBuffer;

    m_pSwapChain->GetBuffer( 0, IID_PPV_ARGS( &pBackBuffer ) );
    m_pDevice->CreateRenderTargetView( pBackBuffer, nullptr, &m_pRenderTargetView );

    SAFE_RELEASE( pBackBuffer );
}

void CGraphics::SetProjectionMatrix( const float matrix[ 4 ][ 4 ] ) {
    D3D11_MAPPED_SUBRESOURCE MappedResource;

    if ( m_pDeviceContext->Map( m_pVertexConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource ) == S_OK ) {
        VERTEX_CONSTANT_BUFFER_DX11* ConstantBuffer = ( VERTEX_CONSTANT_BUFFER_DX11* ) MappedResource.pData;
        memcpy( &ConstantBuffer->mvp, matrix, sizeof( float ) * 4 * 4 );

        m_pDeviceContext->Unmap( m_pVertexConstantBuffer, 0 );
    }
}

void CGraphics::SetupRenderState( ID3D11DeviceContext* device_context ) {
    RECT Rect;
    GetClientRect( m_TargetWindow, &Rect );

    D3D11_VIEWPORT Viewport = {};

    Viewport.Width = static_cast< FLOAT >( Rect.right - Rect.left );
    Viewport.Height = static_cast< FLOAT >( Rect.bottom - Rect.top );
    Viewport.MinDepth = 0.f;
    Viewport.MaxDepth = 1.0f;

    device_context->RSSetViewports( 1, &Viewport );

    float ProjectionMatrix[ 4 ][ 4 ] = {
            { 2.0f / static_cast< float >( Rect.right - Rect.left ), 0.f, 0.f, 0.f },
            { 0.f, 2.0f / -static_cast< float >( Rect.bottom - Rect.top ), 0.f, 0.f },
            { 0.f, 0.f, 0.5f, 0.f },
            { -1.f, 1.f, 0.5f, 1.0f },
    };

    SetProjectionMatrix( ProjectionMatrix );

    float ClearColor[] = {
        static_cast< float >( m_ClearColor.r ),
        static_cast< float >( m_ClearColor.g ),
        static_cast< float >( m_ClearColor.b ),
        static_cast< float >( m_ClearColor.a )
    };

    m_pDeviceContext->OMSetRenderTargets( 1, &m_pRenderTargetView, nullptr );
    m_pDeviceContext->ClearRenderTargetView( m_pRenderTargetView, ClearColor );

    unsigned int Stride = sizeof( Vertex ), Offset = 0;
    device_context->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &Stride, &Offset );

    device_context->IASetIndexBuffer( m_pIndexBuffer, sizeof( std::int32_t ) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, 0 );
    device_context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    device_context->VSSetConstantBuffers( 0, 1, &m_pVertexConstantBuffer );
    device_context->VSSetShader( m_pVertexShader, nullptr, 0 );
    device_context->PSSetShader( m_pPixelShader, nullptr, 0 );
    device_context->PSSetSamplers( 0, 1, &m_pSamplerState );
    device_context->IASetInputLayout( m_pInputLayout );
    device_context->GSSetShader( nullptr, nullptr, 0 );
    device_context->HSSetShader( nullptr, nullptr, 0 );
    device_context->DSSetShader( nullptr, nullptr, 0 );
    device_context->CSSetShader( nullptr, nullptr, 0 );

    const float BlendFactor[ 4 ] = { 0.f, 0.f, 0.f, 0.f };
    device_context->OMSetBlendState( m_pBlendState, BlendFactor, 0xffffffff );

    device_context->OMSetDepthStencilState( m_pDepthStencilState, 0 );
    device_context->RSSetState( m_pRasterizerState );
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
        position.x,
        position.y,
        size.x,
        size.y,
        min_depth,
        max_depth
    };

    m_pDeviceContext->RSSetViewports( 1, &Viewport );
}

ID3D11Device* CGraphics::GetDevice( ) {
    return m_pDevice;
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
            std::cerr << "[Graphics::RenderDrawData] Failed to setup VertexBuffer" << std::endl;
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
            std::cerr << "[Graphics::RenderDrawData] Failed to setup IndexBuffer" << std::endl;
            return false;
        }
    }

    D3D11_MAPPED_SUBRESOURCE VertexResource, IndexResource;

    if ( m_pDeviceContext->Map( m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &VertexResource ) != S_OK ) {
        std::cerr << "[Graphics::RenderDrawData] Failed to map VertexBuffer" << std::endl;
        return false;
    }

    if ( m_pDeviceContext->Map( m_pIndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &IndexResource ) != S_OK ) {
        std::cerr << "[Graphics::RenderDrawData] Failed to map IndexBuffer" << std::endl;
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

    if ( m_pSwapChain->Present( static_cast< int >( m_VSync ), 0 ) != S_OK )
        return false;

    return true;
}

Texture* CGraphics::CreateTexture( const char* texture_name, D3D11_TEXTURE2D_DESC texture_description, D3D11_SUBRESOURCE_DATA sub_resource_data, D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_description ) {
    ID3D11Texture2D* pTexture = nullptr;

    if ( FAILED( Graphics.GetDevice( )->CreateTexture2D( &texture_description, &sub_resource_data, &pTexture ) ) )
        throw std::runtime_error( "Failed to create texture: " + std::string( texture_name ) );

    ID3D11ShaderResourceView* pTextureSRV = nullptr;

    if ( FAILED( Graphics.GetDevice( )->CreateShaderResourceView( pTexture, &shader_resource_view_description, &pTextureSRV ) ) )
        throw std::runtime_error( "Failed to create shader resource view for texture: " + std::string( texture_name ) );

    return new Texture( texture_name, pTexture, pTextureSRV );
}

void CGraphics::DestroyTexture( const char* texture_name ) {
    /*auto Texture = pTextures[ texture_name ];

    if ( Texture ) {
        Texture->Name = nullptr;

        SAFE_RELEASE( Texture->pTexture );
        SAFE_RELEASE( Texture->pTextureSRV );
    }

    Texture = nullptr;*/
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

CGraphics Graphics;