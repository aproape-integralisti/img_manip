#include "include.h"
#include "image.h"

int main()
{
    Image img_1("pic_11.jpg");
  
    cout << img_1;

    img_1.imageCompress(10);

    img_1.printImage();

    return 0;
}