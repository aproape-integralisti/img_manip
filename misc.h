#pragma once
#include "include.h"
#include "pixel.h"

void _ImageTransform(Mat const &cv_img, vector<vector<Pixel>> &img)
{
	img.resize(cv_img.rows, vector<Pixel>(cv_img.cols));

	for (int row = 0; row < cv_img.rows; row++)
	{
		for (int col = 0; col < cv_img.cols; col++)
		{
			img[row][col] = cv_img.at<Vec3b>(row, col);
		}
	}
}

bool _ImageEmpty(Mat const &cv_img)
{
	if (cv_img.empty()) 
	{
		return true;
	}
	return false;
}

int _ImageRead(vector<vector<Pixel>> &img, string const& call)
{
	Mat cv_img;

	cv_img = imread(call, IMREAD_COLOR);

	if (_ImageEmpty(cv_img))
	{
		cout << "INVALID READ IN OPENCV AT: " << call << '\n';

		return -1;
	}

	_ImageTransform(cv_img, img);

	return 0;
}
