#include <RenderFacade.h>

void RenderFacade::checkAssertions(){
	assert(this->shaders != NULL && "No shaders loaded, load shaders first");
	assert(this->model_entities.size() != 0 && "No models loaded, load some models first");
	assert(this->light_entities.size() != 0 && "No lights loaded, load some lights first");
	assert(this->camera != NULL && "No camera loaded, load a camera first");
	assert(this->projection != NULL && "No projection loaded, load a projection first");
	assert(this->frameBufferObject != NULL && "No FBO loaded, load a FBO first");
	assert(this->lowQualityRenderShader != "" && "No Low Quality Shader Name identified");
	assert(this->depthShader != "" && "No Depth Shader Name identified");
}

void RenderFacade::switchFace(Camera * cam, const int index){
	if (index == 0) cam->setPitchYaw(0.0f, 90.0f);
	else if (index == 1) cam->setPitchYaw(0.0f, -90.0f);
	else if (index == 2) cam->setPitchYaw(-90.0f, 180.0f);
	else if (index == 3) cam->setPitchYaw(90.0f, 180.0f);
	else if (index == 4) cam->setPitchYaw(0.0f, 180.0f);
	else if (index == 5) cam->setPitchYaw(0.0f, 0.0f);
}

RenderFacade::RenderFacade(){
	this->shaders = NULL;
	this->frameBufferObject = NULL;
	this->projection = NULL;
	this->camera = NULL;

	//-- To draw shadow map
	GLfloat planeVertex[] =
	{
		4.6f, 2.0f, 0.0f, 1.0f, 0.0f,
		2.0f, 4.6f, 0.0f, 0.0f, 1.0f,
		2.0f, 2.0f, 0.0f, 0.0f, 0.0f,

		4.6f, 2.0f, 0.0f, 1.0f, 0.0f,
		4.6f, 4.6f, 0.0f, 1.0f, 1.0f,
		2.0f, 4.6f, 0.0f, 0.0f, 1.0f
	};

	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertex), &planeVertex, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);

	texture_program.loadShader("../src/shaders/texture.vert", CGLSLProgram::VERTEX);
	texture_program.loadShader("../src/shaders/texture.frag", CGLSLProgram::FRAGMENT);

	texture_program.create_link();

	texture_program.enable();

	texture_program.addAttribute("position");
	texture_program.addAttribute("texcoord");

	texture_program.addUniform("projection");
	texture_program.addUniform("view");
	texture_program.addUniform("model");
	texture_program.addUniform("texture1");

	texture_program.disable();
}

RenderFacade::~RenderFacade(){

}

void RenderFacade::initModelEntities(
	const vector<Routes*> routes, 
	const vector<Transformation*> transformations, 
	const vector<Light*> lights, 
	const vector<MaterialProperties*> materialProperties){
	for (int i = 0; i < (int)routes.size(); i++) {
		this->model_entities.push_back(new Reader(routes[i]));
		this->model_entities.back()->setTransformation(transformations[i]);
		this->model_entities.back()->setLight(lights[i]);
		this->model_entities.back()->setMaterialProperties(materialProperties[i]);
	}
}

void RenderFacade::initLightEntities(
	const vector<Routes*> routes, 
	const vector<Transformation*> transformations,
	const vector<Light*> lights, 
	const vector<MaterialProperties*> materialProperties){
	for (int i = 0; i < (int)routes.size(); i++) {
		this->light_entities.push_back(new Reader(routes[i]));
		this->light_entities.back()->setTransformation(transformations[i]);
		this->light_entities.back()->setLight(lights[i]);
		this->light_entities.back()->setMaterialProperties(materialProperties[i]);
	}
}

void RenderFacade::bindProjection(Projection * projection){
	this->projection = projection;
}

void RenderFacade::bindCamera(Camera * camera){
	this->camera = camera;
}

void RenderFacade::bindShaderPrograms(map<string, CGLSLProgram*>* shaders){
	this->shaders = shaders;
}

void RenderFacade::bindLowQualityShader(string lowQualityShaderName){
	this->lowQualityRenderShader = lowQualityShaderName;
}

void RenderFacade::bindDepthShader(string depthShader){
	this->depthShader = depthShader;
}

void RenderFacade::bindFBO(FrameBuffer * FBO){
	this->frameBufferObject = FBO;
}

void RenderFacade::render(string shaderName){
	this->checkAssertions();
	this->FBOrender_shadow_map();
	this->buildCubeMap();
	CGLSLProgram* shader = this->shaders->at(shaderName);
	shader->enable();
	this->camera->bind(shader);
	this->projection->bind(shader);
	int light_index = 0;
	for (Model* light : this->light_entities) {
		light->getLight()->bind(shader, false, light_index);
		light_index++;
	}
	for (Model* model : this->model_entities) {
		model->bind(shader);
		model->render(shader);
	}
	for (Model* light : this->light_entities) {
		light->bind(shader);
		light->render(shader);
	}
	shader->disable();
}

void RenderFacade::render(Projection * projection, Camera * camera, string shaderName){
	this->checkAssertions();
	this->FBOrender_shadow_map();
	CGLSLProgram* shader = this->shaders->at(shaderName);
	shader->enable();
	camera->bind(shader);
	projection->bind(shader);
	int light_index = 0;
	for (Model* light : this->light_entities) {
		light->getLight()->bind(shader, false, light_index);
		light_index++;
	}
	for (Model* model : this->model_entities) {
		model->bind(shader);
		model->render(shader);
	}
	for (Model* light : this->light_entities) {
		light->bind(shader);
		light->render(shader);
	}
	shader->disable();
}

