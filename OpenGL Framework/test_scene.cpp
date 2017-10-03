#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "test_scene.h"
#include "renderer.h"
#include "window.h"
#include "camera.h"
#include "keyboard.h"
#include "mouse.h"

void TestScene::Initialize() {
	cube = Renderer::CreateCube();
	model = glm::mat4();
	shader = Renderer::CreateShader("test.vert", "test.frag");
	noise = FastNoise();
	time = 0;
	speed = 1.0f;
}

void TestScene::Update(float delta) {
	while (Keyboard::NextEvent()) {
		if (Keyboard::Event.action == PRESS) {
			std::cout << "key pressed: " << Keyboard::Event.key << std::endl;
		}
	}

	while (Mouse::NextEvent()) {
		if (Mouse::Event.type == BUTTON) {
			if (Mouse::Event.action == PRESS) {
				std::cout << "mouse pressed: " << Mouse::Event.button << " (" << Mouse::GetX() << ", " << Mouse::GetY() << ")" << std::endl;
			}
		}
	}

	if (Keyboard::IsKeyDown(KEY_EQUAL))
		speed += .0005;
	if (Keyboard::IsKeyDown(KEY_MINUS))
		speed -= .0005;

	//r += delta;
	//g += delta;
	//b += delta;
	//if (r > 1.0f) r -= 1.0f;
	//if (g > 1.0f) g -= 1.0f;
	//if (b > 1.0f) b -= 1.0f;
	Camera::SetPosition(0.0f, 0.0f, 4.0f);
	time += delta * speed;
}

void TestScene::Render() {
	//Renderer::Clear(r, g, b, 1.0f);
	Renderer::Clear();
	Renderer::SetShader(shader);
	Renderer::SetVAO(cube);

	model = glm::mat4();
	//model = glm::rotate(model, time, glm::vec3(1.0f));
	float n = noise.GetPerlin(time * 100, 0.0);
	//std::cout << n << " " << time <<std::endl;
	model = glm::translate(model, glm::vec3(0, n, 0));

	Renderer::SetUniform("model", model);
	Renderer::Render(CUBE_INDICES);
	Renderer::SetVAO(0);
	Renderer::SetShader(0);
}

void TestScene::Release() {}

TestScene TestScene::instance = TestScene();

TestScene* TestScene::GetInstance() {	return &instance;	}

TestScene::TestScene() {}
