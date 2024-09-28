#pragma once

#include <cmath>

namespace math
{
    inline float toRadians(float degrees)
    {
        return degrees * M_PI / 180.f;
    }
}

template <typename T>
struct Vec2
{
    T x, y;

    Vec2() : x(0), y(0) {}
    Vec2(T x, T y) : x(x), y(y) {}

    bool operator==(const Vec2 v)
    {
        return x == v.x && y == v.y;
    }

    bool operator!=(const Vec2 v)
    {
        return x != v.x || y != v.y;
    }

    Vec2 operator+(Vec2 v)
    {
        return Vec2(x + v.x, y + v.y);
    }
};
typedef Vec2<int> iVec2;
typedef Vec2<float> fVec2;

template <typename T>
struct Vec3
{
    T x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    Vec3 rotateX(float angle)
    {
        float rads = math::toRadians(angle);
        y = y * cos(rads) - z * sin(rads);
        z = y * sin(rads) + z * cos(rads);
        return *this;
    }

    Vec3 rotateY(float angle)
    {
        float rads = math::toRadians(angle);
        x = x * cos(rads) + z * sin(rads);
        z = -x * sin(rads) + z * cos(rads);
        return *this;
    }

    Vec3 rotateZ(float angle)
    {
        float rads = math::toRadians(angle);
        x = x * cos(rads) - y * sin(rads);
        y = x * sin(rads) + y * cos(rads);
        return *this;
    }

    Vec3 normalize() const
    {
        float length = std::sqrt(x * x + y * y + z * z);
        return {x / length, y / length, z / length};
    }

    float distance(Vec3 v) const
    {
        return std::sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y) + (z - v.z) * (z - v.z));
    }

    float length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    float dot(Vec3 v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    bool operator==(const Vec3 v)
    {
        return x == v.x && y == v.y && z == v.z;
    }

    Vec3 operator+(Vec3 v)
    {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    Vec3 operator-(Vec3 v)
    {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    Vec3 operator*(T scalar)
    {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    Vec3 operator*(Vec3 v)
    {
        return Vec3(x * v.x, y * v.y, z * v.z);
    }

    Vec3 operator/(T scalar)
    {
        return Vec3(x / scalar, y / scalar, z / scalar);
    }

    Vec3 operator+=(Vec3 v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec3 operator*=(Vec3 v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }
};
typedef Vec3<int> iVec3;
typedef Vec3<float> fVec3;

template <typename T>
struct Mat
{
    int rows, cols;
    T **data;

    Mat(int rows, int cols)
        : rows(rows), cols(cols)
    {
        data = new T *[rows];
        for (int i = 0; i < rows; ++i)
            data[i] = new T[cols]();

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] = 0;
    }

    Mat(const Mat &other) : rows(other.rows), cols(other.cols)
    {
        data = new T *[rows];
        for (int i = 0; i < rows; ++i)
        {
            data[i] = new T[cols];
            for (int j = 0; j < cols; ++j)
            {
                data[i][j] = other.data[i][j];
            }
        }
    }

    Mat(Mat &&other) noexcept : rows(other.rows), cols(other.cols), data(other.data)
    {
        other.data = nullptr;
        other.rows = other.cols = 0;
    }

    ~Mat()
    {
        for (int i = 0; i < rows; ++i)
        {
            delete[] data[i];
        }

        delete[] data;
    }

    static Mat identity(int size)
    {
        Mat result(size, size);

        for (int i = 0; i < size; ++i)
            result.data[i][i] = 1;

        return result;
    }

    T *operator[](const int i) const
    {
        return data[i];
    }

    const Mat operator*(const Mat &m) const
    {
        if (cols != m.rows)
            return Mat(0, 0);

        Mat result(rows, m.cols);

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < m.cols; ++j)
                for (int k = 0; k < cols; ++k)
                    result.data[i][j] += data[i][k] * m.data[k][j];

        return result;
    }

    const Mat operator*(const T scalar)
    {
        Mat result(rows, cols);

        for (int i = 0; i < rows * cols; ++i)
            result.data[i] = data[i] * scalar;

        return result;
    }

    const Mat operator+(const Mat &m) const
    {
        if (rows != m.rows || cols != m.cols)
            return Mat(0, 0);

        Mat result(rows, cols);

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + m.data[i][j];

        return result;
    }

    const Mat operator-(const Mat &m) const
    {
        if (rows != m.rows || cols != m.cols)
            return Mat(0, 0);

        Mat result(rows, cols);

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] - m.data[i][j];

        return result;
    }
};
typedef Mat<int> iMat;
typedef Mat<float> fMat;