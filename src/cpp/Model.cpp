#include <Model.h>
#include <iostream>

Model::Model() {
	//this->glVBO = (GLfloat*)malloc(sizeof(GLfloat));

	/*Init Uniforms ID*/
	this->ID = new vector<GLint>(8, 0);

	/*Init Tranformation*/
	this->transformation = new Transformation();

	/*Init Material Colors*/
	this->material = new Light();
	this->lightProperties = new LightProperties(0.5f, 0.5f, 0.5f, 0.5f);
	this->shininess = 4.0f;
}

Model::Model(Routes* routes, Transformation* transformation, Light* light) {
	//-- Init data structures
	this->routes = routes;

	//-- Init Uniforms ID
	this->ID = new vector<GLint>(12, 0);

	//-- Init Tranformation
	this->transformation = transformation;

	//-- Init Bounding Box
	this->boundingBox = new BoundingBox();

	//-- Init Material Colors
	this->material = light;
		//new Light(vec3(0.0f, 0.0f, 0.0f), vec3(0.5f, 0.3f, 0.2f), vec3(0.2f, 0.1f, 0.2f), vec3(0.25f, 0.0f, 0.2f));
	this->lightProperties = new LightProperties(0.1f, 100.0f, 0.1f, 0.2f);
	this->shininess = 10.0f;
	this->shading = vec4(true, false, false, false);
	this->lightningType = vec2(true, false);
	this->animation = NULL;
}

Model::~Model() {

}

void Model::render(GLuint shader_id) {

	//-- Animate
	if (this->animation) this->animation->animate();

	//-- Move Bounding Box
	this->boundingBox->move(this->transformation->getTransformMatrix());


	//-- Bind Uniforms
	this->ID->at(0) = glGetUniformLocation(shader_id, "u_matAmbientReflectances");
	glUniform3f(this->ID->at(0), this->material->getAmbient()->r, this->material->getAmbient()->g, this->material->getAmbient()->b);

	this->ID->at(1) = glGetUniformLocation(shader_id, "u_matDiffuseReflectances");
	glUniform3f(this->ID->at(1), this->material->getDiffuse()->r, this->material->getDiffuse()->g, this->material->getDiffuse()->b);

	this->ID->at(2) = glGetUniformLocation(shader_id, "u_matSpecularReflectances");
	glUniform3f(this->ID->at(2), this->material->getSpecular()->r, this->material->getSpecular()->g, this->material->getSpecular()->b);

	this->ID->at(3) = glGetUniformLocation(shader_id, "u_matShininess");
	glUniform1f(this->ID->at(3), this->shininess);

	this->ID->at(4) = glGetUniformLocation(shader_id, "u_shininess");
	glUniform1f(this->ID->at(4), *(this->lightProperties->getShininess()));

	this->ID->at(5) = glGetUniformLocation(shader_id, "u_roughness");
	glUniform1f(this->ID->at(5), *(this->lightProperties->getRoughness()));

	this->ID->at(6) = glGetUniformLocation(shader_id, "u_fresnel");
	glUniform1f(this->ID->at(6), *(this->lightProperties->getFresnel()));

	this->ID->at(7) = glGetUniformLocation(shader_id, "u_albedo");
	glUniform1f(this->ID->at(7), *(this->lightProperties->getAlbedo()));

	this->ID->at(8) = glGetUniformLocation(shader_id, "u_textureIsActive");
	glUniform1i(this->ID->at(8), (GLint)*(this->texture->isActive()));

	this->ID->at(9) = glGetUniformLocation(shader_id, "u_shadingBitMap");
	glUniform4f(this->ID->at(9), this->shading.x, this->shading.y, this->shading.z, this->shading.w);

	this->ID->at(10) = glGetUniformLocation(shader_id, "u_modelMat");
	glUniformMatrix4fv(this->ID->at(10), 1, GL_FALSE, &(this->transformation->getTransformMatrix())[0][0]);

	// -- Binding Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture->getID());
	glUniform1i(glGetUniformLocation(shader_id, "u_texture"), 0);

	// -- VBO Data
	glBindBuffer(GL_ARRAY_BUFFER, this->glVBO_dir);
		// -- Vertex 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), 0);
		// -- Normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
		// -- Texture Coord
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	// -- Drawing
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->glVBO_indexes_dir);

	glDrawElements(GL_TRIANGLES, this->glVBO_indexes_size, GL_UNSIGNED_INT, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);
}

vector<GLfloat> Model::getGLVBO() {
	return this->glVBO;
}

Transformation * Model::getTransformation() {
	return this->transformation;
}

BoundingBox * Model::getBoundingBox() {
	return this->boundingBox;
}

Texture * Model::getTexture() {
	return this->texture;
}

Light * Model::getMaterialLight(){
	return this->material;
}

