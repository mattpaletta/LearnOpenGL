#pragma once

template<typename T>
struct Point2d {
	constexpr Point2d(const T& _x, const T& _y) : x(_x), y(_y) {} 
	T x;
	T y;
};

template<typename T>
struct Point3d {
	constexpr Point3d(const T& _x, const T& _y, const T& _z) : x(_x), y(_y), z(_z) {} 
	T x;
	T y;
	T z;
};
