#version 330 core

// Positions / co-ordinates
layout (location = 0) in vec3 aPos;
// normals (not normalised per se)
layout (location = 1) in vec3 aNormal;
// colors
layout (location = 2) in vec3 aColor;
// texture
layout (location = 3) in vec2 aTex;

// outputs the current position of the fragment shader
out vec3 crntPos;
// we output color of fragment shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;
// outputs the normal for the fragment shader
out vec3 Normal;

// matrices needed for 3D view with perspective
uniform mat4 camMatrix;
// imports the model matrix from the main function
uniform mat4 model;

void main()
{
	// calculates the current position
	crntPos = vec3(model * vec4(aPos, 1.0f));

	// Assigns the normal from the vertex data to the normal
	Normal = aNormal;

	// Assigns the colors from the Vertex Data to "color"
	color = aColor;

	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;

	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}