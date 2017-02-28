#include <Model.h>
#include <iostream>

void Model::bindData(Projection* projection, Camera* camera, vector<Light*> *globalLights){
	//-- Bind Lights
	unsigned int i = 0;
	for (Light* light : *(globalLights)) {
		if (*(light->active())) {
			glUniform3f(
				glGetUniformLocation(this->shaderProgram->getProgramID(), ("u_light["+ std::to_string(i) +"].ambient").c_str()),
				light->getAmbient()->r, 
				light->getAmbient()->g, 
				light->getAmbient()->b);

			glUniform3f(
				glGetUniformLocation(this->shaderProgram->getProgramID(), ("u_light[" + std::to_string(i) + "].diffuse").c_str()),
				light->getDiffuse()->r, 
				light->getDiffuse()->g, 
				light->getDiffuse()->b);

			glUniform3f(glGetUniformLocation(this->shaderProgram->getProgramID(), ("u_light[" + std::to_string(i) + "].specular").c_str()),
				light->getSpecular()->r,
				light->getSpecular()->g,
				light->getSpecular()->b);
		}
		else {
			glUniform3f(
				glGetUniformLocation(this->shaderProgram->getProgramID(), ("u_light[" + std::to_string(i) + "].ambient").c_str()),
				0.0f,
				0.0f,
				0.0f);

			glUniform3f(
				glGetUniformLocation(this->shaderProgram->getProgramID(), ("u_light[" + std::to_string(i) + "].diffuse").c_str()),
				0.0f,
				0.0f,
				0.0f);

			glUniform3f(glGetUniformLocation(this->shaderProgram->getProgramID(), ("u_light[" + std::to_string(i) + "].specular").c_str()),
				0.0f,
				0.0f,
				0.0f);
		}

		glUniform3f(glGetUniformLocation(this->shaderProgram->getProgramID(), ("u_light[" + std::to_string(i) + "].type").c_str()),
			(GLfloat)light->getType()->x, 
			(GLfloat)light->getType()->y, 
			(GLfloat)light->getType()->z);

		glUniform3f(glGetUniformLocation(this->shaderProgram->getProgramID(), ("u_light[" + std::to_string(i) + "].position").c_str()),
			light->getPosition()->x, 
			light->getPosition()->y, 
			light->getPosition()->z);

		glUniform1f(glGetUniformLocation(this->shaderProgram->getProgramID(), ("u_light[" + std::to_string(i) + "].constant").c_str()),
			light->getAttenuation()->x);

		glUniform1f(glGetUniformLocation(this->shaderProgram->getProgramID(), ("u_light[" + std::to_string(i) + "].linear").c_str()),
			light->getAttenuation()->y);

		glUniform1f(glGetUniformLocation(this->shaderProgram->getProgramID(), ("u_light[" + std::to_string(i) + "].quadratic").c_str()),
			light->getAttenuation()->z);

		glUniform3f(glGetUniformLocation(this->shaderProgram->getProgramID(), ("u_light[" + std::to_string(i) + "].direction").c_str()),
			light->getDirection()->x,
			light->getDirection()->y,
			light->getDirection()->z);

		glUniform1f(glGetUniformLocation(this->shaderProgram->getProgramID(), ("u_light[" + std::to_string(i) + "].exponent").c_str()),
			*(light->getSpotExp()));

		glUniform1f(glGetUniformLocation(this->shaderProgram->getProgramID(), ("u_light[" + std::to_string(i) + "].cosCutOff").c_str()),
			*(light->getSpotCosCutOff()));
		i++;
	}

	//-- Bind General Attributes
	glUniform3f(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_camera_position"),
		camera->getPosition().x,
		camera->getPosition().y,
		camera->getPosition().z);

	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_view_matrix"), 1, GL_FALSE, &(camera->getMatrix())[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_projection_matrix"), 1, GL_FALSE, &(projection->getMatrix())[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_normal_matrix"), 1, GL_FALSE, &(glm::inverse(glm::transpose(camera->getMatrix())))[0][0]);

	//-- Bind Material Attributes
	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_model_matrix"), 1, GL_FALSE, &(this->transformation->getTransformMatrix())[0][0]);

	glUniform3f(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_material.ambient"),
		this->material->getAmbient()->r, 
		this->material->getAmbient()->g, 
		this->material->getAmbient()->b);

	glUniform3f(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_material.diffuse"),
		this->material->getDiffuse()->r,
		this->material->getDiffuse()->g,
		this->material->getDiffuse()->b);

	glUniform3f(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_material.specular"),
		this->material->getSpecular()->r,
		this->material->getSpecular()->g,
		this->material->getSpecular()->b);

	glUniform1f(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_material.shininess"),
		*(this->materialProperties->getShininess()));

	glUniform1f(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_material.roughness"),
		*(this->materialProperties->getRoughness()));

	glUniform1f(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_material.fresnel"),
		*(this->materialProperties->getFresnel()));

	glUniform1f(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_material.albedo"),
		*(this->materialProperties->getAlbedo()));

	//-- Something else
	if (this->texture)
		glUniform1i(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_textureIsActive"), 
			(GLint)*(this->texture->isActive()));

	glUniform4f(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_shadingBitMap"),
		this->shading.x,
		this->shading.y,
		this->shading.z,
		this->shading.w);

	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram->getProgramID(), "DepthBiasMVP"), 1, GL_FALSE, &(this->DepthBiasMVP)[0][0]);
}

