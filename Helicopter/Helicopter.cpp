// Helicopter.h
#include "Helicopter.h"

#define _USE_MATH_DEFINES

#include <bits/stdc++.h>
#include <thread>
#include <GL/glut.h>

#include "Materials.h"

using namespace std;

Helicopter::Helicopter() {
    __angleBlade = 0.0f;
    __angleBodyFront = 0.0f;
    __angleBodySide = 0.0f;

    __angle = 0.0f;

    __camera_x = 0.0f;
    __camera_y = 10.0f;
    __camera_z = 50.0f;

    __translate_x = 0.0f;
    __translate_y = 0.0f;
    __translate_z = 0.0f;

    this->circle = gluNewQuadric();
    this->sphere = gluNewQuadric();
    this->cylinder = gluNewQuadric();

    __front = 0;
    __side = 0;
}

void Helicopter::draw_cube() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, chrome_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, chrome_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, chrome_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, chrome_shininess);

    for (int i = 0; i < 6; i++) {
        glNormal3fv(normal[i]);

        glBegin(GL_POLYGON);
            glVertex3fv(points[face[i][0]]);
            glVertex3fv(points[face[i][1]]);
            glVertex3fv(points[face[i][2]]);
            glVertex3fv(points[face[i][3]]);
        glEnd();
    }
}

void Helicopter::draw_cylinder() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, chrome_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, chrome_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, chrome_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, chrome_shininess);

    gluCylinder(cylinder, 1.0f, 1.0f, 1.0f, 16, 5);
}

void Helicopter::draw_sphere() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, chrome_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, chrome_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, chrome_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, chrome_shininess);

    gluSphere(sphere, 1.0f, 16, 5);
}

void Helicopter::draw_blade() {
    glRotatef(__angleBlade, 0.0f, 1.0f, 0.0f); // ��������
    glTranslated(0.0f, 0.0f, -0.1f);

    glPushMatrix();
        glPushMatrix(); // ���� - 1
            glScaled(2.5f, 0.2f, 0.2f);
            draw_cube();
        glPopMatrix();

        glRotated(90, 0.0f, 1.0f, 0.0f);
        glTranslated(-0.1f, 0.0f, -0.1f);

        glPushMatrix(); // ���� - 2
            glScaled(2.5f, 0.2f, 0.2f);
            draw_cube();
        glPopMatrix();

        glRotated(90, 0.0f, 1.0f, 0.0f);
        glTranslated(-0.1f, 0.0f, -0.1f);

        glPushMatrix(); // ���� - 3
            glScaled(2.5f, 0.2f, 0.2f);
            draw_cube();
        glPopMatrix();

        glRotated(90, 0.0f, 1.0f, 0.0f);
        glTranslated(-0.1f, 0.0f, -0.1f);

        glPushMatrix(); // ���� - 4
            glScaled(2.5f, 0.2f, 0.2f);
            draw_cube();
        glPopMatrix();
    glPopMatrix();

    //glRotated(90, 0.0f, 1.0f, 0.0f); // �N�����ॿ
    //glTranslated(0.3f, 0.0f, 0.4f);
}

void Helicopter::draw_tripod() {
    glTranslated(-2.5f, 0.0f, 0.0f);

    glPushMatrix();
        glPushMatrix();
            glScaled(5.0f, .2f, .4f);
            draw_cube();
        glPopMatrix();

        glRotatef(-120, 1.0f, 0.0f, 0.0f);
        glTranslated(0.0f, -0.1f, 0.0f);

        glPushMatrix();
            glTranslated(1.5f, 0.0f, 0.0f);
            glScaled(.2f, .2f, .8f);
            draw_cube();
        glPopMatrix();

        glPushMatrix();
            glTranslated(3.3f, 0.0f, 0.0f);
            glScaled(.2f, .2f, .8f);
            draw_cube();
        glPopMatrix();
    glPopMatrix();
}

