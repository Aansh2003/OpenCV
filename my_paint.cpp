#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int r=0,g=0,b=0;
Point top_left = Point(0,0);
Point bottom_right = Point(0,0);
Mat img(480, 640, CV_8UC3, cv::Scalar(255,255,255));

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
	  cout<<"Hi";
          img.at<Vec3b>(y,x)[0]=b;
          img.at<Vec3b>(y,x)[1]=g;
          img.at<Vec3b>(y,x)[2]=r;
     }
     else if( event == EVENT_LBUTTONUP )
     {
          
     }
     else if  ( event == EVENT_MBUTTONDOWN )
     {
          int slide_value = 0;
          namedWindow("My Window",0);
          createTrackbar("R", "My Window", nullptr, 100);
          setTrackbarPos("R", "My Window", r);
          createTrackbar("G", "My Window", nullptr, 100);
          setTrackbarPos("G", "My Window", g);
          createTrackbar("B", "My Window", nullptr, 100);
          setTrackbarPos("B", "My Window", b);
     }
     else if ( event == EVENT_RBUTTONDOWN ){
          top_left = Point(x,y);
     }
     else if ( event == EVENT_RBUTTONUP ){
          bottom_right = Point(x,y);
          rectangle(img,top_left,bottom_right,Scalar(b,g,r),2,LINE_8);
     }
}

int main(int argc, char** argv)
{
     int key = 0;
     namedWindow("My paint",1);
     setMouseCallback("My paint", CallBackFunc, NULL);
     while(key!=113)
     {
          imshow("My paint", img);
	  if(key==112){
	  namedWindow("Hello",1);
	  }
          key = waitKey(0);
     }
     	destroyAllWindows();
     return 0;
}
