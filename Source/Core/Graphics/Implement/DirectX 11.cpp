#include "DirectX 11.hpp"

#include "../../Win32/Win32.hpp"

#define SAFE_RELEASE(p) if (p) { \
    p->Release(); \
    p = nullptr; \
}

bool CGraphics::Initiate( HWND hwnd, bool vertical_sync ) {
    m_TargetWindow = hwnd;
    m_VSync = vertical_sync;

    RECT Rect;
    GetClientRect( hwnd, &Rect );

    DXGI_SWAP_CHAIN_DESC SwapChainDescription = {};
    SwapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    SwapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    SwapChainDescription.OutputWindow = hwnd;
    SwapChainDescription.SampleDesc.Count = 1;
    SwapChainDescription.Windowed = TRUE;
    SwapChainDescription.BufferCount = 1;
    SwapChainDescription.BufferDesc.Width = Rect.right - Rect.left;
    SwapChainDescription.BufferDesc.Height = Rect.bottom - Rect.top;
    SwapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    if ( D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &SwapChainDescription, &m_pSwapChain, &m_pDevice, nullptr, &m_pDeviceContext ) < S_OK )
        return FALSE;

    { // Back buffer
        ID3D11Texture2D* BackBuffer;

        m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( void** ) &BackBuffer );

        if ( m_pDevice->CreateRenderTargetView( BackBuffer, nullptr, &m_pRenderTargetView ) < S_OK ) {
            SAFE_RELEASE( BackBuffer );
            return FALSE;
        }

        SAFE_RELEASE( BackBuffer );
    }

    { // Vertex shader
        ID3DBlob* VertexShaderBlob;

        if ( FAILED( D3DCompile( m_VertexShaderSource, strlen( m_VertexShaderSource ), nullptr, nullptr, nullptr, "main", "vs_4_0", 0, 0, &VertexShaderBlob, nullptr ) ) )
            return FALSE;

        if ( m_pDevice->CreateVertexShader( VertexShaderBlob->GetBufferPointer( ), VertexShaderBlob->GetBufferSize( ), nullptr, &m_pVertexShader ) != S_OK ) {
            SAFE_RELEASE( VertexShaderBlob );
            return FALSE;
        }

        D3D11_INPUT_ELEMENT_DESC LocalLayout[] = {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },  // x, y, z, rhw
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },  // u, v
            { "COLOR", 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }   // color
        };

        if ( m_pDevice->CreateInputLayout( LocalLayout, 3, VertexShaderBlob->GetBufferPointer( ), VertexShaderBlob->GetBufferSize( ), &m_pInputLayout ) != S_OK ) {
            SAFE_RELEASE( VertexShaderBlob );
            return FALSE;
        }

        SAFE_RELEASE( VertexShaderBlob );
    }

    // Vertex constant buffer
    {
        D3D11_BUFFER_DESC BufferDescription;
        BufferDescription.ByteWidth = sizeof( VERTEX_CONSTANT_BUFFER_DX11 );
        BufferDescription.Usage = D3D11_USAGE_DYNAMIC;
        BufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        BufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        BufferDescription.MiscFlags = 0;

        m_pDevice->CreateBuffer( &BufferDescription, nullptr, &m_pVertexConstantBuffer );
    }

    { // Pixel shader
        ID3DBlob* PixelShaderBlob;

        if ( FAILED( D3DCompile( m_PixelShaderSource, strlen( m_PixelShaderSource ), nullptr, nullptr, nullptr, "main", "ps_4_0", 0, 0, &PixelShaderBlob, nullptr ) ) )
            return FALSE;

        if ( m_pDevice->CreatePixelShader( PixelShaderBlob->GetBufferPointer( ), PixelShaderBlob->GetBufferSize( ), nullptr, &m_pPixelShader ) != S_OK ) {
            SAFE_RELEASE( PixelShaderBlob );
            return false;
        }

        SAFE_RELEASE( PixelShaderBlob );
    }

    { // Rasterizer state
        D3D11_RASTERIZER_DESC RasterizerDescription = {};
        RasterizerDescription.FillMode = D3D11_FILL_SOLID;
        RasterizerDescription.CullMode = D3D11_CULL_NONE;
        RasterizerDescription.ScissorEnable = false;
        RasterizerDescription.DepthClipEnable = true;
        
        m_pDevice->CreateRasterizerState( &RasterizerDescription, &m_pRasterizerState );
    }

    // Create depth stencil state
    {
        D3D11_DEPTH_STENCIL_DESC DepthStencilDescription;

        DepthStencilDescription.DepthEnable = false;
        DepthStencilDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        DepthStencilDescription.DepthFunc = D3D11_COMPARISON_ALWAYS;
        DepthStencilDescription.StencilEnable = false;
        DepthStencilDescription.FrontFace.StencilFailOp = DepthStencilDescription.FrontFace.StencilDepthFailOp = DepthStencilDescription.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        DepthStencilDescription.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        DepthStencilDescription.BackFace = DepthStencilDescription.FrontFace;

        m_pDevice->CreateDepthStencilState( &DepthStencilDescription, &m_pDepthStencilState );
    }

    { // Blend state
        D3D11_BLEND_DESC BlendDescription = {};
        BlendDescription.AlphaToCoverageEnable = false;
        BlendDescription.RenderTarget[ 0 ].BlendEnable = true;
        BlendDescription.RenderTarget[ 0 ].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        BlendDescription.RenderTarget[ 0 ].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        BlendDescription.RenderTarget[ 0 ].BlendOp = D3D11_BLEND_OP_ADD;
        BlendDescription.RenderTarget[ 0 ].SrcBlendAlpha = D3D11_BLEND_ONE;
        BlendDescription.RenderTarget[ 0 ].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
        BlendDescription.RenderTarget[ 0 ].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        BlendDescription.RenderTarget[ 0 ].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

        m_pDevice->CreateBlendState( &BlendDescription, &m_pBlendState );
    }

    return true;
}

