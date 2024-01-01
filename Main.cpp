#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// defining a list of vertices
GLfloat vertices[] =
{ //    COORDINATES      /     COLORS          /   TexCoord   //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f,  0.0f,    0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f,  0.0f,    0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f,  1.0f,    1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f,  1.0f,    1.0f, 0.0f  // Lower left corner

};

// defining list of indices what order should
// be used while constructing triangles
GLuint indices[] = {
	0, 2, 1, // Upper triangle
	0, 3, 2  // Lower triangle
};


int main() {

	// used to init glfw
	glfwInit();

	/* glfw doesnt know version info
	we specify it by using hints
	version being used is OpenGL 3.3
	*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // major version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // minor version

	// used to specify that we need newer features. Specify that we are using core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// creating a window object of size 800 x 800 pixels
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Rendering", NULL, NULL);

	// error check if the window object creation has failed
	if (window == NULL) {

		std::cout << "Failed to create GLFW window !" << std::endl;
		glfwTerminate();
		return -1;
	}

	// telling the context to use the newly created window object
	glfwMakeContextCurrent(window);

	// loading glad so it configures OpenGL
	gladLoadGL();

	// specifying area of window we want opengl 
	// to render in (bottom-left is 0,0)
	glViewport(0, 0, 800, 800);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// get ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//  Texture
	Texture popCat("./nyan_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);


	// respond to events perfomed before window is closedj
	while (!glfwWindowShouldClose(window)) {

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Assigns a value to var uniform. Must use uniform only after activating shader program
		glUniform1f(uniID, 0.5f);
		// binding the texture
		popCat.Bind();
		// Bind the VAO so OpenGL knows to use it. 
		// Why is there a need to bind VAO again and again ?
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// taking care of all GLFW window events
		glfwPollEvents();
	}

	// cleanup
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram.Delete();

	// destroying the created window object
	glfwDestroyWindow(window);

	// terminate glfw
	glfwTerminate();

	return 0;
}