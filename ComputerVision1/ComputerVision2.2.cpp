#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void main() {
	//read the image
	string path = "Images/Images1/kever.jpg";
	Mat image = imread(path);
	Mat imageGray, imageBlur, imageCanny, imageDilate, imageErode;
	int low = 25, high = 75;


	namedWindow("trackbars", (640, 200));
	createTrackbar("hue Min", "trackbars", &low, 500);
	createTrackbar("hue Max", "trackbars", &high, 500);

	cvtColor(image, imageGray, COLOR_BGR2GRAY);
	GaussianBlur(imageGray, imageBlur, Size(3, 3), 3, 0);

	while (1) {
		Canny(imageBlur, imageCanny, low, high);

		Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
		/*dilate(imageCanny, imageDilate, kernel);
		erode(imageDilate, imageErode, kernel);*/

		imshow("Image", imageCanny);
		waitKey(1);
	}

}