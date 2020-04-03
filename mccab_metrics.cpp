/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : mccab_metric.cpp
  * description     : implementation file for mccab_metric module
  * date of creation: 27/10/2016
  * date of update  : 17/01/2017
  * @author          : Mohammed ZAGANE
  */
#include <fstream> // ifstream
#include <vector>// vector
#include "preprocessing.h"
#include "mccab_metrics.h"
#include "load_parameters.h"

/**
  *
  */
void M_M::M_M_Init()
{
    McCab_Number = 0;
}
/**
  * constructor
  */
Mccab_Metrics::Mccab_Metrics()
{
    //
}
/**
  * destructor
  */
Mccab_Metrics::~Mccab_Metrics()
{
    //
}
/**
  * this function return the Mc Cabe number (cyclomatic complexity)
  */
void Mccab_Metrics::setMcCab_Number(std::vector<std::string> Input_Code)
{
    int McCab_Nbr = 1;
    std::string Line;
    unsigned long Index =0;

    while (Index< Input_Code.size())
    {
        Line = Input_Code[Index];
        for(int i=0;i<Control_Commands.size();i++)//
        {
            int j=0;
            int k=0;
            bool not_found = true;
            do
            {
                k = Line.find(Control_Commands[i], j);
                if( (k >=0) && (k<= Line.length()) )
                {
                    McCab_Nbr++;
                    j = k + Control_Commands[i].length();
                    not_found = false;
                }
                else
                {
                    not_found = true;
                }

            }while(!not_found);
        }
        Index++;
    }
    Mccab_Met.McCab_Number = McCab_Nbr;
}

/**
  * Accessors : return the McCabe number (cyclomatic complexity)
  */
int Mccab_Metrics::getMcCab_Number()
{
    return Mccab_Met.McCab_Number;
}
/**
  * set the McCab metrics structure by calling setMcCab_Number()
  */
void Mccab_Metrics::setMccab_Met(std::vector<std::string> Input_Code)
{
    setMcCab_Number(Input_Code);
}
/**
  * accessors : get the McCab metrics structure
  */
M_M Mccab_Metrics::getMccab_Met()
{
    return Mccab_Met;
}
