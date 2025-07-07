---
icon: browser
---

# Win32

## win32.create\_window

<pre class="language-lua"><code class="lang-lua"><strong>win32.create_window(size: vector2, fullscreen: boolean) -> integer
</strong></code></pre>

Returns an integer that serves as our 'window\_reference' to other functions.

## win32.destroy\_window

<pre class="language-lua"><code class="lang-lua"><strong>win32.destroy_window(window_reference: integer) -> nil
</strong></code></pre>

## win32.create\_console

```lua
win32.create_console(position: vector2, size: vector2, fullscreen: boolean) -> integer
```

## win32.destroy\_console

<pre class="language-lua"><code class="lang-lua"><strong>win32.destroy_console(console_reference: integer) -> nil
</strong></code></pre>

## win32.message\_box

```lua
win32.message_box(window_reference: integer) -> nil
```

## win32.get\_screen\_size

```lua
win32.get_screen_size() -> vector2
```

