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
//	sql.select = "SELECT DATE_FORMAT (SNAPSHOT_D, '%Y') as 'Year', DATE_FORMAT (SNAPSHOT_D, '%Y') as 'Time', SUM(ACCT_KPI_TYPE_TXN_VAL) as 'Value' ";
	sql.select =
			"SELECT DATE_FORMAT (SNAPSHOT_D, '%Y') as 'Time', SUM(ACCT_KPI_TYPE_TXN_VAL) as 'Value'";
//	sql.from = "FROM BDC_TXN_FACT_MA_MORE as base, BDC_KPI_DIM_MORE as kpi";
	sql.from = "FROM BDC_TXN_FACT_MA_MORE base, BDC_KPI_DIM_MORE KPI";
	sql.where = "WHERE base.KPI_TYPE_ID = KPI.KPI_TYPE_ID";
	sql.groupBy = "GROUP BY DATE_FORMAT (SNAPSHOT_D, '%Y')";
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
	for (Dimension<string> d : sds) {
		string s = d.getName();
		transform(s.begin(), s.end(), s.begin(), ptr_fun<int, int>(toupper));
		if (s == "time") {
		}

		if (s == "business") {
		}

		if (s == "money_category") {
		}

		if (s == "account_type") {
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
				df.addValue(float(rs->getDouble(name)));
			}
			cubeDims.floatDimension.push_back(df);
//			df.print();
		} else {
			Dimension<string> sf = Dimension<string>(name);
			while (rs->next()) {
				sf.addValue(rs->getString(name));
			}
			cubeDims.stringDimension.push_back(sf);
//			sf.print();
		}
	}
	delete rs;
}

