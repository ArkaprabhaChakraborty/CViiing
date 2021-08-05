#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    if(argc!=1)
    {
        printf("usage ./WarpPerspective \n");
        return -1;
    }
    char* image_path = "/home/arkaprabha/CViiing/photos/cards.jpg";
    
    Mat image, warped, crop;
    float h = 350, w = 250;

    image = imread(image_path,1);
    Point2f src[4] = { {111,219},{287,188},{152,480},{352,440} };
    Point2f dst[4] = {{0,0},{w,0},{0,h},{w,h}};
    crop = getPerspectiveTransform(src,dst);
    warpPerspective(image,warped,crop,Point(w,h));
    
    for(int i = 0;i<4;i++)
    {
       circle(image,src[i],10,Scalar(0,0,255),FILLED);
    }

    imshow("Original Image",image);
    imshow("Warped image",warped);  
    waitKey(0);
    return 0;
}
