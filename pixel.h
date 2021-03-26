#pragma once

#include "include.h"

struct Pixel
{
	uint16_t r;
	uint16_t g;
	uint16_t b;

	Vec3b toVec3b();

	Pixel& operator= (Vec3b const&);
	friend ostream& operator<< (ostream&, Pixel const &);
};