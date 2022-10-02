#define _USE_MATH_DEFINES

#include <bits/stdc++.h>
#include <GL/glut.h>

#include "Helicopter.h";
#include "Axis.h"
#include "Helipad.h"
#include "FerrisWheel.h"

#include "Texture.h"
#include "Billboard.h"
#include "Foggy.h"

#include "CSkyDome.h"

using namespace std;

Helicopter helicopter;
Axis axis;
Helipad helipad;
FerrisWheel ferrisWheel = FerrisWheel(24, 15);
Billboard billboard;
Foggy foggy;

CSkyDome skydome;

int width = 500, height = 500;
int mouse_x = 0, mouse_y = 0;

float pitch = 10.0f; // 俯仰角
float yaw = 90.0f; // 偏擺角
int radius = 50; // 視角距離

/*
Light
*/
// Global Ambient - 一律由 Global 產生 Ambient
GLfloat global_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

// 太陽光 - 平行光
GLfloat sun_position[] = { 0.0, 100.0, 0.0, 0.0 };
GLfloat sun_direction[] = { 0.0, -1.0, 0.0, 1.0 };
GLfloat sun_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat sun_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat sun_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat sun_position_inverse[] = { 0.0, -sun_position[1], 0.0, 0.0 };
GLfloat sun_direction_inverse[] = { 0.0, -sun_direction[1], 0.0, 1.0 };

// Texture
GLuint TextureID[69];
int offset = 0;

#define POS_NUMS 200
GLfloat cloud_position_x[POS_NUMS];
GLfloat cloud_position_y[POS_NUMS];
GLfloat cloud_position_z[POS_NUMS];

/*
Command
*/
bool onSpecial = false; //  用來阻止 OnKeyBoard 的偵測

string command; // 觸發 OnSpecialFunc 時輸入指令
string param;
int order;

GLfloat commandColor[3] = { 1.0, 1.0, 1.0 };

void commandLine(unsigned char key);

/*
Function
*/
void init();
void display();
void reshape(int w, int h);

void OnTimer(int id);
void OnMouse(int button, int state, int x, int y);
void OnMouseMove(int x, int y);
void OnKeyBoard(unsigned char key, int x, int y);
void OnSpecialFunc(int key, int x, int y);

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutCreateWindow("Helicopter");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutTimerFunc(helicopter.TIMES, OnTimer, 1);
    glutTimerFunc(helicopter.TIMES * 10, OnTimer, 2);

    glutMouseFunc(OnMouse);
    glutMotionFunc(OnMouseMove);
    glutKeyboardFunc(OnKeyBoard);
    glutSpecialFunc(OnSpecialFunc);

    glutMainLoop();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_FOG);

    // Sun
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, sun_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, sun_direction);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sun_ambient); // [0, 0, 0]
    glEnable(GL_LIGHT7);
    glLightfv(GL_LIGHT7, GL_POSITION, sun_position_inverse);
    glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, sun_direction_inverse);
    glLightfv(GL_LIGHT7, GL_DIFFUSE, sun_diffuse);
    glLightfv(GL_LIGHT7, GL_SPECULAR, sun_specular);
    glLightfv(GL_LIGHT7, GL_AMBIENT, sun_ambient); // [0, 0, 0]

    // Ferris Wheel Light
    ferrisWheel.turnOnCenterLight();

    // Global Light
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    // Texture
    TextureID[0] = Create_Texture_Circle();
    TextureID[1] = Create_Texture_Land();
    TextureID[2] = Create_Texture_Star();
    TextureID[3] = Create_Texture_Tree();
    TextureID[4] = Create_Texture_Cloud();

    for (int i = 0; i < 64; i++)
        TextureID[i + 5] = Create_Texture_Waterwave(i);

    srand(time(NULL));
    for (int i = 0; i < POS_NUMS; i++) {
        cloud_position_x[i] = rand() % 800 - 400;
        cloud_position_y[i] = rand() % 20 + 120 - 10;
        cloud_position_z[i] = rand() % 800 - 400;
    }

    // Face Culling - IDK WTF IS THIS
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}

