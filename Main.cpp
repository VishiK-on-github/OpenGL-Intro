#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

const unsigned int height = 800;
const unsigned int width = 800;

// defining a list of vertices
GLfloat vertices[] =
{ //    COORDINATES      /     COLORS            /   TexCoord   
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f

};

// defining list of indices what order should
// be used while constructing triangles
GLuint indices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Rendering", NULL, NULL);

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
	glViewport(0, 0, width, height);

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

	// variables to help set rotation
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// opengl by default doesnt know triangle to 
	// boot on top of which one hence the weird render 
	// where triangle disappears
	// enables the depth buffer
	glEnable(GL_DEPTH_TEST);


	// respond to events perfomed before window is closedj
	while (!glfwWindowShouldClose(window)) {

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		// clean the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// timer code block
		double currentTime = glfwGetTime();

		// updating rotation based on time difference
		if (currentTime - prevTime >= 1.0f / 60.0f) {
			rotation += 0.5f;
			prevTime = currentTime;
		}

		// init identity matrices
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// rotating the model with texture with time
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

		// before this all the objects - model, world, camera are at origin
		// we need to move the camera instead we move the world itself
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		// here we set clipping - from how close or till how far camera
		// can see something
		proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

		// setting variables for the vertex shaders
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


		// Assigns a value to var uniform. Must use uniform only after activating shader program
		glUniform1f(uniID, 0.5f);
		// binding the texture
		popCat.Bind();
		// Bind the VAO so OpenGL knows to use it. 
		// Why is there a need to bind VAO again and again ?
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
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