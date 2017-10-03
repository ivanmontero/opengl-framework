#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "scene.h"
#include "fast_noise.h"

class TestScene : public Scene {
private:
	//float r = 0, g = 1.0f/3.0f, b = 2.0f/3.0f;
	GLuint cube;
	GLuint shader;
	glm::mat4 model;
	FastNoise noise;
	float time, speed;
public:
	void Initialize();  
	void Update(float delta);
	void Render();
	void Release();

	static TestScene* GetInstance();
private:
	static TestScene instance;
	TestScene();
};