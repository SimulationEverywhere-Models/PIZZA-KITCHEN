/*******************************************************************
*
*  DESCRIPTION: class Pizzero
*
*  AUTHOR: Federico Juan Dellasoppa
*
*  EMAIL: mailto://fdellaso@dc.uba.ar
*
*  DATE: 29/9/2003
*
*******************************************************************/

/** include files **/
#include "pizzero.h"       // base header
#include "message.h"       // class InternalMessage
#include "mainsimu.h"      // class Simulator
#include "except.h"        // class InvalidMessageException
#include "constpiz.h"      // constants

/*******************************************************************
* Function Name: Pizzero
* Description: constructor
********************************************************************/
Pizzero::Pizzero( const string &name )
: Atomic( name )
, inPedidos( addInputPort( "inPedidos" ) )
, outPedidos( addOutputPort( "outPedidos" ) )
, inHorno( addInputPort( "inHorno" ) )
, outHorno( addOutputPort( "outHorno" ) )
, outSalida( addOutputPort( "outSalida" ) )
{
}

/*******************************************************************
* Function Name: initFunction
* Description: Empiezo mirando si hay pedidos
********************************************************************/
Model &Pizzero::initFunction()
{
        pedido = 0;
        salida = 0;
        hayLugar = 0;
        hayLista = 0;
        hornoLleno = 0;
        terminando = 0;
        meter = 0;
        pedir = 1;
        holdIn( active, Time::Zero );

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Pizzero::externalFunction( const ExternalMessage &msg )
{
        if( msg.port() == inPedidos )
	{
                esperando = 0;  //      Encontre un pedido

                //      Preparo la pizza
                pedido = (int)msg.value();

                //      Me fijo que tipo de pizza es
                int pizza = pedido % 10 ;
                int tiempoPrepa = 0;

                if ( pizza == MUZZA )
                {
                        tiempoPrepa = 32;
                }
                else if ( pizza == NAPO )
                {
                        tiempoPrepa = 36;
                }
                else if ( pizza == FUGA )
                {
                        tiempoPrepa = 38;
                }
                else
                {
                        MTHROW( InvalidMessageException() );
                }

// COMPLETAR                    //      alterar con random

                //      Me fijo si hay lugar
                hayLugar = 1;
                holdIn( active, Time(0 , 0 , 5 + tiempoPrepa , 0) );
                
        }//     if( msg.port() == inPedidos )

        else if( msg.port() == inHorno )
        {
                if ( hayLugar )
                {
                        hayLugar = 0;   //      Ya me contestaron
                        if ( (int)msg.value() )
                        {
                                //      Meto al horno
                                meter = 1;
                                holdIn( active, Time(0 , 0 , 10 , 0) );
                        }
                        else
                        {
                                //      Me fijo si hay alguna pizza lista
                                hornoLleno = 1;
                                hayLista = 1;
                                holdIn( active, Time(0 , 0 , 5 , 0) );
                        }
                }
                
                else if ( hayLista )
                {
                        hayLista = 0;   //      Ya me contestaron
                        if ( (int)msg.value() )
                        {
                                //      Saco del horno, termino la preparacion
                                //      y la despacho
                                if ( hornoLleno )
                                {
                                        //      Si el horno estaba lleno, ya no
                                        //      y puedo meter otra pizza
                                        hornoLleno = 0;
                                        meter = 1;
                                }
                                terminando = 1;

                                //      Me fijo que tipo de pizza es
                                //      y si es p/llevar
                                salida = (int)msg.value();
                                
                                int pizza = salida % 10 ;
                                int caja = salida / 10 ;
                                int tiempoTerm;

                                if ( pizza == NAPO )
                                {
                                        tiempoTerm = 7;
                                }
                                else
                                {
                                        tiempoTerm = 2;
                                }

                                if ( caja )
                                        tiempoTerm += 15;

// COMPLETAR                    //      alterar con random

                                holdIn( active, Time(0 , 0 , 5 + tiempoTerm , 0) );
                        }
                        else
                        {
                                if ( hornoLleno )
                                {
                                        //      Espero un rato
                                        //      y vuelvo a preguntar
                                        hayLista = 1;
                                        holdIn( active, Time(0 , 0 , 30 , 0) );
                                }
                                else
                                {
                                        //      Pido otro pedido
                                        pedir = 1;
                                        holdIn( active, Time(0 , 0 , 3 , 0) );
                                }
                        }
                }//     if ( hayLista )
                
        }//     if( msg.port() == inHorno )

	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Pizzero::internalFunction( const InternalMessage & )
{
        if ( esperando )
        {
                //      No encontre un pedido
                //      descanso 30 seg y me fijo se hay algo en el horno
                esperando = 0;
                hayLista = 1;
                holdIn( active, Time(0 , 0 , 30 , 0) );
        }
        else if ( pedir )
        {
                //      Fui a buscar un pedido
                pedir = 0;
                esperando = 1;
                holdIn( active, Time(0 , 0 , 1 , 0) );
        }
        else if ( terminando && meter )
        {
                //      Saque una pizza y tengo una para meter
                terminando = 0;
                holdIn( active, Time(0 , 0 , 10 , 0) );
        }
        else if ( terminando )
        {
                //      Termine una pizza pero no tengo otra para meter
                //      => me fijo si hay otra lista
                terminando = 0;
                hayLista = 1;
                holdIn( active, Time(0 , 0 , 10 , 0) );
        }
        else if ( meter )
        {
                //      Meti una pizza
                meter = 0;
                hayLista = 1;
                holdIn( active, Time(0 , 0 , 0 , 10) );
        }
        else
        {
                //      Mire si hay lugar o si hay lista
                passivate();
        }

	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Pizzero::outputFunction( const InternalMessage &msg )
{
        if ( pedir )
                sendOutput( msg.time(), outPedidos, (Value)MSG_DAME ) ;
        else if ( hayLugar )
                sendOutput( msg.time(), outHorno, (Value)MSG_HAY_LUGAR ) ;
        else if ( hayLista )
                sendOutput( msg.time(), outHorno, (Value)MSG_HAY_LISTA ) ;
        else if ( terminando )
                sendOutput( msg.time(), outSalida, (Value)salida ) ;
        else if ( meter )
                sendOutput( msg.time(), outHorno, (Value)pedido ) ;

        return *this ;
}

/*******************************************************************
* Function Name: ~Pizzero
* Description: destructor
********************************************************************/
Pizzero::~Pizzero()
{
}
 