#pragma once

#include "include.h"
#include "pixel.h"

class Image
{
private:

	string name;
	vector<vector<Pixel>> pixels;
	
public:

	Image() = default;
	Image(string const&);

	bool imageReconstruct(Mat &);
	void printImage();
	void imageCompress(int const &);
	void showCentroid(int const&);

	friend ostream& operator<< (ostream&, Image const&);
};

