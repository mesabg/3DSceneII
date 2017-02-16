#include <ConcreteRenderController.h>

double ConcreteRenderController::lastFrameTime = ConcreteRenderController::getCurrentTime();
double ConcreteRenderController::delta = 0.0f;

ConcreteRenderController::ConcreteRenderController() {
	this->gui = GUI::Instance(this);
	this->illuminationPrograms = new map<string, CGLSLProgram*>();
	this->illuminationProgram = NULL;
	this->illuminationProgram2 = NULL;
	this->initGLSLPrograms();
	this->stage = Stage::Instance(this);
}

ConcreteRenderController::ConcreteRenderController(const float width, const float height) {
	//-- Initializing complete GUI 
	this->gui = GUI::Instance(this, (int)width, (int)height);
	this->sideBar = SideBar::Instance(this);

	//-- Initializing Shading Programs
	this->illuminationPrograms = new map<string, CGLSLProgram*>();
	this->illuminationProgram = NULL;
	this->illuminationProgram2 = NULL;
	this->initGLSLPrograms();

	//-- Initializing Stage
	this->stage = Stage::Instance(this);
	this->stage->Notify("InitSideBar", NULL);
	this->stage->Notify("width/height", (void*)(new float[2]{ width, height }));
	this->stage->Notify("init VBOs", NULL);
	this->stage->Notify("shader id", (void*)this->illuminationProgram->getProgramID());
	this->stage->Notify("shader id2", (void*)this->illuminationProgram2->getProgramID());

	//-- Reshape screen
	this->gui->reshape(this->gui->getWindow(), (int)width, (int)height);
	this->sideBar->reshape((int)width, (int)height);
}

ConcreteRenderController::~ConcreteRenderController() {
	//-- Kill Everything
}

void ConcreteRenderController::Send(string message, void* data, RenderColleague* renderColleague) {
	if (message == "Reshape" && renderColleague == this->gui) {
		this->stage->getProjection()->setAspectRatio(((float*)data)[0] / ((float*)data)[1]);
		this->sideBar->reshape((int)((float*)data)[0], (int)((float*)data)[1]);
	}

	//-- Main Object Initializing
	if (message == "MainObject" && renderColleague == this->stage) {
		this->sideBar->setSelectModelTarget(this->stage->getSelectedModelIndex());
		this->sideBar->setSelectLightTarget(this->stage->getSelectedLightIndex());
		this->sideBar->bindPrincipal();
	}

	//-- Event processing
	if (message == "eventKeyPressed" && renderColleague == this->gui)
		this->stage->Notify(message, data);

	if (message == "eventScroll" && renderColleague == this->gui)
		this->stage->Notify(message, data);

	if (message == "mouseButton" && renderColleague == this->gui)
		this->stage->Notify(message, data);

	//-- Options
	if (message == "SendSelectedModelProperties" && renderColleague == this->sideBar)
		this->sideBar->setModel( this->stage->getSelectedModel() );

	if (message == "SendSelectedLightProperties" && renderColleague == this->sideBar)
		this->sideBar->setModel( this->stage->getSelectedLight() );

	//-- Animation
	if (message == "Animate" && renderColleague == this->sideBar)
		this->stage->Notify(message, data);
}

void ConcreteRenderController::render() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//-- SkyBox

	//-- Render the stage
	this->illuminationProgram->enable();
	this->stage->render();
	this->illuminationProgram->disable();

	//-- Update Side Bar
	this->sideBar->update();

	double currentFrameTime = getCurrentTime();
	delta = (currentFrameTime - lastFrameTime)/1000.0f;
	lastFrameTime = currentFrameTime;
}

void ConcreteRenderController::initGLSLPrograms() {
	/*Graphic Card Info*/
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	/*Structure to initialize*/
	/*vector< map<string, string>* > *routes = new vector< map<string, string>* >({
		new map<string, string>({ { "name", "Phong" }, { "vertex", "../src/shaders/Phong.vert" }, { "fragment", "../src/shaders/Phong.frag" } } ),
		new map<string, string>({ { "name", "Blinn-Phong" },{ "vertex", "../src/shaders/Phong.vert" }, { "fragment", "../src/shaders/Phong.frag" } }),
		new map<string, string>({ { "name", "Oren-Nayar" },{ "vertex", "../src/shaders/Phong.vert" }, { "fragment", "../src/shaders/Phong.frag" } }),
		new map<string, string>({ { "name", "Cook-Torrance" },{ "vertex", "../src/shaders/Phong.vert" }, { "fragment", "../src/shaders/Phong.frag" } })
	});*/

	/*Initialize Shader Programs*/
	/*std::vector< map<string, string>* >::iterator programRoute;
	for (programRoute = routes->begin(); programRoute != routes->end(); programRoute++){
		std::cout << "\nLoading " << (*programRoute)->at("name") << " shading program...\n";

		this->illuminationPrograms->insert_or_assign(
			(*programRoute)->at("name"),
			new CGLSLProgram(this)
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
	}*/

	this->illuminationProgram = new CGLSLProgram();
	this->illuminationProgram->loadShader("../src/shaders/Vertex1.vert", CGLSLProgram::VERTEX);
	this->illuminationProgram->loadShader("../src/shaders/Vertex2.vert", CGLSLProgram::VERTEX);
	this->illuminationProgram->loadShader("../src/shaders/BlinnPhong.frag", CGLSLProgram::FRAGMENT);
	this->illuminationProgram->create_link();



	this->illuminationProgram2 = new CGLSLProgram();
	this->illuminationProgram2->loadShader("../src/shaders/byVertexLightning.vert", CGLSLProgram::VERTEX);
	this->illuminationProgram2->loadShader("../src/shaders/byVertexLightning.frag", CGLSLProgram::FRAGMENT);
	this->illuminationProgram2->create_link();
}


double ConcreteRenderController::getCurrentTime(){
	return glfwGetTime()*1000/*/glfwGetTimerValue()*/;
}

double ConcreteRenderController::getFrameTimeSeconds(){
	return delta;
}

int ConcreteRenderController::infinity() {
	while (!glfwWindowShouldClose(this->gui->getWindow())) {
		this->render();
		glfwSwapBuffers(this->gui->getWindow());
		glfwPollEvents();
	}
	return EXIT_SUCCESS;
}

int ConcreteRenderController::finish() {
	this->gui->Destroy();
	this->sideBar->Destroy();
	return EXIT_SUCCESS;
}