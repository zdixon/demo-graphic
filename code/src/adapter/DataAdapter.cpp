/*
 * DataAdapter.cpp
 *
 *  Created on: Jul 21, 2017
 *      Author: fm
 */
#include <algorithm>   // transform()
#include <cctype>      // toupper(), tolower()
#include "DataAdapter.h"
/**
 *
 */
DataAdapter::DataAdapter() :
		_dbhandler(DBHandler()), _isOpen(false) {

}

/*
 *
 */
DataAdapter::~DataAdapter() {

}

/**
 *
 */
bool DataAdapter::isOpen() {
	return _isOpen;
}

/**
 *
 */
void DataAdapter::open() {
	if (!_isOpen)
		_dbhandler.getConnection();
	_isOpen = true;
}

/**
 *
 */
void DataAdapter::close() {
	if (_isOpen)
		_dbhandler.closeConnection();
	_isOpen = false;
}

/**
 *
 */
void DataAdapter::getResult(InterfaceData & interDims,
		InterfaceData & cubeDims) {
	SQL sql = SQL();
	setSQLTemplate(sql);

	parseFloatDimensions(sql, interDims.floatDimension);
	parseIntDimensions(sql, interDims.intDimension);
	parseStringDimensions(sql, interDims.stringDimension);

	string str = parseSQL(sql);
	sql::ResultSet* rs = _dbhandler.exeQuery(str);

	parseResultSet(rs, cubeDims);
}

/**
 * This function is customized
 */
void DataAdapter::setSQLTemplate(SQL & sql) {
	sql.select = "SELECT SUM(ACCT_KPI_TYPE_TXN_VAL) as 'Value'";
	sql.from = "FROM BDC_TXN_FACT_MA_MORE base, BDC_KPI_DIM_MORE KPI";
	sql.where = "WHERE base.KPI_TYPE_ID = KPI.KPI_TYPE_ID";
	sql.groupBy = "GROUP BY 'Time'";
	sql.orderBy = "ORDER BY 'Time'";
}
/**
 *
 */
void DataAdapter::parseFloatDimensions(SQL & sql,
		vector<Dimension<float> > & fds) {
	cout << "nothing here, we don't have float dimensions" << endl;
}

/**
 *
 */
void DataAdapter::parseIntDimensions(SQL & sql, vector<Dimension<int> > & ids) {
	cout << "nothing here, we don't have int dimensions" << endl;
}

/**
 *
 */
