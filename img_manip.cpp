#include "include.h"
#include "image.h"

int main()
{
    Image img_1("pic_14.jpg");
  
    cout << img_1;

    img_1.imageCompress(16);

    img_1.printImage();

    return 0;
}