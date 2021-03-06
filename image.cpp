#include "image.h"
#include "misc.h"
#include "kmeans_remake.h"

Image::Image(string const &address)
{
	string call = "resources\\" + address;

	if (_ImageRead(pixels, call))
	{
		cout << "IMAGE FAILED TO LOAD" << '\n';
	}
	else
	{
		name = address;
	}
}

void Image::imageCompress(int &clusters) {
	 kMeans(pixels, clusters);
}

bool Image::imageReconstruct(Mat &cv_img)
{
	Vec3b intensity;

	for (int row = 0; row < pixels.size(); row++)
	{
		for (int col = 0; col < pixels[0].size(); col++)
		{
			cv_img.at<Vec3b>(row, col) = pixels[row][col].toVec3b();
		}
	}

	if (_ImageEmpty(cv_img))
	{
		cout << "RECONSTRUCTION FAILED FOR: " << name << '\n';
		
		return false;
	}

	cout << "RECONSTRUCTION SUCCESSFULL FOR: " << name << '\n';

	return true;
}


void Image::printImage()
{
	Mat cv_img(pixels.size(), pixels[0].size(), CV_8UC3);

	if (name == "")
	{
		cout << "THERE IS NO IMAGE HERE" << '\n';

		return;
	}

	name += " reconstructed";

	if (imageReconstruct(cv_img)) {
		imshow(name, cv_img);
		waitKey(0);
	}
}

void Image::showCentroid(int const& centroid, string const &nameOfCentroid)
{
	Mat cv_img(pixels.size(), pixels[0].size(), CV_8UC3);
	Vec3b intensity;

	for (int row = 0; row < pixels.size(); row++)
	{
		for (int col = 0; col < pixels[0].size(); col++)
		{
			if (pixels[row][col].cluster_id == centroid)
			{
				cv_img.at<Vec3b>(row, col) = pixels[row][col].toVec3b();
			}
			else
			{
				intensity[2] = 0;
				intensity[1] = 0;
				intensity[0] = 0;

				cv_img.at<Vec3b>(row, col) = intensity;
			}
		}
	}

	imshow(nameOfCentroid, cv_img);
	waitKey(0);
	///zoom(image);
}

ostream& operator<<(ostream& os, Image const &img)
{
	if (!img.pixels.empty())
	{
		os << "SUCCESSFULLY MANAGED TO READ IMAGE AT: " << img.name << '\n';
	}
	
	return os;
}