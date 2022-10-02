// Billboard.h
#include "Billboard.h"

#include <GL/glut.h>

#include <bits/stdc++.h>

using namespace std;

Billboard::Billboard() {

}

void Billboard::setAxes() {
    glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);

    GLfloat w[3];
    w[0] = modelviewMatrix[2];
    w[1] = modelviewMatrix[8];
    w[2] = modelviewMatrix[10];

    GLfloat len = sqrt(w[0] * w[0] + w[2] * w[2]);
    a[0] = w[2] / len;
    a[1] = 0.0;
    a[2] = -w[0] / len;
    b[0] = 0.0;
    b[1] = 1.0;
    b[2] = 0.0;
}

void Billboard::draw(GLfloat x, GLfloat z, GLfloat width, GLfloat height) {

    float v0[3], v1[3], v2[3], v3[3];

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.5);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    /*----Compute the 4 vertices of the billboard ----*/
    v0[0] = x - (width / 2) * a[0];
    v0[1] = 0.0;
    v0[2] = z - (width / 2) * a[2];

    v1[0] = x + (width / 2) * a[0];
    v1[1] = 0.0;
    v1[2] = z + (width / 2) * a[2];

    v2[0] = x + (width / 2) * a[0];
    v2[1] = height;
    v2[2] = z + (width / 2) * a[2];

    v3[0] = x - (width / 2) * a[0];
    v3[1] = height;
    v3[2] = z - (width / 2) * a[2];

    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex3fv(v0);

        glTexCoord2f(1.0, 0.0);
        glVertex3fv(v1);

        glTexCoord2f(1.0, 1.0);
        glVertex3fv(v2);

        glTexCoord2f(0.0, 1.0);
        glVertex3fv(v3);
    glEnd();

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
}