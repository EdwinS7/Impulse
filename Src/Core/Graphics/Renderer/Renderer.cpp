#include "Renderer.hpp"

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
        return a->z_index < b->z_index;
    } );

    return CommandPointer;
}

CRenderer Renderer;