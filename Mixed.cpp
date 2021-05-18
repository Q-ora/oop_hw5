#include "Mixed.h"

/** 投影片內容:
 * if the integer part is non-zero, the negative sign is entered on the integer part;
 * if the integer part is 0, the negative sign is entered on the numerator part
 * (and therefore the negative sign should never be in the denominator).
 * Valid inputs: 2 7/3 , -5 2/7 , 4 0/7 , 0 2/5 , 0 -8/3
 * Invalid inputs: 2 4/0 , -2 -4/5 , 3 -6/3 , 0 2/-3
 */

// 如果是整數,將分母直接設為1
// 有可能 0 0/x , x > 1

// constructor
Mixed::Mixed(int x) {
    integer = x;
    numerator = 0;
    denominator = 1;
}

Mixed::Mixed(int a, int b, int c) {
    if(c <= 0) {  //分母等於0 或 分母是負數
        integer = numerator = 0;
        denominator = 1;
    }
    else if(a != 0 && b < 0) {   //整數非零且分子是負數
        integer = numerator = 0;
        denominator = 1;
    }
    else {
        integer = a;
        numerator = b;
        denominator = c;
    }
}


// member function
double Mixed::Evaluate() const{
    int sign = 1;
    if(integer != 0 && isNegative())
        sign = -1;

    double ret = 0;
    ret = (double)integer + (double)(sign*numerator)/(double)denominator;
    return ret;
}

void Mixed::Simplify() {
    int sign = 1;
    if(integer != 0 && isNegative())
        sign = -1;

    //最簡分數
    int n = numerator/denominator;
    int r = numerator%denominator;
    // gcc 9.3.0負數mod後會是負數
    if(numerator < 0 && n != 0)
        r = -r;
    n *= sign;
    integer += n;
    numerator = r;

    // 現在是分子比分母小, 分母一定大於0
    // 約分分子和分母
    int numer_abs = sign*numerator;   //分子的絕對值
    for(int i=2;i<=numer_abs;i++){
        while(numerator%i == 0 && denominator%i == 0){
            numerator /= i;
            denominator /= i;
        }
    }
}

void Mixed::ToFraction() {
    int sign = 1;
    if(integer != 0 && isNegative())
        sign = -1;

    // fraction part may be improper fraction
    // integer part may be zero
    int int_to_numer = integer*denominator;
    numerator = int_to_numer + sign*numerator;
    integer = 0;

    // 約分分子和分母
    int numer_abs = sign*numerator;   //分子的絕對值
    int min = numer_abs;
    if(denominator < min) min = denominator;
    for(int i=2;i<=min;i++){
        while(numerator%i == 0 && denominator%i == 0){
            numerator /= i;
            denominator /= i;
        }
    }
}

bool Mixed::isInteger() const {
    int sign = 1;
    if(integer != 0 && isNegative())
        sign = -1;
    
    // let the number be of the form p/q
    int p,q;
    p = integer*denominator + sign*numerator;
    q = denominator;
    if(p%q == 0)
        return true;
    else
        return false;
}

bool Mixed::isNegative() const {
    // 負號只會在第一個非零項
    if(integer < 0)
        return true;
    else if(integer == 0 && numerator < 0)
        return true;
    else
        return false;
}


