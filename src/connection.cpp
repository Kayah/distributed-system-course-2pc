#include "connection.h"

connection *connecter(const char *config)
{
    return new connection(config);
}

void disconnect(connection *c)
{
    if (!c)
        return;

    c->disconnect();
    delete c;
}

int check_connection(connection *c)
{
    if (!c)
        return 0;

    if (c->is_open())
    {
        cout << "Connection to "<< c->dbname() <<" opened successfuly!" <<endl;
    }
    else
    {
        cout << "Cannot open connection to db" << endl;
        return -1;
    }
    return 0;
}
