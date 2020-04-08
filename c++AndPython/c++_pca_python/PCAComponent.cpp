/*
 * PCAComponent.cpp
 *
 *  Created on: May 3, 2016
 *      Author: inna
 */

#include "PCAComponent.h"

namespace NDUV {

    PCAComponent::PCAComponent() : m_name(UNKNOWN), m_index(0)
	{
		// TODO Auto-generated constructor stub

	}

	PCAComponent::~PCAComponent() {
		// TODO Auto-generated destructor stub
	}

    PCAComponent::PCAComponent(Constituents name,int index) : m_name(name), m_index(index)
	{

	}
    void PCAComponent::print()
    {

           cout << "##########          Name = " << m_name << " index = "<< m_index <<" model = "<< m_modelNumber<<"          ##########"<< endl;


           m_Feigenvector.print("Eigenvector = ");
           m_BconstituteCoefficient.print("PCR Coefficients = ");
           m_Cconstitute.print("m_Cconstitute Value = ");
           m_OriginalConcentrations.print("m_OriginalConcentrations = ");
           eigvalues.print("Eigen Values = ");

           for(int i=0;i< (int)m_PrincipalComponents.size();i++)
           {
              cout  << "Principal Component = [ " + to_string(i+1) << " ]";
              m_PrincipalComponents[i].print();
           }

           m_Sscore.print("Score");
           //cout << "New Spectrum             = ";
           //m_Aintensity.print();
           //cout << "] " << endl;
           cout << "SUM OF PCA SPECRUM       = ";
           sumOfSpectraPCA.print();
           //cout << "] "<< endl;
           //cout << "Residual                   = ";
           //m_Eerror.print();
           cout << "SCORE1                     = ";
           m_OriginalSpectra.print();

           cout << "End " << endl;

	}

} /* namespace NDUV */
