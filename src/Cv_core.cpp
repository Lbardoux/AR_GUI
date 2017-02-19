#include "Cv_core.hpp"


const mat_data_t matAt(const cv::Mat& mat, int x, int y)
{
    return mat.at<mat_data_t>(y, x);
}

mat_data_t& matAt(cv::Mat& mat, int x, int y)
{
    return mat.at<mat_data_t>(y, x);
}

void fillMat(cv::Mat& mat, const mat_data_t& color)
{
	for(int i = 0; i < mat.cols; ++i)
		for(int j = 0; j < mat.rows; ++j)
			matAt(mat, i, j) = color;
}

mat_data_t matRedColor(void)
{
    return mat_data_t(0, 0, 255, 1);
}

mat_data_t matBlueColor(void)
{
    return mat_data_t(255, 0, 0, 1);
}

mat_data_t matGreenColor(void)
{
    return mat_data_t(0, 255, 0, 1);
}

mat_data_t matBlackColor(void)
{
	return mat_data_t(0, 0, 0, 1);
}

mat_data_t matEmptyColor(void)
{
	return mat_data_t(0, 0, 0, 0);
}