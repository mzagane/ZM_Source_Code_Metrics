/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : project.h
  * description     : header file for project module (class)
  * date of creation: 14/01/2017
  * date of update  :
  * author          : Mohammed ZAGANE
  * Description     : this file contains the declaration of the project class
  *                   constructor, accessors and all related functions
  */


#ifndef PROJECT_H_INCLUDED
#define PROJECT_H_INCLUDED

#include <vector> //
#include <string>
#include "src_file.h"
#include "loc_metrics.h" // for L_M structure
#include "halstead_metrics.h" // for H_M structure

//using namespace std;


class Project
{

    private:
        //attributes
        std::string Project_Name; //!< project name
        std::string Project_Directory;//!< project directory
        std::vector<Src_File> Project_Files;//!< list of the src file of the project
        L_M Project_L_M;//!< Line of code metrics of the project
        H_M Project_H_M;//!< Halstead Metrics of the project
        M_M Project_M_M;//!< Mccab Metrics of the project

        //Methods


    public :
        //Attributes

        //Methods
        Project();//!<constructor
        Project(std::string Prj_Name, std::string Prj_Dir);//!< constructor with initialization
        std::string getProject_Name();//!< accessor: return the project name
        std::string getProject_Directory();//!< accessor: return the project Directory
        void setProject_Name(std::string Prj_Name);//!< accessor: return the project name
        void setProject_Directory(std::string Prj_Dir);//!< accessor: return the project Directory
        int setProject_Files();//!<search for src file in project directory (and subdirectorys)
        std::vector<Src_File> getProject_Files();//!< accessor: return the list of src file of the project
        std::string getLanguage(std::string File_Name);//!< return the file language from the file extension
        void setProject_L_M();//!< calculate Line of code metrics of the project = sum of loc metrics of the project's file
        L_M getProject_L_M();//!< return the Line of code metrics of the project
        void setProject_H_M();//!< calculate the Halstead metrics of the project = sum of Halstead of the project's file
        H_M getProject_H_M();//!< return the Halstead metrics of the project
        void setProject_M_M();//!< calculate the Mccab metrics of the project = sum of Mccabe metrics of the project's file
        M_M getProject_M_M();//!< return the Mccabe metrics of the project
        ~Project();//!< destructor
};

#endif // PROJECT_H_INCLUDED
