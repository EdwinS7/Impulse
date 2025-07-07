#ifndef RENDERER_H
#define RENDERER_H

#include "../Common.hpp"
#include "../Include.hpp"

class CRenderer {
private:
	int m_VerticesCount{ 0 }, m_IndicesCount{ 0 };

public:
	DrawCommand* WriteToBuffer( 
		D3D_PRIMITIVE_TOPOLOGY primitive_topology, 
		const std::vector<Vertex>* vertices, 
		const std::vector<int32_t>* indices, 
		Texture* texture, 
		int z_index
	);

    bool RemoveFromBuffer( DrawCommand* draw_command );
} extern Renderer;

#endif 