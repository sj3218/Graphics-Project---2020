/*
1. Park Sejeong
2. Project 2
3. CS250
4. Spring 2020
*/
#include "Affine.h"

Hcoord::Hcoord(float X, float Y, float Z, float W) :x(X), y(Y), z(Z), w(W)
{
}

Point::Point(float X, float Y, float Z)
{
    x = X;
    y = Y;
    z = Z;
    w = 1.0f;
}

Vector::Vector(float X, float Y, float Z)
{
    x = X;
    y = Y;
    z = Z;
}

Affine::Affine(void)
{
    this->row[3].w = 1.0f;
}

Affine::Affine(const Vector& Lx, const Vector& Ly, const Vector& Lz, const Point& D)
{
    this->row[0].x = Lx.x;
    this->row[0].y = Ly.x;
    this->row[0].z = Lz.x;
    this->row[0].w = D.x;

    this->row[1].x = Lx.y;
    this->row[1].y = Ly.y;
    this->row[1].z = Lz.y;
    this->row[1].w = D.y;

    this->row[2].x = Lx.z;
    this->row[2].y = Ly.z;
    this->row[2].z = Lz.z;
    this->row[2].w = D.z;

    this->row[3].w = 1.0f;
}

Hcoord operator+(const Hcoord& u, const Hcoord& v)
{
    return Hcoord(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}

Hcoord operator-(const Hcoord& u, const Hcoord& v)
{
    return Hcoord(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}

Hcoord operator-(const Hcoord& v)
{
    return Hcoord(-v.x, -v.y, -v.z, -v.w);
}

Hcoord operator*(float r, const Hcoord& v)
{
    return Hcoord(r * v.x, r * v.y, r * v.z, r * v.w);
}

Hcoord operator*(const Matrix& A, const Hcoord& v)
{
    float x = A[0].x * v.x + A[0].y * v.y + A[0].z * v.z + A[0].w * v.w;
    float y = A[1].x * v.x + A[1].y * v.y + A[1].z * v.z + A[1].w * v.w;
    float z = A[2].x * v.x + A[2].y * v.y + A[2].z * v.z + A[2].w * v.w;
    float w = A[3].x * v.x + A[3].y * v.y + A[3].z * v.z + A[3].w * v.w;

    return Hcoord(x, y, z, w);
}

Matrix operator*(const Matrix& A, const Matrix& B)
{
    Matrix matrix;
    matrix[0].x = A[0].x * B[0].x + A[0].y * B[1].x + A[0].z * B[2].x + A[0].w * B[3].x;
    matrix[0].y = A[0].x * B[0].y + A[0].y * B[1].y + A[0].z * B[2].y + A[0].w * B[3].y;
    matrix[0].z = A[0].x * B[0].z + A[0].y * B[1].z + A[0].z * B[2].z + A[0].w * B[3].z;
    matrix[0].w = A[0].x * B[0].w + A[0].y * B[1].w + A[0].z * B[2].w + A[0].w * B[3].w;

    matrix[1].x = A[1].x * B[0].x + A[1].y * B[1].x + A[1].z * B[2].x + A[1].w * B[3].x;
    matrix[1].y = A[1].x * B[0].y + A[1].y * B[1].y + A[1].z * B[2].y + A[1].w * B[3].y;
    matrix[1].z = A[1].x * B[0].z + A[1].y * B[1].z + A[1].z * B[2].z + A[1].w * B[3].z;
    matrix[1].w = A[1].x * B[0].w + A[1].y * B[1].w + A[1].z * B[2].w + A[1].w * B[3].w;

    matrix[2].x = A[2].x * B[0].x + A[2].y * B[1].x + A[2].z * B[2].x + A[2].w * B[3].x;
    matrix[2].y = A[2].x * B[0].y + A[2].y * B[1].y + A[2].z * B[2].y + A[2].w * B[3].y;
    matrix[2].z = A[2].x * B[0].z + A[2].y * B[1].z + A[2].z * B[2].z + A[2].w * B[3].z;
    matrix[2].w = A[2].x * B[0].w + A[2].y * B[1].w + A[2].z * B[2].w + A[2].w * B[3].w;

    matrix[3].x = A[3].x * B[0].x + A[3].y * B[1].x + A[3].z * B[2].x + A[3].w * B[3].x;
    matrix[3].y = A[3].x * B[0].y + A[3].y * B[1].y + A[3].z * B[2].y + A[3].w * B[3].y;
    matrix[3].z = A[3].x * B[0].z + A[3].y * B[1].z + A[3].z * B[2].z + A[3].w * B[3].z;
    matrix[3].w = A[3].x * B[0].w + A[3].y * B[1].w + A[3].z * B[2].w + A[3].w * B[3].w;

    return matrix;
}

Affine operator*(const Affine& A, const Affine& B)
{
    Affine result;
    for (int i = 0; i < 4; i++)
    {
        result.row[i].x = (A.row[i].x * B.row[0].x) + (A.row[i].y * B.row[1].x) + (A.row[i].z * B.row[2].x) + (A.row[i].w * B.row[3].x);
        result.row[i].y = (A.row[i].x * B.row[0].y) + (A.row[i].y * B.row[1].y) + (A.row[i].z * B.row[2].y) + (A.row[i].w * B.row[3].y);
        result.row[i].z = (A.row[i].x * B.row[0].z) + (A.row[i].y * B.row[1].z) + (A.row[i].z * B.row[2].z) + (A.row[i].w * B.row[3].z);
        result.row[i].w = (A.row[i].x * B.row[0].w) + (A.row[i].y * B.row[1].w) + (A.row[i].z * B.row[2].w) + (A.row[i].w * B.row[3].w);
    }
    return result;
}

float dot(const Vector& u, const Vector& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

float abs(const Vector& v)
{
    return std::sqrt(dot(v, v));
}

Vector normalize(const Vector& v)
{
    return (1.f / abs(v)) * v;
}

Vector cross(const Vector& u, const Vector& v)
{
    return Vector(u.y * v.z - u.z * v.y, -(u.x * v.z - u.z * v.x), u.x * v.y - u.y * v.x);
}

Affine rotate(float t, const Vector& v)
{
    float cosT = std::cos(t);
    float sinT = std::sin(t);
    float lengthV = abs(v);

    float value1 = (1.f - cosT) / std::pow(lengthV, 2.f);
    float value2 = sinT / lengthV;

    Matrix cosTIdentityMatrix;
    cosTIdentityMatrix[0].x = cosT;
    cosTIdentityMatrix[1].y = cosT;
    cosTIdentityMatrix[2].z = cosT;

    Matrix outerMatrix;
    outerMatrix[0] = value1 * Hcoord(v.x * v.x, v.x * v.y, v.x * v.z);
    outerMatrix[1] = value1 * Hcoord(v.y * v.x, v.y * v.y, v.y * v.z);
    outerMatrix[2] = value1 * Hcoord(v.z * v.x, v.z * v.y, v.z * v.z);

    Matrix crossProductMatrix;
    crossProductMatrix[0] = value2 * Hcoord(0.f, -v.z, v.y);
    crossProductMatrix[1] = value2 * Hcoord(v.z, 0.f, -v.x);
    crossProductMatrix[2] = value2 * Hcoord(-v.y, v.x, 0.f);

    Matrix result;
    result[0] = cosTIdentityMatrix[0] + outerMatrix[0] + crossProductMatrix[0];
    result[1] = cosTIdentityMatrix[1] + outerMatrix[1] + crossProductMatrix[1];
    result[2] = cosTIdentityMatrix[2] + outerMatrix[2] + crossProductMatrix[2];
    result[3].w = 1.0f;

    return Affine(result);
}

Affine translate(const Vector& v)
{
    Vector firstColumn(1.f, 0.f, 0.f);
    Vector secondColumn(0.f, 1.f, 0.f);
    Vector thirdColumn(0.f, 0.f, 1.f);
    Point forthColumn(v.x, v.y, v.z);

    return Affine(firstColumn, secondColumn, thirdColumn, forthColumn);
}

Affine scale(float r)
{
    Vector firstColumn(r, 0.f, 0.f);
    Vector secondColumn(0.f, r, 0.f);
    Vector thirdColumn(0.f, 0.f, r);
    Point forthColumn(0.f, 0.f, 0.f);

    return Affine(firstColumn, secondColumn, thirdColumn, forthColumn);
}

Affine scale(float rx, float ry, float rz)
{
    Vector firstColumn(rx, 0.f, 0.f);
    Vector secondColumn(0.f, ry, 0.f);
    Vector thirdColumn(0.f, 0.f, rz);
    Point forthColumn(0.f, 0.f, 0.f);

    return Affine(firstColumn, secondColumn, thirdColumn, forthColumn);
}

Affine inverse(const Affine& A)
{
    Matrix cofactorMatrix;
    cofactorMatrix[0].x = A[1].y * A[2].z - A[1].z * A[2].y;
    cofactorMatrix[0].y = -(A[1].x * A[2].z - A[1].z * A[2].x);
    cofactorMatrix[0].z = A[1].x * A[2].y - A[1].y * A[2].x;

    cofactorMatrix[1].x = -(A[0].y * A[2].z - A[0].z * A[2].y);
    cofactorMatrix[1].y = A[0].x * A[2].z - A[0].z * A[2].x;
    cofactorMatrix[1].z = -(A[0].x * A[2].y - A[0].y * A[2].x);

    cofactorMatrix[2].x = A[0].y * A[1].z - A[0].z * A[1].y;
    cofactorMatrix[2].y = -(A[0].x * A[1].z - A[0].z * A[1].x);
    cofactorMatrix[2].z = A[0].x * A[1].y - A[0].y * A[1].x;

    float determinantMatrixA = 1.f/(dot(Vector(A[0].x, A[0].y, A[0].z), Vector(cofactorMatrix[0].x, cofactorMatrix[0].y, cofactorMatrix[0].z)));

    Matrix inverseMatrix;
    inverseMatrix[0] = determinantMatrixA * Hcoord(cofactorMatrix[0].x, cofactorMatrix[1].x, cofactorMatrix[2].x);
    inverseMatrix[1] = determinantMatrixA * Hcoord(cofactorMatrix[0].y, cofactorMatrix[1].y, cofactorMatrix[2].y);
    inverseMatrix[2] = determinantMatrixA * Hcoord(cofactorMatrix[0].z, cofactorMatrix[1].z, cofactorMatrix[2].z);

    Hcoord point(-A[0].w, -A[1].w, -A[2].w);

    inverseMatrix[0].w = dot(inverseMatrix[0], point);
    inverseMatrix[1].w = dot(inverseMatrix[1], point);
    inverseMatrix[2].w = dot(inverseMatrix[2], point);
    inverseMatrix[3].w = 1.0f;

    return Affine(inverseMatrix);
}

Affine transpose(const Affine& A)
{
    Affine New;

    New.row[0].x = A.row[0].x;
    New.row[1].x = A.row[0].y;
    New.row[2].x = A.row[0].z;
    New.row[3].x = A.row[0].w;

    New.row[0].y = A.row[1].x;
    New.row[1].y = A.row[1].y;
    New.row[2].y = A.row[1].z;
    New.row[3].y = A.row[1].w;

    New.row[0].z = A.row[2].x;
    New.row[1].z = A.row[2].y;
    New.row[2].z = A.row[2].z;
    New.row[3].z = A.row[2].w;

    New.row[0].w = A.row[3].x;
    New.row[1].w = A.row[3].y;
    New.row[2].w = A.row[3].z;
    New.row[3].w = A.row[3].w;

    return New;
}

Affine BuildShadow(const Vector& v)
{
    Affine shadowMatrix;
    shadowMatrix.row[0].x = v.y;
    shadowMatrix.row[0].y = -v.x;
    shadowMatrix.row[2].y = -v.z;
    shadowMatrix.row[2].z = v.y;
    shadowMatrix.row[3].y = -1.f;
    shadowMatrix.row[3].w = v.y;

    return shadowMatrix;
}
