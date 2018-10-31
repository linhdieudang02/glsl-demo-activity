#ifndef EXAMPLEAPP_H
#define EXAMPLEAPP_H

#include <api/MinVR.h>
using namespace MinVR;

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#ifdef _WIN32
#include "GL/glew.h"
#include "GL/wglew.h"
#elif (!defined(__APPLE__))
#include "GL/glxew.h"
#endif

// OpenGL Headers
#if defined(WIN32)
#define NOMINMAX
#include <windows.h>
#include <GL/gl.h>
#elif defined(__APPLE__)
#define GL_GLEXT_PROTOTYPES
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#endif

#include <BasicGraphics.h>


class ExampleApp : public VRApp {
public:
    
    /** The constructor passes argc, argv, and a MinVR config file on to VRApp.
     */
	ExampleApp(int argc, char** argv);
    virtual ~ExampleApp();    
    
    /** RENDERING CALLBACKS **/
    virtual void onRenderGraphicsScene(const VRGraphicsState& state);
    virtual void onRenderGraphicsContext(const VRGraphicsState& state);
    
private:
    
    virtual void reloadShaders();
    
    basicgraphics::GLSLProgram _shader;
    std::unique_ptr<basicgraphics::Mesh> _mesh;
    std::shared_ptr<basicgraphics::Texture> _tex;
};


#endif //EXAMPLEAPP_H
