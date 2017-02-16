#include <MaterialProperties.h>

MaterialProperties::MaterialProperties(){
	this->shininess = 0.0f;
	this->roughness = 0.0f;
	this->fresnel = 0.0f;
	this->albedo = 0.0f;
}

MaterialProperties::MaterialProperties(float shininess, float fresnel, float roughness, float albedo){
	this->shininess = shininess;
	this->roughness = roughness;
	this->fresnel = fresnel;
	this->albedo = albedo;
}

MaterialProperties::~MaterialProperties(){
	delete &this->roughness;
	delete &this->shininess;
	delete &this->fresnel;
	delete &this->albedo;
}

float * MaterialProperties::getShininess(){
	return &this->shininess;
}

float * MaterialProperties::getRoughness(){
	return &this->roughness;
}

float * MaterialProperties::getFresnel(){
	return &this->fresnel;
}

float * MaterialProperties::getAlbedo() {
	return &this->albedo;
}

void MaterialProperties::setShininess(float shininess){
	this->shininess = shininess;
}

void MaterialProperties::setRoughness(float roughness){
	this->roughness = roughness;
}

void MaterialProperties::setFresnel(float fresnel){
	this->fresnel = fresnel;
}

void MaterialProperties::setAlbedo(float albedo) {
	this->albedo = albedo;
}