
#include <iostream>
#include <string>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
using namespace std;
using namespace cv;

Mat image1;

void cameraCapture(){

	VideoCapture cap(0);
	if(!cap.isOpened()){
		cout<<"Cannot open the camera"<< endl;
	}

	double dwidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dheight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	cout<<"Frame Size :"<< dwidth<< " & "<<dheight<<endl;
	namedWindow("Camera Ready", CV_WINDOW_AUTOSIZE);
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
	image1 = imread("savedImage/liveImage.jpg");

}

void detectBlueBeads(Mat image){
	//GaussianBlur(image, image, Size(9,9),2,2);
	//namedWindow("reduced noise", WINDOW_AUTOSIZE);
	//imshow("reduced noise",image);

	//pixel value (row, column)
		/*int pixelValue1 = (int)image.at<uchar>(184,226);
		int pixelValue2 = (int)image.at<uchar>(182,144);
		int pixelValue3 = (int)image.at<uchar>(191,212);
		int pixelValue4 = (int)image.at<uchar>(182,125);
		cout<< " the pixel value for the blue bead(184,226) :"<< pixelValue1 << endl;
		cout<< " the pixel value for the green bead((182,144) :"<< pixelValue2 << endl;
		cout<< " the pixel value for the green bead(191,212) :"<< pixelValue3 << endl;
		cout<< " the pixel value for the green bead(182,125) :"<< pixelValue4 << endl;*/

	//to detect blue beads

	int maxpixelValofBead = 51; //36;//lightest
	int minpixelValofBead= 23;//24;//darkest
	int sizeofBead = 25;
	//int lengthofBead = 40;
	int detectPixelVal = 0;
	int beadCount = 0;
	//int imageRow = 0;
	//int flagCheck = 0;
	//for (int rungRow =37; rungRow < image.rows ; rungRow++){

	for (int imageColumn = 0 ; imageColumn < image.cols; imageColumn++){

		detectPixelVal = (int)image.at<uchar>(203,imageColumn); //rungRow, imageColumn);//58

		if(( detectPixelVal <= maxpixelValofBead)&&( detectPixelVal >=minpixelValofBead))
		{

			//rungRow = image.rows;
			//cout<< "the row at which it is being detected :"<< rungRow <<endl;
			//cout<<"Column on image we are on the bead :"<<imageColumn<<endl;
			imageColumn = imageColumn+ sizeofBead;

			if(imageColumn < image.cols)
			{ //check for beads not fully in the image

				//cout<<" Bead detected"<< endl;
				beadCount++;
			}
			//cout<<"Column on image we are on after detecting bead :"<<imageColumn<<endl;
			//imageRow = rungRow;
		}
		if (beadCount==5){
			break;
		}

	}
	//if(flagCheck ==1){
	//	break;
	//}
	//cout<<"the Image row :"<< rungRow<<endl;
	//break;

	//rungRow = rungRow +lengthofBead;

	//}
	//beadCount--;
	cout<<"Number of Blue beads detected :"<< beadCount<< endl;

}

void detectYellowBeads( Mat blueSrc){

	Mat srcImg1;
	cvtColor(blueSrc , srcImg1, CV_BGR2GRAY);
	imshow("Blue-Grey Image", srcImg1);

	//pixel value (row, column)
	/*int pixelValue1 = (int)srcImg1.at<uchar>(275,210);
	int pixelValue2 = (int)srcImg1.at<uchar>(275,282);
	int pixelValue3 = (int)srcImg1.at<uchar>(275,217);
	int pixelValue4 = (int)srcImg1.at<uchar>(275,305);
	cout<< " the pixel value for the yellow bead(275,210) :"<< pixelValue1 << endl;
	cout<< " the pixel value for the green bead(275,282) :"<< pixelValue2 << endl;
	cout<< " the pixel value for the green bead(275,217) :"<< pixelValue3 << endl;
	cout<< " the pixel value for the green bead(275,305) :"<< pixelValue4 << endl;*/


	int maxpixelValofBead = 51;//65;//51;//120;//87;//51;//33;//lightest
	int minpixelValofBead= 12;//40;//12;//darkest
	int sizeofBead = 21;//25;
	//int lengthofBead = 40;
	int detectPixelVal = 0;
	int yellowbeadCount = 0;

	for (int imageColumn = 0 ; imageColumn < srcImg1.cols; imageColumn++){

		detectPixelVal = (int)srcImg1.at<uchar>(273,imageColumn); //rungRow, imageColumn);//58

		if(yellowbeadCount == 0){

			if(imageColumn > 233){

				maxpixelValofBead = 80; // case- have one bead in last farthest segment
			}
			if((detectPixelVal <= maxpixelValofBead) && (detectPixelVal >= 30)){//to differentiate between wood and the bead  ----30
				yellowbeadCount++;
				//cout<< "the column we are on for the 1st bead "<<imageColumn<<endl;
				imageColumn = imageColumn+ sizeofBead + 13; // the first bead looks big in the camera
				//cout<<" bead count here "<< yellowbeadCount<<endl;
				//cout<<"we are inside this"<<endl;
			}
		}
		else if(yellowbeadCount >0){

			if(imageColumn > 233){
				maxpixelValofBead = 75; // case- have one bead in last farthest segment
			}

			if(( detectPixelVal <= maxpixelValofBead)&&( detectPixelVal >= minpixelValofBead))
			{

				//rungRow = image.rows;
				//cout<< "the row at which it is being detected :"<< rungRow <<endl;
				//cout<< "the column at which it is being detected :"<< imageColumn <<endl;
				imageColumn = imageColumn+ sizeofBead;
				detectPixelVal = (int)srcImg1.at<uchar>(273,imageColumn);

				/*if(( detectPixelVal > maxpixelValofBead) && (detectPixelVal)){ //needed only when there is extra backlight
				yellowbeadCount--;
			}*/


				//if(imageColumn < srcImg1.cols)
				//{ //check for beads not fully in the image

					//cout<<" Bead detected"<< endl;
					yellowbeadCount++;
					//cout<<" bead count over here : "<< yellowbeadCount<<endl;
				//}
				//cout<<"Column on image we are on after detecting bead :"<<imageColumn<<endl;
				//imageRow = rungRow;
			}

			if (yellowbeadCount>3){
				maxpixelValofBead = 81;
			}
		}
		if (yellowbeadCount == 5){
			break;
		}

	}
	cout<<"Number of Yellow beads detected :"<< yellowbeadCount<< endl;


}

