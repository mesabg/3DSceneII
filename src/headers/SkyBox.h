#pragma once
#ifndef __SKYBOX_H__
#define __SKYBOX_H__

//-- Gloabal includes
#include <Texture.h>
#include <vector>

//-- Using spaces
using std::vector;
using std::string;

class SkyBox {
private:
	GLuint textureID;
public:
	SkyBox();
	SkyBox(vector<string> textureFiles);
	~SkyBox();

	void render();
};


#endif