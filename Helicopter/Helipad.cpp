// Helipad.h
#include "Helipad.h"

#include <GL/glut.h>

#include "Materials.h"

using namespace std;

Helipad::Helipad() {
    //glEnable(GL_DEPTH_TEST);
}

void Helipad::draw_ground() {
    glNormal3f(0, 1, 0);

    // Ground
    //glColor3f(0.5f, 0.5f, 0.5f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, plastic_gray_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, plastic_gray_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, plastic_gray_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, plastic_gray_shininess);

    glBegin(GL_POLYGON);
        glVertex3f(-12.0f, 0.0f, 12.0f);
        glVertex3f(12.0f, 0.0f, 12.0f);
        glVertex3f(12.0f, 0.0f, -12.0f);
        glVertex3f(-12.0f, 0.0f, -12.0f);
    glEnd();

    // Pattern
    // Circle
    glPushMatrix();
        // Outer-Circle-1 White
        glMaterialfv(GL_FRONT, GL_AMBIENT, plastic_white_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, plastic_white_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, plastic_white_diffuse);
        glMaterialf(GL_FRONT, GL_SHININESS, plastic_white_shininess);

        glTranslated(0.0f, 0.001f, 0.0f);
        glPushMatrix();
            glRotatef(90, -1, 0, 0);
            gluDisk(circle, 0, 10, 32, 1);
        glPopMatrix();

        // Inner-Circle-1 Green
        glMaterialfv(GL_FRONT, GL_AMBIENT, plastic_green_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, plastic_green_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, plastic_green_diffuse);
        glMaterialf(GL_FRONT, GL_SHININESS, plastic_green_shininess);

        glTranslated(0.0f, 0.001f, 0.0f);
        glPushMatrix();
            glRotatef(90, -1, 0, 0);
            gluDisk(circle, 0, 9.75, 32, 1);
        glPopMatrix();

        // Outer-Circle-2 Yellow
        glMaterialfv(GL_FRONT, GL_AMBIENT, plastic_yellow_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, plastic_yellow_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, plastic_yellow_diffuse);
        glMaterialf(GL_FRONT, GL_SHININESS, plastic_yellow_shininess);

        glTranslated(0.0f, 0.001f, 0.0f);
        glPushMatrix();
            glRotatef(90, -1, 0, 0);
            gluDisk(circle, 0, 7.5, 32, 1);
        glPopMatrix();

        // Inner-Circle-2 Green
        glMaterialfv(GL_FRONT, GL_AMBIENT, plastic_green_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, plastic_green_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, plastic_green_diffuse);
        glMaterialf(GL_FRONT, GL_SHININESS, plastic_green_shininess);

        glTranslated(0.0f, 0.001f, 0.0f);
        glPushMatrix();
            glRotatef(90, -1, 0, 0);
            gluDisk(circle, 0, 7, 32, 1);
        glPopMatrix();
    glPopMatrix();

    // Mark-H
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, plastic_white_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, plastic_white_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, plastic_white_diffuse);
        glMaterialf(GL_FRONT, GL_SHININESS, plastic_white_shininess);

        glTranslated(0.0f, 0.005f, 0.0f);
        glNormal3f(0, 1, 0);

        glBegin(GL_POLYGON);
            glVertex3f(-4.0f, 0.0f, 4.0f);
            glVertex3f(4.0f, 0.0f, 4.0f);
            glVertex3f(4.0f, 0.0f, 2.0f);
            glVertex3f(-4.0f, 0.0f, 2.0f);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex3f(1.0f, 0.0f, 2.0f);
            glVertex3f(1.0f, 0.0f, -2.0f);
            glVertex3f(-1.0f, 0.0f, -2.0f);
            glVertex3f(-1.0f, 0.0f, 2.0f);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex3f(-4.0f, 0.0f, -2.0f);
            glVertex3f(4.0f, 0.0f, -2.0f);
            glVertex3f(4.0f, 0.0f, -4.0f);
            glVertex3f(-4.0f, 0.0f, -4.0f);
        glEnd();
    glPopMatrix();
}

void Helipad::draw_face(GLfloat height) {
    // Building-Face
    // 邊柱
    glMaterialfv(GL_FRONT, GL_AMBIENT, plastic_gray_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, plastic_gray_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, plastic_gray_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, plastic_gray_shininess);

    glNormal3f(0, 1, 0);

    // 邊柱-左
    glBegin(GL_POLYGON);
        //glNormal3f(0, 1, 0);

        glVertex3f(-12.0f, 0.0f, 12.0f);
        glVertex3f(-12.0f, -height, 12.0f);
        glVertex3f(-10.0f, -height, 12.0f);
        glVertex3f(-10.0f, 0.0f, 12.0f);
    glEnd();
    // 邊柱-右
    glBegin(GL_POLYGON);
        //glNormal3f(0, 0, 1);

        glVertex3f(10.0f, 0.0f, 12.0f);
        glVertex3f(10.0f, -height, 12.0f);
        glVertex3f(12.0f, -height, 12.0f);
        glVertex3f(12.0f, 0.0f, 12.0f);
    glEnd();
    // 邊柱-上
    glBegin(GL_POLYGON);
        //glNormal3f(0, 0, 1);

        glVertex3f(-10.0f, 0.0f, 12.0f);
        glVertex3f(-10.0f, -2.0f, 12.0f);
        glVertex3f(10.0f, -2.0f, 12.0f);
        glVertex3f(10.0f, 0.0f, 12.0f);
    glEnd();

    // 中心面
    //glMaterialfv(GL_FRONT, GL_AMBIENT, plastic_black_ambient);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, plastic_black_specular);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, plastic_black_diffuse);
    //glMaterialf(GL_FRONT, GL_SHININESS, plastic_black_shininess);

    glNormal3f(0, 1, 0);

    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-10.0f, -2.0f, 12.0f);

        glTexCoord2f(height / 5.0, 0.0);
        glVertex3f(-10.0f, -height, 12.0f);

        glTexCoord2f(height / 5.0, height / 5.0);
        glVertex3f(10.0f, -height, 12.0f);

        glTexCoord2f(0.0, height / 5.0);
        glVertex3f(10.0f, -2.0f, 12.0f);
    glEnd();
}

void Helipad::draw(GLfloat height) {
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPushMatrix();
        for (int i = 0; i < 4; i++) {
            glRotated(90, 0, 1, 0);
            draw_face(height);
        }
    glPopMatrix();

    draw_ground();
}