void Helicopter::draw_searchlight() {
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, __searchlight_position);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, __searchlight_direction);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, __searchlight_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, __searchlight_specular);
    glLightfv(GL_LIGHT1, GL_AMBIENT, __searchlight_ambient); // [0, 0, 0]
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, __searchlight_cutoff);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, __searchlight_exponent);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05);

    glPushMatrix();
        // Sphere
        GLfloat emission[4] = { 0.329412, 0.223529, 0.027451, 1.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, brass_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, brass_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, brass_diffuse);
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        glMaterialf(GL_FRONT, GL_SHININESS, brass_shininess);

        gluSphere(sphere, 1.0f, 16, 5);

        glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
    glPopMatrix();
}

void Helicopter::draw() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glTranslated(__translate_x, __translate_y, __translate_z);
    glRotatef(__angle, 0, 1, 0); // ��������
    glTranslated(-1.5f, 0.7f, -1.0f);
    glRotated(__angleBodyFront, 0, 0, 1); // �����ɱ�
    glRotated(__angleBodySide, 1, 0, 0); // �����ɱ�

    glPushMatrix(); // ����
        glScaled(3.0f, 1.0f, 2.0f);
        draw_cube();
    glPopMatrix();

    glPushMatrix(); // ���ӿO
        glTranslated(0.1f, 0.2f, 1.0f);
        glScaled(0.2f, 0.2f, 0.2f);
        draw_searchlight();
    glPopMatrix();

    glPushMatrix(); // ��D���l��D�������s��
        glTranslated(1.5f, 1.0f, 1.0f);

        glPushMatrix(); // �D���l
            glRotatef(-90, 1.0f, 0.0f, 0.0f);
            glScaled(0.2f, 0.2f, 0.5f);
            draw_cylinder();
        glPopMatrix();

        glTranslated(0.0f, 0.6f, 0.0f);

        glPushMatrix(); // �D�s���I
            glScaled(0.4f, 0.2f, 0.4f);
            draw_sphere();
        glPopMatrix();

        glTranslated(0.0f, 0.2f, 0.0f);
        draw_blade(); // �D����
    glPopMatrix();

    glPushMatrix();
        glTranslated(3.0f, 0.5f, 1.0f);

        glPushMatrix(); // ���[
            glRotatef(90, 0.0f, 1.0f, 0.0f);
            glScaled(0.2f, 0.2f, 1.5f);
            draw_cylinder();
        glPopMatrix();

        glTranslated(1.7f, 0.0f, 0.0f);

        glPushMatrix(); // ����l��Ʈ������s�աA�@�_���� 30 ��
            glRotatef(-30, 0.0f, 0.0f, 1.0f);

            glPushMatrix(); // �Ƴs���I - 1
                glScaled(.3f, .3f, .3f);
                draw_sphere();
            glPopMatrix();

            glTranslated(0.0f, 0.2f, 0.0f);

            glPushMatrix(); // ���l
                glRotatef(-90, 1.0f, 0.0f, 0.0f);
                glScaled(0.2f, 0.2f, 1.0f);
                draw_cylinder();
            glPopMatrix();

            glTranslated(0.0f, 1.0f, 0.0f);

            glPushMatrix(); // �Ƴs���I - 2
                glScaled(.3f, .3f, .3f);
                draw_sphere();
            glPopMatrix();

            glTranslated(0.0f, 0.0f, 0.25f);

            glPushMatrix(); // �Ʈ���
                glRotatef(90, 1.0f, 0.0f, 0.0f);
                glScaled(.4f, .4f, .4f);
                draw_blade();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix(); // ���Ӹ}�[���s��
        glTranslated(1.5f, -0.7f, 0.0f);

        glPushMatrix();
            glTranslated(0.0f, 0.0f, 2.0f);
            draw_tripod();
        glPopMatrix();

        glPushMatrix();
            glRotatef(180, 0.0f, 1.0f, 0.0f);
            draw_tripod();
        glPopMatrix();
    glPopMatrix();
}

