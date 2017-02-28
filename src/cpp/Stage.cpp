#include <Stage.h>
#include <iostream>

using namespace std;

Stage* Stage::uniqueStage = NULL;

void Stage::switchFace(Camera * cam, const int index){
	if (index == 0) cam->setPitchYaw(0.0f, 90.0f);
	else if (index == 1) cam->setPitchYaw(0.0f, -90.0f);
	else if (index == 2) cam->setPitchYaw(-90.0f, 180.0f);
	else if (index == 3) cam->setPitchYaw(90.0f, 180.0f);
	else if (index == 4) cam->setPitchYaw(0.0f, 180.0f);
	else if (index == 5) cam->setPitchYaw(0.0f, 0.0f);
}

Stage::Stage(RenderController* renderController) :RenderColleague(renderController) {
	this->initGLSLPrograms();
	//-- Init local structures
	this->projection = new Projection();

	//-- Initialize default values
	this->selectedModel = new float;
	*(this->selectedModel) = -1.0f;
	this->selectedLight = new float;
	*(this->selectedLight) = -1.0f;

	//-- Models Loading
	vector<Routes*> modelsRoutes(amountOfEntities, NULL);
	vector<Transformation*> modelsTransform(amountOfEntities, NULL);
	vector<Light*> modelsLight(amountOfEntities, NULL);
	vector<MaterialProperties*> modelsMaterialProperties(amountOfEntities, NULL);

	modelsRoutes[0] = (new Routes(
		/*OBJ File*/	"../models/player/player.obj",
		/*Texture*/		"../models/player/player.png"
	));
	modelsTransform[0] = (new Transformation(
		/*Scale*/			6.7f,
		/*Position*/		glm::vec3(-16.2f, 4.0f, -6.5f),
		/*Angle*/			0.0f,
		/*Rot Direction*/	glm::vec3(0.0f, 1.0f, 0.0f)
	));
	modelsLight[0] = (new Light(
		vec3(0.0f, 0.0f, 0.0f), //-- Does not matter
		vec3(0.3f),
		vec3(0.4f),
		vec3(0.5f)
	));
	modelsMaterialProperties[0] = (new MaterialProperties(0.1f, 100.0f, 0.1f, 0.2f));

	modelsRoutes[1] = (new Routes(
		/*OBJ File*/	"../models/futbol/futbol.obj",
		/*Texture*/		"../models/futbol/futbol.jpg"
	));
	modelsTransform[1] = (new Transformation(
		/*Scale*/			3.5f,
		/*Position*/		glm::vec3(-14.0f, 4.0f, 20.4f),
		/*Angle*/			0.0f,
		/*Rot Direction*/	glm::vec3(0.0f, 1.0f, 0.0f)
	));
	modelsLight[1] = (new Light(
		vec3(0.0f, 0.0f, 0.0f), //-- Does not matter
		vec3(0.5f),
		vec3(0.5f),
		vec3(0.5f)
	));
	modelsMaterialProperties[1] = (new MaterialProperties(0.1f, 100.0f, 0.1f, 0.2f));


	modelsRoutes[2] = (new Routes(
		/*OBJ File*/	"../models/ChessBoard/ChessBoard.obj",
		/*Texture*/		"../models/ChessBoard/ChessBoard.jpg"
	));
	modelsTransform[2] = (new Transformation(
		/*Scale*/			20.0f,
		/*Position*/		glm::vec3(0.0f, 0.0f, 10.0f),
		/*Angle*/			0.0f,
		/*Rot Direction*/	glm::vec3(0.0f, 1.0f, 0.0f)
	));
	modelsLight[2] = (new Light(
		vec3(0.0f, 0.0f, 0.0f), //-- Does not matter
		vec3(0.149f, 0.094f, 0.082f),
		vec3(0.404f, 0.251f, 0.227f),
		vec3(0.553f, 0.435f, 0.42f)
	));
	modelsMaterialProperties[2] = (new MaterialProperties(0.1f, 100.0f, 0.1f, 0.2f));


	modelsRoutes[3] = (new Routes(
		/*OBJ File*/	"../models/ChessPieces/king/king.obj",
		/*Texture*/		"../models/ChessPieces/king/king.jpg"
	));
	modelsTransform[3] = (new Transformation(
		/*Scale*/			6.7f,
		/*Position*/		glm::vec3(2.4f, 4.0f, -6.8f),
		/*Angle*/			0.0f,
		/*Rot Direction*/	glm::vec3(0.0f, 1.0f, 0.0f)
	));
	modelsLight[3] = (new Light(
		vec3(0.0f, 0.0f, 0.0f), //-- Does not matter
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.757f, 0.604f, 0.42f),
		vec3(0.8f, 0.8f, 0.8f)
	));
	modelsMaterialProperties[3] = (new MaterialProperties(0.1f, 100.0f, 0.1f, 0.2f));


	modelsRoutes[4] = (new Routes(
		/*OBJ File*/	"../models/ChessPieces/bishop/bishop.obj",
		/*Texture*/		"../models/ChessPieces/bishop/bishop.jpg"
	));
	modelsTransform[4] = (new Transformation(
		/*Scale*/			6.7f,
		/*Position*/		glm::vec3(7.0f, 4.0f, -6.5f),
		/*Angle*/			0.0f,
		/*Rot Direction*/	glm::vec3(0.0f, 1.0f, 0.0f)
	));
	modelsLight[4] = (new Light(
		vec3(0.0f, 0.0f, 0.0f), //-- Does not matter
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.757f, 0.604f, 0.42f),
		vec3(0.8f, 0.8f, 0.8f)
	));
	modelsMaterialProperties[4] = (new MaterialProperties(0.1f, 100.0f, 0.1f, 0.2f));


	modelsRoutes[5] = (new Routes(
		/*OBJ File*/	"../models/ChessPieces/knight/knight.obj",
		/*Texture*/		"../models/ChessPieces/knight/knight.jpg"
	));
	modelsTransform[5] = (new Transformation(
		/*Scale*/			6.7f,
		/*Position*/		glm::vec3(11.7f, 4.0f, -6.3f),
		/*Angle*/			1.5708f,
		/*Rot Direction*/	glm::vec3(0.0f, 1.0f, 0.0f)
	));
	modelsLight[5] = (new Light(
		vec3(0.0f, 0.0f, 0.0f), //-- Does not matter
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.757f, 0.604f, 0.42f),
		vec3(0.8f, 0.8f, 0.8f)
	));
	modelsMaterialProperties[5] = (new MaterialProperties(0.1f, 100.0f, 0.1f, 0.2f));


	modelsRoutes[6] = (new Routes(
		/*OBJ File*/	"../models/ChessPieces/pawn/pawn.obj",
		/*Texture*/		"../models/ChessPieces/pawn/pawn.jpg"
	));
	modelsTransform[6] = (new Transformation(
		/*Scale*/			6.7f,
		/*Position*/		glm::vec3(-11.5f, 4.0f, -1.98f),
		/*Angle*/			0.0f,
		/*Rot Direction*/	glm::vec3(0.0f, 1.0f, 0.0f)
	));
	modelsLight[6] = (new Light(
		vec3(0.0f, 0.0f, 0.0f), //-- Does not matter
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.757f, 0.604f, 0.42f),
		vec3(0.8f, 0.8f, 0.8f)
	));
	modelsMaterialProperties[6] = (new MaterialProperties(0.1f, 100.0f, 0.1f, 0.2f));


	modelsRoutes[7] = (new Routes(
		/*OBJ File*/	"../models/ChessPieces/queen/queen.obj",
		/*Texture*/		"../models/ChessPieces/queen/queen.jpg"
	));
	modelsTransform[7] = (new Transformation(
		/*Scale*/			6.7f,
		/*Position*/		glm::vec3(-2.22f, 4.0f, -6.7f),
		/*Angle*/			0.0f,
		/*Rot Direction*/	glm::vec3(0.0f, 1.0f, 0.0f)
	));
	modelsLight[7] = (new Light(
		vec3(0.0f, 0.0f, 0.0f), //-- Does not matter
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.757f, 0.604f, 0.42f),
		vec3(0.8f, 0.8f, 0.8f)
	));
	modelsMaterialProperties[7] = (new MaterialProperties(0.1f, 100.0f, 0.1f, 0.2f));


	modelsRoutes[8] = (new Routes(
		/*OBJ File*/	"../models/ChessPieces/rook/rook.obj",
		/*Texture*/		"../models/ChessPieces/rook/rook.jpg"
	));
	modelsTransform[8] = (new Transformation(
		/*Scale*/			6.7f,
		/*Position*/		glm::vec3(16.3f, 4.0f, -6.7f),
		/*Angle*/			0.0f,
		/*Rot Direction*/	glm::vec3(0.0f, 1.0f, 0.0f)
	));
	modelsLight[8] = (new Light(
		vec3(0.0f, 0.0f, 0.0f), //-- Does not matter
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.757f, 0.604f, 0.42f),
		vec3(0.8f, 0.8f, 0.8f)
	));
	modelsMaterialProperties[8] = (new MaterialProperties(0.1f, 100.0f, 0.1f, 0.2f));

	modelsRoutes[9] = (new Routes(
		/*OBJ File*/	"../models/barrel/barrel.obj",
		/*Textures*/	vector<string>{ 
							"../models/barrel/barrel.png" ,
							"../models/barrel/barrelNormal.png"
						}
	));
	modelsTransform[9] = (new Transformation(
		/*Scale*/			3.2f,
		/*Position*/		glm::vec3(-1.4f, 10.4f, 8.0f),
		/*Angle*/			0.0f,
		/*Rot Direction*/	glm::vec3(0.0f, 1.0f, 0.0f)
	));
	modelsLight[9] = (new Light(
		vec3(0.0f, 0.0f, 0.0f), //-- Does not matter
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.757f, 0.604f, 0.42f),
		vec3(0.8f, 0.8f, 0.8f)
	));
	modelsMaterialProperties[9] = (new MaterialProperties(0.1f, 100.0f, 0.1f, 0.2f));

	


	//-- Reflection Mapping Vector
	vector<bool> reflectionVectorMapModels = {false, false, false, false, false, false, false, false, true, false};

	//-- Init Model Collection
	this->modelCollection = new ModelCollection(modelsRoutes, modelsTransform, modelsLight, modelsMaterialProperties);
	this->modelCollection->setReflectionMap(reflectionVectorMapModels);

	//-- Light Models Loading
	vector<Routes*> lightsRoutes(amountOfLights, NULL);
	vector<Transformation*> lightsTransform(amountOfLights, NULL);
	vector<Light*> lightsLight(amountOfLights, NULL);
	vector<MaterialProperties*> lightsMaterialProperties(amountOfLights, NULL);

	lightsRoutes[0] = (new Routes(
		/*OBJ File*/	"../models/stall/stall.obj",
		/*Texture*/		"../models/stall/stall.png"
	));
	lightsTransform[0] = (new Transformation(
		/*Scale*/			1.0f,
		/*Position*/		vec3(2.9f, 18.5f, -7.70f),
		/*Angle*/			0.0f,
		/*Rot Direction*/	glm::vec3(0.0f, 1.0f, 0.0f)
	));
	lightsLight[0] = (new Light(
		vec3(2.9f, 18.5f, -7.70f), 
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f), 
		vec3(1.0f, 1.0f, 1.0f)
	));
	lightsMaterialProperties[0] = (new MaterialProperties(0.1f, 100.0f, 0.1f, 0.2f));

	//-- Reflection map to the lights
	vector<bool> reflectionVectorMapLights = { false, false, false, false, false, false, false, false, true };

	//-- Initializing Light Collection
	this->lightCollection = new ModelCollection(lightsRoutes, lightsTransform, lightsLight, lightsMaterialProperties);
	this->lightCollection->setReflectionMap(reflectionVectorMapLights);

	//-- Initializing Player
	this->player = new Player(this->modelCollection->getEntity(0));
	this->camera = new Camera(this->modelCollection->getEntity(0)->getTransformation());
	this->mousePicker = new MousePicker(this->camera, this->projection);

	this->skyBox = new SkyBox({ 
		"../sky/down-under/right.tga", 
		"../sky/down-under/left.tga", 
		"../sky/down-under/up.tga",
		"../sky/down-under/down.tga", 
		"../sky/down-under/back.tga",
		"../sky/down-under/front.tga"}, 
		this->projection->getProjection(), 
		this->camera->getView());

	this->modelCollection->setSkyBox(this->skyBox);
	this->lightCollection->setSkyBox(this->skyBox);

	//-- Init Frame Buffer Object
	this->frameBufferObject = new FrameBuffer();

	this->clicked = false;

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

