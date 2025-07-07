---
icon: shapes
---

# Renderer

{% hint style="warning" %}
A window with an attached graphics library is required for this to function.
{% endhint %}

## renderer.write\_to\_buffer

```lua
renderer.write_to_buffer(primitive_topology: integer, vertices: table, indices: table, texture: texture, z_index: number) -> draw_command
```

* `primitive_topology` (integer) – Specifies the type of primitive to be rendered. It determines how the vertices will be connected (e.g., triangles, lines, etc.).&#x20;
* `vertices` (table) – A table containing [Vertex](../../data-types/vertex.md) objects, each defining a point in 2D or 3D space with position, color, and other attributes.&#x20;
* `indices` (table) – A table of integers representing the order in which vertices should be connected to form the desired shape.
* `texture` ([texture](../../../data-types/texture.md)) - A reference to a texture resource used to sample colors during rendering. This could be a handle or object managed by the graphics system (e.g. a loaded image or material asset).
* `z_index` (number) – Specifies the global z-index for the rendered object. Useful for depth sorting in 2D/3D rendering.

Returns a [draw\_command](../../data-types/draw-command.md), which can be used to change the `primitive_topology`, `vertices`, and `indices` later on.

<details>

<summary>Example usage</summary>

{% code title="WriteToBuffer.lua" lineNumbers="true" %}
```lua
local window_ref: number = win32.create_window("window", 
    1280, -- width
    720, -- height
    false -- fullscreen
)

direct_x.initiate( 
    window_ref, 
    true -- v_sync
)

local position: vector2 = vector2.new(10, 10)
local size: vector2 = vector2.new(100, 100)
local clr: color = color.new(255, 255, 255, 255)

local command: draw_command = renderer.write_to_buffer(
    D3D_PRIMITIVE_TOPOLOGY.LINE_STRIP,
    
    { -- vertices
        vertex.new(
            position.x, -- x
            position.y, -- y
            0,          -- z
            1,          -- rhw
            0,          -- u
            0,          -- v
            clr.hex     -- color
        ),
        
        vertex.new(
            position.x + size.x, -- x
            position.y,          -- y
            0,                   -- z
            1,                   -- rhw
            0,                   -- u
            0,                   -- v
            clr.hex              -- color
        ),
        
        vertex.new(
            position.x + size.x, -- x
            position.y + size.y, -- y
            0,                   -- z
            1,                   -- rhw
            0,                   -- u
            0,                   -- v
            clr.hex              -- color
        ),
        
        vertex.new(
            position.x,          -- x
            position.y + size.y, -- y
            0,                   -- z
            1,                   -- rhw
            0,                   -- u
            0,                   -- v
            clr.hex              -- color
        )
    },
    
    { -- indices
        0, 1, 2, 3, 0
    },

    1 -- z_index
)
```
{% endcode %}

</details>
