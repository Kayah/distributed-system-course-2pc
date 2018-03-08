#include "transaction_mng.h"

error_code 
start_transaction(Transaction &tr, connection *fbc, connection *hbc, connection *acc)
{
    (void) tr;
    if (!fbc || !hbc || !acc)
        return START_TRANSACTION_FAILED;
    
    work fbworker(*fbc);
    work hbworker(*hbc);
    work acworker(*acc);
    
    error_code ret = OK; 
    
    string sqlfb = "BEGIN; INSERT INTO fb VALUES (1, 'Xander', 321, 'kiev', 'new-york', '24/07/97'); PREPARE TRANSACTION 'trip';";
    
    string sqlhb = "BEGIN; INSERT INTO hb VALUES (1, 'Xander', 321,'22/07/98', '24/07/97'); PREPARE TRANSACTION 'hotel';";
    
    string sqlacc = "UPDATE accounts SET amount = -100 where id = 1;";
    
    if ((ret = insert_op(sqlfb, &fbworker)))
    {
        cout << "Failed to make transaction to "<< fbc->dbname() << endl;
        goto err;
    } 
    
    if ((ret = insert_op(sqlhb, &hbworker)))
    {
        cout << "Failed to make transaction to "<< hbc->dbname() << endl;
        goto err;
    }
    
    if ((ret = insert_op(sqlacc, &acworker)))
    {
        cout << "Failed to make transaction to "<< hbc->dbname() << endl;
        goto err;
    }

    if ((ret = finish_purchase(&fbworker, &hbworker, &acworker, fbc, hbc, acc)))
        goto err;

    return OK;

err:
    print_error(ret); 
    return START_TRANSACTION_FAILED;
}

error_code 
insert_op(string sql, work *dbc)
{
    try
    {
       dbc->exec(sql);
    }
    catch(const exception &e)
    {
        cerr<< e.what() << endl;
        return INSERT_OPERATION_FAILED;
    }
    return OK;
}

error_code
finish_transaction(work *worker, string sql)
{
    if (NULL == worker)
        return UNKNOWN_ERROR;
    try
    {
        worker->exec(sql);
        worker->commit();
    }
    catch(const exception &e)
    {
        cerr<< e.what() << endl;
        return FINISH_TRANSACTION_FAILED;
    }
    return OK;
}

error_code
finish_purchase(work *w0, work *w1, work *w2, connection *c0, connection *c1, connection *c2)
{
    string sql0 = "COMMIT PREPARED 'trip';";
    string sql1 = "COMMIT PREPARED 'hotel';";
    
    if (finish_transaction(w0, sql0)) 
    {
        w0->abort();
        delete_prepared_transaction(c0, "ROLLBACK PREPARED 'trip';");    
        cout << "Finish purchase failed for w0" << endl;
        return UNKNOWN_ERROR; 
    }

    if (finish_transaction(w1, sql1))
    {
        delete_commited(c0, "");
        w1->abort();
        delete_prepared_transaction(c1, "ROLLBACK PREPARED 'hotel';");
        cout << "Finish purchase failed for w1" << endl;
        return UNKNOWN_ERROR;
    }

    if (finish_transaction(w2, sql1))
    {
        delete_commited(c0, "");
        delete_commited(c1, "");
        w1->abort();
        cout << "Finish purchase failed for w2" << endl;
        return UNKNOWN_ERROR;
    }
    return OK;
}

void
delete_prepared_transaction(connection *c, string sql)
{
    try
    {
        nontransaction nontr(*c);
        nontr.exec(sql);
        nontr.commit();
    }
    catch(const exception &e)
    {
        cerr << e.what() << endl;
    }
}

void
delete_commited(connection *c, string sql)
{
    (void)sql;
    try
    {
        work worker(*c);
        worker.exec("DELETE from fb where bookingid = 1;");
        worker.commit();
    }
    catch(const exception &e)
    {
        cerr << e.what() << endl;
    }
}
