-- NOTE: 'renderer' already exists, its defined upon startup.
-- NOTE: This is just a temporary lua implementation since the C version is not done.

local generate_arc_points = function(position, segments, radius, completion, angle, color, filled)
    local start_angle = math.rad(angle)
    local arc_portion = completion * 0.01
    local theta_step = 2 * math.pi * arc_portion / segments

    local vertices, indices = {}, {}

    if filled then
        table.insert(vertices, vertex.new(position.x, position.y, 0, 1, 0, 0, color.hex))
        table.insert(indices, 0)
    end

    for i = 0, segments do
        local theta = start_angle + i * theta_step;

        table.insert(vertices, vertex.new(
            position.x + radius * math.cos(theta),
            position.y + radius * math.sin(theta),
            0, 1, 0, 0, color.hex
        ))

        table.insert(indices, i)
        
        if filled then
            table.insert(indices, i + 1)
            table.insert(indices, 0)
        end
    end

    return vertices, indices
end

renderer.circle = function(position, segments, radius, completion, angle, color, filled, z_index)
    local private = {
        position = position,
        segments = segments,
        radius = radius,
        completion = completion,
        angle = angle,
        color = color,
        filled = filled
    }

    local vertices, indices = generate_arc_points(
        position, segments, radius, completion, angle, color, filled
    )

    private.draw_command = renderer.write_to_buffer(
        filled and D3D_PRIMITIVE_TOPOLOGY.TRIANGLE_STRIP or D3D_PRIMITIVE_TOPOLOGY.LINE_STRIP,
        vertices, indices, z_index
    )

    return setmetatable({}, {
        __index = function(self, key)
            return private[key]
        end,

        __newindex = function(self, key, value)
            if key == "draw_command" then
                assert(typeof(value) == "userdata", "draw_command must be a draw_command object")

                private.draw_command = value
            elseif key == "position" then
                assert(typeof(value) == "userdata", "position must be a vector2 object")

                private.position = value

                private.draw_command.vertices, private.draw_command.indices = generate_arc_points(
                    private.position, private.segments, private.radius, private.completion, private.angle, private.color, private.filled
                )
            elseif key == "size" then
                assert(typeof(value) == "userdata", "size must be a vector2 object")

                private.size = value

                private.draw_command.vertices, private.draw_command.indices = generate_arc_points(
                    private.position, private.segments, private.radius, private.completion, private.angle, private.color, private.filled
                )
            elseif key == "color" then
                assert(typeof(value) == "userdata", "color must be a color object")

                private.color = value
                
                private.draw_command.vertices, private.draw_command.indices = generate_arc_points(
                    private.position, private.segments, private.radius, private.completion, private.angle, private.color, private.filled
                )
            elseif key == "filled" then
                assert(typeof(value) == "boolean", "filled must be a boolean")

                if value then
                    private.draw_command.primitive_topology = D3D_PRIMITIVE_TOPOLOGY.TRIANGLE_STRIP
                else
                    private.draw_command.primitive_topology = D3D_PRIMITIVE_TOPOLOGY.LINE_STRIP
                end

                private.filled = value

                private.draw_command.vertices, private.draw_command.indices = generate_arc_points(
                    private.position, private.segments, private.radius, private.completion, private.angle, private.color, private.filled
                )
            else
                private[key] = value
            end
        end
    })
end

renderer.rectangle = function(position, size, color, filled, z_index)
    local private = {
        position = position,
        size = size,
        color = color,
        filled = filled
    }

    local create_vertices = function()
        return {
            vertex.new(private.position.x, private.position.y, 0, 1, 0, 0, private.color.hex),
            vertex.new(private.position.x + private.size.x, private.position.y, 0, 1, 0, 0, private.color.hex),
            vertex.new(private.position.x + private.size.x, private.position.y + private.size.y, 0, 1, 0, 0, private.color.hex),
            vertex.new(private.position.x, private.position.y + private.size.y, 0, 1, 0, 0, private.color.hex)
        }
    end

    private.draw_command = renderer.write_to_buffer(
        filled and D3D_PRIMITIVE_TOPOLOGY.TRIANGLE_STRIP or D3D_PRIMITIVE_TOPOLOGY.LINE_STRIP, 
        create_vertices(), {0, 1, 2, 3, 0}, z_index
    )
    
    return setmetatable({}, {
        __index = function(self, key)
            return private[key]
        end,

        __newindex = function(self, key, value)
            if key == "draw_command" then
                private.draw_command = value
            elseif key == "position" then
                assert(typeof(value) == "userdata", "position must be a vector2 object")

                private.position = value
                private.draw_command.vertices = create_vertices()
            elseif key == "size" then
                assert(typeof(value) == "userdata", "size must be a vector2 object")

                private.size = value
                private.draw_command.vertices = create_vertices()
            elseif key == "color" then
                assert(typeof(value) == "userdata", "color must be a color object")

                private.color = value
                private.draw_command.vertices = create_vertices()
            elseif key == "filled" then
                assert(typeof(value) == "boolean", "filled must be a boolean")

                private.filled = value

                if value then
                    private.draw_command.primitive_topology = D3D_PRIMITIVE_TOPOLOGY.TRIANGLE_STRIP
                else
                    private.draw_command.primitive_topology = D3D_PRIMITIVE_TOPOLOGY.LINE_STRIP
                end
            else
                private[key] = value
            end
        end
    })
end