bool CGraphics::IsInitiated( ) {
    return m_pDevice != nullptr;
}

void CGraphics::ResizeBuffers( int width, int height ) {
    if ( !m_pRenderTargetView )
        return;

    SAFE_RELEASE( m_pRenderTargetView );

    m_pSwapChain->ResizeBuffers( 0, width, height, DXGI_FORMAT_UNKNOWN, 0 );

    { // Create render target
        ID3D11Texture2D* pBackBuffer;

        m_pSwapChain->GetBuffer( 0, IID_PPV_ARGS( &pBackBuffer ) );

        if ( m_pDevice->CreateRenderTargetView( pBackBuffer, nullptr, &m_pRenderTargetView ) < S_OK ) {
            SAFE_RELEASE( pBackBuffer );
            return;
        }

        SAFE_RELEASE( pBackBuffer );
    }
}

void CGraphics::SetupRenderState( ID3D11DeviceContext* device_context ) {
    RECT Rect;
    GetClientRect( m_TargetWindow, &Rect );

    { // Setup viewport
        D3D11_VIEWPORT Viewport = {};
        Viewport.Width = static_cast< FLOAT >( Rect.right - Rect.left );
        Viewport.Height = static_cast< FLOAT >( Rect.bottom - Rect.top );
        Viewport.MinDepth = 0.f;
        Viewport.MaxDepth = 1.0f;

        device_context->RSSetViewports( 1, &Viewport );
    }

    { // Setup projection matrix
        D3D11_MAPPED_SUBRESOURCE mapped_resource;
        if ( m_pDeviceContext->Map( m_pVertexConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource ) == S_OK ) {
            VERTEX_CONSTANT_BUFFER_DX11* ConstantBuffer = ( VERTEX_CONSTANT_BUFFER_DX11* ) mapped_resource.pData;

            float mvp[ 4 ][ 4 ] = {
                { 2.0f / static_cast< float >( Rect.right - Rect.left ), 0.f, 0.f, 0.f },
                { 0.f, 2.0f / -static_cast< float >( Rect.bottom - Rect.top ), 0.f, 0.f },
                { 0.f, 0.f, 0.5f, 0.f },
                { static_cast< float >( Rect.right - Rect.left ) / -static_cast< float >( Rect.right - Rect.left ), 1.f, 0.5f, 1.0f},
            };

            memcpy( &ConstantBuffer->mvp, mvp, sizeof( mvp ) );
            m_pDeviceContext->Unmap( m_pVertexConstantBuffer, 0 );
        }
    }

    device_context->OMSetRenderTargets( 1, &m_pRenderTargetView, nullptr );

    unsigned int Stride = sizeof( Vertex ), Offset = 0;

    device_context->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &Stride, &Offset );
    device_context->IASetIndexBuffer( m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0 );
    device_context->VSSetShader( m_pVertexShader, nullptr, 0 );
    device_context->PSSetShader( m_pPixelShader, nullptr, 0 );
    device_context->IASetInputLayout( m_pInputLayout );

    device_context->IASetInputLayout( m_pInputLayout );
    device_context->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &Stride, &Offset );
    device_context->IASetIndexBuffer( m_pIndexBuffer, sizeof( std::int32_t ) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, 0 );
    device_context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    device_context->VSSetShader( m_pVertexShader, nullptr, 0 );
    device_context->VSSetConstantBuffers( 0, 1, &m_pVertexConstantBuffer );
    device_context->PSSetShader( m_pPixelShader, nullptr, 0 );
    device_context->GSSetShader( nullptr, nullptr, 0 );
    device_context->HSSetShader( nullptr, nullptr, 0 );
    device_context->DSSetShader( nullptr, nullptr, 0 );
    device_context->CSSetShader( nullptr, nullptr, 0 );

    const float BlendFactor[ 4 ] = { 0.f, 0.f, 0.f, 0.f };
    device_context->OMSetBlendState( m_pBlendState, BlendFactor, 0xffffffff );
    device_context->OMSetDepthStencilState( m_pDepthStencilState, 0 );
    device_context->RSSetState( m_pRasterizerState );
}

