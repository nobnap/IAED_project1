# include "manager.h"

/* definition of global variables */
date current_date = {1, 1, 2022};

flight flight_list[MAX_FLIGHTS];
int num_flights = 0;

airport airports[MAX_AIRPORT];
int num_airport = 0;


int input_reader() {
	char command;
	while (1) {
		command = getchar();
		switch (command) {
			case 'q':
				return EXIT_SUCCESS;
			case 'a':
				add_airport();
				break;
			case 'l':
				list_airport();
				break;
			case 'v':
				flights();
				break;
			case 'p':
				departures();
				break;
			case 'c':
				arrivals();
				break;
			case 't':
				date_forward();
				break;
		getchar();
		}
	}
}

int main() {
	input_reader();
	return 0;
}