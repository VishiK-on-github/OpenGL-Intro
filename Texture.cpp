#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {

	// assigns type of texture to the texture object
	type = texType;

	// storing height, width and number of color channels of the image
	int widthImg, heightImg, numColCh;

	// flipping the image so it does not appear upside down
	stbi_set_flip_vertically_on_load(true);

	// reading the image file and store it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// generate OpenGL texture object
	glGenTextures(1, &ID);

	// assign the texture to a texture unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// configuring type of algo used to make text smaller / larger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// configuring way in which texture repeats itself
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// assigning the image to OpenGL texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// generating mipmaps
	glGenerateMipmap(texType);

	// deleting the image data since its already in OpenGL text object
	stbi_image_free(bytes);

	// unbinding the OpenGL texture object so its not modified
	glBindTexture(texType, 0);

}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {

	// get the uniform location
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);

	// activating shader before changing value of the uniform
	shader.Activate();

	// set the value of the uniform
	glUniform1i(texUni, unit);
}

// binding the texture
void Texture::Bind() {
	glBindTexture(type, ID);
}

// unbinding the texture
void Texture::Unbind() {
	glBindTexture(type, 0);
}

// deleting the texture
void Texture::Delete() {
	glDeleteTextures(1, &ID);
}