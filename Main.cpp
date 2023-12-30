#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() {

	// used to init glfw
	glfwInit();

	/* glfw doesnt know version info
	we specify it by using hits */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // major version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // minor version

	// used to specify that we need newer supported features
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// creating a window object
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Rendering", NULL, NULL);

	// error checking for window object
	if (window == NULL) {

		std::cout << "Failed to create GLFW window !" << std::endl;
		glfwTerminate();
		return -1;
	}

	// telling the context to use the newly created window object
	glfwMakeContextCurrent(window);

	// loading configs for opengl
	gladLoadGL();

	// specifying area of window we want opengl 
	// to render in (bottom-left is 0,0)
	glViewport(0, 0, 800, 800);

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