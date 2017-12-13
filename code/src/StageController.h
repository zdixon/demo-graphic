/*
 * Stage.h
 *
 *  Created on: Sep 24, 2017
 *      Author: fm
 */

#ifndef SRC_STAGECONTROLLER_H_
#define SRC_STAGECONTROLLER_H_
#include "ds/Dimension.h"
#include "adapter/DataAdapter.h"
#include "boost/multi_array.hpp"
#include <string>
#include <vector>

typedef boost::multi_array<double, 3> Array3D;
typedef Array3D::index arrIndex;

class StageController {
public:
	StageController();
	virtual ~StageController();
	void setUpDimsArr(vector<Dimension<string> >& dims, Array3D & arr, int stage);

private:
	void stage0(vector<Dimension<string> > & dims);
	void stage1(vector<Dimension<string> > & dims);
	void stage2(vector<Dimension<string> > & dims);
	void stage3(vector<Dimension<string> > & dims);
	void stage4(vector<Dimension<string> > & dims);
	void stage5(vector<Dimension<string> > & dims);
	void stage6(vector<Dimension<string> > & dims);
	void stage7(vector<Dimension<string> > & dims);
	void stage8(vector<Dimension<string> > & dims);
	void stage9(vector<Dimension<string> > & dims);
	void stage10(vector<Dimension<string> > & dims);
	void stage11(vector<Dimension<string> > & dims);
	void stage12(vector<Dimension<string> > & dims);
	void stage13(vector<Dimension<string> > & dims);

	void computeValueArray(vector<Dimension<string> > & dims, Array3D & arr);
	DataAdapter _adapter;
};

#endif /* SRC_STAGECONTROLLER_H_ */
