#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "light.h"

class PointLight : public Light
{
	Colour intensity;
	
	Vector direction;
public :
	Vertex position;
	PointLight(Vertex &p, Colour &c);
	PointLight(Vertex &p, Vector &d, Colour &c);
	virtual void getLightProperties(Vertex &p, Vector *ldir, Colour *i, Vertex *lpos);
};
#endif