// Foggy.h
#include "Foggy.h"

#include <GL/glut.h>

using namespace std;

Foggy::Foggy() {
    this->mode = GL_EXP;

    this->density = 0.002;
    this->start = 5;
    this->end = 100;
}

void Foggy::render() {
    glFogi(GL_FOG_MODE, mode);
    glFogfv(GL_FOG_COLOR, foggy);
    glFogf(GL_FOG_DENSITY, density);
    glFogf(GL_FOG_START, start);
    glFogf(GL_FOG_END, end);

    glClearColor(foggy[0], foggy[1], foggy[2], foggy[3]);
}

void Foggy::setColor(GLfloat* color) { this->foggy[0] = color[0]; this->foggy[1] = color[1]; this->foggy[2] = color[2]; }
void Foggy::setMode(GLint mode) { this->mode = mode; }
void Foggy::setDensity(GLfloat density) { this->density = density; }
void Foggy::setStartEnd(GLfloat start, GLfloat end) { this->start = start; this->end = end; }

GLfloat Foggy::getDensity() { return density; }
