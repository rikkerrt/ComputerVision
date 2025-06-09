#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void main() {
	//read the image
	string path = "Images/Images1/ballstripes.bmp";
	Mat image = imread(path);
	Mat imageGray, imageDilate, imageErode;

	cvtColor(image, imageGray, COLOR_BGR2GRAY);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(imageGray, imageDilate, kernel);
	erode(imageDilate, imageErode, kernel);

	imshow("Image", image);
	imshow("Image dilated", imageDilate);
	imshow("Image eroded", imageErode);
	waitKey(0);

}