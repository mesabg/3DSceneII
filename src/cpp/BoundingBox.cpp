#include <BoundingBox.h>
#include <iostream>

BoundingBox::BoundingBox() {

}

BoundingBox::BoundingBox(glm::vec3 center){
	this->center = center;
}

BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max){
	this->setBorder(min, max);

	//-- Saving vertices
	this->vertices = new vector<vec3>(8, vec3());
	this->vertices->at(0) = vec3(max.x, max.y, max.z);
	this->vertices->at(1) = vec3(max.x, max.y, min.z);
	this->vertices->at(2) = vec3(max.x, min.y, max.z);
	this->vertices->at(3) = vec3(max.x, min.y, min.z);
	this->vertices->at(4) = vec3(min.x, max.y, max.z);
	this->vertices->at(5) = vec3(min.x, max.y, min.z);
	this->vertices->at(6) = vec3(min.x, min.y, max.z);
	this->vertices->at(7) = vec3(min.x, min.y, min.z);

	//-- Saving faces
	this->faces = new vector<vec4>(6, vec4());
	this->faces->at(0) = vec4(0, 1, 2, 3);
	this->faces->at(1) = vec4(0, 1, 2, 3);
	this->faces->at(2) = vec4(0, 1, 2, 3);
	this->faces->at(3) = vec4(0, 1, 2, 3);
	this->faces->at(4) = vec4(0, 1, 2, 3);
	this->faces->at(5) = vec4(0, 1, 2, 3);

	//-- Saving normals
	this->normals = new vector<vec3>(6, vec3());
	for (int i = 0; i < 6; i++)
		this->normals->at(i) = glm::cross(this->vertices->at(this->faces->at(i).x) - this->vertices->at(this->faces->at(i).y), this->vertices->at(this->faces->at(i).z) - this->vertices->at(this->faces->at(i).z));

	//-- Calculatin Center
	this->center = (this->min + this->max) / 2.0f;
}

BoundingBox::~BoundingBox() {}

void BoundingBox::move(mat4 transformation){
	this->min = vec3(transformation * vec4(this->min, 1.0f));
	this->max = vec3(transformation * vec4(this->max, 1.0f));
	this->center = (this->min + this->max) / 2.0f;
	//std::cout << this->center.x << " " << this->center.y << " " << this->center.z << std::endl;
}

bool BoundingBox::checkIntersection(vec3 parametric){
	//-- Build normal vector for each plane
	vector<vec3> *normal = new vector<vec3>{ vec3(), vec3(), vec3(), vec3(), vec3(), vec3() };

	return false;
}

glm::vec3 BoundingBox::getCenter(){
	return this->center;
}

void BoundingBox::setBorder(vec3 min, vec3 max){
	this->min = min;
	this->max = max;
}
