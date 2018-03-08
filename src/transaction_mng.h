#ifndef TRANSACTION_MNG_H
#define TRANSACTION_MNG_H
#include <pqxx/pqxx>
#include <iostream>
#include <string.h>
using std::cout;
using std::cerr;
using std::endl;
using std::exception;
using std::string;
using namespace pqxx;

typedef int error_code;

enum { 
       OK                       = 0, 
       HOTEL_BOOKING_FAILED,     
       FLIGHT_BOOKING_FAILED,    
       INSERT_OPERATION_FAILED,
       FINISH_TRANSACTION_FAILED,
       START_TRANSACTION_FAILED,
       UNKNOWN_ERROR
     };

inline void print_error(error_code e)
{
    switch(e)
    {
        case HOTEL_BOOKING_FAILED:
            cout << "Failed HOTEL_BOOKING_FAILED" << endl;
            break;
        case FLIGHT_BOOKING_FAILED:
            cout << "Failed FLIGHT_BOOKING_FAILED" << endl;
            break;
        case INSERT_OPERATION_FAILED:
            cout << "Failed INSERT_OPERATION_FAILED" << endl;
            break;
        case FINISH_TRANSACTION_FAILED:
            cout << "Failed FINISH_TRANSACTION_FAILED" << endl;
            break;
        case START_TRANSACTION_FAILED:
            cout << "Failed START_TRANSACTION_FAILED" << endl;
            break;
        case UNKNOWN_ERROR:
            cout << "Failed UNKNOWN_ERROR" << endl;
            break;
    }
}

class Transaction
{
public:

    int id;
    string name;
    string flynum;
    string from;
    string to;
    string hotel;
    string date;
    string departure;

    Transaction(int id, string name, string flynum,
                string from, string to, string hotel, 
                string date, string departure):
                id(id), name(name), flynum(flynum),from(from), to(to),
                hotel(hotel), date(date), departure(departure) { }
};

error_code insert_op(string sql, work *worker);
error_code start_transaction(Transaction &tr, connection *fbc, connection *htc, connection *acc);
error_code finish_transaction(work *worker, string sql);
void delete_prepared_transaction(connection *c, string sql);
error_code finish_purchase(work *w0, work *w1, work *w2, connection *c0, connection *c1, connection *c2);
void delete_commited(connection *c, string sql);
#endif
