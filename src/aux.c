# include "manager.h"

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
	airport t;/* find a way to simplify all those strcpy and also use the done thing the teacher showed in class !! */
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