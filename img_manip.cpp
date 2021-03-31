#include "include.h"
#include "image.h"
#include "img_manip.h"

int main()
{
<<<<<<< Updated upstream
    Image img_1("pic_17.jpg");

    img_1.imageCompress(16);

    //TODO: add this into a functions
    for (int clusters = 0; clusters < 0; clusters++)
    {
        cout << "CLUSTER: " << clusters << endl;
        img_1.showCentroid(clusters);
    }
=======
    Image img_1("pic_10.png");
  
    cout << img_1;

    img_1.imageCompress(3);
>>>>>>> Stashed changes

    img_1.printImage();

    return 0;
}