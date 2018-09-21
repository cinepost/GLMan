#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
    #include <OpenGL/gl3.h>
    #include <OpenGL/glext.h>
    #include <OpenGL/CGLTypes.h> 
    #include <OpenGL/CGLCurrent.h> 
#elif __linux__
    #include <GL/gl.h>
    #include <GL/glx.h>
    #include <GL/glext.h>
#endif


class Texture
{
    public:
        GLuint texID, texWidth, texHeight, texComponents;
        GLfloat anisoFilterLevel;
        GLenum texType, texInternalFormat, texFormat;
        std::string texName;

        Texture();
        ~Texture();
        void setTexture(const char* texPath, std::string texName, bool texFlip);
        void setTextureHDR(const char* texPath, std::string texName, bool texFlip);
		void setTextureHDR(GLuint width, GLuint height, GLenum format, GLenum internalFormat, GLenum type, GLenum minFilter);
        void setTextureCube(std::vector<const char*>& faces, bool texFlip);
        void setTextureCube(GLuint width, GLenum format, GLenum internalFormat, GLenum type, GLenum minFilter);
        void computeTexMipmap();
        GLuint getTexID();
        GLuint getTexWidth();
        GLuint getTexHeight();
        std::string getTexName();
        void useTexture();
};

#endif