Stage::~Stage() {

}

void Stage::backRender(Camera* cam, Projection* proj){
	//-- Render SkyBox
	this->skyBox->render();

	//-- Render the model collection and light collection
	this->modelCollection->render(
		proj,
		cam,
		this->lightCollection->getLightSet(),
		this->illuminationPrograms,
		{ "Blinn-Phong",
		"Blinn-Phong",
		"Blinn-Phong",
		"Blinn-Phong",
		"Blinn-Phong",
		"Blinn-Phong",
		"Blinn-Phong",
		"Blinn-Phong",
		"Blinn-Phong",
		"Blinn-Phong",});
	this->lightCollection->render(
		proj,
		cam,
		this->lightCollection->getLightSet(),
		this->illuminationPrograms->at("Blinn-Phong"));
}

void Stage::frontRender(){
	//-- Render SkyBox
	this->skyBox->render();

	//-- Move Player
	this->player->move();

	//-- Move Camera
	this->camera->move();

	//-- Calculating Mouse Ray
	this->mousePicker->calculateRay();

	//-- Render the model collection and light collection
	this->modelCollection->render(
		this->projection,
		this->camera,
		this->lightCollection->getLightSet(),
		this->illuminationPrograms,
		{ "Blinn-Phong-With-Shadow",
		"Blinn-Phong-With-Shadow",
		"Blinn-Phong-With-Shadow",
		"Blinn-Phong-With-Shadow",
		"Blinn-Phong-With-Shadow",
		"Blinn-Phong-With-Reflections",
		"Blinn-Phong-With-Shadow",
		"Blinn-Phong-With-Shadow",
		"Blinn-Phong-With-Reflections",
		"Blinn-Phong-With-NormalMapping", });
	this->lightCollection->render(
		this->projection,
		this->camera,
		this->lightCollection->getLightSet(),
		this->illuminationPrograms->at("Blinn-Phong"));
}

