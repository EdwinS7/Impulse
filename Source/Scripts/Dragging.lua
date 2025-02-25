dragging = {
	frames = {},

	active_frame = {
		dragging = false,
		started_out_of_bounds = false,
		difference = vector2.new(0, 0)
	}
} dragging.__index = dragging;

dragging.add_frame = function(frame)
	table.insert(dragging.frames, frame)

	return #dragging.frames
end

local function is_point_hovering_frame(position, frame)
    return position.x >= frame.position.x 
        and position.y >= frame.position.y 
        and position.x <= frame.position.x + frame.size.x 
        and position.y <= frame.position.y + frame.size.y
end

add_connection("cursor_move", function(position)
	if not input.is_key_held(KEY_CODES.MOUSE1) then
		dragging.active_frame.dragging = false

		return
	end

	for index, frame in dragging.frames do
		if not dragging.active_frame.dragging then
			if not is_point_hovering_frame(position, frame) then
				continue
			end

			dragging.active_frame.dragging = true

			dragging.active_frame.difference = vector2.new(
				frame.position.x - position.x,
				frame.position.y - position.y
			)

			table.remove(dragging.frames, index)
			table.insert(dragging.frames, 1, frame)
		end

		frame.position = vector2.new(
			position.x + dragging.active_frame.difference.x,
			position.y + dragging.active_frame.difference.y
		)

		break
	end
end)