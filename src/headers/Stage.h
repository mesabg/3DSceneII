#pragma once
#ifndef __STAGE_H__
#define __STAGE_H__

#include <RenderInterface.h>
#include <Reader.h>
#include <SkyBox.h>
#include <Light.h>
#include <Camera.h>
#include <Projection.h>

extern unsigned int amountOfEntities;
extern unsigned int amountOfLights;

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
	Player* player;
	MousePicker* mousePicker;
	float width;
	float height;
	float* selectedModel;
	float* selectedLight;

	//-- Shader ID
	GLuint shader_id, shader_id2;

	//-- Uniforms IDs
	vector<GLint> *ID;

	//-- Functions
	Stage(RenderController* renderController);
	~Stage();

public:

	/*Get Instance*/
	static Stage* Instance(RenderController* renderController);
	static void Destroy();

	//-- Getters
	Projection* getProjection();
	Model* getSelectedModel();
	Model* getSelectedLight();
	float* getSelectedModelIndex();
	float* getSelectedLightIndex();

	/*Get message*/
	void Notify(string message, void* data);

	/*Functions*/
	void render();
};

#endif