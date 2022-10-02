// Axis.h
#include "Axis.h"

#include <GL/glut.h>

#include <bits/stdc++.h>
#include "Materials.h"

using namespace std;

Axis::Axis() {
    glEnable(GL_DEPTH_TEST);
}

void Axis::draw_axis(GLfloat x, GLfloat y, GLfloat z) {
    glDisable(GL_DEPTH_TEST);

    glPushMatrix();
        glScaled(x, y, z);

        glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 0.0f); // X-axis Red
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);

            glColor3f(0.0f, 1.0f, 0.0f); // Y-axis Green
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);

            glColor3f(0.0f, 0.0f, 1.0f); // Z-axis Blue
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 1.0f);
        glEnd();

        glColor3f(1.0f, 1.0f, 1.0f);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
}

void Axis::draw_ground(GLfloat length, GLfloat width) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glMaterialfv(GL_FRONT, GL_AMBIENT, rubber_green_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, rubber_green_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, rubber_green_shininess);

    glNormal3f(0, 1, 0);

    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(length / 2, 0, width / 2);

        glTexCoord2f(0.0, 8.0);
        glVertex3f(length / 2, 0, -width / 2);

        glTexCoord2f(8.0, 8.0);
        glVertex3f(-length / 2, 0, -width / 2);

        glTexCoord2f(8.0, 0.0);
        glVertex3f(-length / 2, 0, width / 2);
    glEnd();
}

void Axis::draw_skydome(GLfloat x, GLfloat y, GLfloat z, GLfloat range, GLfloat weak) {
    GLfloat width = range * 3;
    GLfloat unit = width / 50; // 設基本單位為 50

    glPushMatrix();
        glNormal3f(0, 1, 0);

        GLfloat slice = width * 2 / 20;
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                glBegin(GL_POLYGON);
                    glTexCoord2f(0.0, 0.0);
                    glVertex3f(width - i * slice, 0, width - j * slice);

                    glTexCoord2f(0.0, unit);
                    glVertex3f(width - i * slice, 0, width - (j + 1) * slice);

                    glTexCoord2f(unit, unit);
                    glVertex3f(width - (i + 1) * slice, 0, width - (j + 1) * slice);

                    glTexCoord2f(unit, 0.0);
                    glVertex3f(width - (i + 1) * slice, 0, width - j * slice);
                glEnd();
            }
        }
        /*glBegin(GL_POLYGON);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(width, 0, width);

            glTexCoord2f(0.0, unit);
            glVertex3f(width, 0, -width);

            glTexCoord2f(unit, unit);
            glVertex3f(-width, 0, -width);

            glTexCoord2f(unit, 0.0);
            glVertex3f(-width, 0, width);
        glEnd();*/

        glTranslated(x, 0, z);

        GLUquadricObj* sphere = gluNewQuadric();
        gluQuadricNormals(sphere, GLU_SMOOTH);
        gluQuadricOrientation(sphere, GLU_INSIDE);

        GLfloat sky[4] = { 135 / 255.0 * weak, 206 / 255.0 * weak, 235 / 255.0 * weak, 1.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, sky);
        glMaterialfv(GL_FRONT, GL_SPECULAR, sky);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, sky);
        glMaterialf(GL_FRONT, GL_SHININESS, 128);

        gluSphere(sphere, range * 0.9, 160, 50);

        GLfloat recover[4] = { 1.0,  1.0,  1.0, 1.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, recover);
        glMaterialfv(GL_FRONT, GL_SPECULAR, recover);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, recover);
        glMaterialf(GL_FRONT, GL_SHININESS, 0);
    glPopMatrix();
}