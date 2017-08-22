#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/objdetect/objdetect.hpp"
using namespace std;

int main(int argc, char** argv){
	cv::VideoCapture cam(0);
	cam.set(CV_CAP_PROP_FPS, 1);
	cv::namedWindow("raw");
	cv::namedWindow("track");

	cv::Scalar colors[] = {
		cv::Scalar(255,0,0),
        cv::Scalar(255,128,0),
        cv::Scalar(255,255,0),
        cv::Scalar(0,255,0),
        cv::Scalar(0,128,255),
        cv::Scalar(0,255,255),
        cv::Scalar(0,0,255),
        cv::Scalar(255,0,255)
	};

	if(!cam.isOpened()){
		cerr << "opencv camera error!" << endl;

	}

	std::string cascadeName = "/home/roger/catkin_ws/src/robotics_projects/face_tracker_pkg/data/face.xml";
	cv::CascadeClassifier cascade;
	if(!cascade.load( cascadeName )){
		cerr << "Load cascade failed"<<endl;
	}

	vector<cv::Rect> faces;
	while(1){
		cv::Size s = cv::Size();
		
		cv::Mat img, gray, histImg;
		cv::Point center;

		if(cam.read(img)){
			cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

			cv::equalizeHist(gray, histImg);

			cascade.detectMultiScale(histImg, faces,1.1, 15, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30,30));

			for(size_t i = 0; i < faces.size(); i++){
				cout << "face " <<endl;
				cv::Scalar color = colors[i%8];
				cv::Rect r = faces[i];
				center.x = cvRound(r.x + r.width * 0.5);
				center.y = cvRound(r.y + r.height * 0.5);
				circle( img, center, cvRound((r.width + r.height)*0.25), color, 3, 8, 0 );

			}
			cv::imshow("raw", img);
			cv::imshow("track", gray);
			cv::waitKey(20);
		}
	}
	
	return 0;
}