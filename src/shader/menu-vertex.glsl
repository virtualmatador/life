#version 450

in vec2 v_xy;
in vec2 v_scale;
in int v_character;
in vec3 v_color;

out int g_character;
out vec2 g_scale;
out vec4 g_color;

void main()
{
	gl_Position = vec4(v_xy, 0, 1.0);
	g_character = v_character;
	g_scale = v_scale;
	g_color = vec4(v_color, 1.0);
}
