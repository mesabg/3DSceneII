#pragma once
#ifndef __STAGE_H__
#define __STAGE_H__

#include <RenderInterface.h>
#include <Reader.h>
#include <SkyBox.h>
#include <Light.h>
#include <Camera.h>
#include <Projection.h>
#include <Player.h>
#include <ModelCollection.h>
#include <FrameBuffer.h>

extern unsigned int amountOfEntities;
extern unsigned int amountOfLights;
extern vec2 getDisplaySize();

class Stage : public RenderColleague
{
private:
	//-- Singleton
	static Stage* uniqueStage;

	//-- Local Variables
	SkyBox* skyBox;
	Light* light;
	Camera* camera;
	Projection* projection;
	vector<Model*> entities, lightModels;
	ModelCollection *modelCollection, *lightCollection;
	map<string, CGLSLProgram*> *illuminationPrograms;
	Player* player;
	MousePicker* mousePicker;
	float width;
	float height;
	float* selectedModel;
	float* selectedLight;
	GLuint idTex, planeVAO, planeVBO;
	CGLSLProgram texture_program;
	glm::mat4 modelo, vista, proyeccion;
	GLuint fboId, rboId;
	GLuint textureId;
	bool isDonePrint = false;

	//-- Button Click variables
	bool clicked;
	int xPos, yPos;
	int xPosFirst, yPosFirst;

	//-- Shader ID
	GLuint shader_id, shader_id2;
	GLuint shadowMapId;

	//-- Uniforms IDs
	vector<GLint> *ID;

	//-- Frame Buffer Object to build dynamic MipMaps
	FrameBuffer* frameBufferObject;

	//-- Functions
	void switchFace(Camera* cam, const int index);

	Stage(RenderController* renderController);
	~Stage();
	void backRender(Camera* cam, Projection* proj);
	
public:
	void frontRender();
	/*Get Instance*/
	static Stage* Instance(RenderController* renderController);
	static void Destroy();

	//-- Getters
	Projection* getProjection();
	Model* getSelectedModel();
	Model* getSelectedLight();
	float* getSelectedModelIndex();
	float* getSelectedLightIndex();

	//-- 
	void initGLSLPrograms();

	/*Get message*/
	void Notify(string message, void* data);

	//-- Build Dynamic CubeMap
	void buildDynamicCubeMap(const int entityID);

	//-- Build Shadow Map
	void buildShadowMap();
	void drawShadowMap();

	/*Functions*/
	void render();
};

#endif