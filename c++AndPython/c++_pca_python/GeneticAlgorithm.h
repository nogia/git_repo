/*
 * GeneticAlgorithm.h
 *
 *  Created on: Sep 19, 2016
 *      Author: inna
 */

#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_
#include "Statistics.h"
#include "Test.h"
namespace NDUV
{
    class Test;
    class Chromosome
	{
       friend class GeneticAlgorithm;
       friend class Test;
       private:
        int seqlength;

		vector<int> binsequence;
		vector<int> sequence;
		Stat stat;

        void print(int fitnessrank=-1,int generation = 0,int populationsize = 0,bool printvariables = false);

       public:
        ~Chromosome();
		bool operator()(const Chromosome a,const Chromosome b)const;
        bool operator==(const  Chromosome b)const
        {
            if(stat ==  b.stat && binsequence == b.binsequence && sequence == b.sequence && seqlength == b.seqlength )
            {
                return true;
            }
            else
            {
                 return  false;
            }
        }

	};
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class GeneticAlgorithm
	{
       friend class Test;

       private:

	      int m_length;
          int m_populationSize;
          int m_start;
          int m_end;

          int m_generation;
          int m_generationFitnessCurrentRank;
          bool m_stop;

          int m_blocksize;
          int m_maxNumberOfGenerations;

          pair<double,double> m_fitness;
          vector<int> m_found;
          vector<pair<double,double>> m_fitnesslevels;
          vector<vector<Chromosome>> m_bestFit;
	      vector<Chromosome> chromosomes;
          vector<int> m_sequence;

          GeneticAlgorithm
          (
                  vector<int> sequence,int length = 0,int size = 0,int start = 0,int end = 0,
                  pair<double,double> fitness = pair<double,double>(1000000,1000000),
                  int blocksize = 1,int maxNumberOfGenerations = 20

          );
	     ~GeneticAlgorithm();
          vector<int> CreateSequence();

	      void print();
          bool CheckForDuplicates();
          void EvaluatePopulation(const Test& test);
	      void CreateNewPopulation();
          Chromosome CreteMutation(Chromosome value);
          Chromosome CreateCrossOver(pair<Chromosome,Chromosome> parents,int isplit =-1);
          pair<Chromosome,Chromosome> selectParents();
          void InitialiazePopulation();
          void RunGA(const Test& test);

	};

} /* namespace NDUV */

#endif /* GENETICALGORITHM_H_ */
