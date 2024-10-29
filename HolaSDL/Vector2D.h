#ifndef VECTOR2D_H_
#define VECTOR2D_H_

template <typename T>
class Vector2D {
public:
	T x, y;

	Vector2D() :x(0), y(0) {};
	Vector2D(T x, T y) : x(x), y(y) {};

	T getX() const { return x; };
	T getY() const { return y; };

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
};
template <typename T>
using Point2D = Vector2D<T>;
#endif