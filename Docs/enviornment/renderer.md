---
icon: image
---

# renderer

{% hint style="warning" %}
A window with an attached graphics library is required for this to function.
{% endhint %}

## renderer.write\_to\_buffer

```lua
renderer.write_to_buffer(primitive_topology: integer, vertices: table, indices: table) -> draw_command
```

* `primitive_topology` (integer) – Specifies the type of primitive to be rendered. It determines how the vertices will be connected (e.g., triangles, lines, etc.).&#x20;
* `vertices` (table) – A table containing Vertex objects, each defining a point in 2D or 3D space with position, color, and other attributes.&#x20;
* `indices` (table) – A table of integers representing the order in which vertices should be connected to form the desired shape.

Returns a `draw_command`, which can be used to change the primitive\_topology, vertices, and indices later on.
