#ifndef __WOOD_H__
#define __WOOD_H__
 
#include "colour.h"
#include "Vector.h"
#include "perlin.h"
#include "Material.h"

class Wood {
private:
	PerlinNoise perlin;

	Colour color1;
	Colour color2;
	double scale;
	double shininess;
	double reflectivity;

public:
	Wood();

	virtual Colour getColor(Vector);
	virtual double getShininess();
	virtual double getReflectivity();
};

#endif
