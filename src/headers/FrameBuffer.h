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

	const int REFRACTION_WIDTH = 1280;
	const int REFRACTION_HEIGHT = 720;

	GLint reflectionFrameBuffer;
	GLint reflectionTexture;
	GLint reflectionDepthBuffer;

	GLint refractionFrameBuffer;
	GLint refractionTexture;
	GLint refractionDepthTexture;

	void initialiseReflectionFrameBuffer();
	void initialiseRefractionFrameBuffer();
	void bindFrameBuffer(int frameBuffer, int width, int height);
	GLuint createFrameBuffer();
	GLuint createTextureAttachment(int width, int height);
	GLuint createDepthTextureAttachment(int width, int height);
	GLuint createDepthBufferAttachment(int width, int height);
public:
	FrameBuffer();
	~FrameBuffer();

	//-- Functions
	void cleanUp();
	void bindReflectionFrameBuffer();
	void bindRefractionFrameBuffer();
	void unbindCurrentFrameBuffer();
	GLint getReflectionTexture();
	GLint getRefractionTexture();
	GLint getRefractionDepthTexture();

};


#endif