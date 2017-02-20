#include <ModelCollection.h>

ModelCollection::ModelCollection(
	vector<Routes*> routes, 
	vector<Transformation*> transformations, 
	vector<Light*> lights, 
	vector<MaterialProperties*> materialProperties){

	for (int i = 0; i < (int)routes.size(); i++) {
		this->entities.push_back(new Reader(routes[i]));
		this->entities.back()->setTransformation(transformations[i]);
		this->entities.back()->setLight(lights[i]);
		this->lightSet.push_back(lights[i]);
		this->entities.back()->setMaterialProperties(materialProperties[i]);
	}
}

ModelCollection::~ModelCollection(){
	for (Model* model : this->entities)
		model->~Model();
}

void ModelCollection::render(Projection* projection, Camera* camera, vector<Light*>* lights, CGLSLProgram* shader){
	for (Model* model : this->entities) {
		model->setShader(shader);
		model->render(projection, camera, lights);
	}
}

void ModelCollection::initVBOs(){
	for (Model* model : this->entities)
		model->initGLDataBinding();
}

Model * ModelCollection::getEntity(const unsigned int index){
	return this->entities[index];
}

vector<Light*>* ModelCollection::getLightSet(){
	return &this->lightSet;
}
