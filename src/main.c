/*
 * File: main.c
 *
 * Author: Maria João Rosa
 * Email: maria.j.rosa@tecnico.ulisboa.pt
 *
 * Description: File containing all the code used in the first Introduction to
 * Algorithms and Data Structures project.
 *
 */

#include "manager.h"

/*
 * Definition of Global Variables
 */

/* Default date at startup */
date current_date = {1, 1, 2022};

/* Date until which new flights can be added */
date limit_date = {1, 1, 2023};

/* List of flights */
flight flight_list[MAX_FLIGHTS];
/* Number of existing flights */
int num_flights = 0;

/* Auxiliary list of flights and their respective arrival dates and times */
arrival arrivals_list[MAX_FLIGHTS];

/* Auxiliary list of flights */
flight departures_list[MAX_FLIGHTS];

/* List of existing airports */
airport airports[MAX_AIRPORT];
/* Number of existing airports */
int num_airport = 0;

/*
 * Command Related Functions
 */

/* Determines which function to run depending on the command */
int input_reader() {
	char command;
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
	}
	return 1;
}

/* Calls the input_reader() function */
int main() {
	while (input_reader()) {
	};
	return 0;
}

/* Adds airport to the airport list */
void add_airport() {
	airport input;

	getchar();
	read_char(input.ID, MAX_ID, "\t ");
	read_char(input.country, MAX_COUNTRY, "\t ");
	read_char(input.city, MAX_CITY, "\n");

	if (airport_error(input)) return;

	airports[num_airport] = input;

	printf(AIRPORT_NEW, input.ID);
	num_airport++;
}

/* Lists all airports or the airports specified by the user */
void list_airport() {
	int i;
	char c = getchar();

	if (c == '\n') {
		airport_order();
		for (i = 0; i < num_airport; i++) {
			printf(AIRPORT_OUTPUT, airports[i].ID, airports[i].city,
			       airports[i].country, flight_counter(airports[i]));
		}

	} else {
		while (c != '\n') {
			char ID[MAX_ID];

			scanf("%s", ID);
			i = search_airport(ID);
			if (i >= 0) {
				printf(AIRPORT_OUTPUT, airports[i].ID, airports[i].city,
				       airports[i].country, flight_counter(airports[i]));
			}
			c = getchar();
		}
	}
}

/* Lists all flights or adds a flight to the flight list if arguments are given
 */
void flights() {
	int i;
	flight input;

	if (getchar() == '\n') {
		for (i = 0; i < num_flights; i++) {
			printf(FLIGHT_OUTPUT, flight_list[i].code, flight_list[i].dep_ID,
			       flight_list[i].ar_ID, flight_list[i].dep_date.day,
			       flight_list[i].dep_date.month, flight_list[i].dep_date.year,
			       flight_list[i].dep_time.hour, flight_list[i].dep_time.min);
		}

	} else {
		scanf(FLIGHT_INPUT, input.code, input.dep_ID, input.ar_ID,
		      &input.dep_date.day, &input.dep_date.month, &input.dep_date.year,
		      &input.dep_time.hour, &input.dep_time.min, &input.duration.hour,
		      &input.duration.min, &input.capacity);

		if (flight_errors(input)) return;

		flight_list[num_flights] = input;
		num_flights++;
	}
}

/* Lists all flights departing from the specified airports */
void departures() {
	int i;
	char c = getchar();

	while (c != '\n') {
		char ID[MAX_ID];

		scanf("%s", ID);
		i = search_airport(ID);
		if (i >= 0) search_departures(ID);
		c = getchar();
	}
}

/* Lists all flights arriving at the specified airports */
void arrivals() {
	int i;
	char c = getchar();

	while (c != '\n') {
		char ID[MAX_ID];

		scanf("%s", ID);
		i = search_airport(ID);
		if (i >= 0) search_arrivals(ID);
		c = getchar();
	}
}

/* Moves the current date forward */
void date_forward() {
	date new;

	scanf(DATE_INPUT, &new.day, &new.month, &new.year);

	if (compare_date(new, limit_date) == 1 ||
	    compare_date(new, current_date) == -1) {
		printf(ERROR_DATE);
		return;
	}

	current_date = new;
	limit_date = new;
	limit_date.year++;

	printf(DATE_OUTPUT, current_date.day, current_date.month, current_date.year);
}

