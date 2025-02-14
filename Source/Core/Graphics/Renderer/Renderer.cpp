#include "Renderer.hpp"

#define RGBA_TO_DWORD(r, g, b, a) ((DWORD)((((a) & 0xff) << 24) | (((r) & 0xff) << 16) | (((g) & 0xff) << 8) | ((b) & 0xff)))

DrawCommand* CRenderer::WriteToBuffer( D3D_PRIMITIVE_TOPOLOGY primitive_type, std::vector<Vertex>* vertices, std::vector<int32_t>* indices ) {
	m_VerticesCount += vertices->size( );
	m_IndicesCount += indices->size( );

	Graphics.DrawCommands.push_back(DrawCommand(
		primitive_type, *vertices, *indices
	));

	return &Graphics.DrawCommands.back( );
}

void CRenderer::Line( Vector2 from, Vector2 to, Color color ) {
	std::vector<Vertex> Vertices = {
		{ ( float ) from.x, ( float ) from.y, 0.f, 1.f, 0.f, 0.f, RGBA_TO_DWORD( color.r, color.g, color.b, color.a ) },
		{ ( float ) to.x, ( float ) to.y, 0.f, 1.f, 0.f, 0.f, RGBA_TO_DWORD( color.r, color.g, color.b, color.a ) },
	};

	std::vector<int32_t> Indices = {
		0, 1
	};

	WriteToBuffer( D3D11_PRIMITIVE_TOPOLOGY_LINELIST, &Vertices, &Indices );
}

void CRenderer::Polyline( std::vector<Vector2> points, Color color ) {
	std::vector<Vertex> Vertices = {};
	std::vector<int32_t> Indices = {};

	for ( int i = 0; i < points.size( ); i++ ) {
		Vector2 Point = points[ i ];

		Vertices.push_back( 
			Vertex( Point.x, Point.y, 0, 1.f, 0.f, 0.f, RGBA_TO_DWORD( color.r, color.g, color.b, color.a ) )
		);

		Indices.push_back( i );
	}

	WriteToBuffer( D3D11_PRIMITIVE_TOPOLOGY_LINELIST, &Vertices, &Indices );
}

void CRenderer::Polygon( std::vector<Vector2> points, Color color ) {
	std::vector<Vertex> Vertices = {};
	std::vector<int32_t> Indices = {};

	for ( int i = 0; i < points.size( ); i++ ) {
		Vector2 Point = points[ i ];

		Vertices.push_back(
			Vertex( Point.x, Point.y, 0, 1.f, 0.f, 0.f, RGBA_TO_DWORD( color.r, color.g, color.b, color.a ) )
		);

		Indices.push_back( 0 );
		Indices.push_back( i );
		Indices.push_back( i + 1 );
	}

	WriteToBuffer( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, &Vertices, &Indices );
}

void CRenderer::Rectangle( Vector2 position, Vector2 size, Color color ) {
	std::vector<Vertex> Vertices = {
		{ ( float ) position.x, ( float ) position.y, 0.f, 1.f, 0.f, 0.f, RGBA_TO_DWORD( color.r, color.g, color.b, color.a ) },
		{ ( float ) position.x + ( float ) size.x, ( float ) position.y, 0.f, 1.f, 0.f, 0.f, RGBA_TO_DWORD( color.r, color.g, color.b, color.a ) },
		{ ( float ) position.x + ( float ) size.x, ( float ) position.y + ( float ) size.y, 0.f, 1.f, 0.f, 0.f, RGBA_TO_DWORD( color.r, color.g, color.b, color.a ) },
		{ ( float ) position.x, ( float ) position.y + ( float ) size.y, 0.f, 1.f, 0.f, 0.f, RGBA_TO_DWORD( color.r, color.g, color.b, color.a ) }
	};

	std::vector<int32_t> Indices = {
		0, 1, 2, 3, 0
	};

	WriteToBuffer( D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP, &Vertices, &Indices );
}

void CRenderer::FilledRectangle( Vector2 position, Vector2 size, Color color ) {
	std::vector<Vertex> Vertices = {
		{ ( float ) position.x, ( float ) position.y, 0.f, 1.f, 0.f, 0.f, RGBA_TO_DWORD( color.r, color.g, color.b, color.a ) },
		{ ( float ) position.x + ( float ) size.x, ( float ) position.y, 0.f, 1.f, 0.f, 0.f, RGBA_TO_DWORD( color.r, color.g, color.b, color.a ) },
		{ ( float ) position.x + ( float ) size.x, ( float ) position.y + ( float ) size.y, 0.f, 1.f, 0.f, 0.f, RGBA_TO_DWORD( color.r, color.g, color.b, color.a ) },
		{ ( float ) position.x, ( float ) position.y + ( float ) size.y, 0.f, 1.f, 0.f, 0.f, RGBA_TO_DWORD( color.r, color.g, color.b, color.a ) }
	};

	std::vector<int32_t> Indices = {
		0, 1, 2, 3, 0
	};

	WriteToBuffer( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, &Vertices, &Indices );
}

CRenderer Renderer;