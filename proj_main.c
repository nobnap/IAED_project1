# include <stdio.h>
# include <string.h>
# include "types.h"

date current_date = {1, 1, 2022};

airport airport_list[MAX_AIRPORT];
int num_airport = 0;

flight flight_list[MAX_FLIGHTS];
int num_flights = 0;

void add_airport() {
	airport input;
	int i;

	scanf("%s%s%s", input.ID, input.country, input.city);

	for (i = 0; i < 3; i++) {
		if (input.ID[i] > 'Z' || input.ID[i] < 'A')
			printf("invalid airport ID\n");
			return;
	}
		if (num_airport == MAX_AIRPORT) {
		printf("too many airports\n");
		return;
	}
	for (i = 0; i < num_airport; i++) {
		if (strcmp(airport_list[i].ID, input.ID)) {
			printf("duplicate airport\n");
			return;
		}
	}

	airport_list[num_airport] = input;
	num_airport++;
	printf("airport %s\n", input.ID);
}

void list_airport() {

}

void input_reader() {
	char command;
	while (command != 'q') {
		switch (command = getchar()) {
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
}

int main() {
	input_reader();
	return 0;
}