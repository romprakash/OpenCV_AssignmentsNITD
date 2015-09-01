#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;

int main(int argc, char** argv)
{
   namedWindow("Initial Image" , CV_WINDOW_AUTOSIZE);

   // Load the source image
   Mat src = imread( "lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);

   Size size(64,64);
   resize(src,src,size, INTER_AREA);

   // Create a destination Mat object
   Mat dst;

   // display the source image
   imshow("Initial Image", src);

   for (int i=1; i<51; i=i+2)
   {
      // Median smoothing
      medianBlur( src, dst, i );

      // show the blurred image with the text
      imshow( "Median filter", dst );

      // wait for 5 seconds
      waitKey(5000);
   }
}
