# define MAX_COUNTRY 30
# define MAX_CITY 50
# define MAX_AIRPORT 40
# define MAX_FLIGHTS 30000

typedef struct {
	int year, month, day;
} date;

typedef struct {
	int hour, min;
} time;

typedef struct {
	char ID[4];
	char country[MAX_COUNTRY];
	char city[MAX_CITY];
} airport;

typedef struct {
	char code[7];
	char dep_ID[4];
	char ar_ID[4];
	date dep_date;
	time dep_time;
	date duration;
	int passengers;
} flight;