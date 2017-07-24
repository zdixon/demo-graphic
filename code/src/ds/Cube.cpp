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
				_cubes(vector<CubeCell>()),
				_adapter(DataAdapter()) {
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
void Cube::setInterfaceDimensions() {
}

/**
 *
 */
void Cube::queryDatabase() {
}

/**
 *
 */
void Cube::computerCubes() {
}
