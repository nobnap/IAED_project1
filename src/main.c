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
			case 'p':
				departures();
				break;
			/* case 'c':
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
	read_char(input.ID, MAX_ID, "\t ");
	read_char(input.country, MAX_COUNTRY, "\t ");
	read_char(input.city, MAX_CITY, "\n");

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
	int i, in;
	char c = getchar();
	airport_order();
	if (c == '\n') {
		for (i = 0; i < num_airport; i++) {
			printf("%s %s %s %d\n", airports[i].ID, airports[i].city,
			       airports[i].country, flight_counter(airports[i]));
		}
	} else {
		while (c != '\n') {
			char ID[MAX_ID];
			scanf("%s", ID);
			in = search_airport(ID);
			if (in >= 0) {
				printf("%s %s %s %d\n", airports[in].ID, airports[in].city,
				       airports[in].country, flight_counter(airports[in]));
			}
			c = getchar();
		}
	}
}

void flights() {
	int i;
	flight input;
	if (getchar() == '\n') {
		for (i = 0; i < num_flights; i++) {
			printf("%s %s %s %02d-%02d-%04d %02d:%02d\n", flight_list[i].code,
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
		num_flights++;
	}
}

void departures() {
	int n;
	char c = getchar();
	while (c != '\n') {
		char ID[MAX_ID];
		scanf("%s", ID);
		n = search_airport(ID);
		if (n >= 0) search_departures(ID);
		c = getchar();
	}
}

void arrivals() {
	int n;
	char c = getchar();
	while (c != '\n') {
		char ID[MAX_ID];
		scanf("%s", ID);
		n = search_airport(ID);
		if (n >= 0) search_arrivals(ID);
		c = getchar();
	}
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
	return EXIT_FAILURE;
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

int search_airport(char ID[]) {
	int lower = 0, middle, upper = num_airport - 1;
	middle = (lower + upper) / 2;
	while (upper >= lower) {
		if (!strcmp(ID, airports[middle].ID)) {
			return middle;
		}
		if (before(ID, airports[middle].ID)) {
			upper = middle - 1;
		} else {
			lower = middle + 1;
		}
		middle = (lower + upper) / 2;
	}
	printf("%s: %s", ID, ERROR_NONEXISTENT_ID);
	return -1;
}

/* Returns -1 if d1 is before d2, 0 if they are the same date and 1 if d1 is
 * after d2 */
int relative_date(date d1, date d2) {
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

int relative_time(time t1, time t2) {
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

int compare_timedate(date dateA, time timeA, date dateB, time timeB) {
	int date, time;
	date = relative_date(dateA, dateB);
	time = relative_time(timeA, timeB);
	if (date) return date;
	return time;
}

void order_departures(flight list[], int size) {
	int i, j;
	flight v;
	for (i = 1; i < size; i++) {
		v = list[i];
		for (j = i - 1;
		     j >= 0 && compare_timedate(v.dep_date, v.dep_time, list[j].dep_date,
		                                list[j].dep_time) == -1;
		     j--) {
			list[j + 1] = list[j];
		}
		list[j + 1] = v;
	}
}

void search_departures(char ID[]) {
	int i, n = 0;
	flight list[MAX_FLIGHTS];
	for (i = 0; i < num_flights; i++) {
		if (!strcmp(ID, flight_list[i].dep_ID)) {
			list[n] = flight_list[i];
			n++;
		}
	}
	order_departures(list, n);
	for (i = 0; i < n; i++) {
		printf("%s %s %02d-%02d-%04d %02d:%02d\n", list[i].code, list[i].ar_ID,
		       list[i].dep_date.day, list[i].dep_date.month, list[i].dep_date.year,
		       list[i].dep_time.hour, list[i].dep_time.min);
	}
}

void arrival_time();

void order_arrivals(flight list[], int size) {
	int i, j;
	flight v;
	for (i = 1; i < size; i++) {
		v = list[i];
		for (j = i - 1;
		     j >= 0 && compare_timedate(v.dep_date, v.dep_time, list[j].dep_date,
		                                list[j].dep_time) == 1; /* CHANGE VARIABLES !! */
		     j--) {
			list[j + 1] = list[j];
		}
		list[j + 1] = v;
	}
}

void search_arrivals(char ID[]) {
	int i, n = 0;
	flight list[MAX_FLIGHTS];
	for (i = 0; i < num_flights; i++) {
		if (!strcmp(ID, flight_list[i].dep_ID)) {
			list[n] = flight_list[i];
			n++;
		}
	}
	order_arrivals(list, n);
	for (i = 0; i < n; i++) {
		printf("%s %s %02d-%02d-%04d %02d:%02d\n", list[i].code, list[i].dep_ID,
		       list[i].dep_date.day, list[i].dep_date.month, list[i].dep_date.year,
		       list[i].dep_time.hour, list[i].dep_time.min);
	}
}