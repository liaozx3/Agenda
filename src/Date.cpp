#include "Date.hpp"
#include <string>
#include <sstream>
using std::string;
using std::stringstream;
int d[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int change1(string s) {
    stringstream ss(s);
    int temp;
    ss >> temp;
    return temp;
}
string change2(int i) {
    stringstream ss;
    ss << i;
    string s = ss.str();
    return s;
}
Date::Date():m_year(0), m_month(0), m_day(0), m_hour(0), m_minute(0) {}
Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute)
    :m_year(t_year), m_month(t_month), m_day(t_day), m_hour(t_hour), m_minute(t_minute) {}
Date::Date(string t_dateString) {  //  0000-00-00/00:00
    bool flag = 0;
    if (t_dateString.size() != 16) {
        flag = 1;
    }
    if (t_dateString[4] != '-' || t_dateString[7] != '-')
        flag = 1;
    if (t_dateString[10] != '/' || t_dateString[13] != ':')
        flag = 1;
    for (int i = 0; i < 4; i++) {
        if (t_dateString[i] < '0' || t_dateString[i] > '9') {
            flag = 1;
        }
    }
    for (int i = 5; i < 7; i++) {
        if (t_dateString[i] < '0' || t_dateString[i] > '9') {
            flag = 1;
        }
    }
    for (int i = 8; i < 10; i++) {
        if (t_dateString[i] < '0' || t_dateString[i] > '9') {
            flag = 1;
        }
    }
    for (int i = 11; i < 13; i++) {
        if (t_dateString[i] < '0' || t_dateString[i] > '9') {
            flag = 1;
        }
    }
    for (int i = 14; i < 16; i++) {
        if (t_dateString[i] < '0' || t_dateString[i] > '9') {
            flag = 1;
        }
    }
    if(flag) {
        m_year = 0;
        m_month = 0;
        m_day = 0;
        m_hour = 0;
        m_minute = 0;
    } else {
        string y, m, d, h, mi;
        y += t_dateString[0];
        y += t_dateString[1];
        y += t_dateString[2];
        y += t_dateString[3];
        m_year = change1(y);
        m += t_dateString[5];
        m += t_dateString[6];
        m_month = change1(m);
        d += t_dateString[8];
        d += t_dateString[9];
        m_day = change1(d);
        h += t_dateString[11];
        h += t_dateString[12];
        m_hour = change1(h);
        mi += t_dateString[14];
        mi += t_dateString[15];
        m_minute = change1(mi);
    }
}

int Date::getYear() const {
    return m_year;
}
void Date::setYear(const int t_year) {
    m_year = t_year;
}
int Date::getMonth() const {
    return m_month;
}
void Date::setMonth(const int t_month) {
    m_month = t_month;
}
int Date::getDay() const {
    return m_day;
}
void Date::setDay(const int t_day) {
    m_day = t_day;
}
int Date::getHour() const {
    return m_hour;
}
void Date::setHour(const int t_hour) {
    m_hour = t_hour;
}
int Date::getMinute() const {
    return m_minute;
}
void Date::setMinute(const int t_minute) {
    m_minute = t_minute;
}
bool isRUN(int a) {
    return ((a % 4 == 0 && a %100 != 0) || a%400 == 0);
}
bool Date::isValid(const Date t_date) {
    if (t_date.getYear() < 1000 || t_date.getYear() > 9999)
        return false;
    if (t_date.getMonth() < 1 || t_date.getMonth() > 12)
        return false;
    if (t_date.getMonth() == 2) {
        if (isRUN(t_date.getYear())) {
            if (t_date.getDay() < 1 || t_date.getDay() > 29) {
                return false;
            }
        } else {
            if (t_date.getDay() < 1 || t_date.getDay() > 28) {
                return false;
            }
        }
    } else {
        if (t_date.getDay() < 1 || t_date.getDay() > d[t_date.getMonth()-1])
            return false;
    }
    if (t_date.getHour() < 0 || t_date.getHour() > 23)
        return false;
    if (t_date.getMinute() < 0 || t_date.getMinute() > 59)
        return false;
    return true;
}  //  0000-00-00/00:00
Date Date::stringToDate(const std::string t_dateString) {
    Date s(t_dateString);
    return s;
}
std::string Date::dateToString(Date t_date) {
    if (!t_date.isValid(t_date)) {
        return "0000-00-00/00:00";
    }
    string s;
    s += change2(t_date.getYear());
    s += '-';
    if (t_date.getMonth() < 10)
        s += '0';
    s += change2(t_date.getMonth());
    s += '-';
    if (t_date.getDay() < 10)
        s += '0';
    s += change2(t_date.getDay());
    s += '/';
    if (t_date.getHour() < 10)
        s += '0';
    s += change2(t_date.getHour());
    s += ':';
    if (t_date.getMinute() < 10)
        s += '0';
    s += change2(t_date.getMinute());
    return s;
}
Date& Date::operator=(const Date &t_date) {
    if (*this == t_date)
        return *this;
    m_year = t_date.getYear();
    m_month = t_date.getMonth();
    m_day = t_date.getDay();
    m_hour = t_date.getHour();
    m_minute = t_date.getMinute();
    return *this;
}
bool Date::operator==(const Date &t_date) const {
    if (m_year == t_date.getYear()) {
        if (m_month == t_date.getMonth()) {
            if (m_day == t_date.getDay()) {
                if (m_hour == t_date.getHour()) {
                    if (m_minute == t_date.getMinute()) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool Date::operator>(const Date &t_date) const {
    if (m_year > t_date.getYear()) {
        return true;
    } else if (m_year == t_date.getYear()) {
        if (m_month > t_date.getMonth()) {
            return true;
        } else if (m_month == t_date.getMonth()) {
            if (m_day > t_date.getDay()) {
                return true;
            } else if (m_day == t_date.getDay()) {
                if (m_hour > t_date.getHour()) {
                    return true;
                } else if (m_hour == t_date.getHour()) {
                    if (m_minute > t_date.getMinute()) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}
bool Date::operator<(const Date &t_date) const {
    if (*this == t_date || *this > t_date) {
        return false;
    } else {
        return true;
    }
}
bool Date::operator>=(const Date &t_date) const {
    return (*this == t_date || *this > t_date);
}
bool Date::operator<=(const Date &t_date) const {
    return (*this == t_date || *this < t_date);
}
