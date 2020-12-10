#shader vertex
#version 330 core
layout(location = 0) in vec4 position; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
    TexCoords = position.zw;
}

#shader fragment
#version 330 core
in vec2 TexCoords;
layout(location = 0) out vec4 color;

uniform sampler2D text;
uniform vec4 u_Color;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = u_Color * sampled;
}