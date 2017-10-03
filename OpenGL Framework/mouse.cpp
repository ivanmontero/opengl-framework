#include "mouse.h"

bool Mouse::buttons[8] = {};
float Mouse::x = 0;
float Mouse::y = 0;
std::queue<MouseEvent> Mouse::mouseEvents;
MouseEvent Mouse::Event;

void Mouse::Initialize() {}

void Mouse::CursorCallback(float xpos, float ypos) {
	x = xpos;
	y = ypos;

	mouseEvents.push(MouseEvent(CURSOR, xpos, ypos));
}

void Mouse::ButtonCallback(int button, int action, int mods) {
	if (action == GLFW_PRESS)
		buttons[button] = true;
	else if (action == GLFW_RELEASE)
		buttons[button] = false;

	mouseEvents.push(MouseEvent(BUTTON, button, action, mods));
}

void Mouse::ScrollCallback(float xoffset, float yoffset) {
	mouseEvents.push(MouseEvent(SCROLL, xoffset, yoffset));
}

bool Mouse::IsButtonDown(int button){
	return buttons[button];
}

float Mouse::GetX(){
	return x;
}

float Mouse::GetY(){
	return y;
}

bool Mouse::NextEvent() {
	if(mouseEvents.empty())
		return false;
	Event = mouseEvents.front();
	mouseEvents.pop();
	return true;
}

int Mouse::GetEventButton() {
	return Event.button;
}

bool Mouse::GetEventButtonState() {
	return Event.action == GLFW_PRESS;
}

float Mouse::GetEventX() {
	return Event.x;
}

float Mouse::GetEventY() {
	return Event.y;
}