/*void Helicopter::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION); // ��v��ı�x�}
    glLoadIdentity();
    gluPerspective(90, 1, 1, 200); // �]�m���Y�Ѽ�

    glMatrixMode(GL_MODELVIEW); // �ҫ����ϯx�}
    glLoadIdentity();
    gluLookAt(__translate_x + __camera_x, __translate_y + __camera_y, __translate_z + __camera_z, __translate_x, __translate_y, __translate_z, 0.0f, 1.0f, 0.0f); // �]�m�۾��Ѽ�
    //gluLookAt(0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f); // �]�m�۾��ѼơG����
    //gluLookAt(0.0f, 10.0f, 70.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // �]�m�۾��ѼơG����
    //gluLookAt(70.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // �]�m�۾��ѼơG���

    glPushMatrix();
        glTranslated(0.0f, 0.0f, -40.0f);
        ferrisWheel.draw();
    glPopMatrix();

    glPushMatrix();
        glTranslated(0.0f, 5.0f, 0.0f);
        Helipad::draw();
        //Axis::draw_axis(10.0f, 10.0f, 10.0f);
        draw_helicopter();
    glPopMatrix();

    Axis::draw_ground(120.0f, 120.0f);

    glutSwapBuffers(); // �洫��ӽw�İϡ]GLUT_DOUBLE�^
    glFlush();

    //cout << "Coord: [" << __translate_x << ", " << __translate_y << ", " << __translate_z << "], Angle: " << __angle << "\n";
}*/


/*------------------------------------------------------------
 * Getter & Setter
 */
GLfloat* Helicopter::getPosition() {
    GLfloat* position = new GLfloat[3]{ __translate_x, __translate_y, __translate_z };
    return position;
}
GLfloat Helicopter::getAngle() { return __angle; }

void Helicopter::setCamera(GLfloat pitch, GLfloat yaw, GLfloat radius) {
    __camera_x = cos(pitch * M_PI / 180) * cos(yaw * M_PI / 180) * radius;
    __camera_y = sin(pitch * M_PI / 180) * radius;
    __camera_z = cos(pitch * M_PI / 180) * sin(yaw * M_PI / 180) * radius;
}
GLfloat* Helicopter::getCamera() {
    GLfloat* camera = new GLfloat[3]{ __camera_x, __camera_y, __camera_z };
    return camera;
}

void Helicopter::setSearchlightColor(GLfloat* color) { for (int i = 0; i < 3; i++) __searchlight_diffuse[i] = __searchlight_specular[i] = color[i]; }
GLfloat* Helicopter::getSearchlightColor() { return __searchlight_diffuse; }

void Helicopter::setSearchlightDirectionV(GLfloat v) { __searchlight_direction[1] = v; }
GLfloat Helicopter::getSearchlightDirectionV() { return __searchlight_direction[1]; }
void Helicopter::setSearchlightDirectionH(GLfloat h) { __searchlight_direction[2] = h; }
GLfloat Helicopter::getSearchlightDirectionH() { return __searchlight_direction[2]; }

void Helicopter::setSearchlightCutoff(GLfloat cutoff) { __searchlight_cutoff = cutoff; }
GLfloat Helicopter::getSearchlightCutoff() { return __searchlight_cutoff; }

/*------------------------------------------------------------
 * ��������G�u�������� Y �b����
 */
void Helicopter::rotate(GLfloat angle) {
    __angle = (int)(__angle + angle) % 360;
}

/*------------------------------------------------------------
 * �������ʡG�������פ��o�C�� 0
 */
void Helicopter::translate(GLfloat translate_x, GLfloat translate_y, GLfloat translate_z) {
    __translate_x += translate_x;
    __translate_y += translate_y;
    __translate_z += translate_z;

    if (__translate_y < 0)
        __translate_y = 0;
}

/*------------------------------------------------------------
 * �����ե�
 */
void Helicopter::initCoordinate() {
    // �N�V�e��ɨ��C�C�k�s
    if (__front == MOVE_FRONT && 0 < __angleBodyFront)
        __angleBodyFront -= 0.05;
    else if (__front == MOVE_BACK && __angleBodyFront < 0)
        __angleBodyFront += 0.05;
    else
        __angleBodyFront /= 1.05; // �����e��ɡA���t�ɥ�����

    // �N�V���k�ɨ��C�C�k�s
    if (__side == MOVE_RIGHT && __angleBodySide < 0)
        __angleBodySide += 0.05;
    else if (__side == MOVE_LEFT && 0 < __angleBodySide)
        __angleBodySide -= 0.05;
    else
        __angleBodySide /= 1.05; // �������k�ɡA���t�ɥ�����
}