/*
 * Auxiliary Functions
 */

/* Reads the input until the end characters or until it's reached max size */
void read_char(char word[], int size, char end[]) {
	int i, j;
	char a = getchar();

	for (i = 0; i < size - 1; i++) {
		for (j = 0; end[j] != '\0'; j++) {
			if (a == end[j]) {
				word[i] = '\0';
				return;
			}
		}
		word[i] = a;
		a = getchar();
	}
	word[i++] = '\0';
}

int airport_error(airport input) {
	int i;
	for (i = 0; input.ID[i] != '\0'; i++) {
		if (!isupper(input.ID[i])) {
			printf(ERROR_INVALID_ID);
			return 1;
		}
	}
	if (num_airport >= MAX_AIRPORT) {
		printf(ERROR_AIRPORT_LIMIT);
		return 1;
	}
	for (i = 0; i < num_airport; i++) {
		if (!strcmp(airports[i].ID, input.ID)) {
			printf(ERROR_AIRPORT_DUPLICATE);
			return 1;
		}
	}
	return 0;
}

/* Returns the number of flights departing from an airport */
int flight_counter(airport ap) {
	int i, flights = 0;

	for (i = 0; i < num_flights; i++) {
		if (!strcmp(flight_list[i].dep_ID, ap.ID)) flights++;
	}
	return flights;
}

/* Orders airports alphabetically based on their ID */
void airport_order() {
	int i, j, done;
	airport t;

	for (i = 0; i < num_airport; i++) {
		done = 1;
		for (j = num_airport - 1; j > i; j--)
			if (strcmp(airports[j].ID, airports[j - 1].ID) < 0) {
				t = airports[j - 1];
				airports[j - 1] = airports[j];
				airports[j] = t;
				done = 0;
			}
		if (done) break;
	}
}

/* Searches for an airport in an ordered list through binary search */
int search_airport(char ID[]) {
	int cmp, lower = 0, middle, upper = num_airport - 1;

	airport_order();
	middle = (lower + upper) / 2;

	while (upper >= lower) {
		cmp = strcmp(ID, airports[middle].ID);
		if (!cmp) {
			return middle;
		}
		if (cmp < 0) {
			upper = middle - 1;
		} else {
			lower = middle + 1;
		}
		middle = (lower + upper) / 2;
	}

	printf(ERROR_NONEXISTENT_ID, ID);
	return -1;
}

/* Checks a potential flight for errors */
int flight_errors(flight input) {
	if (!valid_code(input.code)) {
		return printf(ERROR_CODE);
	}
	if (search_flight(input)) {
		return printf(ERROR_FLIGHT_DUPLICATE);
	}
	if (search_airport(input.dep_ID) == -1 || search_airport(input.ar_ID) == -1) {
		return 1;
	}
	if (num_flights >= MAX_FLIGHTS) {
		return printf(ERROR_FLIGHT_LIMIT);
	}
	if (compare_date(input.dep_date, current_date) == -1 ||
	    compare_date(input.dep_date, limit_date) == 1) {
		return printf(ERROR_DATE);
	}
	if (input.duration.hour > 12 ||
	    (input.duration.hour == 12 && input.duration.min > 0)) {
		return printf(ERROR_DURATION);
	}
	if (input.capacity < 10 || input.capacity > 100) {
		return printf(ERROR_CAPACITY);
	}
	return 0;
}

/* Checks if a flight code is valid */
int valid_code(char code[]) {
	int i, size = strlen(code);

	for (i = 0; i < 2; i++) {
		if (!isupper(code[i])) return 0;
	}
	if (!isdigit(code[i]) || code[i] == '0') return 0;
	while (++i < size) {
		if (!isdigit(code[i])) return 0;
	}
	return 1;
}

/* Searches for a flight in a list through linear search */
int search_flight(flight f) {
	int i;

	for (i = 0; i < num_flights; i++) {
		if (!strcmp(f.code, flight_list[i].code) &&
		    !compare_date(f.dep_date, flight_list[i].dep_date)) {
			return 1;
		}
	}
	return 0;
}

/* Compares two dates */
int compare_date(date d1, date d2) {
	if (d1.year < d2.year)
		return -1;
	else if (d1.year == d2.year) {
		if (d1.month < d2.month)
			return -1;
		else if (d1.month == d2.month) {
			if (d1.day < d2.day)
				return -1;
			else if (d1.day == d2.day)
				return 0;
			else
				return 1;
		} else
			return 1;
	} else
		return 1;
}

