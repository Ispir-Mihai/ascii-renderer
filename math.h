#pragma once

#include <cmath>

template <typename T>
struct Vec2
{
    T x, y;

    Vec2() : x(0), y(0) {}
    Vec2(T x, T y) : x(x), y(y) {}

    // Normalize the vector
    Vec2 normalize() const
    {
        float length = std::sqrt(x * x + y * y);
        return {x / length, y / length};
    }

    // Calculate the distance between two vectors
    float distance(Vec2 v) const
    {
        return std::sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
    }

    // Calculate the length of the vector
    float length() const
    {
        return std::sqrt(x * x + y * y);
    }

    // Calculate the dot product of two vectors
    float dot(Vec2 v) const
    {
        return x * v.x + y * v.y;
    }

    // Compare two vectors
    bool operator==(const Vec2 v)
    {
        return x == v.x && y == v.y;
    }

    // Compare two vectors
    bool operator!=(const Vec2 v)
    {
        return x != v.x || y != v.y;
    }

    // Add two vectors
    Vec2 operator+(Vec2 v)
    {
        return Vec2(x + v.x, y + v.y);
    }

    // Substract two vectors
    Vec2 operator-(Vec2 v)
    {
        return Vec2(x - v.x, y - v.y);
    }

    // Multiply a vector by a scalar
    Vec2 operator*(T scalar)
    {
        return Vec2(x * scalar, y * scalar);
    }

    // Multiply two vectors
    Vec2 operator*(Vec2 v)
    {
        return Vec2(x * v.x, y * v.y);
    }

    // Divide the vector by a scalar
    Vec2 operator/(T scalar)
    {
        return Vec2(x / scalar, y / scalar);
    }

    // Add to the vector
    Vec2 operator+=(Vec2 v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    // Substract from the vector
    Vec2 operator-=(Vec2 v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    // Multiply the vector by a scalar
    Vec2 operator*=(Vec2 v)
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }
};
typedef Vec2<int> iVec2;
typedef Vec2<float> fVec2;

namespace math
{
    // Convert degrees to radians
    inline float toRadians(float degrees)
    {
        return degrees * M_PI / 180.f;
    }

    // Convert radians to degrees
    inline float toDegrees(float radians)
    {
        return radians * 180.f / M_PI;
    }

    // Calculate the area of a triangle
    inline float triArea(const iVec2 &v0, const iVec2 &v1, const iVec2 &v2)
    {
        return std::fabs((v1.x - v0.x) * (v2.y - v0.y) - (v2.x - v0.x) * (v1.y - v0.y)) / 2.0f;
    }

    // Check if a point is inside a triangle (edge function)
    inline bool edgeFunction(const iVec2 &a, const iVec2 &b, const iVec2 &c)
    {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) >= 0;
    }
}

template <typename T>
struct Vec3
{
    T x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    // Rotate the Vector around origin
    Vec3 rotate(Vec3 origin, Vec3 euler)
    {
        // Translate the point to the origin (subtract origin)
        x -= origin.x;
        y -= origin.y;
        z -= origin.z;

        // Convert Euler angles (in degrees) to radians
        float radsX = math::toRadians(euler.x);
        float radsY = math::toRadians(euler.y);
        float radsZ = math::toRadians(euler.z);

        // Rotation around X axis
        T ny = y * cos(radsX) - z * sin(radsX);
        T nz = y * sin(radsX) + z * cos(radsX);
        y = ny;
        z = nz;

        // Rotation around Y axis
        T nx = x * cos(radsY) + z * sin(radsY);
        nz = -x * sin(radsY) + z * cos(radsY);
        x = nx;
        z = nz;

        // Rotation around Z axis
        nx = x * cos(radsZ) - y * sin(radsZ);
        ny = x * sin(radsZ) + y * cos(radsZ);
        x = nx;
        y = ny;

        // Translate the point back to its original position (add origin)
        x += origin.x;
        y += origin.y;
        z += origin.z;

        return *this;
    }

    // Normalize the vector
    Vec3 normalize() const
    {
        float length = std::sqrt(x * x + y * y + z * z);
        return {x / length, y / length, z / length};
    }

    // Calculate the distance between two vectors
    float distance(Vec3 v) const
    {
        return std::sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y) + (z - v.z) * (z - v.z));
    }

    // Calculate the length of the vector
    float length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Calculate the dot product of two vectors
    float dot(Vec3 v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    // Compare two vectors
    bool operator==(const Vec3 v)
    {
        return x == v.x && y == v.y && z == v.z;
    }

    // Compare two vectors
    bool operator!=(const Vec3 v)
    {
        return x != v.x || y != v.y || z != v.z;
    }

    // Add two vectors
    Vec3 operator+(Vec3 v)
    {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    // Substract two vectors
    Vec3 operator-(Vec3 v)
    {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    // Multiply a vector by a scalar
    Vec3 operator*(T scalar)
    {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    // Multiply two vectors
    Vec3 operator*(Vec3 v)
    {
        return Vec3(x * v.x, y * v.y, z * v.z);
    }

    // Divide the vector by a scalar
    Vec3 operator/(T scalar)
    {
        return Vec3(x / scalar, y / scalar, z / scalar);
    }

    // Add to the vector
    Vec3 operator+=(Vec3 v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    // Substract from the vector
    Vec3 operator-=(Vec3 v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // Multiply the vector by a scalar
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

    // Constructor
    Mat(int rows, int cols)
        : rows(rows), cols(cols)
    {
        // Allocate memory for the matrix
        data = new T *[rows];
        for (int i = 0; i < rows; ++i)
            data[i] = new T[cols]();

        // Fill the matrix with zeros
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] = 0;
    }

    // Copy constructor
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

    ~Mat()
    {
        // Free memory
        for (int i = 0; i < rows; ++i)
        {
            delete[] data[i];
        }

        delete[] data;
    }

    // Create an identity matrix
    static Mat identity(int size)
    {
        Mat result(size, size);

        for (int i = 0; i < size; ++i)
            result.data[i][i] = 1;

        return result;
    }

    // Access the matrix element
    T *operator[](const int i) const
    {
        return data[i];
    }

    // Multiply two matrices
    Mat operator*(const Mat &m) const
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

    // Multiply the matrix by a scalar
    Mat operator*(const T scalar)
    {
        Mat result(rows, cols);

        for (int i = 0; i < rows * cols; ++i)
            result.data[i] = data[i] * scalar;

        return result;
    }

    // Add two matrices
    Mat operator+(const Mat &m) const
    {
        if (rows != m.rows || cols != m.cols)
            return Mat(0, 0);

        Mat result(rows, cols);

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + m.data[i][j];

        return result;
    }

    // Substract two matrices
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