//
// Created by ryousuke kaga on 2023/10/31.
//

#include "Vector2.h"

int double_cmp(double a, double b) {
    return fabs(a-b) < EPSILON;
}

void Vector2::set(double s) {
    x = s;
    y = s;
}


void Vector2::set(double x_, double y_) {
    x = x_;
    y = y_;
}


void Vector2::set(const std::initializer_list<double>& lst) {
    auto inputElem = lst.begin();
    x = *inputElem;
    y = *(++inputElem);
}


void Vector2::set(const Vector2& other) {
    x = other.x;
    y = other.y;
}


void Vector2::setZero() {
    x = 0;
    y = 0;
}


void Vector2::normalize() {
    double norm = sqrt(x * x + y * y);
    x /= norm;
    y /= norm;
}


Vector2 Vector2::add(double v) const {
    return {x + v, y + v};
}


Vector2 Vector2::add(const Vector2& v) const {
    return {x + v.x, y + v.y};
}


Vector2 Vector2::sub(double v) const {
    return {x - v, y - v};
}


Vector2 Vector2::sub(const Vector2& v) const {
    return {x - v.x, y - v.y};
}


Vector2 Vector2::mul(double v) const {
    return {x * v, y * v};
}


Vector2 Vector2::mul(const Vector2& v) const {
    return {x * v.x, y * v.y};
}


Vector2 Vector2::div(double v) const {
    return {x / v, y / v};
}


Vector2 Vector2::div(const Vector2& v) const {
    return {x / v.x, y / v.y};
}


double Vector2::dot(const Vector2& v) const {
    return x * v.x + y * v.y;
}


Vector2 Vector2::rsub(double v) const {
    return {v - x, v - y};
}


Vector2 Vector2::rsub(const Vector2& v) const {
    return {v.x - x, v.y - y};
}


Vector2 Vector2::rdiv(double v) const {
    return {v / x, v / y};
}


Vector2 Vector2::rdiv(const Vector2& v) const {
    return {v.x / x, v.y / y};
}


void Vector2::iadd(double v) {
    x += v;
    y += v;
}


void Vector2::iadd(const Vector2& v) {
    x += v.x;
    y += v.y;
}


void Vector2::isub(double v) {
    x -= v;
    y -= v;
}


void Vector2::isub(const Vector2& v) {
    x -= v.x;
    y -= v.y;
}


void Vector2::imul(double v) {
    x *= v;
    y *= v;
}


void Vector2::imul(const Vector2& v) {
    x *= v.x;
    y *= v.y;
}


void Vector2::idiv(double v)  {
    x /= v;
    y /= v;
}


void Vector2::idiv(const Vector2& v) {
    x /= v.x;
    y /= v.y;
}


const double& Vector2::at(size_t i) const {
    return i == 0 ? x :
           i == 1 ? y : x;
}


double& Vector2::at(size_t i) {
    return i == 0 ? x :
           i == 1 ? y : x;
}


double Vector2::sum() const {
    return x + y;
}


double Vector2::avg() const {
    return (x + y) / 2;
}


double Vector2::min() const {
    return x < y ? x : y;
}


double Vector2::max() const {
    return x > y ? x : y;
}


double Vector2::absmin() const {
    return abs(x) < abs(y) ? abs(x) : abs(y);
}


double Vector2::absmax() const {
    return abs(x) > abs(y) ? abs(x) : abs(y);
}


double Vector2::length() const {
    return sqrt(x*x + y*y);
}


double Vector2::lengthSquared() const {
    return x*x + y*y;
}


Vector2 Vector2::normalized() const {
    return div(length());
}


double Vector2::distanceTo(const Vector2& other) const {
    return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}


double Vector2::distanceSquaredTo(const Vector2& other) const {
    return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
}


Vector2 Vector2::projected(const Vector2& normal) const {
    return sub(normal.mul(dot(normal)));
}


Vector2 Vector2::reflected(const Vector2& normal) const {
    return sub(normal.mul(dot(normal) * 2));
}


bool Vector2::isEqual(const Vector2& other) const {
    return double_cmp(x, other.x) && double_cmp(y, other.y);
}


double& Vector2::operator[](size_t i) {
    return at(i);
}


const double& Vector2::operator[](size_t i) const {
    return at(i);
}


Vector2& Vector2::operator=(const std::initializer_list<double>& lst) {
    auto inputElem = lst.begin();
    x = *inputElem;
    y = *(++inputElem);
    return *this;
}


Vector2& Vector2::operator=(const Vector2& v) {
    x = v.x;
    y = v.y;
    return *this;
}


Vector2& Vector2::operator+=(double v) {
    iadd(v);
    return *this;
}


Vector2& Vector2::operator+=(const Vector2& v) {
    iadd(v);
    return *this;
}


Vector2& Vector2::operator-=(double v) {
    isub(v);
    return *this;
}


Vector2& Vector2::operator-=(const Vector2& v) {
    isub(v);
    return *this;
}


Vector2& Vector2::operator*=(double v) {
    imul(v);
    return *this;
}


Vector2& Vector2::operator*=(const Vector2& v) {
    imul(v);
    return *this;
}


Vector2& Vector2::operator/=(double v) {
    idiv(v);
    return *this;
}


Vector2& Vector2::operator/=(const Vector2& v) {
    idiv(v);
    return *this;
}


bool Vector2::operator==(const Vector2& v) const {
    return isEqual(v);
}


bool Vector2::operator!=(const Vector2& v) const {
    return !isEqual(v);
}


Vector2 operator+(const Vector2& a) {
    return a;
}


Vector2 operator-(const Vector2& a) {
    return {-a.x, -a.y};
}


Vector2 operator+(double a, const Vector2& b) {
    return b.add(a);
}


Vector2 operator+(const Vector2& a, double b) {
    return a.add(b);
}


Vector2 operator+(const Vector2& a, const Vector2& b) {
    return a.add(b);
}


Vector2 operator-(const Vector2& a, double b) {
    return a.sub(b);
}


Vector2 operator-(double a, const Vector2& b) {
    return b.rsub(a);
}


Vector2 operator-(const Vector2& a, const Vector2& b) {
    return a.sub(b);
}


Vector2 operator*(const Vector2& a, double b) {
    return a.mul(b);
}


Vector2 operator*(double a, const Vector2& b) {
    return b.mul(a);
}


Vector2 operator*(const Vector2& a, const Vector2& b) {
    return a.mul(b);
}


Vector2 operator/(const Vector2& a, double b) {
    return a.div(b);
}


Vector2 operator/(double a, const Vector2& b) {
    return b.rdiv(a);
}


Vector2 operator/(const Vector2& a, const Vector2& b) {
    return a.div(b);
}


Vector2 min(const Vector2& a, const Vector2& b) {
    return {std::min(a.x, b.x), std::min(a.y, b.y)};
}


Vector2 max(const Vector2& a, const Vector2& b) {
    return {std::max(a.x, b.x), std::max(a.y, b.y)};
}


Vector2 clamp(const Vector2& v, const Vector2& low,
                 const Vector2& high) {
    return {std::clamp(v.x, low.x, high.x), std::clamp(v.y, low.y, high.y)};
}


Vector2 ceil(const Vector2& a) {
    return {std::ceil(a.x), std::ceil(a.y)};
}


Vector2 floor(const Vector2& a) {
    return {std::floor(a.x), std::floor(a.y)};
}