// CREDITS: https://github.com/ocornut/imgui/blob/master/backends/imgui_impl_dx11.cpp#L147
bool CGraphics::RenderDrawData( ) {
    int TotalVerticesCount{ 0 }, TotalIndicesCount{ 0 };

    std::sort( DrawCommands.begin( ), DrawCommands.end( ), [ ] ( const DrawCommand& a, const DrawCommand& b ) {
        return a.z_index < b.z_index;
    } );

    for ( DrawCommand& draw_command : DrawCommands ) {
        TotalVerticesCount += static_cast< int >( draw_command.vertices.size( ) );
        TotalIndicesCount += static_cast< int >( draw_command.indices.size( ) );
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
            return FALSE;
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
            return FALSE;
        }
    }

    D3D11_MAPPED_SUBRESOURCE VertexResource, IndexResource;

    if ( m_pDeviceContext->Map( m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &VertexResource ) != S_OK ) {
        std::cerr << "[Graphics::RenderDrawData] Failed to map VertexBuffer" << std::endl;
        return FALSE;
    }

    if ( m_pDeviceContext->Map( m_pIndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &IndexResource ) != S_OK ) {
        std::cerr << "[Graphics::RenderDrawData] Failed to map IndexBuffer" << std::endl;
        return FALSE;
    }

    {
        Vertex* VertexDst = ( Vertex* ) VertexResource.pData;
        std::int32_t* IndexDst = ( std::int32_t* ) IndexResource.pData;

        for ( DrawCommand& draw_command : DrawCommands ) {
            memcpy( VertexDst, draw_command.vertices.data( ), draw_command.vertices.size( ) * sizeof( Vertex ) );
            memcpy( IndexDst, draw_command.indices.data( ), draw_command.indices.size( ) * sizeof( std::int32_t ) );

            VertexDst += draw_command.vertices.size( );
            IndexDst += draw_command.indices.size( );
        }

        m_pDeviceContext->Unmap( m_pVertexBuffer, 0 );
        m_pDeviceContext->Unmap( m_pIndexBuffer, 0 );
    }

    SetupRenderState( m_pDeviceContext );

    int VertexOffset{ 0 }, IndexOffset{ 0 };

    for ( DrawCommand& draw_command : DrawCommands ) {
        m_pDeviceContext->IASetPrimitiveTopology( draw_command.primitive_topology );
        m_pDeviceContext->DrawIndexed( static_cast< UINT >( draw_command.indices.size( ) ), IndexOffset, VertexOffset );

        VertexOffset += static_cast< int >( draw_command.vertices.size( ) );
        IndexOffset += static_cast< int >( draw_command.indices.size( ) );
    }

    return TRUE;
}

void CGraphics::Present( ) {
    if ( Win32.IsResizing( m_TargetWindow ) )
        return;

    float ClearColor[] = { 
        static_cast< float >( m_ClearColor.r ),
        static_cast< float >( m_ClearColor.g ),
        static_cast< float >( m_ClearColor.b ),
        static_cast< float >( m_ClearColor.a )
    };

    m_pDeviceContext->OMSetRenderTargets( 1, &m_pRenderTargetView, nullptr );
    m_pDeviceContext->ClearRenderTargetView( m_pRenderTargetView, ClearColor );

    RenderDrawData( );

    m_pSwapChain->Present( static_cast<int>( m_VSync ), 0 );
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
    SAFE_RELEASE( m_pBlendState );
    SAFE_RELEASE( m_pRasterizerState );
    SAFE_RELEASE( m_pDepthStencilState );
}

CGraphics Graphics;