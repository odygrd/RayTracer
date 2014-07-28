#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "vertex.h"
#include "vector.h"
#include "colour.h"
#include <math.h>
#include <string>

class Light {
	Light *lt_next;
public:
	Vertex position;
	Light(void);
	void link(Light *light);
	Light *next(void);
	virtual void getLightProperties(Vertex &pos, Vector *ldir, Colour *i, Vertex *lpos);
};

#endif
