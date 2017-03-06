#include <Camera.h>

void Camera::refresh() {
	this->target.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	this->target.y = sin(glm::radians(yaw));
	this->target.z = sin(glm::radians(pitch)) * cos(glm::radians(yaw));
	this->target = glm::normalize(this->target);

	//--this->view = glm::lookAt(this->position, this->position + this->target, this->up);
	this->view = glm::lookAt(this->position, this->target, this->up);
}

float Camera::calculateHorizontalDistance(){
	return this->distanceFromPlayer * glm::cos(glm::radians(this->pitch));
}

float Camera::calculateVerticalDistance(){
	return this->distanceFromPlayer * glm::sin(glm::radians(this->pitch));
}

void Camera::calculateCameraPossition(float horizontalDistance, float verticalDistance){
	float theta = /*this->player->getRotationY() +*/ this->angleAroundPlayer;
	float offsetX = horizontalDistance * glm::sin(glm::radians(theta));
	float offsetZ = horizontalDistance * glm::cos(glm::radians(theta));

	this->position.x = /*this->player->getPosition().x*/ 0.0f - offsetX;
	this->position.z = /*this->player->getPosition().z*/ 8.0f - offsetZ;
	this->position.y = /*this->player->getPosition().y*/ 6.0f + verticalDistance;
	//this->target = /*this->position - */this->player->getPosition();

	this->speed = 0.2f;
}

Camera::Camera() {
	this->position = vec3(3.0f, 3.0f, 10.0f);
	this->target = vec3(0.0f, 0.0f, 0.0f);
	this->up = vec3(0.0f, 1.0f, 0.0f);
	this->player = NULL;

	/*Setting variables*/
	this->distanceFromPlayer = 50.0f;
	this->angleAroundPlayer = 0.0f;
	this->pitch = 20.0f;
	this->yaw = 0.0f;
	this->roll = 0.0f;

	this->refresh();
}

Camera::Camera(Transformation * player){
	this->position = vec3(0.0f, 0.0f, 20.0f);
	this->target = vec3(0.0f, 0.0f, -1.0f);
	this->up = vec3(0.0f, 1.0f, 0.0f);
	this->player = player;

	/*Setting variables*/
	this->distanceFromPlayer = 40.0f;
	this->angleAroundPlayer = 0.0f;
	this->pitch = 30.0f;
	this->yaw = 0.0f;

	this->refresh();
}

Camera::Camera(vec3 position, vec3 target, vec3 up) {
	this->position = position;
	this->target = target;
	this->up = up;
	this->refresh();
}

Camera::Camera(vec3 position, float pitch, float yaw, vec3 up){
	this->position = position;
	this->pitch = pitch;
	this->yaw = yaw;
	this->up = up;
	this->refresh();
}

Camera::~Camera() {

}

mat4 Camera::getMatrix() {
	return this->view;
}

mat4 * Camera::getView(){
	return &this->view;
}

vec3 Camera::getPosition() {
	return this->position;
}

vec3 Camera::getTarget() {
	return this->target;
}

vec3 Camera::getUp() {
	return this->up;
}

void Camera::setPosition(vec3 position) {
	this->position = position;
	this->refresh();
}

void Camera::setPositionAndTarget(vec3 position, vec3 target) {
	this->position = position;
	this->target = target;
	this->refresh();
}

void Camera::setTarget(vec3 target) {
	this->target = target;
	this->refresh();
}

void Camera::setUp(vec3 up) {
	this->up = up;
	this->refresh();
}

void Camera::setPitchYaw(float pitch, float yaw){
	this->pitch = pitch;
	this->yaw = yaw;
	this->refresh();
}

void Camera::addPosition(vec3 position) {
	this->position += position;
	this->refresh();
}

void Camera::addPositionAndTarget(vec3 position, vec3 target) {
	this->position += position;
	this->target += target;
	this->refresh();
}

void Camera::addTarget(vec3 target) {
	this->target += target;
	this->refresh();
}

void Camera::addUp(vec3 up) {
	this->up += up;
	this->refresh();
}

void Camera::calculatePitch(int button, int action, int x, int y) {
	//--if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		//--this->pitch -= glm::radians((float)y) * glm::radians(this->speed);
		this->pitch -= glm::radians((float)y) * 0.1f;
}

void Camera::calculateAngleAroundPlayer(int button, int action, int x, int y){
	//--if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		//this->angleAroundPlayer -= glm::radians((float)x) * glm::radians(this->speed);
		this->angleAroundPlayer -= glm::radians((float)x) * 0.1f;
}

void Camera::bind(CGLSLProgram * shader){
	//shader->enable();
	glUniform3f(
		glGetUniformLocation(shader->getProgramID(), "u_camera_position"),
		(GLfloat)position.x,
		(GLfloat)position.y,
		(GLfloat)position.z);
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "u_view_matrix"), 1, GL_FALSE, &(this->getMatrix())[0][0]);
	//shader->disable();
}

void Camera::move(){
	this->calculateCameraPossition(this->calculateHorizontalDistance(), this->calculateVerticalDistance());
	this->yaw = 180.0f - (this->player->getRotationY() - this->angleAroundPlayer);
	this->refresh();
}

void Camera::calculateZoom(int scroll) {
	this->distanceFromPlayer -= (scroll * 0.9f);
}