#include "ExampleApp.h"

#include <config/VRDataIndex.h>

using namespace basicgraphics;
using namespace std;
using namespace glm;

ExampleApp::ExampleApp(int argc, char** argv) : VRApp(argc, argv)
{
}

ExampleApp::~ExampleApp()
{
	shutdown();
}


void ExampleApp::onRenderGraphicsContext(const VRGraphicsState &renderState) {
    // This routine is called once per graphics context at the start of the
    // rendering process.  So, this is the place to initialize textures,
    // load models, or do other operations that you only want to do once per
    // frame.
    
	// Is this the first frame that we are rendering after starting the app?
    if (renderState.isInitialRenderCall()) {

		//For windows, we need to initialize a few more things for it to recognize all of the
		// opengl calls.
		#ifndef __APPLE__
			glewExperimental = GL_TRUE;
			GLenum err = glewInit();
			if (GLEW_OK != err)
			{
				std::cout << "Error initializing GLEW." << std::endl;
			}
		#endif     


        glEnable(GL_DEPTH_TEST);
        glClearDepth(1.0f);
        glDepthFunc(GL_LEQUAL);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glEnable(GL_MULTISAMPLE);

		// This sets the background color that is used to clear the canvas
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

		// This load shaders from disk, we do it once when the program starts up.
		reloadShaders();
    
        std::vector<Mesh::Vertex> cpuVertexArray;
        std::vector<int>             cpuIndexArray;
        std::vector<std::shared_ptr<Texture>> textures;
        
        vec3 normal(0,0,1);
        
        Mesh::Vertex vert;
        vert.position = vec3(0,0,0);
        vert.normal = normal;
        vert.texCoord0 = glm::vec2(0, 0);
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(0);
        
        vert.position = vec3(1,0,0);
        vert.normal = normal;
        vert.texCoord0 = glm::vec2(1, 0);
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(1);
        
        vert.position = vec3(0,1,0);
        vert.normal = normal;
        vert.texCoord0 = glm::vec2(0, 1);
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(2);
        
        const int numVertices = cpuVertexArray.size();
        const int cpuVertexByteSize = sizeof(Mesh::Vertex) * numVertices;
        const int cpuIndexByteSize = sizeof(int) * cpuIndexArray.size();
        _mesh.reset(new Mesh(textures, GL_TRIANGLES, GL_STATIC_DRAW, cpuVertexByteSize, cpuIndexByteSize, 0, cpuVertexArray, cpuIndexArray.size(), cpuIndexByteSize, &cpuIndexArray[0]));
        
        _tex = Texture::create2DTextureFromFile("tex.jpg");
        
        
    }
}

void ExampleApp::onRenderGraphicsScene(const VRGraphicsState &renderState) {
    // This routine is called once per eye/camera.  This is the place to actually
    // draw the scene.
    
	// clear the canvas and other buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Setup the view matrix to set where the camera is located in the scene
    glm::vec3 eye_world = glm::vec3(0, 0, 3);
    glm::mat4 view = glm::lookAt(eye_world, glm::vec3(0,0,0), glm::vec3(0,1,0));
    
    glm::mat4 model(1.0);
   
	// Setup the projection matrix so that things are rendered in perspective
	GLfloat windowHeight = renderState.index().getValue("FramebufferHeight");
	GLfloat windowWidth = renderState.index().getValue("FramebufferWidth");
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 0.01f, 100.0f);
	
	
    mat4 modelViewProjection = projection * view * model;
    
    _shader.use(); // Tell opengl we want to use this specific shader.
    _shader.setUniform("modelViewProjectionMatrix", modelViewProjection);
    _shader.setUniform("normalMatrix", view * transpose(inverse(model)));
    
    //TODO: Bind texture
    
    
    
    
    // Draw the mesh
    glBindVertexArray(_mesh->getVAOID());
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    

}

void ExampleApp::reloadShaders()
{
	_shader.compileShader("ColorShader.vert", GLSLShader::VERTEX);
	_shader.compileShader("ColorShader.frag", GLSLShader::FRAGMENT);
	_shader.link();
	_shader.use();
}
