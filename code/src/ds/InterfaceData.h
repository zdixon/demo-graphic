/*
 * Data Struct.h
 *
 *  Created on: Jul 21, 2017
 *      Author: fm
 */

#ifndef SRC_DS_INTERFACEDATA_H_
#define SRC_DS_INTERFACEDATA_H_

#include "../ds/Dimension.h"

struct InterfaceData {
	vector<Dimension<int> > intDimension;
	vector<Dimension<float> > floatDimension;
	vector<Dimension<string> > stringDimension;
	InterfaceData() {
		intDimension = vector<Dimension<int> >();
		floatDimension = vector<Dimension<float> >();
		stringDimension = vector<Dimension<string> >();
	}
};

#endif /* SRC_DS_INTERFACEDATA_H_ */
