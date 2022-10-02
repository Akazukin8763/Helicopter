// FerrisWheel.h
#include "FerrisWheel.h"

#define _USE_MATH_DEFINES

#include <bits/stdc++.h>
#include <GL/glut.h>

#include "Materials.h"

using namespace std;

// 鑽戒旅館
//GLUquadricObj* FerrisWheel::cylinder = gluNewQuadric();

void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC) {
    float tStep = (M_PI) / (float)uiSlices;
    float sStep = (M_PI) / (float)uiStacks;
    for (float t = -M_PI / 2; t <= (M_PI / 2) + .0001; t += tStep) {
        glBegin(GL_TRIANGLE_STRIP);
        for (float s = -M_PI; s <= M_PI + .0001; s += sStep) {
            glVertex3f(fA * cos(t) * cos(s), fB * cos(t) * sin(s), fC * sin(t));
            glVertex3f(fA * cos(t + tStep) * cos(s), fB * cos(t + tStep) * sin(s), fC * sin(t + tStep));
        }
        glEnd();
    }
}

/*FerrisWheel::FerrisWheel() : super(24, 15) {
}*/
FerrisWheel::FerrisWheel(GLfloat radius, int n) {
    __radius = radius;
    __n = n;

    __angle = 0.0f;

    gluQuadricNormals(cylinder, GLU_SMOOTH);
}

void FerrisWheel::draw_carriage() {
    glPushMatrix();
        // 底
        glBegin(GL_POLYGON);
            glNormal3f(0, -1, 0);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(-1, 0, 1.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-1, 0, -1.5);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(1, 0, -1.5);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(1, 0, 1.5);
        glEnd();

        // 頂
        glBegin(GL_POLYGON);
            glNormal3f(0, 1, 0);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(1, 1.8, 1.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(1, 1.8, -1.5);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(-1, 1.8, -1.5);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(-1, 1.8, 1.5);
        glEnd();

        // 四面
        glBegin(GL_POLYGON); // 左
            glNormal3f(0, 0, -1);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(1, 0, 1.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(1, 1.8, 1.5);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(-1, 1.8, 1.5);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(-1, 0, 1.5);
        glEnd();

        glBegin(GL_POLYGON); // 右
            glNormal3f(0, 0, 1);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(-1, 0, -1.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-1, 1.8, -1.5);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(1, 1.8, -1.5);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(1, 0, -1.5);
        glEnd();

        glBegin(GL_POLYGON); // 前
            glNormal3f(-1, 0, 0);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(1, 0, -1.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(1, 1.8, -1.5);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(1, 1.8, 1.5);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(1, 0, 1.5);
        glEnd();

        glBegin(GL_POLYGON); // 後
            glNormal3f(1, 0, 0);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(-1, 0, 1.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-1, 1.8, 1.5);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(-1, 1.8, -1.5);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(-1, 0, -1.5);
        glEnd();
    glPopMatrix();
}

void FerrisWheel::draw_torus() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, pearl_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, pearl_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pearl_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, pearl_shininess);

    //glNormal3f(0, 1, 0);

    glPushMatrix();
        glTranslated(0, 0, 3);
        glutSolidTorus(1, __radius, 8, __n);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0, 0, -3);
        glutSolidTorus(1, __radius, 8, __n);
    glPopMatrix();
}

