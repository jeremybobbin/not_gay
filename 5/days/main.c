#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 30, 30, 31, 30, 31},
};

int day_of_year(int year, int month, int day)
{
	int i, leap;

	if (month > 12)
		return -1;

	leap = year%4 == 0 && year %100 != 0 || year%400 == 0;
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	if ((!leap && yearday > 365) || (leap && yearday > 364))
	{
		*pmonth = -1;
		*pday = -1;
		return;
	}

	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];

	*pmonth = i;
	*pday = yearday;
}

int main(int argc, char *argv) {
	int month, day;
	month_day(2001, 365, &month, &day);
	printf("Monthday(2001, 365):\nMonth: %d\nDay: %d\n\n", month, day);

	month_day(2001, 366, &month, &day);
	printf("Monthday(2001, 366):\nMonth: %d\nDay: %d\n\n", month, day);


	/* Leap years */
	month_day(2000, 364, &month, &day);
	printf("Monthday(2000, 364):\nMonth: %d\nDay: %d\n\n", month, day);

	month_day(2000, 366, &month, &day);
	printf("Monthday(2000, 366):\nMonth: %d\nDay: %d\n\n", month, day);
}
