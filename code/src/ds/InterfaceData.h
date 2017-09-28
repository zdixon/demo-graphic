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
	// in fact, we store everything in stringDimension
	// the float dimension will be used only for the value/money
	std::vector<Dimension<int> > intDimension;
	std::vector<Dimension<float> > floatDimension;
	std::vector<Dimension<std::string> > stringDimension;

	InterfaceData() {
		intDimension = std::vector<Dimension<int> >();
		floatDimension = std::vector<Dimension<float> >();
		stringDimension = std::vector<Dimension<std::string> >();
	}
	void print() {
		std::cout << "\nall int dimensions: " << std::endl;
		for (Dimension<int> id : intDimension) {
			id.print();
		}
		std::cout << "\nall float dimensions: " << std::endl;
		for (Dimension<float> fd : floatDimension) {
			fd.print();
		}
		std::cout << "\nall string dimensions: " << std::endl;
		for (Dimension<std::string> sd : stringDimension) {
			sd.print();
		}
	}

	void clear() {
		std::cout << "clear " << std::endl;
		intDimension.clear();
		floatDimension.clear();
		stringDimension.clear();
	}
};

#endif /* SRC_DS_INTERFACEDATA_H_ */
