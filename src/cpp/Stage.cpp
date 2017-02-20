#include <Stage.h>
#include <iostream>

using namespace std;

Stage* Stage::uniqueStage = NULL;

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
		vec3(0.5f, 0.3f, 0.2f), 
		vec3(0.2f, 0.1f, 0.2f), 
		vec3(1.0f, 1.0f, 1.0f)
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
		vec3(0.431f, 0.0f, 0.0f),
		vec3(1.0f, 0.098f, 0.0f),
		vec3(0.392f, 0.588f, 0.098f)
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
		vec3(0.5f, 0.3f, 0.2f),
		vec3(0.2f, 0.1f, 0.2f),
		vec3(0.25f, 0.0f, 0.2f)
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
		vec3(0.51f, 1.0f, 0.196f),
		vec3(1.0f, 0.902f, 0.196f),
		vec3(0.51f, 0.902f, 0.196f)
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
		vec3(0.51f, 1.0f, 0.196f),
		vec3(1.0f, 0.902f, 0.196f),
		vec3(0.51f, 0.902f, 0.196f)
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
		vec3(0.51f, 1.0f, 0.196f),
		vec3(1.0f, 0.902f, 0.196f),
		vec3(0.51f, 0.902f, 0.196f)
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
		vec3(0.51f, 1.0f, 0.196f),
		vec3(1.0f, 0.902f, 0.196f),
		vec3(0.51f, 0.902f, 0.196f)
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
		vec3(0.51f, 1.0f, 0.196f),
		vec3(1.0f, 0.902f, 0.196f),
		vec3(0.51f, 0.902f, 0.196f)
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
		vec3(0.51f, 1.0f, 0.196f),
		vec3(1.0f, 0.902f, 0.196f),
		vec3(0.51f, 0.902f, 0.196f)
	));
	modelsMaterialProperties[8] = (new MaterialProperties(0.1f, 100.0f, 0.1f, 0.2f));

	//-- Init Model Collection
	this->modelCollection = new ModelCollection(modelsRoutes, modelsTransform, modelsLight, modelsMaterialProperties);

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
		/*Position*/		vec3(16.0f, 18.5f, -6.8f),
		/*Angle*/			0.0f,
		/*Rot Direction*/	glm::vec3(0.0f, 1.0f, 0.0f)
	));
	lightsLight[0] = (new Light(
		vec3(16.0f, 18.5f, -6.8f), 
		vec3(0.392f, 0.0f, 0.0f), 
		vec3(1.0f, 1.0f, 1.0f), 
		vec3(0.333f, 0.333f, 0.333f)
	));
	lightsMaterialProperties[0] = (new MaterialProperties(0.1f, 100.0f, 0.1f, 0.2f));

	//-- Initializing Light Collection
	this->lightCollection = new ModelCollection(lightsRoutes, lightsTransform, lightsLight, lightsMaterialProperties);

	//-- Initializing Player
	this->player = new Player(this->modelCollection->getEntity(0));
	this->camera = new Camera(this->modelCollection->getEntity(0)->getTransformation());
	this->mousePicker = new MousePicker(this->camera, this->projection);

	this->skyBox = new SkyBox({ 
		"../sky/space/right.png", 
		"../sky/space/left.png", 
		"../sky/space/up.png",
		"../sky/space/down.png", 
		"../sky/space/back.png",
		"../sky/space/front.png"}, 
		this->projection->getProjection(), 
		this->camera->getView());
}

Stage::~Stage() {

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
	//new map<string, string>({ { "name", "Phong" }, { "vertex", "../src/shaders/Phong.vert" }, { "fragment", "../src/shaders/Phong.frag" } } ),
	new map<string, string>({ { "name", "Blinn-Phong" },{ "vertex", "../src/shaders/BlinnPhong.vert" }, { "fragment", "../src/shaders/BlinnPhong.frag" } })
	//new map<string, string>({ { "name", "Oren-Nayar" },{ "vertex", "../src/shaders/Phong.vert" }, { "fragment", "../src/shaders/Phong.frag" } }),
	//new map<string, string>({ { "name", "Cook-Torrance" },{ "vertex", "../src/shaders/Phong.vert" }, { "fragment", "../src/shaders/Phong.frag" } })
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
		this->camera->calculatePitch(((int*)data)[0], ((int*)data)[1], ((int*)data)[2], ((int*)data)[3]);
		this->camera->calculateAngleAroundPlayer(((int*)data)[0], ((int*)data)[1], ((int*)data)[2], ((int*)data)[3]);
	}
	/*
	if (message == "Animate") {
		this->entities[4]->getAnimation()->setOnRet();
		this->entities[5]->getAnimation()->setOnRet();
		this->entities[8]->getAnimation()->setOnRet();
	}*/
}

void Stage::render() {
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
		this->illuminationPrograms->at("Blinn-Phong"));
	this->lightCollection->render(
		this->projection, 
		this->camera, 
		this->lightCollection->getLightSet(), 
		this->illuminationPrograms->at("Blinn-Phong"));
}
