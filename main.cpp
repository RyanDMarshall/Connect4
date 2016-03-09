
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

int main(int argc, char *argv[]) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Connect 4");

    setup();
    glutDisplayFunc(display);

    MovePiece();

    glutMainLoop();

    return 0;
}