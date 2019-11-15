#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int day_of_year(int year, int month, int day)
{
	int i, leap;
	char *cur, *max;

	if (month > 12)
		return -1;

	leap = year%4 == 0 && year %100 != 0 || year%400 == 0;

	for (cur = daytab[leap], max = cur+month; cur < max; cur++)
		day += *cur;

	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	char *cur;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	if ((!leap && yearday > 365) || (leap && yearday > 366))
	{
		*pmonth = -1;
		*pday = -1;
		return;
	}

	for (cur = &daytab[leap][1]; yearday > *cur; cur++)
		yearday -= *cur;

	*pmonth = cur - daytab[leap];
	*pday = yearday;
}

int main(int argc, char *argv) {
	int month, day;

	printf("Day of year(1998, 7, 16): %d\n\n", day_of_year(1998, 7, 16));
	printf("Day of year(1998, 1, 1): %d\n\n", day_of_year(1998, 1, 1));
	printf("Day of year(1998, 2, 1): %d\n\n", day_of_year(1998, 2, 1));

	month_day(2001, 365, &month, &day);
	printf("Monthday(2001, 365):\nMonth: %d\nDay: %d\n\n", month, day);

	month_day(2001, 366, &month, &day);
	printf("Monthday(2001, 366):\nMonth: %d\nDay: %d\n\n", month, day);


	/* Leap years */
	month_day(2004, 366, &month, &day);
	printf("Monthday(2004, 366):\nMonth: %d\nDay: %d\n\n", month, day);

	month_day(2004, 367, &month, &day);
	printf("Monthday(2004, 367):\nMonth: %d\nDay: %d\n\n", month, day);

}
