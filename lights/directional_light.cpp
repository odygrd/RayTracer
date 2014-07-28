// a simple directional light source
#include "stdafx.h"
#include "directional_light.h"


// specified by a direction and a colour

DirectionalLight::DirectionalLight(Vector &d, Colour &i)
{
	direction.x = -d.x;
	direction.y = -d.y;
	direction.z = -d.z;
	direction.normalise();
	intensity = Colour(i.red, i.green, i.blue, i.alpha);
	position = Vertex(0, 0,0, 1);
}

// provide the intensity and direction from which light arrives at given vertex

void DirectionalLight::getLightProperties(Vertex &pos, Vector *ldir, Colour *i, Vertex *lpos)
{
	lpos->x = position.x;
	lpos->y = position.y;
	lpos->z = position.z;

	// the direction is always the same (light is infinitely far away)
	ldir->x = direction.x;
	ldir->y = direction.y;
	ldir->z = direction.z;

	// the intensity is always the same (not dependent on where it's going
	Colour(intensity.red, intensity.green, intensity.blue, intensity.alpha) = i;
}
