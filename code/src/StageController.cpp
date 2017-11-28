/*
 * StageController.cpp
 *
 *  Created on: Sep 24, 2017
 *      Author: fm
 */

#include "StageController.h"
#include <stdlib.h>     /* atof */
StageController::StageController() :
		_adapter(DataAdapter()) {
	_adapter.open();
	// TODO Auto-generated constructor stub

}

StageController::~StageController() {
	// TODO Auto-generated destructor stub
}

void StageController::setUpDimsArr(vector<Dimension<string> > & dims, Array3D & arr, int stage) {
	stage = (stage + 7) % 7;
	std::cout << "----stage: "<< stage << std::endl;

	switch (stage) {
	case 0:
		stage0(dims);
		break;
	case 1:
		stage1(dims);
		break;
	case 2:
		stage2(dims);
		break;
	case 3:
		stage3(dims);
		break;
	case 4:
		stage4(dims);
		break;
	case 5:
		stage5(dims);
		break;
	case 6:
		// cout << "#####THE LAST STAGE IS NOT WORKING#######" << endl;
		stage6(dims);
		break;
	}

//	for(auto d : dims){
//		d.print();
//	}
	computeValueArray(dims, arr);
}

/*
 * Fumeng: I hard-code the sqls, but we should be able to use some inputs to parse sqls
 */

 void StageController::stage0(vector<Dimension<string> > & dims) {
	string sql = "SELECT SUM(ACCT_KPI_TYPE_TXN_VAL) as 'Value' "
			"FROM BDC_TXN_FACT_MA_MORE base, BDC_KPI_DIM_MORE KPI "
			"WHERE base.KPI_TYPE_ID = KPI.KPI_TYPE_ID ";
	dims = vector<Dimension<string> >();
	_adapter.getResult(sql, dims);
}

void StageController::stage1(vector<Dimension<string> > & dims) {
	string sql = "SELECT DATE_FORMAT (SNAPSHOT_D, '%Y') as 'Time',SUM(ACCT_KPI_TYPE_TXN_VAL) as 'Value' "
			"FROM BDC_TXN_FACT_MA_MORE base, BDC_KPI_DIM_MORE KPI "
			"WHERE base.KPI_TYPE_ID = KPI.KPI_TYPE_ID "
			"GROUP BY DATE_FORMAT (SNAPSHOT_D, '%Y') "
			"ORDER BY 'Time';";
	dims = vector<Dimension<string> >();
	_adapter.getResult(sql, dims);
}
void StageController::stage2(vector<Dimension<string> > & dims) {
	string sql =
			"SELECT DATE_FORMAT (SNAPSHOT_D, '%M') as 'Time', DATE_FORMAT (SNAPSHOT_D, '%Y') as 'Year', SUM(ACCT_KPI_TYPE_TXN_VAL) as 'Value' "
					"FROM BDC_TXN_FACT_MA_MORE base, BDC_KPI_DIM_MORE KPI "
					"WHERE base.KPI_TYPE_ID = KPI.KPI_TYPE_ID AND SNAPSHOT_D >= \"2016-01-01\" AND SNAPSHOT_D <= \"2016-12-31\" "
					"GROUP BY DATE_FORMAT (SNAPSHOT_D, '%Y%M') "
					"ORDER BY DATE_FORMAT (SNAPSHOT_D,  '%m'); ";
	dims = vector<Dimension<string> >();
	_adapter.getResult(sql, dims);
}

