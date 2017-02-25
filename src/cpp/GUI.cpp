#include <GUI.h>
#include <iostream>

GUI* GUI::uniqueGUI = NULL;
GLFWwindow* GUI::gWindow = NULL;
int GUI::gWidth = 1440;
int GUI::gHeight = 900;

GUI::GUI(RenderController* renderController) :RenderColleague(renderController) {
	GUI::gWidth = 1440;
	GUI::gHeight = 900;

	if (!initGlfw() || glewInit() != GLEW_OK)
		exit(1);
}


GUI::GUI(RenderController* renderController, const int gWidth, const int gHeight) : RenderColleague(renderController) {
	GUI::gWidth = gWidth;
	GUI::gHeight = gHeight;

	if (!initGlfw() || glewInit() != GLEW_OK)
		exit(1);
}


GUI::~GUI() {
	glfwDestroyWindow(GUI::gWindow);
	glfwTerminate();
}


GUI* GUI::Instance(RenderController* renderController) {
	if (!uniqueGUI)
		uniqueGUI = new GUI(renderController);
	return uniqueGUI;
}

GUI* GUI::Instance(RenderController* renderController, const int width, const int height) {
	if (!uniqueGUI)
		uniqueGUI = new GUI(renderController, width, height);
	return uniqueGUI;
}

void GUI::Destroy() {
	if (!uniqueGUI) return;
	uniqueGUI->~GUI();
}


float GUI::getHeight() {
	return (float)GUI::gHeight;
}


float GUI::getWidth() {
	return (float)GUI::gWidth;
}


GLFWwindow * GUI::getWindow() {
	return GUI::gWindow;
}

void GUI::setSize(const float width, const float height) {
	reshape(GUI::gWindow, (int)width, (int)height);
}

void GUI::Notify(string message, void* data) {

}


bool GUI::initGlfw() {
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_SAMPLES, 4);
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GUI::gWindow = glfwCreateWindow(GUI::gWidth, GUI::gHeight, "3DScene", NULL, NULL);

	if (!GUI::gWindow) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(GUI::gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(GUI::gWindow, (vidMode->width - GUI::gWidth) >> 1, (vidMode->height - GUI::gHeight) >> 1);

	//-- GLFW Callbacks
	glfwSetWindowSizeCallback(GUI::gWindow, reshape);
	glfwSetKeyCallback(GUI::gWindow, keyInput);
	glfwSetMouseButtonCallback(GUI::gWindow, mouseButton);
	glfwSetCursorPosCallback(GUI::gWindow, cursorPos);
	glfwSetScrollCallback(GUI::gWindow, scrollCallback);

	return true;
}


void GUI::reshape(GLFWwindow *window, int width, int height) {
	GUI* localGUI = GUI::Instance(NULL);
	glViewport(0, 0, GUI::gWidth, GUI::gHeight);
	localGUI->renderController->Send("Reshape", (void*)(new float[2]{ (float)GUI::gWidth, (float)GUI::gHeight }), localGUI);
}


/*Visual Callbacks*/
void GUI::cursorPos(GLFWwindow* window, double x, double y) {
	//-- Prevent default
	if (TwEventMousePosGLFW(int(x), int(y))) return;

	GUI *localUserInterface = GUI::Instance(NULL);
	int stateMouseButtonRight = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
	int stateMouseButtonLeft = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	int x1 = (int)x;
	int y1 = (int)y;
	localUserInterface->renderController->Send("mouseButton", (void*)(new int[4]{ GLFW_MOUSE_BUTTON_LEFT , stateMouseButtonLeft, x1, y1 }), localUserInterface);
}


void GUI::mouseButton(GLFWwindow* window, int button, int action, int mods) {
	//-- Prevent default
	if (TwEventMouseButtonGLFW(button, action)) return;
}


void GUI::keyInput(GLFWwindow * window, int key, int scancode, int action, int mods) {
	//-- Prevent default
	if (TwEventKeyGLFW(key, action)) return;

	GUI *localUserInterface = GUI::Instance(NULL);
	/*Key pressed an key release*/
	localUserInterface->renderController->Send("eventKeyPressed", (void*)(new int[2]{key , action}), localUserInterface);
}

void GUI::scrollCallback(GLFWwindow * window, double mod, double scroll) {
	//-- Prevent default
	if (TwEventMouseWheelGLFW((int)scroll)) return;

	GUI *localUserInterface = GUI::Instance(NULL);
	int scroll_value = (int)scroll;
	localUserInterface->renderController->Send("eventScroll", (void*)&scroll_value, localUserInterface);
}



//-- Mouse Class
vec2 Mouse::position = vec2();
double Mouse::x = 0.0f;
double Mouse::y = 0.0f;

Mouse::Mouse() {}

Mouse::~Mouse() {}

vec2 Mouse::getPosition() {
	glfwGetCursorPos(GUI::getWindow(), &Mouse::x, &Mouse::y);
	Mouse::position.x = (float)Mouse::x;
	Mouse::position.y = (float)Mouse::y;
	return position;
}
