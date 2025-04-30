#ifndef RENDERER_H
#define RENDERER_H

#include "../Common.hpp"
#include "../Include.hpp"

class CRenderer {
public:
	DrawCommand* WriteToBuffer( D3D_PRIMITIVE_TOPOLOGY primitive_topology, std::vector<Vertex>* vertices, std::vector<int32_t>* indices, int z_index = 0 );

	ID3D11Texture2D* CreateTexture( const char* texture_name, D3D11_TEXTURE2D_DESC texture_description, D3D11_SUBRESOURCE_DATA sub_resource_data, D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_description );
	void DestroyTexture( const char* texture_name );

private:
	std::unordered_map<const char*, Texture*> m_pTextures;

	int m_VerticesCount{ 0 }, m_IndicesCount{ 0 };

} extern Renderer;

#endif 