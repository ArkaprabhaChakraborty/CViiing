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

    /*
    convertTo()
    
    void cv::Mat::convertTo(OutputArray m,int rtype, double alpha = 1, double beta = 0)const
    
    Converts an array to another data type with optional scaling.

    The method converts source pixel values to the target data type. saturate_cast<> is applied at the end to avoid possible overflows:
    m(x,y)=saturate_cast<rType>(α(∗this)(x,y)+β)
    
    Parameters
    m:	output matrix; if it does not have a proper size or type before the operation, it is reallocated.
    rtype:	desired output matrix type or, rather, the depth since the number of channels are the same as the input has; if rtype is negative, the output matrix will have the same type as the input.
    alpha:	optional scale factor.
    beta:	optional delta added to the scaled values.
    */




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