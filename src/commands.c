# include "manager.h"

void add_airport() {
	airport input;
	int i;

	scanf("%s%s%s", input.ID, input.country, input.city);

	for (i = 0; i < MAX_ID-1; i++) {
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

void list_airport() {
	int i;
	/* char c = getchar(); */
	if (num_airport) {
		airport_order();
/* 		while (c != '\n') {
			char ID[MAX_ID];
			scanf("%s", ID);  usar binary search pelo ID maybe?? !! 
			printf("teste");
			c = getchar();
		} */
		for (i = 0; i < num_airport; i++) 
			printf("%s %s %s %d\n", airports[i].ID, airports[i].country, airports[i].city, flight_counter(airports[i]));
	}
}

void date_forward() {
	date new;
	scanf("%d-%d-%d", &new.day, &new.month, &new.year);
	
	/* faltam os erros */
	if (current_date.year > new.year ||\
	(current_date.year == new.year && current_date.month > new.month) ||\
	(current_date.year == new.year && current_date.month == new.month &&\
	 current_date.day > new.day) || new.year >= current_date.year+1) {
		printf(ERROR_DATE);
		return;
	}

	current_date = new; 
	printf("%02d-%02d-%04d\n", current_date.day, current_date.month, current_date.year);
}