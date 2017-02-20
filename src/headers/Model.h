#pragma once
#ifndef __MODEL_H_
#define __MODEL_H_

//-- Global Includes
#include <string>
#include <sstream>
#include <vector>

//-- Class Includes
#include <CGLSLProgram.h>

#include <Camera.h>
#include <Projection.h>
#include <BoundingBox.h>
#include <Transformation.h>
#include <Animation.h>
#include <Texture.h>
#include <Routes.h>
#include <Light.h>
#include <MaterialProperties.h>

using glm::vec2;
using glm::tvec2;
using glm::vec3;
using glm::vec4;
using glm::tvec4;
using std::string;
using std::vector;

class Model {
protected:
	//-- Array to VBO
	vector<GLfloat> glVBO;
	GLuint glVBO_dir;
	GLuint glVBO_indexes_dir;
	vector<GLuint> glVBO_indexes;
	GLuint glVBO_indexes_size;
	vec3 minVec, maxVec;

	//-- Routes
	Routes* routes;

	//-- Shading Program
	CGLSLProgram* shaderProgram;

	//-- Arrays to load a model
	vector<GLfloat*> vertexes;
	vector<GLfloat*> normal;
	vector<GLfloat*> texture_;
	GLfloat max, min;
	int vertexesLenght;

	//-- Structures
	Transformation* transformation;
	BoundingBox* boundingBox;
	Texture* texture;

	//-- Shader Active
	tvec4<bool> shading;
	tvec2<bool> lightningType;

	//-- Light material values
	Light* material;
	MaterialProperties* materialProperties;

	//-- Uniforms IDs
	vector<GLint> *ID;

	//-- Animation
	Animation* animation;

	//-- Some functions
	void bindData(Projection* projection, Camera* camera, vector<Light*> *globalLights);
	void drawElements();

public:
	Model();
	Model(Routes* routes);
	~Model();
	void render(Projection* projection, Camera* camera, vector<Light*> *globalLights);

	//-- Getters
	vector<GLfloat> getGLVBO();
	Transformation* getTransformation();
	BoundingBox* getBoundingBox();
	Texture* getTexture();
	Light* getMaterialLight();
	MaterialProperties* getMaterialProperties();
	GLuint getGLVBO_dir();
	GLuint getGLVBO_indexes_dir();
	vector<GLuint> getGLVBO_indexes();
	GLuint getGLVBO_indexes_size();
	Routes* getRoutes();
	tvec4<bool>* getShadingVectorBitMap();
	bool* getShadingVectorBitMapXCoord_phong();
	bool* getShadingVectorBitMapYCoord_blinn();
	bool* getShadingVectorBitMapZCoord_oren();
	bool* getShadingVectorBitMapWCoord_cook();
	tvec2<bool>* getLightningType();
	bool* getLightningTypeX_frag();
	bool* getLightningTypeY_vert();
	Animation* getAnimation();

	//-- Setters
	void setTransformation(Transformation* transformation);
	void setTexture(Texture* texture);
	void setAnimation(Animation* animation);
	void setMaterialProperties(MaterialProperties* materialProperties);
	void setLight(Light* light);
	void setShader(CGLSLProgram* shader);

	//-- Inherit
	void Inherit(Model* model);

	//-- Functions
	void initGLDataBinding();
	bool isPointed(vec3 ray);
	void roundIt();
};


//-- Functions
void split(const std::string &s, char delim, std::vector<std::string> &elems);
#endif