void DataAdapter::parseStringDimensions(SQL & sql,
		vector<Dimension<string> > & sds) {
	std::locale loc;
	int counter = 0;
	for (Dimension<string> d : sds) {
		string s = d.getName();
		string c = d.getCurrentLevel();

		transform(s.begin(), s.end(), s.begin(), ptr_fun<int, int>(tolower));
		transform(c.begin(), c.end(), c.begin(), ptr_fun<int, int>(tolower));

		if (s == "time") {
			if (c == "top") {
				/**
				 * This is the default one: year against sum of values
				 */
				sql.select =
						"SELECT SUM(ACCT_KPI_TYPE_TXN_VAL) as 'Value', DATE_FORMAT (SNAPSHOT_D, '%Y') as 'Time'";
				sql.groupBy = "GROUP BY DATE_FORMAT (SNAPSHOT_D, '%Y')";
				sql.orderBy = "ORDER BY DATE_FORMAT (SNAPSHOT_D, '%Y')";
				counter++;
			} else if (c == "year") {
				/**
				 * This is when navigates to specific years
				 */
				vector<string> years = vector<string>();
				d.getRepValues(years);
				string str = " and DATE_FORMAT(SNAPSHOT_D, '%Y') in (";
				for (string y : years) {
					str += "'" + y + "',";
				}
				str = str.substr(0, str.length() - 1) + ")";
				sql.where += str;
				sql.select =
						"SELECT SUM(ACCT_KPI_TYPE_TXN_VAL) as 'Value', DATE_FORMAT(SNAPSHOT_D, '%m') as 'Time', DATE_FORMAT(SNAPSHOT_D, '%Y') as 'Year'";
				sql.groupBy = "GROUP BY DATE_FORMAT (SNAPSHOT_D, '%m')";
				sql.orderBy = "ORDER BY DATE_FORMAT (SNAPSHOT_D, '%m')";
				counter++;
			} else if (c == "month") {
				/**
				 * This is when navigates to specific years AND specific months in the format of 2012-05
				 */
				vector<string> months = vector<string>();
				d.getRepValues(months);
				string str = " and DATE_FORMAT(SNAPSHOT_D, '%Y-%m') in (";
				for (string m : months) {
					str += "'" + m + "',";
				}
				str = str.substr(0, str.length() - 1) + ")";
				sql.where += str;

				sql.select =
						"SELECT SUM(ACCT_KPI_TYPE_TXN_VAL) as 'Value', DATE_FORMAT(SNAPSHOT_D, '%d') as 'Time', DATE_FORMAT(SNAPSHOT_D, '%Y-%m') as 'Month'";
				sql.groupBy = "GROUP BY DATE_FORMAT (SNAPSHOT_D, '%d')";
				sql.orderBy = "ORDER BY DATE_FORMAT (SNAPSHOT_D, '%d')";

				counter++;
			} else if (c == "day") {
				/**
				 * This is when navigates to specific years AND specific months AND days in the format of 2012-05-01
				 */
				vector<string> days = vector<string>();
				d.getRepValues(days);
				string str = " and DATE_FORMAT(SNAPSHOT_D, '%Y-%m-%d') in (";
				string dayStr = "";
				for (string m : days) {
					str += "'" + m + "',";
					dayStr += m + "/";
				}
				str = str.substr(0, str.length() - 1) + ")";
				dayStr = "'" + dayStr.substr(0, dayStr.length() - 1) + "'";
				sql.where += str;

				sql.select =
						"SELECT SUM(ACCT_KPI_TYPE_TXN_VAL) as 'Value', DATE_FORMAT(SNAPSHOT_D, '%H') as 'Time', DATE_FORMAT(SNAPSHOT_D, '%Y-%m-%d') as 'Day'";
				sql.groupBy = "GROUP BY DATE_FORMAT (SNAPSHOT_D, '%H')";
				sql.orderBy = "ORDER BY DATE_FORMAT (SNAPSHOT_D, '%H')";

				counter++;
			} else {
				cout << " too much detail in time. haven't implemented yet"
						<< endl;
			}

		} else if (s == "business") {
			if (counter == 0) {
				sql.select = "SELECT ";
				// if this is the first
			} else {
				sql.select += ',';
			}

			sql.select += "KPI_BUSINESS_NM as 'Business'";

			if (c == "top") {
				// doing nothing
				// we just have one level
			} else {
				// !!! notice here, we don't have a next level for business
				vector<string> business = vector<string>();
				d.getRepValues(business);
				string str = " and KPI_BUSINESS_NM in (";
				string businessStr = "";
				for (string y : business) {
					str += "'" + y + "',";
					businessStr += y + "/";
				}
				str = str.substr(0, str.length() - 1) + ")";
				businessStr = "'"
						+ businessStr.substr(0, businessStr.length() - 1) + "'";
				sql.where += str;
				counter++;
			}
		} else if (s == "money_category") {
		} else if (s == "account_type") {
		} else {

		}

		// check operator
		// should be just one
		string op = d.getOperator();
		transform(op.begin(), op.end(), op.begin(), ptr_fun<int, int>(toupper));
		if (op != "SUM") {
			cout << "altering operator" << endl;
			size_t f = sql.select.find("SUM(");
			sql.select.replace(f, std::string("SUM(").length(), op + "(");
		}
	}
}

/**
 *
 */
string DataAdapter::parseSQL(SQL sql) {
	return sql.select + " " + sql.from + " " + sql.where + " " + sql.groupBy
			+ " " + sql.orderBy + ";";
}

/**
 *
 */
void DataAdapter::parseResultSet(sql::ResultSet * rs,
		InterfaceData & cubeDims) {

// !!!!!!! to clear up whatever there
	cubeDims.clear();

	sql::ResultSetMetaData * rsmd = rs->getMetaData();
	int numcols = rsmd->getColumnCount();

	vector<string> names = vector<string>();
	vector<string> types = vector<string>();

	for (int i = 0; i < numcols; ++i) {
		string name = rsmd->getColumnLabel(i + 1);
		string type = rsmd->getColumnTypeName(i + 1);
		cout << name << " \t" << type << " \t" << endl;

		rs->beforeFirst();

		if (name == "Value") {
			Dimension<float> df = Dimension<float>(name);
			while (rs->next()) {
				df.addRepValue(float(rs->getDouble(name)));
			}
			cubeDims.floatDimension.push_back(df);
//			df.print();
		} else {
			Dimension<string> sf = Dimension<string>(name);
			while (rs->next()) {
				sf.addRepValue(rs->getString(name));
			}
			cubeDims.stringDimension.push_back(sf);
//			sf.print();
		}
	}
	delete rs;
}

