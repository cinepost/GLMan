#ifndef __MATERIAL_H
#define __MATERIAL_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <tuple>

#ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
    #include <OpenGL/gl3.h>
    #include <OpenGL/CGLTypes.h> 
    #include <OpenGL/CGLCurrent.h> 
#elif __linux__
    #include <GL/gl.h>
    #include <GL/glx.h>
#endif

#include "glman_lib/renderer/texture.h"
#include "glman_lib/renderer/shader.h"


class Material
{
    public:
        GLuint matID;
        Shader matShader;
        std::vector<std::tuple<std::string, Texture>> texList;

        Material();
        ~Material();
        void addTexture(std::string uniformName, Texture texObj);
        void setShader(Shader& shader);
        void renderToShader();
};

#endif