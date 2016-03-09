
#ifndef WIN32
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h> 

#include "visual.h"
#include "driver.h"

#endif

using namespace std;

int lastPosition = 0;
int turn = 1;
bool moveMade = false;

bool gameIsOver = false;
bool redWins = false;
bool yellowWins = false;
bool tie = false;
bool winnerPrinted = false;

int UNKNOWN = 0;
int RED = 1;
int YELLOW = 2;

int connect4Board[6][7] = {
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0}
};

void printBoard(int board[6][7]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            cout << board[i][j] << ' ';
        }

        cout << endl;
    }
        
    cout << endl << endl;
}

void DrawEmptyCircle(double radius, double centerX, double centerY) {

    glColor3f(0.0f, 0.0f, 0.0f);

    double pi = 3.1415926;

    for (int i = 0; i < 360; i++) {

        double j = (i * pi / 180);
        glVertex3f(centerX, centerY, 0);
        glVertex3f(centerX + (radius * sin(j)), centerY + (radius * cos(j)), 0);
    }

}
void DrawRedCircle(double radius, double centerX, double centerY) {

    glColor3f(255.0f, 0.0f, 0.0f);

    double pi = 3.1415926;

    for (int i = 0; i < 360; i++) {

        double j = (i * pi / 180);
        glVertex3f(centerX, centerY, 0);
        glVertex3f(centerX + (radius * sin(j)), centerY + (radius * cos(j)), 0);
    }

}
void DrawYellowCircle(double radius, double centerX, double centerY) {

    glColor3f(255.0f, 255.0f, 0.0f);

    double pi = 3.1415926;

    for (int i = 0; i < 360; i++) {

        double j = (i * pi / 180);
        glVertex3f(centerX, centerY, 0);
        glVertex3f(centerX + (radius * sin(j)), centerY + (radius * cos(j)), 0);
    }

}

void KeyboardArrows(int key, int x, int y)
{
    switch (key)
    {
    case 100:
        if (lastPosition > -3) {
            lastPosition--;
        }
        display();
        break;
    case 102:
        if (lastPosition < 3) {
            lastPosition++;
        }
        display();
        break;
    default:
        break;
    }

}
void KeyboardEnter(unsigned char key, int x, int y) {

    moveMade = false;

    switch (key) {
    case 'a':
        if (lastPosition > -3) {
            lastPosition--;
        }
        display();
        break;
    case 'd':
        if (lastPosition < 3) {
            lastPosition++;
        }
        display();
        break;
    case ' ':
    case 13:
        for (int i = 0; i < 6; i++) {
            if (connect4Board[i][lastPosition + 3] == 0 && (i + 1 != 0) &&
                (connect4Board[i + 1][lastPosition + 3] != 0 || (i == 5))) {
                connect4Board[i][lastPosition + 3] = turn;

                moveMade = true;
            }

        }

        if (moveMade) {
            SwitchTurn();
            lastPosition = 0;
        }

        display();
        break;

    default:
        break;
    }
}

void MovePiece() {

    lastPosition = 0;

    glutSpecialFunc(KeyboardArrows);
    glutKeyboardFunc(KeyboardEnter);
}
void SwitchTurn() {
    switch (turn) {
    case 1:
        turn = 2;
        break;
    case 2:
        turn = 1;
        break;
    }
}

void setup() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 255.0f);
    glRectf(-0.8f, 0.6f, 0.8f, -0.8f);

    setup();

    if (!gameIsOver) {

        glLineWidth(2.5);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);

        double r = 0.1;

        glColor3f(0.0f, 0.0f, 0.0f);

        if (four_of_color(connect4Board, RED)) {
            redWins = true;
            gameIsOver = true;
            setup();
        }
        else if (four_of_color(connect4Board, YELLOW)) {
            yellowWins = true;
            gameIsOver = true;
            setup();
        }
        else if (!four(connect4Board) && (countUnknownSquares(connect4Board) == 0)) {
            tie = true;
            gameIsOver = true;
            setup();
        }

        if (!gameIsOver) {
            switch (turn) {
                case 1:
                    DrawRedCircle(0.1, (lastPosition * 2.3 * r), 0.75);
                    break;
                case 2:
                    DrawYellowCircle(0.1, (lastPosition * 2.3 * r), 0.75);
                    break;
            }
        }
        else {

            endGame(connect4Board, redWins, yellowWins, tie, winnerPrinted);
        }
        
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                switch (connect4Board[i][j]) {
                case 0:
                    DrawEmptyCircle(r, -.69 + (2.3 * r * j), .475 - (2.3 * r * i));
                    break;
                case 1:
                    DrawRedCircle(r, -.69 + (2.3 * r * j), .475 - (2.3 * r * i));
                    break;
                case 2:
                    DrawYellowCircle(r, -.69 + (2.3 * r * j), .475 - (2.3 * r * i));
                    break;
                }
            }
        }
    }

    glEnd();

    glutSwapBuffers();
}