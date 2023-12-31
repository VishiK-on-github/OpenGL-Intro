#include"EBO.h"

/// <summary>
/// Constructor that generates a Elements Buffer Object and links it to indices
/// </summary>
/// <param name="indices">
/// order of indices in which triangles must be rendered
/// </param>
/// <param name="size">
/// size of the list of indices
/// </param>
EBO::EBO(GLuint* indices, GLsizeiptr size) {

	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

/// <summary>
/// Bind the EBO
/// </summary>
void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

/// <summary>
/// Unbinds the EBO
/// </summary>
void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/// <summary>
/// Deletes the EBO
/// </summary>
void EBO::Delete() {
	glDeleteBuffers(1, &ID);
}