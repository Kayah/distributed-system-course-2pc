#ifndef CONNECTION_H
#define CONNECTION_H

#include <pqxx/pqxx>
#include <iostream>
#include <string.h>
using std::cout;
using std::cerr;
using std::endl;
using std::exception;
using namespace pqxx;

#define FLY_BOOKING_DB "dbname = flybooking-db \
                        user=alexkonoriev \
                        password = 12345 \
                        hostaddr = 127.0.0.1 \
                        port = 5432"

#define HOTEL_BOOKING_DB "dbname = hotelbooking-db \
                         user=alexkonoriev \
                         password = 12345 \
                         hostaddr = 127.0.0.1 \
                         port = 5432"

#define ACCOUNT_DB "dbname = account \
                         user=alexkonoriev \
                         password = 12345 \
                         hostaddr = 127.0.0.1 \
                         port = 5432"


connection *connecter(const char *config);
void disconnect(connection *);
int check_connection(connection *c);

#endif
