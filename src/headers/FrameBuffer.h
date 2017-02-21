#pragma once
#ifndef __FRAME_BUFFER_H__
#define __FRAME_BUFFER_H__

//-- Gloabal includes
#include <Texture.h>

#include <vector>
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>

//-- Using spaces
using std::vector;
using std::string;
using glm::mat4;

class FrameBuffer {
private:
	const int REFLECTION_WIDTH = 320;
	const int REFLECTION_HEIGHT = 180;

	const int CUBEMAP_WIDTH = 320;
	const int CUBEMAP_HEIGHT = 320;

	const int REFRACTION_WIDTH = 1280;
	const int REFRACTION_HEIGHT = 720;

	GLuint reflectionFrameBuffer;
	GLuint reflectionTexture;
	GLuint reflectionDepthBuffer;

	GLuint cubeMapFrameBuffer;
	GLuint cubeMapTexture;
	GLuint cubeMapDepthBuffer;

	GLuint refractionFrameBuffer;
	GLuint refractionTexture;
	GLuint refractionDepthTexture;

	void initialiseReflectionFrameBuffer();
	void initialiseRefractionFrameBuffer();
	void initialiseCubeMapFrameBuffer();

	void bindFrameBuffer(int frameBuffer, int width, int height);
	GLuint createFrameBuffer();
	GLuint createTextureAttachment(int width, int height);
	GLuint createCubeTextureAttachment(int width, int height, GLuint textureID);
	GLuint createDepthTextureAttachment(int width, int height);
	GLuint createDepthBufferAttachment(int width, int height);
public:
	FrameBuffer();
	~FrameBuffer();

	//-- Functions
	void cleanUp();
	void bindReflectionFrameBuffer();
	void bindCubeFrameBuffer();
	void bindCubeMapTexture(GLuint textureID, const int index);
	void bindRefractionFrameBuffer();
	void unbindCurrentFrameBuffer();
	GLint getReflectionTexture();
	GLint getRefractionTexture();
	GLint getRefractionDepthTexture();

};


#endif