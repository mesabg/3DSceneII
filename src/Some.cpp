
void Stage::buildShadowMap(){
	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	/*glGenFramebuffers(1, &this->shadowMapId);
	glBindFramebuffer(GL_FRAMEBUFFER, this->shadowMapId);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.*/

	//-- render
	//this->frameBufferObject->bindRefractionFrameBuffer();
	glm::vec3 lightInvDir = *(this->lightCollection->getEntity(0)->getTransformation()->getPosition());
	//vec3(16.0f, 18.5f, -6.8f);
	//glm::vec3(0.5f, 2, 2);
	// Compute the MVP matrix from the light's point of view
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-20, 20, -20, 20, -20, 20);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	//-- Render the model collection and light collection
	//this->frameBufferObject->bindImageFrameBuffer();
	//this->frameBufferObject->activeImageDepthTexture();
	//glBindFramebuffer(GL_FRAMEBUFFER, m_shadowMapFboId);
	


	/*GLuint m_shadowMapFboId, m_shadowMapTextureId;
	glGenFramebuffers(1, &m_shadowMapFboId);
	glBindFramebuffer(GL_FRAMEBUFFER, m_shadowMapFboId);
	glDrawBuffer(GL_NONE);

	glGenTextures(1, &m_shadowMapTextureId);
	glBindTexture(GL_TEXTURE_2D, m_shadowMapTextureId);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1440, 900, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_shadowMapTextureId, 0);*/

	/*GLuint color_tex, fb, depth_stencil_rb, depth_tex;
	glGenTextures(1, &color_tex);
	glBindTexture(GL_TEXTURE_2D, color_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//NULL means reserve texture memory, but texels are undefined
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 480, 320, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	//You must reserve memory for other mipmaps levels as well either by making a series of calls to
	//glTexImage2D or use glGenerateMipmapEXT(GL_TEXTURE_2D).
	//Here, we'll use :
	glGenerateMipmap(GL_TEXTURE_2D);



	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 480, 320, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	glGenTextures(1, &depth_tex);
	glBindTexture(GL_TEXTURE_2D, depth_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 256, 256, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);


	//-------------------------
	glGenFramebuffers(1, &fb);
	glBindFramebuffer(GL_FRAMEBUFFER, fb);
	//Attach 2D texture to this FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_tex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_tex, 0);*/
	
	/*

	//-------------------------
	glGenRenderbuffers(1, &depth_stencil_rb);
	glBindRenderbuffer(GL_RENDERBUFFER, depth_stencil_rb);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 480, 320);
	
	//-------------------------
	//Attach depth buffer to FBO
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_stencil_rb);
	
	//Also attach as a stencil
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth_stencil_rb);*/



	/*
	int msaa = 4;
	GLuint rboColorId;
	glGenRenderbuffers(1, &rboColorId);
	glBindRenderbuffer(GL_RENDERBUFFER, rboColorId);
	//glRenderbufferStorageMultisample(GL_RENDERBUFFER, 0, GL_RGB8, width, height);

	// create a 4x MSAA renderbuffer object for depthbuffer
	GLuint rboDepthId;
	glGenRenderbuffers(1, &rboDepthId);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepthId);
	//glRenderbufferStorageMultisample(GL_RENDERBUFFER, 0, GL_DEPTH_COMPONENT, width, height);

	// create a 4x MSAA framebuffer object
	GLuint fboMsaaId;
	glGenFramebuffers(1, &fboMsaaId);
	glBindFramebuffer(GL_FRAMEBUFFER, fboMsaaId);

	// attach colorbuffer image to FBO
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,       // 1. fbo target: GL_FRAMEBUFFER
		GL_COLOR_ATTACHMENT0, // 2. color attachment point
		GL_RENDERBUFFER,      // 3. rbo target: GL_RENDERBUFFER
		rboColorId);          // 4. rbo ID

							  // attach depthbuffer image to FBO
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,       // 1. fbo target: GL_FRAMEBUFFER
		GL_DEPTH_ATTACHMENT,  // 2. depth attachment point
		GL_RENDERBUFFER,      // 3. rbo target: GL_RENDERBUFFER
		rboDepthId);
		*/








	/*Intento con depth*/


	// get OpenGL info
	//glInfo glInfo;
	//glInfo.getInfo();
	//glInfo.printSelf();

	/*glClearColor(0, 0, 0, 0);                   // background color
	glClearStencil(0);                          // clear stencil buffer
	glClearDepth(1.0f);                         // 0 is near, 1 is far
	glDepthFunc(GL_LEQUAL);*/

	

	//glPushAttrib(GL_COLOR_BUFFER_BIT | GL_PIXEL_MODE_BIT); // for GL_DRAW_BUFFER and GL_READ_BUFFER
	//glDrawBuffer(GL_BACK);
	//glReadBuffer(GL_BACK);
	/*
	GLuint fboId, rboId;
	glGenFramebuffers(1, &fboId);
	glBindFramebuffer(GL_FRAMEBUFFER, fboId);

	// create a renderbuffer object to store depth info
	// NOTE: A depth renderable image should be attached the FBO for depth test.
	// If we don't attach a depth renderable image to the FBO, then
	// the rendering output will be corrupted because of missing depth test.
	// If you also need stencil test for your rendering, then you must
	// attach additional image to the stencil attachement point, too.
	glGenRenderbuffers(1, &rboId);
	glBindRenderbuffer(GL_RENDERBUFFER, rboId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 320, 320);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// attach a texture to FBO depth attachement point
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureId, 0);

	// attach a renderbuffer to depth attachment point
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER_EXT, rboId);

	//@@ disable color buffer if you don't attach any color buffer image,
	//@@ for example, rendering depth buffer only to a texture.
	//@@ Otherwise, glCheckFramebufferStatusEXT will not be complete.
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	*/

	glBindFramebuffer(GL_FRAMEBUFFER, fboId);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 680, 450);
	this->modelCollection->low_render(depthMVP, this->illuminationPrograms->at("Depth"));
	// draw a rotating teapot
	/*this->modelCollection->render(
		this->projection,
		this->camera,
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
		"Blinn-Phong" });*/

	// copy the framebuffer pixels to a texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1440, 900);

	glBindTexture(GL_TEXTURE_2D, textureId);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);


	
	//-------------------------
	//Does the GPU support current FBO configuration?
	/*GLenum status;
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	switch (status)
	{
	case GL_FRAMEBUFFER_COMPLETE:
		cout << "good\n";
	}*/
	//-------------------------
	//and now you can render to GL_TEXTURE_2D
	/*glBindFramebuffer(GL_FRAMEBUFFER, fboMsaaId);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//It's always a good idea to clear the stencil at the same time as the depth when the format is D24S8.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glViewport(0, 0, 680, 450);*/

	//-- render objects
	/*this->modelCollection->render(
		this->projection,
		this->camera,
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
		"Blinn-Phong" });*/
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//glViewport(0, 0, 1440, 900);


	//this->frameBufferObject->unbindCurrentFrameBuffer();

	//this->Send("texId", (void*)id);

	glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);
	glm::mat4 depthBiasMVP = biasMatrix*depthMVP;
	this->modelCollection->setShadow(depthBiasMVP, textureId);


	
	/*texture_program.enable();
	modelo = mat4(1.0f);
	vista = glm::lookAt(vec3(0.0f, 0.0f, 8.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	proyeccion = glm::perspective(45.0f, (float)480 / (float)480, 0.1f, 1000.0f);

	glUniformMatrix4fv(texture_program.getLocation("model"), 1, GL_FALSE, value_ptr(modelo));
	glUniformMatrix4fv(texture_program.getLocation("view"), 1, GL_FALSE, value_ptr(vista));
	glUniformMatrix4fv(texture_program.getLocation("projection"), 1, GL_FALSE, value_ptr(proyeccion));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glUniform1i(texture_program.getLocation("texture1"), 0);

	glBindVertexArray(planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	texture_program.disable();*/

	//glDeleteRenderbuffers(1, &depth_stencil_rb);
	//glDeleteFramebuffers(1, &fb);

	
	//this->frameBufferObject->unbindCurrentFrameBuffer();

	/*glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1440, 900);*/
						   // Always check that our framebuffer is ok
	/*if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;*/
}