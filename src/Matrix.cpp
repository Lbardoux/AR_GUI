/**
 * @file Matrix.cpp
 */
#include <algorithm>
#include <utility>

#include "Matrix.hpp"

Matrix::Matrix(const float& a, const float& b, const float& c, const float& d,
	           const float& e, const float& f, const float& g, const float& h,
	           const float& i, const float& j, const float& k, const float& l,
	           const float& m, const float& n, const float& o, const float& p) noexcept
{
	this->buffer.at(0)  = a;
	this->buffer.at(1)  = b;
	this->buffer.at(2)  = c;
	this->buffer.at(3)  = d;
	this->buffer.at(4)  = e;
	this->buffer.at(5)  = f;
	this->buffer.at(6)  = g;
	this->buffer.at(7)  = h;
	this->buffer.at(8)  = i;
	this->buffer.at(9)  = j;
	this->buffer.at(10) = k;
	this->buffer.at(11) = l;
	this->buffer.at(12) = m;
	this->buffer.at(13) = n;
	this->buffer.at(14) = o;
	this->buffer.at(15) = p;
}

Matrix::~Matrix(void) noexcept
{
	this->buffer.fill(0.0f);
}

Matrix::Matrix(const Matrix& other) noexcept
{
	std::copy(other.buffer.begin(), other.buffer.end(), this->buffer.begin());
}

Matrix::Matrix(Matrix&& other) noexcept
{
	std::swap(this->buffer, other.buffer);
}

Matrix& Matrix::operator=(const Matrix& other) noexcept
{
	
	return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
	
	return *this;
}

Matrix operator*(const Matrix& m1, const Matrix& m2) noexcept
{
	Matrix result;
	
	return result;
}

Matrix& Matrix::operator*=(const Matrix& other) noexcept
{

	return *this;	
}

Matrix rotationX(float angle)
{
	return Matrix();
}

Matrix rotationY(float angle)
{
	return Matrix();
}

Matrix rotationZ(float angle)
{
	return Matrix();
}

Matrix translation(float x, float y, float z)
{
	return Matrix();
}

Matrix scale(float s)
{
	return Matrix();
}
