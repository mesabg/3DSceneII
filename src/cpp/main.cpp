#include <main.h>

int main() {
	ConcreteRenderController* renderController = new ConcreteRenderController(1440.0f, 900.0f);
	renderController->infinity();
	renderController->finish();
}

float getFrameTimeSeconds(){
	return (float)ConcreteRenderController::getFrameTimeSeconds();
}

vec2 getMousePosition(){
	return Mouse::getPosition();
}

vec2 getDisplaySize(){
	return vec2(GUI::getWidth(), GUI::getHeight());
}
