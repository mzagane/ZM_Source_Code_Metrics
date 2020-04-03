/**
  * Project         : ZM SOURCE CODE METRICS
  * File            : tokeniser.cpp
  * description     : implementation file for tokeniser module
  * date of creation: 04/11/2016
  * date of update  :
  * author          : Mohammed ZAGANE
  */

/**
  * include
  */
#include <fstream> // ifstream
#include <cstring>// strtok
#include <regex> // smatch, regex
#include "preprocessing.h"
#include "halstead_metrics.h"
#include "load_parameters.h"
#include "tokeniser.h"

//--- debug : to delete
#include <iostream>
//---------


/**
  * this function it's used by the Generate_Tokens_List_Second_Pass and Generate_Tokens_List_Third_Pass
  *  to detect the string token to avoid reprocessing line
  */

bool Is_A_String_Token (std::string Line)
{
    for (unsigned int i=0; i<String_Markup.size();i++)
    {
        if((Line.substr(0,1) == String_Markup[i]) && (Line.substr(Line.length()-1,1) == String_Markup[i]))
        {

            return true;
        }
    }

    return false;
}

/**
  * this function it's used by the Generate_Tokens_List_Third_Pass to detect the char token
  * to avoid reprocessing line
  */

bool Is_A_Char_Token (std::string Line)
{
    for (unsigned int i=0; i<Char_Markup.size();i++)
    {
        if((Line.substr(0,1) == Char_Markup[i]) && (Line.substr(Line.length()-1,1) == Char_Markup[i]))
        {

            return true;
        }
    }

    return false;

}



/**
  * this function it's used by the Generate_Tokens_List_Fourth_Pass
  *  to detect the string token to avoid reprocessing line
  */

bool Is_A_Number_Token (std::string Line)
{
    //Regular expression for the numbers tokens
    std::string Int_Regex = Integer_Number_Regex[0];
    std::string Rel_Regex = Real_Number_Regex[0];
    std::string Oct_Regex = Octal_Number_Regex[0];
    std::string Hex_Regex = Hexadecimal_Number_Regex[0];
    std::regex Int_Nbr_Regex (Int_Regex.c_str());
    std::regex Rel_Nbr_Regex (Rel_Regex.c_str());
    std::regex Oct_Nbr_Regex (Oct_Regex.c_str());
    std::regex Hex_Nbr_Regex (Hex_Regex.c_str());

    /* j'ai separe les tests pour eviter les eventuels problems
     de priorite : peut etre un reel est concidere comme un entier
    en recuperant juste la partie entiere : 252.52 --> 252  .   52
    ,...*/
    if (regex_match(Line, Rel_Nbr_Regex) )
    {
        return true;
    }
    else if (regex_match(Line, Int_Nbr_Regex) )
    {
        return true;
    }
    else if (regex_match(Line, Hex_Nbr_Regex) )
    {
        return true;
    }
    else if (regex_match(Line, Oct_Nbr_Regex) )
    {
        return true;
    }
    else
    {
        return false;
    }

}

/**
 * this function generates the list of the program token
 * Parameters :
 *  - string Source_Code_File_Name : full path to the source code file to process
 *  - string vector contain the tokens
 *  - empty vector if the function fails
 */

std::vector<std::string> Generate_Tokens_List(std::vector<std::string> Input_Code)
{
    std::vector<std::string>  Tokens_List;
    //extracting code from the source file
    std::vector<std::string> Program_Code = Extract_Code (Input_Code);
    std::vector<std::string> Tokens_First_Pass = Separate_Strings(Program_Code); // first pass : separates string tokens
    std::vector<std::string> Tokens_Second_Pass = Separate_Chars(Tokens_First_Pass); // second pass : separates the char tokens
    std::vector<std::string> Tokens_Third_Pass = Separate_Numbers(Tokens_Second_Pass); // third pass : separates the number tokens
    Tokens_List = Generate_Tokens_List_Fourth_Pass(Tokens_Third_Pass);// tokenising the remaining code

    return Tokens_List;
}