void detectOrangeBeads(Mat greenSrc){
	Mat srcImg2;
	cvtColor(greenSrc , srcImg2, CV_BGR2GRAY);
	imshow("Blue-Grey Image", srcImg2);

	//pixel value (row, column)
	/*int pixelValue1 = (int)srcImg2.at<uchar>(294,237);
	int pixelValue2 = (int)srcImg2.at<uchar>(294,256);
	int pixelValue3 = (int)srcImg2.at<uchar>(294,276);
	int pixelValue4 = (int)srcImg2.at<uchar>(300,295);
	cout<< " the pixel value for the yellow bead(294,237) :"<< pixelValue1 << endl;
	cout<< " the pixel value for the green bead(294,256) :"<< pixelValue2 << endl;
	cout<< " the pixel value for the green bead(294,276) :"<< pixelValue3 << endl;
	cout<< " the pixel value for the green bead(300,295) :"<< pixelValue4 << endl;*/

	int maxpixelValofBead = 55;//101;//34;//lightest
	int minpixelValofBead= 14;//36;//15;//darkest
	int sizeofBead = 26;//36
	//int lengthofBead = 40;
	int detectPixelVal = 0;
	int orangeBeadCount = 0;

	for (int imageColumn = 0 ; imageColumn < srcImg2.cols; imageColumn++){

		//cout<<"printing the imageColumn "<<imageColumn<<endl;
		detectPixelVal = (int)srcImg2.at<uchar>(294,imageColumn); //rungRow, imageColumn);//58

		if(orangeBeadCount == 0){

			if(imageColumn > 233){
				//cout<<"we are getting here"<<endl;
				maxpixelValofBead = 66; // case- have one bead in last farthest segment
			}
			if( (detectPixelVal <= maxpixelValofBead) && (detectPixelVal >= minpixelValofBead)){ //to differentiate between wood and the bead
				orangeBeadCount++;
				//cout<<" bead count here "<< orangeBeadCount<< " on column "<<imageColumn<<endl;
				imageColumn = imageColumn + sizeofBead +4; // the first bead looks big in the camera

			}

		}
		else if(orangeBeadCount >0){

			detectPixelVal = (int)srcImg2.at<uchar>(294,imageColumn);
			if(imageColumn > 233){
				maxpixelValofBead = 66; // case- have one bead in last farthest segment
			}


			if(( detectPixelVal <= maxpixelValofBead)&&( detectPixelVal >=minpixelValofBead))
			{

				//rungRow = image.rows;
				//cout<< "the row at which it is being detected :"<< rungRow <<endl;
				//cout<<"Column on image we are on the bead :"<<imageColumn<<endl;
				imageColumn = imageColumn+ sizeofBead;

				//if(imageColumn < srcImg2.cols)
				//{ //check for beads not fully in the image

				//cout<<" Bead detected"<< endl;
				orangeBeadCount++;
				//}
				//cout<<"Column on image we are on after detecting bead :"<<imageColumn<<endl;
				//imageRow = rungRow;
			}
		}
		if (orangeBeadCount==5){
			break;
		}

	}
	cout<<"Number of Orange beads detected :"<< orangeBeadCount<< endl;


}

