#include "plate_localization.h"

using namespace cv;

void SubPuber::PlateRecognitionCallback(const sensor_msgs::ImageConstPtr &cameraImage)
{
  Mat img = cv_bridge::toCvShare(cameraImage, "bgr8")->image;

  std::vector<Mat> channels;
  split(img, channels);
  Mat grayImage = Mat(img.rows, img.cols, CV_8UC1);
  grayImage = channels.at(0) - 0.8 * channels.at(1) - 0.8 * channels.at(2);

  threshold(grayImage, grayImage, 70, 255, THRESH_BINARY);
  Mat element = getStructuringElement(MORPH_RECT,
                                      Size(15, 15),
                                      Point(-1, -1));

  dilate(grayImage, grayImage, element);
  erode(grayImage, grayImage, element);
  erode(grayImage, grayImage, element);
  dilate(grayImage, grayImage, element);

	Mat cornerImg = Mat::zeros(img.size(), CV_32FC1);
	cornerHarris(grayImage, cornerImg, 2, 3, 0.04, BORDER_DEFAULT);
  Mat normImage, scaledImage;
	normalize(cornerImg, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);

  for (int i = 0; i < normImage.rows; i++)
  {
    for (int j = 0; j < normImage.cols; j++)
    {
      if ((int)normImage.at<float>(i, j) >  100)
      {
        circle(img, Point(j, i), 5, Scalar(10, 10, 255), 2, 8, 0);
      }
    }
  }
  
  sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", img).toImageMsg();
  recognizedImagePub.publish(*msg);
}