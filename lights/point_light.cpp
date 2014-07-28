#include "stdafx.h"
#include "point_light.h"

PointLight::PointLight(Vertex &p, Colour &c) 
	: position(p), intensity(c), direction(0,0,0)
{}

PointLight::PointLight(Vertex &p, Vector &d, Colour &c) 
	: position(p), intensity(c), direction(d)
{}

void PointLight::getLightProperties(Vertex &p, Vector *ldir, Colour *i, Vertex *lpos)
{
	lpos->x = position.x;
	lpos->y = position.y;
	lpos->z = position.z;

	ldir->x = position.x - p.x;
	ldir->y = position.y - p.y;
	ldir->z = position.z - p.z;

	float d = (float) (p.distance(position));

	Colour(intensity.red / d*d, intensity.green / d*d, intensity.blue / d*d, intensity.alpha) = i;
	if (direction.x != 0 || direction.y != 0 || direction.z != 0)
	{
		Colour((float)(i->red * pow(ldir->dot(direction), 2)), (float)(i->green * pow(ldir->dot(direction), 2)), (float)(i->blue * pow(ldir->dot(direction), 2)), intensity.alpha) = i;
	}
}
