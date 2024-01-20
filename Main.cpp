#include"Mesh.h"

const unsigned int height = 800;
const unsigned int width = 800;


// Vertices coordinates
Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
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

	// texture data
	Texture textures[]
	{
		Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// storing the mesh data in vectors for the mesh
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	// create the floor mesh
	Mesh floor(verts, ind, tex);

	// shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));

	// create light mesh
	Mesh light(lightVerts, lightInd, tex);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	// opengl by default doesnt know triangle to 
	// boot on top of which one hence the weird render 
	// where triangle disappears
	// enables the depth buffer
	glEnable(GL_DEPTH_TEST);

	// to enable vsync otherwise camera is unusable
	glfwSwapInterval(1);

	// creating camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// respond to events perfomed before window is closedj
	while (!glfwWindowShouldClose(window)) {

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		// clean the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// to handler camera inputs
		camera.Inputs(window);

		// send info of camera matrix to vertex shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Draws different meshes
		floor.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// taking care of all GLFW window events
		glfwPollEvents();
	}

	// cleanup
	shaderProgram.Delete();
	lightShader.Delete();

	// destroying the created window object
	glfwDestroyWindow(window);

	// terminate glfw
	glfwTerminate();

	return 0;
}