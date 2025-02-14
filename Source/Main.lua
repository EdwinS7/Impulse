-- NOTE: Indentation is only broken on GitHub.
local screen_size = win32.get_screen_size( )
local width, height = screen_size.x / 1.5, screen_size.y / 1.5

local console_ref = win32.create_console("Test", 
	(screen_size.x / 2) - (width / 2), 
	(screen_size.y / 2) - (height / 2),
	width, height
)

print("Hello World!")

do -- win32 / rendering
    local window_ref = win32.create_window("Test", 
	    1280, 720, false
    )

    directx.initiate(window_ref)

    local shape = renderer.write_to_buffer(D3D_PRIMITIVE_TOPOLOGY.TRIANGLE_LIST,
        { -- Vertices
            vertex(50, 50, 0, 1, 0, 0, color(255, 0, 0, 255).hex),
            vertex(100, 50, 0, 1, 0, 0, color(0, 255, 0, 255).hex),
            vertex(75, 100, 0, 1, 0, 0, color(0, 0, 255, 255).hex)
        }, 
        { -- Indices
            0, 1, 2
        }
    )

    --[[ NOTE: This works just too lazy to make something.
        shape.vertices = {}
        shape.indices = {}
    --]]
end

add_connection("shutdown", function()
    print("Goodbye World!")
end)