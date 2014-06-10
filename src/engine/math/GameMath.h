/*
	Quaternion and Matrix manipulations

	Original source can be found here:
	Copyright 2010, Etay Meiri - http://ogldev.atspace.co.uk/index.html
*/

/*	Copyright 2010 Etay Meiri

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

// TODO: rewrite math lib in GLSL, for better performance?

#ifndef __GAME_MATH_H__
#define __GAME_MATH_H__

#ifdef _WIN32
	#include <cmath>
#else
	#include <math.h>
#endif

#include <cstdlib>

static const float PI_OVER_180 = (float)(3.14159265358979323846 / 180.0f);
static const float _180_OVER_PI = (float)(180.0f / 3.14159265358979323846);

inline float toRadian(float deg) {
	return deg * PI_OVER_180;
}

inline float toDegree(float rad) {
	return rad * _180_OVER_PI;
}

struct Quaternion {
	float x, y, z, w;

	Quaternion(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w) {}

	void normalize() {
		float length = sqrtf(x * x + y * y + z * z + w * w);

		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	Quaternion conjugate() {
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion mult(const Quaternion& r) {
		float _w = (w * r.w) - (x * r.x) - (y * r.y) - (z * r.z);
		float _x = (x * r.w) + (w * r.x) + (y * r.z) - (z * r.y);
		float _y = (y * r.w) + (w * r.y) + (z * r.x) - (x * r.z);
		float _z = (z * r.w) + (w * r.z) + (x * r.y) - (y * r.x);

		return Quaternion(_x, _y, _z, _w);
	}
};

struct Vector3f {
	float x;
	float y;
	float z;

	Vector3f() : x(0), y(0), z(0) {}

	Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

	Vector3f& operator+=(const Vector3f& r) {
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}

	Vector3f& operator-=(const Vector3f& r) {
		x -= r.x;
		y -= r.y;
		z -= r.z;

		return *this;
	}

	Vector3f& operator*=(float f) {
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	Vector3f cross(const Vector3f& v) const {
		float _x = y * v.z - z * v.y;
		float _y = z * v.x - x * v.z;
		float _z = x * v.y - y * v.x;

		return Vector3f(_x, _y, _z);
	}

	Vector3f& normalize() {
		float length = sqrtf(x * x + y * y + z * z);

		x /= length;
		y /= length;
		z /= length;

		return *this;
	}

	void rotate(float angle, const Vector3f& axis) {
		float sinHalfAngle = sinf(toRadian(angle/2));
    	float cosHalfAngle = cosf(toRadian(angle/2));

    	float Rx = axis.x * sinHalfAngle;
    	float Ry = axis.y * sinHalfAngle;
    	float Rz = axis.z * sinHalfAngle;
    	float Rw = cosHalfAngle;
    	Quaternion rotationQ(Rx, Ry, Rz, Rw);

   	 	Quaternion conjugateQ = rotationQ.conjugate();
		Quaternion W = this->multQuaternion(rotationQ).mult(conjugateQ);

    	x = W.x;
    	y = W.y;
   	 	z = W.z;
	}

	Quaternion multQuaternion(const Quaternion& q) {
		float _w = -(q.x * x) - (q.y * y) - (q.z * z);
		float _x = (q.w * x) + (q.y * z) - (q.z * y);
		float _y = (q.w * y) + (q.z * x) - (q.x * z);
		float _z = (q.w * z) + (q.x * y) - (q.y * x);

		return Quaternion(_x, _y, _z, _w);
	}
};

inline Vector3f operator+(const Vector3f& l, const Vector3f& r) {
	return Vector3f(l.x + r.x, l.y + r.y, l.z + r.z);
}

inline Vector3f operator-(const Vector3f& l, const Vector3f& r) {
	return Vector3f(l.x - r.x, l.y - r.y, l.z - r.z);
}

inline Vector3f operator*(const Vector3f& l, float f) {
	return Vector3f(l.x * f, l.y * f, l.z * f);
}

class Matrix4f {
	public:
		float m[4][4];

		/**
		* Matrix is deliberately left uninitialised because values
		* will be rewritten anyway
		*/
		Matrix4f() {}

		inline void loadIdentity() {
			m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
			m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
			m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
			m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
		}

		inline Matrix4f operator*(const Matrix4f& right) const {
			Matrix4f ret;

			for (unsigned int i = 0; i < 4; ++i) {
				for (unsigned int j = 0; j < 4; ++j) {
					ret.m[i][j] = m[i][0] * right.m[0][j] +
								  m[i][1] * right.m[1][j] +
								  m[i][2] * right.m[2][j] +
								  m[i][3] * right.m[3][j];
				}
			}

			return ret;
		}

		void scale(float scaleX, float scaleY, float scaleZ) {
			m[0][0] = scaleX; m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
			m[1][0] = 0.0f;   m[1][1] = scaleY; m[1][2] = 0.0f;   m[1][3] = 0.0f;
			m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = scaleZ; m[2][3] = 0.0f;
			m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;
		}

		void rotate(float rotateX, float rotateY, float rotateZ) {
			Matrix4f rx, ry, rz;

			float x = toRadian(rotateX);
			float y = toRadian(rotateY);
			float z = toRadian(rotateZ);

			rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f;	 rx.m[0][2] = 0.0f;		rx.m[0][3] = 0.0f;
			rx.m[1][0] = 0.0f; rx.m[1][1] = cosf(x); rx.m[1][2] = -sinf(x); rx.m[1][3] = 0.0f;
			rx.m[2][0] = 0.0f; rx.m[2][1] = sinf(x); rx.m[2][2] = cosf(x);	rx.m[2][3] = 0.0f;
			rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f;	 rx.m[3][2] = 0.0f;		rx.m[3][3] = 1.0f;

			ry.m[0][0] = cosf(y);	ry.m[0][1] = 0.0f; ry.m[0][2] = -sinf(y);	ry.m[0][3] = 0.0f;
			ry.m[1][0] = 0.0f;		ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f;		ry.m[1][3] = 0.0f;
			ry.m[2][0] = sinf(y);	ry.m[2][1] = 0.0f; ry.m[2][2] = cosf(y);	ry.m[2][3] = 0.0f;
			ry.m[3][0] = 0.0f;		ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f;		ry.m[3][3] = 1.0f;

			rz.m[0][0] = cosf(z); rz.m[0][1] = -sinf(z); rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
			rz.m[1][0] = sinf(z); rz.m[1][1] = cosf(z);  rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
			rz.m[2][0] = 0.0f;	  rz.m[2][1] = 0.0f;	 rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
			rz.m[3][0] = 0.0f;	  rz.m[3][1] = 0.0f;	 rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;

			*this = rz * ry * rx;
		}

		void translate(float x, float y, float z) {
			m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
			m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
			m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
			m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
		}

		void initCameraTransform(const Vector3f& Target, const Vector3f& Up) {
			Vector3f N = Target;
			N.normalize();
			Vector3f U = Up;
			U.normalize();
			U = U.cross(N);
			Vector3f V = N.cross(U);

			m[0][0] = U.x;   m[0][1] = U.y;   m[0][2] = U.z;   m[0][3] = 0.0f;
			m[1][0] = V.x;   m[1][1] = V.y;   m[1][2] = V.z;   m[1][3] = 0.0f;
			m[2][0] = N.x;   m[2][1] = N.y;   m[2][2] = N.z;   m[2][3] = 0.0f;
			m[3][0] = 0.0f;  m[3][1] = 0.0f;  m[3][2] = 0.0f;  m[3][3] = 1.0f;
		}

		void setPerspectiveProjection(float fov, float width, float height, float zNear, float zFar) {
			float ar = width / height;
			float zRange = zNear - zFar;
			float tanHalfFOV = tanf(toRadian(fov / 2.0f));

			m[0][0] = 1.0f / (tanHalfFOV * ar); m[0][1] = 0.0f;            m[0][2] = 0.0f;          m[0][3] = 0.0;
			m[1][0] = 0.0f;                   m[1][1] = 1.0f / tanHalfFOV; m[1][2] = 0.0f;          m[1][3] = 0.0;
			m[2][0] = 0.0f;                   m[2][1] = 0.0f;            m[2][2] = (-zNear - zFar) / zRange; m[2][3] = 2.0f * zFar * zNear / zRange;
			m[3][0] = 0.0f;                   m[3][1] = 0.0f;            m[3][2] = 1.0f;          m[3][3] = 0.0;
		}
};

