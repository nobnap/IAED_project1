#define less(A, B) (A < B)

/*Número máximo de carateres para cada string*/
# define MAX_COUNTRY 31
# define MAX_CITY 51
# define MAX_ID 4
# define MAX_CODE 8

# define MAX_AIRPORT 40
# define MAX_FLIGHTS 30000

# define ERROR_ID "invalid airport ID\n"
# define ERROR_AIRPORT_LIMIT "too many airports\n"
# define ERROR_AIRPORT_DUPLICATE "duplicate airport\n"

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