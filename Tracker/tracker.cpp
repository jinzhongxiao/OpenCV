#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/tracking/tracking.hpp"
using namespace std;
using namespace cv;
int main(int argc, char** argv){
	// Set up tracker
	// Instead of MIL, you can use BOOSTING, KCF, TLD, MEDIANFLOW, GOTURN
	// those 5 usage can see http://www.learnopencv.com/object-tracking-using-opencv-cpp-python/
	Ptr<Tracker> tracker = Tracker::create( "GOTURN" );

	VideoCapture video(0);
	if(!video.isOpened())
	{
        cout << "Could not open" << endl;
        return 1;
    }
	// Read first frame. 
    Mat frame;
    video.read(frame);
 
    // Define an initial bounding box
    Rect2d bbox(287, 23, 86, 320);
 
    // Uncomment the line below if you 
    // want to choose the bounding box
    bbox = selectROI(frame, false);
     
    // Initialize tracker with first frame and bounding box
    tracker->init(frame, bbox);
 
    while(video.read(frame))
    {
        // Update tracking results
        tracker->update(frame, bbox);
 
        // Draw bounding box
        rectangle(frame, bbox, Scalar( 255, 0, 0 ), 2, 1 );
 
        // Display result
        imshow("Tracking", frame);
        int k = waitKey(1);
        if(k == 27) break;
 
    }
	return 0;
}

