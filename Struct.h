#pragma once

struct Vector
{
	float x;
	float y;
	Vector()
	{
		x = 0;
		y = 0;
	}
	Vector(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	Vector operator+(const Vector& other)
	{
		return Vector(x + other.x, y + other.y);
	}
	Vector operator-(const Vector& other)
	{
		return Vector(x - other.x, y - other.y);
	}
	Vector operator*(const Vector& other)
	{
		return Vector(x * other.x, y * other.y);
	}
};