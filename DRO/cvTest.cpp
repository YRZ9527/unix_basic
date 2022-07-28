#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;
int main()
{
    cout << "nihao" << endl;
    Mat img = imread("/Users/yunyi/Desktop/timg.jpeg", IMREAD_GRAYSCALE);
    imshow("imgIuput", img);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
