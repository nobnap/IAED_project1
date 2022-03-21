# include <stdio.h>
# include "types.h"

date current_date = {1, 1, 2022};

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