#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, const char** argv )
{
     Mat img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR); //open and read the image

      if (img.empty())
     {
          cout << "Image cannot be loaded..!!" << endl;
          return -1;
     }

     Size size(64,64);
     resize(img,img,size, INTER_AREA);

      cvtColor(img, img, CV_BGR2GRAY); //change the color image to grayscale image

      Mat img_hist_equalized;
     equalizeHist(img, img_hist_equalized); //equalize the histogram

      //create windows
     namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
     namedWindow("Histogram Equalized", CV_WINDOW_AUTOSIZE);

      //show the image
     imshow("Original Image", img);
     imshow("Histogram Equalized", img_hist_equalized);

      waitKey(0); //wait for key press

      destroyAllWindows(); //destroy all open windows

      return 0;
}
