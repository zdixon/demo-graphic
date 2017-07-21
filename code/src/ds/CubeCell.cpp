/*
 * CubeCell.cpp
 *
 *  Created on: Jul 21, 2017
 *      Author: fm
 */

#include <vector>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <type_traits>

#include "Dimension.h"
#include "CubeCell.h"
/*
 * Constructor
 */
template<typename X, typename Y, typename Z, typename V>
CubeCell<X, Y, Z, V>::CubeCell() {
}

/*
 * Deconstructor
 */
template<typename X, typename Y, typename Z, typename V>
CubeCell<X, Y, Z, V>::~CubeCell() {
}

/*
 *
 */
template<typename X, typename Y, typename Z, typename V>
CubeCell<X, Y, Z, V>::CubeCell(Dimension<X> & x, Dimension<Y> & y,
		Dimension<Z> & z, Dimension<V> & v) :
		_x(x), _y(y), _z(z), _v(v) {
}

/*
 *
 */
template<typename X, typename Y, typename Z, typename V>
CubeCell<X, Y, Z, V>::CubeCell(Dimension<X> & x, Dimension<Y> & y,
		Dimension<V> & v) :
		_x(x), _y(y), _z(Dimension<Z>()), _v(v) {
}

/*
 *
 */
template<typename X, typename Y, typename Z, typename V>
CubeCell<X, Y, Z, V>::CubeCell(Dimension<X> & x, Dimension<V> & v) :
		_x(x), _y(Dimension<Y>()), _z(Dimension<Z>()), _v(v) {
}

/*
 * I don't think this type is valid, but ok...
 */
template<typename X, typename Y, typename Z, typename V>
CubeCell<X, Y, Z, V>::CubeCell(Dimension<V> & v) :
		_x(Dimension<X>()), _y(Dimension<Y>()), _z(Dimension<Z>()), _v(v) {
}

/*
 *
 */
template<typename X, typename Y, typename Z, typename V>
void CubeCell<X, Y, Z, V>::setX(Dimension<X> & d) {
	_x = d;
}

/*
 *
 */
template<typename X, typename Y, typename Z, typename V>
void CubeCell<X, Y, Z, V>::setY(Dimension<Y> & d) {
	_y = d;

}

/*
 *
 */
template<typename X, typename Y, typename Z, typename V>
void CubeCell<X, Y, Z, V>::setZ(Dimension<Z> & d) {
	_z = d;
}

/*
 *
 */
template<typename X, typename Y, typename Z, typename V>
void CubeCell<X, Y, Z, V>::getX(Dimension<X> & d) {
	d = _x;
}

/*
 *
 */
template<typename X, typename Y, typename Z, typename V>
void CubeCell<X, Y, Z, V>::getY(Dimension<Y> & d) {
	d = _y;
}

/*
 *
 */
template<typename X, typename Y, typename Z, typename V>
void CubeCell<X, Y, Z, V>::getZ(Dimension<Z> & d) {
	d = _z;
}

/*
 *
 */
template<typename X, typename Y, typename Z, typename V>
void CubeCell<X, Y, Z, V>::print() {
	cout << "(x,y,z,v)=";
	if (!std::is_same<X, empty>::value) {
		cout << _x.getValueAt(0) << ",";
	}
	if (!std::is_same<Y, empty>::value) {
		cout << _y.getValueAt(0) << ",";
	}
	if (!std::is_same<Z, empty>::value) {
		cout << _z.getValueAt(0) << ",";
	}
	cout << _v.getValueAt(0) << endl;
}

// crying....
// (T_T)

// string and float
template class CubeCell<string, string, string, float> ;
template class CubeCell<string, string, float, float> ;
template class CubeCell<string, float, string, float> ;
template class CubeCell<float, string, string, float> ;
template class CubeCell<float, float, string, float> ;
template class CubeCell<float, string, float, float> ;
template class CubeCell<string, float, float, float> ;
template class CubeCell<float, float, float, float> ;

// string and int
template class CubeCell<string, string, int, float> ;
template class CubeCell<string, int, string, float> ;
template class CubeCell<int, string, string, float> ;
template class CubeCell<int, int, string, float> ;
template class CubeCell<int, string, int, float> ;
template class CubeCell<string, int, int, float> ;
template class CubeCell<int, int, int, float> ;

// int and float
template class CubeCell<float, float, int, float> ;
template class CubeCell<float, int, float, float> ;
template class CubeCell<int, float, float, float> ;
template class CubeCell<int, int, float, float> ;
template class CubeCell<int, float, int, float> ;
template class CubeCell<float, int, int, float> ;

// string, int, and float
template class CubeCell<string, int, float, float> ;
template class CubeCell<string, float, int, float> ;
template class CubeCell<int, string, float, float> ;
template class CubeCell<float, string, int, float> ;
template class CubeCell<int, float, string, float> ;
template class CubeCell<float, int, string, float> ;

// string and empty
template class CubeCell<string, string, empty, float> ;
template class CubeCell<string, empty, string, float> ;
template class CubeCell<empty, string, string, float> ;
template class CubeCell<empty, empty, string, float> ;
template class CubeCell<empty, string, empty, float> ;
template class CubeCell<string, empty, empty, float> ;
template class CubeCell<empty, empty, empty, float> ;

// int and empty
template class CubeCell<int, int, empty, float> ;
template class CubeCell<int, empty, int, float> ;
template class CubeCell<empty, int, int, float> ;
template class CubeCell<empty, empty, int, float> ;
template class CubeCell<empty, int, empty, float> ;
template class CubeCell<int, empty, empty, float> ;

// float and empty
template class CubeCell<float, float, empty, float> ;
template class CubeCell<float, empty, float, float> ;
template class CubeCell<empty, float, float, float> ;
template class CubeCell<empty, empty, float, float> ;
template class CubeCell<empty, float, empty, float> ;
template class CubeCell<float, empty, empty, float> ;

// int, float and empty
template class CubeCell<float, int, empty, float> ;
template class CubeCell<float, empty, int, float> ;
template class CubeCell<empty, float, int, float> ;
template class CubeCell<int, float, empty, float> ;
template class CubeCell<int, empty, float, float> ;
template class CubeCell<empty, int, float, float> ;

// string, float and empty
template class CubeCell<float, string, empty, float> ;
template class CubeCell<float, empty, string, float> ;
template class CubeCell<empty, float, string, float> ;
template class CubeCell<string, float, empty, float> ;
template class CubeCell<string, empty, float, float> ;
template class CubeCell<empty, string, float, float> ;

// int, string and empty
template class CubeCell<string, int, empty, string> ;
template class CubeCell<string, empty, int, string> ;
template class CubeCell<empty, string, int, string> ;
template class CubeCell<int, string, empty, string> ;
template class CubeCell<int, empty, string, string> ;
template class CubeCell<empty, int, string, string> ;
