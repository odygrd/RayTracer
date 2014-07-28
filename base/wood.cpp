#include "stdafx.h"
#include "wood.h"


Wood::Wood() {
	color1.red = 0.1043;
	color1.green = 0.0737;
	color1.blue = 0.0517;
	color2.red = 0.4215;
	color2.green = 0.2686;
	color2.blue = 0.1888;
	scale = 2;
	shininess = -1;
	reflectivity = -1;
}

Colour Wood::getColor(Vector point) {
	double x = point.x * scale;
	double y = point.y * scale;
	double z = point.z * scale;

	double grain = perlin.noise(x, y, z) * 5;

	grain = grain - (int)grain;

	Colour col;

	col = color1 * grain;
	col+=	color2 * (1.0f - grain);
	return col;
}

double Wood::getShininess() {
	return shininess;
}

double Wood::getReflectivity() {
	return reflectivity;
}