LightProperties * Model::getMaterialLightProperties(){
	return this->lightProperties;
}

GLuint Model::getGLVBO_dir() {
	return this->glVBO_dir;
}

GLuint Model::getGLVBO_indexes_dir() {
	return this->glVBO_indexes_dir;
}

vector<GLuint> Model::getGLVBO_indexes() {
	return this->glVBO_indexes;
}

GLuint Model::getGLVBO_indexes_size() {
	return this->glVBO_indexes_size;
}

Routes * Model::getRoutes() {
	return this->routes;
}

tvec4<bool> * Model::getShadingVectorBitMap(){
	return &this->shading;
}

bool * Model::getShadingVectorBitMapXCoord_phong(){
	return &(this->shading.x);
}

bool * Model::getShadingVectorBitMapYCoord_blinn() {
	return &(this->shading.y);
}

bool * Model::getShadingVectorBitMapZCoord_oren() {
	return &(this->shading.z);
}

bool * Model::getShadingVectorBitMapWCoord_cook() {
	return &(this->shading.w);
}

tvec2<bool>* Model::getLightningType(){
	return &this->lightningType;
}

bool * Model::getLightningTypeX_frag(){
	return &(this->lightningType.x);
}

bool * Model::getLightningTypeY_vert() {
	return &(this->lightningType.y);
}

float Model::getShininess() {
	return this->shininess;
}

Animation * Model::getAnimation(){
	return this->animation;
}

void Model::setTransformation(Transformation * transformation) {
	this->transformation = transformation;
}

void Model::setTexture(Texture * texture) {
	this->texture = texture;
}

void Model::setAnimation(Animation* animation){
	this->animation = animation;
}

void Model::Inherit(Model * model) {
	/*Copy All the values*/
	this->routes = model->getRoutes();
	this->glVBO = model->getGLVBO();
	this->transformation = model->getTransformation();
	this->texture = model->getTexture();
	this->boundingBox = model->getBoundingBox();
	this->glVBO_dir = model->getGLVBO_dir();
	this->glVBO_indexes_dir = model->getGLVBO_indexes_dir();
	this->glVBO_indexes = model->getGLVBO_indexes();
	this->glVBO_indexes_size = model->getGLVBO_indexes_size();
	this->shininess = model->getShininess();
}

void Model::initGLDataBinding(int index) {
	this->glVBO_indexes_size = this->glVBO_indexes.size();

	// -- VBO Data
	glGenBuffers(1, &(this->glVBO_dir));
	glBindBuffer(GL_ARRAY_BUFFER, this->glVBO_dir);
	glBufferData(GL_ARRAY_BUFFER, (this->glVBO.size()) * sizeof(GLfloat), &(this->glVBO[0]), GL_STATIC_DRAW);
		// -- Vertexes
		glEnableVertexAttribArray(0);

		// -- Normals
		glEnableVertexAttribArray(1);

		// -- Texture Coord
		glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// -- Indexes Data
	glGenBuffers(1, &(this->glVBO_indexes_dir));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->glVBO_indexes_dir);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->glVBO_indexes.size() * sizeof(GLuint), &(this->glVBO_indexes[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//-- Read Texture
	this->texture = new Texture(this->routes->texture);

	//-- Enable Backface Culling and Z Buffer
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	this->glVBO.~vector();
	this->glVBO_indexes.~vector();
}

bool Model::isPointed(vec3 ray){
	vec3 parametricForm = vec3();
	//-- return
	//this->boundingBox->checkIntersecion();
	return false;
}

void Model::roundIt(){
	float maxi = glm::max(this->maxVec.x, glm::max(this->maxVec.y, this->maxVec.z));

	vec3 centro;
	centro.x = (this->maxVec.x + this->minVec.x) / 2.0f;
	centro.y = (this->maxVec.y + this->minVec.y) / 2.0f;
	centro.z = (this->maxVec.z + this->minVec.z) / 2.0f;

	for (int i = 0; i < (int)this->glVBO.size(); i+=9){
		this->glVBO[i] = (this->glVBO[i] - centro.x) / maxi;
		this->glVBO[i+1] = (this->glVBO[i+1] - centro.y) / maxi;
		this->glVBO[i+2] = (this->glVBO[i+2] - centro.z) / maxi;
	}

	this->maxVec.x = (this->maxVec.x - centro.x) / 2.0f;
	this->maxVec.y = (this->maxVec.y - centro.y) / 2.0f;
	this->maxVec.z = (this->maxVec.z - centro.z) / 2.0f;

	this->minVec.x = (this->minVec.x - centro.x) / 2.0f;
	this->minVec.y = (this->minVec.y - centro.y) / 2.0f;
	this->minVec.z = (this->minVec.z - centro.z) / 2.0f;
}

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}
