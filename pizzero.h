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

#ifndef __PIZZERO_H
#define __PIZZERO_H

/** include files **/
#include "atomic.h"     // class Atomic

/** forward declarations **/

/** declarations **/
class Pizzero : public Atomic
{
public:
	Pizzero( const string &name = "Pizzero" );				  // Default constructor

	~Pizzero();

	virtual string className() const
		{return "Pizzero";}

protected:
	Model &initFunction() ;

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
        const Port &inPedidos;
        Port &outPedidos;
        const Port &inHorno;
        Port &outHorno;
	Port &outSalida;

        int pedido;
        int salida;

        int hayLugar;
        int hayLista;
        int hornoLleno;
        int terminando;
        int pedir;
        int meter;
        int esperando;

};	// class Pizzero


#endif   //__PIZZERO_H
 