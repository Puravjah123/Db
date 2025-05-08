#include <GL/glut.h>
#include <iostream>
using namespace std;
#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
const float x_min = -0.5, y_min = -0.5, x_max = 0.5, y_max = 0.5;
int computeCode(float x, float y) {
    int code = INSIDE;
    if (x < x_min)
        code |= LEFT;
    else if (x > x_max)
        code |= RIGHT;
    if (y < y_min)
        code |= BOTTOM;
    else if (y > y_max)
        code |= TOP;
    return code;
}
bool cohenSutherlandLineClip(float &x0, float &y0, float &x1, float &y1) {
    int code0 = computeCode(x0, y0);
    int code1 = computeCode(x1, y1);
    bool accept = false;
    while (true) {
        if ((code0 == 0) && (code1 == 0)) {
            accept = true;
            break;
        } else if ((code0 & code1) != 0) {
            break;
        } else {
            int code_out = code0 ? code0 : code1;
            float x, y;
            if (code_out & TOP) {
                x = x0 + (x1 - x0) * (y_max - y0) / (y1 - y0);
                y = y_max;
            } else if (code_out & BOTTOM) {
                x = x0 + (x1 - x0) * (y_min - y0) / (y1 - y0);
                y = y_min;
            } else if (code_out & RIGHT) {
                y = y0 + (y1 - y0) * (x_max - x0) / (x1 - x0);
                x = x_max;
            } else if (code_out & LEFT) {
                y = y0 + (y1 - y0) * (x_min - x0) / (x1 - x0);
                x = x_min;
            }
            if (code_out == code0) {
                x0 = x;
                y0 = y;
                code0 = computeCode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
        }
    }

    return accept;
}

void drawLine(float x0, float y0, float x1, float y1) {
    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);
    glEnd();
}

void drawClippingWindow() {
    glBegin(GL_LINE_LOOP);
        glVertex2f(x_min, y_min);
        glVertex2f(x_min, y_max);
        glVertex2f(x_max, y_max);
        glVertex2f(x_max, y_min);
    glEnd();
}

void displayOriginalLine() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    drawClippingWindow();

    float x0 = -0.8f, y0 = -0.7f, x1 = 0.9f, y1 = 0.8f;

    glColor3f(0.0f, 1.0f, 0.0f);
    drawLine(x0, y0, x1, y1);

    glFlush();
}

void displayClippedLine() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    drawClippingWindow();

    float x0 = -0.8f, y0 = -0.7f, x1 = 0.9f, y1 = 0.8f;

    if (cohenSutherlandLineClip(x0, y0, x1, y1)) {
        glColor3f(0.0f, 1.0f, 0.0f);
        drawLine(x0, y0, x1, y1);
    } else {
        glColor3f(1.0f, 0.0f, 0.0f);
        drawLine(x0, y0, x1, y1);
    }

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(500, 500);
    glutCreateWindow("Original Line (Unclipped)");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(displayOriginalLine);
    
    glutInitWindowSize(500, 500);
    glutCreateWindow("Clipped Line");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(displayClippedLine);
    glutMainLoop();
    return 0;
}
