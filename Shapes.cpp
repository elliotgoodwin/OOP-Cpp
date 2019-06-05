// Shapes
// An example of a polymorphic base class
// OOP - Assignment 8
// Elliot Goodwin
// 28/03/19


// includes
#include <iostream> // cout
#include <cmath>    // pow

// declare namespace
using namespace std;

// declare global constants
const double PI = 3.1415;

// Define a virtual base class "Shape"
class Shape {
public:
	// Define virtual destructor to enable use of base class pointers
	virtual ~Shape() {};

	virtual double Perimeter() = 0; // Function to return perimeter of a shape
	virtual double Area() = 0;      // Function to return area of a shape
	virtual double Volume() = 0;    // Function to return volume of a shape
	virtual void Show() = 0;        // Function to print the shape's properties to the console

};


// Define a derived class "TwoD"
class TwoD : public Shape {
public:
	TwoD() : Shape() {};
	virtual ~TwoD() {};

	virtual double Perimeter() = 0;
	virtual double Area() = 0;
	virtual double Volume() { return 0; }  // Consider volume as a property of a 3D shape
	virtual void Show() = 0;
};

class Rectangle : public TwoD {
protected:
	double width;
	double length;

public:
	Rectangle() : width(0), length(0) {};
	Rectangle(double a, double b) : width(a), length(b) {};
	virtual ~Rectangle() {};

	double Perimeter() { return 2 * (width + length); }
	double Area() { return width*length; }
	void Show() {
		cout << "Rectangle:" << endl;
		cout << "Length = " << Rectangle::length << ", width = " << Rectangle::width << endl;
		cout << "Perimeter = " << Rectangle::Perimeter() << endl;
		cout << "Area = " << width*length << endl;
	}
};

class Square : public Rectangle {
public:
	Square() : Rectangle() {};
	Square(double a) : Rectangle(a, a) {};
	~Square() {};

	double Perimeter() { return Rectangle::Perimeter(); }
	double Area() { return Rectangle::Area(); }
	void Show() {
		cout << "Sqaure:" << endl;
		cout << "Length = " << Rectangle::length << endl;
		cout << "Perimeter = " << Rectangle::Perimeter() << endl;
		cout << "Area = " << Square::Area() << endl;
	}
};

class Ellipse : public TwoD {
protected:
	double major;
	double minor;

public:
	Ellipse() : major(0), minor(0) {};
	Ellipse(double a, double b) : major(a), minor(b) {};
	virtual ~Ellipse() {};

	double Perimeter() { return PI*(major + minor)*(1 + pow((major + minor), 2) * pow((major - minor), -2)); }
	double Area() { return PI*major*minor; }
	void Show() {
		cout << "Ellipse:" << endl;
		cout << "Major axis = " << Ellipse::major << ", minor axis = " << Ellipse::minor << endl;
		cout << "Perimeter = " << Ellipse::Perimeter() << endl;
		cout << "Area = " << PI*major*minor << endl;
	}
};

class Circle : public Ellipse {
public:
	Circle() : Ellipse() {};
	Circle(double r) : Ellipse(r, r) {};
	~Circle() {};

	double Perimeter() { return Ellipse::Perimeter(); }
	double Area() { return Ellipse::Area(); }
	void Show() {
		cout << "Circle:" << endl;
		cout << "Radius = " << Ellipse::major << endl;
		cout << "Perimeter = " << Ellipse::Perimeter() << endl;
		cout << "Area = " << Circle::Area() << endl;
	}
};



class ThreeD : public Shape {
public:
	ThreeD() : Shape() {};
	virtual ~ThreeD() {};

	virtual double Perimeter() { return 0; }  // Consider perimeter as a property of a 2D shape
	virtual double Area() = 0;
	virtual double Volume() = 0;
	virtual void Show() = 0;
};

class Cuboid : public ThreeD {
protected:
	double length, width, depth;

public:
	Cuboid() : length(0), width(0), depth(0) {};
	Cuboid(double a, double b, double c) : length(a), width(b), depth(c) {};
	virtual ~Cuboid() {};

