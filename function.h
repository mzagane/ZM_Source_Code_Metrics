/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : function.h
  * description     : header file for function module (class)
  * date of creation: 14/01/2017
  * date of update  :
  * author          : Mohammed ZAGANE
  * Description     : this file contains the declaration of the function class
  *                   constructor, accessors and all related functions
  */


#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include <vector> //
#include <string>
#include "halstead_metrics.h"
#include "mccab_metrics.h"
#include "loc_metrics.h"

//using namespace std;


class Function
{

    private:
        //Attributes
        std::string Function_Declarator;//!< declarator of the function
        std::vector<std::string> Function_Body;//!< body of the function



    public :

        //Attributes
        Halstead_Metrics Function_Halstead_Metrics;// halstead metrics of the function
        Mccab_Metrics    Function_Mccab_Metrics;// Mccab Metrics of the function
        Loc_Metrics      Function_Loc_Metrics;// Loc Metrics of the function

        //Methods
        Function(std::string  Fun_Declarator, std::vector<std::string> Fun_Body);//constructor : initialization
        Function();//constructor
        std::string getFunction_Declarator();//!< accessors : return Function_Body
        std::vector<std::string> getFunction_Body();//!< accessors : return Function_Declarator
        void setFunction_Declarator(std::string Fun_Dec);
        void setFunction_Body(std::vector<std::string> Fun_Body);
        ~Function();//destructor :
};




#endif // FUNCTION_H_INCLUDED
