// Texture.h
#pragma warning(disable:4996)
#include "Texture.h"

#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <GL/glut.h>

//#include "SDL.h"
//#include "SDL_image.h"

#define SIZE64 64

using namespace std;

GLuint Create_Texture_Circle() {
    unsigned char texture[64][64][4];

    int temp;
    for (int y = 0; y < 64; y++) {
        for (int x = 0; x < 64; x++) {
            texture[y][x][0] = 100;
            texture[y][x][1] = 100;
            texture[y][x][2] = 100;
            texture[y][x][3] = 255;
        }
    }
    for (int y = 16, x = 0; y < 48; y++) {
        if (y <= 20 && y >= 17)
            x = x + 2;
        else if (y == 22 || y == 25 || y == 31)
            x = x + 1;
        else if (y == 42 || y == 39 || y == 33)
            x = x - 1;
        else if (y <= 47 && y >= 44)
            x = x - 2;
        temp = x;
        for (x = 0; x < temp; x++) {
            texture[y][x][0] = 150;
            texture[y][x][1] = 150;
            texture[y][x][2] = 150;
            texture[y][x][3] = 255;
        }
        for (x = 64 - temp; x < 64; x++) {
            texture[y][x][0] = 150;
            texture[y][x][1] = 150;
            texture[y][x][2] = 150;
            texture[y][x][3] = 255;
        }
        x = temp;
    }

    for (int x = 16, y = 0; x < 48; x++) {
        if (x <= 20 && x >= 17)
            y = y + 2;
        else if (x == 22 || x == 25 || x == 31)
            y = y + 1;
        else if (x == 42 || x == 39 || x == 33)
            y = y - 1;
        else if (x <= 47 && x >= 44)
            y = y - 2;
        temp = y;
        for (int y = 0; y < temp; y++) {
            texture[y][x][0] = 200;
            texture[y][x][1] = 200;
            texture[y][x][2] = 200;
            texture[y][x][3] = 255;
        }
        for (int y = 64 - temp; y < 64; y++) {
            texture[y][x][0] = 200;
            texture[y][x][1] = 200;
            texture[y][x][2] = 200;
            texture[y][x][3] = 255;
        }
        y = temp;
    }
    for (int i = 0; i < 61; i++) {
        for (int y = i; y < 4 + i; y++) {
            for (int x = i; x < 4 + i; x++) {
                texture[y][x][0] = 255;
                texture[y][x][1] = 255;
                texture[y][x][2] = 255;
                texture[y][x][3] = 255;
            }
        }
    }
    for (int i = 0; i < 61; i++) {
        for (int y = i; y < 4 + i; y++) {
            for (int x = 60 - i; x < 64 - i; x++) {
                texture[y][x][0] = 255;
                texture[y][x][1] = 255;
                texture[y][x][2] = 255;
                texture[y][x][3] = 255;
            }
        }
    }

    GLuint ID;
    glGenTextures(1, &ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SIZE64, SIZE64, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
    return ID;
}

GLuint Create_Texture_Land() {
    unsigned char texture[64][64][4];

    for (int y = 0; y < 32; y++)
        for (int x = 0; x < 32; x++) {
            texture[x][y][0] = 240;
            texture[x][y][1] = 240;
            texture[x][y][2] = 240;
            texture[x][y][3] = 255;
        }

    for (int x = 24; x < 32; x++) {
        texture[x][0][0] = 255;
        texture[x][0][1] = 200;
        texture[x][0][2] = 200;
        texture[x][0][3] = 255;

        texture[0][x][0] = 255;
        texture[0][x][1] = 200;
        texture[0][x][2] = 200;
        texture[0][x][3] = 255;
    }
    for (int x = 26; x < 32; x++) {
        texture[x][1][0] = 255;
        texture[x][1][1] = 200;
        texture[x][1][2] = 200;
        texture[x][1][3] = 255;

        texture[1][x][0] = 255;
        texture[1][x][1] = 200;
        texture[1][x][2] = 200;
        texture[1][x][3] = 255;
    }
    for (int x = 27; x < 32; x++) {
        for (int y = 2; y < 4; y++) {
            texture[x][y][0] = 255;
            texture[x][y][1] = 200;
            texture[x][y][2] = 200;
            texture[x][y][3] = 255;

            texture[y][x][0] = 255;
            texture[y][x][1] = 200;
            texture[y][x][2] = 200;
            texture[y][x][3] = 255;
        }
    }
    for (int x = 28; x < 32; x++) {
        for (int y = 4; y < 7; y++) {
            texture[x][y][0] = 255;
            texture[x][y][1] = 200;
            texture[x][y][2] = 200;
            texture[x][y][3] = 255;

            texture[y][x][0] = 255;
            texture[y][x][1] = 200;
            texture[y][x][2] = 200;
            texture[y][x][3] = 255;
        }
    }
    for (int x = 29; x < 32; x++) {
        for (int y = 7; y < 9; y++) {
            texture[x][y][0] = 255;
            texture[x][y][1] = 200;
            texture[x][y][2] = 200;
            texture[x][y][3] = 255;

            texture[y][x][0] = 255;
            texture[y][x][1] = 200;
            texture[y][x][2] = 200;
            texture[y][x][3] = 255;
        }
    }
    for (int x = 30; x < 32; x++) {
        for (int y = 9; y < 12; y++) {
            texture[x][y][0] = 255;
            texture[x][y][1] = 200;
            texture[x][y][2] = 200;
            texture[x][y][3] = 255;

            texture[y][x][0] = 255;
            texture[y][x][1] = 200;
            texture[y][x][2] = 200;
            texture[y][x][3] = 255;
        }
    }
    for (int x = 31; x < 32; x++) {
        for (int y = 12; y < 16; y++) {
            texture[x][y][0] = 255;
            texture[x][y][1] = 200;
            texture[x][y][2] = 200;
            texture[x][y][3] = 255;

            texture[y][x][0] = 255;
            texture[y][x][1] = 200;
            texture[y][x][2] = 200;
            texture[y][x][3] = 255;
        }
    }

    for (int y = 16; y < 32; y++)
        for (int x = 16; x < 32; x++) {
            texture[x][y][0] = 200;
            texture[x][y][1] = 160;
            texture[x][y][2] = 255;
            texture[x][y][3] = 255;
        }
    for (int y = 20; y < 32; y++)
        for (int x = 20; x < 32; x++) {
            texture[x][y][0] = 255;
            texture[x][y][1] = 200;
            texture[x][y][2] = 255;
            texture[x][y][3] = 255;
        }

    for (int x = 63; x > 31; x--) {
        for (int y = 0; y < 32; y++)
            for (int i = 0; i < 4; i++)
                texture[x][y][i] = texture[63 - x][y][i];
    }

    /* Create the rest half part */
    for (int y = 32; y < 64; y++)
        for (int x = 0; x < 64; x++)
            for (int i = 0; i < 4; i++)
                texture[x][y][i] = texture[x][63 - y][i];

    GLuint ID;
    glGenTextures(1, &ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SIZE64, SIZE64, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
    return ID;
}

GLuint Create_Texture_Star() {
    unsigned char texture[64][64][4];

    int x, y;
    for (x = 0; x < 64; x++)
        for (y = 0; y < 64; y++) {
            texture[x][y][0] = 255;
            texture[x][y][1] = 255;
            texture[x][y][2] = 255;
            texture[x][y][3] = 255;
        }

    x = 31;
    y = 60;
    while (x >= 12) {
        for (int i = y; i > 4; i--) {
            texture[x][i][0] = 100;
            texture[x][i][1] = 100;
            texture[x][i][2] = 255;
            texture[x][i][3] = 255;
        }
        y -= 3;
        x--;
    }
    x = 31;
    y = 20;
    while (x >= 12) {
        for (int i = y; i > 4; i--) {
            texture[x][i][0] = 255;
            texture[x][i][1] = 255;
            texture[x][i][2] = 255;
            texture[x][i][3] = 255;
        }
        y -= 1;
        x--;
    }
    x = 4;
    y = 40;
    while (y >= 18) {
        for (int i = x; i < 32; i++) {
            texture[i][y][0] = 100;
            texture[i][y][1] = 100;
            texture[i][y][2] = 255;
            texture[i][y][3] = 255;
        }
        y -= 1;
        if ((y % 2) == 1)
            x += 2;
        else
            x++;
    }

    for (x = 63; x > 31; x--)
        for (y = 0; y < 64; y++)
            for (int i = 0; i < 4; i++)
                texture[x][y][i] = texture[63 - x][y][i];

    GLuint ID;
    glGenTextures(1, &ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SIZE64, SIZE64, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
    return ID;
}

GLuint Create_Texture_Waterwave(int offset) {
    unsigned char texture[64][64][4];

    int x, y, i;

    for (x = 0; x < 64; x++)
        for (y = 0; y < 32; y++) {
            texture[x][y][0] = 0;
            texture[x][y][1] = 100;
            texture[x][y][2] = 255;
            texture[x][y][3] = 255;
        }

    x = 0;
    y = 4;
    while (y <= 28) {
        for (i = x; i < 32; i++) {
            texture[i][y][0] = 200;
            texture[i][y][1] = 255;
            texture[i][y][2] = 255;
            texture[i][y][3] = 255;
        }
        y++;
        if (y < 9)
            x += 3;
        else if (y == 9)
            x++;
        else if (y == 10)
            x += 2;
        else if (y == 11)
            x++;
        else if (y == 12)
            x += 2;
        else if (y == 13)
            x++;
        else if (y == 14)
            x += 2;
        else if (y == 16)
            x++;
        else if (y == 19)
            x++;
        else if (y == 21)
            x++;
        else if (y == 23)
            x++;
        else if (y == 26)
            x++;
        else
            x++;
    }
    x = 0;
    y = 0;
    while (y <= 24) {
        for (i = x; i < 32; i++) {
            texture[i][y][0] = 0;
            texture[i][y][1] = 100;
            texture[i][y][2] = 255;
            texture[i][y][3] = 255;
        }
        y++;
        if (y < 5)
            x += 3;
        else if (y == 5)
            x++;
        else if (y == 6)
            x += 2;
        else if (y == 7)
            x++;
        else if (y == 8)
            x += 2;
        else if (y == 9)
            x++;
        else if (y == 10)
            x += 2;
        else if (y == 11)
            x++;
        else if (y == 14)
            x++;
        else if (y == 16)
            x++;
        else if (y == 18)
            x++;
        else if (y == 21)
            x++;
        else
            x++;
    }

    for (x = 63; x > 31; x--)
        for (y = 0; y < 32; y++)
            for (i = 0; i < 4; i++)
                texture[x][y][i] = texture[63 - x][y][i];

    for (y = 32; y < 64; y++)
        for (x = 0; x < 64; x++)
            for (i = 0; i < 4; i++) {
                if (x >= 47)
                    texture[x][y][i] = texture[x - 47][y - 32][i];
                else
                    texture[x][y][i] = texture[x + 16][y - 32][i];
            }

    unsigned char wave[64][64][4];
    for (int i = 0; i < SIZE64; i++)
        for (int j = 0; j < SIZE64; j++)
            for (int k = 0; k < 4; k++)
                wave[i][j][k] = texture[i][(j + offset) % SIZE64][k];

    GLuint ID;
    glGenTextures(1, &ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SIZE64, SIZE64, 0, GL_RGBA, GL_UNSIGNED_BYTE, wave);
    return ID;

}

GLuint Create_Texture_Tree() {
    unsigned char texture[SIZE64][SIZE64][4];

    int c;
    for (int i = 0; i < SIZE64; i++) {
        for (int j = 0; j < SIZE64; j++) {
            if (j > i / 2 && j <= 64 - i / 2)
                c = 255;
            else
                c = 0;

            texture[i][j][0] = c / 8;
            texture[i][j][1] = c / 2;
            texture[i][j][2] = c / 4;

            if (c == 255)
                texture[i][j][3] = 255;
            else
                texture[i][j][3] = 0;
        }
    }

    for (int i = 0; i < SIZE64 / 3; i++) {
        for (int j = 0; j < SIZE64 / 2 - 4; j++)
            texture[i][j][3] = 0;
        for (int j = SIZE64 / 2 + 4; j < SIZE64; j++)
            texture[i][j][3] = 0;
    }

    GLuint ID;
    glGenTextures(1, &ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SIZE64, SIZE64, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
    return ID;
}

GLuint Create_Texture_Cloud() {
    unsigned char texture[SIZE64][SIZE64][4];

    int c;
    for (int i = 0; i < SIZE64; i++) {
        for (int j = 0; j < SIZE64; j++) {
            if (i > SIZE64 / 4 + 10 * cos(j / 5) + 5 * sin(j / 7) && i <= SIZE64 / 1.3 - 3 * cos(j / 7) - 2 * sin(j / 4) && j > sin(i / 7) * 5 - cos(i / 9) * 2)
                c = 255;
            else
                c = 0;

            texture[i][j][0] =  texture[i][j][1]  = texture[i][j][2] = c;

            if (c == 255)
                texture[i][j][3] = 255;
            else
                texture[i][j][3] = 0;
        }
    }

    GLuint ID;
    glGenTextures(1, &ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SIZE64, SIZE64, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
    return ID;
}

// https://stackoverflow.com/questions/43265521/opengl-and-sdl-image-texture-issue
GLuint LoadTexture(const char* filename) {
    /*SDL_Surface* sur = IMG_Load(filename);

    int mode = GL_RGB;
    if (sur->format->BytesPerPixel == 4)
        mode = GL_RGBA;

    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, sur->w, sur->h, 0, mode, GL_UNSIGNED_BYTE, sur->pixels);

    return texture;*/
    return 0;
}