void RenderFacade::low_quality_render(Model* modelExclude){
	this->checkAssertions();
	CGLSLProgram* shader = this->shaders->at(this->lowQualityRenderShader);
	shader->enable();
	this->camera->bind(shader);
	this->projection->bind(shader);
	int light_index = 0;
	for (Model* light : this->light_entities) {
		light->getLight()->bind(shader, false, light_index);
		light_index++;
	}
	for (Model* model : this->model_entities) {
		if (model != modelExclude) {
			model->bind(shader);
			model->render(shader);
		}
	}
	for (Model* light : this->light_entities) {
		light->bind(shader);
		light->render(shader);
	}
	shader->disable();
}

void RenderFacade::low_quality_render(Projection * projection, Camera * camera, const int index){
	this->checkAssertions();
	CGLSLProgram* shader = this->shaders->at(this->lowQualityRenderShader);
	shader->enable();
	camera->bind(shader);
	projection->bind(shader);
	int i = 0;
	for (Model* light : this->light_entities) {
		light->getLight()->bind(shader, false, i);
		i++;
	}
	i = 0;
	for (Model* model : this->model_entities) {
		if (i == index) continue;
		model->bind(shader);
		model->render(shader);
	}
	for (Model* light : this->light_entities) {
		light->bind(shader);
		light->render(shader);
	}
	shader->disable();
}

void RenderFacade::render_shadow_map(){
	texture_program.enable();
	modelo = glm::translate(glm::vec3(2.5f, -0.2f, 0.0f));
	vista = glm::lookAt(vec3(0.0f, 0.0f, 8.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	proyeccion = glm::perspective(45.0f, (float)getDisplaySize().x / (float)getDisplaySize().y, 0.1f, 1000.0f);

	glUniformMatrix4fv(texture_program.getLocation("model"), 1, GL_FALSE, value_ptr(modelo));
	glUniformMatrix4fv(texture_program.getLocation("view"), 1, GL_FALSE, value_ptr(vista));
	glUniformMatrix4fv(texture_program.getLocation("projection"), 1, GL_FALSE, value_ptr(proyeccion));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->frameBufferObject->getImageDepthTexture());
	glUniform1i(texture_program.getLocation("texture1"), 0);

	glBindVertexArray(planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	texture_program.disable();
}

void RenderFacade::FBOrender_shadow_map(){
	glm::vec3 lightPos;
	glm::vec3 lightInvDir;
	glm::vec3 finalVal;
	glm::mat4 depthProjectionMatrix;
	if ( *(this->light_entities[0]->getLight()->getTypeZSpot()) ) {
		lightPos = *(this->light_entities[0]->getLight()->getPosition());
		lightInvDir = *(this->light_entities[0]->getLight()->getDirection());
		finalVal = -lightInvDir*lightPos;
	}
	else finalVal = *(this->light_entities[0]->getLight()->getPosition());
	
	// Compute the MVP matrix from the light's point of view
	depthProjectionMatrix = glm::ortho<float>(-25, 25, -25, 25, -20, 60);
	glm::mat4 depthViewMatrix = glm::lookAt(finalVal, glm::vec3(0, 0, 10), glm::vec3(0, 1, 0));
	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
	this->frameBufferObject->bindImageFrameBuffer();
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);


	for (Model* model : this->model_entities) {
		model->setShader(this->shaders->at(this->depthShader));
		model->lowRender(depthMVP);
	}
	
	this->frameBufferObject->unbindCurrentFrameBuffer();
	glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);
	glm::mat4 depthBiasMVP = biasMatrix*depthMVP;
	for (Model* model : this->model_entities) {
		model->setDepthBiasMVP(depthBiasMVP);
		model->setShadowMapId(this->frameBufferObject->getImageDepthTexture());
	}
}

void RenderFacade::FBOrender_color_cube_map(Model * model, const int index){
	this->checkAssertions();
	Camera* aux_camera = new Camera(*(model->getTransformation()->getPosition()), 0.0f, 0.0f, vec3(0.0f, 1.0f, 0.0f));
	Projection* aux_projection = new Projection(90.0f, 1.0f, 1.0f, 1000.0f);

	this->frameBufferObject->bindCubeMapFrameBuffer();
	for (int i = 0; i < 6; i++) {
		this->frameBufferObject->activeCubeMapColorTexture(i);
		this->switchFace(aux_camera, i);
		this->low_quality_render(aux_projection, aux_camera, index);
	}
	this->frameBufferObject->unbindCurrentFrameBuffer();

	model->getTexture()->setCubeMapTexture(this->frameBufferObject->getCubeMapColorTexture());
}

void RenderFacade::buildCubeMap(){
	for (int i = 0; i < this->model_entities.size(); i++)
		if ( *(this->model_entities[i]->getIsReflected()) || *(this->model_entities[i]->getIsRefracted()) )
			this->FBOrender_color_cube_map(model_entities[i], i);
}

int RenderFacade::isClicked(vec3 ray){
	int index = 0;
	vec3 cam_pos = this->camera->getPosition();
	for (Model* model : this->model_entities) {
		if (model->isPointed(cam_pos, ray))
			return index;
		index++;
	}
	return -1;
}

Model * RenderFacade::getModel(const int index){
	return this->model_entities.at(index);
}

Model * RenderFacade::getLightModel(const int index){
	return this->light_entities.at(index);
}

void RenderFacade::initVBOs(){
	for (Model* model : this->model_entities)
		model->initGLDataBinding();

	for (Model* light : this->light_entities)
		light->initGLDataBinding();
}
