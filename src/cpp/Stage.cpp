#include <Stage.h>
#include <iostream>

using namespace std;

Stage* Stage::uniqueStage = NULL;

Stage::Stage(RenderController* renderController) :RenderColleague(renderController) {
	//-- Init local structures
	this->skyBox = new SkyBox();
	this->light = new Light(vec3(16.0f, 18.5f, -6.8f), vec3(0.392f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), vec3(0.333f, 0.333f, 0.333f));
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
	//-- Initializing Entities
	for (unsigned int i = 0; i < amountOfEntities; i++) this->entities.push_back(new Reader(modelsRoutes[i], modelsTransform[i], modelsLight[i]));

	
	vector<State*> * states;
	
	//-- Animate TORRE
	states = new vector<State*>(1, NULL);
	states->at(0) = new State( vec3(16.3f, 4.0f, 26.2f), vec3(0.0f, 0.0f, 0.1f), false, 330 );
	this->entities[8]->setAnimation(new Animation(this->entities[8]->getTransformation(), states));
	this->entities[8]->getAnimation()->setOn(true);

	//-- Animate CABALLO
	states = new vector<State*>(4, NULL);
	states->at(0) = new State(vec3(11.7f, 4.0f, -1.6f), vec3(0.0f, 0.0f, 0.1f), false, 47);
	states->at(1) = new State(vec3(2.43f, 4.0f, -6.3f), vec3(-0.1f, 0.0f, 0.0f), false, 93);
	states->at(2) = new State(vec3(11.7f, 4.0f, -6.3f), vec3(0.0f, 0.0f, 0.1f), false, 94);
	states->at(3) = new State(vec3(11.7f, 4.0f, -6.3f), vec3(0.1f, 0.0f, 0.0f), false, 46);
	this->entities[5]->setAnimation(new Animation(this->entities[5]->getTransformation(), states));
	this->entities[5]->getAnimation()->setOn(true);


	//-- Animate Alfil
	states = new vector<State*>(2, NULL);
	states->at(0) = new State(vec3(11.7f, 4.0f, -1.6f), vec3(-0.1f, 0.0f, 0.1f), false, 189);
	states->at(1) = new State(vec3(2.43f, 4.0f, -6.3f), vec3(0.1f, 0.0f, 0.1f), false, 145);
	this->entities[4]->setAnimation(new Animation(this->entities[4]->getTransformation(), states));
	this->entities[4]->getAnimation()->setOn(true);


	//-- Light Models Loading
	vector<Routes*> lightsRoutes(amountOfLights, NULL);
	vector<Transformation*> lightsTransform(amountOfLights, NULL);
	vector<Light*> lightsLight(amountOfLights, NULL);

	lightsRoutes[0] = (new Routes(
		/*OBJ File*/	"../models/stall/stall.obj",
		/*Texture*/		"../models/stall/stall.png"
	));
	lightsTransform[0] = (new Transformation(
		/*Scale*/			1.0f,
		/*Position*/		*(this->light->getPosition()),
		/*Angle*/			0.0f,
		/*Rot Direction*/	glm::vec3(0.0f, 1.0f, 0.0f)
	));
	lightsLight[0] = this->light;

	//-- Initializing Lights
	for (unsigned int i = 0; i < amountOfLights; i++) this->lightModels.push_back(new Reader(lightsRoutes[i], lightsTransform[i], lightsLight[i]));

	//-- Initializing Player
	this->player = new Player(this->entities[0]);
	this->camera = new Camera(player);
	this->mousePicker = new MousePicker(this->camera, this->projection);

	//-- Initializing Uniforms ID
	this->ID = new vector<GLint>(15, 0);
}

Stage::~Stage() {

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
	return this->entities[int(*(this->selectedModel))];
}

Model * Stage::getSelectedLight(){
	//-- Cambiar por un arreglo de luces a futuro
	return this->lightModels[0];
}

float * Stage::getSelectedModelIndex(){
	return this->selectedModel;
}

float * Stage::getSelectedLightIndex(){
	return this->selectedLight;
}

void Stage::Notify(string message, void* data) {
	if (message == "init VBOs") {
		for (int i = 0; i < (int)this->entities.size(); i++)
			this->entities[i]->initGLDataBinding(i);
		for (int i = 0; i < (int)this->lightModels.size(); i++)
			this->lightModels[i]->initGLDataBinding(i);
	}
	else if (message == "shader id")
		this->shader_id = *((GLuint*)(&data));

	else if (message == "shader id2")
		this->shader_id2 = *((GLuint*)(&data));
	else if (message == "width/height") {
		this->width = ((float*)data)[0];
		this->height = ((float*)data)[1];
	}

	if (message == "InitSideBar") 
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

	if (message == "Animate") {
		this->entities[4]->getAnimation()->setOnRet();
		this->entities[5]->getAnimation()->setOnRet();
		this->entities[8]->getAnimation()->setOnRet();
	}
}

