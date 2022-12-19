#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "licensePlate.h"

using namespace cv;
using namespace std;

void licensePlateDetect();

int main() {

licensePlateDetect();

    return 0;
}

void licensePlateDetect() {

// Instantiate Mat objects
LicensePlate lp;

// Detect camera
 VideoCapture cap(0);
 Mat image;

 while(true) {

 // Read the camera image
 cap.read(image);

 // checking if image is correct
 if(!image.data ) {
    cout <<  "Image not found or unable to open" << endl ;
    system(0);
  }

// Instantiate Mat objects
 Mat imageGray, imageBlur, imageCanny, imageDilate;
 Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

 // Preprocessing of images
 cvtColor(image, imageGray, COLOR_BGR2GRAY);
 GaussianBlur(imageGray, imageBlur, Size(3, 3), 3, 0);
 Canny(imageBlur, imageCanny, 25, 75);
 dilate(imageCanny, imageDilate, kernel);

 // Finding contours and placemant on image
 lp.getContours(imageDilate, image);

 // Show shape of license plate on image
 lp.view("Image", image);

 waitKey(1);
    }
}



