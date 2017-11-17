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

#define EMPTY "EMPTY"

using namespace std;

class CubeCell {
public:
	CubeCell();
	CubeCell(Dimension<string> x, Dimension<string> y, Dimension<string> z, Dimension<float> v);
	CubeCell(Dimension<string> x, Dimension<string> y, Dimension<float> v);
	CubeCell(Dimension<string> x, Dimension<float> v);
	CubeCell(Dimension<float> v);

	string getXLabel();
	string getXName();
	string getYLabel();
	string getYName();
	string getZLabel();
	string getZName();
	float getValue();
	void print();

	void setX(string x);
	void setX(Dimension<string> x);
	void setY(string y);
	void setY(Dimension<string> y);
	void setZ(string z);
	void setZ(Dimension<string> z);
	void setV(float v);
	void setV(Dimension<float> v);

private:
	Dimension<string> _x;
	Dimension<string> _y;
	Dimension<string> _z;
	Dimension<float> _v;
	// you may need more fields such as size and text
};

#endif /* SRC_DS_CUBECELL_H_ */