/**
  * this function make the first pass of generating program tokens, it's separate string tokens from code
  * Parameters :
  * - vector<string> : string vector (only code : without comments,...)
  * Returned values :
  * -  string vector contains the first pass tokens
  */

std::vector<std::string> Separate_Strings(std::vector<std::string> Input_Code)
{

    std::vector<std::string>  Tokens_List;
    std::string Line="", Previous_Line="", Token="";
    std::string Befor_String_Markup = Befor_Str_Markup[0]; // Befor_String_Markup is the char added to string markup
                                                        // to add this markup to a string like in c++ : "abcd :\" def"
                                                        // pascal : 'abcd : '' def'
    bool First_String_Markup_Found = false; // to indicate that the first string markup found or not yet
    bool Last_String_Markup_Found = false;// to indicate that the last string markup found or not yet
    bool String_Found_In_Line = false; // to indicate that a string found in the line or not
    int Str_Mrkp_Index = 0;/* it used to indicate witch string markup used (' or ") in language
                            like javascript, php wich have more then one markup for string*/
    unsigned long Index = 0; // to manepelate the Lines char by char
    unsigned long Ind =0;
    while (Ind< Input_Code.size())
    {
        Line = Input_Code[Ind];
        String_Found_In_Line = false;
        Index = 0;
        if (!String_Found_In_Line) // no string is found in the line
        {
            for (unsigned int i=0; i<String_Markup.size();i++)
            {
                if((Line.find(String_Markup[i]) >=0) && (Line.find(String_Markup[i])<= Line.length()))
                {
                    String_Found_In_Line = true;
                    Str_Mrkp_Index = i;
                    break;
                }
            }

        }

        if(!String_Found_In_Line) //  no string is found in the line
        {
            Token = Line;
            Tokens_List.insert(Tokens_List.end(), Token);
            Token = "";
        }
        else // one or more string was (where) found in the line
        {
            Index = 0;
            while (Index < Line.length())
            {
                if(!First_String_Markup_Found)
                {
                    if (Line.substr(Index, 1) == String_Markup[Str_Mrkp_Index])
                    {
                        First_String_Markup_Found = true;
                        if(Token.length()>0)
                        {
                            Tokens_List.insert(Tokens_List.end(), Token);
                            Token = "";
                        }
                    }

                    Token += Line.substr(Index, 1);
                    Index++;
                }
                else if (!Last_String_Markup_Found)
                {
                    if (Line.substr(Index, 1) == String_Markup[Str_Mrkp_Index])
                    {
                        Token += Line.substr(Index, 1);
                        /*example : in c++ code
                        " this is a string contains this : \" a string markup, so it not concedired as a last markup"
                        pascal :
                        'this is a string contains this : '' a string markup, so it not concedired as a last markup'
                        */
                        if(Line.substr(Index-1, 1) != Befor_String_Markup)
                        {
                            Last_String_Markup_Found = true;
                            if(Token.length()>0)
                            {
                                Tokens_List.insert(Tokens_List.end(), Token);
                                Token = "";
                            }

                            First_String_Markup_Found = false;
                            Last_String_Markup_Found = false;

                        }
                        else // else = Line.substr(Index-1, 1) == Befor_String_Markup
                        {
                            if(Line.length()>=3)  // "\ "
                            {
                                if((Line.substr(Index-2, 1) == Befor_String_Markup)  /*&&
                                   (Line.substr(Index-3, 1) == String_Markup[Str_Mrkp_Index])*/) // example (c++):  "\\" , pascal : ''''
                                {
                                    Last_String_Markup_Found = true;
                                    if(Token.length()>0)
                                    {
                                        Tokens_List.insert(Tokens_List.end(), Token);
                                        Token = "";
                                    }

                                    First_String_Markup_Found = false;
                                    Last_String_Markup_Found = false;
                                }
                            }
                        }
                        Index++;
                    }
                    else
                    {
                        Token += Line.substr(Index, 1);
                        Index++;
                    }
                }
            }

            if(Token.length()>0)
            {
                Tokens_List.insert(Tokens_List.end(), Token);
                Token = "";
            }
        }
        Ind++;
    }
    return Tokens_List;
}


