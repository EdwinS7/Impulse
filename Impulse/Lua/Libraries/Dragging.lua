dragging = {
    objects = {},

    active_object = {
        is_dragging = false,
        click_started_inside = false,
        offset = vector2.new(0, 0)
    },

    was_mouse_down = false
}
dragging.__index = dragging

local function is_point_hovering(position, object)
    if object.size then
        return position.x >= object.position.x 
            and position.y >= object.position.y 
            and position.x <= object.position.x + object.size.x 
            and position.y <= object.position.y + object.size.y
    elseif object.radius then
        local dx = position.x - object.position.x
        local dy = position.y - object.position.y
        local distance_squared = dx * dx + dy * dy
        
        return distance_squared <= (object.radius * object.radius)
    end
    
    return false
end

dragging.add_object = function(object)
    table.insert(dragging.objects, object)
    return #dragging.objects
end

add_connection("cursor_move", function(position)
    local is_mouse_down = input.is_key_held(KEY_CODES.MOUSE1)
    
    if is_mouse_down and not dragging.was_mouse_down then
        dragging.active_object.is_dragging = false
        dragging.active_object.click_started_inside = false
        
        for index, object in ipairs(dragging.objects) do
            if is_point_hovering(position, object) then
                dragging.active_object.is_dragging = true
                dragging.active_object.click_started_inside = true
                dragging.active_object.offset = vector2.new(
                    object.position.x - position.x,
                    object.position.y - position.y
                )
                
                table.remove(dragging.objects, index)
                table.insert(dragging.objects, 1, object)
                break
            end
        end
    elseif not is_mouse_down and dragging.was_mouse_down then
        dragging.active_object.is_dragging = false
        dragging.active_object.click_started_inside = false
    elseif is_mouse_down then
        if dragging.active_object.is_dragging and 
           dragging.active_object.click_started_inside then
            
            local object = dragging.objects[1]
            if object then
                object.position = vector2.new(
                    position.x + dragging.active_object.offset.x,
                    position.y + dragging.active_object.offset.y
                )
            end
        end
    end
    
    dragging.was_mouse_down = is_mouse_down
end)