void Model::drawElements(){
	// -- Binding Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture->getID());
	glUniform1i(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_texture"), 0);

	//-- Bind MipMap From the SkyBox if its necesary
	if (this->isReflected) {
		//-- Calculate dynamic MipMapping
		//this->skyboxReference->enable(this->shaderProgram->getProgramID(), 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture->getCubeMapTexture());
		glUniform1i(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_cube_map"), 1);
	}

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, this->ShadowMapId);
	glUniform1i(glGetUniformLocation(this->shaderProgram->getProgramID(), "shadowMap"), 2);

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

Model::Model() {
	/*Init Uniforms ID*/
	this->ID = new vector<GLint>(8, 0);

	/*Init Tranformation*/
	this->transformation = new Transformation();

	/*Init Material Colors*/
	this->material = new Light();
	this->materialProperties = new MaterialProperties(0.5f, 0.5f, 0.5f, 0.5f);
}

Model::Model(Routes* routes) {
	//-- Init data structures
	this->routes = routes;

	//-- Init Uniforms ID
	this->ID = new vector<GLint>(12, 0);

	//-- Init Tranformation
	this->transformation = NULL;

	//-- Init Bounding Box
	this->boundingBox = new BoundingBox();

	//-- Init Material Colors
	this->material = NULL;

	this->skyboxReference = NULL;

	this->materialProperties = NULL;
	this->isReflected = false;
	this->shading = vec4(true, false, false, false);
	this->lightningType = vec2(true, false);
	this->animation = NULL;
}

Model::~Model() {

}

void Model::render(Projection* projection, Camera* camera, vector<Light*> *globalLights) {
	this->shaderProgram->enable();
	//-- State machine activate
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	if (this->animation) this->animation->animate();
	this->boundingBox->move(this->transformation->getTransformMatrix());
	this->bindData(projection, camera, globalLights);
	this->drawElements();
	this->shaderProgram->disable();
}

void Model::lowRender(glm::mat4 depthMVP){
	this->shaderProgram->enable();
	//-- State machine activate
	
	/*glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/

	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram->getProgramID(),"depthMVP"), 1, GL_FALSE, &depthMVP[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram->getProgramID(), "u_model_matrix"), 1, GL_FALSE, &(this->transformation->getTransformMatrix())[0][0]);
	// -- VBO Data
	glBindBuffer(GL_ARRAY_BUFFER, this->glVBO_dir);
	// -- Vertex 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), 0);

	// -- Drawing
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->glVBO_indexes_dir);

	glDrawElements(GL_TRIANGLES, this->glVBO_indexes_size, GL_UNSIGNED_INT, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	this->shaderProgram->disable();
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

MaterialProperties * Model::getMaterialProperties(){
	return this->materialProperties;
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

void Model::setMaterialProperties(MaterialProperties * materialProperties){
	this->materialProperties = materialProperties;
}

void Model::setLight(Light * light){
	this->material = light;
}

void Model::setShader(CGLSLProgram * shader){
	this->shaderProgram = shader;
}

void Model::setSkyBox(SkyBox * skybox){
	this->skyboxReference = skybox;
}

void Model::isReflect(bool isReflected){
	this->isReflected = isReflected;
}

void Model::setShadowMapId(const GLuint ShadowMapId){
	this->ShadowMapId = ShadowMapId;
}

void Model::setDepthBiasMVP(const glm::mat4 DepthBiasMVP){
	this->DepthBiasMVP = DepthBiasMVP;
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
}

void Model::initGLDataBinding() {
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
