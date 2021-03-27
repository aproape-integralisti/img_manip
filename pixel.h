#pragma once

#include "include.h"

struct Pixel
{
	uint16_t r, g, b;
	int cluster;
	double minDist;

	Pixel();
	Pixel(uint16_t, uint16_t, uint16_t);

	Vec3b toVec3b();
	double distance(Pixel const&);

	Pixel& operator= (Vec3b const&);
	friend ostream& operator<< (ostream&, Pixel const &);
};