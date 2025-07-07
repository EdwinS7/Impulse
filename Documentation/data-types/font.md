# Font

## Constructor

{% hint style="warning" %}
There is no constructer, use [create\_font](https://edwn.gitbook.io/impulse/enviornment/libraries/graphics#graphics.create_font).
{% endhint %}

<table><thead><tr><th width="124" align="center">Properties</th><th>Description</th></tr></thead><tbody><tr><td align="center">name</td><td>The font’s name or identifier.</td></tr><tr><td align="center">size</td><td>The size of the font in points or pixels.</td></tr><tr><td align="center">padding</td><td>Extra padding around each glyph in pixels.</td></tr><tr><td align="center">antialiasing</td><td>Whether antialiasing (font smoothing) is enabled.</td></tr><tr><td align="center">max_offset_y</td><td>The maximum vertical offset among all glyphs.</td></tr><tr><td align="center">glyphs</td><td>Maps characters to glyph userdata objects.</td></tr></tbody></table>

{% hint style="danger" %}
Font is read-only!
{% endhint %}
