#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"

class Mesh {
public:
	// defining dynamic vectors of specified type as 
	// we dont know the size of them while creating
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	VAO VAO;

	// constructor for mesh class
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	void Draw(Shader& shader, Camera& camera);
};

#endif // !MESH_CLASS_H
