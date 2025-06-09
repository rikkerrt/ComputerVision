#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace cv;

void extractCharacters(const Mat& imagePlate, int plateNumber) {
    //preproces the picture
    Mat imageGray, imageThreshold;
    cvtColor(imagePlate, imageGray, COLOR_BGR2GRAY);

    //hiermee wordt het omgezet naar een definitief zwart-wit, de thersh_otsu zorgt ervoor dat automatisch de beste (volgens de computer) drempelwaarde gelegd wordt.
    threshold(imageGray, imageThreshold, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    
    //make the contours
    vector<vector<Point>> contours;
    findContours(imageThreshold.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    //loops door alle contours heen
    for (int i = 0; i < contours.size(); i++) {
        drawContours(imagePlate, contours, i, Scalar(255, 0, 255), 3);
    }
    imshow("contours", imagePlate);

    //make boundingbox for all contours
    vector<Rect> charRects;
    for (const auto& contour : contours) {
        Rect rect = boundingRect(contour);
        //filtert op grootte zodat zo min mogelijk ruis gedetecteerd wordt
        if (rect.height > 20 && rect.width > 10 && rect.height < 100 && rect.width < 100) {
        charRects.push_back(rect);
        }
    }
    //sorteert de contours zodat ze in de goeie volghorde opgeslagen worden
    sort(charRects.begin(), charRects.end(), [](const Rect& a, const Rect& b) {
        return a.x < b.x;
    });

    //slaat alle symbolen op op basis van index (symbool x op nummberbord) en plateNumber (hoeveelste nummerbord)
    int index = 1;
    for (const auto& rect : charRects) {
        Mat charImg = imageThreshold(rect);
        imwrite("resources/plates/Nummerbord" + to_string(plateNumber) + "_" + to_string(index) + ".png", charImg);

        Mat imgResize;
        resize(charImg, imgResize, Size(), 4, 4);
		imshow("Character " + to_string(index), imgResize);
        index++;
    }
    cout << "alles is opgeslagen" << endl;
}

int main() {
    CascadeClassifier plateCascade;
    plateCascade.load("resources/haarcascade_russian_plate_number.xml");
    if (plateCascade.empty()) {
        cout << "Kon plate_classifier.xml niet laden." << endl;
        return 0;
    }

    Mat image = imread("images/images1/frenchPlate.jpg");
	imshow("Original Image", image);

    vector<Rect> plates;

    //search for plates with xml data
    plateCascade.detectMultiScale(image, plates, 1.1, 5);

    //if no plates have been found, end the program
    if (plates.empty()) {
        cout << "Geen nummerplaat gevonden." << endl;
		waitKey(0);
        return 0;
    }

    int plateCount = 1;

    //go through all plates in picture
    for (const auto& rect : plates) {
        Mat plateROI = image(rect);
        extractCharacters(plateROI, plateCount);
        plateCount++;
    }

    waitKey(0);
    return 0;
}
