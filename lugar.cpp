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

/** include files **/
#include "lugar.h"         // base header
#include "message.h"       // class InternalMessage
#include "mainsimu.h"      // class Simulator
#include "except.h"        // class InvalidMessageException
#include "constpiz.h"      // constants
#include "realfunc.h"      // Real Functions

/*******************************************************************
* Function Name: Lugar
* Description: constructor
********************************************************************/
Lugar::Lugar( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, out( addOutputPort( "out" ) )
{
}

/*******************************************************************
* Function Name: initFunction
* Description:
********************************************************************/
Model &Lugar::initFunction()
{
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Lugar::externalFunction( const ExternalMessage &msg )
{
        Value segs = randInt( Real(60.0) ).value() ;
        holdIn( active, Time(0 , 7 , (int)segs , 0) );
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Lugar::internalFunction( const InternalMessage & )
{
        passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Lugar::outputFunction( const InternalMessage &msg )
{
        sendOutput( msg.time(), out, (Value)MSG_LISTA );
        return *this ;
}

/*******************************************************************
* Function Name: ~Lugar
* Description: destructor
********************************************************************/
Lugar::~Lugar()
{
}
 