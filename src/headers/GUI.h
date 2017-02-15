#pragma once
#ifndef __USER_INTERFACE_H_
#define __USER_INTERFACE_H_

//-- Global Includes
#include <AntTweakBar.h>

//-- Class Includes
#include <RenderInterface.h>

class GUI : public RenderColleague
{
private:
	/*Variables*/
	static GUI* uniqueGUI;
	static GLFWwindow* gWindow;
	static int gWidth;
	static int gHeight;

	/*Inicializadores*/
	GUI(RenderController* renderController);
	GUI(RenderController* mediator, const int gWidth, const int gHeight);
	~GUI();

	/*Funciones propias*/
	bool initGlfw();

public:

	//-- Get Instance
	static GUI* Instance(RenderController* renderController);
	static GUI* Instance(RenderController* renderController, int width, int height);
	static void Destroy();

	//-- @Override
	void Notify(string message, void* data);

	//-- Get functions
	static float getHeight();
	static float getWidth();
	static GLFWwindow* getWindow();

	//-- Set functions
	void setSize(const float width, const float height);

	//-- GLFW Callbacks
	static void reshape(GLFWwindow *window, int width, int height);
	static void cursorPos(GLFWwindow* window, double x, double y);
	static void mouseButton(GLFWwindow* window, int button, int action, int mods);
	static void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void scrollCallback(GLFWwindow* window, double x, double y);
};


class Mouse {
private:
	static vec2 position;
	static double x, y;

public:
	Mouse();
	~Mouse();

	//-- Getters
	static vec2 getPosition();
};

#endif
