#include "include.h"
#include "image.h"

int main()
{
    Image img_1("pic_5.png");
  
    cout << img_1;

    img_1.kmeans();

    img_1.printImage();

    return 0;
}