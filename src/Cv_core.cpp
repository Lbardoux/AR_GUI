#include "Cv_core.hpp"


const mat_data_t matAt(const cv::Mat& mat, int x, int y)
{
	return mat.at<mat_data_t>(y, x);
}

mat_data_t& matAt(cv::Mat& mat, int x, int y)
{
	return mat.at<mat_data_t>(y, x);
}

mat_data_t matRedColor(void)
{
	return mat_data_t(0,0,255);
}

mat_data_t matBlueColor(void)
{
	return mat_data_t(255,0,0);
}

mat_data_t matGreenColor(void)
{
	return mat_data_t(0,255,0);
}