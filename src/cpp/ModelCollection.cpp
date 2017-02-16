#include <ModelCollection.h>

ModelCollection::ModelCollection(
	vector<Routes*> routes, 
	vector<Transformation*> transformations, 
	vector<Light*> lights, 
	vector<MaterialProperties*> materialProperties,
	vector<CGLSLProgram*> shaders){

	for (unsigned int i = 0; i < amountOfEntities; i++) {
		this->entities.push_back(new Reader(routes[i]));
		this->entities.back()->setTransformation(transformations[i]);
		this->entities.back()->setLight(lights[i]);
		this->entities.back()->setMaterialProperties(materialProperties[i]);
		this->entities.back()->setShader(shaders[i]);
	}
}

ModelCollection::~ModelCollection(){
	for (Model* model : this->entities)
		model->~Model();
}

void ModelCollection::render(Projection* projection, Camera* camera){
	for (Model* model : this->entities)
		model->render(projection, camera);
}
