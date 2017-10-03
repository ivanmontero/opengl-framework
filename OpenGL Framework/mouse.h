#pragma once
#include <GLFW/glfw3.h>
#include <queue>
#include "constants.h"

#define CURSOR 0
#define BUTTON 1
#define SCROLL 2

struct MouseEvent {
	int type;
	// Cursor & Scroll
	float x;
	float y;
	MouseEvent(int type, float x, float y) 
		: type(type), x(x), y(y) {}
	// Button
	int button;
	int action;
	int mods;
	MouseEvent(int type, int button, int action, int mods) 
		: type(type), button(button), action(action), mods(mods) {}
	MouseEvent() {};
};

class Mouse {
private:
	static bool buttons[8];
	static float x, y;
	static std::queue<MouseEvent> mouseEvents;
public:
	static void Initialize();
	static void CursorCallback(float xpos, float ypos);
	static void ButtonCallback(int button, int action, int mods);
	static void ScrollCallback(float xoffset, float yoffset);

	static bool IsButtonDown(int button);
	static float GetX();
	static float GetY();

	// Event based
	static bool NextEvent();
	// Button
	static int GetEventButton();
	static bool GetEventButtonState();
	// Cursor & Scroll
	static float GetEventX();
	static float GetEventY();

public:
	static MouseEvent Event;	// current event
};