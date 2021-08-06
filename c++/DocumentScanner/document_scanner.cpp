#include<stdio.h>
#include<opencv2/opencv.hpp>
#include<vector>
#include<iostream>
#include<stdlib.h>

using namespace cv;
using namespace std;

Mat resize_image(Mat image)
{
    Mat img;
    resize(image,img, Size(),0.5,0.5);
    return img; 
}


Mat preprocessing(Mat image)
{
    Mat img;
    img = image;

    cvtColor(img, img, COLOR_BGR2GRAY); // BRF to GRAY
    GaussianBlur(img, img, Size(5,5), 15, 1);
    Canny(img, img, 75, 85);
    
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5,5));
    dilate(img,img,kernel);

    return img;
}

vector<Point> getContours(Mat image,Mat output_image)
{
    vector<vector<Point>> contours;
    vector<Vec4i> heirarchy;
    
    findContours(image, contours, heirarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    
    vector<Point> biggestpoints;
    int maxarea = 0;
    
    for(int i=0;i<contours.size();i++)
    {
        int area = contourArea(contours[i]);
        printf("Area of contour %d is %d \n",i,area);
        if(area>2000)
        {
            float p =   arcLength(contours[i],true);
            approxPolyDP(contours[i],conPoly[i], 0.01*p,true);

            if(area>maxarea && conPoly[i].size() == 4)
            {
                drawContours(output_image,conPoly,i,Scalar(0,0,255),5);
                biggestpoints = {conPoly[i][0],conPoly[i][1],conPoly[i][2],conPoly[i][3]};
                maxarea = area;
            }
        }
    }
    return biggestpoints;
}     


void drawPoints(vector<Point> points, Scalar color, Mat image)
{
    for(int i=0;i<points.size();i++)
    {
        circle(image,points[i],30,color,FILLED);
        putText(image,to_string(i),points[i],FONT_HERSHEY_SIMPLEX,5,color,5);
    }
}

vector<Point> reorder(vector<Point> points)
{
    vector<Point> newPoints;
    vector<int> sumpoints, subpoints;
    for(int i=0;i<points.size();i++)
    {
        sumpoints.push_back(points[i].x + points[i].y);
        subpoints.push_back(points[i].x - points[i].y);
    }
    
    newPoints.push_back(points[min_element(sumpoints.begin(), sumpoints.end()) - sumpoints.begin()]);
    newPoints.push_back(points[max_element(subpoints.begin(), subpoints.end()) - subpoints.begin()]);
    newPoints.push_back(points[min_element(subpoints.begin(), subpoints.end()) - subpoints.begin()]);
    newPoints.push_back(points[max_element(sumpoints.begin(), sumpoints.end()) - sumpoints.begin()]);

    return newPoints;
}


Mat getWarped(Mat image, vector<Point> points, float w, float h)
{
    Mat image_out;
    Point2f src[4] = { points[0],points[1],points[2], points[3] };
    Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
    Mat matrix = getPerspectiveTransform(src,dst);
    warpPerspective(image,image_out,matrix,Point(w,h));
    return image_out;
}


int main(int argc, char** argv)
{
    if(argc!=2)
    {
        printf("usage: ./DocumentScanner <Full path to image> \n");
        return 1;
    }
    Mat image, processedimage, image_copy, img, imgwarped;
    
    image = imread(argv[1]);
    img = imread(argv[1]);
    float w = 420.0,h = 590.0;
    //image_copy = resize_image(image);
    processedimage = preprocessing(image);

    vector<Point> initialPoints;
    initialPoints = getContours(processedimage,img);

    vector<Point> docpoints = reorder(initialPoints);
    printf("Number of Points found: %ld \n",initialPoints.size());
    drawPoints(docpoints,Scalar(0,0,255),img);

    imgwarped = getWarped(image,docpoints,w,h);

    imshow("Original",image);
    imshow("Preprocessed",processedimage);
    imshow("Image Copy",img);
    imshow("Document",imgwarped);

    waitKey(0);
    return 0;
}