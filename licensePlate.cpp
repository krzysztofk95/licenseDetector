#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "licensePlate.h"

using namespace cv;
using namespace std;

void LicensePlate::view(string frameName, Mat frame) {
    imshow(frameName, frame);
}

void LicensePlate::getContours(Mat imageDilate, Mat image) {

// Each vector will be a contour and each contour will have some Points
    vector <vector<Point>> contours;
    vector <Vec4i> hierarchy;

    findContours(imageDilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (int i = 0; i < contours.size(); i++) {

        // Areas of each contour;
        int area = contourArea(contours[i]);

        // New vector of updated values of contours
        vector <vector<Point>> contoursPoly(contours.size());
        vector <Rect> boundRect(contours.size());
        string objectType;

        // Eliminate small contour areas
        if (area > 10000 && area < 20000) {

            // Approximation of corner points
            approxPolyDP(contours[i], contoursPoly[i], 5, true);

            // Finding bounding rectangle around corner points
            boundRect[i] = boundingRect(contoursPoly[i]);

            int objectCorner = (int) contoursPoly[i].size();

            if (objectCorner == 4) {
                objectType = "License Plate";
            }

            // Create rectange of each detected object
            rectangle(image, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

            // Name rectangle
            putText(image, objectType, {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_PLAIN, 2, Scalar(0, 0, 0), 2);
        }
    }
}


