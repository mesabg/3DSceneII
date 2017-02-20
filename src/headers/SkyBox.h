#pragma once
#ifndef __SKYBOX_H__
#define __SKYBOX_H__

//-- Gloabal includes
#include <Texture.h>
#include <CGLSLProgram.h>

#include <vector>
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>

//-- Using spaces
using std::vector;
using std::string;
using glm::mat4;

class SkyBox {
private:
	const float SIZE = 500.0f;

	//-- VBO
	GLuint textureID;
	vector<GLfloat> glVBO;
	GLfloat *glVAO;
	GLuint glVBO_dir;

	//-- VAO
	GLuint glVAO_dir;

	//-- Shader Program
	CGLSLProgram* shader;

	//-- Projection and view matrices
	mat4 *projection;
	mat4 *view;

	void generateVertexes();
	void initShaderProgram();
	void initVBO();
	void initTextures(vector<string> *textureFiles);
public:
	SkyBox();
	SkyBox(vector<string> textureFiles, mat4 *projection, mat4 *view);
	~SkyBox();

	void render();
};


#endif