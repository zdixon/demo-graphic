/*
 * Data Struct.h
 *
 *  Created on: Jul 21, 2017
 *      Author: fm
 */

#ifndef SRC_DS_DATASTRUCT_H_
#define SRC_DS_DATASTRUCT_H_

#include "../ds/Dimension.h"

struct InterfaceStruct {
	vector<Dimension<int> > intDimension;
	vector<Dimension<float> > floatDimension;
	vector<Dimension<string> > stringDimension;
	InterfaceStruct() {
		intDimension = vector<Dimension<int> >();
		floatDimension = vector<Dimension<float> >();
		stringDimension = vector<Dimension<string> >();
	}
};

struct CubeStruct {
	vector<Dimension<int> > intDimension;
	vector<Dimension<float> > floatDimension;
	vector<Dimension<string> > stringDimension;
	vector<CubeCell> cube;
	CubeStruct() {
		intDimension = vector<Dimension<int> >();
		floatDimension = vector<Dimension<float> >();
		stringDimension = vector<Dimension<string> >();
		cube = vector<CubeCell>();
	}
};

#endif /* SRC_DS_DATASTRUCT_H_ */
