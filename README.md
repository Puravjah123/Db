1. Header Includes and Global Variables
cpp
#include <GL/freeglut.h>  // Includes OpenGL Utility Toolkit for window management
#include <iostream>       // For input/output operations

int r, xc, yc, x, y;     // r=radius, xc/yc=center coordinates, x/y=current pixel coordinates
float p;                  // Decision parameter for Bresenham's algorithm
2. putPixel Function
cpp
void putPixel(int px, int py)
{
    glBegin(GL_POINTS);          // Begin drawing points
    glVertex2f((float)px, (float)py);  // Draw a single point at (px, py)
    glEnd();                     // End drawing points
}
This function draws a single pixel at the specified coordinates.

3. plotPoints Function (8-Way Symmetry)
cpp
void plotPoints(int px, int py)
{
    // Draws 8 symmetric points for each calculated point to form a complete circle
    putPixel(xc + px, yc + py);  // Octant 1
    putPixel(xc + py, yc + px);  // Octant 2
    putPixel(xc + py, yc - px);  // Octant 3
    putPixel(xc + px, yc - py);  // Octant 4
    putPixel(xc - px, yc - py);  // Octant 5
    putPixel(xc - py, yc - px);  // Octant 6
    putPixel(xc - px, yc + py);  // Octant 7
    putPixel(xc - py, yc + px);  // Octant 8
}
This function uses circle symmetry to plot 8 points for each calculated point, covering all octants.

4. drawCircle Function (Bresenham's Algorithm)
cpp
void drawCircle()
{
    // Draw coordinate axes
    glBegin(GL_LINES); 
    glVertex2f(-640.0F, 0);  // X-axis from left to right
    glVertex2f(640.0F, 0); 
    glVertex2f(0, -480.0F);   // Y-axis from bottom to top
    glVertex2f(0, 480.0F); 
    glEnd();
    
    // Initialize Bresenham's algorithm parameters
    p = 1.25F - (float)r;  // Initial decision parameter
    x = 0, y = r;           // Start at top of circle
    
    // Main algorithm loop
    while (x < y) { 
        plotPoints(x, y);    // Plot the current points
        
        // Update decision parameter
        if (p < 0) {
            p += 2.0F * (float)x + 1.0F;  // Move horizontally
        }
        else if (p >= 0) {
            --y;                          // Move diagonally
            p += 2.0F * (float)(x - y) + 1.0F;
        }
        ++x;  // Always increment x
    }
    
    glFlush();  // Force execution of OpenGL commands
}
This implements Bresenham's circle drawing algorithm, which efficiently determines which pixels to plot.

5. init Function (OpenGL Initialization)
cpp
void init()
{
    // Set up orthographic projection (2D coordinate system)
    glOrtho(-640.0, 640.0, -480.0, 480.0, -1.0, 1.0); 
    
    // Set clear color to blue and clear the screen
    glClearColor(0.0F, 0.0F, 1.0F, 0.0F);
    glClear(GL_COLOR_BUFFER_BIT); 
    
    // Set drawing color to white
    glColor3f(1.0F, 1.0F, 1.0F);
}
Initializes OpenGL settings for our 2D drawing.

6. main Function (Program Entry Point)
cpp
int main(int argc, char **argv)
{
    // Get user input for circle parameters
    std::cout << "Enter radius: "; 
    std::cin >> r;
    std::cout << "Enter X coordinate of center: "; 
    std::cin >> xc;
    std::cout << "Enter Y coordinate of center: "; 
    std::cin >> yc;
    
    // Scale up coordinates (likely for higher resolution)
    r = r * 16; 
    xc = xc * 16; 
    yc = yc * 16;
    
    // Initialize GLUT
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE);  // Single buffer mode
    glutInitWindowSize(640, 480);      // Window size
    glutInitWindowPosition(400, 150);  // Window position
    glutCreateWindow("Bresenham's Circle Drawing Algorithm"); 
    
    // Initialize OpenGL and start main loop
    init();
    glutDisplayFunc(drawCircle);  // Set display callback
    glutMainLoop();              // Enter event processing loop
    
    return 0;
}
Key Notes:
The code implements Bresenham's circle algorithm which is efficient as it uses only integer arithmetic.

The 8-way symmetry reduces calculations by only computing points for one octant.

The scaling (×16) is likely used to allow for sub-pixel precision in the input coordinates.

OpenGL's coordinate system has (0,0) at the center of the window in this setup.

The decision parameter p determines whether to move straight right or diagonally down-right at each step.