void FerrisWheel::draw_core() {
    GLfloat angle = 360.0 / __n; // 內角
    GLfloat length = sqrt(2.0 * __radius * __radius * (1 - cos(2 * M_PI / __n))); // 邊

    GLfloat length_cross = sqrt(length * length + 6 * 6);
    GLfloat cos_theta = (length_cross * length_cross + length * length - 6 * 6) / (2 * length_cross * length); // 餘弦定理
    GLfloat angle_cross = acos(cos_theta) * 180 / M_PI;

    GLfloat angle_carriage = 55;
    GLfloat length_cross_carriage = (length / 2) / cos(angle_carriage * M_PI / 180); // secant
    GLfloat length_straight_carriage = (length / 2) * tan(angle_carriage * M_PI / 180); // 用在位置

    for (int i = 0; i < __n; i++) {
        // 支撐
        GLfloat connect_x = __radius * cos(angle * M_PI / 180.0 * i);
        GLfloat connect_y = __radius * sin(angle * M_PI / 180.0 * i);

        glMaterialfv(GL_FRONT, GL_AMBIENT, pearl_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, pearl_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, pearl_diffuse);
        glMaterialf(GL_FRONT, GL_SHININESS, pearl_shininess);

        glPushMatrix();
            glRotatef(__angle, 0, 0, 1);
            glTranslated(connect_x, connect_y, 0);
            glRotatef(angle / 2 + angle * i, 0, 0, 1);

            // 支撐柱（兩環體橫向連接）
            glPushMatrix();
                glTranslated(0, 0, 3);
                glRotated(180, 1, 0, 0);

                //glNormal3f(0, 1, 0);
                gluCylinder(cylinder, .5, .5, 6, 4, 5);
            glPopMatrix();

            // 支撐斜角架（兩環體斜向交叉連接）
            glPushMatrix();
                glTranslated(0, 0, 3);
                glRotated(-90.0 - angle_cross, 1, 0, 0);
                glScaled(1, .7, 1);

                //glNormal3f(0, 1, 0);
                gluCylinder(cylinder, .5, .5, length_cross, 4, 5);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0, 0, -3);
                glRotated(-90.0 + angle_cross, 1, 0, 0);
                glScaled(1, .7, 1);

                //glNormal3f(0, 1, 0);
                gluCylinder(cylinder, .5, .5, length_cross, 4, 5);
            glPopMatrix();

            // 支撐車廂（交叉，兩環體各一對）
            glPushMatrix();
                glRotatef(-angle_carriage, 0, 0, 1);
                glTranslated(0, 0, 3);
                glRotated(-90, 1, 0, 0);

                //glNormal3f(0, 1, 0);
                gluCylinder(cylinder, .5, .5, length_cross_carriage, 4, 5);
            glPopMatrix();

            glPushMatrix();
                glRotatef(180 - angle + angle_carriage, 0, 0, 1);
                glTranslated(0, 0, 3);
                glRotated(-90, 1, 0, 0);

                //glNormal3f(0, 1, 0);
                gluCylinder(cylinder, .5, .5, length_cross_carriage, 4, 5);
            glPopMatrix();

            glPushMatrix();
                glRotatef(-angle_carriage, 0, 0, 1);
                glTranslated(0, 0, -3);
                glRotated(-90, 1, 0, 0);

                //glNormal3f(0, 1, 0);
                gluCylinder(cylinder, .5, .5, length_cross_carriage, 4, 5);
            glPopMatrix();

            glPushMatrix();
                glRotatef(180 - angle + angle_carriage, 0, 0, 1);
                glTranslated(0, 0, -3);
                glRotated(-90, 1, 0, 0);

                //glNormal3f(0, 1, 0);
                gluCylinder(cylinder, .5, .5, length_cross_carriage, 4, 5);
            glPopMatrix();

            // 支撐車廂（橫向，兩環體連接）
            glPushMatrix();
                glTranslated(length_straight_carriage, length / 2, 3);
                glRotated(180, 1, 0, 0);

                //glNormal3f(0, 1, 0);
                gluCylinder(cylinder, .5, .5, 6, 4, 5);
            glPopMatrix();
        glPopMatrix();

        // 車廂
        GLfloat carriage_x = (__radius + length_straight_carriage) * cos(angle * M_PI / 180.0 * (i + 0.5) + __angle * M_PI / 180.0);
        GLfloat carriage_y = (__radius + length_straight_carriage) * sin(angle * M_PI / 180.0 * (i + 0.5) + __angle * M_PI / 180.0);

        GLfloat emission[4] = { __carriage_rgb_emission[0] * 0.1, __carriage_rgb_emission[1] * 0.1, __carriage_rgb_emission[2] * 0.1, 1.0 };
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        glPushMatrix();
            glTranslated(carriage_x, carriage_y - 2.3, 0);
            draw_carriage();
        glPopMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
    }
}

