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

#ifndef __ADMLUG_H
#define __ADMLUG_H

/** include files **/
#include "atomic.h"     // class Atomic

/** forward declarations **/

/** declarations **/
class AdministradorLugares : public Atomic
{
public:
	AdministradorLugares( const string &name = "AdministradorLugares" );				  // Default constructor

	~AdministradorLugares();

	virtual string className() const
		{return "AdministradorLugares";}

protected:
	Model &initFunction() ;

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
        const Port &inPizzero;
        Port &outPizzero;

        //      Conexiones con los lugares
        const Port &inLugar1;
        Port &outLugar1;
        const Port &inLugar2;
        Port &outLugar2;
        const Port &inLugar3;
        Port &outLugar3;
        const Port &inLugar4;
        Port &outLugar4;
        const Port &inLugar5;
        Port &outLugar5;
        const Port &inLugar6;
        Port &outLugar6;
        const Port &inLugar7;
        Port &outLugar7;
        const Port &inLugar8;
        Port &outLugar8;
        const Port &inLugar9;
        Port &outLugar9;
        const Port &inLugar10;
        Port &outLugar10;

        //      Variables de estado
        int ocupado[10];
        int listas[10];
        int pizza;
        int hayLugar;
        int hayLista;
        Value lugar;
        Value lista;

};	// class AdministradorLugares


#endif   //__ADMLUG_H
 