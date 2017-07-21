/*
 * CubeCell.h
 *
 *  Created on: Jul 21, 2017
 *      Author: fm
 *  This class represents a subcube and its dimension
 */

#ifndef SRC_DS_CUBECELL_H_
#define SRC_DS_CUBECELL_H_

#include <vector>
#include "Dimension.h"

using namespace std;

template<typename X, typename Y, typename Z, typename V>
class CubeCell {
public:
	CubeCell();
	virtual ~CubeCell();
	CubeCell(Dimension<X> & x, Dimension<Y> & y, Dimension<Z> & z, Dimension<V> & v);
	CubeCell(Dimension<X> & x, Dimension<Y> & y, Dimension<V> & v);
	CubeCell(Dimension<X> & x, Dimension<V> & v);
	CubeCell(Dimension<V> & v);
	void setX(Dimension<X> &);
	void setY(Dimension<Y> &);
	void setZ(Dimension<Z> &);
	void getX(Dimension<X> &);
	void getY(Dimension<Y> &);
	void getZ(Dimension<Z> &);
	void print();
private:
	Dimension<X> _x;
	Dimension<Y> _y;
	Dimension<Z> _z;
	Dimension<V> _v;
};

#endif /* SRC_DS_CUBECELL_H_ */
