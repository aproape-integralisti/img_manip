#pragma once

#include "include.h"

struct Pixel
{
	uchar r, g, b;
	int cluster;

	Pixel();
	///Pixel(uint16_t, uint16_t, uint16_t);

	Vec3b toVec3b();
	double distance(Pixel const&);

	Pixel& operator= (Vec3b const&);
	friend ostream& operator<< (ostream&, Pixel const &);
};