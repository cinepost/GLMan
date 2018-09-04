#include <boost/log/trivial.hpp>

#include "glman_lib/renderer/renderer.h"


Renderer::Renderer() { 
	CGLPixelFormatAttribute pixelFormatAttributes[4] = {
		kCGLPFAAccelerated,   // no software rendering
		kCGLPFAOpenGLProfile, // core profile with the version stated below
	 	(CGLPixelFormatAttribute) kCGLOGLPVersion_3_2_Core,
		(CGLPixelFormatAttribute) 0
	};

	CGLPixelFormatObj pixelFormat;
	CGLError errorCode;
	GLint num; // stores the number of possible pixel formats
	
	errorCode = CGLChoosePixelFormat( pixelFormatAttributes, &pixelFormat, &num );
	// add error checking here
	
	errorCode = CGLCreateContext( pixelFormat, NULL, &context ); // second parameter can be another context for object sharing
	// add error checking here
	
	CGLDestroyPixelFormat( pixelFormat );

	errorCode = CGLSetCurrentContext( context );
	// add error checking here

	BOOST_LOG_TRIVIAL(info) << "GLMan renderer initilized";
}

Renderer::~Renderer() {
	CGLSetCurrentContext( NULL );
	CGLDestroyContext( context );
	
	BOOST_LOG_TRIVIAL(info) << "GLMan renderer destroyed";
}