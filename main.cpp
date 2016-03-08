#include "Canvas.h"
#include <math.h>
#include "Eigen/Dense"
using namespace Eigen;

unsigned int width = 512;
unsigned int height = 512;
bool leftButtonPressed = false;
float mouse_pos_x = 0;
float mouse_pos_y = 0;
float mouse_speed = 0.0001;

// horizontal angle : toward -Z
float horizontal_angle = 0.0f;
// vertical angle : 0, look at the horizon
float vertical_angle = 0.0f;

Canvas canvas;
Vector3f camera(0, 0, 5);
Vector3f center(0, 0, 0);
//visible area on the screen
float n = -1.0f;
float f = -10.0f;
float r = 1.0f;
float t = 1.0f;
float b = -1.0f;
float l = -1.0f;


std::vector<Vector4f> points;
Matrix4f perspective_matrix;
Matrix4f camera_matrix;
Matrix4f final_matrix;

void MouseMove(double x, double y)
{
    if (leftButtonPressed == true) {
    //check in which direction the mouse is moving
    float x_diff = x- mouse_pos_x;
    float y_diff = y -mouse_pos_y;
    //Vector3f camera_n (x_diff, y_diff, 0);

    //update current mouse position
        mouse_pos_x = x;
        mouse_pos_y = y;

        horizontal_angle += mouse_speed * float(width/2 - mouse_pos_x );
        vertical_angle   += mouse_speed * float( height/2 - mouse_pos_y );
    }

    //calculate speed??

}

void MouseButton(MouseButtons mouseButton, bool press)
{
    //check for the left button
    if (mouseButton == LeftButton)
    {
        if (press == true) leftButtonPressed = true;
        else leftButtonPressed = false;

    }
}

void KeyPress(char keychar)
{


}

void OnPaint()
{
    canvas.Clear();



   /* if (leftButtonPressed == true)
    {
        horizontal_angle += mouse_speed * float(width/2 - mouse_pos_x );
        vertical_angle   += mouse_speed * float( height/2 - mouse_pos_y );
    }*/

    Matrix4f Xrotation;
    Xrotation <<
      1, 0, 0, 0,
      0, cos(horizontal_angle), -sin(horizontal_angle), 0,
      0, sin(horizontal_angle), cos(horizontal_angle), 0,
      0, 0, 0, 1;

    Matrix4f Yrotation;
    Yrotation <<
      cos(horizontal_angle), 0, sin(horizontal_angle), 0,
      0, 1, 0, 0,
      -sin(horizontal_angle), 0, cos(horizontal_angle), 0,
      0, 0, 0, 1;



    //compute Mperspective=Morth*Mper
    perspective_matrix <<
      2*n/(r-l), 0, (l+r)/(l-r), 0,
      0, 2*n/(t-b), (b+t)/(b-t), 0,
      0, 0, (n+f)/(n-f), 2*f*n/(f-n),
      0, 0, 1, 0;

    //compute Mcamera
    Vector3f gaze_dir= center - camera; //center-eye_pos
    /*Vector3f gaze_dir (
                cos(vertical_angle) * sin(horizontal_angle),
                sin(vertical_angle),
                cos(vertical_angle) * cos(horizontal_angle)
    );*/
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
      1, 0, 0, -camera[0],
      0, 1, 0, -camera[1],
      0, 0, 1, -camera[2],
      0, 0, 0, 1;

      camera_matrix = MV*temp;
      final_matrix= perspective_matrix*camera_matrix;

  for(int i=0; i<points.size()-1; i++)
  {

    Vector4f p = final_matrix*Yrotation*points[i];
    Vector4f q = final_matrix*Yrotation*points[i+1];

    canvas.AddLine(p[0]/p[2], p[1]/p[2], q[0]/q[2], q[1]/q[2]);

  }
}

void OnTimer()
{

}

int main(int, char **){



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




    //Link the call backs
    canvas.SetMouseMove(MouseMove);
    canvas.SetMouseButton(MouseButton);
    canvas.SetKeyPress(KeyPress);
    //Draw cube
    canvas.SetOnPaint(OnPaint);
    canvas.SetTimer(0.05, OnTimer);
    //Show Window
    canvas.Initialize(width, height, "3D Wireframe Cube");
    canvas.Show();

    return 0;
}
