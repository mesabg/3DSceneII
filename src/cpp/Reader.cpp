#include <Reader.h>
#include <iostream>

void Reader::processNode(aiNode * node, const aiScene * scene){
	for (GLuint i = 0; i < node->mNumMeshes; i++){
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		for (GLuint i = 0; i < mesh->mNumVertices; i++) {
			if (i == 0) {
				minVec.x = maxVec.x = mesh->mVertices[i].x;
				minVec.y = maxVec.y = mesh->mVertices[i].y;
				minVec.z = maxVec.z = mesh->mVertices[i].z;
			} else {
				// -- Min
				minVec.x = mesh->mVertices[i].x < minVec.x ? mesh->mVertices[i].x : minVec.x;
				minVec.y = mesh->mVertices[i].y < minVec.y ? mesh->mVertices[i].y : minVec.y;
				minVec.z = mesh->mVertices[i].z < minVec.z ? mesh->mVertices[i].z : minVec.z;

				// -- Max
				maxVec.x = mesh->mVertices[i].x > maxVec.x ? mesh->mVertices[i].x : maxVec.x;
				maxVec.y = mesh->mVertices[i].y > maxVec.y ? mesh->mVertices[i].y : maxVec.y;
				maxVec.z = mesh->mVertices[i].z > maxVec.z ? mesh->mVertices[i].z : maxVec.z;
			}
			this->glVBO.push_back(mesh->mVertices[i].x);
			this->glVBO.push_back(mesh->mVertices[i].y);
			this->glVBO.push_back(mesh->mVertices[i].z);
			this->glVBO.push_back(mesh->mNormals[i].x);
			this->glVBO.push_back(mesh->mNormals[i].y);
			this->glVBO.push_back(mesh->mNormals[i].z);
			if (mesh->mTextureCoords[0]) {
				this->glVBO.push_back(mesh->mTextureCoords[0][i].x);
				this->glVBO.push_back(mesh->mTextureCoords[0][i].y);
				if (mesh->mTextureCoords[0][i].z) this->glVBO.push_back(mesh->mTextureCoords[0][i].z);
				else this->glVBO.push_back(0.0f);
			}
		}
		for (GLuint i = 0; i < mesh->mNumFaces; i++){
			aiFace face = mesh->mFaces[i];
			for (GLuint j = 0; j < face.mNumIndices; j++)
				this->glVBO_indexes.push_back(face.mIndices[j]);
		}
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
		this->processNode(node->mChildren[i], scene);
}

Reader::Reader(Routes* routes, Transformation* transformation, Light* light) :Model(routes, transformation, light) {
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(routes->model.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}

	/*Process ASSIMP's root node recursively*/
	this->processNode(scene->mRootNode, scene);
	this->roundIt();
	this->boundingBox->setBorder(minVec, maxVec);
}

Reader::~Reader() {

}