void Stage::initGLSLPrograms(){
	//-- Graphic Card Info
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	//-- Structure to initialize
	this->illuminationPrograms = new map<string, CGLSLProgram*>();
	vector< map<string, string>* > *routes = new vector< map<string, string>* >({
		new map<string, string>({ { "name", "Blinn-Phong" },{ "vertex", "../src/shaders/BlinnPhong.vert" }, { "fragment", "../src/shaders/BlinnPhong.frag" } }),
		new map<string, string>({ { "name", "Blinn-Phong-With-Shadow" },{ "vertex", "../src/shaders/BlinnPhongShadow.vert" },{ "fragment", "../src/shaders/BlinnPhongShadow.frag" } }),
		new map<string, string>({ { "name", "Blinn-Phong-With-Reflections" },{ "vertex", "../src/shaders/BlinnPhongReflections.vert" },{ "fragment", "../src/shaders/BlinnPhongReflections.frag" } }),
		new map<string, string>({ { "name", "Blinn-Phong-With-NormalMapping" },{ "vertex", "../src/shaders/BlinnPhongNormalMapping.vert" },{ "fragment", "../src/shaders/BlinnPhongNormalMapping.frag" } }),
		new map<string, string>({ { "name", "Depth" },{ "vertex", "../src/shaders/Depth.vert" },{ "fragment", "../src/shaders/Depth.frag" } })
	});

	//-- Initialize Shader Programs
	std::vector< map<string, string>* >::iterator programRoute;
	for (programRoute = routes->begin(); programRoute != routes->end(); programRoute++){
		std::cout << "\nLoading " << (*programRoute)->at("name") << " shading program...\n";

		this->illuminationPrograms->insert_or_assign(
			(*programRoute)->at("name"),
			new CGLSLProgram()
		);


		this->illuminationPrograms->at( (*programRoute)->at("name") )->loadShader(
			(*programRoute)->at("vertex"),
			CGLSLProgram::VERTEX
		);

		this->illuminationPrograms->at((*programRoute)->at("name"))->loadShader(
			(*programRoute)->at("fragment"),
			CGLSLProgram::FRAGMENT
		);

		this->illuminationPrograms->at((*programRoute)->at("name"))->create_link();

	}
}

