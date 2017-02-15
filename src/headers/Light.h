#pragma once
#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <glm\glm\glm.hpp>

using glm::vec3;
using glm::tvec3;

class Light {
private:
	vec3 position;	/*Position of the light*/
	vec3 ambient;	/*Values of the refraction of the light*/
	vec3 diffuse;
	vec3 specular;
	vec3 direction;
	vec3 attenuation;
	tvec3<bool> type;
	bool isActive;
	float spotExp;
	float spotCosCutOff;

public:
	Light();
	Light(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular);
	~Light();

	//-- Getters
	vec3* getPosition();
	float* getPositionX();
	float* getPositionY();
	float* getPositionZ();
	vec3* getAmbient();
	vec3* getDiffuse();
	vec3* getSpecular();
	vec3* getDirection();
	vec3* getAttenuation();
	float* getAttenuationX();
	float* getAttenuationY();
	float* getAttenuationZ();
	tvec3<bool>* getType();
	bool* getTypeXDirectional();
	bool* getTypeYPoint();
	bool* getTypeZSpot();
	bool* active();
	float* getSpotExp();
	float* getSpotCosCutOff();

	//-- Setters
	void setPosition(vec3 position);
	void set(vec3 ambient, vec3 diffuse, vec3 specular);
	void setAmbient(vec3 ambient);
	void setDiffuse(vec3 diffuse);
	void setSpecular(vec3 specular);
	void setActive(bool isActive);
	void setDirection(vec3 direction);
	void setAttenuation(vec3 attenuation);
	void setSpotCosCutOff(float spotCosCutOff);

	//-- Adders
	void addPosition(vec3 position);
};

#endif