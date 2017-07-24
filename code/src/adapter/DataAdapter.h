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
#include "../ds/InterfaceData.h"

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
	void getResult(InterfaceData interDims, InterfaceData & cubeDims);
	bool isOpen();
private:
	bool _isOpen;
	DBHandler _dbhandler;
	void ResultSetToDimension();
};

#endif /* SRC_ADAPTER_DATAADAPTER_H_ */
