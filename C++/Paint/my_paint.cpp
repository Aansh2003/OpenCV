#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;


int r,g,b;
int X,Y;
Point top_left = Point(0,0);
Point bottom_right = Point(0,0);
Mat img(480, 640, CV_8UC3, cv::Scalar(255,255,255));
Mat col(200,200,CV_8UC3, cv::Scalar(255,255,255));
Mat mask;
int slide_value1 = 0,slide_value2=0,slide_value3=0;
bool Iscircle = 0;
void cbuttonCallback(int, void *){
     Iscircle = !(circle);
}
static void CallBack(int , void*){
     r = (double) slide_value1;
     g = (double) slide_value2;
     b = (double) slide_value3;
     inRange(col, Scalar(0, 0, 0), Scalar(255, 255, 255), mask);
     col.setTo(Scalar(b, g, r), mask);
     imshow("Colour_track",col);
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
          X = x;
          Y = y;
     }
     else if( event == EVENT_LBUTTONUP )
     {
          double radius = sqrt(pow((X-x),2)+pow((Y-y),2));
          circle(img, Point(X,Y),radius, Scalar(b,g,r),2, LINE_8);
     }
     else if  ( event == EVENT_MBUTTONDOWN )
     {
          r =0,b=0,g=0;
          namedWindow("Colour_track",1);
          createTrackbar("R", "My paint", &slide_value1, 255,CallBack);
          createTrackbar("G", "My paint", &slide_value2, 255,CallBack);
          createTrackbar("B", "My paint", &slide_value3, 255,CallBack);
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
     createButton("Circle",&cbuttonCallback,&Iscircle,QT_RADIOBOX);
     setMouseCallback("My paint", CallBackFunc, NULL);
     while(key!=113)
     {
          imshow("My paint", img);
          key = waitKey(0);
     }
     	destroyAllWindows();
     return 0;
}
