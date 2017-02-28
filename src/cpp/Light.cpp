#include <Light.h>

Light::Light() {
	this->position = vec3(0.0f, 0.0f, 0.0f);
	this->ambient = vec3(1.0f, 1.0f, 1.0f);
	this->diffuse = vec3(1.0f, 1.0f, 1.0f);
	this->specular = vec3(1.0f, 1.0f, 1.0f);
	this->direction = vec3(0.0f, 0.0f, 0.0f);
	this->attenuation = vec3(1.0f, 2.0f, 3.0f);
	this->isActive = true;
	this->type = vec3(true, false, false);
	this->spotExp = 1.0f;
	this->spotCosCutOff = 1.0f;
}

Light::Light(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular) {
	this->position = position;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->direction = vec3(0.50f, 0.10f, -0.40f);
	this->attenuation = vec3(0.0009f, 0.0008f, 0.0007f);
	this->isActive = true;
	this->type = vec3(true, false, false);
	this->spotExp = 0.0001f;
	this->spotCosCutOff = 0.0001f;
}

Light::~Light() {

}

vec3* Light::getPosition() {
	return &(this->position);
}

float * Light::getPositionX(){
	return &(this->position.x);
}

float * Light::getPositionY() {
	return &(this->position.y);
}

float * Light::getPositionZ() {
	return &(this->position.z);
}

vec3* Light::getAmbient() {
	return &this->ambient;
}

vec3* Light::getDiffuse() {
	return &this->diffuse;
}

vec3* Light::getSpecular() {
	return &this->specular;
}

vec3 * Light::getDirection(){
	return &this->direction;
}

vec3 * Light::getAttenuation(){
	return &(this->attenuation);
}

float * Light::getAttenuationX(){
	return &(this->attenuation.x);
}

float * Light::getAttenuationY() {
	return &(this->attenuation.y);
}

float * Light::getAttenuationZ() {
	return &(this->attenuation.z);
}

tvec3<bool>* Light::getType(){
	return &(this->type);
}

bool * Light::getTypeXDirectional(){
	return &(this->type.x);
}

bool * Light::getTypeYPoint() {
	return &(this->type.y);
}

bool * Light::getTypeZSpot() {
	return &(this->type.z);
}

bool * Light::active(){
	return &this->isActive;
}

float * Light::getSpotExp(){
	return &(this->spotExp);
}

float * Light::getSpotCosCutOff(){
	return &(this->spotCosCutOff);
}

void Light::setPosition(vec3 position) {
	this->position = position;
}

void Light::set(vec3 ambient, vec3 diffuse, vec3 specular) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

void Light::setAmbient(vec3 ambient) {
	this->ambient = ambient;
}

void Light::setDiffuse(vec3 diffuse) {
	this->diffuse = diffuse;
}

void Light::setSpecular(vec3 specular) {
	this->specular = specular;
}

void Light::setActive(bool isActive){
	this->isActive = isActive;
}

void Light::setDirection(vec3 direction){
	this->direction = direction;
}

void Light::setAttenuation(vec3 attenuation){
	this->attenuation = attenuation;
}

void Light::setSpotCosCutOff(float spotCosCutOff){
	this->spotCosCutOff = spotCosCutOff;
}

void Light::addPosition(vec3 position) {
	this->position += position;
}
