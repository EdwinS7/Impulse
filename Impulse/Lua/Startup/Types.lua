D3D11_TEXTURE2D_DESC = {
        Width = 0,
        Height = 0,
        MipLevels = 1,
        ArraySize = 1,
        Format = DXGI_FORMAT.UNKNOWN,

        SampleDesc = { 
            Count = 1, 
            Quality = 0
        },

        Usage = D3D11_USAGE.DEFAULT,
        BindFlags = 0,
        CPUAccessFlags = 0,
        MiscFlags = 0
    }

D3D11_SHADER_RESOURCE_VIEW_DESC = {
    Format = nil,  -- DXGI_FORMAT (you can set the actual format value here)
    ViewDimension = nil,  -- D3D11_SRV_DIMENSION (you can set the actual dimension here)
    union = {
        Buffer = nil,                -- D3D11_BUFFER_SRV
        Texture1D = nil,             -- D3D11_TEX1D_SRV
        Texture1DArray = nil,        -- D3D11_TEX1D_ARRAY_SRV
        Texture2D = nil,             -- D3D11_TEX2D_SRV
        Texture2DArray = nil,        -- D3D11_TEX2D_ARRAY_SRV
        Texture2DMS = nil,           -- D3D11_TEX2DMS_SRV
        Texture2DMSArray = nil,      -- D3D11_TEX2DMS_ARRAY_SRV
        Texture3D = nil,             -- D3D11_TEX3D_SRV
        TextureCube = nil,           -- D3D11_TEXCUBE_SRV
        TextureCubeArray = nil,      -- D3D11_TEXCUBE_ARRAY_SRV
        BufferEx = nil,              -- D3D11_BUFFEREX_SRV
    }
}