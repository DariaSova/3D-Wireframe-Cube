#include "Canvas.h"
#include <math.h>
#include "eigen/Eigen/Dense"
using namespace Eigen;

unsigned int width = 512;
unsigned int height = 512;

Canvas canvas;

std::vector<Vector4d> points;

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
