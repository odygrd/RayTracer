#ifndef _RAYTRACE_H_
#define _RAYTRACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <chrono>

#include "scene.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "cone.h"
#include "qsphere.h"
#include "ellipsoid.h"
#include "cylinder.h"
#include "directional_light.h"
#include "point_light.h"
#include "output.h"
#include "camera.h"
#include "viewplane.h"
#include "transform.h"
#include "constants.h"
#include "wood.h"

typedef unsigned char uchar;

double frand();
void write_framebuffer();
void saveppm(const char *filename);
void savebmp(const char *filename);
void clear_framebuffer();

#endif