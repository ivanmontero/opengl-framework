#pragma once
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
/* TODO 
 - Init
 - Render meshes
 - Render
 - Create personalized mesh class
*/

#define PI 3.14159265358979f

class Renderer {
private:
	static glm::mat4 projection;
	static float distance, fov;
	static bool wireframe;
	static GLuint currentShader;
	//static GLuint VAO, VBO, EBO;
	static int frameWidth, frameHeight;
public:
	static bool Initialize(int width, int height);
	static void Resize(int width, int height);

	static void Clear();
	static void Clear(float r, float g, float b, float a);

	static void Render(int indices);

	static void SetShader(GLuint shader);
	static void SetVAO(GLuint vao);
	static void SetFramebuffer(GLuint fbo);

	static void SetUniform(const char* name, float f);
	static void SetUniform(const char* name, int i);
	static void SetUniform(const char* name, float x, float y, float z);
	static void SetUniform(const char* name, glm::mat4 mat);

	static void SetFOV(float rad);
	static void SetRenderDistance(float dist);

	static GLuint CreateShader(const char*, const char*);
	static GLuint CreateShader(const char*, const char*, const char*);
	static GLuint CreateTexture(const char*);	// TODO: Resource manager
	static GLuint CreateTexture(int, int);

	static GLuint CreateCube();

private:
	static void CompileShader(GLuint, const char*);
};

#define CUBE_INDICES 36