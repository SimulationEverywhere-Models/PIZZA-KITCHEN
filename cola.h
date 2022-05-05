/*******************************************************************
*
*  DESCRIPTION: class Cola
*
*  AUTHOR: Federico Juan Dellasoppa
*
*  EMAIL: mailto://fdellaso@dc.uba.ar
*
*  DATE: 29/9/2003
*
*******************************************************************/

#ifndef __COLA_H
#define __COLA_H

/** include files **/
#include <list>
#include "atomic.h"     // class Atomic

/** forward declarations **/

/** declarations **/
class Cola : public Atomic
{
public:
	Cola( const string &name = "Cola" );				  // Default constructor

	~Cola();

	virtual string className() const
		{return "Cola";}

protected:
	Model &initFunction() ;

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
        const Port &in;
        const Port &dame;
	Port &out;

        typedef list<Value> ElementList ;
	ElementList elementos ;

};	// class Cola


#endif   //__COLA_H
 