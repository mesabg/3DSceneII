#pragma once
#ifndef __MODEL_COLLECTION_H__
#define __MODEL_COLLECTION_H__

//-- Global Includes
#include <string>
#include <vector>
#include <map>

//-- Class Includes
#include <Reader.h>

//-- Using Spaces
using std::string;
using std::vector;
using std::map;
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

//-- Externs
extern unsigned int amountOfEntities;
extern unsigned int amountOfLights;

class ModelCollection{
protected:
	vector<Model*> entities;
public:
	ModelCollection(
		vector<Routes*> routes, 
		vector<Transformation*> tranformations, 
		vector<Light*> lights, 
		vector<MaterialProperties*> materialProperties,
		vector<CGLSLProgram*> shaders);

	~ModelCollection();

	//-- Methods
	void render(Projection* projection, Camera* camera);
};

#endif