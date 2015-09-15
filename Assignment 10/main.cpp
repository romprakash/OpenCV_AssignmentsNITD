#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

void conv2(Mat src, int kernel_size)
{
    Mat dst,kernel;
    kernel = Mat::ones( kernel_size, kernel_size, CV_64F )/ (float)(kernel_size*kernel_size);

    /// Apply filter
    filter2D(src, dst, -1 , kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    namedWindow( "filter2D", CV_WINDOW_AUTOSIZE );imshow( "filter2D", dst );
}

int main ( int argc, char** argv )
{
    Mat src;

    /// Load an image
    src = imread( "lena.jpg", CV_LOAD_IMAGE_GRAYSCALE );
    if( !src.data )  { return -1; }

    conv2(src,3);

    namedWindow("OriginalImage", CV_WINDOW_AUTOSIZE);
    imshow("OriginalImage",src);


    waitKey(0);
    return 0;
}
