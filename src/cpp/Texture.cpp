#include <Texture.h>
#include <iostream>

void Texture::loadDeafultCubeMap(){
	glGenTextures(1, &this->cubemap_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemap_texture);
	for (int i = 0; i < 6; i++)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, 128, 128, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

Texture::Texture(string route) {
	this->route = route;
	this->m_texture = loadTexture(route.c_str());
	this->loadDeafultCubeMap();
	this->active = true;
}

GLuint Texture::loadTexture(GLchar const *path) {
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;
}

void Texture::setActive(bool active){
	this->active = active;
}

void Texture::setCubeMapTexture(GLuint texture){
	this->cubemap_texture = texture;
}

bool * Texture::isActive(){
	return &this->active;
}

GLuint Texture::getCubeMapTexture(){
	return this->cubemap_texture;
}

Texture::~Texture() {
	this->route.~basic_string();
}

GLuint Texture::getID() {
	return this->m_texture;
}