void Stage::render() {
	//-- Move Player
	this->player->move();

	//-- Move Camera
	this->camera->move();

	//-- Calculating Mouse Ray
	this->mousePicker->calculateRay();

	//cout << this->entities[0]->getTransformation()->getQuaternion()->x << endl;
	//std::cout << *(this->selectedModel) << " " << *(this->selectedLight) << std::endl;
	//cout << "x:: " << mousePicker->getCurrentMouseRay().x << " y:: " << mousePicker->getCurrentMouseRay().y << " z:: " << mousePicker->getCurrentMouseRay().z << endl;

	//-- Bind ambient light uniforms, projection and view matrices

	//-- Light Colors
	if (*(this->light->active())) {
		this->ID->at(0) = glGetUniformLocation(this->shader_id, "u_lightAmbientIntensitys");
		glUniform3f(this->ID->at(0), this->light->getAmbient()->r, this->light->getAmbient()->g, this->light->getAmbient()->b);

		this->ID->at(1) = glGetUniformLocation(this->shader_id, "u_lightDiffuseIntensitys");
		glUniform3f(this->ID->at(1), this->light->getDiffuse()->r, this->light->getDiffuse()->g, this->light->getDiffuse()->b);

		this->ID->at(2) = glGetUniformLocation(this->shader_id, "u_lightSpecularIntensitys");
		glUniform3f(this->ID->at(2), this->light->getSpecular()->r, this->light->getSpecular()->g, this->light->getSpecular()->b);
	} else {
		this->ID->at(0) = glGetUniformLocation(this->shader_id, "u_lightAmbientIntensitys");
		glUniform3f(this->ID->at(0), 0.0f, 0.0f, 0.0f);

		this->ID->at(1) = glGetUniformLocation(this->shader_id, "u_lightDiffuseIntensitys");
		glUniform3f(this->ID->at(1), 0.0f, 0.0f, 0.0f);

		this->ID->at(2) = glGetUniformLocation(this->shader_id, "u_lightSpecularIntensitys");
		glUniform3f(this->ID->at(2), 0.0f, 0.0f, 0.0f);
	}
	
	this->ID->at(3) = glGetUniformLocation(this->shader_id, "u_lightPosition");
	glUniform3f(this->ID->at(3), this->lightModels[0]->getMaterialLight()->getPosition()->x, this->lightModels[0]->getMaterialLight()->getPosition()->y, this->lightModels[0]->getMaterialLight()->getPosition()->z);

	this->ID->at(4) = glGetUniformLocation(this->shader_id, "eye_position");
	glUniform3f(this->ID->at(4), this->camera->getPosition().x, this->camera->getPosition().y, this->camera->getPosition().z);

	this->ID->at(5) = glGetUniformLocation(this->shader_id, "u_viewMat");
	glUniformMatrix4fv(this->ID->at(5), 1, GL_FALSE, &(this->camera->getMatrix())[0][0]);

	this->ID->at(6) = glGetUniformLocation(this->shader_id, "u_projMat");
	glUniformMatrix4fv(this->ID->at(6), 1, GL_FALSE, &(this->projection->getMatrix())[0][0]);

	this->ID->at(7) = glGetUniformLocation(this->shader_id, "u_normalMat");
	glUniformMatrix4fv(this->ID->at(7), 1, GL_FALSE, &(glm::inverse(glm::transpose(this->camera->getMatrix())))[0][0]);

	this->ID->at(8) = glGetUniformLocation(this->shader_id, "u_lightAttenuation");
	glUniform3f(this->ID->at(8), this->light->getAttenuation()->x, this->light->getAttenuation()->y, this->light->getAttenuation()->z);

	this->ID->at(9) = glGetUniformLocation(this->shader_id, "u_lightType");
	glUniform3f(this->ID->at(9), (GLfloat)this->light->getType()->x, (GLfloat)this->light->getType()->y, (GLfloat)this->light->getType()->z);

	this->ID->at(10) = glGetUniformLocation(this->shader_id, "u_lightSpotDirection");
	glUniform3f(this->ID->at(10), this->light->getDirection()->x, this->light->getDirection()->y, this->light->getDirection()->z);

	this->ID->at(11) = glGetUniformLocation(this->shader_id, "u_lightSpotExp");
	glUniform1f(this->ID->at(11), *(this->light->getSpotExp()) );

	this->ID->at(12) = glGetUniformLocation(this->shader_id, "u_spotCosCutOff");
	glUniform1f(this->ID->at(12), *(this->light->getSpotCosCutOff()));
	

	//-- Render all the entities
	for (int i = 0; i < (int)this->entities.size(); i++)
		if ((int)this->entities[i]->getLightningType()->x) {
			this->entities[i]->render(this->shader_id); //-- shader id 1
		} else {
			this->entities[i]->render(this->shader_id2); //-- shader id 2
		}

	//-- Render light models
	for (int i = 0; i < (int)this->lightModels.size(); i++)
		this->lightModels[i]->render(this->shader_id);
}
