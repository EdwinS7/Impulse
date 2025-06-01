#pragma once

#include "../../Graphics/Include.hpp"
#include "Win32.hpp"

namespace LuaBind::LuaGraphics {
    int Initiate( lua_State* lua_state ) {
        auto ThrowError = [ lua_state ] ( int arg, const char* message ) -> int {
            luaL_argerror( lua_state, arg, message );
            lua_pushboolean( lua_state, false );
            return 1;
        };

        DXGI_SWAP_CHAIN_DESC SwapChainDescription = {};
        if ( lua_istable( lua_state, 1 ) ) {
            lua_getfield( lua_state, 1, "buffer_format" );
            if ( lua_isnumber( lua_state, -1 ) )
                SwapChainDescription.BufferDesc.Format = static_cast< DXGI_FORMAT >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 1, "buffer_usage" );
            if ( lua_isnumber( lua_state, -1 ) )
                SwapChainDescription.BufferUsage = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 1, "output_window" );
            if ( lua_isnumber( lua_state, -1 ) )
                SwapChainDescription.OutputWindow = LuaWin32::WindowHandles[ lua_tointeger( lua_state, -1 ) ];
            lua_pop( lua_state, 1 );


            lua_getfield( lua_state, 1, "sample_count" );
            if ( lua_isnumber( lua_state, -1 ) )
                SwapChainDescription.SampleDesc.Count = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );


            lua_getfield( lua_state, 1, "windowed" );
            if ( lua_isboolean( lua_state, -1 ) )
                SwapChainDescription.Windowed = lua_toboolean( lua_state, -1 );
            lua_pop( lua_state, 1 );


            lua_getfield( lua_state, 1, "buffer_count" );
            if ( lua_isnumber( lua_state, -1 ) )
                SwapChainDescription.BufferCount = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );


            lua_getfield( lua_state, 1, "buffer_width" );
            if ( lua_isnumber( lua_state, -1 ) )
                SwapChainDescription.BufferDesc.Width = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );


            lua_getfield( lua_state, 1, "buffer_height" );
            if ( lua_isnumber( lua_state, -1 ) )
                SwapChainDescription.BufferDesc.Height = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );


            lua_getfield( lua_state, 1, "swap_effect" );
            if ( lua_isnumber( lua_state, -1 ) )
                SwapChainDescription.SwapEffect = static_cast< DXGI_SWAP_EFFECT >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );
        }
        else
            return ThrowError( 1, " Expected a table for SwapChainDescription" );

        D3D11_BUFFER_DESC BufferDescription = {};
        if ( lua_istable( lua_state, 2 ) ) {
            lua_getfield( lua_state, 2, "byte_width" );
            if ( lua_isnumber( lua_state, -1 ) )
                BufferDescription.ByteWidth = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 2, "usage" );
            if ( lua_isnumber( lua_state, -1 ) )
                BufferDescription.Usage = static_cast< D3D11_USAGE >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 2, "bind_flags" );
            if ( lua_isnumber( lua_state, -1 ) )
                BufferDescription.BindFlags = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 2, "cpu_access_flags" );
            if ( lua_isnumber( lua_state, -1 ) )
                BufferDescription.CPUAccessFlags = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 2, "misc_flags" );
            if ( lua_isnumber( lua_state, -1 ) )
                BufferDescription.MiscFlags = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );
        }
        else
            return ThrowError( 2, "Expected a table for BufferDescription" );

        D3D11_RASTERIZER_DESC RasterizerDescription = {};
        if ( lua_istable( lua_state, 3 ) ) {
            lua_getfield( lua_state, 3, "fill_mode" );
            if ( lua_isnumber( lua_state, -1 ) )
                RasterizerDescription.FillMode = static_cast< D3D11_FILL_MODE >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );


            lua_getfield( lua_state, 3, "cull_mode" );
            if ( lua_isnumber( lua_state, -1 ) )
                RasterizerDescription.CullMode = static_cast< D3D11_CULL_MODE >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 3, "scissor_enable" );
            if ( lua_isboolean( lua_state, -1 ) )
                RasterizerDescription.ScissorEnable = lua_toboolean( lua_state, -1 );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 3, "depth_clip_enable" );
            if ( lua_isboolean( lua_state, -1 ) )
                RasterizerDescription.DepthClipEnable = lua_toboolean( lua_state, -1 );
            lua_pop( lua_state, 1 );
        }
        else
            return ThrowError( 3, "Expected a table for RasterizerDescription" );

        D3D11_DEPTH_STENCIL_DESC DepthStencilDescription = {};
        if ( lua_istable( lua_state, 4 ) ) {
            lua_getfield( lua_state, 4, "depth_enable" );
            if ( lua_isboolean( lua_state, -1 ) )
                DepthStencilDescription.DepthEnable = lua_toboolean( lua_state, -1 );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 4, "depth_write_mask" );
            if ( lua_isnumber( lua_state, -1 ) )
                DepthStencilDescription.DepthWriteMask = static_cast< D3D11_DEPTH_WRITE_MASK >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 4, "depth_func" );
            if ( lua_isnumber( lua_state, -1 ) )
                DepthStencilDescription.DepthFunc = static_cast< D3D11_COMPARISON_FUNC >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 4, "stencil_enable" );
            if ( lua_isboolean( lua_state, -1 ) )
                DepthStencilDescription.StencilEnable = lua_toboolean( lua_state, -1 );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 4, "front_face" );
            if ( lua_istable( lua_state, -1 ) ) {
                lua_getfield( lua_state, -1, "stencil_fail_op" );
                if ( lua_isnumber( lua_state, -1 ) )
                    DepthStencilDescription.FrontFace.StencilFailOp = static_cast< D3D11_STENCIL_OP >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                lua_getfield( lua_state, -1, "stencil_depth_fail_op" );
                if ( lua_isnumber( lua_state, -1 ) )
                    DepthStencilDescription.FrontFace.StencilDepthFailOp = static_cast< D3D11_STENCIL_OP >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                lua_getfield( lua_state, -1, "stencil_pass_op" );
                if ( lua_isnumber( lua_state, -1 ) )
                    DepthStencilDescription.FrontFace.StencilPassOp = static_cast< D3D11_STENCIL_OP >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                lua_getfield( lua_state, -1, "stencil_func" );
                if ( lua_isnumber( lua_state, -1 ) )
                    DepthStencilDescription.FrontFace.StencilFunc = static_cast< D3D11_COMPARISON_FUNC >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );
            }
            lua_pop( lua_state, 1 );

            DepthStencilDescription.BackFace = DepthStencilDescription.FrontFace;
        }
        else
            return ThrowError( 4, "Expected a table for DepthStencilDescription" );

        D3D11_SAMPLER_DESC SamplerDescription = {};
        if ( lua_istable( lua_state, 5 ) ) {
            lua_getfield( lua_state, 5, "filter" );
            if ( lua_isnumber( lua_state, -1 ) )
                SamplerDescription.Filter = static_cast< D3D11_FILTER >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 5, "address_u" );
            if ( lua_isnumber( lua_state, -1 ) )
                SamplerDescription.AddressU = static_cast< D3D11_TEXTURE_ADDRESS_MODE >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 5, "address_v" );
            if ( lua_isnumber( lua_state, -1 ) )
                SamplerDescription.AddressV = static_cast< D3D11_TEXTURE_ADDRESS_MODE >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 5, "address_w" );
            if ( lua_isnumber( lua_state, -1 ) )
                SamplerDescription.AddressW = static_cast< D3D11_TEXTURE_ADDRESS_MODE >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 5, "mip_lod_bias" );
            if ( lua_isnumber( lua_state, -1 ) )
                SamplerDescription.MipLODBias = static_cast< FLOAT >( lua_tonumber( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 5, "max_anisotropy" );
            if ( lua_isnumber( lua_state, -1 ) )
                SamplerDescription.MaxAnisotropy = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 5, "comparison_func" );
            if ( lua_isnumber( lua_state, -1 ) )
                SamplerDescription.ComparisonFunc = static_cast< D3D11_COMPARISON_FUNC >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 5, "border_color" );
            if ( lua_istable( lua_state, -1 ) ) {
                for ( int i = 0; i < 4; ++i ) {
                    lua_rawgeti( lua_state, -1, i + 1 );
                    if ( lua_isnumber( lua_state, -1 ) )
                        SamplerDescription.BorderColor[ i ] = static_cast< FLOAT >( lua_tonumber( lua_state, -1 ) );
                    else
                        SamplerDescription.BorderColor[ i ] = 0.f;
                    lua_pop( lua_state, 1 );
                }
            }
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 5, "min_lod" );
            if ( lua_isnumber( lua_state, -1 ) )
                SamplerDescription.MinLOD = static_cast< FLOAT >( lua_tonumber( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 5, "max_lod" );
            if ( lua_isnumber( lua_state, -1 ) )
                SamplerDescription.MaxLOD = static_cast< FLOAT >( lua_tonumber( lua_state, -1 ) );
            lua_pop( lua_state, 1 );
        }
        else
            return ThrowError( 5, "Expected a table for SamplerDescription" );

        D3D11_BLEND_DESC BlendDescription = {};

        if ( lua_istable( lua_state, 6 ) ) {
            lua_getfield( lua_state, 6, "alpha_to_coverage_enable" );
                if ( lua_isboolean( lua_state, -1 ) )
                    BlendDescription.AlphaToCoverageEnable = lua_toboolean( lua_state, -1 );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 6, "independent_blend_enable" );
                if ( lua_isboolean( lua_state, -1 ) )
                    BlendDescription.IndependentBlendEnable = lua_toboolean( lua_state, -1 );
            lua_pop( lua_state, 1 );

            lua_getfield( lua_state, 6, "render_target" );
            if ( lua_istable( lua_state, -1 ) ) {
                lua_getfield( lua_state, -1, "blend_enable" );
                if ( lua_isboolean( lua_state, -1 ) )
                    BlendDescription.RenderTarget[ 0 ].BlendEnable = lua_toboolean( lua_state, -1 );
                lua_pop( lua_state, 1 );

                lua_getfield( lua_state, -1, "src_blend" );
                if ( lua_isnumber( lua_state, -1 ) )
                    BlendDescription.RenderTarget[ 0 ].SrcBlend = static_cast<D3D11_BLEND>( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                lua_getfield( lua_state, -1, "dest_blend" );
                if ( lua_isnumber( lua_state, -1 ) )
                    BlendDescription.RenderTarget[ 0 ].DestBlend = static_cast< D3D11_BLEND >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                lua_getfield( lua_state, -1, "blend_op" );
                if ( lua_isnumber( lua_state, -1 ) )
                    BlendDescription.RenderTarget[ 0 ].BlendOp = static_cast< D3D11_BLEND_OP >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                lua_getfield( lua_state, -1, "src_blend_alpha" );
                if ( lua_isnumber( lua_state, -1 ) )
                    BlendDescription.RenderTarget[ 0 ].SrcBlendAlpha = static_cast< D3D11_BLEND >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                lua_getfield( lua_state, -1, "dest_blend_alpha" );
                if ( lua_isnumber( lua_state, -1 ) )
                    BlendDescription.RenderTarget[ 0 ].DestBlendAlpha = static_cast< D3D11_BLEND >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                lua_getfield( lua_state, -1, "blend_op_alpha" );
                if ( lua_isnumber( lua_state, -1 ) )
                    BlendDescription.RenderTarget[ 0 ].BlendOpAlpha = static_cast< D3D11_BLEND_OP >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                lua_getfield( lua_state, -1, "render_target_write_mask" );
                if ( lua_isnumber( lua_state, -1 ) )
                    BlendDescription.RenderTarget[ 0 ].RenderTargetWriteMask = static_cast< D3D11_COLOR_WRITE_ENABLE >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );
            }
            else
                return ThrowError( 6, "Expected a table for BlendDescription.RenderTarget" );

            lua_pop( lua_state, 1 );
        }
        else
            return ThrowError( 6, "Expected a table for BlendDescription" );

        lua_pushboolean( lua_state, Graphics.Initiate(
            SwapChainDescription,
            BufferDescription, 
            RasterizerDescription, 
            DepthStencilDescription, 
            SamplerDescription,
            BlendDescription, 
            lua_tostring( lua_state, 7 ), 
            lua_tostring( lua_state, 8 ), 
            lua_toboolean( lua_state, 9 )
        ) );

        return 1;
    }

    int SetProjectionMatrix( lua_State* lua_state ) {
        auto ThrowError = [ lua_state ] ( int arg, const char* message ) -> int {
            luaL_argerror( lua_state, arg, message );
            return 0;
        };

        if ( !lua_istable( lua_state, 1 ) )
            return ThrowError( 1, "Expected a table as the first argument" );

        float Matrix[ 4 ][ 4 ];
        for ( int i = 0; i < 16; ++i ) {
            lua_rawgeti( lua_state, 1, i + 1 );

            if ( !lua_isnumber( lua_state, -1 ) )
                return ThrowError( 1, "All matrix elements must be numbers" );

            Matrix[ i / 4 ][ i % 4 ] = static_cast< float >( lua_tonumber( lua_state, -1 ) );

            lua_pop( lua_state, 1 );
        }

        Graphics.SetProjectionMatrix( Matrix );

        return 0;
    }

    int SetViewport( lua_State* lua_state ) {
        auto ThrowError = [ lua_state ] ( int arg, const char* message ) -> int {
            luaL_argerror( lua_state, arg, message );
            return 0;
        };

        if ( !lua_isuserdata( lua_state, 1 ) )
            return ThrowError( 1, "Expected a vector2 as the first argument" );

        if ( !lua_isuserdata( lua_state, 2 ) )
            return ThrowError( 1, "Expected a vector2 as the second argument" );

        if ( !lua_isnumber( lua_state, 3 ) )
            return ThrowError( 1, "Expected a number as the third argument" );

        if ( !lua_isnumber( lua_state, 4 ) )
            return ThrowError( 1, "Expected a number as the fourth argument" );

        Graphics.SetViewport(
            *( Vector2* ) luaL_checkudata( lua_state, 1, "vector2" ),
            *( Vector2* ) luaL_checkudata( lua_state, 2, "vector2" ),
            luaL_optnumber( lua_state, 5, 0.0f ),
            luaL_optnumber( lua_state, 6, 1.0f )
        );

        return 0;
    }

    int CreateTexture( lua_State* lua_state ) {
        auto ThrowError = [ lua_state ] ( int arg, const char* message ) -> int {
            luaL_argerror( lua_state, arg, message );
            return 0;
        };

        if ( !lua_isstring( lua_state, 1 ) )
            return ThrowError( 1, "Expected a string for the first argument" );

        D3D11_TEXTURE2D_DESC TextureDescription = {};
        if ( lua_istable( lua_state, 2 ) ) {
            lua_pushvalue( lua_state, 2 );

            lua_pushstring( lua_state, "width" );
            lua_gettable( lua_state, -2 );
            if ( !lua_isnil( lua_state, -1 ) )
                TextureDescription.Width = lua_tointeger( lua_state, -1 );
            lua_pop( lua_state, 1 );

            lua_pushstring( lua_state, "height" );
            lua_gettable( lua_state, -2 );
            if ( !lua_isnil( lua_state, -1 ) )
                TextureDescription.Height = lua_tointeger( lua_state, -1 );
            lua_pop( lua_state, 1 );

            lua_pushstring( lua_state, "mip_levels" );
            lua_gettable( lua_state, -2 );
            if ( !lua_isnil( lua_state, -1 ) )
                TextureDescription.MipLevels = lua_tointeger( lua_state, -1 );
            lua_pop( lua_state, 1 );

            lua_pushstring( lua_state, "array_size" );
            lua_gettable( lua_state, -2 );
            if ( !lua_isnil( lua_state, -1 ) )
                TextureDescription.ArraySize = lua_tointeger( lua_state, -1 );
            lua_pop( lua_state, 1 );

            lua_pushstring( lua_state, "format" );
            lua_gettable( lua_state, -2 );
            if ( !lua_isnil( lua_state, -1 ) )
                TextureDescription.Format = static_cast< DXGI_FORMAT >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_pushstring( lua_state, "sample_desc" );
            lua_gettable( lua_state, -2 );
            if ( lua_istable( lua_state, -1 ) ) {
                lua_pushstring( lua_state, "count" );
                lua_gettable( lua_state, -2 );
                if ( !lua_isnil( lua_state, -1 ) )
                    TextureDescription.SampleDesc.Count = lua_tointeger( lua_state, -1 );
                lua_pop( lua_state, 1 );

                lua_pushstring( lua_state, "quality" );
                lua_gettable( lua_state, -2 );

                if ( !lua_isnil( lua_state, -1 ) )
                    TextureDescription.SampleDesc.Quality = lua_tointeger( lua_state, -1 );
                lua_pop( lua_state, 1 );
            }
            lua_pop( lua_state, 1 );

            lua_pushstring( lua_state, "usage" );
            lua_gettable( lua_state, -2 );
            if ( !lua_isnil( lua_state, -1 ) )
                TextureDescription.Usage = static_cast< D3D11_USAGE >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_pushstring( lua_state, "bind_flags" );
            lua_gettable( lua_state, -2 );
            if ( !lua_isnil( lua_state, -1 ) )
                TextureDescription.BindFlags = lua_tointeger( lua_state, -1 );
            lua_pop( lua_state, 1 );

            lua_pushstring( lua_state, "cpu_access_flags" );
            lua_gettable( lua_state, -2 );
            if ( !lua_isnil( lua_state, -1 ) )
                TextureDescription.CPUAccessFlags = lua_tointeger( lua_state, -1 );
            lua_pop( lua_state, 1 );

            lua_pushstring( lua_state, "misc_flags" );
            lua_gettable( lua_state, -2 );
            if ( !lua_isnil( lua_state, -1 ) )
                TextureDescription.MiscFlags = lua_tointeger( lua_state, -1 );
            lua_pop( lua_state, 1 );
        }
        else
            return ThrowError( 2, "Expected a table for the second arguement" );
        lua_pop( lua_state, 1 );

        D3D11_SUBRESOURCE_DATA SubResourceData = {};
        if ( lua_istable( lua_state, 3 ) ) {
            lua_pushvalue( lua_state, 3 );

            lua_pushstring( lua_state, "p_sys_mem" );
            lua_gettable( lua_state, -2 );
            if ( !lua_isnil( lua_state, -1 ) ) {
                if ( lua_islightuserdata( lua_state, -1 ) )
                    SubResourceData.pSysMem = static_cast< unsigned char* >( lua_touserdata( lua_state, -1 ) );
                else
                    luaL_error( lua_state, "p_sys_mem must be a userdata pointer" );
            }
            lua_pop( lua_state, 1 );

            lua_pushstring( lua_state, "sys_mem_pitch" );
            lua_gettable( lua_state, -2 );
            if ( !lua_isnil( lua_state, -1 ) ) {
                if ( lua_isnumber( lua_state, -1 ) )
                    SubResourceData.SysMemPitch = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
                else
                    luaL_error( lua_state, "sys_mem_pitch must be a number" );
            }
            lua_pop( lua_state, 1 );

            lua_pushstring( lua_state, "sys_mem_slice_pitch" );
            lua_gettable( lua_state, -2 );
            if ( !lua_isnil( lua_state, -1 ) ) {
                if ( lua_isnumber( lua_state, -1 ) )
                    SubResourceData.SysMemSlicePitch = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
                else
                    luaL_error( lua_state, "sys_mem_slice_pitch must be a number" );
            }
            lua_pop( lua_state, 1 );
        }
        else
            return ThrowError( 3, "Expected a table for the third arguement" );
        lua_pop( lua_state, 1 );

        D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDescription = {};
        if ( lua_istable( lua_state, 4 ) ) {
            lua_pushvalue( lua_state, 4 );

            lua_pushstring( lua_state, "format" );
            lua_gettable( lua_state, -2 );
            if ( !lua_isnil( lua_state, -1 ) )
                ShaderResourceViewDescription.Format = static_cast< DXGI_FORMAT >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_pushstring( lua_state, "view_dimension" );
            lua_gettable( lua_state, -2 );
            if ( !lua_isnil( lua_state, -1 ) )
                ShaderResourceViewDescription.ViewDimension = static_cast< D3D11_SRV_DIMENSION >( lua_tointeger( lua_state, -1 ) );
            lua_pop( lua_state, 1 );

            lua_pushstring( lua_state, "union" );
            lua_gettable( lua_state, -2 );
            if ( lua_istable( lua_state, -1 ) ) {
                lua_pushstring( lua_state, "texture2d" );
                lua_gettable( lua_state, -2 );

                if ( lua_istable( lua_state, -1 ) ) {
                    lua_pushstring( lua_state, "most_detailed_mip" );
                    lua_gettable( lua_state, -2 );
                    if ( !lua_isnil( lua_state, -1 ) )
                        ShaderResourceViewDescription.Texture2D.MostDetailedMip = lua_tointeger( lua_state, -1 );
                    lua_pop( lua_state, 1 );

                    lua_pushstring( lua_state, "mip_levels" );
                    lua_gettable( lua_state, -2 );

                    if ( !lua_isnil( lua_state, -1 ) )
                        ShaderResourceViewDescription.Texture2D.MipLevels = lua_tointeger( lua_state, -1 );
                    lua_pop( lua_state, 1 );
                }
                lua_pop( lua_state, 1 );
            }
            lua_pop( lua_state, 1 );
        }
        else
            return ThrowError( 4, "Expected a table for the fourth arguement" );
        lua_pop( lua_state, 1 );

        Texture* _Texture = Graphics.CreateTexture(
            lua_tostring( lua_state, 1 ), TextureDescription,
            SubResourceData, ShaderResourceViewDescription
        );

        Texture** UserData = static_cast< Texture** >(
            lua_newuserdata( lua_state, sizeof( Texture* ) )
        );

        *UserData = _Texture;

        luaL_getmetatable( lua_state, "texture" );
        lua_setmetatable( lua_state, -2 );

        return 1;
    }

    int DestroyTexture( lua_State* lua_state ) {
        auto ThrowError = [ lua_state ] ( int arg, const char* message ) -> int {
            luaL_argerror( lua_state, arg, message );
            return 0;
        };

        Texture* _Texture = ( Texture* ) luaL_checkudata(
            lua_state, 1, "texture"
        );

        if ( !_Texture )
            return ThrowError( 1, "Expected a texture for the first argument" );

        Graphics.DestroyTexture( _Texture );

        return 0;
    }

    int _CreateFont( lua_State* lua_state ) {
        auto ThrowError = [ lua_state ] ( int arg, const char* message ) -> int {
            luaL_argerror( lua_state, arg, message );
            return 0;
        };

        if ( !lua_isstring( lua_state, 1 ) )
            return ThrowError( 1, "Expected a string for the first argument" );

        if ( !lua_isnumber( lua_state, 2 ) )
            return ThrowError( 2, "Expected a number for the second argument" );

        if ( !lua_isnumber( lua_state, 3 ) )
            return ThrowError( 3, "Expected a number for the third argument" );

        if ( !lua_isboolean( lua_state, 4 ) )
            return ThrowError( 4, "Expected a boolean for the fourth argument" );

        Font* _Font = Graphics._CreateFont(
            lua_tostring( lua_state, 1 ),
            lua_tointeger( lua_state, 2 ),
            lua_tointeger( lua_state, 3 ),
            lua_toboolean( lua_state, 4 )
        );

        Font** UserData = static_cast< Font** >(
            lua_newuserdata( lua_state, sizeof( Font* ) )
        );

        *UserData = _Font;

        luaL_getmetatable( lua_state, "font" );
        lua_setmetatable( lua_state, -2 );

        return 1;
    }

    int DestroyFont( lua_State* lua_state ) {
        Font* _Font = ( Font* ) luaL_checkudata(
            lua_state, 1, "font"
        );

        if ( _Font )
            Graphics.DestroyFont( _Font );

        return 0;
    }

    int Cleanup( lua_State* lua_state ) {
        Graphics.Cleanup( );

        return 0;
    }
}