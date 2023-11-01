//
// Created by ryousuke kaga on 2023/10/31.
//

#ifndef FLUID_ENGINE_VECTOR2_H
#define FLUID_ENGINE_VECTOR2_H

#include <vector>
#include <algorithm>
#include <cmath>

#define EPSILON 1e-4

int double_cmp(double a, double b);

class Vector2 final {
public:
    constexpr Vector2(): x(0), y(0) {}
    constexpr Vector2(double x_, double y_) : x(x_), y(y_) {}
    constexpr Vector2(const Vector2& v) : x(v.x), y(v.y) {}
    void set(double s);
    void set(double x_, double y_);
    void set(const std::initializer_list<double>& lst);
    void set(const Vector2& other);
    void setZero();
    void normalize();
    Vector2 add(double v) const;
    Vector2 add(const Vector2& v) const;
    Vector2 sub(double v) const;
    Vector2 sub(const Vector2& v) const;
    Vector2 mul(double v) const;
    Vector2 mul(const Vector2& v) const;
    Vector2 div(double v) const;
    Vector2 div(const Vector2& v) const;
    double dot(const Vector2& v) const;
    Vector2 rsub(double v) const;
    Vector2 rsub(const Vector2& v) const;
    Vector2 rdiv(double v) const;
    Vector2 rdiv(const Vector2& v) const;
    void iadd(double v);
    void iadd(const Vector2& v);
    void isub(double v);
    void isub(const Vector2& v);
    void imul(double v);
    void imul(const Vector2& v);
    void idiv(double v);
    void idiv(const Vector2& v);
    const double& at(size_t i) const;
    double& at(size_t i);
    double sum() const;
    double avg() const;
    double min() const;
    double max() const;
    double absmin() const;
    double absmax() const;
    Vector2 normalized() const;
    double length() const;
    double lengthSquared() const;
    double distanceTo(const Vector2& other) const;
    double distanceSquaredTo(const Vector2& other) const;
    Vector2 projected(const Vector2& normal) const;
    Vector2 reflected(const Vector2& normal) const;
    bool isEqual(const Vector2& other) const;

    double& operator[](size_t i);
    const double& operator[](size_t i) const;
    Vector2& operator=(const std::initializer_list<double>& lst);
    Vector2& operator=(const Vector2& v);
    Vector2& operator+=(double v);
    Vector2& operator+=(const Vector2& v);
    Vector2& operator-=(double v);
    Vector2& operator-=(const Vector2& v);
    Vector2& operator*=(double v);
    Vector2& operator*=(const Vector2& v);
    Vector2& operator/=(double v);
    Vector2& operator/=(const Vector2& v);
    bool operator==(const Vector2& v) const;
    bool operator!=(const Vector2& v) const;
    double x;
    double y;
};


using Vector2 = Vector2;


Vector2 operator+(const Vector2& a);


Vector2 operator-(const Vector2& a);


Vector2 operator+(double a, const Vector2& b);


Vector2 operator+(const Vector2& a, double b);


Vector2 operator+(const Vector2& a, const Vector2& b);


Vector2 operator-(const Vector2& a, double b);


Vector2 operator-(double a, const Vector2& b);


Vector2 operator-(const Vector2& a, const Vector2& b);


Vector2 operator*(const Vector2& a, double b);


Vector2 operator*(double a, const Vector2& b);


Vector2 operator*(const Vector2& a, const Vector2& b);


Vector2 operator/(const Vector2& a, double b);


Vector2 operator/(double a, const Vector2& b);


Vector2 operator/(const Vector2& a, const Vector2& b);


Vector2 min(const Vector2& a, const Vector2& b);


Vector2 max(const Vector2& a, const Vector2& b);


Vector2 clamp(const Vector2& v, const Vector2& low,
                 const Vector2& high);


Vector2 ceil(const Vector2& a);


Vector2 floor(const Vector2& a);

#endif //FLUID_ENGINE_VECTOR2_H
