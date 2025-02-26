---
description: Simple centered window with a basic direct x implementation.
icon: browser
---

# Window

```lua
local window_ref: number = win32.create_window("window", 
    1280, -- width
    720, -- height
    false, -- fullscreen
)

direct_x.initiate( 
    window_ref, 
    true, -- v_sync
)

local rectangle = renderer.rectangle(
    vector2.new(100, 100), -- position
    vector2.new(100, 100), -- size
    color.new(255, 255, 255, 255),
    true, -- filled
)
```
