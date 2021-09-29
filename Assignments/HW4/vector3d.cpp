#include <cmath>
#include "vector3d.h"

const double PI = 3.141592653589;

Vector3d::Vector3d(float _x, float _y, float _z){
    x = _x;
    y = _y;
    z = _z;
}

Vector3d::Vector3d(Vector3d vec, float mag){
    vec.normalize();
    if(mag == 0)
		std::cout << "Vector is invalid, error 1" << std::endl; //throw "Vector is invalid";
	x = mag * vec.x;
    y = mag * vec.y;
    z = mag * vec.z;
}

// Arithmetic

Vector3d Vector3d::operator+(const Vector3d& vec) const //Addition
{
	return Vector3d(x+vec.x, y+vec.y, z+vec.z);
}

Vector3d Vector3d::operator-(const Vector3d& vec) const //Subtraction
{
	return Vector3d(x-vec.x, y-vec.y, z-vec.z);
}

// Scalar

Vector3d Vector3d::operator *(float val) const // Multiplication
{
	return Vector3d(x * val, y * val, z*val);
}

Vector3d Vector3d::operator/(float val) const // Scalar division
{
	return Vector3d(x / val, y / val, z/val);
}

// Vector Products

float Vector3d::operator*(const Vector3d& vec) const // Dot product
{
	return x * vec.x + y * vec.y + z * vec.z;
}

Vector3d Vector3d :: cross(const Vector3d& rhs) const //Cross product
{
	Vector3d temp(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
	return temp;
}

// Miscellaneous Operations

float Vector3d::rand_float()
{
	float value = rand()/float(RAND_MAX);
	return value;
}

float Vector3d :: mag() const // Vector Magnitude
{
	return sqrt(x*x + y*y + z*z);
}

Vector3d Vector3d :: unit() const // Unit Vector
{
	float m = mag();
	if(m == 0)
		throw "invalid vector";
	return Vector3d(x/m, y/m, z/m);
}

void Vector3d :: normalize() // Normalize Vector
{
	float m = mag();
	if(m == 0)
		throw "invalid vector";
	x = x/m;
	y = y/m;
	z = z/m;
}

Vector3d Vector3d :: inverse() const // Invert Vector
{
	return (*this)*-1;
}

Vector3d Vector3d :: proj(const Vector3d& vec) const // Projection Vector
{
	float m = vec.mag();
	if(m == 0)
		std::cout << "Vector is invalid, error 3" << std::endl;  // throw "invalid vector";
	return vec.unit()*(operator*(vec)/m);
}

double Vector3d :: angle(const Vector3d& vec) const // Angle Between Vectors (rads)
{
	float this_mag = mag();
	float vec_mag = vec.mag();
	if(this_mag == 0 || vec_mag == 0)
		std::cout << "Vector is invalid, error 5" << std::endl; // throw "invalid vector";
	return acos(operator*(vec)/(this_mag*vec_mag));
}

void Vector3d :: rotate(const Vector3d& vec, double angle) // Rotate Vector by Angle (rads)
{
	double rotationMatrix[4][4];

	double L = (vec.x*vec.x + vec.y * vec.y + vec.z * vec.z);
    double u2 = vec.x * vec.x;
    double v2 = vec.y * vec.y;
    double w2 = vec.z * vec.z; 
 
    rotationMatrix[0][0] = (u2 + (v2 + w2) * cos(angle)) / L;
    rotationMatrix[0][1] = (vec.x * vec.y * (1 - cos(angle)) - vec.z * sqrt(L) * sin(angle)) / L;
    rotationMatrix[0][2] = (vec.x * vec.z * (1 - cos(angle)) + vec.y * sqrt(L) * sin(angle)) / L;
    rotationMatrix[0][3] = 0.0; 
 
    rotationMatrix[1][0] = (vec.x * vec.y * (1 - cos(angle)) + vec.z * sqrt(L) * sin(angle)) / L;
    rotationMatrix[1][1] = (v2 + (u2 + w2) * cos(angle)) / L;
    rotationMatrix[1][2] = (vec.y * vec.z * (1 - cos(angle)) - vec.x * sqrt(L) * sin(angle)) / L;
    rotationMatrix[1][3] = 0.0; 
 
    rotationMatrix[2][0] = (vec.x * vec.z * (1 - cos(angle)) - vec.y * sqrt(L) * sin(angle)) / L;
    rotationMatrix[2][1] = (vec.y * vec.z * (1 - cos(angle)) + vec.x * sqrt(L) * sin(angle)) / L;
    rotationMatrix[2][2] = (w2 + (u2 + v2) * cos(angle)) / L;
    rotationMatrix[2][3] = 0.0; 
 
    rotationMatrix[3][0] = 0.0;
    rotationMatrix[3][1] = 0.0;
    rotationMatrix[3][2] = 0.0;
    rotationMatrix[3][3] = 1.0;

	double inputMatrix[4][1] = {0.0, 0.0, 0.0};
	double outputMatrix[4][1] = {0.0, 0.0, 0.0, 0.0};

	inputMatrix[0][0] = x;
    inputMatrix[1][0] = y;
    inputMatrix[2][0] = z;
    inputMatrix[3][0] = 1.0;

	for(int i = 0; i < 4; i++ ){
        for(int j = 0; j < 1; j++){
            outputMatrix[i][j] = 0;
            for(int k = 0; k < 4; k++){
                outputMatrix[i][j] += rotationMatrix[i][k] * inputMatrix[k][j];
            }
        }
    }

	x = (float)outputMatrix[0][0];
	y = (float)outputMatrix[1][0];
	z = (float)outputMatrix[2][0];

}

ostream& operator<<(ostream& out, const Vector3d& vec) // Stream Insertion and Extraction
{
	out << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
	return out;
}
