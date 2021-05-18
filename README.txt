姓名: 謝宗哲
學號: 408210005
email: steven900412@gmail.com
完成項目:
    1. 繳交main.cpp, Mixed.h, Mixed.cpp, makefile, README.txt, main(可執行檔)
    2. 新增以下兩個member function方便判斷Mixed的狀態:
        bool isInteger() const;   // check if the number has no fraction part
        bool isNegative() const;  // check if the number is smaller than 0
    3. 在 Evaluate() 和 其他邏輯運算及+-*/ 後面添加const修飾
    4. 大部分函式都有在結束時將Mixed化成simplified form (除了constructor和operator>>會保持數字原本輸入的模樣)
    5. 只有include <iostream>, 沒有include其他library
Bonus:
    1. 實作以下五個operator overloading function:
        Mixed & operator+=(const Mixed &);
        Mixed & operator-=(const Mixed &);
        Mixed & operator*=(const Mixed &);
        Mixed & operator/=(const Mixed &);
        explicit operator double() const;   //如果沒有用explicit conversion, +-*/會和double的+-*/搞混
    