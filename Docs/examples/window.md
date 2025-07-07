---
description: Simple centered window with a basic direct x implementation.
icon: browser
---

# Window

<pre class="language-lua" data-title="Window.lua" data-line-numbers><code class="lang-lua">local screen_size = win32.get_screen_size( )

<strong>local window_size = screen_size / 1.5
</strong>local window_pos = vector2.new(
<strong>    (screen_size.x - window_size.x) / 2,
</strong>    (screen_size.y - window_size.x / 2) / 2
)
local client_size

window_reference, client_size = win32.create_window(
    "Impulse Engine", 
    window_pos, 
    window_size,
    false
)

local swap_chain_desc = {
    output_window = window_reference,
    windowed = true,

    buffer_format = DXGI_FORMAT.B8G8R8A8_UNORM,
    buffer_usage = DXGI_USAGE.RENDER_TARGET_OUTPUT,
    
    sample_count = 1,
    buffer_count = 2,

    buffer_width = client_size.x,
    buffer_height = client_size.y,

    swap_effect = DXGI_SWAP_EFFECT.DISCARD
}
local float_size = 4
local buffer_desc = {
    byte_width = 4 * 4 * float_size,
    usage = D3D11_USAGE.DYNAMIC,
    bind_flags = D3D11_BIND_FLAG.CONSTANT_BUFFER,
    cpu_access_flags = D3D11_CPU_ACCESS_FLAG.WRITE,
    misc_flags = 0
}
local rasterizer_desc = {
    fill_mode = D3D11_FILL_MODE.SOLID,
    cull_mode = D3D11_CULL_MODE.BACK,

    scissor_enable = false, -- TODO: Add clipping.
    depth_clip_enable = true
}
local depth_stencil_desc = {
    depth_enable = true,

    depth_write_mask = D3D11_DEPTH_WRITE_MASK.ZERO, 
    depth_func = D3D11_COMPARISON_FUNC.ALWAYS,

    stencil_enable = false,
    
    front_face = {
        stencil_fail_op = D3D11_STENCIL_OP.KEEP,
        stencil_depth_fail_op = D3D11_STENCIL_OP.KEEP,
        stencil_pass_op = D3D11_STENCIL_OP.KEEP,
        stencil_func = D3D11_COMPARISON_FUNC.ALWAYS
    }
}
local sampler_desc = {
    filter = D3D11_FILTER.MIN_MAG_MIP_LINEAR,
    address_u = D3D11_TEXTURE_ADDRESS_MODE.CLAMP,
    address_v = D3D11_TEXTURE_ADDRESS_MODE.CLAMP,
    address_w = D3D11_TEXTURE_ADDRESS_MODE.CLAMP,
    mip_lod_bias = 0.0,
    comparison_func = D3D11_COMPARISON_FUNC.ALWAYS,
    min_lod = 0.0,
    max_lod = 0.0
}
local blend_desc = {
    alpha_to_coverage_enable = false,
    independent_blend_enable = false,

    render_target = {
        blend_enable = true,
        
        src_blend = D3D11_BLEND.SRC_ALPHA,
        dest_blend = D3D11_BLEND.INV_SRC_ALPHA,
        blend_op = D3D11_BLEND_OP.ADD,
        src_blend_alpha = D3D11_BLEND.ONE,
        dest_blend_alpha = D3D11_BLEND.INV_SRC_ALPHA,
        blend_op_alpha = D3D11_BLEND_OP.ADD,
        render_target_write_mask = D3D11_COLOR_WRITE_ENABLE.ALL
    }
}
local vertex_shader_src = file_system.read_file("Game/Shaders/vertex_shader.hlsl")
local pixel_shader_src = file_system.read_file("Game/Shaders/pixel_shader.hlsl")

-- This will throw an error if it fails.
graphics.initiate(
    swap_chain_desc, buffer_desc, rasterizer_desc,
    depth_stencil_desc, sampler_desc, blend_desc,
    vertex_shader_src, pixel_shader_src, false -- vsync
)

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
</code></pre>
