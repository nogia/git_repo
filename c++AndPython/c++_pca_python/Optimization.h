/*
 * Optimization.h
 *
 *  Created on: May 19, 2016
 *      Author: inna
 */

#ifndef OPTIMIZATION_H_
#define OPTIMIZATION_H_

#include "ProjConstants.h"

namespace NDUV {

class Optimization {
public:
	friend class Statistic;
	Optimization();
   ~Optimization();
	bool operator()(const  Optimization a,const  Optimization b)const;

    int getIndex();
	void print();

private:
       mat scoreWithResidual;
       mat meani;
       mat meanCentralResidual;
       mat mahalanobis;
       mat Di2;
       mat RMSG;
       mat eigvalues;
       mat error;
       double RealErrorFunction_i;
       double MalinowskiIndicator_i;
       double SumOfEigValues;
       double TPV;
      int numberOfPCA;
      int index;

      double meanCentralResidualAverage;
      double RMSGAVERAGE;
      void CalculateOptimizationStatistic
      (
              mat eigvalues,int numberOfSamples,int numberOfVariables,int npca,
              mat error
      );

};

} /* namespace NDUV */

#endif /* OPTIMIZATION_H_ */
