#include <Light.h>

Light::Light() {
	this->position = vec3(0.0f, 0.0f, 0.0f);
	this->ambient = vec3(1.0f, 1.0f, 1.0f);
	this->diffuse = vec3(1.0f, 1.0f, 1.0f);
	this->specular = vec3(1.0f, 1.0f, 1.0f);
	this->direction = vec3(0.0f, 0.0f, 0.0f);
	this->attenuation = vec3(0.9f, 0.8f, 0.7f);
	this->isActive = true;
	this->type = vec3(true, false, false);
	this->spotExp = 0.01f;
	this->spotCosCutOff = 0.8f;
	this->spotCosOuterCutOff = 0.8f;
}

Light::Light(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular) {
	this->position = position;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->direction = vec3(0.50f, 0.10f, -0.40f);
	this->attenuation = vec3(0.9f, 0.8f, 0.7f);
	this->isActive = true;
	this->type = vec3(true, false, false);
	this->spotExp = 0.01f;
	this->spotCosCutOff = 0.8f;
	this->spotCosOuterCutOff = 0.8f;
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

float * Light::getSpotCosOuterCutOff(){
	return &this->spotCosOuterCutOff;
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

void Light::setSpotCosOuterCutOff(float spotCosOuterCutOff){
	this->spotCosOuterCutOff = spotCosOuterCutOff;
}

void Light::addPosition(vec3 position) {
	this->position += position;
}

void Light::bind(CGLSLProgram * shader, bool mode, int index){
	if (!mode) {
		//-- Bind it as a global light
		if (this->isActive) {
			//-- Light is on
			glUniform3f(
				glGetUniformLocation(shader->getProgramID(), ("u_light[" + std::to_string(index) + "].ambient").c_str()),
				(GLfloat)this->ambient.r,
				(GLfloat)this->ambient.g,
				(GLfloat)this->ambient.b);

			glUniform3f(
				glGetUniformLocation(shader->getProgramID(), ("u_light[" + std::to_string(index) + "].diffuse").c_str()),
				(GLfloat)this->diffuse.r,
				(GLfloat)this->diffuse.g,
				(GLfloat)this->diffuse.b);

			glUniform3f(
				glGetUniformLocation(shader->getProgramID(), ("u_light[" + std::to_string(index) + "].specular").c_str()),
				(GLfloat)this->specular.r,
				(GLfloat)this->specular.g,
				(GLfloat)this->specular.b);
		}
		else {
			//-- Light is off
			glUniform3f(
				glGetUniformLocation(shader->getProgramID(), ("u_light[" + std::to_string(index) + "].ambient").c_str()),
				(GLfloat)0.0f,
				(GLfloat)0.0f,
				(GLfloat)0.0f);

			glUniform3f(
				glGetUniformLocation(shader->getProgramID(), ("u_light[" + std::to_string(index) + "].diffuse").c_str()),
				(GLfloat)0.0f,
				(GLfloat)0.0f,
				(GLfloat)0.0f);

			glUniform3f(
				glGetUniformLocation(shader->getProgramID(), ("u_light[" + std::to_string(index) + "].specular").c_str()),
				(GLfloat)0.0f,
				(GLfloat)0.0f,
				(GLfloat)0.0f);
		}
		
		glUniform3f(
			glGetUniformLocation(shader->getProgramID(), ("u_light[" + std::to_string(index) + "].position").c_str()),
			(GLfloat)this->position.x,
			(GLfloat)this->position.y,
			(GLfloat)this->position.z);

		glUniform3f(
			glGetUniformLocation(shader->getProgramID(), ("u_light[" + std::to_string(index) + "].type").c_str()),
			(GLfloat)this->type.x,
			(GLfloat)this->type.y,
			(GLfloat)this->type.z);

		//-- Bind Attenuation Properties
		glUniform1f(
			glGetUniformLocation(shader->getProgramID(), ("u_attenuation[" + std::to_string(index) + "].constant").c_str()),
			(GLfloat)this->attenuation.x);

		glUniform1f(
			glGetUniformLocation(shader->getProgramID(), ("u_attenuation[" + std::to_string(index) + "].linear").c_str()),
			(GLfloat)this->attenuation.y);

		glUniform1f(glGetUniformLocation(shader->getProgramID(), ("u_attenuation[" + std::to_string(index) + "].quadratic").c_str()),
			(GLfloat)this->attenuation.z);

		glUniform3f(glGetUniformLocation(shader->getProgramID(), ("u_attenuation[" + std::to_string(index) + "].direction").c_str()),
			(GLfloat)this->direction.x,
			(GLfloat)this->direction.y,
			(GLfloat)this->direction.z);

		glUniform1f(glGetUniformLocation(shader->getProgramID(), ("u_attenuation[" + std::to_string(index) + "].exponent").c_str()),
			(GLfloat)this->spotExp);

		glUniform1f(glGetUniformLocation(shader->getProgramID(), ("u_attenuation[" + std::to_string(index) + "].inner_cosine").c_str()),
			(GLfloat)this->spotCosCutOff);

		glUniform1f(glGetUniformLocation(shader->getProgramID(), ("u_attenuation[" + std::to_string(index) + "].outer_cosine").c_str()),
			(GLfloat)this->spotCosOuterCutOff);
	}
	else {
		//-- Bind it as a material light
		glUniform3f(
			glGetUniformLocation(shader->getProgramID(), "u_material.ambient"),
			(GLfloat)this->ambient.r,
			(GLfloat)this->ambient.g,
			(GLfloat)this->ambient.b);

		glUniform3f(
			glGetUniformLocation(shader->getProgramID(), "u_material.diffuse"),
			(GLfloat)this->diffuse.r,
			(GLfloat)this->diffuse.g,
			(GLfloat)this->diffuse.b);

		glUniform3f(glGetUniformLocation(shader->getProgramID(), "u_material.specular"),
			(GLfloat)this->specular.r,
			(GLfloat)this->specular.g,
			(GLfloat)this->specular.b);
	}
}
