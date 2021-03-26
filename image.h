#pragma once

#include "include.h"
#include "pixel.h"

class Image
{
private:

	vector<vector<Pixel>> img;
	
public:

	Image(string const&);

	friend ostream& operator<< (ostream&, Image const&);
};

