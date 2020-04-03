/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : src_file.cpp
  * description     : implementation file for src_file module (class)
  * date of creation: 14/01/2017
  * date of update  :
  * author          : Mohammed ZAGANE
  * Description     : this file contains the definition of the src_file class methods
  *                   constructor, accessors and all related functions
  */

#include <fstream>//ifstream
#include "load_parameters.h"// global variables : parameters
#include "src_file.h"


//constructor
Src_File::Src_File(std::string Src_F_Name, std::string Src_Lang)
{
    Src_File_Name = Src_F_Name;
    Src_File_Language = Src_Lang;
}
//constructor
Src_File::Src_File()
{
    //--
}
// accessors : return source file name
std::string Src_File::getSrc_File_Name()
{
    return Src_File_Name;
}
//accessors : return language of the source
std::string Src_File::getSrc_File_Language()
{
    return Src_File_Language;
}
//accessors : define source file name
void Src_File::setSrc_File_Name(std::string Src_F_Name)
{
    Src_File_Name = Src_F_Name;
}
//accessors : define language of the source
void Src_File::setSrc_File_Language(std::string Src_Lang)
{
    Src_File_Language = Src_Lang;
}

/**
  * this function load the source file in a std::vector of string
  */
std::vector<std::string> Src_File::Load_Src_File()
{
    // reading the src file in : Src_Code
    std::ifstream Src_File (Src_File_Name.c_str());
    std::vector<std::string> Src_Code;
    std::string Line;
    if(Src_File.good())
    {
        while (getline(Src_File, Line))
        {
            Src_Code.insert(Src_Code.end(), Line);
        }
    }
    Src_File.close();
    return Src_Code;

}

/**
  * read the src file and extracts function from it
  * after eliminating comments and spaces, tab..
  */
int Src_File::setSrc_File_Functions()
{
    Function * New_Function;
    std::vector<std::string> New_Fun_Body = Load_Src_File();;

    New_Function = new Function();
    New_Function->setFunction_Declarator("");
    New_Function->setFunction_Body(New_Fun_Body);
    Src_File_Functions.insert(Src_File_Functions.end(), * New_Function);

    New_Fun_Body.clear();
    return Src_File_Functions.size();// functions number
}
std::vector<Function> Src_File::getSrc_File_Functions()
{
    return Src_File_Functions;
}
/**
  * calculate halstead metrics of the src file = sum of the H M of all file's functions
  */
void Src_File::setSrc_File_H_M()
{
    std::vector<std::string> Function_Code;
    H_M Temp;
    Src_File_H_M.H_M_Init();// initiallization of the structure to 0

    for (int i=0; i < Src_File_Functions.size(); i++)
    {
        Function_Code.clear();
        Function_Code = Src_File_Functions[i].getFunction_Body();
        Function_Code.insert(Function_Code.begin(), Src_File_Functions[i].getFunction_Declarator());
        Src_File_Functions[i].Function_Halstead_Metrics.setHalst_Met(Function_Code);
        Temp = Src_File_Functions[i].Function_Halstead_Metrics.getHalst_Met();
        Src_File_H_M.B_Number_of_Delivered_Bugs_1    += Temp.B_Number_of_Delivered_Bugs_1;
        Src_File_H_M.B_Number_of_Delivered_Bugs_2    += Temp.B_Number_of_Delivered_Bugs_2;
        Src_File_H_M.D_Difficulty                    += Temp.D_Difficulty;
        Src_File_H_M.E_Effort                        += Temp.E_Effort;
        Src_File_H_M.n1_Number_Of_Distinct_Operators += Temp.n1_Number_Of_Distinct_Operators;
        Src_File_H_M.N1_Total_Number_Of_Operators    += Temp.N1_Total_Number_Of_Operators;
        Src_File_H_M.n2_Number_Of_Distinct_Operands  += Temp.n2_Number_Of_Distinct_Operands;
        Src_File_H_M.N2_Total_Number_Of_Operands     += Temp.N2_Total_Number_Of_Operands;
        Src_File_H_M.N_Program_Length                += Temp.N_Program_Length;
        Src_File_H_M.n_Program_Vocabulary            += Temp.n_Program_Vocabulary;
        Src_File_H_M.T_Time_Required_To_Program      += Temp.T_Time_Required_To_Program;
        Src_File_H_M.V_Volume                        += Temp.V_Volume;
        Src_File_H_M._N_Calculated_Program_Length    += Temp._N_Calculated_Program_Length;
    }

}
/**
  * accessors : return halstead metrics of the src file = sum of the H M of all file's functions
  */
H_M Src_File::getSrc_File_H_M()
{
    return Src_File_H_M;
}

/**
  * calculate McCab metrics of the src file = sum of the M M of all file's functions
  */
void Src_File::setSrc_File_M_M()
{
    std::vector<std::string> Function_Code;
    M_M Temp;
    Src_File_M_M.M_M_Init();// initiallization of the structure to 0

    for (int i=0; i < Src_File_Functions.size(); i++)
    {
        Function_Code.clear();
        Function_Code = Src_File_Functions[i].getFunction_Body();
        Function_Code.insert(Function_Code.begin(), Src_File_Functions[i].getFunction_Declarator());
        Src_File_Functions[i].Function_Mccab_Metrics.setMccab_Met(Function_Code);
        Temp = Src_File_Functions[i].Function_Mccab_Metrics.getMccab_Met();
        Src_File_M_M.McCab_Number += Temp.McCab_Number;
    }
}
/**
  * accessors : return McCab metrics of the src file
  */
M_M Src_File::getSrc_File_M_M()
{
    return Src_File_M_M;
}

/**
  * calculate LOC metrics of the src file = sum of the L M of all file's functions
  */
void Src_File::setSrc_File_L_M()
{
    std::vector<std::string> Function_Code;
    L_M Temp;
    Src_File_L_M.L_M_Init();// initiallization of the structure to 0

    for (int i=0; i < Src_File_Functions.size(); i++)
    {
        Function_Code.clear();
        Function_Code = Src_File_Functions[i].getFunction_Body();
        Function_Code.insert(Function_Code.begin(), Src_File_Functions[i].getFunction_Declarator());
        Src_File_Functions[i].Function_Loc_Metrics.setL_Met(Function_Code);
        Temp = Src_File_Functions[i].Function_Loc_Metrics.getL_Met();

        Src_File_L_M.Empty_Lines       += Temp.Empty_Lines;
        Src_File_L_M.Lines_Of_Comments += Temp.Lines_Of_Comments;
        Src_File_L_M.Lines_Of_Program  += Temp.Lines_Of_Program;
        Src_File_L_M.Physic_Lines      += Temp.Physic_Lines;
    }

}


/**
  * accessors : return LOC metrics of the src file
  */
L_M Src_File::getSrc_File_L_M()
{
    return Src_File_L_M;
}

Src_File::~Src_File()
{
    //
}

