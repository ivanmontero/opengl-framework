//#include "mesh.h"
//#include "shader.h"
//#include <sstream>
//
//Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures) {
//	this->vertices = vertices;
//	this->indices = indices;
//	this->textures = textures;
//
//	glGenVertexArrays(1, &this->VAO);
//	glGenBuffers(1, &this->VBO);
//	glGenBuffers(1, &this->EBO);
//
//	glBindVertexArray(this->VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
//
//	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
//
//	// Vertex positions
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
//
//	// Vertex normals
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
//
//	// Vertex Texture Coords
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
//
//	glBindVertexArray(0);
//}
//
//void Mesh::Draw(Shader shader) {
//	GLuint diffuseNum = 1;
//	GLuint specularNum = 1;
//
//	for (GLuint i = 0; i < this->textures.size(); i++) {
//		glActiveTexture(GL_TEXTURE0 + i);
//
//		std::string name = this->textures[i].type;
//		std::string number = (name == "texture_diffuse") ? std::to_string(diffuseNum++) : std::to_string(specularNum++);
//
//		glUniform1i(glGetUniformLocation(shader.Program, (/* "material." + */name + number).c_str()), i);
//		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
//	}
//	//glActiveTexture(GL_TEXTURE0);
//
//	// Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
//	glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 16.0f);
//
//	glBindVertexArray(this->VAO);
//	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//
//	for (GLuint i = 0; i < this->textures.size(); i++) {
//		glActiveTexture(GL_TEXTURE0 + i);
//		glBindTexture(GL_TEXTURE_2D, 0);
//	}
//}