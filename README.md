# ZM_Source_Code_Metrics (debug version)
ZM Src Code Metrics allows you to calculate several code metrics: LOC, McCab and Halstead. This tool is developed in C ++ (tested on Windows and Linux) and whose aim is to support several programming languages. It generates a global report (project metrics) and detailed by file in the form of an XML file.

This version works very well, but some optimizations and functionalities must be added.

In this version, the processing of Command-line arguments is not yet implemented. Now you have to define the entries (two parameters) directly in the source code (main file: ZM_Source_Code_Metrics.cpp).

The two parameters to define are:
1) the path of the directory which contains the source codes for which we want to calculate the metrics, (the variable: std :: string Project_Dir = "path_to_your_files";),
2) the path of the programming language file (a configuration language file (.lng) specific to the programming language (c, c ++, ...) of your source), these files are included in the "languages" directory.
