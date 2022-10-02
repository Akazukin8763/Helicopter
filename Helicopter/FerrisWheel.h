// FerrisWheel.h
#pragma once
#ifndef FERRISWHEEL_H
#define FERRISWHEEL_H

#include <GL/glut.h>

class FerrisWheel {
private:
	GLfloat __radius;
	int __n;

	GLfloat __angle;

	GLUquadricObj* cylinder = gluNewQuadric();

	// Center Light
	GLfloat __centerlight_position[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat __centerlight_direction[4] = { 0.0, 0.0, 1.0, 0.0 };
	GLfloat __centerlight_diffuse[4] = { 0.75164, 0.60648, 0.22648, 1.0 };
	GLfloat __centerlight_specular[4] = { 0.628281, 0.555802, 0.366065, 1.0 };
	GLfloat __centerlight_ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat __centerlight_cutoff = 180.0;
	GLfloat __centerlight_exponent = 50.0;

	// Carriage rgb
	int __rgb_counter = 0;
	GLfloat __carriage_rgb_emission[4] = { 1.0, 1.0, 1.0, 1.0 };

	void draw_carriage();

	void draw_torus();
	void draw_core(); // ³sµ²±ì + ¨®´[
	void draw_center();
	void draw_stand();

public:
	FerrisWheel(GLfloat radius, int n);

	void draw();

	void twinkling();
	void turnOffCenterLight() { glDisable(GL_LIGHT2); };
	void turnOnCenterLight() { glEnable(GL_LIGHT2); }

	void rotate(GLfloat rotate);
};

#endif // FERRISWHEEL_H