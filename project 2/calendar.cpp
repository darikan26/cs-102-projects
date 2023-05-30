/**
 * CS-102 Project 02: A program that prints a calendar for a given month
and year.
 * @file calendar.cpp
 * @author(s) Derya Arikan
 *  @collaborators
 * @date Monday, January 30th
 */

# include <iostream>
# include <cmath>
using namespace std;

/**
    * Checks whether a year is a leap year or not.
    * @param y: the year that will be checked.
    * @return true if y is a leap year.
    */
bool is_leap_year(int y) {
    if ( y%4 != 0 ) {
        return false;
    }
    if ( y%100 == 0 ) {
        if ( y%400 != 0 ) {
            return false;
        }
    }
    return true;

}

/**
    * Calculates what day of the week the first day of a given month-year will fall on.
    * @param m: the month
    * @param y: the year
    * @return int starts_on which is 0 for Su, 1 for M, 2 for T, 3 for W, 4 for Th, 
    * 5 for F, 6 for Sa.
    */
int day_of_week(int m, int y) {
    // number of days since jan 1, 1900
    int num_days = 0;
    for ( int year = 1900; year < y; year++ ) { //use leap year function in here?
        if ( is_leap_year(year) == true ) {
            num_days += 366;
        } else {
            num_days += 365;
        }
    }
    // number of days since beginning of the year
    int month_lengths[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if ( is_leap_year(y) == true) {
        month_lengths[1] = 29;
    }
    for ( int month = 1; month < m; month++ ) {
        num_days += MONTH_LENGTHS[month-1];
    }
    
    // get the day of the week
    int starts_on = fmod(num_days + 1, 7);
    
    return starts_on;
}
/* 
* Special thanks to Edu and Andrew for listening to me whine about the 
* misbehavior of this function, and for their helpful suggestions in
* brainstorming possible errors.
* I figured it out in the end, but they really challenged me to
* think about why the code was doing the thing it was doing. 
*/

/**
    * Adds to an array all the days in the month.
    * @param p: pointer to dynamic array that holds the days in the month
    * @param c: capacity of the dynamic array of days within month
    * @param s: number that correlates to what day of the week the month starts on
    * @param m: the month
    * @param y: the year
    * @return nothing
    */
void add_days_to_array(int* p, int c, int s, int m, int y) {
    for ( int i = 0; i < c; i++ ) {
        p[i] = i + 1;
    }
}

/**
    * Returns how many days there should be within a given month, taking into 
    * account whether it is in a leap year or not.
    * @param m: the month
    * @param y: the year
    * @return integer representing the number of days within month
    */
int calculate_days(int m, int y) {
    if ( m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12 ) {
        return 31;
    }
    if ( m == 4 || m == 6 || m == 9 || m == 11 ) {
        return 30;
    }
    if ( m == 2 ) {
        if (is_leap_year(y)) {
            return 29;
        }
        return 28;
    }
}

/**
    * Prints the calendar for a given month and year.
    * @param m: the month
    * @param y: the year
    * @return nothing
    */
void print_calendar(int m, int y) {
    // Make title  May.1940
    string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    cout << months[m-1] << ' ' << y << '\n';

    // How many days are there in this month?
    int days = calculate_days(m, y);
    // What day of the week does this month start on?
    int starts_on = day_of_week(m, y);

    // Create the dynamic array that holds all the days within the month
    int* month_dynamic_array = new int[days];
    add_days_to_array(month_dynamic_array, days, starts_on, m, y);

    // Print the day of the week labels
    cout << "Su  M  T  W Th  F Sa\n";
    // Print the blank days of the week before the first of the month
    for ( int i = 0; i < starts_on; i++ ) {
        cout << "   ";
    }
    // Print the days from the array
    for ( int i = 0; i < days; i++ ) {
        if ( month_dynamic_array[i]/10 < 1 ) {
            cout << ' ' << month_dynamic_array[i];
        }
        if (month_dynamic_array[i]/10 >= 1 ) {
            cout << month_dynamic_array[i];
        }

        // If necessary, print a line break
        if ( (starts_on+i+1)/7 == (starts_on+i)/7 && month_dynamic_array[i] != days ) {
            // If the entry after this is on the same line, print a space
            cout << ' ';
        }
        if ( (starts_on+i+1)/7 > (starts_on+i)/7 || month_dynamic_array[i] == days ) {
            // If the entry is supposed to fall below, print line break
            cout << '\n';
        }
    }
}

// Controls the flow of the program:
int main() {
    int m, y;
    cout << "Enter the month: ";
    cin >> m;
    cout << "Enter the year: ";
    cin >> y;
    print_calendar(m, y);   
}