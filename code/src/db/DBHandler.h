/*
 * DBHandler.h
 *
 *  Created on: Jul 20, 2017
 *      Author: fm
 */

#ifndef DBHANDLER_H_
#define DBHANDLER_H_

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "mysql_connection.h"
#include "mysql_driver.h"
#include "mysql_error.h"

#define EXAMPLE_HOST "makeithappen.cs.brown.edu"
#define EXAMPLE_USER "dbuser"
#define EXAMPLE_PASS "dbpassword"
#define EXAMPLE_DB "Sensors"

class DBHandler {
public:
	DBHandler();
	virtual ~DBHandler();
	int getConnection();
	sql::ResultSet* exeQuery(std::string sql);
	void closeConnection();

private:
    sql::Connection *m_con;
    sql::Statement *m_stmt;
};
#endif /* DBHANDLER_H_ */
