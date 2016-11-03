//============================================================================
// Name        : detectCircle.cpp
// Author      : Joyita
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "opencv/highgui.h"
#include <opencv/cv.h>
//#include "ProcessImage.h"
#include <opencv/cxcore.h>

using namespace std;
using namespace cv;

Mat captureImage(){

	Mat imageSrc;
	VideoCapture cap= VideoCapture(0);
	// cap >> imageSrc;
	if(!cap.isOpened()){
		cout<<"Cannot open the camera"<< endl;
	}
	//imshow("camera capture ",imageSrc);

	double dwidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dheight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	cout<<"Frame Size :"<< dwidth<< " & "<<dheight<<endl;
	namedWindow("Camera Ready", CV_WINDOW_FULLSCREEN);
	for(;;){
		Mat frame;
		cap.retrieve(frame);

		bool bSuccess = cap.read(frame);
		if(!bSuccess){
			cout<<"cannot read the stream from frame "<< endl;
			break;
		}
		imshow("Camera Ready", frame);
		imwrite("savedImage/liveImage.jpg", frame);


		if(waitKey(30)== 27){
			cout<<"ESC key pressed"<< endl;
			break;
		}
	}
	Mat image1 = imread("savedImage/liveImage.jpg");


	return image1;
}

int determineBeadSize(int rowNum, Mat img){

	int readPixelValue = 0;
	//int beadCount= 0;
	int minRange = 32; //lightest
	int maxRange = 20; // darkest
	int beadSize = 0;
	/*int pixelValue1 = (int)img.at<uchar>(rowNum,118);
	int pixelValue2 = (int)img.at<uchar>(rowNum,140);
	int pixelValue3 = (int)img.at<uchar>(211,125);
	cout<<"the value of red dot is :"<< pixelValue1<<endl;
	cout<<"the value of red dot is :"<< pixelValue2<<endl;
	cout<<"the value of red dot is :"<< pixelValue3<<endl;*/

	for (int j= 0 ; j<img.cols; j++){
		readPixelValue = (int)img.at<uchar>(rowNum,j);

		if(( readPixelValue >= maxRange)&& ( readPixelValue <= minRange))
		{
			beadSize++;
			if(beadSize < 10){
				j++;
				continue;
			}
			else if ((beadSize > 20)){
				readPixelValue = (int)img.at<uchar>(rowNum,j++);
				if(( readPixelValue >= maxRange)&& ( readPixelValue <= minRange)){
					break;
				}

			}


		}

	}

	cout<<"the bead size is : "<<beadSize<<endl;

	return beadSize;
}

int main(int argc, char** argv)
{


	cout<<"hello World"<<endl;
	Mat src = captureImage();
	Rect roi1(0, 0 , src.cols/2, src.rows); //croppong the image
	Mat3b crop = src(roi1);
	Mat bgr[3];
	split(crop, bgr);
	imwrite("savedImage/blue.jpg", bgr[0]);
	imwrite("savedImage/green.jpg", bgr[1]);
	imwrite("savedImage/red.jpg", bgr[2]);
	Mat grayImg = imread("savedImage/green.jpg");
	cvtColor(grayImg,grayImg, CV_BGR2GRAY);
	imwrite("savedImage/cropped.jpg", grayImg);

	//red dot calliberation
	int pixelvalue = 0;
	int maxRedDot = 60; //lightest
	int minRdeDot = 29;
	int rungDistance = 0;


	for(int i=0 ; i<grayImg.rows; i++)
	{
		for(int j=0 ; j< grayImg.cols; j++)
		{
			pixelvalue = (int)grayImg.at<uchar>(i,j);
			 if (( pixelvalue <= maxRedDot)&&( pixelvalue > minRdeDot))
			 {

				 cout<<"I am inside"<<endl;
				 rungDistance = i;
				 cout<<rungDistance<<endl;
				 break;
				 cout<<"i am still here"<< endl;
			 }

		}
		if(rungDistance!=0){
			break;
		}

		//cout<<"not out yet"<<endl;
	}

	rungDistance = rungDistance+ 35;
	cout<<"the rung distance is :"<< rungDistance<<endl;

	/*int pixelValue1 = (int)grayImg.at<uchar>(155,89);
	int pixelValue2 = (int)grayImg.at<uchar>(154,96);
	int pixelValue3 = (int)grayImg.at<uchar>(154,92);
	cout<<"the value of red dot is :"<< pixelValue1<<endl;
	cout<<"the value of red dot is :"<< pixelValue2<<endl;
	cout<<"the value of red dot is :"<< pixelValue3<<endl;*/

	/*cout<<"-------------------------------------------<<"<<endl;
		Vec3b pix1 = crop.at<Vec3b>(190, 106); //row,column);
		cout<<"The Blue value at this pixel :"<< (int)pix1[0]<<endl;
		cout<<"The Green value at this pixel :"<< (int)pix1[1]<<endl;
		cout<<"The Red value at this pixel :"<< (int)pix1[2]<<endl;
		cout<<"-------------------------------------------<<"<<endl;

		Vec3b pix3 = crop.at<Vec3b>(190, 123); //row,column);
		cout<<"The Blue value at this pixel :"<< (int)pix3[0]<<endl;
		cout<<"The Green value at this pixel :"<< (int)pix3[1]<<endl;
		cout<<"The Red value at this pixel :"<< (int)pix3[2]<<endl;
		cout<<"-------------------------------------------<<"<<endl;


		Vec3b pix2 = crop.at<Vec3b>(190, 129);
		cout<<"The Blue value at this another pixel :"<< (int)pix2[0]<<endl;
		cout<<"The Green value at this another pixel :"<< (int)pix2[1]<<endl;
		cout<<"The Red value at this another pixel :"<< (int)pix2[2]<<endl;
		cout<<"-------------------------------------------<<"<<endl;

		Vec3b pix4 = crop.at<Vec3b>(190, 115);
		cout<<"The Blue value at this another pixel :"<< (int)pix4[0]<<endl;
		cout<<"The Green value at this another pixel :"<< (int)pix4[1]<<endl;
		cout<<"The Red value at this another pixel :"<< (int)pix4[2]<<endl;
		cout<<"-------------------------------------------<<"<<endl;

		Vec3b pix5 = crop.at<Vec3b>(154, 92); //row,column);
				cout<<"The Blue value at this pixel :"<< (int)pix5[0]<<endl;
				cout<<"The Green value at this pixel :"<< (int)pix5[1]<<endl;
				cout<<"The Red value at this pixel :"<< (int)pix5[2]<<endl;
				cout<<"-------------Red Dot------------------------------<<"<<endl;
				Vec3b pix6 = crop.at<Vec3b>(161, 92); //row,column);
						cout<<"The Blue value at this pixel :"<< (int)pix6[0]<<endl;
						cout<<"The Green value at this pixel :"<< (int)pix6[1]<<endl;
						cout<<"The Red value at this pixel :"<< (int)pix6[2]<<endl;
						cout<<"---------------Below Red dot----------------------------<<"<<endl;*/

		int beadSize = determineBeadSize(rungDistance, grayImg);
		//imwrite("savedImage\form.txt",beadSize);
		cout<<"got the beadsize :"<< beadSize<<endl;
	return 0;
}

