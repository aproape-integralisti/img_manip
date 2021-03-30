#include "include.h"
#include "image.h"

int main()
{
    Image img_1("pic_1.jpg");
    Image img_2("pic_1.jpg");
    Image img_3("pic_1.jpg");

    img_1.imageCompress(16);
    img_2.imageCompress(16);
    img_3.imageCompress(16);

    img_1.printImage();
    img_2.printImage();
    img_3.printImage();
    
    return 0;
}