#ifndef __SHADER_H
#define __SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
    #include <OpenGL/gl3.h>
    #include <OpenGL/CGLTypes.h> 
    #include <OpenGL/CGLCurrent.h> 
#elif __linux__
    #include <GL/gl.h>
    #include <GL/glx.h>
#endif


class Shader
{
    public:
        GLuint Program;

        Shader();
        ~Shader();
        void setShader(const GLchar* vertexPath, const GLchar* fragmentPath);
        void useShader();
};

#endif