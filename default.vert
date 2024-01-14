#version 330 core

// Positions / co-ordinates
layout (location = 0) in vec3 aPos;

// colors
layout (location = 1) in vec3 aColor;

// texture
layout (location = 2) in vec2 aTex;

//
layout (location = 3) in vec3 aNormal;

// we output color of fragment shader
out vec3 color;

// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

out vec3 Normal;
out vec3 crntPos;

// matrices needed for 3D view with perspective
uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	
	crntPos = vec3(model * vec4(aPos, 1.0f));

	// Outputs the positions/coordinates of all vertices
   gl_Position = camMatrix * vec4(crntPos, 1.0);
   // Assigns the colors from the Vertex Data to "color"
   color = aColor;
   // Assigns the texture coordinates from the Vertex Data to "texCoord"
   texCoord = aTex;

   Normal = aNormal;
}