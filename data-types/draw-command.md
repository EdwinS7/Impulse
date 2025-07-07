# Draw command

## Constructor

```lua
draw_command.new(primitive_topology: integer, vertices: table, indices: table) -> draw_command
```

<table><thead><tr><th width="195" align="center">Properties</th><th>Description</th></tr></thead><tbody><tr><td align="center">primitive_topology</td><td>Defines the shape and structure of the primitives being drawn (e.g., points, lines, triangles).</td></tr><tr><td align="center">vertices</td><td>The collection of <a href="vertex.md">Vertexes</a> that define the shape or geometry of the primitive.</td></tr><tr><td align="center">indices</td><td>Defines the order in which vertices are connected to form the primitive.</td></tr><tr><td align="center">z_index</td><td>Represents the depth or layering of the object, determining its visibility relative to other objects in space.</td></tr></tbody></table>

