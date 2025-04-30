local screen_size: vector2 = win32.get_screen_size()

do  
    local console_size: vector2 = vector2.new(screen_size.x / 1.5, screen_size.y / 1.5)

    local console_reference: integer = win32.create_console("Impulse - console", 
        vector2.new((screen_size.x / 2) - (console_size.x / 2), (screen_size.y / 2) - ((console_size.x / 2) / 2)), -- position
        console_size
    )
    
    -- TODO: Add first argument to print for 'console_reference'
    print("[Impulse] Hello World!")
end

do -- Graphics / Renderer usage example
    local window_size: vector2 = vector2.new(screen_size.x / 1.5, screen_size.y / 1.5)

    local window_reference: integer = win32.create_window("Impulse - demo", 
        vector2.new((screen_size.x / 2) - (window_size.x / 2), (screen_size.y / 2) - ((window_size.x / 2) / 2)), 
        window_size,
        false
    )

    local swap_chain_description: table = {
        output_window = window_reference,
        windowed = true,

        buffer_format = DXGI_FORMAT.R8G8B8A8_UNORM,
        buffer_usage = DXGI_USAGE.RENDER_TARGET_OUTPUT,
        
        sample_count = 1,
        buffer_count = 1,

        buffer_width = window_size.x,
        buffer_height = window_size.y,

        swap_effect = DXGI_SWAP_EFFECT.DISCARD
    }

    local float_size: integer = 4 -- sizeof(float)

    local buffer_description: table = {
        byte_width = 4 * 4 * float_size,
        usage = D3D11_USAGE.DYNAMIC,
        bind_flags = D3D11_BIND_FLAG.CONSTANT_BUFFER,
        cpu_access_flags = D3D11_CPU_ACCESS_FLAG.WRITE,
        misc_flags = 0
    }

    local rasterizer_description: table = {
        fill_mode = D3D11_FILL_MODE.SOLID,
        cull_mode = D3D11_CULL_MODE.NONE,

        scissor_enable = false,
        depth_clip_enable = true
    }

    local depth_stencil_description: table = {
        depth_enable = false,
        depth_write_mask = D3D11_DEPTH_WRITE_MASK.ALL, 
        depth_func = D3D11_COMPARISON_FUNC.ALWAYS,

        stencil_enable = false,
        
        front_face = {
            stencil_fail_op = D3D11_STENCIL_OP.KEEP,
            stencil_depth_fail_op = D3D11_STENCIL_OP.KEEP,
            stencil_pass_op = D3D11_STENCIL_OP.KEEP,
            stencil_func = D3D11_COMPARISON_FUNC.ALWAYS
        }
    }

    local blend_description: table = {
        alpha_to_coverage_enable = false,

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

    local vertex_shader_source: string = file_system.read_file("Shaders/vertex_shader.hlsl")
    local pixel_shader_source: string = file_system.read_file("Shaders/pixel_shader.hlsl")

    if not graphics.initiate(window_reference, swap_chain_description, buffer_description, rasterizer_description, depth_stencil_description, blend_description, vertex_shader_source, pixel_shader_source) then
        error("Failed to initiate graphics?")
    end

    local shape: table = renderer.rectangle(
        vector2.new(10, 10),
        vector2.new(100, 100),
        color.new(255, 255, 255, 255),
        true, 0
    )

    dragging.add_object(shape)
end