/*------------------------------------------------------------
 * ��������
 */
void Helicopter::rotateBlade(GLfloat angle) {
    if (__translate_y > 0) // ���a�����~����
        __angleBlade = (int)(__angleBlade + angle) % 360;
}

/*------------------------------------------------------------
 * �������鲾�ʡG�ĥ��N��V���ʡ]���k�e�i�ɥu�o�V�e���ʡ^
 */
void Helicopter::moveForward(GLfloat distance) {
    this->moveForward(distance, MOVE_FRONT);
}

void Helicopter::moveForward(GLfloat distance, int front) {
    this->moveForward(distance, front, NULL);
}

void Helicopter::moveForward(GLfloat distance, int front, int side) {
    if (__translate_y > 0) { // ���a�~��e�i
        __front = front;
        __side = side;

        GLfloat x = -distance * cos(__angle * M_PI / 180);
        GLfloat y = 0;
        GLfloat z = distance * sin(__angle * M_PI / 180);

        // ���t�V�e��ɱ׾����A�W�� 15 ��
        if (front == MOVE_FRONT) {
            this->translate(x, y, z);
            if (__angleBodyFront < 15)
                __angleBodyFront++;
        }
        else if (front == MOVE_BACK) {
            this->translate(-x, y, -z);
            if (-15 < __angleBodyFront)
                __angleBodyFront--;
        }

        // ���t�V���k�ɱ׾����A�W�� 15 ��
        if (side == MOVE_RIGHT) {
            this->translate(x, y, z);
            this->rotate(-2);
            if (-15 < __angleBodySide)
                __angleBodySide--;
        }
        else if (side == MOVE_LEFT) {
            this->translate(x, y, z);
            this->rotate(2);
            if (__angleBodySide < 15)
                __angleBodySide++;
        }
    }
    else
        cout << "���׹L�C�A�L�k����I\n";
}

/*------------------------------------------------------------
* �����۰ʰ_��
*/
/*void Helicopter::autoTakeOff() {
    if (__translate_y != 0)
        return;

    thread thread([&]() {
        for (int i = 0; i < 200; i++) {
            Sleep(TIMES);
            translate(0, 0.1, 0);
            display();
        }
    });
    thread.detach();
}*/

/*------------------------------------------------------------
* �����۰ʭ���
*/
/*void Helicopter::autoLanding() {
    if (__translate_y == 0)
        return;

    thread thread([&]() {
        GLfloat angle = __angle;

        GLfloat translate_x = __translate_x;
        GLfloat translate_y = __translate_y;
        GLfloat translate_z = __translate_z;

        GLfloat distance = sqrt(translate_x * translate_x + translate_z * translate_z);
        GLfloat cos_theta = (distance * distance + translate_z * translate_z - translate_x * translate_x) / (2 * distance * translate_z); // �l���w�z
        GLfloat theta = acos(cos_theta) * 180 / M_PI;

        // �l���w�z�ɤ����� 0 - distance, translate_z
        if (translate_z == 0)
            theta = 90;

        // �����V�k����ܹ�ǭ��I�Gx < 0: angle + theta + 90, x > 0: angle + 90 - theta�]������m�ܭ��I�P z �b�������^
        if (__translate_x < 0)
            angle = angle + theta + 90;
        else
            angle = angle + 90 - theta;
        angle = (int)(angle + 360) % 360; // ������

        for (int i = 0; i < angle; i++) {
            Sleep(TIMES * 0.5);
            rotate(-1);
            display();
        }

        // �����e�i�ܭ��I
        for (GLfloat i = 0; i < distance; i += UNIT_DISTANCE) {
            Sleep(TIMES);
            moveForward(UNIT_DISTANCE);
            display();
        }

        // �����U���ܰ��� 0
        while (__translate_y > 0) {
            Sleep(TIMES);
            translate(0, -0.1, 0);
            display();
        }
    });
    thread.detach();
}*/