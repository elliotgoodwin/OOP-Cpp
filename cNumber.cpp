// cNumber
// A program that defines a class that stores and performs useful operations to complex numbers
// Elliot Goodwin
// OOP Assignment 5
// 04/03/18

// includes
#include<string>
#include<iostream>
#include<cmath>
#include<sstream>

// declare namespace
using namespace std;


// -------- Class definition ----------------------------------------------------------
// ------------------------------------------------------------------------------------
// complexNumber
class cNumber {
    
    // Allow our overloaded operators {<<, >>} functions to be a friend (access private members) of cNumber class
    friend ostream & operator << (ostream &os, const cNumber &z);
    friend istream & operator >> (istream &is, cNumber &z);
    
// private (hidden from main program)
private:
    
    // declare variables
    double Re; // Real part of complex number
    double Im; // Imaginary part of complex number
    
// public (accessible from main program)
public:
    
    // constructors
    // default constructor
    cNumber(){Re = Im = 0;}
    // parameterised constructor
    cNumber(const double r, const double i){ Re = r; Im = i; }
    // destructor
    ~cNumber(){}; //cout << "Destroying complex number" << endl;}
    
    // functions for setting cNumber parameters
    void setRe(const double newRe) { Re = newRe; }
    void setIm(const double newIm) { Im = newIm; }
    void set(const double newRe, const double newIm) { Re = newRe; Im = newIm; }
    // functions for returning cNumber parameters
    double getRe() const { return Re; }
    double getIm() const { return Im; }
    // functions to get modulus, arguement and complex conjugate
    double  getMod()  const { const double mod = pow((pow(Re, 2)*pow(Im, 2)), 0.5); return mod; }  // get modulus of cNumber
    double  getArg()  const { const double arg = (Im / Re); return arg;  }                         // get argument of cNumber
    cNumber getConj() const { cNumber(Re, Im); return cNumber(Re, -Im); }                          // get conjugate of cNumber
    
    void printcNumber(); // prototype member function to print cNumber
    
    // addition: overload + operator for addition z1 + z2
    cNumber operator+(const cNumber &z) const { cNumber a(Re+z.getRe(), Im+z.getIm()); return a; }
    // subtraction: overload - operator for subtraction z1 - z2
    cNumber operator-(const cNumber &z) const { cNumber a(Re-z.getRe(), Im-z.getIm()); return a; }
    // multiply: overload * operator for multiplication z1*z2
    cNumber operator*(const cNumber &z) const { cNumber a(Re*z.getRe() + Im*z.getIm(), Re*z.getIm() + Im*z.getRe()); return a; }
    // protoype divide: overload / operator for division z1/z2
    cNumber operator/(const cNumber &z) const;
    
};

// ----------- Function definitions ---------------------------------------------------
// ------------------------------------------------------------------------------------
// printcNumber
// a function that prints the contents of a cNumber
void cNumber::printcNumber() { cout << getRe() << " + " << getIm() << "i" << endl; }

// bad_istream
// a function that checks for bad istream
bool bad_istream(istream &is){
    if(is.fail()) {
        is.clear();
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error. Bad input.\n" << endl;
        return true;
    }
    else { return false; }
}

// Non-member function to overload << operator for complex numbers
ostream & operator << (ostream &os, const cNumber &z) {
    if(z.getIm() < 0) { os << z.getRe() << " - " << -1*z.getIm() << "i"; }
    else { os << z.getRe() << " + " << z.getIm() << "i"; }
    return os;
}


// Non-member function to overload >> operator for complex numbers
istream & operator >> (istream &is, cNumber &z) {
    
    // declare variables
    char sign;
    string line;
    istringstream ss;
    
    // put contents of input stream in a string
    getline(is, line);
    
    // find position of i in string
    size_t i_pos = line.find_first_of("i");
    // erase i from string
    line.erase(i_pos);
    
    // put contents of string in string stream
    ss.str(line);
    
    // read in the real part of cNumber from string stream
    do { ss >> z.Re; } while (bad_istream(ss)); // check for non-double input
    
    // read in sign of cNumber from string stream
    ss >> sign;
    if(sign != '+' && sign != '-') { cout << "Error. Bad sign. Setting sign to +" << endl; sign = '+'; }

    // read in imaginary part of cNumber from string stream
    do { ss >> z.Im; } while (bad_istream(ss)); // check for non-double input
    if (sign == '-') { z.setIm( -z.getIm() ); } // if sign read in as '-' set imaginary part as negative
    
    return is;
}

// Member function to overload / operator for division of complex numbers z1/z2
cNumber cNumber::operator /(const cNumber &z) const {
    // perform division operation
    cNumber num(Re*z.getRe() + Im*z.getIm(), -Re*z.getIm() + Im*z.getRe());
    double den(z.getRe()*z.getRe() + z.getIm()*z.getIm());
    // construct new cNumebr
    cNumber y{num.getRe()/den, num.getIm()/den};
    return y;
}




// ----------- Main program  ----------------------------------------------------------
// ------------------------------------------------------------------------------------
int main()
{
    cout.precision(3);
    
    // Create two complex numbers
    cNumber a(3, 4), b(1, -2);
    
    // Get value of a
    cout << "Print value of a:" << endl;
    // Example of printing a using overloaded << operator
    cout << a << endl;
    
    // Example of printing using a member function
    cout << "\nPrint value of a using a member function:" << endl;
    cout << "a = "; a.printcNumber();
    
    // Get real and imaginary components
    cout << "\nGet Re and Im components of a:" << endl;
    cout << "Re(a) = " << a.getRe() << endl;
    cout << "Im(a) = " << a.getIm() << endl;
    
    // Set the real and imaginary components
    a.setRe(9); a.setIm(-14);
    cout << "New values of a = " << a << endl;
    // Re-set a to inital values
    a.set(3, 4);
    
    // Get modulus and argument
    cout << "\nGet modulus and argument of a:" << endl;
    cout << "|a| = " << a.getMod() << endl;
    cout << "Arg(a) = " << a.getArg() << endl;
    
    // Get conjugate
    cout << "\nGet the complex conjugate of a:" << endl;
    cout << "a* = " << a.getConj() << endl;
    
    // Get sum, difference, product and quotient of a and b
    cout << "\nExamples using overloaded arithmetic operators:" << endl;
    cout << "a + b = " << (a+b) << endl;
    cout << "a * b = " << (a*b) << endl;
    cout << "a - b = " << (a-b) << endl;
    cout << "a / b = " << (a/b) << endl;
    cout << endl;
    
    // Example of user input complex number
    cNumber z;
    // Prompt user to enter complex number
    cout << "Enter a complex number:" << endl;
    cin >> z;
    cout << "\nYou entered the complex number " << z << endl;
    
    return 0;
}
