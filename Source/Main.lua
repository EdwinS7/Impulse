local width, height = 1280, 720
local console_ref = win32.create_console("Test", (1920 / 2) - (width / 2), (1080 / 2) - (height / 2), width, height)

for _, v in _G do
	print(_)
end