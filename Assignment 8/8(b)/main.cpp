//The intensity of sharpness increases with every keystroke of Esc.

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int main( int argc, char** argv )
{
     //create 2 empty windows
     namedWindow( "Original Image" , CV_WINDOW_AUTOSIZE );
     namedWindow( "Sharpened Image" , CV_WINDOW_AUTOSIZE );

      // Load an image from file
     Mat src = imread( "lena.jpg", CV_LOAD_IMAGE_GRAYSCALE );
     Size size(64,64);
     resize(src,src,size, INTER_AREA);
      //show the loaded image
     imshow( "Original Image", src );

      Mat dst;
      char zBuffer[35];
      for ( int i = 1; i  <  31; i = i + 2 )
     {
       //smooth the image using Gaussian kernel in the "src" and save it to "dst"
      GaussianBlur( src, dst, Size( i, i ), 0, 0 );
      //You use a gaussian smoothing filter and subtract the smoothed version from the original image
      //(in a weighted way so the values of a constant area remain constant).
      addWeighted(src, 1.5, dst, -0.5, 0, dst); // from stackoverflow
       //show the sharpened image with the text
      imshow( "Sharpened Image", dst );

       //wait for 2 seconds
      int c = waitKey(2000);

       //if the "esc" key is pressed during the wait, return
      if (c == 27)
      {
       return 0;
      }
     }

      //make the "dst" image, black
     dst = Mat::zeros( src.size(), src.type() );

        //show the black image with the text
     imshow( "Sharpened Image", dst );


     waitKey(0);

     return 0;
}
