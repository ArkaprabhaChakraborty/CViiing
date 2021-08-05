#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
int main(int argc, char ** argv)
{
    if(argc !=2)
    {
        printf("usage: ./BasicImageProcessing <ImageFilePath> \n");
        return 1;
    }

    Mat image, gray, blur, canny;
    Mat imgDia,imgErode;
    image = imread(argv[1],1);
    cvtColor(image,gray,COLOR_BGR2GRAY); // BRF to GRAY
    GaussianBlur(image, blur,Size(3,3), 5,0);
    Canny(blur,canny,25,75);
    
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5,5));
    dilate(canny,imgDia,kernel);
    erode(imgDia,imgErode,kernel);

    Mat resized;
    resize(image,resized, Size(1000,300));

    Rect roi(60,120,120,50);

    Mat cropped = image(roi);
    imshow("original",image);
    imshow("Gray",gray);
    imshow("Blur",blur);
    imshow("Canny",canny);    
    imshow("Dilated",imgDia);
    imshow("Erode",imgErode);
    imshow("Resized",resized);
    imshow("Cropped",cropped);

    waitKey(0);
    return 0;
}
