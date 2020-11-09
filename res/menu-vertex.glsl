#version 430

layout(location = 0) in vec2 v_xy;
layout(location = 1) in vec2 v_scale;
layout(location = 2) in int v_character;
layout(location = 3) in vec3 v_color;

out vec2 g_scale;
out int g_character;
out vec4 g_color;

void main()
{
	gl_Position = vec4(v_xy, 0.0, 1.0);
	g_scale = v_scale;
	g_character = v_character;
	g_color = vec4(v_color, 1.0);
}
