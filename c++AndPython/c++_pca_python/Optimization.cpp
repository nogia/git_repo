/*
 * Optimization.cpp
 *
 *  Created on: May 19, 2016
 *      Author: inna
 */

#include "Optimization.h"

namespace NDUV
{

	Optimization::Optimization() {
		// TODO Auto-generated constructor stub

	}

	Optimization::~Optimization() {
		// TODO Auto-generated destructor stub
	}
	bool Optimization::operator()(const  Optimization a,const  Optimization b)const
	{

                if( abs(a.RMSGAVERAGE) == abs(b.RMSGAVERAGE))
                {
                    return abs(a.meanCentralResidualAverage) < abs(b.meanCentralResidualAverage);
                }

                return  abs(a.RMSGAVERAGE) < abs(b.RMSGAVERAGE);
	}
    void Optimization::print()
    {
         cout << "##################################################################"<< endl;
        // error.print("Decomposition Residual =");
        // eigvalues.print("Eig values matrix =");
         cout << endl;
         cout  << "PCA = ["             << setw(2) << numberOfPCA                   <<
                  "] RMS = ["           << setw(4) << RMSGAVERAGE                   <<
                  "]  meanCenRes=["     << setw(4) << meanCentralResidualAverage    <<
                  "]  RealErFunc=["     << setw(4) << RealErrorFunction_i           <<
                  "]  MalinInd=["       << setw(4) << MalinowskiIndicator_i         <<
                  "]  TPV=["            << setw(4) << TPV                           <<
                  "]"                                                               <<
         endl;

    }
    void Optimization::CalculateOptimizationStatistic(mat ieigvalues,int numberOfSamples,int numberOfVariables,int npca,mat ierror)
    {
        error = ierror;
        eigvalues = ieigvalues;
        SumOfEigValues = 0;
        for(int i=0;i<(int)eigvalues.n_rows;i++)
        {
            for(int j=0;j< (int)eigvalues.n_cols;j++)
            {
                SumOfEigValues = SumOfEigValues + eigvalues(i,j);
            }
        }

        int d1 = min(numberOfSamples,numberOfVariables);
        int d2 = max(numberOfSamples,numberOfVariables);

        RealErrorFunction_i = pow(SumOfEigValues,0.5) / ((d1 - 1)*(d2 - npca));

    }
} /* namespace NDUV */


