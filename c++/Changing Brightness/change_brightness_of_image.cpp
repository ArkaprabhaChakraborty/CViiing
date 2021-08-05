#include<stdio.h>
#include<opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("usage: ./DisplayImageTransforms <Full path to Image> \n");
        return -1;
    }

    Mat image;
    image  = imread(argv[1],1);

    if(!image.data)
    {
        printf("Image data couldn't be read \n");
        return -1;
    }
    Mat image_brightness_50, image_brightness_100, image_brightness_m_50 , image_brightness_m_100;

    image.convertTo(image_brightness_50, -1, 1, 50);
    image.convertTo(image_brightness_100, -1, 1, 100);
    image.convertTo(image_brightness_m_50, -1, 1, -50);
    image.convertTo(image_brightness_m_100, -1, 1, -100);

    namedWindow("Original",WINDOW_AUTOSIZE);
    namedWindow("Increased 50% brightness",WINDOW_AUTOSIZE);
    namedWindow("Increased 100% brightness",WINDOW_AUTOSIZE);
    namedWindow("Decreased 50% brightness",WINDOW_AUTOSIZE);
    namedWindow("Decreased 100% brightness",WINDOW_AUTOSIZE);
    
    imshow("Original",image);
    imshow("Increased 50% brightness",image_brightness_50);
    imshow("Increased 100% brightness",image_brightness_100);
    imshow("Decreased 50% brightness",image_brightness_m_50);
    imshow("Decreased 100% brightness",image_brightness_m_100);
    

    waitKey(0);
    destroyAllWindows();

    return 0;
}