struct Point3f {
	float x, y, z;

	Point3f(float x, float y, float z) : x(x), y(y), z(z) {}

	inline Point3f& operator += (Vector3f v) {
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return *this;
	}

	inline Point3f& operator -= (Vector3f v) {
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		return *this;
	}
};

inline Point3f operator + (Point3f p, Vector3f v) {
	return Point3f(p.x + v.x, p.y + v.y, p.z + v.z);
}

inline Vector3f operator - (Point3f p, Point3f p1) {
	return Vector3f(p.x - p1.x, p.y - p1.y, p.z - p1.z);
}

inline float distanceBetween(const Point3f & p1, const Point3f & p2) {
	float dx = p2.x - p1.x;
	float dy = p2.y - p1.y;
	float dz = p2.z - p1.z;

	return sqrt(dx*dx + dy*dy + dz*dz);
}

struct Vector2f {
	float x;
	float y;

	Vector2f() {}
	Vector2f(float x, float y) : x(x), y(y) {}
};

struct Vector2i {
	int x;
	int y;

	Vector2i() {}
	Vector2i(int x, int y) : x(x), y(y) {}
};

struct Point2 {
	int x, y;

	Point2() {}
	Point2(int x, int y) : x(x), y(y) {}
};

struct Rectangle2 {
	int x, y, w, h;

	inline bool contains(const Point2 & p) {
		return p.x >= x && p.x <= x + w
			&& p.y >= y && p.y <= y + h;
	}

	inline bool intersects(const Rectangle2 & other) {
		if (x + w < other.x || x > other.x + other.w)
			return false;

		if (y + h < other.y || y > other.y + other.h)
			return false;

		return true;
	}
};

typedef Rectangle2 Rect;

struct Rectangle2f {
	float x, y, w, h;

	inline bool contains(const Point2 & p) {
		return p.x >= x && p.x <= x + w
			&& p.y >= y && p.y <= y + h;
	}

	inline bool intersects(const Rectangle2f & other) {
		if (x + w < other.x || x > other.x + other.w)
			return false;

		if (y + h < other.y || y > other.y + other.h)
			return false;

		return true;
	}
};

typedef Rectangle2f Rectf;

struct Dimension2i {
	int w, h;

	Dimension2i() : w(0), h(0) {}
	Dimension2i(int w, int h) : w(w), h(h) {}
};

/**
* Init srand() before to get different random values every time you start program
*
* @return
*			a random integer value between "min" and "max", both inclusive
*/
inline int getRandom(int min, int max) {
	return (int)(rand() % (max - min)) + min;
}

inline bool isBetween(float value, float min, float max) {
	return value >= min && value <= max;
}

#endif
