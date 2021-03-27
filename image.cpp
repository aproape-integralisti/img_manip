#include "image.h"
#include "misc.h"
#include "kmeans.h"

Image::Image(string const &address)
{
	string call = "resources\\" + address;

	if (_ImageRead(img, call))
	{
		cout << "IMAGE FAILED TO LOAD" << '\n';
	}
	else
	{
		name = address;
	}
}

void Image::kmeans() {
	kMeansClustering(img, 2, 3);
}

void Image::imageReconstruct(Mat &image)
{
	Vec3b intensity;

	for (int row = 0; row < img.size(); row++)
	{
		for (int col = 0; col < img[0].size(); col++)
		{
			image.at<Vec3b>(row, col) = img[row][col].toVec3b();
		}
	}

	if (image.empty())
	{
		cout << "RECONSTRUCTION FAILED FOR: " << name << '\n';
		
		return;
	}

	cout << "RECONSTRUCTION SUCCESSFULL FOR: " << name << '\n';
}


void Image::printImage()
{
	Mat image(img.size(), img[0].size(), CV_8UC3);

	if (name == "")
	{
		cout << "THERE IS NO IMAGE HERE" << '\n';

		return;
	}

	name += " reconstructed";

	imageReconstruct(image);

	imshow(name, image);
	waitKey(0);
}

ostream& operator<<(ostream& os, Image const &image)
{
	/*for(int i = 0; i < image.img.size(); i++)
	{
		for(int j = 0; j < image.img[0].size(); j++)
		{
			os << image.img[i][j] << " ";
		}
		
		os << '\n';
	}*/

	os << "SUCCESSFULLY MANAGED TO READ IMAGE AT: " << image.name << '\n';
	
	return os;
}