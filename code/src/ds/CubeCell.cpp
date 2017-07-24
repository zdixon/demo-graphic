/*
 * CubeCell.cpp
 *
 *  Created on: Jul 24, 2017
 *      Author: fm
 */

#include "CubeCell.h"
#include <iostream>

/*
 *
 */
CubeCell::CubeCell() {

}

/*
 *
 */
CubeCell::CubeCell(Dimension<string> x, Dimension<string> y,
		Dimension<string> z, Dimension<float> v) {
	_x = x, _y = y, _z = z, _v = v;
}

/*
 *
 */
CubeCell::CubeCell(Dimension<string> x, Dimension<string> y,
		Dimension<float> v) {
	_x = x, _y = y, _v = v, _z = Dimension<string>(EMPTY);
}

/*
 *
 */
CubeCell::CubeCell(Dimension<string> x, Dimension<float> v) {
	_x = x, _y = Dimension<string>(EMPTY), _z = Dimension<string>(EMPTY), _v = v;
}

/*
 *
 */
CubeCell::CubeCell(Dimension<float> v) {
	_x = Dimension<string>(EMPTY), _y = Dimension<string>(EMPTY), _z =
			Dimension<string>(EMPTY), _v = v;
}

/*
 *  Assume that we only use the first value
 */
string CubeCell::getXLabel() {
	if (_x.getName() != EMPTY) {
		return string(_x.getFirstValue());
	}
	cout << "No value in x" << endl;
	return "NULL";
}

/*
 *
 */
string CubeCell::getXName() {
	return _x.getName();
}

/*
 *
 */
string CubeCell::getYLabel() {
	if (_y.getName() != EMPTY) {
		return string(_y.getFirstValue());
	}
	cout << "No value in y" << endl;
	return "NULL";
}

/*
 *
 */
string CubeCell::getYName() {
	return _y.getName();
}

/*
 *
 */

string CubeCell::getZLabel() {
	if (_z.getName() != EMPTY) {
		return string(_z.getFirstValue());
	}
	cout << "No value in z" << endl;
	return "NULL";
}

/*
 *
 */
string CubeCell::getZName() {
	return _z.getName();
}

/*
 *
 */
float CubeCell::getValue() {
	if (_v.getName() != EMPTY) {
		return _v.getFirstValue();
	}
	cout << "No value" << endl;
	return -999.f;
}

/*
 *
 */
void CubeCell::print() {
	cout << "(x,y,z,v)=";

	cout << getXLabel() << "," << getYLabel() << "," << getZLabel() << ","
			<< getValue() << endl;

}

/*
 *
 */
void CubeCell::setX(string x) {
	vector<string> tmp = vector<string>();
	tmp.push_back(x);
	_x.setValues(tmp);
}

/*
 *
 */
void CubeCell::setX(Dimension<string> x) {
	_x = x;
}

/*
 *
 */
void CubeCell::setY(string y) {
	vector<string> tmp = vector<string>();
	tmp.push_back(y);
	_y.setValues(tmp);
}

/*
 *
 */
void CubeCell::setY(Dimension<string> y) {
	_y = y;
}

/*
 *
 */
void CubeCell::setZ(string z) {
	vector<string> tmp = vector<string>();
	tmp.push_back(z);
	_z.setValues(tmp);
}

/*
 *
 */
void CubeCell::setZ(Dimension<string> z) {
	_z = z;
}

/*
 *========================================================================================================
 *There might be some problems using != for strings
 *========================================================================================================
 */
void CubeCell::setV(float v) {
	if (_v.getName() != EMPTY) {
		_v.setValues(vector<float>(v));
	} else {
		cout << "Nothing to set" << endl;
	}
}

/*
 *
 */
void CubeCell::setV(Dimension<float> v) {
	_v = v;
}

