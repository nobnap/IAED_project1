/*
 * File: manager.h
 *
 * Author: Maria João Rosa
 * Email: maria.j.rosa@tecnico.ulisboa.pt
 *
 * Description: Header file containing all standard libraries, constants,
 * structures and algorithms used in the project.
 *
 */

/* Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Max String Sizes */
#define MAX_COUNTRY 31
#define MAX_CITY 51
#define MAX_ID 4
#define MAX_CODE 7

/* Max Array Sizes */
#define MAX_AIRPORT 40
#define MAX_FLIGHTS 30000

/* Error Messages */
#define ERROR_INVALID_ID "invalid airport ID\n"
#define ERROR_NONEXISTENT_ID "%s: no such airport ID\n"
#define ERROR_AIRPORT_LIMIT "too many airports\n"
#define ERROR_AIRPORT_DUPLICATE "duplicate airport\n"
#define ERROR_DATE "invalid date\n"
#define ERROR_DURATION "invalid duration\n"
#define ERROR_CODE "invalid flight code\n"
#define ERROR_FLIGHT_DUPLICATE "flight already exists\n"
#define ERROR_FLIGHT_LIMIT "too many flights\n"
#define ERROR_CAPACITY "invalid capacity\n"

/* Input and Output Strings */
#define AIRPORT_NEW "airport %s\n"
#define AIRPORT_OUTPUT "%s %s %s %d\n"
#define FLIGHT_INPUT "%s %s %s %d-%d-%d %d:%d %d:%d %d"
#define FLIGHT_OUTPUT "%s %s %s %02d-%02d-%04d %02d:%02d\n"
#define DEP_AR_OUTPUT "%s %s %02d-%02d-%04d %02d:%02d\n"
#define DATE_INPUT "%d-%d-%d"
#define DATE_OUTPUT "%02d-%02d-%04d\n"

/* 
 * Structures 
 */

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
	time duration;
	int capacity;
} flight;

typedef struct {
	flight flight;
	date date;
	time time;
} arrival;

/* 
 * Command Related Functions
 */

int input_reader();
void add_airport();
void list_airport();
void flights();
void departures();
void arrivals();
void date_forward();

/* 
 * Auxiliary Functions 
 */

void read_char(char word[], int size, char end[]);
int flight_counter(airport ap);
int airport_error(airport input);
void airport_order();
int search_airport(char ID[]);
int flight_errors(flight input);
int valid_code(char code[]);
int search_flight(flight input);
int compare_date(date d1, date d2);
int compare_time(time t1, time t2);
int compare_timedate(date dateA, time timeA, date dateB, time timeB);
void order_departures(int size);
void search_departures(char ID[]);
arrival flight_into_arrival(flight f);
void order_arrivals(int size);
void search_arrivals(char ID[]);