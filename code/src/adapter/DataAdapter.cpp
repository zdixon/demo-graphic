/*
 * DataAdapter.cpp
 *
 *  Created on: Jul 21, 2017
 *      Author: fm
 */

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
void DataAdapter::getResult(SQL sql) {
}

/**
 *
 */
void DataAdapter::addDimensionToSQL(SQL & sql, Dimension<int> d) {
}

/**
 *
 */
void DataAdapter::addDimensionToSQL(SQL & sql, Dimension<float> d) {
}

/**
 *
 */
void DataAdapter::addDimensionToSQL(SQL & sql, Dimension<string> d) {
}

/**
 *
 */
void DataAdapter::addDimensionsToSQL(SQL & sql, vector<Dimension<int> > ds) {
}

/**
 *
 */
void DataAdapter::addDimensionsToSQL(SQL & sql, vector<Dimension<float> > ds) {
}

/**
 *
 */
void DataAdapter::addDimensionsToSQL(SQL & sql, vector<Dimension<string> > ds) {
}
