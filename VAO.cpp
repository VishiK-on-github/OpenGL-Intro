#include"VAO.h"

/// <summary>
/// Constructor that generates a VAO ID
/// </summary>
VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

/// <summary>
/// Links a VBO Attribute such as a position or color to the VAO
/// </summary>
/// <param name="VBO"></param>
/// <param name="layout"></param>
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {

	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

/// <summary>
/// Binds the VAO
/// </summary>
void VAO::Bind() {
	glBindVertexArray(ID);
}

/// <summary>
/// Unbinds the VAO
/// </summary>
void VAO::Unbind() {
	glBindVertexArray(0);
}


/// <summary>
/// Deletes the VAO
/// </summary>
void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}