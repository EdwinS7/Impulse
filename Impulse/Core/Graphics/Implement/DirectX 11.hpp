#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../Common.hpp"
#include "../Include.hpp"

struct VERTEX_CONSTANT_BUFFER_DX11 {
	float mvp[ 4 ][ 4 ];
};

class CGraphics {
public:
	bool Initiate( 
		HWND hwnd, 
		DXGI_SWAP_CHAIN_DESC swap_chain_description, 
		D3D11_BUFFER_DESC buffer_description, 
		D3D11_RASTERIZER_DESC rasterizer_description,
		D3D11_DEPTH_STENCIL_DESC depth_stencil_description, 
		D3D11_SAMPLER_DESC sampler_description, 
		D3D11_BLEND_DESC blend_description, 
		const char* vertex_shader_source, 
		const char* pixel_shader_source 
	);

	bool IsDeviceInitialized( ) const;

    void ResizeSwapChainBuffers( int width, int height );
    void SetProjectionMatrix( const float matrix[ 4 ][ 4 ] );
	void SetupRenderState( ID3D11DeviceContext* device_context );
    
	void SetViewport( 
		Vector2 position, Vector2 size, 
		float min_depth = 0.0f, float max_depth = 1.0f
	);

	ID3D11Device* GetDevice( );

	bool RenderDrawData( );
	bool Present( );


	Texture* CreateTexture( const char* texture_name, D3D11_TEXTURE2D_DESC texture_description, D3D11_SUBRESOURCE_DATA sub_resource_data, D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_description );
	void DestroyTexture( const char* texture_name );

	void Cleanup( );

	std::vector<std::unique_ptr<DrawCommand>> DrawCommands;

private:
	/* Runtime flags */
    bool m_VSync = true;
    Color m_ClearColor = { 0, 0, 0, 255 };

	/* Window / Swap-chain */
	HWND m_TargetWindow = nullptr;
	IDXGISwapChain* m_pSwapChain = nullptr;

	/* D3D11 objects */
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pDeviceContext = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;

	/* Texture */
	ID3D11Texture2D* m_pTexture = nullptr;
	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;

	/* Dynamic buffers */
	int m_VertexBufferSize = 0, m_IndexBufferSize = 0;

	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11Buffer* m_pIndexBuffer = nullptr;

	/* Shaders */
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11InputLayout* m_pInputLayout = nullptr;
	ID3D11Buffer* m_pVertexConstantBuffer = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;

	/* States */
	ID3D11BlendState* m_pBlendState = nullptr;
	ID3D11SamplerState* m_pSamplerState = nullptr;
	ID3D11RasterizerState* m_pRasterizerState = nullptr;
	ID3D11DepthStencilState* m_pDepthStencilState = nullptr;
} extern Graphics;

#endif