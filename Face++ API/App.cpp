#include"APITools.hpp"
#include<Seetaface\FaceDetection\face_detection.h>
using namespace seeta;
ImageData fmtg(Mat &src) {
	Mat gray;
	cvtColor(src, gray, cv::COLOR_BGR2GRAY);
	seeta::ImageData img_data;
	img_data.data = gray.data;
	img_data.width = gray.cols;
	img_data.height = gray.rows;
	img_data.num_channels = gray.channels();
	return img_data;
}
ImageData fmt(Mat &src) {
	seeta::ImageData img_data;
	img_data.data = src.data;
	img_data.width = src.cols;
	img_data.height = src.rows;
	img_data.num_channels = src.channels();
	return img_data;
}
cv::Rect seetaRect2CvRect(seeta::Rect &rect) {
	return cv::Rect(rect.x, rect.y, rect.width, rect.height);
}
//FaceDetection faceDetector("C:\\opencv\\include\\Seetaface\\seeta_fd_frontal_v1.0.bin");

int main()
{

	Mat src = imread("62.jpg");
	Mat compare_img= imread("63.jpg");
	faceplusplusApi facepp;
	string face_token1 = facepp.faceDetect(src);
	string face_token2 = facepp.faceDetect(compare_img);
	//facepp.facesetRemove();
	facepp.facesetCreate();
	facepp.facesetAdd(face_token1);
	//facepp.facesetAdd(face_token2);

	//facepp.faceSetuserid(face_token2, "1");
	facepp.faceSetuserid(face_token1, "2");

	cout<<facepp.faceSearch(face_token2);

	/*VideoCapture cap(0);
	int index = 0;
	cv::Rect tempRect;
	for (Mat frame=Mat::zeros(640,480,CV_8UC3);waitKey(10)!=27;cap >> frame)
	{
		flip(frame, frame, 1);
		index++;
		if (index >5)
		{
			auto gray = fmtg(frame);
			auto detected = faceDetector.Detect(gray);
			for (int i = 0; i < detected.size(); i++)
			{
				auto facebox = seetaRect2CvRect(detected[i].bbox);
				rectangle(frame, facebox, CV_RGB(128, 128, 255), 5);
				tempRect = facebox;
			}
			index = 0;
		}
		else
		{
			rectangle(frame, tempRect, CV_RGB(128, 128, 255), 5);
		}
		devView(frame);
	}*/
	system("pause");
	return 0;
}