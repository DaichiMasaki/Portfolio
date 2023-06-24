#pragma once
#include <cmath>
#include <memory.h>
#include <limits>

namespace Math
{
	const float Pi = 3.1415926535f;
	const float TwoPi = Pi * 2.0f;
	const float PiOver2 = Pi / 2.0f;
	const float Infinity = std::numeric_limits<float>::infinity();
	const float NegInfinity = -std::numeric_limits<float>::infinity();

	inline float ToRadians(float degrees)
	{
		return degrees * Pi / 180.0f;
	}

	inline float ToDegrees(float radians)
	{
		return radians * 180.0f / Pi;
	}

	inline bool NearZero(float val, float epsilon = 0.001f)
	{
		if (fabs(val) <= epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T Max(const T& a, const T& b)
	{
		return (a < b ? b : a);
	}

	template <typename T>
	T Min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	template <typename T>
	T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, value));
	}

	inline float Abs(float value)
	{
		return fabs(value);
	}

	inline float Cos(float angle)
	{
		return cosf(angle);
	}

	inline float Sin(float angle)
	{
		return sinf(angle);
	}

	inline float Tan(float angle)
	{
		return tanf(angle);
	}

	inline float Acos(float value)
	{
		return acosf(value);
	}

	inline float Atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float Cot(float angle)
	{
		return 1.0f / Tan(angle);
	}

	inline float Lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

	inline float Sqrt(float value)
	{
		return sqrtf(value);
	}

	inline float Fmod(float numer, float denom)
	{
		return fmod(numer, denom);
	}
}


class Vector2
{
public:
	float x;
	float y;

	Vector2()
		:x(0.0f)
		, y(0.0f)
	{

	}

	explicit Vector2(float inX, float inY)
		:x(inX)
		, y(inY)
	{

	}

	//�x�N�g���̃Z�b�g
	void Set(float inX, float inY)
	{
		x = inX;
		y = inY;
	}

	//�x�N�g���̑����Z
	friend Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	//�x�N�g���̈����Z
	friend Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	//�x�N�g��x,y���ꂼ��̊|���Z
	friend Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.y, a.y * b.y);
	}

	//�x�N�g���̃X�J���[�|���Z
	friend Vector2 operator*(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	friend Vector2 operator*(float scalar, const Vector2& vec)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	//�X�J���[��*=
	Vector2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	//�x�N�g����+=
	Vector2& operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	//�x�N�g����-=
	Vector2& operator-=(const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	//�x�N�g���̑傫���̓��
	float LengthSq() const { return (x * x + y * y); }

	//�x�N�g���̑傫��
	float Length() const { return(Math::Sqrt(LengthSq())); }

	//�P�ʃx�N�g��(���K��)
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	//�����Ƃ��ăx�N�g�����^����ꂽ���̒P�ʃx�N�g��
	static Vector2 Normalize(const Vector2& vec)
	{
		Vector2 temp = vec;
		temp.Normalize();
		return temp;
	}

	//����
	static float Dot(const Vector2& a, const Vector2& b)
	{
		return(a.x * b.x + a.y * b.y);
	}

	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 NegUnitX;
	static const Vector2 NegUnitY;
};