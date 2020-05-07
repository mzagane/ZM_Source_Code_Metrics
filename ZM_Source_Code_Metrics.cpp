/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : main.cpp
  * description     : the main file
  * date of creation: 26/08/2016
  * date of update  :
  * @author          : Mohammed ZAGANE
  */

#include <iostream> // cout, cin,...
#include <fstream> // for : ofstream
#include "project.h" // for : Project,..
#include "load_parameters.h" // Load_All_Language_Parameters(...)
#include "report.h" // for: Generate_XML_Report(...),





//--------------------------------------



/**
  *
  * Program entry
  *
  */

int main() // the main function
{

    L_M Prj_L_M; // Line Of code metrics of the project
    M_M Prj_M_M; // McCab Metrics of the project
    H_M Prj_H_M; // Halstead Metrics of the project

    L_M File_L_M; // Line Of code metrics of a file
    M_M File_M_M; // McCab Metrics of a file
    H_M File_H_M; // Halstead Metrics a file

    //L_M Function_L_M // Line Of code metrics of a function
    M_M Function_M_M; // McCab Metrics of a function
    H_M Function_H_M; // Halstead Metrics of a function

    std::ofstream Log_File("ZM_Src_Code_Metrics_Report.txt");
    std::string Error_Message="";
    try
    {
        std::cout << "**************************************************" << std::endl;
        std::cout << "* ZM Source Code Metric V3.xx.04.2017            *" << std::endl;
        std::cout << "**************************************************" << std::endl << std::endl;
        Log_File << "**************************************************" << std::endl;
        Log_File << "* ZM Source Code Metric V3.xx.04.2017            *" << std::endl;
        Log_File << "**************************************************" << std::endl << std::endl;

        // win
        //std::string Project_Dir = "D:\\ZM\\Doctorat\\Mon_Travail\\Applications\\ZM_Source_Code_Metrics\\Source_For_Testing2\\";
        std::string Project_Dir = "TEST\\";
        //std::string Project_Dir = "D:\\ZM\\Doctorat\\Mon_Travail\\Applications\\ZM_Source_Code_Metrics\\Test_Java\\";
        //Linux
        //std::string Project_Dir = "/media/DATA/ZM/Doctorat/Mon_Travail/Applications/ZM_Source_Code_Metrics/Source_For_Testing2/";

        std::cout << "Calculating the code metrics for the Project in Directory : "<< std::endl;
        std::cout << Project_Dir << std::endl;

        Log_File<< "Calculating the code metrics for the Project in Directory : "<< std::endl;
        Log_File<< Project_Dir << std::endl;

        std::string Language_File_Name, Language;
        //Language = "cpp";
        //Language = "java";

        //Win
        Language_File_Name = "languages\\cpp.lng";
        //Linux
        //Language_File_Name = "/media/DATA/ZM/Doctorat/Mon_Travail/Applications/ZM_Source_Code_Metrics/languages/" + Language + ".lng";

        std::cout << "Loading Language parameters from : "<< std::endl;
        std::cout << Language_File_Name<< std::endl;
        std::cout << ".....................................";

        Log_File << "Loading Language parameters from : "<< std::endl;
        Log_File<< Language_File_Name<< std::endl;
        Log_File << "................................. ";
        if (Load_All_Language_Parameters(Language_File_Name) == 0)
        {
            std::cout << "OK"<< std::endl;
            Log_File<< "OK"<< std::endl;
        }
        else
        {
            std::cout << "FAILD!"<< std::endl;
            Log_File<< "FAILD!"<< std::endl;
            Error_Message = "Unable to load configuration !!! ):";
            goto Exist_Faild;
        }

        Project Test_Project = Project("Test_Project", Project_Dir);


        Prj_L_M = Test_Project.getProject_L_M(); // Line Of code metrics
        Prj_M_M = Test_Project.getProject_M_M(); // McCab Metrics
        Prj_H_M = Test_Project.getProject_H_M(); // Halstead Metrics

        std::cout <<"**************************************************"<<std::endl;
        std::cout <<"* Project files (Modules)                        *"<<std::endl;
        std::cout <<"**************************************************"<<std::endl <<std::endl;

        Log_File <<"**************************************************"<<std::endl;
        Log_File <<"* Project files (Modules)                        *"<<std::endl;
        Log_File <<"**************************************************"<<std::endl <<std::endl;

        int Nbr_Of_Files_In_Prject = Test_Project.getProject_Files().size();

        std::cout<< "Number of files (Module) = " << Nbr_Of_Files_In_Prject << std::endl << std::endl;

        Log_File<< "Number of files (Module) = " << Nbr_Of_Files_In_Prject << std::endl << std::endl;


        for (int i=0; i< Nbr_Of_Files_In_Prject; i++)
        {
            std::cout<<"----------------------------------------------------"<<std::endl;
            std::cout<<"- File "<< i + 1<< " : " << Test_Project.getProject_Files()[i].getSrc_File_Name()<< std::endl;
            std::cout<<"----------------------------------------------------"<<std::endl;

            Log_File<<"----------------------------------------------------"<<std::endl;
            Log_File<<"- File "<< i + 1<< " : " << Test_Project.getProject_Files()[i].getSrc_File_Name()<< std::endl;
            Log_File<<"----------------------------------------------------"<<std::endl;

            int Nbr_Of_Functions_In_File = Test_Project.getProject_Files()[i].getSrc_File_Functions().size();

            std::cout<<"     Number of functions = " << Nbr_Of_Functions_In_File << std::endl << std::endl;

            Log_File <<"     Number of functions = " << Nbr_Of_Functions_In_File << std::endl << std::endl;

            for (int j=0; j<Test_Project.getProject_Files()[i].getSrc_File_Functions().size();j++)
            {
                std::cout<<"     ----------------------------------------------------"<<std::endl;
                std::cout<<"     - Function "<< j + 1<< " : " << Test_Project.getProject_Files()[i].getSrc_File_Functions()[j].getFunction_Declarator() <<std::endl;
                std::cout<<"     ----------------------------------------------------"<<std::endl;

                Log_File<<"     ----------------------------------------------------"<<std::endl;
                Log_File<<"     - Function "<< j + 1<< " : " << Test_Project.getProject_Files()[i].getSrc_File_Functions()[j].getFunction_Declarator() <<std::endl;
                Log_File<<"     ----------------------------------------------------"<<std::endl;

                /**
                  * McCab metrics of the current function
                  */
                Function_M_M = Test_Project.getProject_Files()[i].getSrc_File_Functions()[j].Function_Mccab_Metrics.getMccab_Met();

                std::cout << "       McCab Metrics :" << std::endl<< std::endl;
                Log_File << "       McCab Metrics :" << std::endl<< std::endl;

                std::cout << "      - The Mc Cabe number (cyclomatic complexity) = " << Function_M_M.McCab_Number << std::endl;
                Log_File << "      - The Mc Cabe number (cyclomatic complexity) = " << Function_M_M.McCab_Number << std::endl;

                std::cout << std::endl<< std::endl;
                Log_File << std::endl<< std::endl;

                /**
                  * Halstead metrics of the current function
                  */
                Function_H_M = Test_Project.getProject_Files()[i].getSrc_File_Functions()[j].Function_Halstead_Metrics.getHalst_Met();

                std::cout << "       Halstead metrics:" << std::endl<< std::endl;
                Log_File << "       Halstead metrics:" << std::endl<< std::endl;

                std::cout << "       The number of distinct operators : n1 = " << Function_H_M.n1_Number_Of_Distinct_Operators<< std::endl;
                Log_File << "       The number of distinct operators : n1 = " << Function_H_M.n1_Number_Of_Distinct_Operators<< std::endl;
                std::cout << "       The number of distinct operands  : n2 = " << Function_H_M.n2_Number_Of_Distinct_Operands<< std::endl;
                Log_File << "       The number of distinct operands  : n2 = " << Function_H_M.n2_Number_Of_Distinct_Operands<< std::endl;
                std::cout << "       The total number of operators    : N1 = " << Function_H_M.N1_Total_Number_Of_Operators<< std::endl;
                Log_File << "       The total number of operators    : N1 = " << Function_H_M.N1_Total_Number_Of_Operators<< std::endl;
                std::cout << "       The total number of operands     : N2 = " << Function_H_M.N2_Total_Number_Of_Operands<< std::endl;
                Log_File << "       The total number of operands     : N2 = " << Function_H_M.N2_Total_Number_Of_Operands<< std::endl;
                std::cout << "       The program vocabulary           : n  = " << Function_H_M.n_Program_Vocabulary<< std::endl;
                Log_File << "       The program vocabulary           : n  = " << Function_H_M.n_Program_Vocabulary<< std::endl;
                std::cout << "       The program length               : N  = " << Function_H_M.N_Program_Length<< std::endl;
                Log_File << "       The program length               : N  = " << Function_H_M.N_Program_Length<< std::endl;
                std::cout << "       The Calculated program length    : N' = " << Function_H_M._N_Calculated_Program_Length << std::endl;
                Log_File << "       The Calculated program length    : N' = " << Function_H_M._N_Calculated_Program_Length << std::endl;
                std::cout << "       The program Volume               : V  = " << Function_H_M.V_Volume<< std::endl;
                Log_File << "       The program Volume               : V  = " << Function_H_M.V_Volume<< std::endl;
                std::cout << "       The program Difficulty           : D  = " << Function_H_M.D_Difficulty<< std::endl;
                Log_File << "       The program Difficulty           : D  = " << Function_H_M.D_Difficulty<< std::endl;
                std::cout << "       The program Effort               : E  = " << Function_H_M.E_Effort<< std::endl;
                Log_File << "       The program Effort               : E  = " << Function_H_M.E_Effort<< std::endl;
                std::cout << "       The Time required to program     : T  = " << Function_H_M.T_Time_Required_To_Program<< std::endl;
                Log_File << "       The Time required to program     : T  = " << Function_H_M.T_Time_Required_To_Program<< std::endl;
                std::cout << "       The Number of delivered Bugs 1   : B  = " << Function_H_M.B_Number_of_Delivered_Bugs_1<< std::endl;
                Log_File << "       The Number of delivered Bugs 1   : B  = " << Function_H_M.B_Number_of_Delivered_Bugs_1<< std::endl;
                std::cout << "       The Number of delivered Bugs 2   : B' = " << Function_H_M.B_Number_of_Delivered_Bugs_2<< std::endl;
                Log_File << "       The Number of delivered Bugs 2   : B' = " << Function_H_M.B_Number_of_Delivered_Bugs_2<< std::endl;

                std::cout << std::endl;
                Log_File <<  std::endl;

                std::cout<<"     ----------------------------------------------------"<<std::endl;
                std::cout<<"     - END Function "<< j+1 << std::endl;
                std::cout<<"     ----------------------------------------------------"<<std::endl;

                Log_File<<"     ----------------------------------------------------"<<std::endl;
                Log_File<<"     - END Function "<< j+1<< std::endl;
                Log_File<<"     ----------------------------------------------------"<<std::endl;

            }

            std::cout << std::endl<< std::endl;
            Log_File << std::endl<< std::endl;

            std::cout << "       Metrics of the file :" << std::endl<< std::endl;
            Log_File << "       Metrics of the file :" << std::endl<< std::endl;

            /**
              * Loc Metrics of the current file
              */

            File_L_M = Test_Project.getProject_Files()[i].getSrc_File_L_M();

            std::cout << "       Line Of Code metrics (LOC) :" << std::endl<< std::endl;
            Log_File << "       Line Of Code metrics (LOC) :" << std::endl<< std::endl;
            std::cout << "       - the number of physic lines      is : " << File_L_M.Physic_Lines<< std::endl;
            Log_File << "       - the number of physic lines      is : " << File_L_M.Physic_Lines<< std::endl;
            std::cout << "       - the number of empty lines       is : " << File_L_M.Empty_Lines<< std::endl;
            Log_File << "       - the number of empty lines       is : " << File_L_M.Empty_Lines<< std::endl;
            std::cout << "       - the number of lines of comments is : " << File_L_M.Lines_Of_Comments << std::endl;
            Log_File << "       - the number of lines of comments is : " << File_L_M.Lines_Of_Comments << std::endl;
            std::cout << "       - the number of lines of program  is : " << File_L_M.Lines_Of_Program << std::endl;
            Log_File << "       - the number of lines of program  is : " << File_L_M.Lines_Of_Program << std::endl;

            /**
              * McCab Metrics of the current file
              */
            File_M_M = Test_Project.getProject_Files()[i].getSrc_File_M_M();

            std::cout << std::endl;
            Log_File << std::endl;
            std::cout << "       McCab Metrics of the file" << std::endl<< std::endl;
            Log_File << "       McCab Metrics of the file" << std::endl<< std::endl;
            std::cout << "      - The McCabe number (cyclomatic complexity) = " << File_M_M.McCab_Number << std::endl;
            Log_File << "      - The McCabe number (cyclomatic complexity) = " << File_M_M.McCab_Number << std::endl;

            /**
              * Halstead Metrics of the current file
              */
            File_H_M = Test_Project.getProject_Files()[i].getSrc_File_H_M();
            std::cout << std::endl;
            Log_File << std::endl;

            std::cout << "       Halstead metrics of the file :" << std::endl<< std::endl;
            Log_File << "       Halstead metrics of the file :" << std::endl<< std::endl;

            std::cout << "       The number of distinct operators : n1 = " << File_H_M.n1_Number_Of_Distinct_Operators<< std::endl;
            Log_File << "       The number of distinct operators : n1 = " << File_H_M.n1_Number_Of_Distinct_Operators<< std::endl;
            std::cout << "       The number of distinct operands  : n2 = " << File_H_M.n2_Number_Of_Distinct_Operands<< std::endl;
            Log_File << "       The number of distinct operands  : n2 = " << File_H_M.n2_Number_Of_Distinct_Operands<< std::endl;
            std::cout << "       The total number of operators    : N1 = " << File_H_M.N1_Total_Number_Of_Operators<< std::endl;
            Log_File << "       The total number of operators    : N1 = " << File_H_M.N1_Total_Number_Of_Operators<< std::endl;
            std::cout << "       The total number of operands     : N2 = " << File_H_M.N2_Total_Number_Of_Operands<< std::endl;
            Log_File << "       The total number of operands     : N2 = " << File_H_M.N2_Total_Number_Of_Operands<< std::endl;
            std::cout << "       The program vocabulary           : n  = " << File_H_M.n_Program_Vocabulary<< std::endl;
            Log_File << "       The program vocabulary           : n  = " << File_H_M.n_Program_Vocabulary<< std::endl;
            std::cout << "       The program length               : N  = " << File_H_M.N_Program_Length<< std::endl;
            Log_File << "       The program length               : N  = " << File_H_M.N_Program_Length<< std::endl;
            std::cout << "       The Calculated program length    : N' = " << File_H_M._N_Calculated_Program_Length << std::endl;
            Log_File << "       The Calculated program length    : N' = " << File_H_M._N_Calculated_Program_Length << std::endl;
            std::cout << "       The program Volume               : V  = " << File_H_M.V_Volume<< std::endl;
            Log_File << "       The program Volume               : V  = " << File_H_M.V_Volume<< std::endl;
            std::cout << "       The program Difficulty           : D  = " << File_H_M.D_Difficulty<< std::endl;
            Log_File << "       The program Difficulty           : D  = " << File_H_M.D_Difficulty<< std::endl;
            std::cout << "       The program Effort               : E  = " << File_H_M.E_Effort<< std::endl;
            Log_File << "       The program Effort               : E  = " << File_H_M.E_Effort<< std::endl;
            std::cout << "       The Time required to program     : T  = " << File_H_M.T_Time_Required_To_Program<< std::endl;
            Log_File << "       The Time required to program     : T  = " << File_H_M.T_Time_Required_To_Program<< std::endl;
            std::cout << "       The Number of delivered Bugs 1   : B  = " << File_H_M.B_Number_of_Delivered_Bugs_1<< std::endl;
            Log_File << "       The Number of delivered Bugs 1   : B  = " << File_H_M.B_Number_of_Delivered_Bugs_1<< std::endl;
            std::cout << "       The Number of delivered Bugs 2   : B' = " << File_H_M.B_Number_of_Delivered_Bugs_2<< std::endl;
            Log_File << "       The Number of delivered Bugs 2   : B' = " << File_H_M.B_Number_of_Delivered_Bugs_2<< std::endl;


            std::cout<<"----------------------------------------------------"<<std::endl;
            std::cout<<"- END File "<< i + 1<< " : " << Test_Project.getProject_Files()[i].getSrc_File_Name()<< std::endl;
            std::cout<<"----------------------------------------------------"<<std::endl <<std::endl;

            Log_File<<"----------------------------------------------------"<<std::endl;
            Log_File<<"- END File "<< i + 1<< " : " << Test_Project.getProject_Files()[i].getSrc_File_Name()<< std::endl;
            Log_File<<"----------------------------------------------------"<<std::endl<<std::endl;

        }

        std::cout << std::endl<< std::endl<< std::endl<< std::endl;
        Log_File << std::endl<< std::endl<< std::endl<< std::endl;

        std::cout <<"**************************************************"<<std::endl;
        std::cout <<"* Metrics of the project                         *"<<std::endl;
        std::cout <<"**************************************************"<<std::endl <<std::endl;

        Log_File <<"**************************************************"<<std::endl;
        Log_File <<"* Metrics of the project                         *"<<std::endl;
        Log_File <<"**************************************************"<<std::endl <<std::endl;


        std::cout << "Line Of Code metrics (LOC) :" << std::endl<< std::endl;
        Log_File << "Line Of Code metrics (LOC) :" << std::endl<< std::endl;
        std::cout << " - the number of physic lines      is : " << Prj_L_M.Physic_Lines<< std::endl;
        Log_File << " - the number of physic lines      is : " << Prj_L_M.Physic_Lines<< std::endl;
        std::cout << " - the number of empty lines       is : " << Prj_L_M.Empty_Lines<< std::endl;
        Log_File << " - the number of empty lines       is : " << Prj_L_M.Empty_Lines<< std::endl;
        std::cout << " - the number of lines of comments is : " << Prj_L_M.Lines_Of_Comments << std::endl;
        Log_File << " - the number of lines of comments is : " << Prj_L_M.Lines_Of_Comments << std::endl;
        std::cout << " - the number of lines of program  is : " << Prj_L_M.Lines_Of_Program << std::endl;
        Log_File << " - the number of lines of program  is : " << Prj_L_M.Lines_Of_Program << std::endl;
        std::cout << std::endl;
        Log_File << std::endl;
        std::cout << "Cyclomatic complexity  VG():" << std::endl<< std::endl;
        Log_File << "Cyclomatic complexity  VG():" << std::endl<< std::endl;
        std::cout << "- the Mc Cabe number               is : " << Prj_M_M.McCab_Number << std::endl;
        Log_File << "- the Mc Cabe number               is : " << Prj_M_M.McCab_Number << std::endl;
        std::cout << std::endl;
        Log_File << std::endl;
        std::cout << "Halstead metrics:" << std::endl<< std::endl;
        Log_File << "Halstead metrics:" << std::endl<< std::endl;
        std::cout << "The number of distinct operators : n1 = " << Prj_H_M.n1_Number_Of_Distinct_Operators<< std::endl;
        Log_File << "The number of distinct operators : n1 = " << Prj_H_M.n1_Number_Of_Distinct_Operators<< std::endl;
        std::cout << "The number of distinct operands  : n2 = " << Prj_H_M.n2_Number_Of_Distinct_Operands<< std::endl;
        Log_File << "The number of distinct operands  : n2 = " << Prj_H_M.n2_Number_Of_Distinct_Operands<< std::endl;
        std::cout << "The total number of operators    : N1 = " << Prj_H_M.N1_Total_Number_Of_Operators<< std::endl;
        Log_File << "The total number of operators    : N1 = " << Prj_H_M.N1_Total_Number_Of_Operators<< std::endl;
        std::cout << "The total number of operands     : N2 = " << Prj_H_M.N2_Total_Number_Of_Operands<< std::endl;
        Log_File << "The total number of operands     : N2 = " << Prj_H_M.N2_Total_Number_Of_Operands<< std::endl;
        std::cout << "The program vocabulary           : n  = " << Prj_H_M.n_Program_Vocabulary<< std::endl;
        Log_File << "The program vocabulary           : n  = " << Prj_H_M.n_Program_Vocabulary<< std::endl;
        std::cout << "The program length               : N  = " << Prj_H_M.N_Program_Length<< std::endl;
        Log_File << "The program length               : N  = " << Prj_H_M.N_Program_Length<< std::endl;
        std::cout << "The Calculated program length    : N' = " << Prj_H_M._N_Calculated_Program_Length << std::endl;
        Log_File << "The Calculated program length    : N' = " << Prj_H_M._N_Calculated_Program_Length << std::endl;
        std::cout << "The program Volume               : V  = " << Prj_H_M.V_Volume<< std::endl;
        Log_File << "The program Volume               : V  = " << Prj_H_M.V_Volume<< std::endl;
        std::cout << "The program Difficulty           : D  = " << Prj_H_M.D_Difficulty<< std::endl;
        Log_File << "The program Difficulty           : D  = " << Prj_H_M.D_Difficulty<< std::endl;
        std::cout << "The program Effort               : E  = " << Prj_H_M.E_Effort<< std::endl;
        Log_File << "The program Effort               : E  = " << Prj_H_M.E_Effort<< std::endl;
        std::cout << "The Time required to program     : T  = " << Prj_H_M.T_Time_Required_To_Program<< std::endl;
        Log_File << "The Time required to program     : T  = " << Prj_H_M.T_Time_Required_To_Program<< std::endl;
        std::cout << "The Number of delivered Bugs 1   : B  = " << Prj_H_M.B_Number_of_Delivered_Bugs_1<< std::endl;
        Log_File << "The Number of delivered Bugs 1   : B  = " << Prj_H_M.B_Number_of_Delivered_Bugs_1<< std::endl;
        std::cout << "The Number of delivered Bugs 2   : B' = " << Prj_H_M.B_Number_of_Delivered_Bugs_2<< std::endl;
        Log_File << "The Number of delivered Bugs 2   : B' = " << Prj_H_M.B_Number_of_Delivered_Bugs_2<< std::endl;


        Generate_XML_Report(Test_Project, "zm_src_code_metrics_report.xml");

    }
    catch (...)
    {
        std::cout<< " Unknown ERROR !!!";
        Log_File << " Unknown ERROR !!!";
    }

    Clear_Vectors();
    return 0;


    Exist_Faild:
    {
        std::cout << "ZM Source Metric V3.xx.05.2017 terminated with errors :"<< std::endl;
        Log_File <<  "ZM Source Metric V3.xx.05.2017 terminated with errors :"<< std::endl;
        std::cout << Error_Message<< std::endl;
        Log_File << Error_Message<< std::endl;
        return -1;
    }
}