	double Area() { return (2 * length*width + 2 * length*depth + 2 * width*depth); }
	double Volume() { return length*width*depth; }
	void Show() {
		cout << "Cuboid:" << endl;
		cout << "Length = " << Cuboid::length << ", width = " << Cuboid::width << ", depth = " << Cuboid::depth << endl;
		cout << "Area = " << Cuboid::Area() << endl;
		cout << "Volume = " << Cuboid::Volume() << endl;
	}
};

class Cube : public Cuboid {
public:
	Cube() : Cuboid() {};
	Cube(int a) : Cuboid(a, a, a) {};
	~Cube() {};

	double Area() { return Cuboid::Area(); }
	double Volume() { return Cuboid::Volume(); }
	void Show() {
		cout << "Cube:" << endl;
		cout << "Length = " << Cuboid::length << ", depth = " << Cuboid::depth << endl;
		cout << "Area = " << Cube::Area() << endl;
		cout << "Volume = " << Cube::Volume() << endl;
	}
};

class Ellipsoid : public ThreeD {
protected:
	double axis_1, axis_2, axis_3;

public:
	Ellipsoid() : axis_1(0), axis_2(0), axis_3(0) {};
	Ellipsoid(double a, double b, double c) : axis_1(a), axis_2(b), axis_3(c) {};
	virtual ~Ellipsoid() {};

	double Area() {
		double area = pow(axis_1*axis_2, 1.6) + pow(axis_1*axis_3, 1.6) + pow(axis_2*axis_3, 1.6);
		area = 4 * PI*pow(area / 3, 1 / (1.6));
		return area;
	}
	double Volume() { return 4 / 3 * PI*axis_1*axis_2*axis_3; }
	void Show() {
		cout << "Ellipsoid:" << endl;
		cout << "length_x = " << Ellipsoid::axis_1 << ", length_y = " << Ellipsoid::axis_2 << ", length_z = " << Ellipsoid::axis_3 << endl;
		cout << "Area = " << Ellipsoid::Area() << endl;
		cout << "Volume = " << Ellipsoid::Volume() << endl;
	}

};

class Sphere : public Ellipsoid {
public:
	Sphere() : Ellipsoid() {};
	Sphere(double r) : Ellipsoid(r, r, r) {};
	~Sphere() {};

	double Area() { return Ellipsoid::Area(); }
	double Volume() { return Ellipsoid::Volume(); }
	void Show() {
		cout << "Sphere:" << endl;
		cout << "Radius = " << Ellipsoid::axis_1 << endl;
		cout << "Area = " << Sphere::Area() << endl;
		cout << "Volume = " << Sphere::Volume() << endl << endl;
	}
};


class Prism : public TwoD {
private:
	double depth;
	TwoD *twoD_ptr;
public:
	Prism() {};
	Prism(TwoD *ptr, double b) : twoD_ptr(ptr), depth(b) {};
	~Prism() {};

	double Perimeter() { return 0; }
	double Area() { return 2 * twoD_ptr->Area() + twoD_ptr->Perimeter()*depth; }
	double Volume() { return (twoD_ptr->Area()*depth); }
	void Show() {
		cout << "Using the 2D shape "; twoD_ptr->Show();
		cout << "to construct a prism with depth = " << Prism::depth << endl;
		cout << "\nPrism:" << endl;
		cout << "Area = " << Prism::Area() << endl;
		cout << "Volume = " << Prism::Volume() << endl << endl;
	}
};





int main() {

	// Create array of base class pointers (one for each shape)
	Shape **shape_array = new Shape*[8];

	// Fill array
	shape_array[0] = new Rectangle(3, 4);
	shape_array[1] = new Square(2);
	shape_array[2] = new Ellipse(3, 4);
	shape_array[3] = new Circle(3);
	shape_array[4] = new Cuboid(1, 2, 3);
	shape_array[5] = new Cube(2);
	shape_array[6] = new Ellipsoid(3, 6, 4);
	shape_array[7] = new Sphere(7);

	for (int i = 0; i < 7; i++) {
		// Show contents of each vector
		shape_array[i]->Show(); cout << endl;
		// Free up memory
		delete shape_array[i];
	}
	delete[] shape_array; // delete the array

	// Prism
	// Use a pointer to a 2D shape as input to Prism paraterised constructor
	double depth = 4.2;
	Prism prism(new Rectangle(1, 2), depth);
	// Show contents of prism
	prism.Show();

	return 0;
}
