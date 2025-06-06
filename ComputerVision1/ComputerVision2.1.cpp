#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void main() {
	//read the image
	string path = "Images/Images1/bert en ernie.jpg";
	Mat image = imread(path);
	Mat imageGray;
	Mat imageBlur;
	Mat imageBlur2;

	cvtColor(image, imageGray, COLOR_BGR2GRAY);

	GaussianBlur(image, imageBlur, Size(5, 5), 7, 0);
	GaussianBlur(image, imageBlur2, Size(9,9), 7, 0);

	imshow("Image", image);
	imshow("ImageGray", imageGray);
	imshow("ImageBlur", imageBlur);
	imshow("ImageBlur2", imageBlur2);	
	waitKey(0);

}