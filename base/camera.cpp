#include "stdafx.h"
#include "camera.h"

Camera::Camera(Vertex eyepos, Vertex lookat, Vector camup)
{
	//set up canonical frame ..
	w = Vector(eyepos.x - lookat.x, eyepos.y - lookat.y, eyepos.z - lookat.z); //camera direction
	w.normalise();
	u = w.cross(camup); // camera right
	u.normalise();
	v = w.cross(u); //camera up

	d = 1000;      //distance from the viewplane
	zoom = 1.0;   //camera zoom
}