/**
  * this function make the second pass of generating program tokens, it's separate the char from code
  * Parameters :
  * - vector<std::string> string vector contains the first pass tokens
  * Returned values :
  * -  std::string vector contains the first pass tokens
  */
std::vector<std::string> Separate_Chars(std::vector<std::string> First_Pass_Tokens)
{
    std::vector<std::string>  Tokens_List;
    std::string Line="", Token="";
    std::string Befor_Char_Markup = Befor_Chr_Markup[0];
    bool First_Char_Markup_Found = false; // to indicate that the first string markup found or not yet
    bool Last_Char_Markup_Found = false;// to indicate that the last string markup found or not yet
    bool Char_Found_In_Line = false; // to indicate that a string found in the line or not
    int Char_Mrkp_Index = 0;/* it used to indicate witch string markup used (' or ") in language
                            like javascript, php wich have more then one markup for string*/
    unsigned long Index = 0;
    unsigned long Ind =0;
    while (Ind< First_Pass_Tokens.size())
    {
        Line = First_Pass_Tokens[Ind];
        Char_Found_In_Line = false;
        Index = 0;

        if(Is_A_String_Token (Line) )
        {
            Token = Line;
            Tokens_List.insert(Tokens_List.end(), Token);
            Token = "";
            Ind++;
            continue;
        }

        if (!Char_Found_In_Line) // no string is found in the line
        {
            for (unsigned int i=0; i<Char_Markup.size();i++)
            {
                if((Line.find(Char_Markup[i]) >=0) && (Line.find(Char_Markup[i])<= Line.length()))
                {
                    Char_Found_In_Line = true;
                    Char_Mrkp_Index = i;
                    break;
                }
            }
        }

        if(!Char_Found_In_Line) //  no string is found in the line
        {
            Token = Line;
            Tokens_List.insert(Tokens_List.end(), Token);
            Token = "";
        }
        else // // one or more string is (where) found in the line
        {

            Index = 0;
            while (Index < Line.length())
            {
                if(!First_Char_Markup_Found)
                {
                    if (Line.substr(Index, 1) == Char_Markup[Char_Mrkp_Index])
                    {
                        First_Char_Markup_Found = true;

                        if(Token.length()>0)
                        {
                            Tokens_List.insert(Tokens_List.end(), Token);
                            Token = "";
                        }

                    }
                    Token += Line.substr(Index, 1);
                    Index++;
                    //continue;
                }
                else if (!Last_Char_Markup_Found)
                {
                    if (Line.substr(Index, 1) == Char_Markup[Char_Mrkp_Index])
                    {
                        Token += Line.substr(Index, 1);
                        /*example : in c++ code
                        " this is a string contains this : \" a string markup, so it not concedired as a last markup"
                        pascal :
                        'this is a string contains this : '' a string markup, so it not concedired as a last markup'
                        */

                        if(Line.substr(Index-1, 1) != Befor_Char_Markup)
                        {
                            Last_Char_Markup_Found = true;
                            if(Token.length()>0)
                            {
                                Tokens_List.insert(Tokens_List.end(), Token);
                                Token = "";
                            }

                            First_Char_Markup_Found = false;
                            Last_Char_Markup_Found = false;
                        }
                        else // else = Line.substr(Index-1, 1) == Befor_Char_Markup
                        {
                            if(Line.length()>=3)
                            {
                                if((Line.substr(Index-2, 1) == Befor_Char_Markup)  &&
                                   (Line.substr(Index-3, 1) == Char_Markup[Char_Mrkp_Index])) // example (c++):  '\\' , pascal : ''''
                                {
                                    Last_Char_Markup_Found = true;
                                    if(Token.length()>0)
                                    {
                                        Tokens_List.insert(Tokens_List.end(), Token);
                                        Token = "";
                                    }

                                    First_Char_Markup_Found = false;
                                    Last_Char_Markup_Found = false;
                                }
                            }
                        }
                        Index++;
                    }
                    else
                    {
                        Token += Line.substr(Index, 1);
                        Index++;
                        //continue;
                    }
                }
            }

            if(Token.length()>0)
            {
                Tokens_List.insert(Tokens_List.end(), Token);
                Token = "";
            }
        }
        Ind++;
    }
    return Tokens_List;
}


