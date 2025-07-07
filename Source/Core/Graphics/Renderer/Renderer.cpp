#include "Renderer.hpp"

#include "../../FileSystem/FileSystem.hpp"

DrawCommand* CRenderer::WriteToBuffer( D3D_PRIMITIVE_TOPOLOGY primitive_topology, const std::vector<Vertex>* vertices, const std::vector<int32_t>* indices, Texture* texture, int z_index ) {
    m_VerticesCount += static_cast< int >( vertices->size( ) );
    m_IndicesCount += static_cast< int >( indices->size( ) );

    auto Command = std::make_unique<DrawCommand>(
        primitive_topology, 
        *vertices, 
        *indices,
        texture,
        z_index
    );

    DrawCommand* CommandPointer = Command.get( );

    Graphics.DrawCommands.push_back( std::move( Command ) );

    std::sort( Graphics.DrawCommands.begin( ), Graphics.DrawCommands.end( ), [ ] ( auto const& a, auto const& b ) {
        return a->ZIndex < b->ZIndex;
    } );

    return CommandPointer;
}

bool CRenderer::RemoveFromBuffer( DrawCommand* draw_command ) {
	auto it = std::find_if( Graphics.DrawCommands.begin( ), Graphics.DrawCommands.end( ), [ & ] ( const std::unique_ptr<DrawCommand>& ptr ) {
		return ptr.get( ) == draw_command;
	} );

	if ( it == Graphics.DrawCommands.end( ) )
		return false;

	Graphics.DrawCommands.erase( it );
	return true;
}

CRenderer Renderer;