/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : loc_metrics.h
  * description     : header file for loc_metrics module
  *                   this module contains all function needed to count the LOC metrics :
  *                   Physic lines, Empty lines, Lines of comment, Lines of code
  * date of creation: 26/08/2016
  * date of update  : 17/01/2017
  * author          : Mohammed ZAGANE
  * license         : Copyright (c) Mohammed ZAGANE, All rights reserved!
  */

#ifndef LOC_METRICS_H_INCLUDED
#define LOC_METRICS_H_INCLUDED
#include <vector>

//using namespace std;

/**
  * Loc Metrics structure
  */
struct L_M
{
    long Physic_Lines; //!< Number of the total lines in the source file
    long Empty_Lines; //!< Number of the empty lines in the source file
    long Lines_Of_Comments; //!< Number of the lines of comments
    long Lines_Of_Program;//!< Number of the program lines (directive, definition, declaration, commands)

    void L_M_Init(); //!< Initialization of L_M's attributes to 0

};

class Loc_Metrics
{
    //Attributes
    private :
        L_M Loc_Met; //!< Line of code metrics structure
    //Methods
    public :
        Loc_Metrics();//!< constructor
        ~Loc_Metrics();//!<destructor
        void setPhysic_Lines(std::vector<std::string> Input_Code);//!< count total lines in the source file
        void setEmpty_Lines(std::vector<std::string> Input_Code);//!< count empty lines in the source file
        void setLines_Of_Comments(std::vector<std::string> Input_Code);//!<count the number of lines of comments
        void setLines_Of_Program(std::vector<std::string> Input_Code);//!<count the number of program line (directive, definition, declaration, commands)

        long getPhysic_Lines();//!< accessors : return total lines in the source file
        long getEmpty_Lines();//!< accessors : return empty lines in the source file
        long getLines_Of_Comments();//!< accessors : return the number of lines of comments
        long getLines_Of_Program();//!< accessors : return the number of program line (directive, definition, declaration, commands)

        void setL_Met(std::vector<std::string> Input_Code);//!< call : setPhysic_Lines(), setEmpty_Lines(), setLines_Of_Comments(), setLines_Of_Program()
                      //!< to set the L_M structure
        L_M getL_Met();//!< Accessors :  get the L_M structure
};
#endif // LOC_METRICS_H_INCLUDED
