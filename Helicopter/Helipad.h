// Helipad.h
#pragma once
#ifndef HELIPAD_H
#define HELIPAD_H

#include <GL/glut.h>

class Helipad {
private:
	GLUquadricObj* circle = gluNewQuadric();

	void draw_ground();
	void draw_face(GLfloat height);

public:
	Helipad();

	void draw(GLfloat height);
};

#endif // HELIPAD_H