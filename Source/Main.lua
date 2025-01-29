-- NOTE: Indentation is only broken on GitHub.
local screen_size = win32.get_screen_size( )

local width, height = screen_size.x / 1.5, screen_size.y / 1.5
local console_ref = win32.create_console("Test", 
	(screen_size.x / 2) - (width / 2), 
	(screen_size.y / 2) - (height / 2),
	width, height
)

for _, v in _G do
	print(_)
end