// Billboard.h
#pragma once
#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <GL/glut.h>

class Billboard {
private:
	GLfloat modelviewMatrix[16] = { 0 };
	GLfloat a[3] = { 0 };
	GLfloat b[3] = { 0, 1, 0 };

public:
	Billboard();

	void setAxes();

	void draw(GLfloat x, GLfloat z, GLfloat width, GLfloat height);
};

#endif // BILLBOARD_H