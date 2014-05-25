#ifndef __EvolutionParameters_hh__
#define __EvolutionParameters_hh__

#include <string>
#include <iostream>


//using namespace std;

/**
 * EvolutionParameters
 *
 * Author: Kevin Peter Hickerson
 * Created: Sun Apr 20 17:11:14 PDT 2014
 */
template <class real, int n> 
class EvolutionParameters
{
	//public: static const double Ydefault = 0;
	public: static const unsigned nnuc = n;
	public: static const unsigned nvar = n + 3;

	public: real T9;	
	public: real hv;
	public: real phie;
	//public: real Y[nnuc+1];
	public: real v[nvar+1];
	public: real* const Y; 

	public: EvolutionParameters() :
		T9(0),
		hv(0),
		phie(0),
		Y(&(v[4]))
	{
		//verbose("Default constructor for EvolutionParameters");
		for (int i = 0; i <= 3; i++)
			v[i] = 0;
		for (int i = 1; i <= nnuc; i++)
			v[i] = 0;							/// Default abundance.
		//Y = &(v[4]);
		printf("Default: Y address is: %p\n", Y);
	}

	public : EvolutionParameters(const EvolutionParameters & copy) :
		T9(copy.T9),
		hv(copy.hv),
		phie(copy.phie),
		Y(&(v[4]))
	{
		//verbose("Copy constructor for EvolutionParameters");
		for (int i = 0; i <= nnuc; i++)			/// Copy abundances.
			v[i] = copy.v[i];				
		//Y = &(v[4]);
		printf("Copy: Y address is: %p\n", Y);
	}

	public : ~EvolutionParameters()				/// Does nothing.
	{
		//verbose("Empty destructor for EvolutionParameters");
		printf("Empty destructor for EvolutionParameters\n");
	}
	
	public : EvolutionParameters & operator = (const EvolutionParameters & other)
    {
		//verbose("Copy operator for EvolutionParameters");
        if (this != &other) // protect against invalid self-assignment
        {
			T9 = other.T9;
			hv = other.hv;
			phie = other.phie;
			for (int i = 0; i <= nnuc; i++)		/// Copy abundances.
				v[i] = other.v[i];			
			//Y = &(v[4]);
			printf("=: Y address is: %p\n", Y);
        }
        return *this;
    }
};

#endif