Stage * Stage::Instance(RenderController * renderController) {
	if (!uniqueStage)
		uniqueStage = new Stage(renderController);
	return uniqueStage;
}

void Stage::Destroy() {
	if (!uniqueStage) return;
	uniqueStage->~Stage();
}

Projection * Stage::getProjection() {
	return this->projection;
}

Model * Stage::getSelectedModel(){
	return this->modelCollection->getEntity(unsigned int(*(this->selectedModel)));
}

Model * Stage::getSelectedLight(){
	//-- Cambiar por un arreglo de luces a futuro 03/02/17
	//-- Hoy es el futuro, pero aun no se ha cambiado ni se va a cambiar 16/02/17
	//-- Hoy es mucho después del futuro inclusive, y no tengo la esperanza de cambiarlo siquiera 24/02/2017
	return this->lightCollection->getEntity(0);
}

float * Stage::getSelectedModelIndex(){
	return this->selectedModel;
}

float * Stage::getSelectedLightIndex(){
	return this->selectedLight;
}

void Stage::Notify(string message, void* data) {
	if (message == "init VBOs") {
		this->modelCollection->initVBOs();
		this->lightCollection->initVBOs();
	}
	else if (message == "width/height") {
		this->width = ((float*)data)[0];
		this->height = ((float*)data)[1];
	}
	else if (message == "InitSideBar") 
		this->Send("MainObject", (void*)this->player);

	/*Managing Events*/
	else if (message == "eventKeyPressed")
		this->player->keyboardInputs(((int*)data)[0], ((int*)data)[1]);
	else if (message == "eventScroll")
		this->camera->calculateZoom( *((int*)data) );
	else if (message == "mouseButton") {
		if (((int*)data)[0] == GLFW_MOUSE_BUTTON_LEFT && ((int*)data)[1] == GLFW_PRESS && !this->clicked) {
			//-- Save first click
			this->clicked = true;
			this->xPos = ((int*)data)[2];
			this->yPos = ((int*)data)[3];
			this->xPosFirst = this->xPos;
			this->yPosFirst = this->yPos;

			this->camera->calculatePitch(0, 0, 0, this->yPos);
			this->camera->calculateAngleAroundPlayer(0, 0, this->xPos, 0);
		}
		else if (((int*)data)[0] == GLFW_MOUSE_BUTTON_LEFT && ((int*)data)[1] == GLFW_PRESS) {
			//-- Updating click values
			this->xPos = this->xPosFirst - ((int*)data)[2];
			this->yPos = this->yPosFirst - ((int*)data)[3];
			this->camera->calculatePitch(0, 0, 0, this->yPos);
			this->camera->calculateAngleAroundPlayer(0, 0, this->xPos, 0);
		}
		else if (((int*)data)[0] == GLFW_MOUSE_BUTTON_LEFT && ((int*)data)[1] == GLFW_RELEASE) {
			//-- Key released
			this->clicked = false;
		}

		//this->camera->calculatePitch(((int*)data)[0], ((int*)data)[1], ((int*)data)[2], ((int*)data)[3]);
		//this->camera->calculateAngleAroundPlayer(((int*)data)[0], ((int*)data)[1], ((int*)data)[2], ((int*)data)[3]);
	}
	/*
	if (message == "Animate") {
		this->entities[4]->getAnimation()->setOnRet();
		this->entities[5]->getAnimation()->setOnRet();
		this->entities[8]->getAnimation()->setOnRet();
	}*/
}

