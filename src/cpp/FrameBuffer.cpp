#include <FrameBuffer.h>

FrameBuffer::FrameBuffer(){
	initialiseReflectionFrameBuffer();
	initialiseRefractionFrameBuffer();
	initialiseCubeMapFrameBuffer();
}

FrameBuffer::~FrameBuffer(){

}

void FrameBuffer::cleanUp(){
	/*glDeleteFramebuffers(reflectionFrameBuffer);
	glDeleteTextures(reflectionTexture);
	glDeleteRenderbuffers(reflectionDepthBuffer);
	glDeleteFramebuffers(refractionFrameBuffer);
	glDeleteTextures(refractionTexture);
	glDeleteTextures(refractionDepthTexture);*/
}

void FrameBuffer::bindReflectionFrameBuffer(){
	bindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void FrameBuffer::bindCubeFrameBuffer(){
	bindFrameBuffer(cubeMapFrameBuffer, CUBEMAP_WIDTH, CUBEMAP_HEIGHT);
}

void FrameBuffer::bindCubeMapTexture(GLuint textureID, const int index){
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, textureID, 0);
}

void FrameBuffer::bindRefractionFrameBuffer(){
	bindFrameBuffer(refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void FrameBuffer::unbindCurrentFrameBuffer(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1440, 900);
}

GLint FrameBuffer::getReflectionTexture(){
	return this->reflectionTexture;
}

GLint FrameBuffer::getRefractionTexture(){
	return this->refractionTexture;
}

GLint FrameBuffer::getRefractionDepthTexture(){
	return this->refractionDepthTexture;
}

void FrameBuffer::initialiseReflectionFrameBuffer(){
	reflectionFrameBuffer = createFrameBuffer();
	reflectionTexture = createTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	unbindCurrentFrameBuffer();
}

void FrameBuffer::initialiseRefractionFrameBuffer(){
	refractionFrameBuffer = createFrameBuffer();
	refractionTexture = createTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	unbindCurrentFrameBuffer();
}

void FrameBuffer::initialiseCubeMapFrameBuffer(){
	cubeMapFrameBuffer = createFrameBuffer();
	cubeMapDepthBuffer = createDepthBufferAttachment(CUBEMAP_WIDTH, CUBEMAP_HEIGHT);
	unbindCurrentFrameBuffer();
}

void FrameBuffer::bindFrameBuffer(int frameBuffer, int width, int height){
	glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, width, height);
}

GLuint FrameBuffer::createFrameBuffer(){
	GLuint frameBuffer;
	glGenFramebuffers(1, &frameBuffer);
	//generate name for frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	//create the framebuffer
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	//indicate that we will always render to color attachment 0
	return frameBuffer;
}

GLuint FrameBuffer::createTextureAttachment(int width, int height){
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		texture, 0);
	return texture;
}

GLuint FrameBuffer::createCubeTextureAttachment(int width, int height, GLuint textureID){
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height,
		0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		texture, 0);
	return texture;
}

GLuint FrameBuffer::createDepthTextureAttachment(int width, int height){
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height,
		0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		texture, 0);
	return texture;
}

GLuint FrameBuffer::createDepthBufferAttachment(int width, int height){
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width,
		height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER, depthBuffer);
	return depthBuffer;
}
