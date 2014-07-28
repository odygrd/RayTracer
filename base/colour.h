#ifndef _COLOUR_H_
#define _COLOUR_H_

class Colour {
public:
	float red;
	float green;
	float blue;
	float alpha;

	Colour(void);
	Colour(float pred, float pgreen, float pblue, float palpha);

	void clear(void);

	Colour& operator+= (const Colour& rhs);
	Colour& operator/= (const float a);
	Colour& operator= (const Colour& rhs);
	Colour& operator= (Colour* rhs);
	Colour& operator* (const Colour& col);
	Colour& operator* (const float& n);
};

#endif
