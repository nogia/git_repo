/*
 * GeneticAlgorithm.cpp
 *
 *  Created on: Sep 19, 2016
 *      Author: inna
 */

#include "GeneticAlgorithm.h"

namespace NDUV
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief GeneticAlgorithm::GeneticAlgorithm
    /// \param length
    /// \param size
    /// \param fitness
    /// \param maxcount
    ///
    GeneticAlgorithm::GeneticAlgorithm
    (
        vector<int> sequence,int length ,int size ,int start,int end, pair<double,double> fitness,int blocksize,int maxNumberOfGenerations ) :

        m_sequence(sequence),
        m_length(length),m_populationSize(size),
        m_start(start),m_end(end),
        m_fitness(fitness),m_generationFitnessCurrentRank(-1),m_generation(-1),
        m_fitnesslevels
        (
          {
            { 0              ,                          m_fitness.first    },
            { m_fitness.first,(m_fitness.second + m_fitness.first ) / 2    },
            {( m_fitness.second + m_fitness.first ) / 2 , m_fitness.second },
            { m_fitness.second ,-1.00                                      },
          }
        ),
        m_bestFit((int) m_fitnesslevels.size()),m_stop(false),m_found(4,0),
        m_blocksize(blocksize),
        m_maxNumberOfGenerations(maxNumberOfGenerations)
	{
        int istart,iend;
        if((int) m_sequence.size() > 0)
        {
            std::sort(m_sequence.begin(),m_sequence.end());
            m_length = (int)m_sequence.size();
            m_start =  m_sequence[0];
            m_end = m_sequence[(int)m_sequence.size() - 1];
        }
        else
        {
            if(m_start >=0 && m_end >=0 && m_start<=m_end && m_end - m_start <= m_length && end <= m_length)
            {
                m_length =  m_end - m_start;
                istart = m_start;iend = m_end;
            }
            else
            {
               istart = 0;iend = m_length;
            }
            for(int i = istart;i < iend;i++)
            {
                m_sequence.push_back(i);
            }
        }


         cout << "Start Initialize GA : "<< endl;
         for(int i=0;i < (int)m_fitnesslevels.size();i++)
         {
             cout << "LEVEL " << i << " = "<< m_fitnesslevels[i].first << " - "<< m_fitnesslevels[i].second << endl;
         }

         if(m_blocksize < 1)
         {
           m_blocksize = 1;
         }
         m_populationSize = std::min(  (double)m_populationSize, pow(2,std::ceil(double(m_sequence.size() / (double)m_blocksize)) ) - 1  );
         InitialiazePopulation();
         cout << "Finish Initialize GA : " << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief GeneticAlgorithm::~GeneticAlgorithm
    ///
	GeneticAlgorithm::~GeneticAlgorithm()
	{ 
        m_found.clear();
        m_fitnesslevels.clear();
        m_bestFit.clear();
        chromosomes.clear();
        m_sequence.clear();
	}
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief GeneticAlgorithm::print
    ///
	void GeneticAlgorithm::print()
	{
        cout << "Start Generation Number =  " << m_generation << endl;
	    for(auto  c: chromosomes)
	    {
			               c.print();
		}
       cout << "End Generation Number =  " << m_generation << endl;
	}
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief GeneticAlgorithm::CreateNewPopulation
    ///
	void GeneticAlgorithm::CreateNewPopulation()
	{
		pair<Chromosome,Chromosome> parents = selectParents();
        chromosomes.clear();
        for(int i =0;i < m_populationSize;i++)
		{
             Chromosome tempseqCrossOver;
             Chromosome tempseqMutation;
             bool dupCrossOver = false;
             bool dupMutation = false;
             tempseqCrossOver = CreateCrossOver(parents);

             int k;
             int count = 0;
             do
             {
                 tempseqMutation = CreteMutation(tempseqCrossOver);
                 for(auto c: chromosomes)
                 {
                      if(c.binsequence ==  tempseqMutation.binsequence)
                      {
                         dupMutation = true;
                         k = 0;//m_start;

                         do
                         {
                              dupMutation = false;

                              if(tempseqMutation.binsequence[k] == 0)
                                  tempseqMutation.binsequence[k] = 1;
                              else
                                  tempseqMutation.binsequence[k] = 0;
                              for(auto j: chromosomes)
                              {
                                   if(j.binsequence ==  tempseqMutation.binsequence)
                                   {
                                       dupMutation = true;
                                   }
                              }
                              k++;

                         }
                         while(dupMutation && k < (int)m_sequence.size()/*m_end*/);

                         if(dupMutation)
                         {
                            dupCrossOver = false;
                            k = 0;//m_start;
                            Chromosome temp = tempseqCrossOver;
                            do
                            {
                               tempseqCrossOver = CreateCrossOver(parents,k);

                               if(temp.binsequence ==  tempseqCrossOver.binsequence)
                               {
                                        dupCrossOver = true;
                               }
                               k++;

                            }
                            while(dupCrossOver && k < (int)m_sequence.size()/*m_end*/);
                         }
                         else
                             break;

                      }
                 }
                 count =0;
                 for(int x=0;x<(int)tempseqMutation.binsequence.size();x++)
                 {
                     count = count + tempseqMutation.binsequence[x];
                 }
                 if(count == 0)
                    dupMutation = true;
             }
             while(dupMutation );

             tempseqMutation.stat.RMSEAVERAGE = 1000000;
             tempseqMutation.sequence.clear();
             for (int n=0; n < (int)tempseqMutation.binsequence.size(); ++n)
             {
                 if( tempseqMutation.binsequence[n] == 1)
                 {
                     tempseqMutation.sequence.push_back(m_sequence[n]);
                 }
             }


             chromosomes.push_back(tempseqMutation);
		}
        if(CheckForDuplicates())
            return;

         m_generation++;

	}
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief GeneticAlgorithm::CreteMutation
    /// \param value
    /// \return
    ///
	Chromosome GeneticAlgorithm::CreteMutation(Chromosome value)
    {
		  Chromosome mutated = value;

          int mutategin = rand()%((int)m_sequence.size() + 1) ;
		  if(mutated.binsequence[mutategin] == 0)
		  {
		        mutated.binsequence[mutategin] = 1;
		  }
		  else if(mutated.binsequence[mutategin] == 1)
		  {
		        mutated.binsequence[mutategin] = 0;
		  }
		  mutated.sequence.clear();
          int count =0;
          for(int i =0;i < (int)mutated.binsequence.size();i++)
		  {

               count = count + mutated.binsequence[i];
		  }
          if(count == 0)
              mutated.binsequence[0]=1;
          for(int i =0;i < (int)mutated.binsequence.size();i++)
          {
              if(mutated.binsequence[i] == 1)
              {
                  mutated.sequence.push_back(m_sequence[i]);
              }
          }
          mutated.stat.RMSEAVERAGE = 1000000;
		  return mutated;
	}


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief GeneticAlgorithm::CreateCrossOver
    /// \param parents
    /// \return
    ///
    Chromosome GeneticAlgorithm::CreateCrossOver(pair<Chromosome,Chromosome> parents,int isplit )
    {
           int split;
           if(isplit < 0 || isplit < (int)m_sequence.size())
                split = rand()%((int)m_sequence.size() + 1) + 1 ;
           else
              split = isplit;
		   Chromosome crossover;
		   int i=0;

           for(;i < split;i++)
		   {
		        crossover.binsequence.push_back(parents.first.binsequence[i]);
		        if(crossover.binsequence[i] == 1)
		        {
                         crossover.sequence.push_back(m_sequence[i]);
		        }
		   }
           for(;i < (int)parents.second.binsequence.size();i++)
		   {
		       crossover.binsequence.push_back(parents.second.binsequence[i]);
		       if(crossover.binsequence[i] == 1)
		       {
                    crossover.sequence.push_back(m_sequence[i]);
		       }
		   }
		   crossover.seqlength = parents.first.binsequence.size();

           crossover.stat.RMSEAVERAGE = 1000000;

		   return crossover;
	}
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief GeneticAlgorithm::CreateSequence
    /// \return
    ///
     vector<int> GeneticAlgorithm::CreateSequence()
     {
         vector<int> seq;
         vector<int> tempseq;
         std::random_device rd;
         std::mt19937 gen(rd());
         std::uniform_int_distribution<> dis(0,1);
         int count =0;
         int length = std::ceil((int)m_sequence.size() /(double) m_blocksize) ;

         for (int n=0; n < length ; ++n)
         {
                       int value = dis(gen);
                       count = count + value;
                       tempseq.push_back(value);
         }
             if(count == 0)
                 tempseq[0]=1;
             seq = vector<int>(m_length,0);
             for(int j=0;j < (int)tempseq.size();j++)
             {
                for(int k=j * m_blocksize;k < min((j+1)*m_blocksize,m_length);k++)
                {
                     seq[k]= tempseq[j];
                }
             }

         return seq;
     }
     /////////////////////////////////////////////////////////////////////////////////////////////////////
     /// \brief GeneticAlgorithm::CheckForDuplicates
     /// \return
     ///
     bool GeneticAlgorithm::CheckForDuplicates()
     {
            bool dup=0;
            for(int i = 0;i < (int)chromosomes.size();i++)
            {
                for(int j = 0;j < (int)chromosomes.size();j++)
                if(i != j && chromosomes[i].binsequence == chromosomes[j].binsequence)
                {
                    cout << "Dup found in binary sequence : i = " << i << " j = "<< j << endl;
                    dup++;

                }
            }
            bool dup1=0;
            for(int i = 0;i < (int)chromosomes.size();i++)
            {
                for(int j = 0;j < (int)chromosomes.size();j++)
                if(i != j && chromosomes[i].sequence == chromosomes[j].sequence)
                {
                    cout << "Dup found in  sequence : i = " << i << " j = "<< j << endl;
                    dup1++;

                }
            }

            return dup != 0 || dup1 !=0;
     }
     ////////////////////////////////////////////////////////////////////////////////////////////////////
     /// \brief GeneticAlgorithm::InitialiazePopulation
     ///
     void GeneticAlgorithm::InitialiazePopulation()
     {
         int newlength = std::ceil(m_length /(double) m_blocksize) ;
         if(m_populationSize == pow(2,newlength) - 1 )
         {
             for(int p=0;p < m_populationSize;p++)
             {
                 int value = p+1;
                 Chromosome chromosome;
                 //chromosome.seqlength = newlength;
                 chromosome.stat.RMSEAVERAGE = 1000000;
                  vector<int> temp ;
                 for(int i =0;i < newlength;i++)
                 {
                         temp.push_back((value >> i) & 1);
                 }
                 chromosome.binsequence = vector<int>(m_length,0);
                 for(int j=0;j < (int)temp.size();j++)
                 {
                      for(int k=j * m_blocksize;k < min((j+1)*m_blocksize,m_length);k++)
                      {
                             chromosome.binsequence[k]= temp[j];
                      }
                 }

                 for (int n=0; n < (int)chromosome.binsequence.size(); ++n)
                 {
                     if( chromosome.binsequence[n] == 1)
                     {
                         chromosome.sequence.push_back(m_sequence[n]);
                     }
                 }
                 chromosomes.push_back(chromosome);
             }

         }
         else
         {
             for(int p=0;p < m_populationSize;p++)
             {
                          Chromosome chromosome;
                          chromosome.seqlength = m_length;
                          chromosome.stat.RMSEAVERAGE = 1000000;

                          bool dup = false;

                          do
                          {
                              chromosome.binsequence = CreateSequence();
                              for(auto i: chromosomes)
                              {
                                   if(i.binsequence ==  chromosome.binsequence)
                                   {
                                      dup = false;
                                      int k = 0;
                                      int a = k;
                                      do
                                      {
                                           dup = false;
                                           if(chromosome.binsequence[k] == 1)
                                               chromosome.binsequence[k] = 0;
                                           else
                                               chromosome.binsequence[k] = 1;
                                           for(auto j: chromosomes)
                                           {
                                                if(j.binsequence ==  chromosome.binsequence)
                                                {
                                                    dup = true;
                                                }
                                           }
                                           k++;
                                           if(k == (int)m_sequence.size())
                                           {
                                               k = ++a;
                                               a = k;
                                           }
                                      }
                                      while(dup && k < (int)m_sequence.size());


                                   }
                              }

                              int count =0;
                              for(int x=0;x<(int)chromosome.binsequence.size();x++)
                              {
                                  count = count + chromosome.binsequence[x];
                              }
                              if(count == 0)
                                 dup = true;
                          }
                          while(dup );

                          for (int n=0; n < (int)chromosome.binsequence.size(); ++n)
                          {
                              if( chromosome.binsequence[n] == 1)
                              {
                                  chromosome.sequence.push_back(m_sequence[n]);
                              }
                          }
                          chromosomes.push_back(chromosome);
                 }
         }

         if(CheckForDuplicates())
             return;

          m_generation = 0;
     }


     /////////////////////////////////////////////////////////////////////////////////////////////////////
     /// \brief GeneticAlgorithm::EvaluatePopulation
     /// \param test
     ///
    void GeneticAlgorithm::EvaluatePopulation(const Test& test)
    {
                    for(Chromosome &chrom: chromosomes)
		            {
                        Test cur_test = test;
                        cur_test.testVariablesPick(cur_test,chrom,m_fitness.second);
		            }
                    m_generationFitnessCurrentRank = -1;
                    if(chromosomes.size() > 0)
		            {
                        std::sort(chromosomes.begin(),chromosomes.end(),chromosomes[0]);
                       if(chromosomes.size() > 0)
                        {
                            m_generationFitnessCurrentRank = 3;
                            for(int i = 0;i < (int)m_fitnesslevels.size();i++)
                            {
                                if(chromosomes[0].stat.RMSEAVERAGE >= m_fitnesslevels[i].first && chromosomes[0].stat.RMSEAVERAGE < m_fitnesslevels[i].second)
                                {
                                    m_generationFitnessCurrentRank = i;
                                }
                            }
                            if( m_generationFitnessCurrentRank >=0)
                            {
                                vector<Chromosome>::iterator it;
                                do
                                {
                                    it = std::find(m_bestFit[m_generationFitnessCurrentRank].begin(),m_bestFit[m_generationFitnessCurrentRank].end(),chromosomes[0]);
                                    if(it == m_bestFit[m_generationFitnessCurrentRank].end() )
                                    {

                                       m_bestFit[m_generationFitnessCurrentRank].push_back(chromosomes[0]);
                                       break;
                                    }
                                    else
                                    {
                                         chromosomes.erase ( chromosomes.begin(), chromosomes.begin()+1);
                                    }
                                }
                                while(it != m_bestFit[m_generationFitnessCurrentRank].end() && chromosomes.size() > 0);
                                if(chromosomes.size() <=0)
                                {
                                     m_found[m_generationFitnessCurrentRank]++;
                                }
                                std::sort( m_bestFit[m_generationFitnessCurrentRank].begin(), m_bestFit[m_generationFitnessCurrentRank].end(),m_bestFit[m_generationFitnessCurrentRank][0]);
                            }

                            bool outvar = true;
                            if(m_generationFitnessCurrentRank == 0 || m_generationFitnessCurrentRank == 1)
                            {
                                outvar = true;
                            }

                            chromosomes[0].print( m_generationFitnessCurrentRank,m_generation,m_populationSize,outvar);
                            //chromosomes[1].print( m_generationFitnessCurrentRank,m_generation,m_populationSize,outvar);
                        }
		            }
                    vector<bool> cond =
                    {
                        m_generation >= (int)std::min( m_maxNumberOfGenerations,(int)pow(2,(double)m_length) - 1),
                        m_bestFit[0].size() > 0 ,
                        m_found[1] > 0,
                        m_found[2] > 0,
                        m_found[3] > 0,
                        pow(2,(double)m_length) - 1 ==  m_populationSize,

                    };
                     m_stop = false;
                    for(auto c: cond)
                    {
                        m_stop = m_stop || c;
                    }
                    if(m_stop )
                    {
                        cout << "Finished condition "<< endl;
                    }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief GeneticAlgorithm::selectParents
    /// \return
    ///
	pair<Chromosome,Chromosome> GeneticAlgorithm::selectParents()
    {
		           pair<Chromosome,Chromosome> result;
		           if(chromosomes.size()>0)
		           {
		               std::sort(chromosomes.begin(),chromosomes.end(),chromosomes[0]);
		               if(chromosomes.size()>1)
		                 {
		                     result.first = chromosomes[0];
		                     result.second = chromosomes[1];
		                 }
		           }
		           return result;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief GeneticAlgorithm::RunGA
    /// \param test
    ///
    void GeneticAlgorithm::RunGA(const Test& test)
	{
                   EvaluatePopulation(test);

                   while(!m_stop)
	 	           {
	 	               CreateNewPopulation();
                       EvaluatePopulation(test);
                       for(int i =0;i < (int)m_bestFit.size();i++)
                       {
                           if(m_bestFit[i].size() > 0)
                           {
                               if(i == 0)
                               {
                                   m_bestFit[i][0].print(0,m_generation,m_populationSize,true);
                               }
                               else
                               {
                                   int r = m_generation;

                                   if(r % 10 == 0 || m_stop)
                                   {
                                        m_bestFit[i][0].print(10,m_generation,m_populationSize,true);
                                        break;
                                   }
                               }
                           }
                       }
	 	           }
	}
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Chromosome::~Chromosome
    ///
    Chromosome::~Chromosome()
    {
        binsequence.clear();
        sequence.clear();
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Chromosome::operator ()
    /// \param a
    /// \param b
    /// \return
    ///
	bool Chromosome::operator()(const Chromosome a,const Chromosome b)const
	{
                return a.stat.RMSEAVERAGE < b.stat.RMSEAVERAGE;
	}
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Chromosome::print
    /// \param fitnessrank
    /// \param generation
    /// \param populationsize
    /// \param printvariables
    ///
    void Chromosome::print(int fitnessrank,int generation,int populationsize,bool printvariables)
	{
        cout << "Generation ="<< generation << " [ "<< endl;
       /* for(auto b: binsequence)
        {
            cout << b <<" ";
        }
        cout << endl;
        for(auto b: sequence)
        {
            cout << b <<" ";
        }
        cout << endl;*/
        stat.print(true,false);
        cout << "Generation ="<< generation << " ]" << endl;
        if(stat.variables.size() > 0)
          stat.printToFile("GeneticAlgorithm" + to_string(fitnessrank + 1) + ".txt",generation,stat.variables[0],stat.variables[stat.variables.size() -1],populationsize,printvariables);

	}
} /* namespace NDUV */
