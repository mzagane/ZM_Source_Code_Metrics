/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : project.cpp
  * description     : implementation file for project module (class)
  * date of creation: 14/01/2017
  * date of update  :
  * author          : Mohammed ZAGANE
  * Description     : this file contains the definition of the project class methods
  *                   constructor, accessors and all related functions
  */
#include <dirent.h>//working with directory
#include "project.h"

//constructor
Project::Project(std::string Prj_Name, std::string Prj_Dir)
{
    Project_Name = Prj_Name;
    Project_Directory = Prj_Dir;
    setProject_Files();//search for src file in project directory (and subdirectorys)
    setProject_L_M();//calculate Line of code metrics of the project = sum of loc metrics of the project's file
    setProject_H_M();//calculate the Halstead metrics of the project = sum of Halstead of the project's file
    setProject_M_M();//calculate the Mccab metrics of the project = sum of Mccabe metrics of the project's file
}

Project::Project()
{
    //---
}
// accessor Project_Name
void Project::setProject_Name(std::string Prj_Name)
{
    Project_Name = Prj_Name;
}
// accessor Project_Directory
void Project::setProject_Directory(std::string Prj_Dir)
{
    Project_Directory = Prj_Dir;
}
// accessor Project_Name
std::string Project::getProject_Name()
{
    return Project_Name;
}
// accessor Project_Directory
std::string Project::getProject_Directory()
{
    return Project_Directory;
}

/**
  * this function extracts the extension from the file name
  * and return the src language
  */
std::string Project::getLanguage(std::string File_Name)
{
    std::string Src_File_Extension = File_Name.substr(File_Name.rfind(".")+1,File_Name.size()-1);

    if (Src_File_Extension == "cpp" || Src_File_Extension == "cc" || Src_File_Extension == "cxx" || Src_File_Extension == "h")
    {
        return "cpp";
    }
    else if (Src_File_Extension == "c")
    {
        return "c";
    }
    else if (Src_File_Extension == "java")
    {
        return "java";
    }
    else if (Src_File_Extension == "pas")
    {
        return "pascal";
    }
    else
    {
        return "NOT_A_SRC_FILE";
    }
}

/**
  * search for src files in the project directory
  */
int Project::setProject_Files()
{
    DIR *Directory;
    DIR *TEMP;
    struct dirent *Dirent;
    std::string File_Name, Lang;
    unsigned int File_Number = 0;
    Src_File * New_Src_File;

    if ((Directory = opendir (getProject_Directory().c_str())) != NULL)
    {
        while ((Dirent = readdir (Directory)) != NULL)
        {
            //if (Dirent->d_type != DT_DIR)
            if ((TEMP = opendir(Dirent->d_name))) 
            {
                closedir(TEMP);
            }
            else
            {
                File_Name = Dirent->d_name;
                Lang = getLanguage(File_Name);
                if (Lang != "NOT_A_SRC_FILE")
                {
                    //creating a new Src_File
                    New_Src_File = new Src_File();
                    New_Src_File->setSrc_File_Name(getProject_Directory()+File_Name);
                    New_Src_File->setSrc_File_Language(Lang);
                    New_Src_File->setSrc_File_Functions();
                    Project_Files.insert(Project_Files.end(), *New_Src_File);
                    File_Number++;
                }

            }
        }
    }
    else
    {
        return -1;// unable to open the directory
    }
    closedir (Directory);

    //delete New_Src_File;
    return File_Number;
}
// accessor Project_Files
std::vector<Src_File> Project::getProject_Files()
{
    return Project_Files;
}
/**
  * return the Mccabe metrics of the project
  */
M_M Project::getProject_M_M()
{
    return Project_M_M;
}
/**
  * return the Halstead metrics of the project
  */
H_M Project::getProject_H_M()
{
    return Project_H_M;
}
/**
  * return the loc metrics of the project
  */
L_M Project::getProject_L_M()
{
    return Project_L_M;
}
/**
  * calculate Line of code metrics of the project = sum of loc metrics of the project's file
  */
void Project::setProject_L_M()
{
    L_M Temp;
    Project_L_M.L_M_Init();
    for (int i=0; i<Project_Files.size(); i++)
    {
        Project_Files[i].setSrc_File_L_M();
        Temp = Project_Files[i].getSrc_File_L_M();
        Project_L_M.Empty_Lines       += Temp.Empty_Lines;
        Project_L_M.Lines_Of_Comments += Temp.Lines_Of_Comments;
        Project_L_M.Lines_Of_Program  += Temp.Lines_Of_Program;
        Project_L_M.Physic_Lines      += Temp.Physic_Lines;
    }

}

/**
  * calculate Halstead metrics of the project = sum of Halstead metrics of the project's file
  */
void Project::setProject_H_M()
{
    H_M Temp;
    Project_H_M.H_M_Init();
    for (int i=0; i<Project_Files.size(); i++)
    {
        Project_Files[i].setSrc_File_H_M();
        Temp = Project_Files[i].getSrc_File_H_M();
        Project_H_M.B_Number_of_Delivered_Bugs_1    += Temp.B_Number_of_Delivered_Bugs_1;
        Project_H_M.B_Number_of_Delivered_Bugs_2    += Temp.B_Number_of_Delivered_Bugs_2;
        Project_H_M.D_Difficulty                    += Temp.D_Difficulty;
        Project_H_M.E_Effort                        += Temp.E_Effort;
        Project_H_M.n1_Number_Of_Distinct_Operators += Temp.n1_Number_Of_Distinct_Operators;
        Project_H_M.N1_Total_Number_Of_Operators    += Temp.N1_Total_Number_Of_Operators;
        Project_H_M.n2_Number_Of_Distinct_Operands  += Temp.n2_Number_Of_Distinct_Operands;
        Project_H_M.N2_Total_Number_Of_Operands     += Temp.N2_Total_Number_Of_Operands;
        Project_H_M.N_Program_Length                += Temp.N_Program_Length;
        Project_H_M.n_Program_Vocabulary            += Temp.n_Program_Vocabulary;
        Project_H_M.T_Time_Required_To_Program      += Temp.T_Time_Required_To_Program;
        Project_H_M.V_Volume                        += Temp.V_Volume;
        Project_H_M._N_Calculated_Program_Length    += Temp._N_Calculated_Program_Length;
    }
}

/**
  * calculate Mccabe metrics of the project = sum of Mccabe metrics of the project's file
  */
void Project::setProject_M_M()
{
    M_M Temp;
    Project_M_M.M_M_Init();
    for (int i=0; i<Project_Files.size(); i++)
    {
        Project_Files[i].setSrc_File_M_M();
        Temp = Project_Files[i].getSrc_File_M_M();
        Project_M_M.McCab_Number    += Temp.McCab_Number ;
    }
}

// destructors : free the dynamically  created objects
Project::~Project()
{
    //
}

/*************************************************************************
*                          END PROJECT CLASS                             *
*************************************************************************/
