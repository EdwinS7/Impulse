---
icon: screwdriver-wrench
---

# Debug

## debug.getregistry

```lua
debug.getregistry() -> table
```

Returns the lua registry.

## debug.getupvalues

```lua
debug.getupvalues(func: function | number) -> table
```

Returns a list of upvalues in the given `func`.

{% hint style="info" %}
An upvalue is a local variable used by an inner function, and is also called an _external local variable_.
{% endhint %}

## debug.getupvalue

```lua
debug.getupvalue(func: function | number, index: number) -> any
```

Returns the upvalue at `index` in the given `func`.

## debug.setupvalue

```lua
debug.setupvalue(func: function | number, index: number, value: any) -> nil
```

Sets the upvalue at the specified `index` in the given `func` or stack level to the provided `value`.
