---
description: Simple centered console that says 'Hello World!'
icon: rectangle-terminal
---

# Console

{% code title="Console.lua" lineNumbers="true" %}
```lua
local screen_size: vector2 = win32.get_screen_size( )

local console_ref: number = win32.create_console("console", 
    (screen_size.x / 2) - ((screen_size.x / 1.5) / 2), -- x
    (screen_size.y / 2) - ((screen_size.y / 1.5) / 2), -- y
    screen_size.x / 1.5, -- width
    screen_size.y / 1.5, -- height
)

print("Hello World!")
```
{% endcode %}
