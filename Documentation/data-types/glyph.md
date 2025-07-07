# Glyph

## Constructor

{% hint style="warning" %}
There is no constructer, use [create\_font](https://edwn.gitbook.io/impulse/enviornment/libraries/graphics#graphics.create_font), which returns a list of characters, each with its own glyph.
{% endhint %}

<table><thead><tr><th width="124" align="center">Properties</th><th>Description</th></tr></thead><tbody><tr><td align="center">advance_x</td><td>The horizontal distance to move the cursor after drawing this glyph (in pixels or font units).</td></tr><tr><td align="center">offset_x</td><td>Horizontal offset to apply when rendering the glyph bitmap.</td></tr><tr><td align="center">offset_y</td><td>Vertical offset to apply when rendering the glyph bitmap.</td></tr><tr><td align="center">width</td><td>Width of the glyph bitmap in pixels.</td></tr><tr><td align="center">height</td><td>Height of the glyph bitmap in pixels.</td></tr><tr><td align="center">u0</td><td>Left coordinate of the glyph in the texture atlas.</td></tr><tr><td align="center">v0</td><td>Top coordinate of the glyph in the texture atlas.</td></tr><tr><td align="center">u1</td><td>Right coordinate of the glyph in the texture atlas.</td></tr><tr><td align="center">v1</td><td>Bottom coordinate of the glyph in the texture atlas.</td></tr><tr><td align="center">texture</td><td>Texture resource containing the glyph image.</td></tr></tbody></table>

{% hint style="danger" %}
Glyph is read-only!
{% endhint %}
