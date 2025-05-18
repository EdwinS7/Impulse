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

renderer.circle = function(position, segments, radius, completion, angle, color, filled, texture, z_index)
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
        filled and D3D11_PRIMITIVE_TOPOLOGY.TRIANGLE_STRIP or D3D11_PRIMITIVE_TOPOLOGY.LINE_STRIP,
        vertices, 
        indices, 
        texture, 
        z_index
    )

    private.destroy = function(self)
        self.draw_command:destroy()
    end

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
                    private.position, 
                    private.segments, 
                    private.radius, 
                    private.completion, 
                    private.angle, 
                    private.color, 
                    private.filled
                )
            elseif key == "size" then
                assert(typeof(value) == "userdata", "size must be a vector2 object")

                private.size = value

                private.draw_command.vertices, private.draw_command.indices = generate_arc_points(
                    private.position, 
                    private.segments, 
                    private.radius, 
                    private.completion, 
                    private.angle, 
                    private.color, 
                    private.filled
                )
            elseif key == "color" then
                assert(typeof(value) == "userdata", "color must be a color object")

                private.color = value
                
                private.draw_command.vertices, private.draw_command.indices = generate_arc_points(
                    private.position, 
                    private.segments, 
                    private.radius, 
                    private.completion, 
                    private.angle, 
                    private.color, 
                    private.filled
                )
            elseif key == "filled" then
                assert(typeof(value) == "boolean", "filled must be a boolean")

                if value then
                    private.draw_command.primitive_topology = D3D11_PRIMITIVE_TOPOLOGY.TRIANGLE_STRIP
                else
                    private.draw_command.primitive_topology = D3D11_PRIMITIVE_TOPOLOGY.LINE_STRIP
                end

                private.filled = value

                private.draw_command.vertices, private.draw_command.indices = generate_arc_points(
                    private.position, 
                    private.segments, 
                    private.radius, 
                    private.completion, 
                    private.angle, 
                    private.color, 
                    private.filled
                )
            end
        end
    })
end

renderer.rectangle = function(position, size, color, filled, texture, z_index)
    local private = {
        position = position,
        size = size,
        color = color,
        filled = filled,
        texture = texture,
        z_index = z_index
    }

    local get_vertices = function()
        return {
            vertex.new(private.position.x, private.position.y, 0, 1, 0, 0, private.color.hex),
            vertex.new(private.position.x + private.size.x, private.position.y, 0, 1, 1, 0, private.color.hex),
            vertex.new(private.position.x + private.size.x, private.position.y + private.size.y, 0, 1, 1, 1, private.color.hex),
            vertex.new(private.position.x, private.position.y + private.size.y, 0, 1, 0, 1, private.color.hex)
        }
    end

    private.draw_command = renderer.write_to_buffer(
        filled and D3D11_PRIMITIVE_TOPOLOGY.TRIANGLE_STRIP or D3D11_PRIMITIVE_TOPOLOGY.LINE_STRIP, 
        get_vertices(), 
        {0, 1, 2, 3, 0}, 
        texture, 
        z_index
    )

    private.destroy = function(self)
        self.draw_command:destroy()
    end
    
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
                private.draw_command.vertices = get_vertices()
            elseif key == "size" then
                assert(typeof(value) == "userdata", "size must be a vector2 object")

                private.size = value
                private.draw_command.vertices = get_vertices()
            elseif key == "color" then
                assert(typeof(value) == "userdata", "color must be a color object")

                private.color = value
                private.draw_command.vertices = get_vertices()
            elseif key == "filled" then
                assert(typeof(value) == "boolean", "filled must be a boolean")

                private.filled = value

                private.draw_command.primitive_topology = value 
                    and D3D11_PRIMITIVE_TOPOLOGY.TRIANGLE_STRIP 
                    or D3D11_PRIMITIVE_TOPOLOGY.LINE_STRIP
            end
        end
    })
end

renderer.text = function(font, string, position, color, z_index)
    local private = {
        font = font,
        string = string,
        position = position,
        color = color,
        z_index = z_index,

        draw_commands = {}
    }

    private.destroy = function(self)
        for i, draw_command in ipairs(self.draw_commands) do
            draw_command:destroy()
        end
    end

    local get_max_offset_y = function()
        local max_offset_y = 0

        for i = 1, #string do
            local char = string:sub(i, i)
            local glyph = font.glyphs[char]
        
            if glyph then
                max_offset_y = math.max(max_offset_y, glyph.offset_y)
            end
        end

        return max_offset_y
    end

    local create_draw_commands = function()
        local max_offset_y = get_max_offset_y()

        local advance_x, advance_y = 0, 0
        local glyph_x, glyph_y = 0, 0

        for i = 1, #private.string do
            local char = private.string:sub(i, i)
            local glyph = private.font.glyphs[char]

            if not glyph then 
                continue 
            end

            local glyph_x = math.floor(private.position.x + advance_x + glyph.offset_x)
            local glyph_y = math.floor(private.position.y + max_offset_y - glyph.offset_y)

            local vertices = {
                vertex.new(glyph_x, glyph_y, 0, 1, 0, 0, private.color.hex),
                vertex.new(glyph_x + glyph.width, glyph_y, 0, 1, 1, 0, private.color.hex),
                vertex.new(glyph_x + glyph.width, glyph_y + glyph.height, 0, 1, 1, 1, private.color.hex),
                vertex.new(glyph_x, glyph_y + glyph.height, 0, 1, 0, 1, private.color.hex)
            }

            private.draw_commands[i] = renderer.write_to_buffer(
                D3D11_PRIMITIVE_TOPOLOGY.TRIANGLE_STRIP,
                vertices,
                {0, 1, 2, 3, 0},
                glyph.texture,
                z_index
            )

            advance_x = advance_x + (glyph.advance_x ~= 0 and glyph.advance_x or glyph.width)
        end
    end

    local reposition_draw_commands = function()
        local max_offset_y = get_max_offset_y()

        local advance_x, advance_y = 0, 0
        local glyph_x, glyph_y = 0, 0

        for i = 1, #private.string do
            local char = private.string:sub(i, i)
            local glyph = private.font.glyphs[char]

            if not glyph then 
                continue 
            end

            local glyph_x = math.floor(private.position.x + advance_x + glyph.offset_x)
            local glyph_y = math.floor(private.position.y + max_offset_y - glyph.offset_y)

            private.draw_commands[i].vertices = {
                vertex.new(glyph_x, glyph_y, 0, 1, 0, 0, private.color.hex),
                vertex.new(glyph_x + glyph.width, glyph_y, 0, 1, 1, 0, private.color.hex),
                vertex.new(glyph_x + glyph.width, glyph_y + glyph.height, 0, 1, 1, 1, private.color.hex),
                vertex.new(glyph_x, glyph_y + glyph.height, 0, 1, 0, 1, private.color.hex)
            }

            advance_x = advance_x + (glyph.advance_x ~= 0 and glyph.advance_x or glyph.width)
        end
    end

    create_draw_commands()

    return setmetatable({}, {
        __index = function(self, key)
            return private[key]
        end,

        __newindex = function(self, key, value)
            if key == "position" then
                assert(typeof(value) == "userdata", "position must be a vector2 object")

                private.position = value
                
                reposition_draw_commands()
            elseif key == "color" then
                assert(typeof(value) == "userdata", "color must be a color object")

                private.color = value
                private.draw_command.vertices = create_vertices()
                private[key] = value
            end
        end
    })
end