#include "manager.h"

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
			/* case 'p':
				departures();
				break;
			case 'c':
				arrivals();
				break; */
			case 't':
				date_forward();
				break;
		}
	}
}

int main() {
	input_reader();
	return 0;
}

void add_airport() {
	airport input;
	int i;

	/*scanf("%s%s%s", input.ID, input.country, input.city);  Mudar o método de
	 * leitura do input !! */
	getchar();
	read_char(input.ID, MAX_ID, ' ');
	read_char(input.country, MAX_COUNTRY, ' ');
	read_char(input.city, MAX_CITY, '\n');

	for (i = 0; i < MAX_ID - 1; i++) {
		if (input.ID[i] > 'Z' || input.ID[i] < 'A') {
			printf(ERROR_INVALID_ID);
			return;
		}
	}
	if (num_airport == MAX_AIRPORT) {
		printf(ERROR_AIRPORT_LIMIT);
		return;
	}
	for (i = 0; i < num_airport; i++) {
		if (!strcmp(airports[i].ID, input.ID)) {
			printf(ERROR_AIRPORT_DUPLICATE);
			return;
		}
	}

	airports[num_airport] = input;

	printf("airport %s\n", input.ID);
	num_airport++;
}

void list_airport() {
	int i;
	char c = getchar();
	airport_order();
	if (c == '\n') {
		for (i = 0; i < num_airport; i++) {
			printf("%s %s %s %d\n", airports[i].ID, airports[i].country,
			       airports[i].city, flight_counter(airports[i]));
		}
	} else {
		while (c != '\n') {
			char ID[MAX_ID];
			scanf("%s", ID);
			search_airport(ID);
			c = getchar();
		}
	}
}

void flights() {
	int i;
	flight input;
	if (getchar() == '\n') {
		for (i = 0; i < num_flights; i++) {
			input = flight_list[i];
			printf("%s %s %s %d-%d-%d %d:%d\n", flight_list[i].code,
			      flight_list[i].dep_ID, flight_list[i].ar_ID,
			      flight_list[i].dep_date.day, flight_list[i].dep_date.month,
			      flight_list[i].dep_date.year, flight_list[i].dep_time.hour,
			      flight_list[i].dep_time.min);
		}
	} else {
		scanf("%s %s %s %d-%d-%d %d:%d %d:%d %d", input.code, input.dep_ID,
		      input.ar_ID, &input.dep_date.day, &input.dep_date.month,
		      &input.dep_date.year, &input.dep_time.hour, &input.dep_time.min,
		      &input.duration.hour, &input.duration.min, &input.passengers);
		flight_list[num_flights] = input;
		printf("%s %s %s %d-%d-%d %d:%d\n", flight_list[num_flights].code,
			      flight_list[num_flights].dep_ID, flight_list[num_flights].ar_ID,
			      flight_list[num_flights].dep_date.day, flight_list[num_flights].dep_date.month,
			      flight_list[num_flights].dep_date.year, flight_list[num_flights].dep_time.hour,
			      flight_list[num_flights].dep_time.min);
		num_flights++;
	}
}

void departures() {
	
}

void date_forward() {
	date new;
	scanf("%d-%d-%d", &new.day, &new.month, &new.year);

	/* dumbass !!
	se current_date = 23-04-2007 entao a data 22-04-2008 deve ser valida
	dumbass !! */
	if (current_date.year != new.year ||
	    (current_date.year == new.year&& current_date.month > new.month) ||
	    (current_date.year == new.year&& current_date.month ==
	     new.month&& current_date.day > new.day)) {
		printf(ERROR_DATE);
		return;
	}

	current_date = new;
	printf("%02d-%02d-%04d\n", current_date.day, current_date.month,
	       current_date.year);
}

void read_char(char word[], int size, char end) {
	int i;
	char a = getchar();
	for (i = 0; i < size - 1; i++) {
		if (a == end) break;
		word[i] = a;
		a = getchar();
	}
	word[i++] = '\0';
}

int flight_counter(airport ap) {
	int i, flights = 0;
	for (i = 0; i < num_flights; i++) {
		if (!strcmp(flight_list[i].dep_ID, ap.ID)) flights++;
	}
	return flights;
}

int before(char A[], char B[]) {
	int i;
	for (i = 0; i < MAX_ID - 1; i++) {
		if (A[i] < B[i])
			return 1;
		else if (A[i] == B[i])
			continue;
		else
			return 0;
	}
}

void airport_order() {
	int i, j;
	airport t; /* also use the done
	              thing the teacher showed in class !! */
	for (i = 0; i < num_airport; i++)
		for (j = num_airport - 1; j > i; j--)
			if (before(airports[j].ID, airports[j - 1].ID)) {
				t = airports[j - 1];
				airports[j - 1] = airports[j];
				airports[j] = t;
			}
}

void search_airport(char ID[]) {
	int lower = 0, middle, upper = num_airport - 1;
	middle = (lower + upper) / 2;
	while (upper >= lower) {
		if (!strcmp(ID, airports[middle].ID)) {
			printf("%s %s %s %d\n", airports[middle].ID, airports[middle].country,
			       airports[middle].city, flight_counter(airports[middle]));
			return;
		}
		if (before(ID, airports[middle].ID)) {
			upper = middle - 1;
		} else {
			lower = middle + 1;
		}
		middle = (lower + upper) / 2;
	}
	printf("%s: %s", ID, ERROR_NONEXISTENT_ID);
}

void search_flight(char code[]) {
	int i;
	for (i = 0; i < num_flights; i++) {
		if (!strcmp(code, flight_list[i].code))
			printf("%s %s %s %d-%d-%d %d:%d\n", flight_list[i].code,
			       flight_list[i].dep_ID, flight_list[i].ar_ID,
			       flight_list[i].dep_date.day, flight_list[i].dep_date.month,
			       flight_list[i].dep_date.year, flight_list[i].dep_time.hour,
			       flight_list[i].dep_time.min);
	}
}
/* Escrito de acordo com Ortografia Clássica, anterior ao incoerente Acordo
 * Ortográfico de 1990. */