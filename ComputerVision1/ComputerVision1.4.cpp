#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

float w = 250, h = 350;
Mat matrix, imageWarped;

void main() {
	//read the image
	string path = "Images/Images1/Puzzelboek.jpg";
	Mat image = imread(path);

	//links boven, x=842 y=200
	//recht boven, x= 1939 y= 255
	//links onder, x= 25 y= 1662
	//rechts onder, x= 1871 y= 2055

	//define the points for perspective transformation
	Point2f src[4] = {{842, 200}, {1939, 255}, {25, 1662}, {1871, 2055} };
	Point2f dst[4] = { {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };

	//warping the image
	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(image, imageWarped, matrix, Size(w, h));

	//resize the image becuase the original is very big
	resize(image, image, Size(), 0.25, 0.25);

	imshow("Image", image);
	imshow("ImageWarped", imageWarped);
	waitKey(0);

}