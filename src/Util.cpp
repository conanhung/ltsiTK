
// Qt header files
#include <QDebug>

// basic file operations
#include <iostream>
#include <fstream>

#include "Util.h"

// CHANGES BRIGHTNESS AND/OR CONTRAST
void setContrastBrightness(const Mat& src, Mat& dst, int _contrast, int _brightness)
{
  int brightness = _brightness - 100;
  int contrast = _contrast - 100;
  
  /*
   * The algorithm is by Werner D. Streidt
   * (http://visca.com/ffactory/archives/5-99/msg00021.html)
   */
  double a, b;
  if( contrast > 0 )
  {
    double delta = 127.*contrast/100;
    a = 255./(255. - delta*2);
    b = a*(brightness - delta);
  }
  else
  {
    double delta = -128.*contrast/100;
    a = (256.-delta*2)/255.;
    b = a*brightness + delta;
  }
  
  src.convertTo(dst, CV_8U, a, b);
}

// Convert CV Point to QPoint
QVector<QPoint> PointToQPoint(const vector<Point2f> &src)
{
  QVector<QPoint> dst;
  for(int i=0; i<src.size(); i++)
  {
    dst.push_back(QPoint(src[i].x,src[i].y));
  }
  return dst;
}

// Get the centroid from a set of points
Point2f getCentroidFromSetPoints(vector<Point2f> points)
{
  Point2f centroid = Point2f(0,0);
  int n=0;
  for( size_t j=0; j<points.size(); j++ )
  {
    n++;
    centroid.x += points[j].x;
    centroid.y += points[j].y;
  }
  centroid.x /= n?n:1;
  centroid.y /= n?n:1;
  return centroid;
}

QStringList stdListStringToQStringList(const std::list<std::string> & stringList)
{
  QStringList qStringList;
  for(std::list<std::string>::const_iterator iter = stringList.begin(); iter!=stringList.end(); ++iter)
  {
    qStringList << QString::fromStdString(*iter);
    qDebug() << QString::fromStdString(*iter);
  }
  return qStringList;
}

void shiftPoints(const QVector<QPoint> &inputArrayPoints, const Point2f &inputOffset, QVector<QPoint> &outputArrayPoints)
{
	int n = inputArrayPoints.size();

	if (!n)
		return;

	outputArrayPoints.resize(n);

	for (int i = 0; i < n; i++)
	{
		outputArrayPoints[i] = QPoint(inputArrayPoints[i].x() + inputOffset.x,
			inputArrayPoints[i].y() + inputOffset.y);
	}
}

/*! @brief shift the values in a matrix by an (x,y) offset
 *
 * Given a matrix and an integer (x,y) offset, the matrix will be shifted
 * such that:
 *
 * 	src(a,b) ---> dst(a+y,b+x)
 *
 * In the case of a non-integer offset, (e.g. cv::Point2f(-2.1, 3.7)),
 * the shift will be calculated with subpixel precision using bilinear
 * interpolation.
 *
 * All valid OpenCV datatypes are supported. If the source datatype is
 * fixed-point, and a non-integer offset is supplied, the output will
 * be a floating point matrix to preserve subpixel accuracy.
 *
 * All border types are supported. If no border type is supplied, the
 * function defaults to BORDER_CONSTANT with 0-padding.
 *
 * The function supports in-place operation.
 *
 * Some common examples are provided following:
 * \code
 * 	// read an image from file
 * 	Mat mat = imread(filename);
 * 	Mat dst;
 *
 * 	// Perform Matlab-esque 'circshift' in-place
 * 	shift(mat, mat, Point(5, 5), BORDER_WRAP);
 *
 * 	// Perform shift with subpixel accuracy, padding the missing pixels with 1s
 * 	// NOTE: if mat is of type CV_8U, then it will be converted to type CV_32F
 * 	shift(mat, mat, Point2f(-13.7, 3.28), BORDER_CONSTANT, 1);
 *
 * 	// Perform subpixel shift, preserving the boundary values
 * 	shift(mat, dst, Point2f(0.093, 0.125), BORDER_REPLICATE);
 *
 * 	// Perform a vanilla shift, integer offset, very fast
 * 	shift(mat, dst, Point(2, 2));
 * \endcode
 *
 * @param src the source matrix
 * @param dst the destination matrix, can be the same as source
 * @param delta the amount to shift the matrix in (x,y) coordinates. Can be
 * integer of floating point precision
 * @param fill the method used to fill the null entries, defaults to BORDER_CONSTANT
 * @param value the value of the null entries if the fill type is BORDER_CONSTANT
 */
