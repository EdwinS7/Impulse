#include "Renderer.hpp"

#define RGBA_TO_DWORD(r, g, b, a) ((DWORD)((((a) & 0xff) << 24) | (((r) & 0xff) << 16) | (((g) & 0xff) << 8) | ((b) & 0xff)))

DrawCommand* CRenderer::WriteToBuffer( D3D_PRIMITIVE_TOPOLOGY primitive_topology, std::vector<Vertex>* vertices, std::vector<int32_t>* indices, int z_index ) {
	m_VerticesCount += static_cast< int >( vertices->size( ) );
	m_IndicesCount += static_cast< int >( indices->size( ) );

	Graphics.DrawCommands.push_back(DrawCommand(
		primitive_topology, *vertices, *indices, z_index
	));

	return &Graphics.DrawCommands.back( );
}

CRenderer Renderer;