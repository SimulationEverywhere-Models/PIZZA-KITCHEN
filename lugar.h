/*******************************************************************
*
*  DESCRIPTION: class Lugar
*
*  AUTHOR: Federico Juan Dellasoppa
*
*  EMAIL: mailto://fdellaso@dc.uba.ar
*
*  DATE: 29/9/2003
*
*******************************************************************/

#ifndef __LUGAR_H
#define __LUGAR_H

/** include files **/
#include "atomic.h"     // class Atomic

/** forward declarations **/

/** declarations **/
class Lugar : public Atomic
{
public:
	Lugar( const string &name = "Lugar" );          // Default constructor

	~Lugar();

	virtual string className() const
		{return "Lugar";}

protected:
	Model &initFunction() ;

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
        const Port &in;
	Port &out;

};	// class Lugar


#endif   //__LUGAR_H
