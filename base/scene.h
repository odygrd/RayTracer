#ifndef _SCENE_H_
#define _SCENE_H_

#include <math.h>
#include <iostream>
#include "object.h"
#include "light.h"
#include "constants.h"
#include "vertex.h"

class Scene {
private:
	Object *scache;
	Object *obj_list;
	Light  *light_list;
	Vertex eyepos;

	
public:
	Scene(void);
	void addObject(Object &obj);
	void addLight(Light &light);
	Colour raytrace(Ray &ray, int level);
	bool shadowtrace(Ray &ray, Vertex lpos,  double tlimit);

};


#endif