void display() {
    GLfloat* helicopter_pos = helicopter.getPosition();
    GLfloat* helicopter_cmr = helicopter.getCamera();

    // Draw Scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION); // 投影視覺矩陣
    glLoadIdentity();
    gluPerspective(90, 1, 1, 1000); // 設置鏡頭參數

    glMatrixMode(GL_MODELVIEW); // 模型視圖矩陣
    glLoadIdentity();
    gluLookAt(helicopter_pos[0] + helicopter_cmr[0], helicopter_pos[1] + helicopter_cmr[1], helicopter_pos[2] + helicopter_cmr[2],
                helicopter_pos[0], helicopter_pos[1], helicopter_pos[2],
                0.0f, 1.0f, 0.0f); // 設置相機參數
    //gluLookAt(0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f); // 設置相機參數：俯視
    //gluLookAt(0.0f, 10.0f, 70.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // 設置相機參數：側視
    //gluLookAt(70.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // 設置相機參數：後視
    billboard.setAxes();
    foggy.render();

    glPushMatrix();

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, TextureID[3]);

        billboard.draw(25, 0, 5.0, 10.0);
        billboard.draw(-25, 0, 5.0, 10.0);
        billboard.draw(0, 25, 5.0, 10.0);
        billboard.draw(0, -25, 5.0, 10.0);

        glTranslated(0.0f, 5.0f, 0.0f);

        billboard.draw(10, 10, 5.0, 10.0);
        billboard.draw(10, -10, 5.0, 10.0);
        billboard.draw(-10, 10, 5.0, 10.0);
        billboard.draw(-10, -10, 5.0, 10.0);

        glBindTexture(GL_TEXTURE_2D, TextureID[4]);
        for (int i = 0; i < POS_NUMS; i++) {
            glPushMatrix();
                glTranslated(0.0f, cloud_position_y[i], 0.0f);
                billboard.draw(cloud_position_x[i], cloud_position_z[i], 10.0, 10.0);
            glPopMatrix();
        }
    glPopMatrix();

    glPushMatrix();
        glTranslated(0.0f, 0.0f, -120.0f);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, TextureID[2]);
        ferrisWheel.draw();
    glPopMatrix();

    glPushMatrix();
        glTranslated(0.0f, 25.0f, 120.0f);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, TextureID[0]);
        helipad.draw(25);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0.0f, 5.0f, 0.0f);
        helipad.draw(5);
        helicopter.draw();
    glPopMatrix();

    glPushMatrix();
        glTranslated(0.0f, 0.01f, 0.0f);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, TextureID[1]);

        axis.draw_ground(50, 50);
    glPopMatrix();


    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TextureID[5 + offset % 64]);
    GLfloat weak = min(sun_diffuse[0], min(sun_diffuse[1], sun_diffuse[2]));
    axis.draw_skydome(helicopter_pos[0], helicopter_pos[1], helicopter_pos[2], 1000, weak);

    //skydome.GenerateDome(60, 1, 10, 5, 5);
    //skydome.RenderSkyDome(0, 101, 0);

    glutSwapBuffers(); // 交換兩個緩衝區（GLUT_DOUBLE）
    glFlush();
}

void reshape(int w, int h) {
    width = w;
    height = h;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // 調整視口位置和大小

    glMatrixMode(GL_PROJECTION); // 投影視覺矩陣
    glLoadIdentity();
    //gluPerspective(90, w / h, 1, 200); // 設置鏡頭參數

    glMatrixMode(GL_MODELVIEW); // 模型視圖矩陣
    glLoadIdentity();
    //gluLookAt(10.0f, 10.0f, 10.0f, 0.0f, 00.0f, 0.0f, 0.0f, 1.0f, 0.0f); // 設置相機參數
}

