#pragma once
#include "include.h"

int readColoredImage(Mat &image, string address)
{
	string aux = "resources\\";

	aux += address;

	image = imread(aux, IMREAD_COLOR);

	if (image.empty())
	{
		cout << "INVALID READ FOR IMAGE" << address;

		return -1;
	}

	return 0;
}

void toClass()
{
}
