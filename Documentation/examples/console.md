---
description: Simple centered console that says 'Hello World!'
icon: rectangle-terminal
---

# Console

{% code title="Console.lua" lineNumbers="true" %}
```lua
local console_reference = win32.create_console(
    "Impulse logs",
    vector2.new(50, 50),
    vector2.new(1280, 720)
)

print(console_reference, "Hello World!")
```
{% endcode %}
