#include <SkyBox.h>

SkyBox::SkyBox() {

}

SkyBox::SkyBox(vector<string> textureFiles){
	glGenTextures(1, &this->textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);
	int width, height;
	unsigned char* image;
	for (int i = 0; i < 6; i++){
		image = SOIL_load_image(textureFiles[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glActiveTexture(0);
}

SkyBox::~SkyBox() {

}

void SkyBox::render(){

}
