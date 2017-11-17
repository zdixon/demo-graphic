/*
 * DataAdapter.h
 *
 *  Created on: Jul 21, 2017
 *      Author: fm
 *      This class will translate 
 */

#ifndef SRC_ADAPTER_DATAADAPTER_H_
#define SRC_ADAPTER_DATAADAPTER_H_

#include <string>
#include <vector>
#include "../db/DBHandler.h"
#include "../ds/InterfaceData.h"

using namespace std;

struct SQL {
	string select = "";
	string from = "";
	string where = "";
	string groupBy = "";
	string orderBy = "";
};

class DataAdapter {
public:
	DataAdapter();
	virtual ~DataAdapter();
	void open();
	void close();
	void getResult(string, vector<Dimension<string> >  &);
	void getDimensionValues(Dimension<string> & odim, Dimension<string> & rdim);
	void getFirstResult(vector<Dimension<string> > & dims, double & v);

	bool isOpen();
	
private:
	bool _isOpen;
	DBHandler _dbhandler;

	void setSQLTemplate(SQL & sql);
	void parseFloatDimensions(SQL & sql, vector<Dimension<float> > & fds);
	void parseIntDimensions(SQL & sql, vector<Dimension<int> > & ids);
	void parseStringDimensions(SQL & sql, vector<Dimension<string> > & sds);
	void parseResultSet(sql::ResultSet * rs, double & v);
	void parseResultSet(sql::ResultSet * rs, Dimension<string> & dim);
	void parseResultSet(sql::ResultSet * rs, vector<Dimension<string> > & dims);
	void parseStringDimension(SQL & sql, Dimension<string> & dim);

	string parseSQL(SQL sql);

};

#endif /* SRC_ADAPTER_DATAADAPTER_H_ */