void FerrisWheel::draw_center() {
    glPushMatrix();
        // Center
        glLightfv(GL_LIGHT2, GL_POSITION, __centerlight_position);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, __centerlight_direction);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, __centerlight_diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, __centerlight_specular);
        glLightfv(GL_LIGHT2, GL_AMBIENT, __centerlight_ambient); // [0, 0, 0]
        //glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, __centerlight_cutoff);
        //glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, __centerlight_exponent);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.05);

        GLfloat emission[4] = { 0.24725, 0.1995, 0.0745, 1.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, gold_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, gold_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, gold_diffuse);
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        glMaterialf(GL_FRONT, GL_SHININESS, gold_shininess);

        //glNormal3f(0, 1, 0);
        DrawEllipsoid(5, 8, 3, 3, 8);

        glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);

        // Connection
        GLfloat angle = 360.0 / __n; // 內角

        glMaterialfv(GL_FRONT, GL_AMBIENT, pearl_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, pearl_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, pearl_diffuse);
        glMaterialf(GL_FRONT, GL_SHININESS, pearl_shininess);

        for (int i = 0; i < __n; i++) {
            glPushMatrix();
                glTranslated(0, 0, 3);
                glRotated(-90 + angle * i, 0, 0, 1);
                glRotated(-90, 1, 0, 0);

                //glNormal3f(0, 1, 0);
                gluCylinder(cylinder, .2, .2, __radius, 4, 5);
            glPopMatrix(); 

            glPushMatrix();
                glTranslated(0, 0, -3);
                glRotated(-90 + angle * i, 0, 0, 1);
                glRotated(-90, 1, 0, 0);

                //glNormal3f(0, 1, 0);
                gluCylinder(cylinder, .2, .2, __radius, 4, 5);
            glPopMatrix();
        }
    glPopMatrix();
}

void FerrisWheel::draw_stand() {
    glPushMatrix();
        glTranslated(0, 0, 5.5);

        glPushMatrix();
            glRotated(23, 0, 0, 1);
            glRotated(90, 1, 0, 0);

            //glNormal3f(0, 1, 0);
            gluCylinder(cylinder, 1, 1, 1.8 * __radius, 8, 5);
        glPopMatrix();

        glPushMatrix();
            glRotated(-23, 0, 0, 1);
            glRotated(90, 1, 0, 0);

            //glNormal3f(0, 1, 0);
            gluCylinder(cylinder, 1, 1, 1.8 * __radius, 8, 5);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslated(0, 0, -5.5);

        glPushMatrix();
            glRotated(23, 0, 0, 1);
            glRotated(90, 1, 0, 0);

            //glNormal3f(0, 1, 0);
            gluCylinder(cylinder, 1, 1, 1.8 * __radius, 8, 5);
        glPopMatrix();

        glPushMatrix();
            glRotated(-23, 0, 0, 1);
            glRotated(90, 1, 0, 0);

            //glNormal3f(0, 1, 0);
            gluCylinder(cylinder, 1, 1, 1.8 * __radius, 8, 5);
        glPopMatrix();
    glPopMatrix();
}

void FerrisWheel::draw() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
        glTranslated(0, 1.8 * __radius * cos(23 * M_PI / 180), 0);

        draw_center();

        draw_torus();
        draw_core();
        draw_stand();
    glPopMatrix();
}

// Carriage RGB 閃爍
void FerrisWheel::twinkling() {
    __rgb_counter++;
    GLfloat theta = __rgb_counter * M_PI / 180.0;

    GLfloat red = cos(theta);
    GLfloat green = cos(theta + 0.5 * M_PI);
    GLfloat blue = cos(theta + M_PI);

    //cout << red << " " << green << " " << blue << "\n";

    __carriage_rgb_emission[0] = red;
    __carriage_rgb_emission[1] = green;
    __carriage_rgb_emission[2] = blue;
}

void FerrisWheel::rotate(GLfloat angle) {
    __angle += angle;
    if (__angle > 360)
        __angle = int(__angle) % 360;
}