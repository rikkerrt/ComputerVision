#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void getContours(Mat imageRecieved, Mat image) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imageRecieved, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << area << endl;

		vector<vector<Point>> contourPoly(contours.size());
		vector<Rect> boundRect(contours.size());
		string objectType;

		if (area > 500) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);
			drawContours(image, contourPoly, i, Scalar(255, 0, 255));
			cout << contourPoly[i].size() << endl;
			boundRect[i] = boundingRect(contourPoly[i]);
			rectangle(image, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

			int objectCorner = (int)contourPoly[i].size();

			if (objectCorner == 3) {objectType = "Triangle";}
			else if (objectCorner == 4) { objectType = "Rectangle"; }
			else if (objectCorner > 4) { objectType = "Circle"; }

			putText(image, objectType, { boundRect[i].x, boundRect[i].y - 5 }, FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 0, 0));
		}
	}

}

void main() {
	//read the image
	string path = "Images/Images1/basisfiguren.jpg";
	Mat image = imread(path);
	Mat imageGray, imageBlur, imageCanny, imageDilate;

	cvtColor(image, imageGray, COLOR_BGR2GRAY);
	GaussianBlur(imageGray, imageBlur, Size(5, 5), 0);
	Canny(imageBlur, imageCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imageCanny, imageDilate, kernel);


	getContours(imageDilate, image);

	imshow("final image", image);
	waitKey(0);

}