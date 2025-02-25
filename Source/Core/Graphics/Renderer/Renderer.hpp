#ifndef RENDERER_H
#define RENDERER_H

#include "../Common.hpp"
#include "../Include.hpp"

class CRenderer {
public:
	DrawCommand* WriteToBuffer( D3D_PRIMITIVE_TOPOLOGY primitive_topology, std::vector<Vertex>* vertices, std::vector<int32_t>* indices, int z_index = 0 );

private:
	int m_VerticesCount{ 0 }, m_IndicesCount{ 0 };

} extern Renderer;

#endif