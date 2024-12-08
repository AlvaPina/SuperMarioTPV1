#ifndef VECTOR2D_H_
#define VECTOR2D_H_

template <typename T>
class Vector2D {
private:
	T x, y;
public:
	Vector2D() :x(0), y(0) {};
	Vector2D(T x, T y) : x(x), y(y) {};

	T getX() const { return x; };
	T getY() const { return y; };

	void setX(T value) { x = value; };
	void setY(T value) { y = value; };

	void addX(T dx) { x += dx; }
	void addY(T dy) { y += dy; }

	Vector2D<T> operator+(Vector2D<T> other) {
		return Vector2D<T>(x + other.x, y + other.y);
	}
	//Vector2D<T> operator+(T cordenada1, T cordenada2) {
	//	return Vector2D<T>(x + cordenada1, y + cordenada2);
	//}
	Vector2D<T> operator-(Vector2D<T> other) {
		return Vector2D<T>(x - other.x, y - other.y);
	}
	Vector2D<T> operator*(Vector2D<T> other) {
		return Vector2D<T>(x * other.x, y * other.y);
	}
	Vector2D<T> operator*(const T& escalar) {
		return Vector2D<T>(x * escalar, y * escalar);
	}
	Vector2D<T>& operator+=(const Vector2D<T>& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
};
template <typename T>
using Point2D = Vector2D<T>;
#endif

