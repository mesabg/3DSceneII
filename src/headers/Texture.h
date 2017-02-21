#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <glew\glew.h>
#include <SOIL\SOIL.h>
#include <iostream>
#include <string>
#include <stdio.h>

using std::string;

class Texture {
private:
	string route;
	GLuint m_texture;
	GLuint cubemap_texture;
	int num_texture;
	bool active;
	bool cubeMapActive;

	void loadDeafultCubeMap();
public:
	Texture(string route);
	~Texture();
	GLuint getID();
	GLuint loadTexture(GLchar const *path);

	//-- Setters
	void setActive(bool active);

	//-- Getter
	bool* isActive();
	GLuint getCubeMapTexture();
};

#endif

