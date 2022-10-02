// Materials.h
#pragma once
#ifndef MATERIALS_H
#define MATERIALS_H

#include <GL/glut.h>

// Materials Source
// http://devernay.free.fr/cours/opengl/materials.html

const GLfloat no_ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat no_specular[4] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat no_emission[4] = { 0.0, 0.0, 0.0, 1.0 };

// Brass
const GLfloat brass_ambient[4] = { 0.329412, 0.223529, 0.027451, 1.0 };
const GLfloat brass_diffuse[4] = { 0.780392, 0.568627, 0.113725, 1.0 };
const GLfloat brass_specular[4] = { 0.992157, 0.941176, 0.807843, 1.0 };
const GLfloat brass_shininess = 27.8974;

// Pearl
const GLfloat pearl_ambient[4] = { 0.25, 0.20725, 0.20725, 1.0 };
const GLfloat pearl_diffuse[4] = { 1, 0.829, 0.829, 1.0 };
const GLfloat pearl_specular[4] = { 0.296648, 0.296648, 0.296648, 1.0 };
const GLfloat pearl_shininess = 0.088 * 128;

// Chrome¡]»Ì¡^
const GLfloat chrome_ambient[4] = { 0.25, 0.25, 0.25, 1.0 };
const GLfloat chrome_diffuse[4] = { 0.4, 0.4, 0.4, 1.0 };
const GLfloat chrome_specular[4] = { 0.774597, 0.774597, 0.774597, 1.0 };
const GLfloat chrome_shininess = 0.6 * 128;

// Gold
const GLfloat gold_ambient[4] = { 0.24725, 0.1995, 0.0745, 1.0 };
const GLfloat gold_diffuse[4] = { 0.75164, 0.60648, 0.22648, 1.0 };
const GLfloat gold_specular[4] = { 0.628281, 0.555802, 0.366065, 1.0 };
const GLfloat gold_shininess = 0.4 * 128;

// White Rubber¡]¥Õ¾ó½¦¡^
const GLfloat rubber_white_ambient[4] = { 0.05, 0.05, 0.05, 1.0 };
const GLfloat rubber_white_diffuse[4] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat rubber_white_specular[4] = { 0.7, 0.7, 0.7, 1.0 };
const GLfloat rubber_white_shininess = 10.0;

// Green Rubber
const GLfloat rubber_green_ambient[4] = { 0.0, 0.05, 0.0, 1.0 };
const GLfloat rubber_green_diffuse[4] = { 0.4, 0.5, 0.4, 1.0 };
const GLfloat rubber_green_specular[4] = { 0.04, 0.7, 0.04,1.0 };
const GLfloat rubber_green_shininess = 10.0;

// White Plastic
const GLfloat plastic_white_ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat plastic_white_diffuse[4] = { 0.55, 0.55, 0.55, 1.0 };
const GLfloat plastic_white_specular[4] = { 0.7, 0.7, 0.7, 1.0 };
const GLfloat plastic_white_shininess = 0.25 * 128;

// Gray Plastic
const GLfloat plastic_gray_ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat plastic_gray_diffuse[4] = { 0.28, 0.28, 0.28, 1.0 };
const GLfloat plastic_gray_specular[4] = { 0.6, 0.6, 0.6, 1.0 };
const GLfloat plastic_gray_shininess = 0.25 * 128;

// Red Plastic
const GLfloat plastic_red_ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat plastic_red_diffuse[4] = { 0.5, 0.0, 0.0, 1.0 };
const GLfloat plastic_red_specular[4] = { 0.7, 0.6, 0.6, 1.0 };
const GLfloat plastic_red_shininess = 0.25 * 128;

// Green Plastic
const GLfloat plastic_green_ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat plastic_green_diffuse[4] = { 0.1, 0.35, 0.1, 1.0 };
const GLfloat plastic_green_specular[4] = { 0.45, 0.55, 0.45, 1.0 };
const GLfloat plastic_green_shininess = 0.25 * 128;

// Yellow Plastic
const GLfloat plastic_yellow_ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat plastic_yellow_diffuse[4] = { 0.35, 0.35, 0.1, 1.0 };
const GLfloat plastic_yellow_specular[4] = { 0.55, 0.55, 0.45, 1.0 };
const GLfloat plastic_yellow_shininess = 0.25 * 128;

// Black Plastic
const GLfloat plastic_black_ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat plastic_black_diffuse[4] = { 0.01, 0.01, 0.01, 1.0 };
const GLfloat plastic_black_specular[4] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat plastic_black_shininess = 0.25 * 128;

#endif // MATERIALS_H