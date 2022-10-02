// Axis.h
#pragma once
#ifndef AXIS_H
#define AXIS_H

#include <GL/glut.h>

class Axis {
private:
	GLfloat flr_diffuse[4] = { 0.60, 0.60, 0.60, 1.0 };
	GLfloat flr_ambient[4] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat flr_specular[4] = { 0.0, 0.0, 0.0, 1.0 };

public:
	Axis();

	void draw_axis(GLfloat x, GLfloat y, GLfloat z);
	void draw_ground(GLfloat length, GLfloat width);
	void draw_skydome(GLfloat x, GLfloat y, GLfloat z, GLfloat range, GLfloat weak);
};

#endif // AXIS_H