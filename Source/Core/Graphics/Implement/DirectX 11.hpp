#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../Common.hpp"
#include "../Include.hpp"

class CGraphics {
public:
    bool Initiate(HWND hwnd, bool vertical_sync);
    bool IsInitiated( );

	void ResizeBuffers( int width, int height );
	void SetupRenderState( ID3D11DeviceContext* device_context );

	bool RenderDrawData( );
	void Present( );

	void Cleanup( );

	std::vector<DrawCommand> DrawCommands;

private:
	HWND m_TargetWindow = nullptr;

    bool m_VSync = false;

    Color m_ClearColor = { 0, 0, 0, 255 };

	int m_VertexBufferSize = 0, m_IndexBufferSize = 0;

	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pDeviceContext = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11Buffer* m_pIndexBuffer = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11InputLayout* m_pInputLayout = nullptr;
	ID3D11Buffer* m_pVertexConstantBuffer = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D11BlendState* m_pBlendState = nullptr;
	ID3D11RasterizerState* m_pRasterizerState = nullptr;
	ID3D11DepthStencilState* m_pDepthStencilState = nullptr;

	struct VERTEX_CONSTANT_BUFFER_DX11 {
		float mvp[ 4 ][ 4 ];
	};

    static constexpr const char* m_VertexShaderSource = R"(
        cbuffer vertexBuffer : register(b0) {
            float4x4 ProjectionMatrix;
        };

        struct VS_INPUT {
            float4 pos : POSITION;  // x, y, z, rhw
            float2 uv  : TEXCOORD0; // u, v
            float4 col : COLOR0;    // r, g, b, a
        };

        struct PS_INPUT {
            float4 pos : SV_POSITION;
            float4 col : COLOR0;
            float2 uv  : TEXCOORD0;
        };

        PS_INPUT main(VS_INPUT input) {
            PS_INPUT output;
        
            output.pos = mul( ProjectionMatrix, float4( input.pos.xy, 0.f, 1.f ) );
            output.col = input.col;
            output.uv  = input.uv;

            return output;
        }
    )";

    static constexpr const char* m_PixelShaderSource = R"(
        struct PS_INPUT {
            float4 pos : SV_POSITION;
            float4 col : COLOR0;
            float2 uv  : TEXCOORD0;
        };

        float4 main(PS_INPUT input) : SV_Target {
            return input.col;
        }
    )";
} extern Graphics;

#endif