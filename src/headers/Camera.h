#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

/*Global includes*/
#include <glew\glew.h>
#include <glfw3.h>
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>

/*Class Includes*/
#include <Player.h>

using glm::mat4;
using glm::vec3;

class Camera {
private:
	mat4 view;
	vec3 position;	/*Position of the camera*/
	vec3 target;	/*What you want to look at (center of the principal player)*/
	vec3 up;		/*(0, 1, 0) to look upside*/
	vec3 cameraFront;
	Player *player;

	//-- Varibles to move camera
	float distanceFromPlayer;
	float angleAroundPlayer;
	float pitch;
	float yaw;
	float roll;
	float speed;

	/*Private Functions*/
	void refresh();

	/*Functions to move the camera*/
	float calculateHorizontalDistance();
	float calculateVerticalDistance();
	void calculateCameraPossition(float horizontalDistance, float verticalDistance);

public:
	Camera();
	Camera(Player* player);
	Camera(vec3 position, vec3 target, vec3 up);
	~Camera();

	/*Getters*/
	mat4 getMatrix();
	vec3 getPosition();
	vec3 getTarget();
	vec3 getUp();

	/*Setters*/
	void setPosition(vec3 position);
	void setPositionAndTarget(vec3 position, vec3 target);	/*Es la funcion que más va a ayudar*/
	void setTarget(vec3 target);
	void setUp(vec3 up);

	/*Adders*/
	void addPosition(vec3 position);
	void addPositionAndTarget(vec3 position, vec3 target);	/*Es la funcion que más va a ayudar*/
	void addTarget(vec3 target);
	void addUp(vec3 up);

	/*Functions to move the camera*/
	void move();
	void calculateZoom(int scroll);
	void calculatePitch(int button, int action, int x, int y);
	void calculateAngleAroundPlayer(int button, int action, int x, int y);
};

#endif