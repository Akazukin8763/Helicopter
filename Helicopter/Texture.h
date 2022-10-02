// Texture.h
#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glut.h>

GLuint Create_Texture_Circle();
GLuint Create_Texture_Land();
GLuint Create_Texture_Star();
GLuint Create_Texture_Waterwave(int offset);

GLuint Create_Texture_Tree();
GLuint Create_Texture_Cloud();

GLuint LoadTexture(const char* filename);

#endif // TEXTURE_H