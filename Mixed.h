#ifndef _MIXED_H_
#define _MIXED_H_

#include <iostream>
using namespace std;
class Mixed {
private:
    int integer;
    int numerator;
    int denominator;
public:
    // constructor
    Mixed(int = 0); // set object to the value of parameter, and has no fraction part
    // conversion constructor(one argument)
    Mixed(int, int, int); // set object follow the integer, numerator, and denominator order
    /* more detail about the setting rules, please check Hw5 pdf page 3 */

    // member function
    double Evaluate() const; // return the decimal equivalent of the Mixed number
    void Simplify(); // simplify the Mixed number representation to lowest terms.
    // (This means that the fraction part should be reduced to lowest terms, and the fraction part should not be an improper fraction)
    void ToFraction(); // convert the mixed number to into fraction form.
    // (This means integer part is 0, and the fraction portion may be an improper fraction)
    /* more detail about the member function description, please check Hw5 pdf page 5 - 6 */

    //---------------------------自訂函數---------------------------------
    bool isInteger() const;   // check if the number has no fraction part
    bool isNegative() const;  // check if the number is smaller than 0
    //-------------------------------------------------------------------

    // operator overloading
    bool operator<(const Mixed &) const;
    bool operator>(const Mixed &) const;
    bool operator<=(const Mixed &) const;
    bool operator>=(const Mixed &) const;
    bool operator==(const Mixed &) const;
    bool operator!=(const Mixed &) const;
    Mixed operator+(const Mixed &) const;
    Mixed operator-(const Mixed &) const;
    Mixed operator*(const Mixed &) const;
    Mixed operator/(const Mixed &) const;
    Mixed & operator++();           // pre-increment
    const Mixed operator++(int);    // post-increment
    Mixed & operator--();           // pre-decrement
    const Mixed operator--(int);    // post-decrement
    
    // -------------------------以下為新增的operator overloading function-------------------------
    Mixed & operator+=(const Mixed &);
    Mixed & operator-=(const Mixed &);
    Mixed & operator*=(const Mixed &);
    Mixed & operator/=(const Mixed &);
    explicit operator double() const;   //如果沒有用explicit conversion, +-*/會和double的+-*/搞混
    // ------------------------------------------------------------------------------------------

    // friend function
    friend istream & operator>>(istream &, Mixed &); // The input format for a Mixed number object will be: integer numerator/denominator
    // (notice that there has a '/'), all parts are all of type int.
    friend ostream & operator<<(ostream &, const Mixed &); // This should output the Mixed number in the same format as above
    /* more detail about the operator>> and operator<<, please check Hw5 pdf page 7 - 9 */

    /* All the operator overloading functions should work as we usually think; for instance, A++ means A = A + 1 , the denominator part should not be 0 when doing division*/
};

#endif