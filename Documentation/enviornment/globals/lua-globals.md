---
description: >-
  The following is a list of functions and variables that are native to Lua.
  These functions can be used in a standard installation of Lua 5.1.4, though
  there are some differences in how some work.
icon: code-simple
---

# Lua globals

## assert

```lua
assert(value: boolean, error_message: string) -> nil
```

Throws an error if the provided value is `false` or `nil`, stopping execution and displaying the provided error message.

## error

```lua
error(message: string, level: number) -> nil
```

Immediately halts execution and throws an error with the given message and optional stack level.

## gcinfo

```lua
gcinfo() -> number
```

Returns the current memory usage in kilobytes, providing insight into Lua's garbage collection.

## getmetatable

```lua
getmetatable(t: table) -> table | nil
```

Retrieves the metatable of the given table, or `nil` if no metatable exists.

## ipairs

```lua
ipairs(t: table) -> function, table, number
```

Returns an iterator function for sequentially iterating over an array-like table in order.

## newproxy

```lua
newproxy(add_metatable: boolean) -> userdata
```

Creates a blank userdata object, optionally with a metatable for custom behavior.

## next

```lua
next(t: table, last_key: any) -> any, any
```

Returns the next key-value pair in a table, allowing iteration when used in a loop.

## pairs

```lua
pairs(t: table) -> function, table
```

Returns an iterator function for traversing all key-value pairs in a table, including non-sequential keys.

## pcall

```lua
pcall(func: function, ...: any) -> boolean, any
```

Calls a function safely, returning `true` and the result if successful, or `false` and an error message if an error occurs.

## print ⚠️

```lua
print(...: any) -> nil
```

Outputs the provided values to the console for debugging or display purposes.

{% hint style="warning" %}
`print` is overwritten by Impulse, go [here](impulse-globals.md#print).
{% endhint %}

## rawequal

```lua
rawequal(v1: any, v2: any) -> boolean
```

Compares two values for equality, ignoring metamethods such as `__eq`.

## rawget

```lua
rawget(t: table, index: any) -> any
```

Directly retrieves a value from a table, bypassing any `__index` metamethods.

## rawlen

```lua
rawlen(t: table) -> number
```

Returns the length of a table or string without invoking metamethods.

## rawset

```lua
rawset(t: table, index: any, value: any) -> nil
```

Directly assigns a value to a table, bypassing any `__newindex` metamethods.

## require

```lua
require(module: string | number) -> any
```

Loads and runs a module script, returning its result if it has already been executed.

## select

```lua
select(index: number, ...: any) -> any
```

Returns all arguments after the specified index, or the total argument count if the index is `"#"`.

## setmetatable

```lua
setmetatable(t: table, new_meta: table) -> table
```

Assigns a new metatable to the given table, enabling custom behaviors like operator overloading.

## tonumber

```lua
tonumber(arg: any, base: number) -> number | nil
```

Converts a value to a number, optionally using a specified base, or returns `nil` if conversion fails.

## tostring

```lua
tostring(value: any) -> string
```

Converts a value into a string representation, typically used for debugging or display.

## type

```lua
type(value: any) -> string
```

Returns a string representing the type of the given value, such as `number`, `string`, or `table`.

## unpack

```lua
unpack(list: table, i: number, j: number) -> ...any
```

Returns multiple values from a table, from index `i` to `j`, effectively "unpacking" them.

## xpcall

```lua
xpcall(func: function, err: function, ...: any) -> boolean, any
```

Similar to [pcall](lua-globals.md#pcall), but allows for a custom error handler function to process errors before they are returned.
