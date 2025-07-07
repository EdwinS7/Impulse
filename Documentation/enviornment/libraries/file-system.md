---
icon: folder-closed
---

# File system

## file\_system.list\_files

<pre class="language-lua"><code class="lang-lua"><strong>file_system.list_files(directory: string) -> table
</strong></code></pre>

## file\_system.file\_exists

```lua
file_system.file_exists(directory: string) -> boolean
```

## file\_system.read\_file

```lua
file_system.read_file(directory: string) -> string
```

## file\_system.write\_file

```lua
file_system.write_file(directory: string, content: string) -> nil
```

## file\_system.rename\_file

```lua
file_system.rename_file(directory: string, new_directory: string) -> nil
```

## file\_system.delete\_file

```lua
file_system.delete_file(directory: string) -> nil
```

## file\_system.list\_directories

```lua
file_system.list_directories(directory: string) -> table
```

## file\_system.directory\_exists

```lua
file_system.directory_exists(directory: string) -> boolean
```

## file\_system.rename\_directory

```lua
file_system.rename_directory(directory: string, new_directory: string) -> boolean
```

## file\_system.create\_directory

```lua
file_system.create_directory(directory: string) -> nil
```

## file\_system.delete\_directory

```lua
file_system.delete_directory(directory: string) -> nil
```

## file\_system.load\_image\_data

```lua
file_system.load_image_data(directory: string) -> pixel_data: userdata, width: number, height: number
```
