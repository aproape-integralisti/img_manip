#include "image.h"
#include "misc.h"

Image::Image(string const &address)
{
	string call = "resources\\" + address;

	if (_ImageRead(img, call))
	{
		cout << "IMAGE FAILED TO LOAD";
	}
}

ostream& operator<<(ostream& os, Image const &image)
{
	/*for(int i = 0; i < image.img.size(); i++)
	{
		for(int j = 0; j < image.img[0].size(); j++)
		{
			os << image.img[i][j] << " ";
		}
		
		os << "\n";
	}*/

	os << "S-a reusit";
	
	return os;
}