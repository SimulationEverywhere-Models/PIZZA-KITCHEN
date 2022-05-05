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

/** include files **/
#include "cola.h"          // base header
#include "message.h"       // class InternalMessage
#include "mainsimu.h"      // class Simulator
#include "except.h"        // class InvalidMessageException
#include "constpiz.h"      // constants

/*******************************************************************
* Function Name: Cola
* Description: constructor
********************************************************************/
Cola::Cola( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, dame( addInputPort( "dame" ) )
, out( addOutputPort( "out" ) )
{
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Cola::initFunction()
{
        elementos.erase( elementos.begin(), elementos.end() ) ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Cola::externalFunction( const ExternalMessage &msg )
{
        if( msg.port() == in )
	{
		elementos.push_back( msg.value() ) ;
	}
        
        else if( msg.port() == dame && !elementos.empty() )
	{
                //      Envio pedido
                holdIn( active, Time(0 , 0 , 0 , 50) );
	}

	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Cola::internalFunction( const InternalMessage & )
{
        elementos.pop_front() ;
        passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Cola::outputFunction( const InternalMessage &msg )
{
        sendOutput( msg.time(), out, elementos.front() ) ;
        return *this ;
}

/*******************************************************************
* Function Name: ~Cola
* Description: destructor
********************************************************************/
Cola::~Cola()
{
}
 