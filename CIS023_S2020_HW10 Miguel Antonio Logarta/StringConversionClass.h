// Project:	StringConversionClass.h
// Author:	Miguel Antonio Logarta
// Date:	January 31, 2020
// Purpose:	Header file for StringConversionClass

#pragma once
class StringConversionClass
{
public:
	string	ConvertTCHARtoString(TCHAR*);				// Converts TCHAR to a string
	TCHAR*	ConvertStringtoTCHAR(string);				// Converts string to TCHAR
	TCHAR	szReturn[TCHAR_SIZE];						// The Return value for ConvertStringtoTCHAR()
};

