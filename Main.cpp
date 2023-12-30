#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


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

	// setting the background color to navy blue, last bit set to 1 - opaque, 0 transparent
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	// only pixels on front buffer are displayed hence swap is needed
	glfwSwapBuffers(window);

	// respond to events perfomed before window is closedj
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	// destroying the created window object
	glfwDestroyWindow(window);

	// terminate glfw
	glfwTerminate();

	return 0;
}