void OnTimer(int id) {
    switch (id) {
        case 1:
            helicopter.rotateBlade(47);
            ferrisWheel.rotate(.07);
            ferrisWheel.twinkling();
            offset++;
            glutTimerFunc(helicopter.TIMES, OnTimer, id);
            break;
        case 2:
            helicopter.initCoordinate();
            glutTimerFunc(helicopter.TIMES, OnTimer, id);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void OnMouse(int button, int state, int x, int y) {
    if (button == 3) { // 滾輪向上
        radius = min(radius + 1, 50);
        helicopter.setCamera(pitch, yaw, radius);
        glutPostRedisplay();
    }
    else if (button == 4) { // 滾輪向下
        radius = max(radius - 1, 20);
        helicopter.setCamera(pitch, yaw, radius);
        glutPostRedisplay();
    }
    mouse_x = x;
    mouse_y = y;
}

void OnMouseMove(int x, int y) {
    if (0 < x && x < width) {
        yaw += (x - mouse_x) * 0.7;
        mouse_x = x;

        if (yaw > 360.f || yaw < -360.f)
            yaw = int(yaw) % 360;
    }
    if (0 < y && y < height) {
        pitch += (y - mouse_y) * 0.2;
        mouse_y = y;

        pitch = min(pitch, 89.0f);
        pitch = max(pitch, 10.0f);
    }

    helicopter.setCamera(pitch, yaw, radius);
    //cout << camera_x << " " << camera_y << " " << camera_z << "\n";
}

void OnKeyBoard(unsigned char key, int x, int y) {
    if (onSpecial) {
        commandLine(key);
        return;
    };

    switch (key) {
        case ' ':
            if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
                helicopter.translate(0, -0.1 * 3, 0);
            else
                helicopter.translate(0, 0.1 * 3, 0);
            break;
        case 'A':
        case 'a':
            helicopter.rotate(6);
            break;
        case 'D':
        case 'd':
            helicopter.rotate(-6);
            break;
        case 'W':
        case 'w':
            helicopter.moveForward(helicopter.UNIT_DISTANCE * 3);
            break;
        case 'S':
        case 's':
            helicopter.moveForward(helicopter.UNIT_DISTANCE * 3, helicopter.MOVE_BACK);
            break;
        case 'E':
        case 'e':
            helicopter.moveForward(helicopter.UNIT_DISTANCE * 3, 0, helicopter.MOVE_RIGHT);
            break;
        case 'Q':
        case 'q':
            helicopter.moveForward(helicopter.UNIT_DISTANCE * 3, 0, helicopter.MOVE_LEFT);
            break;
        /*case 'V':
        case 'v':
            helicopter.autoTakeOff();
            break;
        case 'R':
        case 'r':
            helicopter.autoLanding();
            break;*/
        case 'L':
        case 'l':
            if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
                GLfloat cutoff = helicopter.getSearchlightCutoff();
                helicopter.setSearchlightCutoff(max(5.0f, cutoff - 1));
            }
            else {
                GLfloat cutoff = helicopter.getSearchlightCutoff();
                helicopter.setSearchlightCutoff(min(30.0f, cutoff + 1));
            }
            break;
        case 'F':
        case 'f':
            if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
                ferrisWheel.turnOffCenterLight();
            else
                ferrisWheel.turnOnCenterLight();
            break;
        case '+':
            if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) { // 探照燈亮度 +
                GLfloat* color = helicopter.getSearchlightColor();
                for (int i = 0; i < 3; i++) color[i] = min(1.0, color[i] * 1.05);
                helicopter.setSearchlightColor(color);
            }
            else { // 太陽光亮度 +
                for (int i = 0; i < 3; i++) {
                    sun_diffuse[i] = min(1.0, sun_diffuse[i] * 1.05);
                    sun_specular[i] = min(1.0, sun_specular[i] * 1.05);
                }
                glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);
                glLightfv(GL_LIGHT0, GL_SPECULAR, sun_specular);
                glLightfv(GL_LIGHT7, GL_SPECULAR, sun_diffuse);
                glLightfv(GL_LIGHT7, GL_SPECULAR, sun_specular);
            }
            break;
        case '-':
            if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) { // 探照燈亮度 -
                GLfloat* color = helicopter.getSearchlightColor();
                for (int i = 0; i < 3; i++) color[i] = max(0.0, color[i] * 0.95);
                helicopter.setSearchlightColor(color);
            }
            else { // 太陽光亮度 -
                for (int i = 0; i < 3; i++) {
                    sun_diffuse[i] = max(0.0, sun_diffuse[i] * 0.95);
                    sun_specular[i] = max(0.0, sun_specular[i] * 0.95);
                }
                glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);
                glLightfv(GL_LIGHT0, GL_SPECULAR, sun_specular);
                glLightfv(GL_LIGHT7, GL_SPECULAR, sun_diffuse);
                glLightfv(GL_LIGHT7, GL_SPECULAR, sun_specular);
            }
            break;
        case 'G':
        case 'g':
            if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
                foggy.setDensity(foggy.getDensity() * 0.9);
            else
                foggy.setDensity(foggy.getDensity() * 1.1);
            break;
        case 'M':
        case 'm':
            if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
                foggy.setMode(GL_EXP);
            else if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
                foggy.setMode(GL_EXP2);
            else
                foggy.setMode(GL_LINEAR);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void OnSpecialFunc(int key, int x, int y) {
    GLfloat v = helicopter.getSearchlightDirectionV();
    GLfloat h = helicopter.getSearchlightDirectionH();
    double directRange = 0.3;

    switch (key) {
        case GLUT_KEY_UP:
            helicopter.setSearchlightDirectionV(min(directRange, v + 0.03));
            break;
        case GLUT_KEY_DOWN:
            helicopter.setSearchlightDirectionV(max(-directRange, v - 0.03));
            break;
        case GLUT_KEY_LEFT:
            helicopter.setSearchlightDirectionH(min(directRange, h + 0.03));
            break;
        case GLUT_KEY_RIGHT:
            helicopter.setSearchlightDirectionH(max(-directRange, h - 0.03));
            break;
        case GLUT_KEY_F1:
            onSpecial = true;

            command = "";
            param = "";
            order = -1;

            cout << "Command: ";
        default:
            break;
    }
}

