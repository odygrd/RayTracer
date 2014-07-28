#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vertex.h"
#include "vector.h"
#include "raytrace.h"

#define _USE_MATH_DEFINES // for C++
#include <cmath>

class Camera {
public:
	Vector w;
	Vector u;
	Vector v;
	
	float	d;		// view plane distance
	float	zoom;	// zoom factor

	Camera(Vertex eyepos, Vertex lookat, Vector camup);

};
#endif