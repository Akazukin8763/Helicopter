// Helicopter.h
#pragma once
#ifndef HELICOPTER_H
#define HELICOPTER_H

#include <GL/glut.h>

class Helicopter {
private:
	// Generate by SAMPLE_CODE
	float points[8][3] = { {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 0.0, 1.0},
							{0.0, 1.0, 0.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0} };
	int face[6][4] = { {0, 1, 2, 3}, {7, 6, 5, 4}, {0, 4, 5, 1},
						{1, 5, 6, 2}, {3, 2, 6, 7}, {0, 3, 7, 4} };
	float  normal[6][4] = { {0.0, -1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, -1.0},
							{1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {-1.0, 0.0, 0.0} };

	GLfloat __angleBlade;
	GLfloat __angleBodyFront;
	GLfloat __angleBodySide;

	GLfloat __angle;

	GLfloat __camera_x;
	GLfloat __camera_y;
	GLfloat __camera_z;

	GLfloat __translate_x;
	GLfloat __translate_y;
	GLfloat __translate_z;

	GLUquadricObj* circle;
	GLUquadricObj* sphere;
	GLUquadricObj* cylinder;

	int __front;
	int __side;

	// Search Light
	GLfloat __searchlight_position[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat __searchlight_direction[4] = { -1.0, 0.0, 0.0, 0.0 };
	GLfloat __searchlight_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat __searchlight_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat __searchlight_ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat __searchlight_cutoff = 30.0;
	GLfloat __searchlight_exponent = 64.0;

	// Helicopter
	void draw_cube();
	void draw_cylinder();
	void draw_sphere();

	void draw_blade();
	void draw_tripod();

	void draw_searchlight();

public:
	const int TIMES = 33; //ms

	const GLfloat UNIT_DISTANCE = 0.2f;

	const int MOVE_FRONT = 0x01;
	const int MOVE_BACK = 0x02;
	const int MOVE_RIGHT = 0x03;
	const int MOVE_LEFT = 0x04;

	const int MAN = 0x11;
	const int AUTO = 0x12;

	Helicopter();

	//void display();
	void draw();

	// Getter & Setter
	GLfloat* getPosition();
	GLfloat getAngle();

	void setCamera(GLfloat pitch, GLfloat yaw, GLfloat radius);
	GLfloat* getCamera();

	void setSearchlightColor(GLfloat* color);
	GLfloat* getSearchlightColor();

	void setSearchlightDirectionV(GLfloat v); // Vertical
	GLfloat getSearchlightDirectionV();
	void setSearchlightDirectionH(GLfloat h); // Horizontal
	GLfloat getSearchlightDirectionH();

	void setSearchlightCutoff(GLfloat cutoff);
	GLfloat getSearchlightCutoff();

	// Operation
	void rotate(GLfloat angle);
	void translate(GLfloat translate_x, GLfloat translate_y, GLfloat translate_z);

	void initCoordinate();

	void rotateBlade(GLfloat angle);
	void moveForward(GLfloat distance);
	void moveForward(GLfloat distance, int front);
	void moveForward(GLfloat distance, int front, int side);

	//void autoTakeOff();
	//void autoLanding();
};

#endif // HELICOPTER_H