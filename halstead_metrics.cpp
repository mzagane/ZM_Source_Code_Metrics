/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : halstead_metric.cpp
  * description     : implementation file for halstead_metric module
  * date of creation: 04/11/2016
  * date of update  : 17/01/2017
  * author          : Mohammed ZAGANE
  */

#include <fstream> // ifstream
#include <regex> // regex
#include "preprocessing.h"
#include "halstead_metrics.h"
#include "load_parameters.h"
#include "tokeniser.h" //

/**
  * Initialization of all H_M's members to 0
  */
void H_M::H_M_Init()
{
    n1_Number_Of_Distinct_Operators = 0 ;
    n2_Number_Of_Distinct_Operands = 0 ;
    N1_Total_Number_Of_Operators = 0 ;
    N2_Total_Number_Of_Operands = 0 ;
    n_Program_Vocabulary = 0 ;
    N_Program_Length = 0 ;
    _N_Calculated_Program_Length = 0 ;
    V_Volume = 0 ;
    D_Difficulty = 0 ;
    E_Effort = 0 ;
    T_Time_Required_To_Program = 0 ;
    B_Number_of_Delivered_Bugs_1 = 0 ;
    B_Number_of_Delivered_Bugs_2 = 0 ;

}

/**
  *  Constructor
  */
Halstead_Metrics::Halstead_Metrics()
{
    //
}
/**
  *  Destructor
  */
Halstead_Metrics::~Halstead_Metrics()
{
    //
}
/**
  * this function verify if the given token in parameter is
  *  a Type Specificator or not
  */
bool Is_A_Type_Specificator (std::string Token)
{
    for (unsigned int i=0; i<Type_Specificators.size();i++)
    {
        if(Token == Type_Specificators[i])
        {
            return true;
        }
    }
    return false;
}

/**
  * this function verify if the given token in parameter is
  *  a Storage Class Specificator or not
  */
bool Is_A_Storage_Class_Specificator (std::string Token)
{
    for (unsigned int i=0; i<Storage_Class_Specificators.size();i++)
    {
        if(Token == Storage_Class_Specificators[i])
        {
            return true;
        }
    }
    return false;
}

/**
  * this function verify if the given token in parameter is
  *  a Type Qualificator or not
  */
bool Is_A_Type_Qualificator (std::string Token)
{
    for (unsigned int i=0; i<Type_Qualificators.size();i++)
    {
        if(Token == Type_Qualificators[i])
        {
            return true;
        }
    }
    return false;
}

/**
  * this function verify if the given token in parameter is
  *  a Key Word or not
  */
bool Is_A_Key_Word (std::string Token)
{
    for (unsigned int i=0; i<Key_Words.size();i++)
    {
        if(Token == Key_Words[i])
        {
            return true;
        }
    }
    return false;
}

/**
  * this function verify if the given token in parameter is
  *  a Operator or not
  */
bool Is_An_Operator (std::string Token)
{
    for (unsigned int i=0; i<Operators.size();i++)
    {
        if(Token == Operators[i])
        {
            return true;
        }
    }
    return false;
}

/**
  * this function verify if the given token in parameter is
  *  an Identifier or not
  */
bool Is_An_Identifier (std::string Token)
{
    std::string Str_Iden_Regex = Identifier_Regex[0];
    std::regex Iden_Regex (Str_Iden_Regex.c_str());
    if (regex_match(Token, Iden_Regex) )
    {
        return true;
    }
    else
    {
        return false;
    }
}


