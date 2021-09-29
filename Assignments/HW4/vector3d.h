#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//class for 3 dimentional vectors
//make sure u add checks for null vector and other corner cases throw (char*) exceptions if required

class Vector3d
{
public:
	float x, y, z;
	Vector3d(float = 0, float = 0, float = 0); //Contructor for vector class given (x, y, z)(null vector by default)

	//Constructor to initialize a vector with a vector and magnitude (the new vector will share the direction of given vector)
	Vector3d(Vector3d, float);

    // Arithmetic
	Vector3d operator+(const Vector3d&) const; // Addition
    Vector3d operator-(const Vector3d&) const; // Subtraction

	// Scalar
	Vector3d operator*(float) const; //Multiplication
	Vector3d operator/(float) const; //Scalar division

	// Vector Products
	float operator*(const Vector3d&) const; // Dot product
	Vector3d cross(const Vector3d&) const; // Cross product

	// Miscellaneous
	float mag() const; // Vector Magnitude
	Vector3d unit() const; // Unit Vector
	void normalize(); // Normalize Vector
	Vector3d inverse() const; // Inverted Vector
	Vector3d proj(const Vector3d&) const; // Projection Vector
	double angle(const Vector3d&) const; // Angle Between Vectors (rads)
	void rotate(const Vector3d&, double); // Rotate Vector by Angle (rads)
	friend ostream& operator<<(ostream&, const Vector3d&); // Stream Insertion and Extraction

    // Random Functions
    float rand_float();
};