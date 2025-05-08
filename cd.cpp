#include <GL/freeglut.h> 
#include <iostream>

int r, xc, yc, x, y; 
float p;

void putPixel(int px, int py)
{

glBegin(GL_POINTS); 
glVertex2f((float)px, (float)py);
glEnd();
}


void plotPoints(int px, int py)
{

putPixel(xc + px, yc + py); 
putPixel(xc + py, yc + px); 
putPixel(xc + py, yc - px); 
putPixel(xc + px, yc - py); 
putPixel(xc - px, yc - py); 
putPixel(xc - py, yc - px); 
putPixel(xc - px, yc + py); 
putPixel(xc + py, yc - px); 
putPixel(xc - py, yc + px);
}


void drawCircle()
{

glBegin(GL_LINES); 
glVertex2f(-640.0F, 0);
glVertex2f(640.0F, 0); 
glVertex2f(0, -480.0F); 
glVertex2f(0, 480.0F); 
glEnd();
p = 1.25F - (float)r; 
x = 0, y = r;
while (x < y) { 
plotPoints(x, y); 
if (p < 0) {
p += 2.0F * (float)x + 1.0F;

}
else if (p >= 0) {
--y;
p += 2.0F * (float)(x - y) + 1.0F;

}
++x;
}

glFlush();
}
void init()
{

glOrtho(-640.0, 640.0, -480.0, 480.0, -1.0, 1.0); 
glClearColor(0.0F, 0.0F, 1.0F, 0.0F);
glClear(GL_COLOR_BUFFER_BIT); 
glColor3f(1.0F, 1.0F, 1.0F);
}


int main(int argc, char **argv)
{

std::cout << "Enter radius: "; 
std::cin >> r;
std::cout << "Enter X coordinate of center: "; 
std::cin >> xc;
std::cout << "Enter Y coordinate of center: "; 
std::cin >> yc;
r = r * 16; 
xc = xc * 16; 
yc = yc * 16;
glutInit(&argc, argv); 
glutInitDisplayMode(GLUT_SINGLE); 
glutInitWindowSize(640, 480);
glutInitWindowPosition(400, 150); 
glutCreateWindow("Bresenham's Circle Drawing Algorithm"); 
init();
glutDisplayFunc(drawCircle);
glutMainLoop();
return 0;
}