void shiftImg(const cv::Mat& src, cv::Mat& dst, cv::Point2f delta, int fill, cv::Scalar value) {

	// error checking
	assert(fabs(delta.x) < src.cols && fabs(delta.y) < src.rows);

	// split the shift into integer and subpixel components
	cv::Point2i deltai(ceil(delta.x), ceil(delta.y));
	cv::Point2f deltasub(fabs(delta.x - deltai.x), fabs(delta.y - deltai.y));

	// INTEGER SHIFT
	// first create a border around the parts of the Mat that will be exposed
	int t = 0, b = 0, l = 0, r = 0;
	if (deltai.x > 0) l =  deltai.x;
	if (deltai.x < 0) r = -deltai.x;
	if (deltai.y > 0) t =  deltai.y;
	if (deltai.y < 0) b = -deltai.y;
	cv::Mat padded;
	cv::copyMakeBorder(src, padded, t, b, l, r, fill, value);

	// SUBPIXEL SHIFT
	float eps = std::numeric_limits<float>::epsilon();
	if (deltasub.x > eps || deltasub.y > eps) {
		switch (src.depth()) {
			case CV_32F:
			{
				cv::Matx<float, 1, 2> dx(1-deltasub.x, deltasub.x);
				cv::Matx<float, 2, 1> dy(1-deltasub.y, deltasub.y);
				sepFilter2D(padded, padded, -1, dx, dy, cv::Point(0,0), 0, cv::BORDER_CONSTANT);
				break;
			}
			case CV_64F:
			{
				cv::Matx<double, 1, 2> dx(1-deltasub.x, deltasub.x);
				cv::Matx<double, 2, 1> dy(1-deltasub.y, deltasub.y);
				sepFilter2D(padded, padded, -1, dx, dy, cv::Point(0,0), 0, cv::BORDER_CONSTANT);
				break;
			}
			default:
			{
				cv::Matx<float, 1, 2> dx(1-deltasub.x, deltasub.x);
				cv::Matx<float, 2, 1> dy(1-deltasub.y, deltasub.y);
				padded.convertTo(padded, CV_32F);
				sepFilter2D(padded, padded, CV_32F, dx, dy, cv::Point(0,0), 0, cv::BORDER_CONSTANT);
				break;
			}
		}
	}

	// construct the region of interest around the new matrix
	cv::Rect roi = cv::Rect(std::max(-deltai.x,0),std::max(-deltai.y,0),0,0) + src.size();
	dst = padded(roi);
}

void overlapImg(const cv::Mat& img, const cv::Mat& ov_img, cv::Mat& dst)
{
    for(int y=0;y<img.rows;y++)
		for(int x=0;x<img.cols;x++)
		{
            //int alpha = ov.at<Vec4b>(y,x)[3];
            //int alpha = 256 * (x+y)/(img.rows+img.cols);
			int alpha = 256 * (x+y)/(img.rows+img.cols);
            //dst.at<Vec3b>(y,x)[0] = (1-alpha/256.0) * img.at<Vec3b>(y,x)[0] + (alpha * aortic_root.at<Vec3b>(y,x)[0] / 256);
            //dst.at<Vec3b>(y,x)[1] = (1-alpha/256.0) * img.at<Vec3b>(y,x)[1] + (alpha * aortic_root.at<Vec3b>(y,x)[1] / 256);
            //dst.at<Vec3b>(y,x)[2] = (1-alpha/256.0) * img.at<Vec3b>(y,x)[2] + (alpha * aortic_root.at<Vec3b>(y,x)[2] / 256);
			if(ov_img.at<Vec3b>(y,x)[0])
				dst.at<Vec3b>(y,x)[0] = (1-alpha/256.0) * img.at<Vec3b>(y,x)[0] + (alpha * ov_img.at<Vec3b>(y,x)[0] / 256);
			if(ov_img.at<Vec3b>(y,x)[1])
				dst.at<Vec3b>(y,x)[1] = (1-alpha/256.0) * img.at<Vec3b>(y,x)[1] + (alpha * ov_img.at<Vec3b>(y,x)[1] / 256);
			if(ov_img.at<Vec3b>(y,x)[2])
				dst.at<Vec3b>(y,x)[2] = (1-alpha/256.0) * img.at<Vec3b>(y,x)[2] + (alpha * ov_img.at<Vec3b>(y,x)[2] / 256);
		}
}


vector<Point2f> Read2DPoints(const string& filename)
{
	// Read points
	ifstream pointsstream(filename.c_str());

	if (!pointsstream)
	{
		cout << "Cannot open file " << filename << endl;
		vector<Point2f> p_null;
		return p_null;
	}

	// Read the point from the first image
	string line;
	vector<Point2f> points;

	while (getline(pointsstream, line))
	{
		stringstream ss(line);
		float x, y;
		ss >> x >> y;
		points.push_back(Point2f(x, y));
	}

	return points;
}


vector<Point3f> Read3DPoints(const string& filename)
{
	// Read points
	ifstream pointsstream(filename.c_str());

	if (!pointsstream)
	{
		cout << "Cannot open file " << filename << endl;
		vector<Point3f> p_null;
		return p_null;
	}

	// Read the point from the first image
	string line;
	vector<Point3f> points;

	while (getline(pointsstream, line))
	{
		stringstream ss(line);
		float x, y, z;
		ss >> x >> y >> z;
		points.push_back(Point3f(x, y, z));
	}

	return points;
}
