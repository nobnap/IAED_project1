# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "types.h"

date current_date = {1, 1, 2022};

flight flight_list[MAX_FLIGHTS];
int num_flights = 0;

airport airports[MAX_AIRPORT];
int num_airport = 0;


void add_airport() {
	airport input;
	int i;

	scanf("%s%s%s", input.ID, input.country, input.city);

	for (i = 0; i < 3; i++) {
		if (input.ID[i] > 'Z' || input.ID[i] < 'A') {
			printf(ERROR_ID);
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

	strcpy(airports[num_airport].ID, input.ID); 
	strcpy(airports[num_airport].country, input.country);
	strcpy(airports[num_airport].city, input.city);

	printf("airport %s\n", input.ID);
	num_airport++;
}

int flight_counter(airport ap) {
	int i, flights = 0;
	for (i = 0; i < num_flights; i++) {
		if (!strcmp(flight_list[i].dep_ID, ap.ID))
			flights++;
	}
	return flights;
}

int before(char A[], char B[]) {
	int i;
	for (i = 0; i < MAX_ID-1; i++) {
		if (A[i] < B[i]) return 1;
		else if (A[i] == B[i]) continue;
		else return 0;
	}
	return EXIT_FAILURE;
}

void airport_order() {
	int i, j;
	airport t;
	for (i = 0; i < num_airport; i++)
		for (j = num_airport-1; j > i; j--)
			if (before(airports[j-1].ID, airports[j].ID)) {
				strcpy(t.ID, airports[j-1].ID); 
				strcpy(t.country, airports[j-1].country);
				strcpy(t.city, airports[j-1].city);

				strcpy(airports[j-1].ID, airports[j].ID); 
				strcpy(airports[j-1].country, airports[j].country);
				strcpy(airports[j-1].city, airports[j].city);

				strcpy(airports[j].ID, t.ID); 
				strcpy(airports[j].country, t.country);
				strcpy(airports[j].city, t.city);
			}
}

void list_airport() {
	int i;
	char c = getchar();
	if (num_airport) {
		airport_order();
		while (c != '\n') {
			char ID[MAX_ID];
			scanf("%s", ID);  /* usar binary search pelo ID maybe?? !! */
			printf("teste");
			c = getchar();
		}
		for (i = 0; i < num_airport; i++) 
			printf("%s %s %s %d\n", airports[i].ID, airports[i].country, airports[i].city, flight_counter(airports[i]));
	}
}

void date_forward() {
	date new;
	scanf("%d-%d-%d", &new.day, &new.month, &new.year);
	current_date = new; 
	/* faltam os erros */
	printf("%0d-%0d-%0d", current_date.day, current_date.month, current_date.year);
}

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
			/*case 'v':
				flights();
				break;
			case 'p':
				departures();
				break;
			case 'c':
				arrivals();
				break; */
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