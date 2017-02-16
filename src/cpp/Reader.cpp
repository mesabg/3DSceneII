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
/*
void Reader::processMaterial(aiMaterial * material){
	aiString material_name;
	material->Get(AI_MATKEY_NAME, material_name);
	//--if (material_name.length > 0)
		//--this->material->setName();

	int shadingModel;
	material->Get(AI_MATKEY_SHADING_MODEL, shadingModel);

	if (shadingModel != aiShadingMode_Phong && shadingModel != aiShadingMode_Blinn && shadingModel != aiShadingMode_CookTorrance && shadingModel != aiShadingMode_OrenNayar){
		cout << "This mesh's shading model is not implemented in this loader, setting to default material\n";
		//-- this->material->setName("DefaultMaterial");
	}else{
		aiColor4D ambient(0.0f, 0.0f, 0.0f, 1.0f);
		aiColor4D diffuse(0.0f, 0.0f, 0.0f, 1.0f);
		aiColor4D specular(0.0f, 0.0f, 0.0f, 1.0f);
		float shininess = 0.0;

		material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
		material->Get(AI_MATKEY_COLOR_SPECULAR, specular);
		material->Get(AI_MATKEY_SHININESS, shininess);

		//-- Set material properties

		mater->Ambient = QVector3D(amb.r, amb.g, amb.b);
		mater->Diffuse = QVector3D(dif.r, dif.g, dif.b);
		mater->Specular = QVector3D(spec.r, spec.g, spec.b);
		mater->Shininess = shine;
		
		mater->Ambient *= .2;
		if (mater->Shininess == 0.0)
			mater->Shininess = 30;
	}
}

void Reader::processMesh(aiMesh * mesh){
	newMesh->name = mesh->mName.length != 0 ? mesh->mName.C_Str() : "";
	newMesh->indexOffset = m_indices.size();
	unsigned int indexCountBefore = m_indices.size();
	int vertindexoffset = m_vertices.size() / 3;

	//-- Get Vertices
	if (mesh->mNumVertices > 0)
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i){
			aiVector3D &vec = mesh->mVertices[i];
			m_vertices.push_back(vec.x);
			m_vertices.push_back(vec.y);
			m_vertices.push_back(vec.z);
		}

	//-- Get Normals
	if (mesh->HasNormals())
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i){
			aiVector3D &vec = mesh->mNormals[i];
			m_normals.push_back(vec.x);
			m_normals.push_back(vec.y);
			m_normals.push_back(vec.z);
		}

	//-- Get mesh indexes
	for (unsigned int t = 0; t < mesh->mNumFaces; ++t){
		aiFace* face = &mesh->mFaces[t];
		if (face->mNumIndices != 3){
			cout << "Warning: Mesh face with not exactly 3 indices, ignoring this primitive.\n";
			continue;
		}

		m_indices.push_back(face->mIndices[0] + vertindexoffset);
		m_indices.push_back(face->mIndices[1] + vertindexoffset);
		m_indices.push_back(face->mIndices[2] + vertindexoffset);
	}

	newMesh->indexCount = m_indices.size() - indexCountBefore;
	newMesh->material = m_materials.at(mesh->mMaterialIndex);
}

void Reader::processNode(const aiScene * scene, aiNode * node){
	newNode.name = node->mName.length != 0 ? node->mName.C_Str() : "";

	newNode.transformation = QMatrix4x4(node->mTransformation[0]);

	newNode.meshes.resize(node->mNumMeshes);
	for (uint imesh = 0; imesh < node->mNumMeshes; ++imesh)
	{
		QSharedPointer<Mesh> mesh = m_meshes[node->mMeshes[imesh]];
		newNode.meshes[imesh] = mesh;
	}

	for (uint ich = 0; ich < node->mNumChildren; ++ich)
	{
		newNode.nodes.push_back(Node());
		processNode(scene, node->mChildren[ich], parentNode, newNode.nodes[ich]);
	}
}

void Reader::readMaterials(const aiScene *scene){
	if (scene->HasMaterials())
		for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
			processMaterial(scene->mMaterials[i]);
}

void Reader::readMeshes(const aiScene * scene){
	if (scene->HasMeshes())
		for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
			processMesh(scene->mMeshes[i]);
	else cout << "Error: No meshes found\n";
}

void Reader::readNodes(const aiScene * scene){
	if (scene->mRootNode != NULL){
		Node *rootNode = new Node;
		processNode(scene, scene->mRootNode, 0, *rootNode);
		m_rootNode.reset(rootNode);
	}
	else cout << "Error loading model\n";
}
*/
Reader::Reader(Routes* routes) :Model(routes) {
	Assimp::Importer importer;
	static const aiScene *scene = importer.ReadFile(routes->model.c_str(), 
		aiProcess_Triangulate | 
		aiProcess_FlipUVs |
		aiProcess_GenSmoothNormals |
		aiProcess_CalcTangentSpace |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
	);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		exit(0);
	}

	//-- 
	/*this->readMaterials(scene);
	this->readMeshes(scene);
	this->readNodes(scene);*/



	this->processNode(scene->mRootNode, scene);
	this->roundIt();
	this->boundingBox->setBorder(minVec, maxVec);
}

Reader::~Reader() {

}