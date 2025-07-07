---
icon: paintbrush
---

# Graphics

## graphics.initiate

```lua
graphics.initiate(window_reference: integer, v_sync: boolean) -> nil
```

## graphics.cleanup

```lua
graphics.cleanup() -> nil
```

## graphics.set\_projection\_matrix

```lua
graphics.set_projection_matrix(projection_matrix: table) -> nil
```

<details>

<summary>Example usage</summary>

{% code title="SetProjectionMatrix.lua" lineNumbers="true" %}
```lua
local screen_size = win32.get_screen_size( )

local fov = math.rad(60)
local aspect = screen_size.x / screen_size.y
local near, far = 0.1, 100.0
local f = 1.0 / math.tan(fov / 2)

graphics.set_projection_matrix({
    f / aspect, 0,  0,                              0,
    0,          f,  0,                              0,
    0,          0,  far / (far - near),             1,
    0,          0,  (-near * far) / (far - near),   0
})
```
{% endcode %}

</details>

## graphics.set\_viewport

```lua
graphics.set_viewport(position: vector2, size: vector2, min_depth: number, max_depth: number) -> nil
```

## graphics.create\_texture

```lua
graphics.create_texture(texture_name: string, texture_description: table, sub_resource_data: table, shader_resource_view_desc: table) -> nil
```

## graphics.destroy\_texture

```lua
graphics.destroy_texture(texture: texture) -> nil
```

## graphics.create\_font

```lua
graphics.create_font(font_path: string, size: number, padding: number: antialiasing: boolean) -> font
```

{% hint style="info" %}
This returns a [font](../../data-types/font.md) object.
{% endhint %}

## graphics.destroy\_font

```lua
graphics.destroy_font(font: font) -> nil
```
