#version 450

layout(points) in;
layout(line_strip, max_vertices = 16) out;
layout(std430, binding = 0) buffer SSB0
{
	float font[][8][2];
};

in int g_character[];
in vec2 g_scale[];
in vec4 g_color[];

out vec4 f_color;

void main()
{
	f_color = g_color[0];
	bool bInit = false;
	for (int i = 0; i < 8 && (font[g_character[0]][i][0] > -0.5 || font[g_character[0]][i][1] > -0.5); ++i)
	{
		if (font[g_character[0]][i][0] > -0.5 && font[g_character[0]][i][1] > -0.5)
		{
			if (bInit)
				EmitVertex();
			gl_Position = vec4(
				gl_in[0].gl_Position.x + font[g_character[0]][i][0] * g_scale[0][0], 
				gl_in[0].gl_Position.y + font[g_character[0]][i][1] * g_scale[0][1],
				0.0, 1.0);
			EmitVertex();
			if (bInit)
				EndPrimitive();
			bInit = true;
		}
		else
			bInit = false;
	}
}
