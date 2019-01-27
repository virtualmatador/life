#version 430

uniform int width;
uniform int height;

layout(std430, binding = 0) buffer SSB0
{
	int Cells[];
};
layout(std430, binding = 1) buffer SSB1
{
	int NewCells[];
};

flat out vec4 color;

void main()
{
	int y = gl_VertexID / width;
	int x = gl_VertexID - y * width;
	gl_Position = vec4(
		(0.5 + x) / width * 2.0 - 1.0,
		(height - (0.5 + y)) / height * 2.0 - 1.0,
		0.0, 1.0);
	color = vec4(0.5, Cells[gl_VertexID], 0.5, 1.0);
	if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
		NewCells[gl_VertexID] = 0;
	else
	{
		int iNeighbors = 0;
		for (int i = x - 1; i < x + 2; ++i)
			for (int j = y - 1; j < y + 2; ++j)
				if (Cells[j * width + i] != 0)
					++iNeighbors;
		if (Cells[gl_VertexID] == 0)
		{
			if (iNeighbors == 3)
				NewCells[gl_VertexID] = 1;
			else
				NewCells[gl_VertexID] = 0;
		}
		else
		{
			--iNeighbors;
			if (iNeighbors == 2 || iNeighbors == 3)
				NewCells[gl_VertexID] = 1;
			else
				NewCells[gl_VertexID] = 0;
		}
	}
}
