# Vertex

## Constructor

```lua
vertex.new(x: number, y: number, z: number, rhw: number, u: number, v: number, color: color) -> vertex
```

<table><thead><tr><th width="124" align="center">Properties</th><th>Description</th></tr></thead><tbody><tr><td align="center">x</td><td>Defines the horizontal position of a point in 3D space, determining left or right movement.</td></tr><tr><td align="center">y</td><td>Defines the vertical position of a point in 3D space, determining up or down movement..</td></tr><tr><td align="center">z</td><td>Defines depth in 3D space, determining forward or backward movement.</td></tr><tr><td align="center">rhw</td><td>Represents the reciprocal of the homogeneous W component, used for depth correction and perspective transformation.</td></tr><tr><td align="center">u</td><td>Defines the horizontal texture coordinate, mapping the texture’s position across the surface.</td></tr><tr><td align="center">v</td><td>Defines the vertical texture coordinate, mapping the texture’s position along the surface.</td></tr><tr><td align="center">color</td><td>Defines the vertex's color, often used for shading and lighting effects.</td></tr></tbody></table>

