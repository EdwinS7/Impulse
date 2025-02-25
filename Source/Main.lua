local screen_size: vector2 = win32.get_screen_size( )

local console_ref: number = win32.create_console("console", 
    (screen_size.x / 2) - ((screen_size.x / 1.5) / 2), 
    (screen_size.y / 2) - ((screen_size.y / 1.5) / 2),
    screen_size.x / 1.5, screen_size.y / 1.5
)

local window_ref: number = win32.create_window("window", 
    1280, 720, false
)

do
    directx.initiate(window_ref, true)

    local rectangle = renderer.rectangle(vector2.new(100, 100), vector2.new(100, 100), color.new(255, 255, 255, 255), true)
    
    dragging.add_frame(rectangle)
end

add_connection("shutdown", function()
    print("Goodbye World!")
end)