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

	void setInterfaceDimensions(InterfaceData & interfaceDims);
	void setInterfaceDimensions(vector<Dimension<int> > ids,
			vector<Dimension<float> > fds, vector<Dimension<string> > sds);
	void queryDatabase();
	void computeCubes();
	void printData();

private:
	/*
	 * you may need to add more functions and variables here
	 */
	InterfaceData _interfaceDims;
	InterfaceData _cubeDims;
	vector<CubeCell> _subCubes;
	DataAdapter _adapter;
};

#endif /* SRC_DS_CUBE_H_ */
