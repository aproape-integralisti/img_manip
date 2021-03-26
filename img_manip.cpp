#include "include.h"
#include "misc.h"
#include "init.h"

int main()
{
    Mat image;
    Mat another_one;

    readColoredImage(image, "test.jpg");
    readColoredImage(another_one, "pic_1.jpg");

    imshow("boomer", image);
    imshow("alb negru", another_one);
    waitKey(0);

    return 0;
}