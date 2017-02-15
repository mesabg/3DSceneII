#pragma once
#ifndef __READER_H_
#define __READER_H_

// -- Global Includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// -- Class Includes
#include <Model.h>

// -- Using Spaces
using std::cout;
using std::endl;

class Reader : public Model{
private:
	void processNode(aiNode* node, const aiScene* scene);
public:
	Reader(Routes* routes, Transformation* transformation, Light* light);
	~Reader();
};

#endif