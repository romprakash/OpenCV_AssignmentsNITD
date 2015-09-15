#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<vector>
#include<iostream>


using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{

    Mat img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty())
       return -1;
  //  namedWindow( "lena", CV_WINDOW_AUTOSIZE );
  //  imshow("lena", img);


    Mat ResizeLena = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
    Size size(64,64);//the dst image size,e.g.100x100
    //Mat ResizeLena;//dst image
    //Mat img;//src image
    resize(ResizeLena,ResizeLena,size, INTER_AREA);//resize image
    namedWindow( "lena", CV_WINDOW_AUTOSIZE );
    imshow("lena", ResizeLena);


    cout<<"Rows : "<<ResizeLena.rows;
    cout<<ResizeLena;


    Mat im = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    namedWindow("lenaGray", CV_WINDOW_AUTOSIZE);
    imshow("lenaGray", im);

   Mat imageHist = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);

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

    for(int i = 0; i < 256; i++)
        cout<<histogram[i]<<" ";

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

    //namedWindow("Image", CV_WINDOW_AUTOSIZE);
    //imshow("Image", imageHist);


    waitKey(0);
    return 0;
}