void StageController::stage3(vector<Dimension<string> > & dims) {
	string sql =
			"SELECT DATE_FORMAT (SNAPSHOT_D, '%Y') as 'Time', KPI_BUSINESS_NM as 'Business', SUM(ACCT_KPI_TYPE_TXN_VAL) as 'Value' "
					"FROM BDC_TXN_FACT_MA_MORE base, BDC_KPI_DIM_MORE kpi "
					"WHERE base.KPI_TYPE_ID = kpi.KPI_TYPE_ID "
					"AND KPI_BUSINESS_NM = 'New_money' "
					"GROUP BY DATE_FORMAT (SNAPSHOT_D, '%Y'), KPI_BUSINESS_NM "
					"ORDER BY 'Time';";
	dims = vector<Dimension<string> >();
	_adapter.getResult(sql, dims);

}
void StageController::stage4(vector<Dimension<string> > & dims) {
	string sql = "SELECT KPI_CATEGORY_COARSE_X as 'Money_Category',"
			"DATE_FORMAT (SNAPSHOT_D,  '%Y') as 'Time',"
			"KPI_BUSINESS_NM as 'Business',"
			"MAX(ACCT_KPI_TYPE_TXN_VAL) as 'Value' "
			"FROM BDC_TXN_FACT_MA_MORE as base, BDC_KPI_DIM_MORE as kpi "
			"WHERE base.KPI_TYPE_ID = kpi.KPI_TYPE_ID "
			"AND KPI_BUSINESS_NM = 'New_money' "
			"GROUP BY DATE_FORMAT (SNAPSHOT_D,'%Y'), KPI_CATEGORY_COARSE_X "
			"ORDER BY 'Time';";
	dims = vector<Dimension<string> >();
	_adapter.getResult(sql, dims);
}
void StageController::stage5(vector<Dimension<string> > & dims) {
	string sql = "SELECT AVG(ACCT_KPI_TYPE_TXN_VAL) as 'Value',"
			"DATE_FORMAT (SNAPSHOT_D,  '%M') as 'Time',"
			"REG_ABBREV_C as 'Account_Type',"
			"DATE_FORMAT (SNAPSHOT_D,  '%Y') as 'Year' "
			"FROM BDC_TXN_FACT_MA_MORE base, BDC_KPI_DIM_MORE kpi, BDC_ACCOUNT_MINI_DIM mini_dim "
			"WHERE base.KPI_TYPE_ID = kpi.KPI_TYPE_ID "
			"AND mini_dim.ACCT_MINI_DIM_ID = base.ACCT_MINI_DIM_ID "
			"AND REG_ABBREV_C='IRA' "
			"AND KPI_BUSINESS_NM = 'New_money' "
			"AND SNAPSHOT_D >= '2017-01-01' AND SNAPSHOT_D <= '2017-12-31' "
			"GROUP BY DATE_FORMAT (SNAPSHOT_D, '%M') "
			"ORDER BY DATE_FORMAT (SNAPSHOT_D, '%m') ;";
	dims = vector<Dimension<string> >();
	_adapter.getResult(sql, dims);

}

void StageController::stage6(vector<Dimension<string> > & dims) {
	string sql = "SELECT "
			"AGE_BKT as 'Age',"
			"DATE_FORMAT (SNAPSHOT_D, '%Y') as 'Time',"
			"SUM(ACCT_KPI_TYPE_TXN_VAL) as 'Value',"
			"KPI_BUSINESS_NM as 'Business',"
			"KPI_CATEGORY_COARSE_X as 'Money_Category'"
			"FROM BDC_TXN_FACT_MA_MORE base,BDC_KPI_DIM kpi, BDC_HOUSEHOLD_DEMOG demog,"
			"BDC_INDIVIDUAL_MINI_DIM indi "
			"WHERE     base.KPI_TYPE_ID = kpi.KPI_TYPE_ID "
			"AND base.HH_DEMOG_ID = demog.HH_DEMOG_ID "
			"AND KPI_BUSINESS_NM = 'New_money' "
			"AND KPI_CATEGORY_COARSE_X ='Retirement' "
			"AND base.IP_MINI_DIM_ID = indi.IP_MINI_DIM_ID "
			"GROUP BY DATE_FORMAT (SNAPSHOT_D, '%Y'), AGE_BKT "
			"ORDER BY AGE_BKT,DATE_FORMAT (SNAPSHOT_D, '%Y');";
	dims = vector<Dimension<string> >();
	_adapter.getResult(sql, dims);

}

