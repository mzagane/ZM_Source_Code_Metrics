/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : loc_metrics.cpp
  * description     : implementation file for loc_metrics module
  *                   this module contains all function needed to count the LOC metrics :
  *                   Physic lines, Empty lines, Lines of comment, Lines of code
  * date of creation: 26/08/2016
  * date of update  : 30/11/2016
  * author          : Mohammed ZAGANE
  * license         : Copyright (c) Mohammed ZAGANE, All rights reserved!
  */


#include <fstream> // ifstream

#include "loc_metrics.h"
#include "preprocessing.h"
#include "load_parameters.h"

/**
  * Initialization of L_M's attributes to 0
  */
void L_M::L_M_Init()
{
    Physic_Lines = 0 ;
    Empty_Lines = 0 ;
    Lines_Of_Comments = 0 ;
    Lines_Of_Program = 0 ;
}

/**
  * Constructor
  */
Loc_Metrics::Loc_Metrics()
{
    //
}

/**
  * Constructor
  */
Loc_Metrics::~Loc_Metrics()
{
    //
}

/**
  *count the number of physic lines
  * Parameters :
  *   vector<string> Inuput_Code : a string vector contains the source code lines
  * Returned values :
  *
  *   Nbr of physiques Lines (all lines)
  *
  */
void Loc_Metrics::setPhysic_Lines(std::vector<std::string> Input_Code)
{
    /*long Nbr_Physic_Lines = 0;
    string Line;
    unsigned long Index =0;
    while (Index< Input_Code.size())
    {
        Line = Input_Code[Index];
        Nbr_Physic_Lines++;
        Index++;
    }
    return Nbr_Physic_Lines;*/
    Loc_Met.Physic_Lines = Input_Code.size();
}

/**
  * this function counts the number of empty line
  * Parameters :
  *   vector<string> Inuput_Code : a string vector contains the source code lines
  * Returned values :
  *
  *   Nbr of empty lines
  *

*/
void Loc_Metrics::setEmpty_Lines(std::vector<std::string> Input_Code)
{
    long Nbr_Empty_Lines = 0;
    std::string Line;// holde the line content
    unsigned long Index =0;
    while (Index< Input_Code.size())
    {
        Line = Input_Code[Index];
        if(Line.length() == 0)// if the line is empty
        {
            Nbr_Empty_Lines ++;
        }
        Index++;
    }
    Loc_Met.Empty_Lines = Nbr_Empty_Lines;
}

/**
  * this function counts the number of lines of comments
  * Parameters :
  *   vector<string> Inuput_Code : a string vector contains the source code lines
  * Returned values :
  *
  *   Nbr of Lines Of Comments
  *
  */
void Loc_Metrics::setLines_Of_Comments(std::vector<std::string> Input_Code)
{
    long Nbr_Lines_Of_Comments = 0;
    std::string Line;// holde the line content
    bool Comment_Start_Found = false;
    std::string Cmnt_Strt  = Comment_Start[0];
    std::string Cmnt_End   = Comment_End[0];
    std::string Cmnt_Line  = Comment_Line[0];
    unsigned long Index =0;
    while (Index< Input_Code.size())
    {
        Line = Input_Code[Index];
        if(Line.length() != 0)// if the line isn't empty
        {
            if( !Comment_Start_Found)//the first comment markup not yet found
            {
                // if a one line comment found
                if( (Line.find(Cmnt_Line) >=0) && (Line.find(Cmnt_Line)<= Line.length()) )
                {
                    Nbr_Lines_Of_Comments++; // increment the number of lines of comment
                    Index++;
                    continue; // skip the next instructions and  go to the next line
                }
                // the first comment markup found
                if((Line.find(Cmnt_Strt) >=0) && (Line.find(Cmnt_Strt)<= Line.length()))
                {
                    Comment_Start_Found = true;// indicate that the F C Mrkp Found
                    Nbr_Lines_Of_Comments++; // increment the number of lines of comment
                    // if the S C Mrkp found in the same line ( /* comment */)
                    if((Line.find(Cmnt_End) >=0) && (Line.find(Cmnt_End)<= Line.length()))
                    {
                        Comment_Start_Found = false;// this will indicate the end of the current comment
                    }
                    Index++;
                    continue; // skip the next instruction and go to the next line
                }
            }
            else // the F C Mrkp already found
            {
                // if the S C Mrkp found
                if((Line.find(Cmnt_End) >=0) && (Line.find(Cmnt_End)<= Line.length()))
                {
                    Nbr_Lines_Of_Comments++;// increment the number of lines of comment
                    Comment_Start_Found = false; // this will indicate the end of comment
                    Index++;
                    continue;// skip the next instructions and go to the next line
                }
                else //  if the S C Mrkp not yet found
                {
                    Nbr_Lines_Of_Comments++; // increment the number of lines of comments
                    Index++;
                    continue;// skip the next instructions and go to the next line
                }
            }
        }
        else if( Comment_Start_Found) // if the line is empty, but the F C Mrq is already found
        {
            Nbr_Lines_Of_Comments ++; // increment the number of lines of comment
            Index++;
            continue;// skip and go to the next line
        }
        Index++;
    }
    Loc_Met.Lines_Of_Comments = Nbr_Lines_Of_Comments;
}

/**
  * this function return the number of program line ( directive, declaration,
  * definition, commands
  *
  * Parameters :
  * vector<string> Inuput_Code : a string vector contains the source code lines
  * Returned values :
  *
  * the number of line of program
  */

void Loc_Metrics::setLines_Of_Program(std::vector<std::string> Inuput_Code)
{
    std::vector<std::string> Program_Code = Extract_Code (Inuput_Code);
    Loc_Met.Lines_Of_Program = Program_Code.size();
}

/**
  * Accessors : return the number of physic lines
  */
long Loc_Metrics::getPhysic_Lines()
{
    return Loc_Met.Physic_Lines;
}

/**
  * Accessors : return the number of empty line
  */
long Loc_Metrics::getEmpty_Lines()
{
    return Loc_Met.Empty_Lines ;
}

/**
  * Accessors : return the number of lines of comments
  */
long Loc_Metrics::getLines_Of_Comments()
{
    return Loc_Met.Lines_Of_Comments;
}

/**
  * Accessors : return the number of program line ( directive, declaration,
  */

long Loc_Metrics::getLines_Of_Program()
{
    return Loc_Met.Lines_Of_Program;
}
/**
  * call : setPhysic_Lines(), setEmpty_Lines(), setLines_Of_Comments(), setLines_Of_Program()
  * to set the L_M structure
  */
void Loc_Metrics::setL_Met(std::vector<std::string> Input_Code)
{
    setPhysic_Lines(Input_Code);
    setEmpty_Lines(Input_Code);
    setLines_Of_Comments(Input_Code);
    setLines_Of_Program(Input_Code);
}
/**
  *   accessors
  *   get the L_M structure
  */

L_M Loc_Metrics::getL_Met()
{
    return Loc_Met;
}
