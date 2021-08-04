#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;


int main( int argc, char** argv ) 
{
    if (argc != 2)
    {
        printf("usage: DisplayVideo.out <Image_Path>\n");
        return -1;
    }
    VideoCapture cap(argv[1]);
    namedWindow("Video Capture", WINDOW_NORMAL );

    double fps = cap.get(CAP_PROP_FPS); 
    printf("fps is: %lf \n",fps);

    while(true)
    {
        Mat frame;
        int success = cap.read(frame);
        if (success == 0)
        {
            printf("End of video found \n");
            break;
        }

        imshow("Video Capture",frame);
        if (waitKey(10) == 27)
        {
            printf("Enter key is pressed by user \n");
            break;
        }
    }
    return 0;
}
