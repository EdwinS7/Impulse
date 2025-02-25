---
icon: earth-americas
---

# globals

## add\_connection

```lua
add_connection(connection_name: string, callback: function) -> integer
```

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

## is\_lua\_closure&#x20;

```lua
is_lua_closure(func: function) -> boolean
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

## is\_internet\_connected

```lua
is_internet_connected() -> boolean
```