/* Compares two times */
int compare_time(time t1, time t2) {
	if (t1.hour < t2.hour)
		return -1;
	else if (t1.hour == t2.hour) {
		if (t1.min < t2.min)
			return -1;
		else if (t1.min == t2.min)
			return 0;
		else
			return 1;
	} else
		return 1;
}

/* Compares two time-date pairs */
int compare_timedate(date dateA, time timeA, date dateB, time timeB) {
	int date, time;

	date = compare_date(dateA, dateB);
	time = compare_time(timeA, timeB);
	if (date) return date;
	return time;
}

/* Orders flights from earliest to latest departure through insertion sort */
void order_departures(int size) {
	int i, j;
	flight v;

	for (i = 1; i < size; i++) {
		v = departures_list[i];
		for (j = i - 1;
		     j >= 0 &&
		     compare_timedate(v.dep_date, v.dep_time, departures_list[j].dep_date,
		                      departures_list[j].dep_time) == -1;
		     j--) {
			departures_list[j + 1] = departures_list[j];
		}
		departures_list[j + 1] = v;
	}
}

/* Searches for flights departing from a given airport through its ID */
void search_departures(char ID[]) {
	int i, n = 0;

	for (i = 0; i < num_flights; i++) {
		if (!strcmp(ID, flight_list[i].dep_ID)) {
			departures_list[n] = flight_list[i];
			n++;
		}
	}

	order_departures(n);
	for (i = 0; i < n; i++) {
		printf(DEP_AR_OUTPUT, departures_list[i].code, departures_list[i].ar_ID,
		       departures_list[i].dep_date.day, departures_list[i].dep_date.month,
		       departures_list[i].dep_date.year, departures_list[i].dep_time.hour,
		       departures_list[i].dep_time.min);
	}
}

/* Turns a flight struct into a arrival struct, calculating when it arrives */
arrival flight_into_arrival(flight f) {
	arrival ar;

	ar.flight = f;
	ar.date = f.dep_date;
	ar.time.hour = f.dep_time.hour + f.duration.hour;
	ar.time.min = f.dep_time.min + f.duration.min;

	if (ar.time.min >= 60) {
		ar.time.min -= 60;
		ar.time.hour++;
	}
	if (ar.time.hour >= 24) {
		ar.time.hour -= 24;
		ar.date.day++;
	}
	if (ar.date.month == 2 && ar.date.day > 28) {
		ar.date.day -= 28;
		ar.date.month++;
	} else if ((ar.date.month == 4 || ar.date.month == 6 || ar.date.month == 9 ||
	            ar.date.month == 11) &&
	           ar.date.day > 30) {
		ar.date.day -= 30;
		ar.date.month++;
	} else if (ar.date.day > 31) {
		ar.date.day -= 31;
		ar.date.month++;
	}
	if (ar.date.month > 12) {
		ar.date.month -= 12;
		ar.date.year++;
	}

	return ar;
}

/* Orders flights from earliest to latest arrival through insertion sort */
void order_arrivals(int size) {
	int i, j;
	arrival v;

	for (i = 1; i < size; i++) {
		v = arrivals_list[i];
		for (j = i - 1;
		     j >= 0 && compare_timedate(v.date, v.time, arrivals_list[j].date,
		                                arrivals_list[j].time) == -1;
		     j--) {
			arrivals_list[j + 1] = arrivals_list[j];
		}
		arrivals_list[j + 1] = v;
	}
}

/* Searches for flights arriving at a given airport through its ID */
void search_arrivals(char ID[]) {
	int i, n = 0;

	for (i = 0; i < num_flights; i++) {
		if (!strcmp(ID, flight_list[i].ar_ID)) {
			arrivals_list[n] = flight_into_arrival(flight_list[i]);
			n++;
		}
	}

	order_arrivals(n);
	for (i = 0; i < n; i++) {
		printf(DEP_AR_OUTPUT, arrivals_list[i].flight.code,
		       arrivals_list[i].flight.dep_ID, arrivals_list[i].date.day,
		       arrivals_list[i].date.month, arrivals_list[i].date.year,
		       arrivals_list[i].time.hour, arrivals_list[i].time.min);
	}
}