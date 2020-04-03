/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : mccab_metric.h
  * description     : header file for mccab_metric module
  * date of creation: 27/10/2016
  * date of update  : 03/01/2017
  * @author          : Mohammed ZAGANE
  */

#ifndef MCCAB_METRICS_H_INCLUDED
#define MCCAB_METRICS_H_INCLUDED
#include <vector>// vector

/**
  * Mccab Metrics
  */
struct M_M
{
    int McCab_Number;//!< the cyclomatic complexity (McCab Number)

    void M_M_Init();//!< initialization of the M_M structure to 0
};
class Mccab_Metrics
{
    //Attributes
    private :
        M_M Mccab_Met;//!< the McCab metrics structure
    //Methods
    public :
        Mccab_Metrics();
        ~Mccab_Metrics();
        void setMcCab_Number(std::vector<std::string> Input_Code); //!< accessors : count the cyclomatic complexity (McCab Number)
        int  getMcCab_Number(); //!< accessors : return the cyclomatic complexity (McCab Number)
        void setMccab_Met(std::vector<std::string> Input_Code);//!< set the McCab metrics structure by calling setMcCab_Number()
        M_M getMccab_Met();//!< accessors : get the McCab metrics structure
};
#endif // MCCAB_METRICS_H_INCLUDED