// operator
bool Mixed::operator<(const Mixed &m) const {
    int sign = 1, m_sign = 1;
    if(integer != 0 && isNegative())
        sign = -1;
    if(m.integer != 0 && m.isNegative())
        m_sign = -1;
    // 交叉相乘
    int left_numer = integer*denominator + sign*numerator;
    int right_numer = m.integer*m.denominator + m_sign*m.numerator;
    return left_numer*m.denominator < right_numer*denominator;
}
bool Mixed::operator>(const Mixed &m) const {
    int sign = 1, m_sign = 1;
    if(isNegative())
        sign = -1;
    if(m.isNegative())
        m_sign = -1;
    // 交叉相乘
    int left_numer = integer*denominator + sign*numerator;
    int right_numer = m.integer*m.denominator + m_sign*m.numerator;
    return left_numer*m.denominator > right_numer*denominator;
}
bool Mixed::operator<=(const Mixed &m) const {
    return !(*this > m);
}
bool Mixed::operator>=(const Mixed &m) const {
    return !(*this < m);
}
bool Mixed::operator==(const Mixed &m) const {
    return (*this <= m) && (*this >= m); 
}
bool Mixed::operator!=(const Mixed &m) const {
    return !(*this == m);
}
Mixed Mixed::operator+(const Mixed &m) const {
    // p1/q1 + p2/q2
    int p1,q1,p2,q2;
    int sign1 = 1, sign2 = 1;
    if(integer != 0 && isNegative())
        sign1 = -1;
    if(m.integer != 0 && m.isNegative())
        sign2 = -1;
    p1 = integer*denominator + sign1*numerator;
    p2 = m.integer*m.denominator + sign2*m.numerator;
    q1 = denominator;
    q2 = m.denominator;
    //通分
    p1 *= q2;
    p2 *= q1;
    q1 = q2 = q1*q2;

    Mixed ret(0, p1+p2, q1);    //目前是假分數
    ret.Simplify();
    return ret;
}
Mixed Mixed::operator-(const Mixed &m) const {
    // p1/q1 - p2/q2
    int p1,q1,p2,q2;
    int sign1 = 1, sign2 = 1;
    if(integer != 0 && isNegative())
        sign1 = -1;
    if(m.integer != 0 && m.isNegative())
        sign2 = -1;
    p1 = integer*denominator + sign1*numerator;
    p2 = m.integer*m.denominator + sign2*m.numerator;
    q1 = denominator;
    q2 = m.denominator;
    //通分
    p1 *= q2;
    p2 *= q1;
    q1 = q2 = q1*q2;

    Mixed ret(0, p1-p2, q1);    //目前是假分數
    ret.Simplify();
    return ret;
}
Mixed Mixed::operator*(const Mixed &m) const {
    // p1/q1 * p2/q2
    int p1,q1,p2,q2;
    int sign1 = 1, sign2 = 1;
    if(integer != 0 && isNegative())
        sign1 = -1;
    if(m.integer != 0 && m.isNegative())
        sign2 = -1;
    p1 = integer*denominator + sign1*numerator;
    p2 = m.integer*m.denominator + sign2*m.numerator;
    q1 = denominator;
    q2 = m.denominator;

    Mixed ret(0, p1*p2, q1*q2);
    ret.Simplify();
    return ret;
}
Mixed Mixed::operator/(const Mixed &m) const {
    if(m.integer == 0 && m.numerator == 0){ //return 0
        Mixed ret(0);
        return ret;
    }

    // (p1/q1) / (p2/q2) = (p1*q2) / (p2*q1)
    int p1,q1,p2,q2;
    int sign1 = 1, sign2 = 1;
    if(integer != 0 && isNegative())
        sign1 = -1;
    if(m.integer != 0 && m.isNegative())
        sign2 = -1;
    p1 = integer*denominator + sign1*numerator;
    p2 = m.integer*m.denominator + sign2*m.numerator;
    q1 = denominator;
    q2 = m.denominator;

    //確保分母是正數
    int inverse = 1;
    if(p2*q1 < 0)
        inverse = -1;
    Mixed ret(0, inverse*p1*q2, inverse*p2*q1);
    ret.Simplify();
    return ret;
}
Mixed & Mixed::operator++() {   // pre-increment
    //可能會變號
    ToFraction();
    numerator += denominator;
    Simplify();
    return *this;
}
const Mixed Mixed::operator++(int) {    // post-increment
    //可能會變號
    Mixed m(integer, numerator, denominator);
    ToFraction(); //化成假分數(去掉整數部分)
    numerator += denominator;
    Simplify();
    return m;
}
Mixed & Mixed::operator--() {   // pre-decrement
    //可能會變號
    ToFraction();
    numerator -= denominator;
    Simplify();
    return *this;
}
const Mixed Mixed::operator--(int) {    // post-decrement
    //可能會變號
    Mixed m(integer, numerator, denominator);
    ToFraction(); //化成假分數(去掉整數部分)
    numerator -= denominator;
    Simplify();
    return m;
}
Mixed & Mixed::operator+=(const Mixed &m) {
    *this = *this + m;
    return *this;
}
Mixed & Mixed::operator-=(const Mixed &m) {
    *this = *this - m;
    return *this;
}
Mixed & Mixed::operator*=(const Mixed &m) {
    *this = *this * m;
    return *this;
}
Mixed & Mixed::operator/=(const Mixed &m) {
    *this = *this / m;
    return *this;
}
Mixed::operator double() const {
    return Evaluate();
}


// friend function
istream & operator>>(istream &ist, Mixed &m) {
    char ch;
    int a, b, c;
    ist >> a >> b >> ch >> c;

    if(c <= 0) {  //分母等於0 或 分母是負數
        m.integer = m.numerator = 0;
        m.denominator = 1;
    }
    else if(a != 0 && b < 0) {   //整數非零且分子是負數
        m.integer = m.numerator = 0;
        m.denominator = 1;
    }
    else {
        m.integer = a;
        m.numerator = b;
        m.denominator = c;
    }

    return ist;
}
ostream & operator<<(ostream &ost, const Mixed &m) {
    if(m.integer == 0 && m.numerator == 0)  // 0
        ost << m.integer;
    //非零
    else if(m.integer == 0) //只有小數部分(不為零)
        ost << m.numerator << "/" << m.denominator;
    else if(m.numerator == 0)   //只有整數部分(不為零)
        ost << m.integer;
    else
        ost << m.integer << " " << m.numerator << "/" << m.denominator;

    return ost;
}