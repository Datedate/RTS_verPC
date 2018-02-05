#ifndef _VECTOR2_H_
#define _VECTOR2_H_

class Vector2
{
public:
	float x, y;
public:
	Vector2() { x = 0; y = 0; };
	Vector2(float _x, float _y) { x = _x; y = _y; };
	Vector2(const Vector2& _copy) { x = _copy.x; y = _copy.y; };
	~Vector2() {};

	void Set(float _x, float _y) {
		this->x = _x;
		this->y = _y;
	}
	void Set(const Vector2& _value) {
		this->x = _value.x;
		this->y = _value.y;
	}

	Vector2 operator+(const Vector2& _value) const {
		Vector2 vec = Vector2(this->x + _value.x, this->y + _value.y);
		return vec;
	}
	void operator+=(const Vector2& _value) {
		this->Add(_value);
	}
	Vector2 operator-(const Vector2& _value) const {
		Vector2 vec = Vector2(this->x - _value.x, this->y - _value.y);
		return vec;
	}
	void operator-=(const Vector2& _value) {
		this->Sub(_value);
	}
	Vector2 operator*(float _value) const {
		Vector2 vec = Vector2(this->x * _value, this->y * _value);
		return vec;
	}
	void operator*=(float _value) {
		this->x *= _value;
		this->y *= _value;
	}
	Vector2 operator/(float _value) const {
		Vector2 vec = Vector2(this->x / _value, this->y / _value);
		return vec;
	}
	bool operator<(const Vector2& _value) const {
		if (this->x >= _value.x) return false;
		if (this->y >= _value.y) return false;
		return true;
	}
	bool operator>(const Vector2& _value) const {
		if (this->x <= _value.x) return false;
		if (this->y <= _value.y) return false;
		return true;
	}
	bool operator==(const Vector2& _value) const {
		if (this->x != _value.x) return false;
		if (this->y != _value.y) return false;
		return true;
	}
	bool operator!=(const Vector2& _value) const {
		if (this->x == _value.x) return false;
		if (this->y == _value.y) return false;
		return true;
	}
private:
	void Add(float _x, float _y) {
		this->x += _x;
		this->y += _y;
	}
	void Add(const Vector2& _value) {
		this->x += _value.x;
		this->y += _value.y;
	}
	void Sub(float _x, float _y) {
		this->x -= _x;
		this->y -= _y;
	}
	void Sub(const Vector2& _value) {
		this->x -= _value.x;
		this->y -= _value.y;
	}
};

class Size
{
public:
	Size() { width = 0;height = 0; };
	Size(float _width, float _height) { width = _width; height = _height; }
	~Size() {};
	void Set(float _width, float _height) {
		this->width = _width;
		this->height = _height;
	}
	void Set(const Size& _value) {
		this->width = _value.width;
		this->height = _value.height;
	}
	void Set(const Vector2& _value) {
		this->width = _value.x;
		this->height = _value.y;
	}

	Size operator+(const Size& _value) const {
		Size size = Size(this->width + _value.width, this->height + _value.height);
		return size;
	}
	void operator+=(const Size& _value) {
		this->Add(_value);
	}
	Size operator-(const Size& _value) const {
		Size size = Size(this->width - _value.width, this->height - _value.height);
		return size;
	}
	void operator-=(const Size& _value) {
		this->Sub(_value);
	}
	Size operator*(float _value) const {
		Size size = Size(this->width * _value, this->height * _value);
		return size;
	}
	void operator*=(float _value) {
		this->width *= _value;
		this->height *= _value;
	}
	Size operator/(float _value) const {
		Size size = Size(this->width / _value, this->height / _value);
		return size;
	}
	bool operator<(const Size& _value) const {
		if (this->width >= _value.width) return false;
		if (this->height >= _value.height) return false;
		return true;
	}
	bool operator>(const Size& _value) const {
		if (this->width <= _value.width) return false;
		if (this->height <= _value.height) return false;
		return true;
	}
	bool operator==(const Size& _value) const {
		if (this->width != _value.width) return false;
		if (this->height != _value.height) return false;
		return true;
	}
	bool operator!=(const Size& _value) const {
		if (this->width == _value.width) return false;
		if (this->height == _value.height) return false;
		return true;
	}
private:
	void Add(float _width, float _height) {
		this->width += _width;
		this->height += _height;
	}
	void Add(const Size& _value) {
		this->width += _value.width;
		this->height += _value.height;
	}
	void Add(const Vector2& _value) {
		this->width += _value.x;
		this->height += _value.y;
	}
	void Sub(float _width, float _height) {
		this->width -= _width;
		this->height -= _height;
	}
	void Sub(const Size& _value) {
		this->width -= _value.width;
		this->height -= _value.height;
	}
	void Sub(const Vector2& _value) {
		this->width -= _value.x;
		this->height -= _value.y;
	}
public:
	float width, height;
};


class Rect
{
public:
	Rect() { origin = Vector2(0, 0);size = Size(0, 0); };
	Rect(const Vector2& _origin, const Size& _size) {
		origin = _origin;
		size = _size;
	}
	Rect(float _x, float _y, float _width, float _height) {
		origin.Set(_x, _y);
		size.Set(_width, _height);
	}
	~Rect() {};
	Rect& operator= (const Rect& other) {
		Rect rect = Rect(other.origin, other.size);
		return rect;
	}
	void setRect(float _x, float _y, float _width, float _height) {
		origin.Set(_x, _y);
		size.Set(_width, _height);
	}
	float getMinX() const {
		return origin.x - (size.width / 2.0f);
	}
	float getMidX() const {
		return origin.x;
	}
	float getMaxX() const {
		return origin.x + (size.width / 2.0f);
	}
	float getMinY() const {
		return origin.y - (size.height / 2.0f);
	}
	float getMidY() const {
		return origin.y;
	}
	float getMaxY() const {
		return origin.y + (size.height / 2.0f);
	}
	bool containsPoint(const Vector2& point) const {
		if (getMinX() > point.x || getMaxX() < point.x) return false;
		if (getMinY() > point.y || getMaxY() < point.y) return false;
		return true;
	}
	Vector2 origin;
	Size	size;
};

#endif