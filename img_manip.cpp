#include "include.h"
#include "image.h"

int main()
{
    Image img_1("pic_17.jpg");

    cout << img_1;

    int dimCentroids = img_1.imageCompress(32);

    //TODO: add this into a functions
  /*  for (int id = 0; id < dimCentroids; id++)
    {
        string nameCluster = "cluster";

        img_1.showCentroid(id, nameCluster);
    }*/

    img_1.printImage();

    return 0;
}