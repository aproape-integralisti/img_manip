#include "include.h"
#include "image.h"

int main()
{
    Image img_1("pic_17.jpg");

    int K = 64;
    img_1.imageCompress(K);

    img_1.printImage();

    cout << K << endl;
    return 0;
}