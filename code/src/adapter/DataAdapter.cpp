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
void DataAdapter::getResult(InterfaceData interDims, InterfaceData & cubeDims) {

}