void detectRedBeads(Mat greenSrc){

	Mat srcImg3;
	cvtColor(greenSrc , srcImg3, CV_BGR2GRAY);
	imshow("Blue-Grey Image", srcImg3);

	/*int pixelValue1 = (int)srcImg3.at<uchar>(336,48);
	int pixelValue2 = (int)srcImg3.at<uchar>(336, 74);
	int pixelValue3 = (int)srcImg3.at<uchar>(348,91);
	//int pixelValue4 = (int)srcImg3.at<uchar>(256,210);
	cout<< " the pixel value for the yellow bead(336,48) :"<< pixelValue1 << endl;
	cout<< " the pixel value for the green bead(336, 74) :"<< pixelValue2 << endl;
	cout<< " the pixel value for the green bead(348,91) :"<< pixelValue3 << endl;
	//cout<< " the pixel value for the green bead(256,210) :"<< pixelValue4 << endl;*/
	int maxpixelValofBead = 26;//21;//lightest
	int minpixelValofBead= 2;//darkest
	int sizeofBead = 28;//36;
	//int lengthofBead = 40;
	int detectPixelVal = 0;
	int redbeadCount = 0;

	for (int imageColumn = 0 ; imageColumn < srcImg3.cols; imageColumn++){

		detectPixelVal = (int)srcImg3.at<uchar>(336,imageColumn); //rungRow, imageColumn);//58

		if(( detectPixelVal <= maxpixelValofBead)&&( detectPixelVal >=minpixelValofBead))
		{

			//rungRow = image.rows;
			//cout<< "the row at which it is being detected :"<< rungRow <<endl;
			//cout<<"Column on image we are on the bead :"<<imageColumn<<endl;
			imageColumn = imageColumn+ sizeofBead;

			if(imageColumn < srcImg3.cols)
			{ //check for beads not fully in the image

				//cout<<" Bead detected"<< endl;
				redbeadCount++;
			}
			//cout<<"Column on image we are on after detecting bead :"<<imageColumn<<endl;
			//imageRow = rungRow;
		}
		if (redbeadCount==5){
			break;
		}

	}
	cout<<"Number of Red beads detected :"<< redbeadCount<< endl;



}

void convert2Grey(Mat src){

	Mat grey;
	image1 = grey;
	cvtColor(src , grey, CV_BGR2GRAY);
	namedWindow("greyImage", WINDOW_AUTOSIZE);
	imshow("greyImage", grey);
	cout<< "the total length and breadth of the image is :"<< grey.cols << " and "<< grey.rows<< endl;
	imwrite("savedImage/croppedSample.jpg", grey);
	detectBlueBeads(grey);
	//detect

	//return grey;
}

int main(int argc, char** argv){

	cout<<"Hello world"<<endl;
	cameraCapture(); //live image capture
	Mat3b img = image1; //imread("image/testcase.jpg");
	cout<< "the total length and breadth of the image is :"<< img.cols << " and "<< img.rows<<endl;
    if( img.empty() )
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

	Rect roi1(0, 0 , img.cols/2, img.rows); //croppong the image
	Mat3b crop = img(roi1);
   // namedWindow("original", WINDOW_AUTOSIZE);
	//imshow("original", img);
	namedWindow("Cropped Image", WINDOW_AUTOSIZE);
	imshow("Cropped Image", crop);
	imwrite("savedImage/cropColor.jpg", crop);


	// converting to hsv image
	/*Mat imagehsv;
	cvtColor(crop, imagehsv, CV_BGR2HSV);
	imwrite("savedImage/hsvImage.jpg", imagehsv);
	imshow("hsv image", imagehsv);*/

	/*Vec3b pix = crop.at<Vec3b>(190, 106); //row,column);
	cout<<"The Blue value at this pixel :"<< (int)pix[0]<<endl;
	Vec3b pix1 = crop.at<Vec3b>(196, 120);
	cout<<"The Blue value at this another pixel :"<< (int)pix1[0]<<endl;*/

	//other color channels--//Split the image into several single channel
	Mat bgr[3];
	split(crop, bgr);
	imwrite("savedImage/blue.jpg", bgr[0]);
	imwrite("savedImage/green.jpg", bgr[1]);
	imwrite("savedImage/red.jpg", bgr[2]);
	Mat blueImage= imread("savedImage/blue.jpg");
	//imshow("Blue Image", blueImage);
	Mat greenImage= imread("savedImage/green.jpg");

	convert2Grey(crop);
	detectYellowBeads(blueImage);
	detectOrangeBeads(greenImage);
	detectRedBeads(greenImage);

	 waitKey(0);

	 return 0;

}