void Stage::buildDynamicCubeMap(const int entityID) {
	this->modelCollection->getEntity(entityID)->isReflect(false);
	Camera* aux_camera = new Camera(*(this->modelCollection->getEntity(entityID)->getTransformation()->getPosition()), 0.0f, 0.0f, vec3(0.0f, 1.0f, 0.0f));
	Projection* aux_projection = new Projection(90.0f, 1.0f, 1.0f, 1000.0f);

	this->modelCollection->getEntity(entityID)->getTexture()->setCubeMapTexture(this->frameBufferObject->getCubeMapColorTexture());
	this->frameBufferObject->bindCubeMapFrameBuffer();
	for (int i = 0; i < 6; i++){
		this->frameBufferObject->activeCubeMapColorTexture(i);
		this->switchFace(aux_camera, i);
		this->backRender(aux_camera, aux_projection);
	
	}
	this->frameBufferObject->unbindCurrentFrameBuffer();
	this->modelCollection->getEntity(entityID)->isReflect(true);
}

void Stage::buildShadowMap(){
	glm::vec3 lightInvDir = (*(this->lightCollection->getEntity(0)->getMaterialLight()->getPosition()));
	// Compute the MVP matrix from the light's point of view
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-25, 25, -25, 25, -20, 60);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 10), glm::vec3(0, 1, 0));
	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
	this->frameBufferObject->bindImageFrameBuffer();
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	this->modelCollection->low_render(depthMVP, this->illuminationPrograms->at("Depth"));
	this->frameBufferObject->unbindCurrentFrameBuffer();


	glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);
	glm::mat4 depthBiasMVP = biasMatrix*depthMVP;
	this->modelCollection->setShadow(depthBiasMVP, this->frameBufferObject->getImageDepthTexture());
}

void Stage::drawShadowMap(){
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

void Stage::render() {
	//-- Build Necesary CubeMaps
	this->buildDynamicCubeMap(8);
	this->buildDynamicCubeMap(5);
	this->buildShadowMap();
	this->frontRender();
	this->drawShadowMap();
}