/**
 * this function makes the third pass from generating tokens. its separates the numbers tokens from the code
 *
 */

std::vector<std::string> Separate_Numbers (std::vector<std::string> Second_Pass_Tokens)
{
    std::vector<std::string>  Tokens_List;
    std::string Line="", Token="";
	std::smatch Match; // This will holde the string that match the regex
	int Prefix_Size=0;
	char Last_Prefix_Char;
	char First_Suffix_Char;
	bool Ok_Prefix=false, Ok_Suffix=false;
    //Regular expression for the numbers tokens
    std::string Int_Regex = Integer_Number_Regex[0];
    std::string Rel_Regex = Real_Number_Regex[0];
    std::string Oct_Regex = Octal_Number_Regex[0];
    std::string Hex_Regex = Hexadecimal_Number_Regex[0];
    std::regex Int_Nbr_Regex (Int_Regex.c_str());
    std::regex Rel_Nbr_Regex (Rel_Regex.c_str());
    std::regex Oct_Nbr_Regex (Oct_Regex.c_str());
    std::regex Hex_Nbr_Regex (Hex_Regex.c_str());
    bool Match_Is_A_Number = false;
    bool Match_Found = false;
    unsigned long Ind =0;
    while (Ind< Second_Pass_Tokens.size())
    {
        Line = Second_Pass_Tokens[Ind];
        if(Is_A_String_Token (Line) || Is_A_Char_Token(Line))
        {
            Token = Line;
            Tokens_List.insert(Tokens_List.end(), Token);
            Token = "";
            Ind++;
            continue;
        }
        else
        {
            do
            {
                if ( regex_search(Line, Match, Rel_Nbr_Regex) )
                {
                    Match_Found = true;
                }
                else if (regex_search(Line, Match, Int_Nbr_Regex))
                {
                    Match_Found = true;
                }
                else if ( regex_search(Line, Match, Oct_Nbr_Regex) )
                {
                    Match_Found = true;
                }
                else if ( regex_search(Line, Match, Hex_Nbr_Regex) )
                {
                    Match_Found = true;
                }
                else
                {
                    Match_Found = false;
                }

                if (Match_Found)
                {
                    Prefix_Size = Match.prefix().str().length();
                    Last_Prefix_Char = Match.prefix().str()[Prefix_Size - 1];
                    First_Suffix_Char = Match.suffix().str()[0];
                    Ok_Prefix=false;
                    Ok_Suffix=false;

                    for (unsigned int i=0;i<Separators.size();i++)
                    {
                        if(Last_Prefix_Char == Separators[i][0])
                        {
                            Ok_Prefix = true;
                        }
                        if(First_Suffix_Char == Separators[i][0])
                        {
                            Ok_Suffix = true;
                        }
                    }

                    if ((Ok_Prefix && Ok_Suffix)  || ( (Match[0].str()[0]=='-') || (Match[0].str()[0]=='+') ) )
                    {
                        Match_Is_A_Number = true;
                        //for(unsigned c = 0; c < m.size(); c++)
                        //{
                        // eliminating the sign from the number
                        if((Match[0].str()[0]=='-') || (Match[0].str()[0]=='+'))
                        {
                            Token = Match.prefix().str() + Match[0].str().substr(0,1);// add the sign(- or +) to the previous token : Match.prefix
                            Tokens_List.insert(Tokens_List.end(), Token);
                            Token = Match[0].str().substr(1,Match[0].str().length() -1);// eliminate the sign (- or +) from the number token : Match[0]
                            Tokens_List.insert(Tokens_List.end(), Token);
                            Token = "";
                        }
                        else
                        {
                            Token = Match.prefix().str();
                            Tokens_List.insert(Tokens_List.end(), Token);
                            Token = Match[0].str();
                            Tokens_List.insert(Tokens_List.end(), Token);
                            Token = "";
                        }
                        //}
                    }

                    if(!Match_Is_A_Number)
                    {
                        //--
                        Token = Match.prefix().str() + Match[0].str();
                        Tokens_List.insert(Tokens_List.end(), Token);
                    }
                    Line = Match.suffix().str();
                    Match_Is_A_Number = false;
                }

            }while(Match_Found);

            if( Line.length()  > 0)
            {
                Token = Line;
                Tokens_List.insert(Tokens_List.end(), Token);
                Token = "";
            }
        }
        Ind++;
    }
    return Tokens_List;
}