/**
*  this function get the number of operands
*/
std::vector<Operand> getOperands_List (std::vector<std::string> Tokens)
{
    std::string Line;
    std::vector<Operand> Operands_Lst;
    std::vector<std::string> All_Operands_Lst;
    Operand * New_Operand = new Operand;
    unsigned long i;
    bool Operand_Found;
    unsigned long Ind =0;
    while (Ind< Tokens.size())
    {
        Line = Tokens[Ind];
        if( Is_A_Number_Token(Line))
        {
            Operand_Found = false;
            i = 0;
            while(i<Operands_Lst.size() && !Operand_Found)
            {
                if (Line == Operands_Lst[i].Value)
                {
                    Operand_Found = true;
                    break;
                }
                i++;
            }

            if (Operand_Found)
            {
                Operands_Lst[i].Count += 1;
            }
            else
            {
                New_Operand->Value = Line;
                New_Operand->Type = "NUMBER";
                New_Operand->Count = 1;
                Operands_Lst.insert(Operands_Lst.end(), *New_Operand);
            }
            All_Operands_Lst.insert(All_Operands_Lst.end(), Line);
        }
        else if( Is_A_String_Token(Line))
        {
            Operand_Found = false;
            i = 0;
            while(i<Operands_Lst.size() && !Operand_Found)
            {
                if (Line == Operands_Lst[i].Value)
                {
                    Operand_Found = true;
                    break;
                }
                i++;
            }

            if (Operand_Found)
            {
                Operands_Lst[i].Count += 1;
            }
            else
            {
                New_Operand->Value = Line;
                New_Operand->Type = "STRING";
                New_Operand->Count = 1;
                Operands_Lst.insert(Operands_Lst.end(), *New_Operand);
            }
            All_Operands_Lst.insert(All_Operands_Lst.end(), Line);
        }
        else if( Is_A_Char_Token(Line))
        {
            Operand_Found = false;
            i = 0;
            while(i<Operands_Lst.size() && !Operand_Found)
            {
                if (Line == Operands_Lst[i].Value)
                {
                    Operand_Found = true;
                    break;
                }
                i++;
            }

            if (Operand_Found)
            {
                Operands_Lst[i].Count += 1;
            }
            else
            {
                New_Operand->Value = Line;
                New_Operand->Type = "CHAR";
                New_Operand->Count = 1;
                Operands_Lst.insert(Operands_Lst.end(), *New_Operand);
            }
            All_Operands_Lst.insert(All_Operands_Lst.end(), Line);
        }
        else if( Is_A_Type_Specificator(Line))
        {
            Operand_Found = false;
            i = 0;
            while(i<Operands_Lst.size() && !Operand_Found)
            {
                if (Line == Operands_Lst[i].Value)
                {
                    Operand_Found = true;
                    break;
                }
                i++;
            }

            if (Operand_Found)
            {
                Operands_Lst[i].Count += 1;
            }
            else
            {
                New_Operand->Value = Line;
                New_Operand->Type = "TYPE_SPECIFICATOR";
                New_Operand->Count = 1;
                Operands_Lst.insert(Operands_Lst.end(), *New_Operand);
            }
            All_Operands_Lst.insert(All_Operands_Lst.end(), Line);
        }
        else if( Is_An_Identifier(Line) &&
                !Is_A_Storage_Class_Specificator(Line) &&
                !Is_A_Type_Qualificator(Line) &&
                !Is_A_Key_Word(Line)
                )
        {
            Operand_Found = false;
            i = 0;
            while(i<Operands_Lst.size() && !Operand_Found)
            {
                if (Line == Operands_Lst[i].Value)
                {
                    Operand_Found = true;
                    break;
                }
                i++;
            }

            if (Operand_Found)
            {
                Operands_Lst[i].Count += 1;
            }
            else
            {
                New_Operand->Value = Line;
                New_Operand->Type = "IDENTIFIER";
                New_Operand->Count = 1;
                Operands_Lst.insert(Operands_Lst.end(), *New_Operand);
            }
            All_Operands_Lst.insert(All_Operands_Lst.end(), Line);
        }
        Ind++;
    }

    /*std::ofstream Operands_File ("Operands.temp");// creating the tokens file

    // writing the tokens in the file
    if (Operands_File.good() )
    {
        for (unsigned int p=0; p<All_Operands_Lst.size(); p++)
        {
            Operands_File << All_Operands_Lst[p] << std::endl;
        }
        Operands_File.close();
    }*/
    delete New_Operand;
    All_Operands_Lst.clear();
    return Operands_Lst;
}

/**
*  this function get the number of operators
*/
std::vector<Operator> getOperators_List (std::vector<std::string> Tokens)
{
    std::string Line;
    std::vector<Operator> Operators_Lst;
    std::vector<std::string> All_Operators_Lst;
    Operator * New_Operator = new Operator;
    unsigned long i;
    bool Operator_Found;
    unsigned long Ind =0;
    while (Ind< Tokens.size())
    {
        Line = Tokens[Ind];
        if( Is_A_Storage_Class_Specificator(Line))
        {
            Operator_Found = false;
            i = 0;
            while(i<Operators_Lst.size() && !Operator_Found)
            {
                if (Line == Operators_Lst[i].Value)
                {
                    Operator_Found = true;
                    break;
                }
                i++;
            }

            if (Operator_Found)
            {
                Operators_Lst[i].Count += 1;
            }
            else
            {
                New_Operator->Value = Line;
                New_Operator->Type = "STORAGE_CLASS_SPECIFICATOR";
                New_Operator->Count = 1;
                Operators_Lst.insert(Operators_Lst.end(), *New_Operator);
            }
            All_Operators_Lst.insert(All_Operators_Lst.end(), Line);
        }
        else if( Is_A_Type_Qualificator(Line))
        {
            Operator_Found = false;
            i = 0;
            while(i<Operators_Lst.size() && !Operator_Found)
            {
                if (Line == Operators_Lst[i].Value)
                {
                    Operator_Found = true;
                    break;
                }
                i++;
            }

            if (Operator_Found)
            {
                Operators_Lst[i].Count += 1;
            }
            else
            {
                New_Operator->Value = Line;
                New_Operator->Type = "TYPE_QUALIFICATOR";
                New_Operator->Count = 1;
                Operators_Lst.insert(Operators_Lst.end(), *New_Operator);
            }
            All_Operators_Lst.insert(All_Operators_Lst.end(), Line);
        }
        else if( Is_A_Key_Word(Line))
        {
            Operator_Found = false;
            i = 0;
            while(i<Operators_Lst.size() && !Operator_Found)
            {
                if (Line == Operators_Lst[i].Value)
                {
                    Operator_Found = true;
                    break;
                }
                i++;
            }

            if (Operator_Found)
            {
                Operators_Lst[i].Count += 1;
            }
            else
            {
                New_Operator->Value = Line;
                New_Operator->Type = "KEY_WORD";
                New_Operator->Count = 1;
                Operators_Lst.insert(Operators_Lst.end(), *New_Operator);
            }
            All_Operators_Lst.insert(All_Operators_Lst.end(), Line);
        }
        else if( Is_An_Operator(Line))
        {
            Operator_Found = false;
            i = 0;
            while(i<Operators_Lst.size() && !Operator_Found)
            {
                if (Line == Operators_Lst[i].Value)
                {
                    Operator_Found = true;
                    break;
                }
                i++;
            }

            if (Operator_Found)
            {
                Operators_Lst[i].Count += 1;
            }
            else
            {
                New_Operator->Value = Line;
                New_Operator->Type = "OPERATOR";
                New_Operator->Count = 1;
                Operators_Lst.insert(Operators_Lst.end(), *New_Operator);
            }
            All_Operators_Lst.insert(All_Operators_Lst.end(), Line);
        }
        Ind++;
    }

    /*std::ofstream Operators_File ("Operators.temp");// creating the tokens file

    // writing the tokens in the file
    if (Operators_File.good() )
    {
        for (unsigned int p=0; p<All_Operators_Lst.size(); p++)
        {
            Operators_File << All_Operators_Lst[p] << std::endl;
        }
        Operators_File.close();
    }*/
    delete New_Operator;
    All_Operators_Lst.clear();
    return Operators_Lst;
}

