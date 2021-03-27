#pragma once

#include "include.h"
#include "pixel.h"

class Image
{
private:

	string name;
	vector<vector<Pixel>> img;
	
public:

	Image() = default;
	Image(string const&);

	void imageReconstruct(Mat &);
	void printImage();
	void kmeans();

	friend ostream& operator<< (ostream&, Image const&);
};

