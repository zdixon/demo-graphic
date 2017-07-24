/*
 * Dimension.cpp
 *
 *  Created on: Jul 20, 2017
 *      Author: fm
 *      Email: fy@brown.edu
 */

#include "Dimension.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <algorithm>

template<typename T>
Dimension<T>::Dimension() :
				_name(0),
				_valueSet(set<T>()),
				_valueVector(vector<T>()),
				_path(vector<string>()),
				_operator("sum") {

}

template<typename T>
Dimension<T>::Dimension(string name) :
				_name(name),
				_valueSet(set<T>()),
				_valueVector(vector<T>()),
				_path(vector<string>()),
				_operator("sum") {

}

template<typename T>
Dimension<T>::Dimension(string name, T value) :
				_name(name),
				_valueSet(set<T>()),
				_valueVector(vector<T>()),
				_path(vector<string>()),
				_operator("sum") {
	_valueSet.insert(value);
	_valueVector.push_back(value);
}

template<typename T>
Dimension<T>::~Dimension() {

}

template<typename T>
string Dimension<T>::getName() {
	return _name;
}

template<typename T>
T Dimension<T>::getValueAt(int i) {
	if (_valueVector.size() < i - 1) {
		throw std::out_of_range("i");
	}
	return _valueVector.at(i);
}

template<typename T>
void Dimension<T>::getValues(vector<T> & vs) {
	vs = _valueVector;
}

template<typename T>
void Dimension<T>::getPath(vector<string> & p) {
	p = _path;
}

template<typename T>
void Dimension<T>::print() {
	std::cout << "Dimension (" << _name << "," << getSize() << ")" << std::endl;
	printValues();
	printPath();
}

template<typename T>
void Dimension<T>::printPath() {
	string str = "";
	//! c++11 features
	for (string s : _path) {
		str += s + "->";
	}
	std::cout << "Path: " << str << std::endl;
}

template<typename T>
void Dimension<T>::printValues() {
	string str = "";
	//! c++11 features
	std::cout << "values: ";
	for (T s : _valueVector) {
		std::cout << str << ",";
	}
	std::cout << std::endl;
}

template<typename T>
int Dimension<T>::getSize() {
	return _valueVector.size();
}

template<typename T>
void Dimension<T>::addValue(T v) {
	if (_valueSet.find(v) == _valueSet.end()) {
		// check if we have this value
		_valueSet.insert(v);

		// added it to vector
		_valueVector.push_back(v);
		sort();
	}
}

template<typename T>
void Dimension<T>::addPath(string p) {
	_path.push_back(p);
}

template<typename T>
void Dimension<T>::setName(string str) {
	_name = str;
}

/*
 * get the first value, should be also the min
 */
template<typename T>
T Dimension<T>::getFirstValue() {
	if (!_valueVector.empty()) {
		return _valueVector.front();
	} else {
		throw std::out_of_range("vector too small : ");
	}
}

/*
 * get the last value, should be also the max
 */
template<typename T>
T Dimension<T>::getLastValue() {
	if (!_valueVector.empty()) {
		return _valueVector.back();
	} else {
		throw std::out_of_range("vector too small : ");
	}
}

/*
 * get where am i in the traces
 */
template<typename T>
string Dimension<T>::getCurrentLevel() {
	if (!_path.empty()) {
		return _path.back();
	} else {
		throw std::out_of_range("path too short : ");
	}
	return 0;
}

/*
 *
 */
template<typename T>
string Dimension<T>::getOperator() {
	return _operator;
}

/*
 *
 */
template<typename T>
void Dimension<T>::setOperator(string o) {
	_operator = o;
}

/*
 *
 */
template<typename T>
void Dimension<T>::sort() {
	std::sort(_valueVector.begin(), _valueVector.end(), std::less<T>());
}

/*
 *
 */
template<typename T>
void Dimension<T>::removeLastItemOnPath() {
	if (_path.size() > 0) {
		_path.pop_back();
	}
}

/*
 *
 */
template<typename T>
void Dimension<T>::setValues(vector<T> ts) {
	_valueVector = ts;
	_valueSet = set<T>(_valueVector.begin(), _valueVector.end());
}


/*
 * define whatever you need here
 */
template class Dimension<string> ;
template class Dimension<int> ;
template class Dimension<float> ;
template class Dimension<empty> ;

