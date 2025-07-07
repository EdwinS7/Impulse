---
icon: crown
---

# Impulse globals

## print

```lua
print(console_reference: number, content: string) -> nil
```

## warn

```lua
warn(console_reference: number, content: string) -> nil
```

## error

```lua
error(console_reference: number, content: string) -> nil
```

## add\_connection

```lua
add_connection(connection_name: string, callback: function) -> integer
```

<table><thead><tr><th width="169">Connection name</th><th>Description</th></tr></thead><tbody><tr><td>new_frame</td><td>Triggered at the start of each frame, allowing functions to execute per-frame updates such as rendering or game logic.</td></tr><tr><td>cursor_move</td><td>Invoked when the cursor moves, passing the new cursor position as a <a href="../../data-types/vector2.md">vector2 </a>to the callback for handling input tracking or UI interactions.</td></tr><tr><td>shutdown</td><td>Invoked when the cursor moves, providing updated position coordinates to handle input tracking or UI interactions.</td></tr></tbody></table>

## remove\_connection

```lua
remove_connection(connection_reference: integer) -> nil
```

## load\_string

```lua
load_string(source_code: string) -> function
```

## new\_c\_closure

```lua
new_c_closure(func: function) -> function
```

## is\_l\_closure&#x20;

```lua
is_l_closure(func: function) -> boolean
```

## is\_c\_closure

```lua
is_c_closure(func: function) -> boolean
```

## get\_wrapped\_original

```lua
get_wrapped_original(func: function) -> function
```

## set\_read\_only

```lua
set_read_only(tbl: table) -> nil
```

## get\_read\_only

```lua
get_read_only(tbl: table) -> boolean
```

## random\_string

<pre class="language-lua"><code class="lang-lua"><strong>random_string(length: integer) -> string
</strong></code></pre>

## set\_clipboard

```lua
set_clipboard(data: string) -> nil
```

## get\_clipboard

```lua
get_clipboard() -> string
```

## has\_internet

```lua
has_internet() -> boolean
```
