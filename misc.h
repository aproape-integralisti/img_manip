#pragma once
#include "include.h"
#include "pixel.h"

void _ImageTransform(Mat const &cv_img, vector<vector<Pixel>> &pixels)
{
	pixels.resize(cv_img.rows, vector<Pixel>(cv_img.cols));

	for (int row = 0; row < cv_img.rows; row++)
	{
		for (int col = 0; col < cv_img.cols; col++)
		{
			pixels[row][col] = cv_img.at<Vec3b>(row, col);
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

int _ImageRead(vector<vector<Pixel>> &pixels, string const& call)
{
	Mat cv_img;

	cv_img = imread(call, IMREAD_COLOR);

	if (_ImageEmpty(cv_img))
	{
		cout << "INVALID READ IN OPENCV AT: " << call << '\n';

		return -1;
	}

	_ImageTransform(cv_img, pixels);

	return 0;
}

//TODO: show name in the window
void zoom(Mat const& cv_img)
{
	Mat src, dst, tmp;

	src = cv_img;

	tmp = src;
	dst = tmp;

	while (char(waitKey(1) != 'q'))
	{
		int c;
		c = waitKey(1);
		if ((char)c == 'u')
		{
			pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
			cout << " ** Zoom In: Image x 2" << endl;
		}
		else if ((char)c == 'd')
		{
			pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
			cout << " ** Zoom Out: Image / 2" << endl;
		}
		imshow("zooming", dst);
		tmp = dst;
	}
}