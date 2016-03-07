#include "Canvas.h"
#include <math.h>
#include "Eigen/Dense"
using namespace Eigen;

unsigned int width = 512;
unsigned int height = 512;

Canvas canvas;
float distance = 10.0f;
Vector3f camera(1, 0, 0);
float n = 1.0f;
float f = 5.0f;
float r = 1.0f;
float t = 1.0f;
float b = -1.0f;
float l = -1.0f;
std::vector<Vector4f> points;
Matrix4f viewport_matrix;
Matrix4f perspective_matrix;
Matrix4f camera_matrix;
Matrix4f final_matrix;


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
   // printf("Matrix Size: %lu\n", points.size());

    for(int i=0; i<points.size()-1; i++)///i+2???
    {
        Vector4f p = final_matrix*points[i];
        Vector4f q = final_matrix*points[i+1];
        printf("Point X: %f, %f Y: %f, %f\n", p[0], p[1], q[0], q[1]);

        canvas.AddLine(5*p[0]/p[2], 5*p[1]/p[2], 5*q[0]/q[2], 5*q[1]/q[2]);
        //canvas.AddLine(0,0.2,0.9,0.9);

    }
}

void OnTimer()
{

}

int main(int, char **){
    /*points.push_back(Vector4f(-1, 1, 1, 1));
    points.push_back(Vector4f(1, 1, 1, 1));
    points.push_back(Vector4f(-1, -1, 1, 1));
    points.push_back(Vector4f(1, -1, 1, 1));
    points.push_back(Vector4f(-1, 1, -1, 1));
    points.push_back(Vector4f(1, 1, -1, 1));
    points.push_back(Vector4f(1, -1, -1, 1));
    points.push_back(Vector4f(-1, -1, -1, 1));
    //points.push_back(Vector4f(-1, 1, 1, 1));*/

    //front
    points.push_back(Vector4f(1, 1, 1, 1));
    points.push_back(Vector4f(1, -1, 1, 1));
    points.push_back(Vector4f(-1, -1, 1, 1));
    points.push_back(Vector4f(-1, 1, 1, 1));
    points.push_back(Vector4f(1, 1, 1, 1));

    //rightside
    points.push_back(Vector4f(1, 1, -1, 1));
    points.push_back(Vector4f(1, -1, -1, 1));
    points.push_back(Vector4f(1, -1, 1, 1));
    points.push_back(Vector4f(1, 1, 1, 1));
    points.push_back(Vector4f(1, 1, -1, 1));

    //back
    points.push_back(Vector4f(1, 1, -1, 1));
    points.push_back(Vector4f(1, -1, -1, 1));
    points.push_back(Vector4f(-1, -1, -1, 1));
    points.push_back(Vector4f(-1, 1, -1, 1));
    points.push_back(Vector4f(1, 1, -1, 1));

    //leftside
    points.push_back(Vector4f(-1, 1, -1, 1));
    points.push_back(Vector4f(-1, 1, 1, 1));
    points.push_back(Vector4f(-1, -1, 1, 1));
    points.push_back(Vector4f(-1, -1, -1, 1));


    //compute Mvp
    viewport_matrix <<
            width/2, 0, 0, (width-1)/2,
            0, height/2, 0, (height-1)/2,
            0, 0, 1, 0,
            0, 0, 0, 1;

    //compute Mperspective=Morth*Mper
    perspective_matrix <<
            2*n/(r-l), 0, (l+r)/(l-r), 0,
            0, 2*n/(t-b), (b+t)/(b-t), 0,
            0, 0, (n+f)/(n-f), 2*f*n/(f-n),
            0, 0, 1, 0;

    //compute Mcamera
    Vector3f eye_position = camera* distance;
    Vector3f gaze_dir= eye_position*(-1);
    Vector3f up_vector(0, 1, 0);
    Vector3f w = -(gaze_dir/gaze_dir.norm());
    Vector3f u = ((up_vector.cross(w))/(up_vector.cross(w)).norm());
    Vector3f v = w.cross(u);

    Matrix4f MV;
            MV <<
               u[0], u[1], u[2], 0,
               v[0], v[1], v[2], 0,
               w[0], w[1], w[2], 0,
               0, 0, 0, 1;
    printf("MV X: %f, %f Y: %f, %f\n", MV(0,0), MV(0,1), MV(0,2), MV(0,3));

    Matrix4f temp;
    temp <<
          1, 0, 0, -eye_position[0],
          0, 1, 0, -eye_position[1],
          0, 0, 1, -eye_position[2],
          0, 0, 0, 1;
    printf("TEMP X: %f, %f Y: %f, %f\n", temp(0,0), temp(0,1), temp(0,2), temp(0,3));

    camera_matrix = MV*temp;

   //final_matrix= viewport_matrix*perspective_matrix*camera_matrix;
    final_matrix= perspective_matrix*camera_matrix;
    printf("FINAL X: %f, %f Y: %f, %f\n", final_matrix(0,0), final_matrix(0,1), final_matrix(0,2), final_matrix(0,3));
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
