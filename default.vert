#version 330 core

// Positions / co-ordinates
layout (location = 0) in vec3 aPos;

// colors
layout (location = 1) in vec3 aColor;

// we output color of fragment shader
out vec3 color;

// controls scale of the vertices
uniform float scale;

void main()
{
	// Outputs the positions/coordinates of all vertices
   gl_Position = vec4((1 + scale) * aPos.x, (1 + scale) *  aPos.y, (1 + scale) * aPos.z, 1.0);
   // Assigns the colors from the Vertex Data to "color"
   color = aColor;
}