# include <stdio.h>

# define MAX_COUNTRY 30
# define MAX_CITY 50

typedef struct {
	int year, month, day;
} date;

typedef struct {
	int hour, min;
} time;

typedef struct {
	char ID[4];
	char country[MAX_COUNTRY];
	char city[MAX_CITY];
} airport;

typedef struct {
	char code[7];
	char dep_ID[4];
	char ar_ID[4];
	date dep_date;
	time dep_time;
	int passengers;
} flight;

void add_airport() {
	airport input;
	scanf("%s %s %s", input.ID, input.country, input.city);
}

void input_reader() {
	char command;
	switch (command = getchar()) {
		case 'q':
			break;
		case 'a':
			add_airport();
		/*case 'l':
			list_airport();
		case 'v':
			flights();
		case 'p':
			flight_departures();
		case 'c':
			flight_arrivals();
		case 't':
			date_forward();*/
	}
}

int main() {
	input_reader();
	return 0;
}