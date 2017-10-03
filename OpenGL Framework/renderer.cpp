#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "renderer.h"
#include "camera.h"

glm::mat4 Renderer::projection = glm::mat4();
float Renderer::distance = 100.0f;
float Renderer::fov = PI / 3.0f;
bool Renderer::wireframe = false;
GLuint Renderer::currentShader = 0;
int Renderer::frameWidth = 0;
int Renderer::frameHeight = 0;

bool Renderer::Initialize(int width, int height) {
	// TODO: projection, init opengl
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}
	Resize(width, height);
	// Do 
	return true;
}

void Renderer::Resize(int width, int height) {
	glViewport(0, 0, width, height);
	projection = glm::perspective(fov, (float)width / height, 0.001f, distance);
	// TODO: Get from viewport
	frameWidth = width;
	frameHeight = height;
}

void Renderer::Clear() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::Clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

// Sets the projection and view matrix
void Renderer::Render(int indices) {
	SetUniform("projection", projection);
	SetUniform("view", Camera::GetViewMatrix());
	glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, nullptr);
}


void Renderer::SetShader(GLuint shader) {
	currentShader = shader;
	glUseProgram(shader);
}

void Renderer::SetVAO(GLuint vao) {
	glBindVertexArray(vao);
}

void Renderer::SetFramebuffer(GLuint fbo) {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Renderer::SetUniform(const char* name, float f) {
	glUniform1f(glGetUniformLocation(currentShader, name), f);
}

void Renderer::SetUniform(const char* name, int i) {
	glUniform1i(glGetUniformLocation(currentShader, name), i);
}

void Renderer::SetUniform(const char* name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(currentShader, name), x, y, z);
}

void Renderer::SetUniform(const char* name, glm::mat4 mat) {
	glUniformMatrix4fv(glGetUniformLocation(currentShader, name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Renderer::SetFOV(float rad) {
	fov = rad;
	projection = glm::perspective(fov, (float)frameWidth / frameHeight, 0.001f, distance);
}

void Renderer::SetRenderDistance(float dist) {
	distance = dist;
	projection = glm::perspective(fov, (float)frameWidth / frameHeight, 0.001f, distance);
}

GLuint Renderer::CreateShader(const char* vert, const char* frag) {
	return CreateShader(vert, nullptr, frag);
}

GLuint Renderer::CreateShader(const char* vert, const char* geom, const char* frag) {
	GLuint program = glCreateProgram();

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	CompileShader(vertex, vert);
	glAttachShader(program, vertex);

	if (geom) {
		GLuint geometry = glCreateShader(GL_GEOMETRY_SHADER);
		CompileShader(geometry, geom);
		glAttachShader(program, geometry);
	}

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	CompileShader(fragment, frag);
	glAttachShader(program, fragment);

	glLinkProgram(program);

	// Check
	GLint success;
	GLchar infolog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infolog);
		std::cout << "Failed to link program\n" << infolog << std::endl;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}

// Returns the Vertex Array Object
GLuint Renderer::CreateCube() {
	GLfloat vertices[] = {
		// Positions          // Normals
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	GLuint indices[36] = {
		0,1,2,
		3,4,5,
		6,7,8,
		9,10,11,
		12,13,14,
		15,16,17,
		18,19,20,
		21,22,23,
		24,25,26,
		27,28,29,
		30,31,32,
		33,34,35
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	return VAO;
}

void Renderer::CompileShader(GLuint id, const char* filepath) {
	std::string code;
	std::ifstream file(filepath, std::ios::in);
	if (!file.is_open()) {
		std::cout << "Could not read file " << filepath << ". File does not exist.\n";
		return;
	}
	std::string line = "";
	while (!file.eof()) {
		std::getline(file, line);
		code.append(line + "\n");
	}
	file.close();

	// Compile
	const GLchar* src = code.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// Check
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "Shader " << filepath << " failed to load!" << infoLog << std::endl;
	}
}