/**
 * this function finalize the generation of the list of the program token
 * TODO:
 */

std::vector<std::string> Generate_Tokens_List_Fourth_Pass (std::vector<std::string> Third_Pass_Tokens)
{
    std::vector<std::string>  Tokens_List;
    std::string Line, Token;
    unsigned int Index =0; // long because the token number may be too big
    bool Separator_Found = false;
    unsigned long Ind =0;
    while (Ind< Third_Pass_Tokens.size())
    {
        Line = Third_Pass_Tokens[Ind];
        Index = 0;
        if(Is_A_String_Token (Line) || Is_A_Char_Token(Line) || Is_A_Number_Token(Line))
        {
            Token = Line;
            Tokens_List.insert(Tokens_List.end(), Token);
            Token = "";
            Ind++;
            continue;
        }
        while(Index <Line.length()) // processing the line char by char
        {
            Separator_Found = false;
            for (unsigned int j=0; j<Separators.size(); j++ )
            {
                if(Line.substr(Index,1) == Separators[j])
                {
                    if(Token.length()>0)
                    {
                        Tokens_List.insert(Tokens_List.end(),Token);
                        Token = "";
                    }
                    Separator_Found = true;
                    break;
                }
            }
            Token += Line.substr(Index,1);
            Index++;

            if ( Separator_Found)
            {
                //searching for 3 characters operators
                std::string Temp = "";

                if(Line.length()> Index +1)
                {
                    Temp = Token + Line.substr(Index,1) + Line.substr(Index+1,1) ;
                }
                else
                {
                    goto Skip_Operator3;
                }

                for (unsigned int j=0; j<Separators3.size(); j++ )
                {
                    if(Temp == Separators3[j])
                    {
                        Tokens_List.insert(Tokens_List.end(),Temp);
                        Token = "";
                        Separator_Found = false;
                        Index += 2;//+2
                        goto Skip_Operator2;
                    }

                }

                Skip_Operator3 :
                //searching for 2 characters operators
                Temp = Token + Line.substr(Index,1);
                for (unsigned int j=0; j<Separators2.size(); j++ )
                {
                    if(Temp == Separators2[j])
                    {
                        Tokens_List.insert(Tokens_List.end(),Temp);
                        Token = "";
                        Separator_Found = false;
                        Index++;
                        break;
                    }
                }

                Skip_Operator2 : // if a 3 characters operators found, we skip searching for 2 characters operators

                if(Separator_Found)
                {
                    Tokens_List.insert(Tokens_List.end(),Token);
                    Token = "";
                }
            }
            else
            {
                if (Index >= Line.length() && Token.length()>0)
                {
                    Tokens_List.insert(Tokens_List.end(),Token);
                    Token = "";
                }
            }
        }
        Ind++;
    }
    return Tokens_List;
}

