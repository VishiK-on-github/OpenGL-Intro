#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// defining a list of vertices
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2.0, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

// defining list of indices which ones should 
// be used while constructing triangles
GLuint indices[] = {
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1  // Upper triangle
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

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// respond to events perfomed before window is closedj
	while (!glfwWindowShouldClose(window)) {

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it. 
		// Why is there a need to bind VAO again and again ?
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	// cleanup
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// destroying the created window object
	glfwDestroyWindow(window);

	// terminate glfw
	glfwTerminate();

	return 0;
}