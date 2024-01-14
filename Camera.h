#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera {
public:

	// storing position of the camera
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;

	// height and widht of window
	int width;
	int height;

	// setting speed of the camera and sensitivity
	float speed = 1.0f;
	float sensitivity = 100.0f;

	// camera constructor
	Camera(int width, int height, glm::vec3 position);

	// updating the camera matrix 
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);

	// updating and exporting camera matrix to vertex shader
	void Matrix(Shader& shader, const char* uniform);

	// to handle camera inputs
	void Inputs(GLFWwindow* window);
};

#endif // !CAMERA_CLASS_H
