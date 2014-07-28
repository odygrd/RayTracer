#include "stdafx.h"
#include "colour.h"

Colour::Colour(void)
:   red(0.0),
	green(0.0),
	blue(0.0),
	alpha(0.0)
{}

Colour::Colour(float pred, float pgreen, float pblue, float palpha)
:   red(pred), 
	green(pgreen),	
	blue(pblue),	
	alpha(palpha)
{}

void Colour::clear(void)
{
	red = 0.0;
	green = 0.0;
	blue = 0.0;
	alpha = 0.0;
}

Colour& Colour::operator+=(const Colour& rhs)
{

	this->red += rhs.red;
	this->blue += rhs.blue;
	this->green += rhs.green;

	return (*this);
}

Colour& Colour::operator/=(const float a)
{
	this->red /= a;
	this->blue /= a;
	this->green /= a;

	return (*this);
}

Colour& Colour::operator=(const Colour& rhs)
{
	if (this == &rhs)
		return (*this);

	this->red = rhs.red; 
	this->green = rhs.green; 
	this->blue = rhs.blue;
	this->alpha = rhs.alpha;

	return (*this);
}

//used to set light properties for scene.cpp
Colour& Colour::operator=(Colour* rhs)
{
	if (rhs == this)
		return (*this);

	rhs->red  = red;
	rhs->green = green;
	rhs->blue = blue;
	rhs->alpha = alpha;

	return (*this);
}

Colour& Colour::operator*(const Colour& col)
{
	this->red = this->red * col.red;
	this->green = this->green * col.green;
	this->blue = this->blue * col.blue;

	return (*this);
}


Colour& Colour::operator*(const float& n)
{
	this->red = this->red * n;
	this->green = this->green * n;
	this->blue = this->blue * n;

	return (*this);
}