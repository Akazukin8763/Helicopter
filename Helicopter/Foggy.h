// Foggy.h
#pragma once
#ifndef FOGGY_H
#define FOGGY_H

#include <GL/glut.h>

class Foggy {
private:
	GLfloat foggy[4] = { 0.8f, 0.8f, 1.0f, 1.0f };

	GLint mode;

	GLfloat density;
	GLfloat start;
	GLfloat end;

public:
	Foggy();

	void render();

	void setColor(GLfloat* color);
	void setMode(GLint mode);
	void setDensity(GLfloat density);
	void setStartEnd(GLfloat start, GLfloat end);

	GLfloat getDensity();
};

#endif // FOGGY_H