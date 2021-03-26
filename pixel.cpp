#include "pixel.h"

Pixel& Pixel::operator=(Vec3b intensity)
{
	r = intensity.val[2];
	g = intensity.val[1];
	b = intensity.val[0];

	return *this;
}

ostream& operator<<(ostream& os, Pixel const &pixel)
{
	os << "[" << pixel.r << ", " << pixel.g << ", " << pixel.b << "]";

	return os;
}