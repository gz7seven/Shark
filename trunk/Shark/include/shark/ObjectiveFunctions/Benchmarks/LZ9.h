//===========================================================================
/*!
* \brief Multi-objective optimization benchmark function LZ9.
*
*  The function is described in
*
* H. Li and Q. Zhang. 
* Multiobjective Optimization Problems with Complicated Pareto Sets, MOEA/D and NSGA-II, 
* IEEE Trans on Evolutionary Computation, 2(12):284-302, April 2009. 
*
* <BR><HR>
* This file is part of Shark. This library is free software;
* you can redistribute it and/or modify it under the terms of the
* GNU General Public License as published by the Free Software
* Foundation; either version 3, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this library; if not, see <http://www.gnu.org/licenses/>.
*/
//===========================================================================
#ifndef SHARK_OBJECTIVEFUNCTIONS_BENCHMARK_LZ9_H
#define SHARK_OBJECTIVEFUNCTIONS_BENCHMARK_LZ9_H

#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <shark/ObjectiveFunctions/BoxConstraintHandler.h>

namespace shark {
struct LZ9 : public MultiObjectiveFunction
{	
	LZ9(std::size_t numVariables = 0) : m_handler(SearchPointType(numVariables,0),SearchPointType(numVariables,1) ){
		announceConstraintHandler(&m_handler);
		m_name="LZ9";
	}
	
	std::size_t numberOfObjectives()const{
		return 2;
	}
	
	std::size_t numberOfVariables()const{
		return m_handler.dimensions();
	}
	
	bool hasScalableDimensionality()const{
		return true;
	}

	/// \brief Adjusts the number of variables if the function is scalable.
	/// \param [in] numberOfVariables The new dimension.
	void setNumberOfVariables( std::size_t numberOfVariables ){
		m_handler.setBounds(
			SearchPointType(numberOfVariables,0),
			SearchPointType(numberOfVariables,1)
		);
	}

	ResultType eval( const SearchPointType & x ) const {
		m_evaluationCounter++;

		ResultType value( numberOfObjectives() );

		unsigned int counter1 = 0, counter2 = 0;
		for( unsigned int i = 1; i < x.size(); i++ ) {
			if( i % 2 == 0 ) {
				counter2++;
				value[1] += sqr( x(i) - ::sin( 6 * M_PI * x( 0 ) + i*M_PI/x.size() ) );
			} else {
				counter1++;
				value[0] += sqr( x(i) - ::sin( 6 * M_PI * x( 0 ) + i*M_PI/x.size() ) );
			}
		}

		value[0] *= 2./counter1;
		value[0] += x( 0 );

		value[1] *= 2./counter2;
		value[1] += 1 - x( 0 ) * x( 0 );

		return( value );
	}
private:
	BoxConstraintHandler<SearchPointType> m_handler;
};

ANNOUNCE_MULTI_OBJECTIVE_FUNCTION( LZ9, shark::moo::RealValuedObjectiveFunctionFactory );
}
#endif
