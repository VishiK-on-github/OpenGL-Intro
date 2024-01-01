#include "shaderClass.h"

/// <summary>
/// This method is use to read contents of a file and return it
/// </summary>
/// <param name="filename">
/// The name of the file to be read
/// </param>
/// <returns></returns>
std::string get_file_contents(const char* filename) {

	std::ifstream in(filename, std::ios::binary);

	if (in) {

		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	}

	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// GPU cant understand source code so we compile to machine code
	glCompileShader(vertexShader);
	// Check for vertex shader compile errors
	compileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Fragment Shader into machine code
	glCompileShader(fragmentShader);
	// Check for vertex shader compile errors
	compileErrors(fragmentShader, "FRAGMENT");

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();

	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	// Check if shaders are linked correctly
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

// Activates the Shader Program
void Shader::Activate() {

	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete() {

	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type) {

	// used to store status of compilation
	GLint hasCompiled;
	// character array used to store error message
	char infoLog[1024];

	if (type != "PROGRAM") {

		// checks the status of the last compile operation on shader was successful
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);

		if (hasCompiled == GL_FALSE) {
			// used to get latest info logs for shader
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for : " << type << "\n" << infoLog << std::endl;
		}
	}
	else {

		// checks the status of the last linking operation of shader was successful
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);

		if (hasCompiled == GL_FALSE) {
			// used to get latest info logs for program
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for : " << type << "\n" << infoLog << std::endl;
		}
	}

}