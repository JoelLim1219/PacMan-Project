#include <iostream>
using namespace std;

//LEARNING C++ beginner grammars!

/* this one is to ignore the part only*/
// this is to ignore the whole line

// main() function, cout, endl
/*
int main(void)
{
	cout << "Hello world." << endl; //endl = end line and continue next line
	cout << "I am learning C++."; // \n = new line ; \\ = adds backslash ; \" = adds ""
	return 0;
}
*/

// variable types
/*
int myNum = 1500; // integer with no decimal point
double myFloat = 12.19; // floating number are numbers with decimal points
char myCharacter = 'D'; // characters only e.g. "a", "B", "c"
string myString = "Hello World"; // Whole text
bool myBoolean = true; // true or false only (Boolean)
const double pi = 3.14; // const prevents the value from changing
pi = 0 // error here due to the const preventing changing of value
*/

//input
//int age;
//int main(void)
//{
//	cout << "Age = ";
//	cin >> age;
//	cout << endl
//		 << "Your age is " << age << " years old." << endl;
//	return 0;
//}

// math
//int x = 5, y = 6, z = 7;
//int main()
//{
//	cout << "Sum = " << x + y + z << endl;
//	return 0;
//}

//naming convention
//int file_size; // Snake Case
//int FileSize; // Pascal Case
//int fileSize; // Camel Case
//int iFileSize; // Hungarian Case

// mathematical conventions
//int main()
//{
//	int x = 12;
//	//x++; // this equals x+1
//	//int y = x++; // plus on right x value is overwrite on y then only undergo increment x=13 y=12
//	int y = ++x; // plus on left side (prefix) x is increased first and the value is overwrite on "y" variable. x=13 y=13
//	int z = x + y;
//	cout << x << y << z;
//	return 0;
//}

// using standard library math functions
//int main()
//{
//	//double result = floor(1.2);
//	/*double result = ceil(1.2);*/
//	double result = pow(2,2);
//	cout << result;
//	return 0;
//}

// Area of circle calculator
//int main()
//{
//	int radius;
//	cout << "Radius = ";
//	cin >> radius;
//	const double pi = 3.142;
//	double area = pi * pow(radius, 2);
//	cout << "Area = " << area << endl;
//
//	return 0;
//}

#include <cstdlib>
#include <ctime>