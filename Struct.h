#pragma once
enum class ColliderType;

struct Vector
{
	float x;
	float y;
	Vector()
	{
		this->x = 0;
		this->y = 0;
	}
	Vector(int x, int y)
	{
		this->x = (float)x;
		this->y = (float)y;
	}
	Vector(int x)
	{
		this->x = (float)x;
		this->y = (float)x;
	}
	Vector(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	Vector(float x)
	{
		this->x = x;
		this->y = x;
	}
	Vector operator + (const Vector& other)
	{
		return Vector(x + other.x, y + other.y);
	}
	template<typename T>
	Vector operator + (T num)
	{
		return Vector(x + num, y + num);
	}
	Vector& operator += (const Vector& other)
	{
		this->x + other.x;
		this->y + other.y;
		return *this;
	}

	template<typename T>
	Vector operator - (T num)
	{
		return Vector(x - num, y - num);
	}
	Vector operator - (const Vector& other)
	{
		return Vector(x - other.x, y - other.y);
	}
	Vector& operator -= (const Vector& other)
	{
		this->x - other.x;
		this->y - other.y;
		return *this;
	}

	template<typename T>
	Vector operator * (T num)
	{
		return Vector(x * num, y * num);
	}
	template<typename T>
	Vector& operator *= (T num)
	{
		this->x	* num;
		this->y	* num;
		return *this;
	}

	Vector operator * (const Vector& other)
	{
		return Vector(x * other.x, y * other.y);
	}
	template<typename T>
	Vector& operator /= (T num)
	{
		assert(0 != num);
		this->x / num;
		this->y / num;
		return *this;
	}
	template<typename T>
	Vector operator / (T num)
	{
		assert(0 != num);
		return Vector(x / num, y / num);
	}

	float Magnitude() const
	{
		return sqrtf(x * x) + (y * y);
	}

	float SqrMagnitude() const
	{
		return (x * x) + (y * y);
	}

	void Normalize()
	{
		float magnitude = Magnitude();
		if (magnitude == 0)
		{
			return;
		}
		this->x /= magnitude;
		this->y /= magnitude;
	}

	Vector Normalized() const
	{
		float magnitude = Magnitude();
		if (magnitude == 0)
		{
			return Vector();
		}
		float x = this->x / magnitude;
		float y = this->y / magnitude;
		return Vector(x, y);
	}
};

struct RectSize
{
	float left;
	float right;
	float top;
	float bottom;
	RectSize() { left = 0; right = 0; top = 0; bottom = 0; }
	RectSize(float left, float right, float top, float bottom)
	{
		this->left = left; this->right = right;
		this->top = top; this->bottom = bottom;
	}

	RectSize operator+(const Vector& other)
	{
		return RectSize(left + other.x, right + other.x, top + other.y, bottom + other.y);
	}
	RectSize operator-(const Vector& other)
	{
		return RectSize(left - other.x, right - other.x, top - other.y, bottom - other.y);
	}
};

struct ColliderMatrix
{
	Vector offset;
	Vector scale;
	ColliderType type;
	ColliderMatrix(ColliderType type, Vector offset, Vector scale) 
	{ 
		this->type = type;
		this->offset = offset; 
		this->scale = scale; 
	}
};

struct Color
{
	Color()
	{
		this->r = 255;
		this->g = 255;
		this->b = 255;
		this->a = 1;
	}
	BYTE r, g, b;
	FLOAT a;
	Color(BYTE r, BYTE g, BYTE b, FLOAT a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};
