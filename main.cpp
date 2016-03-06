#include "Canvas.h"
#include <math.h>
#include "eigen/Eigen/Dense"
using namespace Eigen;

unsigned int width = 512;
unsigned int height = 512;

Canvas canvas;
float Distance = 5.0f;
float n = 1.0f;
float f = 5.0f;
float r = 1.0f;
float t = 1.0f;
float b = -1.0f;
float l = -1.0f;
std::vector<Vector4d> points;
Matrix4d viewport_matrix;
Matrix4d perspective_matrix;


void InitializeGL()
{

}

void MouseMove(double x, double y)
{

}

void MouseButton(MouseButtons mouseButton, bool press)
{

}

void KeyPress(char keychar)
{

}

void OnPaint()
{

}

void OnTimer()
{

}

int main(int, char **){
    points.push_back(Vector4d(1, 1, 1, 1));
    points.push_back(Vector4d(1, -1, 1, 1));
    points.push_back(Vector4d(1, -1, -1, 1));
    points.push_back(Vector4d(1, 1, -1, 1));
    points.push_back(Vector4d(-1, 1, 1, 1));
    points.push_back(Vector4d(-1, -1, 1, 1));
    points.push_back(Vector4d(-1, -1, -1, 1));
    points.push_back(Vector4d(-1, 1, -1, 1));

    //compute Mvp
    viewport_matrix <<
            width/2, 0, 0, (width-1)/2,
            0, height/2, 0, (height-1)/2,
            0, 0, 1, 0,
            0, 0, 0, 1;

    //compute Mperspective=Morth*Mper
    perspective_matrix <<
            2*n/(r-l), 0, (l+r)/(l-r), 0,
            0, 2*n*(t-b), (b+t)/(b-t), 0,
            0, 0, (n+f)/(n-f), -2*f*n/(f-n),
            0, 0, 1, 0;

    //compute Mcamera
    //draw lines for all the points

    //Link the call backs
    canvas.SetMouseMove(MouseMove);
    canvas.SetMouseButton(MouseButton);
    canvas.SetKeyPress(KeyPress);
    canvas.SetOnPaint(OnPaint);
    canvas.SetTimer(0.05, OnTimer);
    //Show Window
    canvas.Initialize(width, height, "OpenGL Intro Demo");
    //Do our initialization
    InitializeGL();
    canvas.Show();

    return 0;
}
