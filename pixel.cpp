#include "pixel.h"

Pixel::Pixel() : r(0), g(0), b(0), cluster_id(-1) {}

///Pixel::Pixel(uint16_t r, uint16_t g, uint16_t b) : r(r), g(g), b(b), cluster(-1), minDist(DBL_MAX) {}

Vec3b Pixel::toVec3b()
{
	Vec3b intensity;

	intensity.val[2] = (uchar)r;
	intensity.val[1] = (uchar)g;
	intensity.val[0] = (uchar)b;

	return intensity;
}

double Pixel::getDistance(Pixel const &px) const {
	return sqrt((px.r - r)*(px.r - r) + (px.g - g)* (px.g - g) + (px.b - b)* (px.b - b));
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