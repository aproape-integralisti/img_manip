#include "pixel.h"

Vec3b Pixel::toVec3b()
{
	Vec3b intensity;

	intensity.val[2] = (uchar)r;
	intensity.val[1] = (uchar)g;
	intensity.val[0] = (uchar)b;

	return intensity;
}

Pixel& Pixel::operator=(Vec3b const &intensity)
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