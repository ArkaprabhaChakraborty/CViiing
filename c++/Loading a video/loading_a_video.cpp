#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;


int main( int argc, char** argv ) 
{
    if (argc != 2)
    {
        printf("usage: DisplayVideo.out <Image_Path>\n");
        return 1;
    }
    VideoCapture cap(argv[1]); // To use camera use VideoCapture cap(0);
    /*
    This is one of few constructors available in VideoCapture class. 
    This constructor will open the video file and initialize 
    the VideoCapture object for reading the video stream from the specified file.
    */

    namedWindow("Video Capture", WINDOW_NORMAL );

    double fps = cap.get(CAP_PROP_FPS); 
    
    /*
    double VideoCapture::get(int propId) const
    This function returns the value of the specified property of the VideoCapture object. For unsupported properties, this function will return 0.
    propId - This argument specify the property of the VideoCapture object which is to be obtained. Most common properties are 
        CAP_PROP_POS_MSEC - Current position of the video file in milliseconds
        CAP_PROP_POS_FRAMES - Relative position of the frame to be captured next (Starting from 0, e.g. - 0, 1, 2, 3, ...) 
        CAP_PROP_FRAME_WIDTH - Width of the frames in the video
        CAP_PROP_FRAME_HEIGHT - Height of the frames in the video
        CAP_PROP_FPS - Frame rate of the video 
        CAP_PROP_FOURCC - 4-character code of the codec 
        CAP_PROP_FRAME_COUNT - Total number of frames in the video file 
    */

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
