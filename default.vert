#version 330 core

// Positions / co-ordinates
layout (location = 0) in vec3 aPos;

// colors
layout (location = 1) in vec3 aColor;

// texture
layout (location = 2) in vec2 aTex;

// we output color of fragment shader
out vec3 color;

// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

// controls scale of the vertices
uniform float scale;

// matrices needed for 3D view with perspective
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	// Outputs the positions/coordinates of all vertices
   gl_Position = proj * view * model * vec4(aPos, 1.0);
   // Assigns the colors from the Vertex Data to "color"
   color = aColor;
   // Assigns the texture coordinates from the Vertex Data to "texCoord"
   texCoord = aTex;
}