/*
 * DBHandler.cpp
 *
 *  Created on: Jul 20, 2017
 *      Author: fm
 */

#include "DBHandler.h"
#include "DBHandler.h"

DBHandler::DBHandler() :
		m_stmt(0), m_con(0) {
	// TODO Auto-generated constructor stub

}

DBHandler::~DBHandler() {
	closeConnection();
}

void DBHandler::closeConnection() {
	try {
		if (m_stmt) {
			m_stmt->close();
			delete m_stmt;
		}

		if (m_con) {
			m_con->close();
			delete m_con;
		}

		std::cout << "Close connection." << std::endl;

	} catch (sql::SQLException &e) {

		//   MySQL Connector/C++ throws three different exceptions:

		//   - sql::MethodNotImplementedException (derived from sql::SQLException)
		//   - sql::InvalidArgumentException (derived from sql::SQLException)
		//   - sql::SQLException (derived from std::runtime_error)

		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__
				<< std::endl;
		/* what() (derived from std::runtime_error) fetches error message */
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}

}
int DBHandler::getConnection() {
	std::string url(EXAMPLE_HOST);
	const std::string user(EXAMPLE_USER);
	const std::string pass(EXAMPLE_PASS);
	const std::string database(EXAMPLE_DB);

	std::cout << "Connector/C++ tutorial framework..." << std::endl;
	std::cout << std::endl;

	try {

		sql::Driver *driver;

		driver = get_driver_instance();
		m_con = driver->connect(url, user, pass);
		m_con->setSchema(database);
		m_stmt = m_con->createStatement();

		return 0;

	} catch (sql::SQLException &e) {

		//   MySQL Connector/C++ throws three different exceptions:

		//   - sql::MethodNotImplementedException (derived from sql::SQLException)
		//   - sql::InvalidArgumentException (derived from sql::SQLException)
		//   - sql::SQLException (derived from std::runtime_error)

		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__
				<< std::endl;
		/* what() (derived from std::runtime_error) fetches error message */
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

		return 1;
	}

}

sql::ResultSet* DBHandler::exeQuery(std::string sql) {
	try {
		sql::ResultSet *res;
		res = m_stmt->executeQuery(sql);
		while (res->next()) {
			std::cout << "\t... MySQL replies: ";
			/* Access column data by alias or column name */
			std::cout << res->getString("KPI_TYPE_ID") << std::endl;
			std::cout << "\t... MySQL says it again: ";
			/* Access column data by numeric offset, 1 is the first column */
			std::cout << res->getString(2) << std::endl;
		}
		return res;
	} catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__
				<< std::endl;
		/* what() (derived from std::runtime_error) fetches error message */
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return 0;
	}
}

