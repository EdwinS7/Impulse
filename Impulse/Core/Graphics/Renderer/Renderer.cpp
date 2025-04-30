#include "Renderer.hpp"

DrawCommand* CRenderer::WriteToBuffer( D3D_PRIMITIVE_TOPOLOGY primitive_topology, std::vector<Vertex>* vertices, std::vector<int32_t>* indices, int z_index ) {
	m_VerticesCount += static_cast< int >( vertices->size( ) );
	m_IndicesCount += static_cast< int >( indices->size( ) );

	Graphics.DrawCommands.push_back(DrawCommand(
		primitive_topology, *vertices, *indices, z_index
	));

	return &Graphics.DrawCommands.back( );
}

ID3D11Texture2D* CRenderer::CreateTexture( const char* texture_name, D3D11_TEXTURE2D_DESC texture_description, D3D11_SUBRESOURCE_DATA sub_resource_data, D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_description ) {
	ID3D11Texture2D* pTexture = nullptr;

	if ( FAILED( Graphics.GetDevice()->CreateTexture2D( &texture_description, &sub_resource_data, &pTexture ) ) )
		throw std::runtime_error( "Failed to create texture: " + std::string( texture_name ) );

	ID3D11ShaderResourceView* pTextureSRV = nullptr;

	if ( FAILED( Graphics.GetDevice( )->CreateShaderResourceView( pTexture, &shader_resource_view_description, &pTextureSRV ) ) )
		throw std::runtime_error( "Failed to create shader resource view for texture: " + std::string( texture_name ) );

	auto _Texture = Texture( texture_name, pTexture, pTextureSRV );
	m_pTextures[ texture_name ] = &_Texture;

	return pTexture;
}

void CRenderer::DestroyTexture( const char* texture_name ) {
	auto Texture = m_pTextures[ texture_name ];

	if ( Texture ) {
		Texture->Name = nullptr;

		SAFE_RELEASE( Texture->pTexture );
		SAFE_RELEASE( Texture->pTextureSRV );
	}

	Texture = nullptr;
}

CRenderer Renderer;