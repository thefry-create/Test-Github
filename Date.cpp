// Implements the Date class with basic getters, setters, and a formatted print function
#include "Date.h"
#include <iostream>
#include <string>
using namespace std;

// Sets the values for the date and time
void Date::set(int month_, int day_, int year_, int hour_) {
    month = month_;
    day = day_;
    year = year_;
    hour = hour_;
}

// Getters for the date and time fields
int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }
int Date::getYear() const { return year; }
int Date::getHour() const { return hour; }

// Prints the date in a readable format: Month Day, Year, Hour:00
void Date::print() const {
    string months[] = {"January", "February", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December"};
    cout << months[month - 1] << " " << day << ", " << year << ", " << hour << ":00";
}
