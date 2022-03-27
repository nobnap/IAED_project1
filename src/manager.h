/* Standard Libraries */
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

/* String Sizes */
# define MAX_COUNTRY 31
# define MAX_CITY 51
# define MAX_ID 4
# define MAX_CODE 8

/* Max Array Sizes */
# define MAX_AIRPORT 40
# define MAX_FLIGHTS 30000

/* Error Messages */
# define ERROR_ID "invalid airport ID\n"
# define ERROR_AIRPORT_LIMIT "too many airports\n"
# define ERROR_AIRPORT_DUPLICATE "duplicate airport\n"
# define ERROR_DATE "invalid date\n"


/* Structures */
typedef struct {
	int day, month, year;
} date;

typedef struct {
	int hour, min;
} time;

typedef struct {
	char ID[MAX_ID];
	char country[MAX_COUNTRY];
	char city[MAX_CITY];
} airport;

typedef struct {
	char code[MAX_CODE];
	char dep_ID[MAX_ID];
	char ar_ID[MAX_ID];
	date dep_date;
	time dep_time;
	date duration;
	int passengers;
} flight;

typedef struct {
	airport airp;
	int flights_ap;
} list;

date current_date;

flight flight_list[MAX_FLIGHTS];
int num_flights;

airport airports[MAX_AIRPORT];
int num_airport;


/* Command-Related Functions */
void add_airport();
void list_airport();
void flights();
void departures();
void arrivals();
void date_forward();

/* Auxiliary Functions */
int flight_counter(airport ap);
int before(char A[], char B[]);
void airport_order();