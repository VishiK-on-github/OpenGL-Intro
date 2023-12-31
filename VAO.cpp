#include"VAO.h"

/// <summary>
/// Constructor that generates a VAO ID
/// </summary>
VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

/// <summary>
/// Links a VBO to the VAO using a certain layout
/// </summary>
/// <param name="VBO"></param>
/// <param name="layout"></param>
void VAO::LinkVBO(VBO& VBO, GLuint layout) {

	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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