/*******************************************************************
*
*  DESCRIPTION: class AdministradorLugares
*
*  AUTHOR: Federico Juan Dellasoppa
*
*  EMAIL: mailto://fdellaso@dc.uba.ar
*
*  DATE: 29/9/2003
*
*******************************************************************/

/** include files **/
#include "admlug.h"        // base header
#include "message.h"       // class InternalMessage
#include "mainsimu.h"      // class Simulator
#include "except.h"        // class InvalidMessageException
#include "constpiz.h"      // constants

/*******************************************************************
* Function Name: AdministradorLugares
* Description: constructor
********************************************************************/
AdministradorLugares::AdministradorLugares( const string &name )
: Atomic( name )
, inPizzero( addInputPort( "inPizzero" ) )
, outPizzero( addOutputPort( "outPizzero" ) )
, inLugar1( addInputPort( "inLugar1" ) )
, outLugar1( addOutputPort( "outLugar1" ) )
, inLugar2( addInputPort( "inLugar2" ) )
, outLugar2( addOutputPort( "outLugar2" ) )
, inLugar3( addInputPort( "inLugar3" ) )
, outLugar3( addOutputPort( "outLugar3" ) )
, inLugar4( addInputPort( "inLugar4" ) )
, outLugar4( addOutputPort( "outLugar4" ) )
, inLugar5( addInputPort( "inLugar5" ) )
, outLugar5( addOutputPort( "outLugar5" ) )
, inLugar6( addInputPort( "inLugar6" ) )
, outLugar6( addOutputPort( "outLugar6" ) )
, inLugar7( addInputPort( "inLugar7" ) )
, outLugar7( addOutputPort( "outLugar7" ) )
, inLugar8( addInputPort( "inLugar8" ) )
, outLugar8( addOutputPort( "outLugar8" ) )
, inLugar9( addInputPort( "inLugar9" ) )
, outLugar9( addOutputPort( "outLugar9" ) )
, inLugar10( addInputPort( "inLugar10" ) )
, outLugar10( addOutputPort( "outLugar10" ) )
{
}

/*******************************************************************
* Function Name: initFunction
* Description:
********************************************************************/
Model &AdministradorLugares::initFunction()
{
        int i;
        for (i = 0; i < 10; i++)
        {
                ocupado[i] = 0;
                listas[i] = 0;
        }
        pizza = 0;
        hayLugar = 0;
        hayLista = 0;
        lugar = 1.0;
        lista = 0.0;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &AdministradorLugares::externalFunction( const ExternalMessage &msg )
{
        int i;

        if ( msg.port() == inPizzero )
        {
                int mensaje = (int)msg.value();

                //      Si es un pedido
                if ( (1 <= mensaje && mensaje <= 3) ||
                        (11 <= mensaje && mensaje <= 13) )
                {
                        int ocupe = 0;
                        for(i = 0; i < 10 && !ocupe; i++)
                        {
                                if (!ocupado[i])
                                {
                                        ocupe = 1;
                                        ocupado[i] = mensaje;
                                        pizza = i + 1;
                                }
                        }

                        holdIn( active, Time::Zero );
                }

                else if ( mensaje == MSG_HAY_LUGAR )
                {
                        hayLugar = 1;

                        lugar = 0.0;
                        for (i = 0; i < 10; i++)
                        {
                                if (!ocupado[i])
                                        lugar = 1.0;
                        }

                        holdIn( active, Time::Zero );
                }

                else if ( mensaje == MSG_HAY_LISTA )
                {
                        hayLista = 1;

                        lista = 0.0;
                        int desocupe = 0;
                        for (i = 0; i < 10 && !desocupe; i++)
                        {
                                if (listas[i])
                                {
                                        //      Si hay una pizza lista,
                                        //      la saca y libera el lugar
                                        desocupe = 1;
                                        listas[i] = 0;
                                        lista = (Value)ocupado[i];
                                        ocupado[i] = 0;
                                }
                        }

                        holdIn( active, Time::Zero );
                }
                
                else
                {
                        MTHROW( InvalidMessageException() );
                }
                
        }//     if ( msg.port() == inPizzero )

        if ( msg.port() == inLugar1 )
        {
                listas[0] = 1;
        }
        if ( msg.port() == inLugar2 )
        {
                listas[1] = 1;
        }
        if ( msg.port() == inLugar3 )
        {
                listas[2] = 1;
        }
        if ( msg.port() == inLugar4 )
        {
                listas[3] = 1;
        }
        if ( msg.port() == inLugar5 )
        {
                listas[4] = 1;
        }
        if ( msg.port() == inLugar6 )
        {
                listas[5] = 1;
        }
        if ( msg.port() == inLugar7 )
        {
                listas[6] = 1;
        }
        if ( msg.port() == inLugar8 )
        {
                listas[7] = 1;
        }
        if ( msg.port() == inLugar9 )
        {
                listas[8] = 1;
        }
        if ( msg.port() == inLugar10 )
        {
                listas[9] = 1;
        }

	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &AdministradorLugares::internalFunction( const InternalMessage & )
{
        if ( pizza )
                pizza = 0;
        else if ( hayLugar )
                hayLugar = 0;
        else if ( hayLista )
                hayLista = 0;

        passivate();

	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &AdministradorLugares::outputFunction( const InternalMessage &msg )
{
        if ( pizza )
        {
                if ( pizza == 1 )
                        sendOutput( msg.time(), outLugar1, 1.0 );
                if ( pizza == 2 )
                        sendOutput( msg.time(), outLugar2, 1.0 );
                if ( pizza == 3 )
                        sendOutput( msg.time(), outLugar3, 1.0 );
                if ( pizza == 4 )
                        sendOutput( msg.time(), outLugar4, 1.0 );
                if ( pizza == 5 )
                        sendOutput( msg.time(), outLugar5, 1.0 );
                if ( pizza == 6 )
                        sendOutput( msg.time(), outLugar6, 1.0 );
                if ( pizza == 7 )
                        sendOutput( msg.time(), outLugar7, 1.0 );
                if ( pizza == 8 )
                        sendOutput( msg.time(), outLugar8, 1.0 );
                if ( pizza == 9 )
                        sendOutput( msg.time(), outLugar9, 1.0 );
                if ( pizza == 10 )
                        sendOutput( msg.time(), outLugar10, 1.0 );
        }//     if ( pizza )
        else if ( hayLugar )
        {
                sendOutput( msg.time(), outPizzero, lugar );
        }
        else if ( hayLista )
        {
                sendOutput( msg.time(), outPizzero, lista );
        }

        return *this ;
}

/*******************************************************************
* Function Name: ~AdministradorLugares
* Description: destructor
********************************************************************/
AdministradorLugares::~AdministradorLugares()
{
}