void Halstead_Metrics::setHalst_Met(std::vector<std::string> Input_Code)
{

    std::vector<std::string> Tokens = Generate_Tokens_List (Input_Code);// return the list of all tokens, this function is defined in tokeniser module
    std::vector<Operator> Operators_List= getOperators_List(Tokens);//generating operators list
    std::vector<Operand> Operands_List= getOperands_List(Tokens);//generating operands list
    //calculating n1, N1
    Halst_Met.n1_Number_Of_Distinct_Operators = 0;
    Halst_Met.N1_Total_Number_Of_Operators = 0;
    for (unsigned long i=0; i<Operators_List.size(); i++)
    {
        Halst_Met.n1_Number_Of_Distinct_Operators += 1;
        Halst_Met.N1_Total_Number_Of_Operators += Operators_List[i].Count;
    }
    //calculating n2, N2
    Halst_Met.n2_Number_Of_Distinct_Operands = 0;
    Halst_Met.N2_Total_Number_Of_Operands = 0;
    for (unsigned long i=0; i<Operands_List.size();i++)
    {
        Halst_Met.n2_Number_Of_Distinct_Operands += 1;
        Halst_Met.N2_Total_Number_Of_Operands += Operands_List[i].Count;

    }
    //Program vocabulary : n, Program length : N
    Halst_Met.n_Program_Vocabulary = Halst_Met.n1_Number_Of_Distinct_Operators + Halst_Met.n2_Number_Of_Distinct_Operands;
    Halst_Met.N_Program_Length = Halst_Met.N1_Total_Number_Of_Operators + Halst_Met.N2_Total_Number_Of_Operands;
    //Calculated Program Length N'
    Halst_Met._N_Calculated_Program_Length =
    Halst_Met.n1_Number_Of_Distinct_Operators * log2(Halst_Met.n1_Number_Of_Distinct_Operators) +
    Halst_Met.n2_Number_Of_Distinct_Operands * log2(Halst_Met.n2_Number_Of_Distinct_Operands);
    //program Volume : V, Program difficulty : D, Program Effort, Time Required To Program : T, Number of Delivered Bugs : B
    Halst_Met.V_Volume = Halst_Met.N_Program_Length * log2(Halst_Met.n_Program_Vocabulary);
    Halst_Met.D_Difficulty = (Halst_Met.n1_Number_Of_Distinct_Operators/2) * (Halst_Met.N2_Total_Number_Of_Operands/Halst_Met.n2_Number_Of_Distinct_Operands);
    Halst_Met.E_Effort = Halst_Met.D_Difficulty * Halst_Met.V_Volume;
    Halst_Met.T_Time_Required_To_Program = Halst_Met.E_Effort / 18;
    Halst_Met.B_Number_of_Delivered_Bugs_1 = (pow(Halst_Met.E_Effort ,2/3)) / 3000;
    Halst_Met.B_Number_of_Delivered_Bugs_2 = Halst_Met.V_Volume / 3000;

}
/**
  *  Accessors : return the halstead metrics structure
  */
H_M Halstead_Metrics::getHalst_Met()
{
    return Halst_Met;
}
