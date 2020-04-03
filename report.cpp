/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : report.cpp
  * description     : this file contains code for generating XML report
  * date of creation: 30/04/2017
  * date of update  :
  * @author          : Mohammed ZAGANE
  */

#include <fstream> // for : ofstream

#include "project.h" // for Project
#include "report.h"
#include "loc_metrics.h" // for L_M
#include "halstead_metrics.h" // for H_M
#include "mccab_metrics.h"// for M_M



/**
  * This function generate a report file in XML format
  * Parameters :
  *  - 'Project The_Project' : Object of 'Project' type
  *  The project that we need to generate the report file for
  *  - 'std::string Report_Name' : The report name
  * Returned values
  *  -  0 file successfully generated
  */

int Generate_XML_Report (Project The_Project, std::string Report_Name)
{


    L_M Prj_L_M; // Line Of code metrics of the project
    M_M Prj_M_M; // McCab Metrics of the project
    H_M Prj_H_M; // Halstead Metrics of the project

    L_M File_L_M; // Line Of code metrics of a file
    M_M File_M_M; // McCab Metrics of a file
    H_M File_H_M; // Halstead Metrics a file

    //L_M Function_L_M // Line Of code metrics of a function
    L_M Function_L_M; // McCab Metrics of a function
    M_M Function_M_M; // McCab Metrics of a function
    H_M Function_H_M; // Halstead Metrics of a function

    std::ofstream XML_Log_File(Report_Name);
    XML_Log_File<< "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>"<< std::endl;
    XML_Log_File<< "<zm_src_code_metrics_report>"<< std::endl;
    XML_Log_File<< "    <project_info>"<< std::endl;
    XML_Log_File<< "        <project_name> "<< The_Project.getProject_Name()<< " </project_name>"<< std::endl;
    XML_Log_File<< "    </project_info>"<< std::endl;

    int Nbr_Of_Files_In_Prject = The_Project.getProject_Files().size();

    XML_Log_File<< "    <project_files>"<< std::endl;
    for (int i=0; i< Nbr_Of_Files_In_Prject; i++)
    {
        XML_Log_File<< "        <file>"<< std::endl;
        XML_Log_File<< "            <file_name> " << The_Project.getProject_Files()[i].getSrc_File_Name() << " </file_name>"<< std::endl;
        XML_Log_File<< "            <file_language> " << The_Project.getProject_Files()[i].getSrc_File_Language() << " </file_language>"<< std::endl;


        XML_Log_File<< "            <file_modules>"<< std::endl;
        int Nbr_Of_Functions_In_File = The_Project.getProject_Files()[i].getSrc_File_Functions().size();

        for (int j=0; j<The_Project.getProject_Files()[i].getSrc_File_Functions().size();j++)
        {
            XML_Log_File<< "                <module>"<< std::endl;
            XML_Log_File<< "                    <module_name> "<< The_Project.getProject_Files()[i].getSrc_File_Functions()[j].getFunction_Declarator() << " </module_name>" <<std::endl;

            /**
              * Metrics of the current function
              */
            Function_L_M = The_Project.getProject_Files()[i].getSrc_File_Functions()[j].Function_Loc_Metrics.getL_Met();
            Function_M_M = The_Project.getProject_Files()[i].getSrc_File_Functions()[j].Function_Mccab_Metrics.getMccab_Met();
            Function_H_M = The_Project.getProject_Files()[i].getSrc_File_Functions()[j].Function_Halstead_Metrics.getHalst_Met();

            XML_Log_File<< "                    <module_metrics> "<< std::endl;

            XML_Log_File<< "                        <loc> "<< std::endl;
            XML_Log_File<< "                            <physic_lines> "<< Function_L_M.Physic_Lines << " </physic_lines>" <<std::endl;
            XML_Log_File<< "                            <empty_lines> "<< Function_L_M.Empty_Lines << " </empty_lines>" <<std::endl;
            XML_Log_File<< "                            <lines_of_comments> "<< Function_L_M.Lines_Of_Comments << " </lines_of_comments>" <<std::endl;
            XML_Log_File<< "                            <lines_of_program> "<< Function_L_M.Lines_Of_Program << " </lines_of_program>" <<std::endl;
            XML_Log_File<< "                        </loc> "<< std::endl;

            XML_Log_File<< "                        <mccab> "<< std::endl;
            XML_Log_File<< "                            <cyclomatic_complexity> "<< Function_M_M.McCab_Number << " </cyclomatic_complexity>" <<std::endl;
            XML_Log_File<< "                        </mccab> "<< std::endl;

            XML_Log_File<< "                        <halstead> "<< std::endl;
            XML_Log_File<< "                            <n1> "<< Function_H_M.n1_Number_Of_Distinct_Operators << " </n1>" <<std::endl;
            XML_Log_File<< "                            <n2> "<< Function_H_M.n2_Number_Of_Distinct_Operands << " </n2>" <<std::endl;
            XML_Log_File<< "                            <N1> "<< Function_H_M.N1_Total_Number_Of_Operators << " </N1>" <<std::endl;
            XML_Log_File<< "                            <N2> "<< Function_H_M.N2_Total_Number_Of_Operands << " </N2>" <<std::endl;
            XML_Log_File<< "                            <n> "<< Function_H_M.n_Program_Vocabulary << " </n>" <<std::endl;
            XML_Log_File<< "                            <N> "<< Function_H_M.N_Program_Length << " </N>" <<std::endl;
            XML_Log_File<< "                            <N_> "<< Function_H_M._N_Calculated_Program_Length << " </N_>" <<std::endl;
            XML_Log_File<< "                            <V> "<< Function_H_M.V_Volume << " </V>" <<std::endl;
            XML_Log_File<< "                            <D> "<< Function_H_M.D_Difficulty << " </D>" <<std::endl;
            XML_Log_File<< "                            <E> "<< Function_H_M.E_Effort << " </E>" <<std::endl;
            XML_Log_File<< "                            <T> "<< Function_H_M.T_Time_Required_To_Program << " </T>" <<std::endl;
            XML_Log_File<< "                            <B> "<< Function_H_M.B_Number_of_Delivered_Bugs_1 << " </B>" <<std::endl;
            XML_Log_File<< "                            <B_> "<< Function_H_M.B_Number_of_Delivered_Bugs_2 << " </B_>" <<std::endl;
            XML_Log_File<< "                        </halstead> "<< std::endl;
            XML_Log_File<< "                    </module_metrics> "<< std::endl;
            XML_Log_File<< "                </module>"<< std::endl;
        }

        XML_Log_File<< "            </file_modules>"<< std::endl;

        /**
          * Metrics of the current file
          */
        File_L_M = The_Project.getProject_Files()[i].getSrc_File_L_M();
        File_M_M = The_Project.getProject_Files()[i].getSrc_File_M_M();
        File_H_M = The_Project.getProject_Files()[i].getSrc_File_H_M();

        XML_Log_File<< "            <file_metrics> "<< std::endl;

        XML_Log_File<< "                <loc> "<< std::endl;
        XML_Log_File<< "                    <physic_lines> "<< File_L_M.Physic_Lines << " </physic_lines>" <<std::endl;
        XML_Log_File<< "                    <empty_lines> "<< File_L_M.Empty_Lines << " </empty_lines>" <<std::endl;
        XML_Log_File<< "                    <lines_of_comments> "<< File_L_M.Lines_Of_Comments << " </lines_of_comments>" <<std::endl;
        XML_Log_File<< "                    <lines_of_program> "<< File_L_M.Lines_Of_Program << " </lines_of_program>" <<std::endl;
        XML_Log_File<< "                </loc> "<< std::endl;

        XML_Log_File<< "                <mccab> "<< std::endl;
        XML_Log_File<< "                    <cyclomatic_complexity> "<< File_M_M.McCab_Number << " </cyclomatic_complexity>" <<std::endl;
        XML_Log_File<< "                </mccab> "<< std::endl;

        XML_Log_File<< "                <halstead> "<< std::endl;
        XML_Log_File<< "                    <n1> "<< File_H_M.n1_Number_Of_Distinct_Operators << " </n1>" <<std::endl;
        XML_Log_File<< "                    <n2> "<< File_H_M.n2_Number_Of_Distinct_Operands << " </n2>" <<std::endl;
        XML_Log_File<< "                    <N1> "<< File_H_M.N1_Total_Number_Of_Operators << " </N1>" <<std::endl;
        XML_Log_File<< "                    <N2> "<< File_H_M.N2_Total_Number_Of_Operands << " </N2>" <<std::endl;
        XML_Log_File<< "                    <n> "<< File_H_M.n_Program_Vocabulary << " </n>" <<std::endl;
        XML_Log_File<< "                    <N> "<< File_H_M.N_Program_Length << " </N>" <<std::endl;
        XML_Log_File<< "                    <N_> "<< File_H_M._N_Calculated_Program_Length << " </N_>" <<std::endl;
        XML_Log_File<< "                    <V> "<< File_H_M.V_Volume << " </V>" <<std::endl;
        XML_Log_File<< "                    <D> "<< File_H_M.D_Difficulty << " </D>" <<std::endl;
        XML_Log_File<< "                    <E> "<< File_H_M.E_Effort << " </E>" <<std::endl;
        XML_Log_File<< "                    <T> "<< File_H_M.T_Time_Required_To_Program << " </T>" <<std::endl;
        XML_Log_File<< "                    <B> "<< File_H_M.B_Number_of_Delivered_Bugs_1 << " </B>" <<std::endl;
        XML_Log_File<< "                    <B_> "<< File_H_M.B_Number_of_Delivered_Bugs_2 << " </B_>" <<std::endl;
        XML_Log_File<< "                 </halstead> "<< std::endl;
        XML_Log_File<< "            </file_metrics> "<< std::endl;

        XML_Log_File<< "        </file>"<< std::endl;

    }

    XML_Log_File<< "    </project_files>"<< std::endl;

    Prj_L_M = The_Project.getProject_L_M(); // Line Of code metrics
    Prj_M_M = The_Project.getProject_M_M(); // McCab Metrics
    Prj_H_M = The_Project.getProject_H_M(); // Halstead Metrics

    XML_Log_File<< "    <project_metrics> "<< std::endl;

    XML_Log_File<< "        <loc> "<< std::endl;
    XML_Log_File<< "            <physic_lines> "<< Prj_L_M.Physic_Lines << " </physic_lines>" <<std::endl;
    XML_Log_File<< "            <empty_lines> "<< Prj_L_M.Empty_Lines << " </empty_lines>" <<std::endl;
    XML_Log_File<< "            <lines_of_comments> "<< Prj_L_M.Lines_Of_Comments << " </lines_of_comments>" <<std::endl;
    XML_Log_File<< "            <lines_of_program> "<< Prj_L_M.Lines_Of_Program << " </lines_of_program>" <<std::endl;
    XML_Log_File<< "        </loc> "<< std::endl;

    XML_Log_File<< "        <mccab> "<< std::endl;
    XML_Log_File<< "            <cyclomatic_complexity> "<< Prj_M_M.McCab_Number << " </cyclomatic_complexity>" <<std::endl;
    XML_Log_File<< "        </mccab> "<< std::endl;

    XML_Log_File<< "        <halstead> "<< std::endl;
    XML_Log_File<< "            <n1> "<< Prj_H_M.n1_Number_Of_Distinct_Operators << " </n1>" <<std::endl;
    XML_Log_File<< "            <n2> "<< Prj_H_M.n2_Number_Of_Distinct_Operands << " </n2>" <<std::endl;
    XML_Log_File<< "            <N1> "<< Prj_H_M.N1_Total_Number_Of_Operators << " </N1>" <<std::endl;
    XML_Log_File<< "            <N2> "<< Prj_H_M.N2_Total_Number_Of_Operands << " </N2>" <<std::endl;
    XML_Log_File<< "            <n> "<< Prj_H_M.n_Program_Vocabulary << " </n>" <<std::endl;
    XML_Log_File<< "            <N> "<< Prj_H_M.N_Program_Length << " </N>" <<std::endl;
    XML_Log_File<< "            <N_> "<< Prj_H_M._N_Calculated_Program_Length << " </N_>" <<std::endl;
    XML_Log_File<< "            <V> "<< Prj_H_M.V_Volume << " </V>" <<std::endl;
    XML_Log_File<< "            <D> "<< Prj_H_M.D_Difficulty << " </D>" <<std::endl;
    XML_Log_File<< "            <E> "<< Prj_H_M.E_Effort << " </E>" <<std::endl;
    XML_Log_File<< "            <T> "<< Prj_H_M.T_Time_Required_To_Program << " </T>" <<std::endl;
    XML_Log_File<< "            <B> "<< Prj_H_M.B_Number_of_Delivered_Bugs_1 << " </B>" <<std::endl;
    XML_Log_File<< "            <B_> "<< Prj_H_M.B_Number_of_Delivered_Bugs_2 << " </B_>" <<std::endl;
    XML_Log_File<< "        </halstead> "<< std::endl;
    XML_Log_File<< "    </project_metrics> "<< std::endl;

    XML_Log_File<< "</zm_src_code_metrics_report>"<< std::endl;

    return 0;
}
