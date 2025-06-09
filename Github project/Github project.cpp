// Github project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
struct stDate {

    short Day;
    short Month;
    short Year;

};
bool IsLeapYear(short Year) {

    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}
short NumberOfDaysInAMonth(short Month, short Year) {

    if (Month < 1 || Month > 12) {

        return 0;
    }
    short Days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : Days[Month - 1];
}
bool IsLastDayInMonth(stDate Date) {

    return (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year));
}
bool IsLastMonthInYear(short Month) {

    return (Month == 12);
}
stDate IncreaseDateByOneDay(stDate Date) {

    if (IsLastDayInMonth(Date)) {
        if (IsLastMonthInYear(Date.Month)) {
            Date.Day = 1;
            Date.Month = 1;
            Date.Year++;
        }
        else {
            Date.Day = 1;
            Date.Month++;
        }
    }
    else {
        Date.Day++;
    }

    return Date;
}
short GetDayOrderInWeek(short Day, short Month, short Year) {

    short a = 0, y = 0, m = 0;

    a = (14 - Month) / 12;
    y = Year - a;
    m = Month + (12 * a) - 2;

    // Gregorian:
    //0:sun, 1:Mon, 2:Tue...etc
    return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}
short GetDayOrderInWeek(stDate Date) {

    return GetDayOrderInWeek(Date.Day, Date.Month, Date.Year);
}
bool IsDate1Before(stDate Date1, stDate Date2) {

    return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);

}
bool IsWeekEnd(stDate Date) {

    short DayOrderInWeek = GetDayOrderInWeek(Date);

    return (DayOrderInWeek == 5 || DayOrderInWeek == 6);
}
short ReadDay() {
    short Day = 0;
    cout << "Please enter Day ? ";
    cin >> Day;

    return Day;
}
short ReadMonth() {
    short Month = 0;
    cout << "Please enter Month ? ";
    cin >> Month;

    return Month;
}
short ReadYear() {
    short Year = 0;
    cout << "Please enter Year ? ";
    cin >> Year;

    return Year;
}
stDate ReadFullDate() {

    stDate Date;

    Date.Day = ReadDay();
    Date.Month = ReadMonth();
    Date.Year = ReadYear();

    return Date;
}
string GetDayName(stDate Date) {

    short DayOrderInWeek = GetDayOrderInWeek(Date);
    string DayName[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

    return DayName[DayOrderInWeek];
}
short CalculateActualVacationDays(stDate Date1, stDate Date2) {

    short ActualVacationDays = 0;

    while (IsDate1Before(Date1, Date2)) {


        if (!IsWeekEnd(Date1))
            ActualVacationDays++;

        Date1 = IncreaseDateByOneDay(Date1);

    }
    //Adding last day
    if (!IsWeekEnd(Date2)) {

        ActualVacationDays++;
    }

    return ActualVacationDays;
}
int main() {

    stDate Date1, Date2;

    cout << "Vacation Starts : \n\n";
    Date1 = ReadFullDate();
    cout << "\nVacation Ends : \n\n";
    Date2 = ReadFullDate();

    cout << "\n\nVacation From : " << GetDayName(Date1) << " , " << Date1.Day
        << "/" << Date1.Month << "/" << Date1.Year << "\n";
    cout << "Vacation To : " << GetDayName(Date2) << " , " << Date2.Day
        << "/" << Date2.Month << "/" << Date2.Year << "\n";

    cout << "\n\nActual Vacation Days is : " << CalculateActualVacationDays(Date1, Date2) << "\n\n";

    system("Pause > 0");
    return 0;
}