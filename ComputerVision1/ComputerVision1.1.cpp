#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void main() {
	string path = "Images/Images1/aardappel.jpg";
	Mat image = imread(path);

	imshow("Image", image);
	waitKey(0);

}