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
#include "../ds/Dimension.h"

struct SQL {
	std::string select = "";
	std::string from = "";
	std::string where = "";
	std::string orderBy = "";
	std::string groupBy = "";
};

using namespace std;
class DataAdapter {
public:
	DataAdapter();
	virtual ~DataAdapter();
	void open();
	void close();
	void getResult(SQL sql);
	void addDimensionToSQL(SQL & sql, Dimension<int>);
	void addDimensionToSQL(SQL & sql, Dimension<string>);
	void addDimensionToSQL(SQL & sql, Dimension<float>);
	void addDimensionsToSQL(SQL & sql, vector<Dimension<int> >);
	void addDimensionsToSQL(SQL & sql, vector<Dimension<string> >);
	void addDimensionsToSQL(SQL & sql, vector<Dimension<float> >);
	bool isOpen();
private:
	bool _isOpen;
	DBHandler _dbhandler;
	void ResultSetToDimension();
};

#endif /* SRC_ADAPTER_DATAADAPTER_H_ */
