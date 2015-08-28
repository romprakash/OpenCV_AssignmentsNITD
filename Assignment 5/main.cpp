#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

int threshold_value = 200;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
char* window_name = "Threshold";

char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";

/// Function headers
void Threshold_Demo( int, void* );

/**
 * @function main
 */
int main( int argc, char** argv )
{

  /// Load an image and resize it to 64X64
    Mat src = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
    Size size(64,64);
    resize(src,src,size, INTER_AREA);

  /// Convert the image to Gray
  cvtColor( src, src_gray, CV_RGB2GRAY );

  /// Create a window to display results
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Create Trackbar to choose type of Threshold
  createTrackbar( trackbar_type,
                  window_name, &threshold_type,
                  max_type, Threshold_Demo );

  createTrackbar( trackbar_value,
                  window_name, &threshold_value,
                  max_value, Threshold_Demo );

  /// Call the function to initialize
  Threshold_Demo( 0, 0 );

  /// Histogram
  Mat imageHist = src;

    // allcoate memory for no of pixels for each intensity value
    int histogram[256];

    // initialize all intensity values to 0
    for(int i = 0; i < 255; i++)
    {
        histogram[i] = 0;
    }

    // calculate the no of pixels for each intensity values
    for(int y = 0; y < imageHist.rows; y++)
        for(int x = 0; x < imageHist.cols; x++)
            histogram[(int)imageHist.at<uchar>(y,x)]++;


    // draw the histograms
    int hist1_w = 512; int hist1_h = 400;
    int bin1_w = cvRound((double) hist1_w/256);

    Mat histImage1(hist1_h, hist1_w, CV_8UC1, Scalar(255, 255, 255));

    // find the maximum intensity element from histogram
    int max = histogram[0];
    for(int i = 1; i < 256; i++){
        if(max < histogram[i]){
            max = histogram[i];
        }
    }

    // normalize the histogram between 0 and histImage.rows

    for(int i = 0; i < 255; i++){
        histogram[i] = ((double)histogram[i]/max)*histImage1.rows;
    }


    // draw the intensity line for histogram
    for(int i = 0; i < 255; i++)
    {
        line(histImage1, Point(bin1_w*(i), hist1_h),
                              Point(bin1_w*(i), hist1_h - histogram[i]),
             Scalar(0,0,0), 1, 8, 0);
    }

    // display histogram
    namedWindow("Intensity Histogram", CV_WINDOW_AUTOSIZE);
    imshow("Intensity Histogram", histImage1);


  /// Wait until user finishes program
  while(true)
  {
    int c;
    c = waitKey( 20 );
    if( (char)c == 27 )
      { break; }
   }

}


/**
 * @function Threshold_Demo
 */
void Threshold_Demo( int, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

  threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );

  imshow( window_name, dst );
}
