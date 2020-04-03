/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : src_file.h
  * description     : header file for src_fie module (class)
  * date of creation: 14/01/2017
  * date of update  :
  * author          : Mohammed ZAGANE
  * Description     : this file contains the declaration of the src_file class
  *                   constructor, accessors and all related functions
  */


#ifndef SRC_FILE_H_INCLUDED
#define SRC_FILE_H_INCLUDED
#include <vector> //
#include <string>

#include "function.h"
#include "halstead_metrics.h" // H_M structure
#include "loc_metrics.h"


class Src_File
{

    private:
        //Attributes
        std::string Src_File_Name;//!< source file name
        std::string Src_File_Language;//!< language of the source
        std::vector<Function> Src_File_Functions;//!< list of file functions
        H_M Src_File_H_M;//!< halstead metrics of the src file = sum of the H M of all file's functions
        M_M Src_File_M_M;//!< McCab metrics of the src file = sum of the M M of all file's functions
        L_M Src_File_L_M;//!< LOC metrics of the src file = sum of the L M of all file's functions

    public :
        //Attribute

        //Methods
        Src_File(std::string Src_F_Name, std::string Src_Lang);//!< constructor with initialization
        Src_File();//!< constructor
        std::string getSrc_File_Name();//!< accessors : return source file name
        std::string getSrc_File_Language();//!< accessor : return language of the source
        void setSrc_File_Name(std::string Src_F_Name);//!< accessors : define source file name
        void setSrc_File_Language(std::string Src_Lang);//!< accessors : define language of the source
        int setSrc_File_Functions();//!<  accessor: extraction of the function from the source file
        std::vector<Function> getSrc_File_Functions();//!<  accessor: return the extracted function
        void setSrc_File_H_M();//!< calculate halstead metrics of the src file = sum of the H M of all file's functions
        H_M getSrc_File_H_M();//!< accessors : return halstead metrics of the src file = sum of the H M of all file's functions
        void setSrc_File_M_M();//!< calculate McCab metrics of the src file = sum of the M M of all file's functions
        M_M getSrc_File_M_M();//!< accessors : return McCab metrics of the src file = sum of the M M of all file's functions
        void setSrc_File_L_M();//!< calculate LOC metrics of the src file = sum of the L M of all file's functions
        L_M getSrc_File_L_M();//!< accessors : return LOC metrics of the src file = sum of the L M of all file's functions

        // other function
        std::vector<std::string> Load_Src_File();//!< this function load the source file in a vector of string
        ~Src_File();// destructor
};

#endif // SRC_FILE_H_INCLUDED
