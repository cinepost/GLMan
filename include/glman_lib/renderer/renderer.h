#ifndef __Renderer_h__
#define __Renderer_h__

#include <iostream>
#include <string>
#include <map>
#include <vector>

#ifdef __APPLE__
	#include <OpenGL/OpenGL.h>
	#include <OpenGL/gl3.h>
	#include <OpenGL/CGLTypes.h> 
	#include <OpenGL/CGLCurrent.h> 
#elif __linux__
	#include <GL/gl.h>
	#include <GL/glx.h>
#endif

class Renderer {
    public:
    	Renderer();
    	~Renderer();
		
	private:
		CGLContextObj context;
};

#endif