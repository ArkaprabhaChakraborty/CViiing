#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    if(argc!=2)
    {
        printf("usage ./ColorDetection <Full_path_for_the_IMAGE> \n");
        return 1;
    }
    Mat image = imread(argv[1]);
    int hmin=0,smin=0,vmin=0;
    int hmax=0,smax=0,vmax=0;
    Mat img,mask;
    cvtColor(image,img,COLOR_BGR2HSV);
    namedWindow("Trackbar",(700,250));
    createTrackbar("Hue Min","Trackbar",&hmin,179);
    createTrackbar("Sat Min","Trackbar",&smin,255);
    createTrackbar("Vue Min","Trackbar",&vmin,255);
    createTrackbar("Hue Max","Trackbar",&hmax,179);
    createTrackbar("Sat Max","Trackbar",&smax,255);
    createTrackbar("vue Max","Trackbar",&vmax,255);

    while(true)
    {
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(img,lower,upper,mask);
        imshow("Original",image);
        imshow("HSV converted",img);
        imshow("Mask",mask);
        waitKey(27);
    }
    destroyAllWindows();
    return 0;
}