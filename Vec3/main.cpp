#include <stdlib.h>
#include <iostream>


template <class X>

class Vec3
{
private:

	X x, y, z;

public:

	Vec3()
	{
		x = 0; y = 0; z = 0;
	}
	Vec3(X x, X y, X z) : x(x), y(y), z(z) {}

	Vec3(Vec3 &vec)
	{
		x = vec.getX();
		y = vec.getY();
		z = vec.getZ();
	}

	X getX() const
	{
		return x;
	}

	X getY() const
	{
		return  y;
	}

	X getZ() const
	{
		return  z;
	}

	Vec3 operator +(const Vec3 v)
	{
		Vec3 <X> vec(x + v.x, y + v.y, z + v.z);
		return vec;
	}

	Vec3 operator -(const Vec3 v)
	{
		Vec3 <X> vec(x - v.x, y - v.y, z - v.z);
		return vec;
	}

	void operator +=(const Vec3 v)
	{
		x += v.getX();
		y += v.getY();
		z += v.getZ();
	}

	void operator -=(const Vec3 v)
	{
		x -= v.getX();
		y -= v.getY();
		z -= v.getZ();
	}

	void operator =(const Vec3 v)
	{
		x = v.getX();
		y = v.getY();
		z = v.getZ();
	}

	void zero()
	{
		x = 0; y = 0; z = 0;
	}

	void normalize()
	{
		X length = sqrt(x*x + y*y + z*z);

		if (length != 0) {
			x /= length;
			y /= length;
			z /= length;
		}
	}

	X distance_to(Vec3 & vector)
	{
		X dx, dy, dz;
		dx = vector.x - x;
		dy = vector.y - y;
		dz = vector.z - z;

		return sqrt(dx*dx + dy*dy + dz*dz);
	}

};

int main() {

	Vec3<int> v(3, 3, 3), u(2, 2, 2), w;
	w = v + u;
	std::cout << "vector w(u+v): x = " << w.getX() << " y = " << w.getY() << " z = " << w.getZ() << std::endl;
	system("pause");
	return 0;
}

