/**
 * @file Matrix.cpp
 */
#include <algorithm>
#include <utility>
#include <functional>
#include <iterator>
#include <cmath>

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

float& Matrix::at(int x, int y) noexcept
{
	return this->buffer.at(y*4 + x);
}

const float& Matrix::at(int x, int y) const noexcept
{
	return this->buffer.at(y*4 + x);
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
	std::copy(other.buffer.begin(), other.buffer.end(), this->buffer.begin());
	return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
	std::swap(this->buffer, other.buffer);
	return *this;
}

Matrix operator*(const Matrix& m1, const Matrix& m2) noexcept
{
	Matrix result;
	for(int ym1=0;ym1<4;++ym1)
	{
		for(int xm2=0;xm2<4;++xm2)
		{
			for(int ym2=0;ym2<4;++ym2)
			{
				result.at(xm2, ym1) += m1.at(ym2, ym1) * m2.at(xm2, ym2);
			}
		}
	}
	return result;
}

Matrix& Matrix::operator*=(float v) noexcept
{
	*this = (*this)*v;
	return *this;
}

Matrix& Matrix::operator/=(float v) noexcept
{
	*this = (*this)/v;
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) noexcept
{
	*this = (*this) * other;
	return *this;
}

Matrix identityMatrix(void)
{
	return Matrix(1.0f, 0.0f, 0.0f, 0.0f,
				  0.0f, 1.0f, 0.0f, 0.0f,
				  0.0f, 0.0f, 1.0f, 0.0f,
				  0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix translationMatrix(const Vector& v)
{
	return translationMatrix(v.x(), v.y(), v.z());
}

Matrix rotationXMatrix(float angle)
{
	return Matrix(1.0f, 0.0f,            0.0f,             0.0f,
				  0.0f, std::cos(angle), -std::sin(angle), 0.0f,
				  0.0f, std::sin(angle), std::cos(angle),  0.0f,
				  0.0f, 0.0f,            0.0f,             1.0f);
}

Matrix rotationYMatrix(float angle)
{
	return Matrix(std::cos(angle),  0.0f, std::sin(angle), 0.0f,
				  0.0f,             1.0f, 0.0f,            0.0f,
				  -std::sin(angle), 0.0f, std::cos(angle), 0.0f,
				  0.0f,             0.0f, 0.0f,            1.0f);
}

Matrix rotationZMatrix(float angle)
{
	return Matrix(std::cos(angle), -std::sin(angle), 0.0f, 0.0f,
				  std::sin(angle), std::cos(angle),  0.0f, 0.0f,
				  0.0f,            0.0f,             1.0f, 0.0f,
				  0.0f,            0.0f,             0.0f, 1.0f);
}

Matrix translationMatrix(float x, float y, float z)
{
	return Matrix(1.0f, 0.0f, 0.0f, x,
				  0.0f, 0.0f, 0.0f, y,
				  0.0f, 0.0f, 0.0f, z,
				  0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix scaleMatrix(float x, float y, float z)
{
	return Matrix(x,    0.0f, 0.0f, 0.0f,
				  0.0f, y,    0.0f, 0.0f,
				  0.0f, 0.0f, z,    0.0f,
				  0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix operator*(const Matrix& m, float v) noexcept
{
    Matrix result;
    std::transform(m.buffer.begin(), m.buffer.end(), result.buffer.begin(), [&v](float value){return value*v;});
    return result;
}

Matrix operator*(float v, const Matrix& m) noexcept
{
    return m*v;
}

Matrix operator/(const Matrix& m, float v) noexcept
{
    Matrix result;
    std::transform(m.buffer.begin(), m.buffer.end(), result.buffer.begin(), [&v](float value){return value*v;});
    return result;
}

std::ostream& operator<<(std::ostream& out, const Matrix& m)
{
    for(int i=0;i<4;++i)
    {
        out << "[ ";
        for(int j=0;j<4;++j)
        {
            out << m.at(j, i) << ' ';
        }
        out << ']' << std::endl;
    }
    return out;
}

const float* Matrix::getBuffer() const noexcept
{
	return &(this->buffer[0]);
}