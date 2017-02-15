#pragma once
#ifndef __LIGHT_PROPERTIES_H__
#define __LIGHT_PROPERTIES_H__

class LightProperties {
private:
	float shininess;
	float fresnel;
	float roughness;
	float albedo;

public:
	LightProperties();
	LightProperties(float shininess, float fresnel, float roughness, float albedo);
	~LightProperties();

	//-- Getters
	float* getShininess();
	float* getRoughness();
	float* getFresnel();
	float* getAlbedo();

	//-- Setters
	void setShininess(float shininess);
	void setRoughness(float roughness);
	void setFresnel(float fresnel);
	void setAlbedo(float albedo);

};

#endif