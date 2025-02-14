#ifndef RENDERER_H
#define RENDERER_H

#include "../Common.hpp"
#include "../Include.hpp"

class CRenderer {
public:
	DrawCommand* WriteToBuffer( D3D_PRIMITIVE_TOPOLOGY primitive_type, std::vector<Vertex>* vertices, std::vector<int32_t>* indices );
	
	void Line( Vector2 from, Vector2 to, Color color );

	void Polyline(std::vector<Vector2> points, Color color);
	void Polygon(std::vector<Vector2> points, Color color);

	void Rectangle(Vector2 position, Vector2 size, Color color);
	void FilledRectangle(Vector2 position, Vector2 size, Color color);

private:
	int m_VerticesCount{ 0 }, m_IndicesCount{ 0 };

} extern Renderer;

#endif