#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int hmin = 0, smin = 110, vmin = 153;
int hmax = 19, smax = 240, vmax = 255;

void main() {
	//read the image
	string path = "Images/Images1/kerstballen.bmp";
	Mat image = imread(path);
	Mat imageHSV, mask, imageDilate, imageErode;

	namedWindow("trackbars", (640, 200));
	createTrackbar("hue Min", "trackbars", &hmin, 179);
	createTrackbar("hue Max", "trackbars", &hmax, 179);

	createTrackbar("sat Min", "trackbars", &smin, 255);
	createTrackbar("sat Max", "trackbars", &smax, 255);

	createTrackbar("val Min", "trackbars", &vmin, 255);
	createTrackbar("val Max", "trackbars", &vmax, 255);



	while (true) {
		cvtColor(image, imageHSV, COLOR_BGR2HSV);

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imageHSV, lower, upper, mask);

		Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
		erode(mask, imageErode, kernel);
		dilate(imageErode, imageDilate, kernel);

		imshow("image", image);
		imshow("imageHSV", imageHSV);
		imshow("image mask", mask);
		imshow("imageDilate", imageDilate);
		waitKey(1);
	}
}