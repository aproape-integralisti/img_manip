#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "misc.h"

using namespace std;
using namespace cv;

int main()
{
    Mat image = imread("resources\\test.jpg", IMREAD_COLOR);
    Mat another_one = imread("resources\\pic_1.jpg", IMREAD_GRAYSCALE);
    if (image.empty())
    {
        cout << "nuj ba de ce nu merge";

        return 1;
    }

    imshow("boomer", image);
    imshow("alb negru", another_one);
    waitKey(0);

    return 0;
}