void commandLine(unsigned char key) {
    try {
        if (key == ' ') { // 切換參數
            cout << key;

            if (command == "") { // 還未輸入指令完整
                if (param == "SUN" || param == "HSL" || param == "FOG") {
                    command = param;
                }
                else { // 指令錯誤
                    onSpecial = false;
                    cout << "\nERROR\n";
                }

                param = "";
                order = 0;
            }
            else { // 已輸入完指令
                if (command == "SUN" || command == "HSL" || command == "FOG") {
                    commandColor[order] = stof(param);
                    param = "";
                    order++;
                }
            }
        }
        else if (key == 13) { // Enter
            if (command == "SUN") {
                if (order == 2) { // 可能忘記輸入空白
                    commandColor[order] = stof(param);
                    param = "";
                }

                for (int i = 0; i < 3; i++) {
                    sun_diffuse[i] = sun_specular[i] = commandColor[i];
                    commandColor[i] = 0;
                }
                glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);
                glLightfv(GL_LIGHT0, GL_SPECULAR, sun_specular);
                glLightfv(GL_LIGHT7, GL_SPECULAR, sun_diffuse);
                glLightfv(GL_LIGHT7, GL_SPECULAR, sun_specular);

                order = 0;
                onSpecial = false;
                cout << "\nSUCCESS\n";
            }
            else if (command == "HSL") {
                if (order == 2) { // 可能忘記輸入空白
                    commandColor[order] = stof(param);
                    param = "";
                }

                helicopter.setSearchlightColor(commandColor);
                for (int i = 0; i < 3; i++) commandColor[i] = 0;

                order = 0;
                onSpecial = false;
                cout << "\nSUCCESS\n";
            }
            else if (command == "FOG") {
                if (order == 2) { // 可能忘記輸入空白
                    commandColor[order] = stof(param);
                    param = "";
                }

                foggy.setColor(commandColor);
                for (int i = 0; i < 3; i++) commandColor[i] = 0;

                order = 0;
                onSpecial = false;
                cout << "\nSUCCESS\n";
            }
            else {
                onSpecial = false;
                cout << "\nERROR\n";
            }
        }
        else { // 輸入指令中
            cout << key;
            param += ::toupper(key);
        }
    }
    catch (...) {
        command = "";
        param = "";
        order = -1;
        onSpecial = false;
        cout << "\nError\n";
    }
}