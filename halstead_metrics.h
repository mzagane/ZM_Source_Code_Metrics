/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : halstead_metric.h
  * description     : header file for halstead_metric module
  * date of creation: 04/11/2016
  * date of update  : 17/01/2017
  * @author          : Mohammed ZAGANE
  */

#ifndef HALSTEAD_METRICS_H_INCLUDED
#define HALSTEAD_METRICS_H_INCLUDED
#include <vector>// vector
#include <cmath>// log2 , pow

//using namespace std;

struct Operand
{
    std::string Value; // the value of the operand
    std::string Type; //  IDENTIFIER, STRING, NUMBER, CHAR, TYPE_SPECIFICATOR
    unsigned long Count; // occurrence number
};
struct Operator
{
    std::string Value; // the value of the operand
    std::string Type; // OPERATOR, KEYWORD, STORAGE_CLASS_SPECIFICATOR, TYPE_QUALIFICATOR
    unsigned long Count; // occurrence number
};
/**
  * Number of distinct operators : n1
  * Number of distinct operands  : n2
  * Total number of operators    : N1
  * Total number of operands     : N2
  **
  * From these numbers, several measures can be calculated:
  **
  * Program vocabulary           : n = n1+n2
  * Program length               : N=N1+N2
  * Calculated program length    : _N = n1*log(2)n1 + n2*log(2)n2
  * Volume                       : V= N * log(2)n
  * Difficulty                   : D = n1/2 * N2/n2
  * Effort                       : E = D * V
  * Time Required To Program     : T = E/18 seconds
  * Number of delivered bugs     : B = E^(2/3) / 3000  or  B = V/3000
  */

struct H_M
{
    unsigned long n1_Number_Of_Distinct_Operators;
    unsigned long n2_Number_Of_Distinct_Operands;
    unsigned long N1_Total_Number_Of_Operators;
    unsigned long N2_Total_Number_Of_Operands;
    unsigned long n_Program_Vocabulary;
    unsigned long N_Program_Length;
    double         _N_Calculated_Program_Length;
    double         V_Volume;
    double         D_Difficulty;
    double         E_Effort;
    double         T_Time_Required_To_Program;
    double         B_Number_of_Delivered_Bugs_1;
    double         B_Number_of_Delivered_Bugs_2;

    //<! initialization of the structure to 0 for all members
    void H_M_Init();

};

class Halstead_Metrics
{
    //Attributes
    private :
        H_M Halst_Met;//!< the Halstead metrics
    //Methods
    public :
        Halstead_Metrics();
        ~Halstead_Metrics();
        void setHalst_Met(std::vector<std::string> Input_Code);//!< accessors : calculate the Halstead metrics (set H_M Halst_Met)
        H_M getHalst_Met();//!< accessors : return the Halstead metrics
};

//Other functions
bool Is_A_Type_Specificator (std::string Token); //!< verify if the given token in parameter is a Type specificator or not
bool Is_A_Storage_Class_Specificator (std::string Token);//!< verify if the given token in parameter is a storage class specificator or not
bool Is_A_Type_Qualificator (std::string Token);//!< verify if the given token in parameter is a Type qualificator or not
bool Is_A_Key_Word (std::string Token);//!< verify if the given token in parameter is a Key word or not
bool Is_An_Operator (std::string Token);//!< verify if the given token in parameter is an operator or not
bool Is_An_Identifier(std::string Token);//!< verify if the given token in parameter is an identifier or not
std::vector<Operand> getOperands_List (std::vector<std::string> Tokens);//!< get the Operands list
std::vector<Operator> getOperators_List (std::vector<std::string> Tokens);//!< get the operators list


#endif // HALSTEAD_METRICS_H_INCLUDED
