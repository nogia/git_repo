/*
 * PCAComponent.h
 *
 *  Created on: May 3, 2016
 *      Author: inna
 */

#ifndef PCACOMPONENT_H_
#define PCACOMPONENT_H_

#include "ProjConstants.h"

namespace NDUV {

class PCAComponent {
    friend class Statistic;
	public:
		PCAComponent();
        PCAComponent(Constituents name,int index);
		void print();
		virtual ~PCAComponent();

    private:
        Constituents m_name;                  // name  for example NO2 or other
        int    m_index;                 // index = sample number
        int    m_modelNumber;           // Defined by Number Of PCA Selected
		mat m_Eerror;                 // [1 x f] = row
		mat m_Feigenvector;           // [f x 1] = column
		mat m_Sscore;                 // [1 x f] = row
        mat eigvalues;
		mat m_Aintensity;             // [1 x f] = m_Sscore[1 x f] * m_Feigenvector[f x 1] + m_Eerror[1 x f]   1 row for one sample
        mat m_OriginalSpectra;
        mat sumOfSpectraPCA;
        mat m_Cconstitute;             // [f x 1] = m_BconstituteCoefficient[f x f] * m_Sscore'[f x 1] = [f x 1] // 1 row for each constitute

                                      //          = m_BconstituteCoefficient[f x f] * (m_Aintensity[f x 1] * m_Feigenvector[1 x 1]) = [f x 1]

        mat m_BconstituteCoefficient; // [f x f] =   m_Cconstitute[f x 1] * m_Sscore[1 x f] * (m_Sscore'[f x 1] * m_Sscore[1 x f)-1 = [f x f]

        mat m_OriginalConcentrations; // [f x 1]

        vector<mat> m_PrincipalComponents;

};


} /* namespace NDUV */

#endif /* PCACOMPONENT_H_ */
