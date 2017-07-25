/*
 * Dimension.h
 *
 *  Created on: Jul 20, 2017
 *      Author: fm
 *      A class to serve as a media between the interface changes
 */

#ifndef SRC_DS_DIMENSION_H_
#define SRC_DS_DIMENSION_H_

#include <string>
#include <sstream>
#include <iostream>
#include <set>
#include <vector>

typedef bool empty;
using namespace std;

template<typename T>
class Dimension {
public:
	// constructor
	Dimension();

	// constructor with an initial setting of name
	Dimension(string str);

	// constructor with an initial setting of name and value
	Dimension(string n, T v);

	virtual ~Dimension();

	// get the name of this dimension
	string getName();

	// get the value
	T getValueAt(int i);

	// get all the values
	void getRepValues(vector<T> & vs);

	// get the path of levels
	void getPath(vector<string> & p);

	// get current level
	string getCurrentLevel();

	// print the content of this dimension, name and values
	void print();

	// print path
	void printPath();

	//print values
	void printValues();

	// get the size of value
	int getSize();

	// get the operator
	string getOperator();

	// get the first / min value of the value set
	T getFirstValue();

	// get the last / max value of the value set
	T getLastValue();

	// add a value
	void addNonRepValue(T v);

	// add a value
	void addRepValue(T v);

	// add a level to the path
	void addPath(string p);

	// remove last one
	void removeLastItemOnPath();

	// set the name of the dimension
	void setName(string str);

	// set the operator
	void setOperator(string str);

	// set all values
	void setValues(vector<T>);

	// sort
	void sort();

protected:
	std::string _name;

	// the set is an inner structure to check if elements are distinguishable
	set<T> _valueSet;

	// the structure to store actually data
	vector<T> _valueVector;

	// store the path of values
	vector<string> _path;

	// the operator we wanna apply, by default, it is "sum"
	string _operator;

	// print set for debug purposes
	void printSet();
};

#endif /* SRC_DS_DIMENSION_H_ */
