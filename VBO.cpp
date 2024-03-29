#include"VBO.h"

VBO::VBO(std::vector<Vertex>& vertices) {

	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

/// <summary>
/// Bind the VBO
/// </summary>
void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

/// <summary>
/// Unbinds the VBO
/// </summary>
void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/// <summary>
/// Deletes the VBO
/// </summary>
void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}