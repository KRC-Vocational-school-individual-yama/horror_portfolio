#pragma once

#include<assert.h>
#include<string>
#include<vector>
#include<list>
#include<math.h>
#include"../main/config.h"

#include<DxLib.h>

namespace DxLib {
	struct Vec2 {
		int x, y;
	};

	inline Vec2 operator +(const Vec2& a,const Vec2& b) {
		return Vec2{ a.x + b.x,a.y + b.y };
	}
	inline Vec2 operator -(const Vec2& a, const Vec2 b) {
		return Vec2{a.x-b.x,a.y-b.y};
	}
	inline Vec2 operator *(const Vec2& a, const Vec2& b) {
		return Vec2{a.x*b.x,a.y*b.y};
	}
	inline Vec2 operator /(const Vec2& a, const Vec2& b) {
		return Vec2{a.x/b.x,a.y/b.y};
	}
	inline Vec2 operator %(const Vec2& a, const Vec2& b) {
		return Vec2{a.x%b.x,a.y%b.y};
	}

	inline Vec2& operator +=( Vec2& a, const Vec2& b) {
		a.x += b.x;
		a.y += b.y;
		return a;
	}
	inline Vec2 operator -=( Vec2& a, const Vec2& b) {
		a.x -= b.x;
		a.y -= b.y;
		return a;
	}
	inline Vec2 operator *=(Vec2& a, const Vec2& b) {
		a.x *= b.x;
		a.y *= b.y;
		return a;
	}
	inline Vec2 operator /=(Vec2& a, const Vec2& b) {
		a.x /= b.x;
		a.y /= b.y;
		return a;
	}
	inline Vec2 operator %=(Vec2& a, const Vec2& b) {
		a.x %= b.x;
		a.y%= b.y;
		return a;
	}
	inline const bool operator ==(const Vec2& a, const Vec2& b) {
		return a.x==b.x&&a.y==b.y;
	}

	inline const VECTOR operator +(const VECTOR& a, const VECTOR& b) {
		return VAdd(a,b);
	}
	inline const VECTOR operator -(const VECTOR& a, const VECTOR& b) {
		return VSub(a, b);
	}
	inline const VECTOR operator *(const VECTOR& a, const VECTOR& b) {
		return { a.x * b.x,a.y * b.y,a.z * b.z };
	}
	inline const MATRIX operator *(const MATRIX& a, const MATRIX& b) {
		return MMult(a, b);
	}
	inline const VECTOR operator *(const VECTOR& a, const MATRIX& b) {
		return VTransform(a, b);
	}
}