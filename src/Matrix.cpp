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
				  0.0f, 1.0f, 0.0f, y,
				  0.0f, 0.0f, 1.0f, z,
				  0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix scaleMatrix(float x, float y, float z)
{
	return Matrix(x,    0.0f, 0.0f, 0.0f,
				  0.0f, y,    0.0f, 0.0f,
				  0.0f, 0.0f, z,    0.0f,
				  0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix& Matrix::inverse()
{ 
    int indxc[4], indxr[4];
    int ipiv[4] = { 0, 0, 0, 0 };

    for (int i = 0; i < 4; i++) {
        int irow = -1, icol = -1;
        float big = 0.f;

        // Choose pivot
        for (int j = 0; j < 4; j++) {
            if (ipiv[j] != 1) {
                for (int k = 0; k < 4; k++) {
                    if (ipiv[k] == 0) {
                        if (fabsf(this->at(j, k)) >= big) {
                            big = std::abs(this->at(j, k));
                            irow = j;
                            icol = k;
                        }
                    }
                    else if (ipiv[k] > 1)
                        printf("singular matrix in make_inverse()\n");
                }
            }
        }

        if(!(irow >= 0 && irow < 4) || !(icol >= 0 && icol < 4))
        	throw std::invalid_argument("La matrice est non inversible");

        ++ipiv[icol];
        // Swap rows _irow_ and _icol_ for pivot
        if (irow != icol) {
            for (int k = 0; k < 4; ++k)
                std::swap(this->at(irow, k), this->at(icol, k));
        }

        indxr[i] = irow;
        indxc[i] = icol;
        if (this->at(icol, icol) == 0.)
            printf("singular matrix in make_inverse()\n");

        // Set $m[icol][icol]$ to one by scaling row _icol_ appropriately
        float pivinv = 1.f / this->at(icol, icol);
        this->at(icol, icol) = 1.f;
        for (int j = 0; j < 4; j++)
            this->at(icol, j) *= pivinv;

        // Subtract this row from others to zero out their columns
        for (int j = 0; j < 4; j++) {
            if (j != icol) {
                float save = this->at(j, icol);
                this->at(j, icol) = 0;
                for (int k = 0; k < 4; k++)
                    this->at(j, k) -= this->at(icol, k)*save;
            }
        }
    }

    // Swap columns to reflect permutation
    for (int j = 3; j >= 0; j--) {
        if (indxr[j] != indxc[j]) {
            for (int k = 0; k < 4; k++)
                std::swap(this->at(k, indxr[j]), this->at(k, indxc[j]));
        }
    }

    return *this;
}

Vector cross(Vector & u, Vector & v)
{
	return Vector(
        (u.y() * v.z()) - (u.z() * v.y()),
        (u.z() * v.x()) - (u.x() * v.z()),
        (u.x() * v.y()) - (u.y() * v.x()));
}

Matrix lookAt(const Point& from, const Point& to, const Vector& up)
{
    Vector dir = Vector(from, to).normalize();
    Vector up_normalized = up;
    up_normalized.normalize();
    Vector right = cross(dir, up_normalized).normalize();
    Vector newUp = cross(right, dir).normalize();

    Transform m(
        right.x(), newUp.x(), -dir.x(), from.x(),
        right.y(), newUp.y(), -dir.y(), from.y(),
        right.z(), newUp.z(), -dir.z(), from.z(),
        0,         0,          0,       1);

    return m.inverse();
}

Matrix perspective(const float fov, const float aspect, const float znear, const float zfar)
{
    // perspective, openGL version
    float itan= 1 / tanf((fov * M_PI / 180) * 0.5f);
    float id= 1 / (znear - zfar);

    return Matrix(
        itan/aspect,    0,               0,                 0,
                  0, itan,               0,                 0,
                  0,    0, (zfar+znear)*id, 2.f*zfar*znear*id,
                  0,    0,              -1,                 0);
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
	return this->buffer.data();
}