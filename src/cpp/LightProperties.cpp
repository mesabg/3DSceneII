#include <LightProperties.h>

LightProperties::LightProperties(){
	this->shininess = 0.0f;
	this->roughness = 0.0f;
	this->fresnel = 0.0f;
	this->albedo = 0.0f;
}

LightProperties::LightProperties(float shininess, float fresnel, float roughness, float albedo){
	this->shininess = shininess;
	this->roughness = roughness;
	this->fresnel = fresnel;
	this->albedo = albedo;
}

LightProperties::~LightProperties(){
	delete &this->roughness;
	delete &this->shininess;
	delete &this->fresnel;
	delete &this->albedo;
}

float * LightProperties::getShininess(){
	return &this->shininess;
}

float * LightProperties::getRoughness(){
	return &this->roughness;
}

float * LightProperties::getFresnel(){
	return &this->fresnel;
}

float * LightProperties::getAlbedo() {
	return &this->albedo;
}

void LightProperties::setShininess(float shininess){
	this->shininess = shininess;
}

void LightProperties::setRoughness(float roughness){
	this->roughness = roughness;
}

void LightProperties::setFresnel(float fresnel){
	this->fresnel = fresnel;
}

void LightProperties::setAlbedo(float albedo) {
	this->albedo = albedo;
}