/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : function.cpp
  * description     : implementation file for function module (class)
  * date of creation: 14/01/2017
  * date of update  :
  * author          : Mohammed ZAGANE
  * Description     : this file contains the definition of the function class
  *                   constructor, accessors and all related functions
  */
#include "function.h"
#include "load_parameters.h"// global variables : parameters

Function::Function(std::string Fun_Declarator, std::vector<std::string> Fun_Body)
{
    Function_Declarator = Fun_Declarator;
    Function_Body = Fun_Body;
}
//constructor
Function::Function()
{
    //
}
//accessors : return Function_Declarator
std::string Function::getFunction_Declarator()
{
    return Function_Declarator;
}
//accessors : return Function_Body
std::vector<std::string> Function::getFunction_Body()
{
    return Function_Body;
}
//accessors : define Function_Declarator
void Function::setFunction_Declarator(std::string Fun_Dec)
{
    Function_Declarator = Fun_Dec;
}

void Function::setFunction_Body(std::vector<std::string> Fun_Body)
{
    Function_Body = Fun_Body;
}

Function::~Function()
{
    //
}
/*************************************************************************
*                          END FUNCTION CLASS                            *
*************************************************************************/

