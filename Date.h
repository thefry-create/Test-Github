#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include <iostream>
using namespace std;

class Date
{
private:
    int month, day, year, hour; // Hour in military time
    // int calcElapsedTime(Date d); // I implemented this private member function, but you are not required to implement it

public:
    void set(int month_, int day_, int year_, int hour_);
    int getMonth() const;
    int getDay() const;
    int getYear() const;
    int getHour() const;
    void print() const;
};

#endif // DATE_H_INCLUDED
