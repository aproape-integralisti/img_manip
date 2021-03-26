#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat image = imread("resources\\test.jpg", IMREAD_COLOR);

    if (image.empty())
    {
        cout << "nuj ba de ce nu merge";

        return 1;
    }

    imshow("boomer", image);
    waitKey(0);

    return 0;
}