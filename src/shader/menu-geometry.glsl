#version 450

layout(points) in;
layout(line_strip, max_vertices = 2) out;
layout(std430, binding = 0) buffer SSB0
{
	float font[];
};

in int g_character[];
in float g_scale[];
in vec4 g_color[];
out vec4 f_color;

void main()
{
	f_color = g_color[0];
	int fnt = g_character[0] * 8 * 2;
	bool bInit = false;
	for (int i = 0; i < 8 && (font[fnt + i * 2] > -0.5 || font[fnt + i * 2 + 1] > -0.5); ++i)
	{
		if (font[fnt + i * 2] > -0.5 && font[fnt + i * 2 + 1] > -0.5)
		{
			if (bInit)
				EmitVertex();
			gl_Position = vec4(
				gl_in[0].gl_Position.x + font[fnt + i * 2] * g_scale[0], 
				gl_in[0].gl_Position.y + font[fnt + i * 2 + 1] * g_scale[0],
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
