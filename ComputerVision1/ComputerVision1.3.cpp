#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void main() {
	//create the image
	Mat image(750, 750, CV_8UC3, Scalar(255, 255, 255));

	//create a circle
	circle(image, Point(150, 150), 100, Scalar(0, 0, 255), FILLED);

	//create a rectangle
	rectangle(image, Point(500, 50), Point(700, 300), Scalar(255, 0, 0), FILLED);

	line(image, Point(400, 350), Point(700, 650), Scalar(0, 255, 0), 5);
	line(image, Point(400, 650), Point(700, 350), Scalar(0, 255, 0), 5);

	putText(image, "Hello World, Ik sta nu in de image!", Point(100, 700), FONT_HERSHEY_PLAIN, 2, Scalar(0, 0, 0));

	imshow("shapes", image);

	waitKey(0);
}