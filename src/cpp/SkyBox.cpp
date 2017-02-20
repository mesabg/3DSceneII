#include <SkyBox.h>
#include <iostream>
using std::cout;
using std::endl;

void SkyBox::generateVertexes(){
	this->glVBO = {
		-SIZE, SIZE, -SIZE,
		-SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, SIZE, -SIZE,
		-SIZE, SIZE, -SIZE,

		-SIZE, -SIZE, SIZE,
		-SIZE, -SIZE, -SIZE,
		-SIZE, SIZE, -SIZE,
		-SIZE, SIZE, -SIZE,
		-SIZE, SIZE, SIZE,
		-SIZE, -SIZE, SIZE,

		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, SIZE,
		SIZE, SIZE, SIZE,
		SIZE, SIZE, SIZE,
		SIZE, SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,

		-SIZE, -SIZE, SIZE,
		-SIZE, SIZE, SIZE,
		SIZE, SIZE, SIZE,
		SIZE, SIZE, SIZE,
		SIZE, -SIZE, SIZE,
		-SIZE, -SIZE, SIZE,

		-SIZE, SIZE, -SIZE,
		SIZE, SIZE, -SIZE,
		SIZE, SIZE, SIZE,
		SIZE, SIZE, SIZE,
		-SIZE, SIZE, SIZE,
		-SIZE, SIZE, -SIZE,

		-SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE, SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE, SIZE,
		SIZE, -SIZE, SIZE };
}

void SkyBox::initShaderProgram(){
	this->shader = new CGLSLProgram();
	this->shader->loadShader("../src/shaders/SkyBox.vert", CGLSLProgram::VERTEX);
	this->shader->loadShader("../src/shaders/SkyBox.frag", CGLSLProgram::FRAGMENT);
	this->shader->create_link();
}

void SkyBox::initVBO(){
	// -- Data
	glGenVertexArrays(1, &(this->glVAO_dir));
	glBindVertexArray(this->glVAO_dir);
	glBindBuffer(GL_ARRAY_BUFFER, this->glVAO_dir);
	glBufferData(GL_ARRAY_BUFFER, (this->glVBO.size()) * sizeof(GLfloat), &(this->glVBO[0]), GL_STATIC_DRAW);
	// -- Vertexes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glBindVertexArray(0);
}

void SkyBox::initTextures(vector<string> *textureFiles){
	glGenTextures(1, &this->textureID);
	glActiveTexture(GL_TEXTURE0);
	
	int width, height;
	unsigned char* image;

	this->textureID = SOIL_load_OGL_cubemap(
		textureFiles->at(0).c_str(),
		textureFiles->at(1).c_str(),
		textureFiles->at(2).c_str(),
		textureFiles->at(0).c_str(),
		textureFiles->at(0).c_str(),
		textureFiles->at(0).c_str(),
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
	);
	if (!this->textureID) {
		cout << "Ha ocurrido un error\n";
		exit(0);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

SkyBox::SkyBox() {

}

SkyBox::SkyBox(vector<string> textureFiles, mat4 *projection, mat4 *view){
	this->projection = projection;
	this->view = view;
	cout << "SkyBox:: Initializing shader program...\n";
	this->initShaderProgram();
	cout << "SkyBox:: Shaders done, generating vertexes..\n";
	this->generateVertexes();
	cout << "SkyBox:: Vertexes generated, initializing VAO...\n";
	this->initVBO();
	cout << "SkyBox:: VAO initialized, initializing textures..\n";
	this->initTextures(&textureFiles);
	cout << "SkyBox:: Textures initialized. SkyBox:: Ready\n";
	/*glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/
}

SkyBox::~SkyBox() {

}

void SkyBox::render(){
	this->shader->enable();
	
	//-- Bind Uniforms
	mat4 _view = *(this->view);
	mat4 _projection = *(this->projection);
	glUniformMatrix4fv(glGetUniformLocation(this->shader->getProgramID(), "u_view_matrix"), 1, GL_FALSE, &_view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(this->shader->getProgramID(), "u_projection_matrix"), 1, GL_FALSE, &_projection[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);
	glUniform1i(glGetUniformLocation(this->shader->getProgramID(), "u_cube_map"), 0);
	glBindVertexArray(this->glVAO_dir);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	this->shader->disable();
}