void StageController::stage7(vector<Dimension<string> > & dims) {
	string sql = "SELECT "
		"BRANCH_REGION_X as 'Region',"
		//"IN_RADIUS_BRANCH_NM as 'Region_Branch',"
		"DATE_FORMAT (SNAPSHOT_D, '%Y') as 'Time',"
		"SUM(ACCT_KPI_TYPE_TXN_VAL) as 'Value',"
		"KPI_CATEGORY_COARSE_X as 'Money_Category', "
		"KPI_BUSINESS_NM as 'Business'"
		"FROM BDC_TXN_FACT_MA_MORE base,"
		"BDC_KPI_DIM_MORE kpi,"
		"BDC_HOUSEHOLD_DEMOG demog "
		"WHERE base.KPI_TYPE_ID = kpi.KPI_TYPE_ID "
		"AND base.HH_DEMOG_ID = demog.HH_DEMOG_ID "
		"AND KPI_BUSINESS_NM = 'New_money' "
		//"AND KPI_CATEGORY_COARSE_X ='Retirement' "
		//"AND SNAPSHOT_D >= '2014-01-01' AND SNAPSHOT_D <= '2016-12-31' "
		"GROUP BY DATE_FORMAT (SNAPSHOT_D, '%Y'), BRANCH_REGION_X, KPI_CATEGORY_COARSE_X;"; // , IN_RADIUS_BRANCH_NM; ";

	dims = vector<Dimension<string> >();
	_adapter.getResult(sql, dims);

}

void StageController::stage8(vector<Dimension<string> > & dims) {
	string sql = "";
	dims = vector<Dimension<string> >();
	_adapter.getResult(sql, dims);

}

void StageController::computeValueArray(vector<Dimension<string> > & dims, Array3D & arr) {
	cout << "----in computeValueArray" << endl;
	Dimension<string> values;
	vector<Dimension<string> > dimsRefined;

	for (int i = 0; i < 4; i++) {
		if (i < dims.size() && dims[i].getName().compare("Value") != 0) {
			dimsRefined.push_back(dims[i]);
		} else if (i < dims.size() && dims[i].getName().compare("Value") == 0){
			values = dims[i];
		} else {
			Dimension<string> s("Space Holder", "BIG BROTHER IS WATCHING YOU");
			dimsRefined.push_back(s);
		}
	}
	int X = dimsRefined[0].getNonRepSize();
	int Y = dimsRefined[1].getNonRepSize();
	int Z = dimsRefined[2].getNonRepSize();
	std::cout << "----" << X << "," << Y << "," << Z << std::endl;
	arr.resize(boost::extents[X][Y][Z]);
	int index = 0;

	for (int xi = 0; xi < X; xi++) {
		for (int yi = 0; yi < Y; yi++) {
			for (int zi = 0; zi < Z; zi++) {
					std::string str = ""; int f = 1;
					values.getValueAt(index, str, f);
				if ((Y == 1 && Z == 1 && yi == 0 && zi == 0)|| (Y != 1 && Z == 1 && zi == 0) || (Y != 1 && Z != 1)) {
					if (f) {
						arr[xi][yi][zi] = atof(str.c_str());
					}
					else {
						arr[xi][yi][zi] = -1;
					}
					index++;

				} else {
					arr[xi][yi][zi] = -1;
				}

			}
		}
	}
	/*
	 * double check the values in array
	 */
	// for (int xi = 0; xi < X; xi++) {
	// 	for (int yi = 0; yi < Y; yi++) {
	// 		for (int zi = 0; zi < Z; zi++) {
	// 			std::cout << arr[xi][yi][zi] << " ";
	// 		}
	// 	}
	// 	std::cout << std::endl;

	// }
	dims = dimsRefined;
	// cout << "----end computeValueArray" << endl;
}
