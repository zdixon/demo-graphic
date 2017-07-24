/*
 * Cube.h
 *
 *  Created on: Jul 24, 2017
 *      Author: fm
 */

#ifndef SRC_DS_CUBE_H_
#define SRC_DS_CUBE_H_

#include <vector>

#include "CubeCell.h"
#include "InterfaceData.h"
#include "../adapter/DataAdapter.h"

class Cube {
public:
	Cube();
	virtual ~Cube();

	void setInterfaceDimensions();
	void queryDatabase();
	void computerCubes();

private:
	/*
	 * you may need to add more functions and variables here
	 */
	InterfaceData _interfaceDims;
	InterfaceData _cubeDims;
	vector<CubeCell> _cubes;
	DataAdapter _adapter;
};

#endif /* SRC_DS_CUBE_H_ */
