#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;

#define YEAR 405
#define MONTH 15
#define DAY 35

int date[YEAR][MONTH][DAY];
int number[YEAR * MONTH * DAY];
int sum[YEAR * MONTH * DAY];
int totDaysOfCycle;
void init()
{
	int year, month, day, daysOfMonth;
	totDaysOfCycle = 0;
	for(year = 2000; year < 2400; year ++){
		for(month = 1; month <= 12; month ++){
			switch(month) {
			case 2 :
				if((year % 400 == 0) ||
					(year % 100 != 0 && year % 4 == 0))
					daysOfMonth = 29;
				else
					daysOfMonth = 28;
				break;
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				daysOfMonth = 31;
				break;
			default:
				daysOfMonth = 30;
			}
			for(day = 1; day <= daysOfMonth; day ++){
				date[year - 2000][month][day] = ++ totDaysOfCycle;
				if(month == 2 && day == 29)	number[totDaysOfCycle] = 1;
				else	number[totDaysOfCycle] = 0;
			}
		}
	}
	sum[0] = 0;
//	printf("totDaysOfCycle = %d\n", totDaysOfCycle);
	for(int i = 1; i <= totDaysOfCycle; i ++){
		sum[i] = sum[i - 1] + number[i];
	}
}

int year[2], month[2], day[2], dateCase[2];
char strYear[2][10], strMonth[2][10], strDay[2][10];

int parseYear(char *str){
	int res = 0;
	for(int i = 0; i < 4; i ++){
		res = res * 10;
		res += str[i] - '0';
	}
	return res;
}

int parseMonth(char *str){
	int res = -1;
	if(str[0] == 'J' && str[1] == 'a' && str[2] == 'n') res = 1;
	if(str[0] == 'F' && str[1] == 'e' && str[2] == 'b') res = 2;
	if(str[0] == 'M' && str[1] == 'a' && str[2] == 'r') res = 3;
	if(str[0] == 'A' && str[1] == 'p' && str[2] == 'r') res = 4;
	if(str[0] == 'M' && str[1] == 'a' && str[2] == 'y') res = 5;
	if(str[0] == 'J' && str[1] == 'u' && str[2] == 'n') res = 6;
	if(str[0] == 'J' && str[1] == 'u' && str[2] == 'l') res = 7;
	if(str[0] == 'A' && str[1] == 'u' && str[2] == 'g') res = 8;
	if(str[0] == 'S' && str[1] == 'e' && str[2] == 'p') res = 9;
	if(str[0] == 'O' && str[1] == 'c' && str[2] == 't') res = 10;
	if(str[0] == 'N' && str[1] == 'o' && str[2] == 'v') res = 11;
	if(str[0] == 'D' && str[1] == 'e' && str[2] == 'c') res = 12;
	return res;
}

int parseDay(char *str){
	int len = 0, res = 0;
	len = strlen(str);
	str[ -- len ] = '\0';
	for(int i = 0; i < len; i ++){
		res = res * 10;
		res += str[i] - '0';
	}
	return res;
}

void parse(){
	for(int i = 0; i < 2; i ++){
		scanf("%s %s %s", strMonth[i], strDay[i], strYear[i]);
		year[i] = parseYear(strYear[i]);
		month[i] = parseMonth(strMonth[i]);
		day[i] = parseDay(strDay[i]);
		dateCase[i] = date[year[i] % 400][month[i]][day[i]];
	}
}

int getNum(int year, int dateNum){
	int res = year / 400 * sum[totDaysOfCycle];
	res += sum[dateNum];
	return res;
}

int main()
{
	init();
	int T, cas, ans[3], i;

	scanf("%d", &T);
	for(cas = 1; cas <= T; cas ++){
		parse();
		for(i = 0; i < 2; i ++)
			ans[i] = getNum(year[i], dateCase[i]);
		ans[2] = number[dateCase[0]];
		ans[2] += ans[1] - ans[0];
		printf("Case #%d: %d\n", cas, ans[2]);
	}
    return 0;
}
