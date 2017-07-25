/*
 * DataAdapter.cpp
 *
 *  Created on: Jul 21, 2017
 *      Author: fm
 */
#include <algorithm>   // transform()
#include <cctype>      // toupper(), tolower()
#include <boost/algorithm/string.hpp>
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
				sql.select += " ,DATE_FORMAT (SNAPSHOT_D, '%Y') as 'Time'";
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
				sql.select +=
						", DATE_FORMAT(SNAPSHOT_D, '%m') as 'Time', DATE_FORMAT(SNAPSHOT_D, '%Y') as 'Year'";
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

				sql.select +=
						", DATE_FORMAT(SNAPSHOT_D, '%d') as 'Time', DATE_FORMAT(SNAPSHOT_D, '%Y-%m') as 'Month'";
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

				sql.select +=
						", DATE_FORMAT(SNAPSHOT_D, '%H') as 'Time', DATE_FORMAT(SNAPSHOT_D, '%Y-%m-%d') as 'Day'";
				sql.groupBy = "GROUP BY DATE_FORMAT (SNAPSHOT_D, '%H')";
				sql.orderBy = "ORDER BY DATE_FORMAT (SNAPSHOT_D, '%H')";

				counter++;
			} else {
				cout << " too much detail in time. haven't implemented yet"
						<< endl;
			}

		} else if (s == "business") {
			if (c == "top") {
				// doing nothing
				// we just have one level
				sql.select += ", KPI_BUSINESS_NM as 'Business'";
			} else {
				sql.select += ", KPI_BUSINESS_NM as 'Business'";
				// !!! notice here, we don't have a next level for business
				vector<string> business = vector<string>();
				d.getRepValues(business);
				string str = " and KPI_BUSINESS_NM in (";
				string businessStr = "";
				for (string y : business) {
					str += "'" + y + "',";
				}
				str = str.substr(0, str.length() - 1) + ")";
				sql.where += str;
				counter++;
			}
		} else if (s == "money_category") {
			if (c == "top") {
				/*
				 *if we just add money
				 */
				sql.select += ", KPI_CATEGORY_COARSE_X as 'Money_Category'";
			} else if (c == "coarse") {
				/*
				 *if we select a money coarse category
				 */
				sql.select +=
						", KPI_CATEGORY_COARSE_X as 'Money_Coarse', KPI_CATEGORY_MID_X as 'Money_Category'";
				vector<string> moneyCoarse = vector<string>();
				d.getRepValues(moneyCoarse);
				string str = " and KPI_CATEGORY_COARSE_X in (";
				for (string y : moneyCoarse) {
					str += "'" + y + "',";
				}
				str = str.substr(0, str.length() - 1) + ")";
				sql.where += str;
				counter++;
			} else if (c == "mid") {
				/**
				 *  if we select a money mid category
				 */
				sql.select +=
						", KPI_CATEGORY_COARSE_X as 'Money_Coarse', KPI_CATEGORY_MID_X as 'Money_Mid', KPI_CATEGORY_FINE_X as 'Money_Category'";
				vector<string> moneyMid = vector<string>();
				d.getRepValues(moneyMid);
				string strCoarse = " and KPI_CATEGORY_COARSE_X in (";
				string strMid = " and KPI_CATEGORY_MID_X in (";
				std::vector<std::string> strs;

				for (string y : moneyMid) {
					boost::split(strs, y, boost::is_any_of("-"));
					strCoarse += "'" + strs.at(0) + "',";
					strMid += "'" + strs.at(1) + "',";
				}
				strCoarse = strCoarse.substr(0, strCoarse.length() - 1) + ")";
				strMid = strMid.substr(0, strMid.length() - 1) + ")";
				sql.where += strCoarse;
				sql.where += strMid;
				counter++;
			} else if (c == "fine") {
				/**
				 * I don't think this is useful...
				 */
				sql.select +=
						", KPI_CATEGORY_COARSE_X as 'Money_Coarse', KPI_CATEGORY_MID_X as 'Money_Mid', KPI_CATEGORY_FINE_X as 'Money_Fine'";
				vector<string> moneyMid = vector<string>();
				d.getRepValues(moneyMid);
				string strCoarse = " and KPI_CATEGORY_COARSE_X in (";
				string strMid = " and KPI_CATEGORY_MID_X in (";
				string strFine = " and KPI_CATEGORY_Fine_X in (";
				std::vector<std::string> strs;

				for (string y : moneyMid) {
					boost::split(strs, y, boost::is_any_of("-"));
					strCoarse += "'" + strs.at(0) + "',";
					strMid += "'" + strs.at(1) + "',";
					strFine += "'" + strs.at(2) + "',";
				}
				strCoarse = strCoarse.substr(0, strCoarse.length() - 1) + ")";
				strMid = strMid.substr(0, strMid.length() - 1) + ")";
				strFine = strMid.substr(0, strMid.length() - 1) + ")";
				sql.where += strCoarse;
				sql.where += strMid;
				sql.where += strFine;
				counter++;
			} else {
				cout
						<< " too much detail in money category. haven't implemented yet"
						<< endl;
			}

		} else if (s == "account_type") {
			// we only have one level here
			if (c == "top") {
				sql.select += ", REG_ABBREV_C as 'Account_Type'";
				sql.from += ", BDC_ACCOUNT_MINI_DIM mini_dim";
				sql.where +=
						" AND mini_dim.ACCT_MINI_DIM_ID = base.ACCT_MINI_DIM_ID";
				counter++;
			} else {
				sql.select += ", REG_ABBREV_C as 'Account_Type'";
				sql.from += ", BDC_ACCOUNT_MINI_DIM mini_dim";
				sql.where +=
						" AND mini_dim.ACCT_MINI_DIM_ID = base.ACCT_MINI_DIM_ID";
				// !!! notice here, we don't have a next level for account type
				vector<string> account = vector<string>();
				d.getRepValues(account);
				string str = " and REG_ABBREV_C in (";
				for (string y : account) {
					str += "'" + y + "',";
				}
				str = str.substr(0, str.length() - 1) + ")";
				sql.where += str;
				counter++;
			}
		} else if (s == "value") {
			/**
			 *add a fake dimension to init select and set operator
			 */
			sql.select = "SELECT SUM(ACCT_KPI_TYPE_TXN_VAL) as 'Value'"
					+ sql.select;
			sql.from = "FROM BDC_TXN_FACT_MA_MORE base, BDC_KPI_DIM_MORE KPI"
					+ sql.from;
			sql.where = "WHERE base.KPI_TYPE_ID = KPI.KPI_TYPE_ID" + sql.where;
			// check operator
			// should be just one
			string op = d.getOperator();
			transform(op.begin(), op.end(), op.begin(),
					ptr_fun<int, int>(toupper));
			if (op != "SUM") {
				cout << "altering operator" << endl;
				size_t f = sql.select.find("SUM(");
				sql.select.replace(f, std::string("SUM(").length(), op + "(");
			}
		} else {
			cout << "Invalid dimension called " << s << endl;
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

