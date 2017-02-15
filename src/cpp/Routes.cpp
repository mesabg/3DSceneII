#include <Routes.h>

Routes::Routes(string model, string texture) {
	this->model = model;
	this->texture = texture;
}

Routes::Routes() {

}

Routes::~Routes() {
	this->model.~basic_string();
	this->texture.~basic_string();
	return;
}
