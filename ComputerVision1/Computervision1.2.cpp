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
	Mat imageResized;
	Mat imageCropped;

	//check size of image
	cout << image.size() << endl;

	//resize the image
	resize(image, imageResized, Size(), 3, 3);

	//Define the ROI (Region Of Interest)
	Rect roi(75, 200, 300, 300);
	imageCropped = imageResized(roi);
	

	imshow("Image", image);
	imshow("ImageResized", imageResized);
	imshow("ImageCropped", imageCropped);
	waitKey(0);

}