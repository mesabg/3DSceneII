#pragma once
#ifndef __LIGHT_H__
#define __LIGHT_H__

//-- Global Includes
#include <glm\glm\glm.hpp>

//-- Class Includes
#include <CGLSLProgram.h>

using glm::vec3;
using glm::tvec3;

class Light {
private:
	vec3 position;	//-- Position of the light
	vec3 ambient;	//-- Values of the refraction of the light
	vec3 diffuse;
	vec3 specular;
	vec3 direction;
	vec3 attenuation;
	tvec3<bool> type;
	bool isActive;
	float spotExp;
	float spotCosCutOff;
	float spotCosOuterCutOff;

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
	float* getSpotCosOuterCutOff();

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
	void setSpotCosOuterCutOff(float spotCosOuterCutOff);

	//-- Adders
	void addPosition(vec3 position);

	//-- Other General Functions
	/// <summary>
	/// Binds the light to the actual shader program.
	/// </summary>
	/// <param name="shader">Shader Program to use.</param>
	/// <param name="mode">If false, light will be bind it as a global light. If true light will be bind it as a material light. Default "false".</param>
	/// <param name="index">Index to use when it is a global light. Default "0".</param>
	/// <returns>nothing</returns>
	void bind(CGLSLProgram* shader, bool mode = false, int index = 0);
};

#endif