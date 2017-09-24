/*
 * Cube.cpp
 *
 *  Created on: Jul 24, 2017
 *      Author: fm
 */

#include "Cube.h"

/**
 *
 */
Cube::Cube() :
				_interfaceDims(InterfaceData()),
				_cubeDims(InterfaceData()),
				_subCubes(vector<CubeCell>()),
				_adapter(DataAdapter()) {
	cout << "initialize a cube" << endl;
	_adapter.open();
}
/**
 *
 */
Cube::~Cube() {
	_adapter.close();
}

/**
 *
 */
void Cube::setInterfaceDimensions(InterfaceData & interfaceDims) {
	_interfaceDims = interfaceDims;
}

/**
 *
 */
void Cube::setInterfaceDimensions(vector<Dimension<int> > ids, vector<Dimension<float> > fds,
		vector<Dimension<string> > sds) {
	_interfaceDims.floatDimension = fds;
	_interfaceDims.intDimension = ids;
	_interfaceDims.stringDimension = sds;
}

/**
 *
 */
void Cube::queryDatabase() {
	_adapter.getResult(_interfaceDims, _cubeDims);

}

void Cube::printData() {
	_cubeDims.print();
}
/**
 *
 */
void Cube::computeCubes() {
}
