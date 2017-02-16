#pragma once
#ifndef __LIGHT_PROPERTIES_H__
#define __LIGHT_PROPERTIES_H__

class MaterialProperties {
private:
	float shininess;
	float fresnel;
	float roughness;
	float albedo;

public:
	MaterialProperties();
	MaterialProperties(float shininess, float fresnel, float roughness, float albedo);
	~MaterialProperties();

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