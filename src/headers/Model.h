#pragma once
#ifndef __MODEL_H_
#define __MODEL_H_

/*Global Includes*/
#include <string>
#include <sstream>
#include <vector>

/*Class Includes*/
#include <BoundingBox.h>
#include <Transformation.h>
#include <Animation.h>
#include <Texture.h>
#include <Routes.h>
#include <Light.h>
#include <LightProperties.h>

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

	Routes* routes;

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
	LightProperties* lightProperties;
	float shininess;

	//-- Uniforms IDs
	vector<GLint> *ID;

	//-- Animation
	Animation* animation;

public:
	Model();
	Model(Routes* routes, Transformation* transformation, Light* light);
	~Model();
	void render(GLuint shader_id);

	//-- Getters
	vector<GLfloat> getGLVBO();
	Transformation* getTransformation();
	BoundingBox* getBoundingBox();
	Texture* getTexture();
	Light* getMaterialLight();
	LightProperties* getMaterialLightProperties();
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
	float getShininess();
	Animation* getAnimation();

	//-- Setters
	void setTransformation(Transformation* transformation);
	void setTexture(Texture* texture);
	void setAnimation(Animation* animation);

	//-- Inherit
	void Inherit(Model* model);

	//-- Functions
	void initGLDataBinding(int index);
	bool isPointed(vec3 ray);
	void roundIt();
};


//-- Functions
void split(const std::string &s, char delim, std::vector<std::string> &elems);
#endif
