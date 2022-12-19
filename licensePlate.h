#ifndef LICENSE_PLATE_H
#define LICENSE_PLATE_H

using namespace cv;
using namespace std;

class LicensePlate {

public:
    void view(string frameName, Mat frame);
    void getContours(Mat imgDil, Mat img);
};

#endif
