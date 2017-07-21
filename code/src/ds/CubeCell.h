/*
 * CubeCell.h
 *
 *  Created on: Jul 21, 2017
 *      Author: fm
 *  This struct represents a subcube and its dimension
 */
//
#ifndef SRC_DS_CUBECELL_H_
#define SRC_DS_CUBECELL_H_

#include <vector>
#include "Dimension.h"

using namespace std;

struct CubeCell {
	CubeCell();
	CubeCell(Dimension<string> & x, Dimension<string> & y,
			Dimension<string> & z, Dimension<float> & v) {
		_x = x, _y = y, _z = z, _v = v;
	}
	CubeCell(Dimension<string> & x, Dimension<string> & y,
			Dimension<float> & v) {
		_x = x, _y = y, _v = v, _z = NULL;
	}
	CubeCell(Dimension<string> & x, Dimension<float> & v) {
		_x = x, _y = NULL, _z = NULL, _v = v;
	}
	CubeCell(Dimension<float> & v) {
		_x = NULL, _y = NULL, _z = NULL, _v = v;
	}
	Dimension<string> _x;
	Dimension<string> _y;
	Dimension<string> _z;
	Dimension<float> _v;
};

#endif /* SRC_DS_CUBECELL_H_ */
