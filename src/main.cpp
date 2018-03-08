#include "connection.h"
#include "transaction_mng.h"

using std::string;

int main()
{
    connection *fbconnection = NULL;
    connection *htconnection = NULL; 
    connection *adconnection = NULL; 
    int ret = 0;

    fbconnection = connecter(FLY_BOOKING_DB); 
    if (check_connection(fbconnection))
      delete fbconnection;

    htconnection = connecter(HOTEL_BOOKING_DB); 
    if (check_connection(htconnection))
    {
        disconnect(fbconnection);
        delete htconnection;
    }
    
    adconnection = connecter(ACCOUNT_DB); 
    if (check_connection(adconnection))
    {
        disconnect(fbconnection);
        disconnect(htconnection);
        delete adconnection;
    }
    
    Transaction trip(1, "Alex", "KY 123", "Kiev", "New-York", "Continental", "24/07/2018", "24/08/2018"); 
    
    if ((ret = start_transaction(trip, fbconnection, htconnection, adconnection)))
    {
        cout <<"Failed make_transaction" <<endl;
    }
    else
    {
        cout <<"Congratualtations with a new purchace !" << endl;
    }

    cout << "Ales gut" << endl;
    disconnect(fbconnection);
    disconnect(htconnection); 
    
    return 0;
}
