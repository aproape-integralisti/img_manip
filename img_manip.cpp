#include "include.h"
#include "image.h"

int main()
{
    Image img_1("pic_1.jpg");
  
    cout << img_1;

    img_1.imageCompress(3);

    img_1.printImage();

    return 0;
}