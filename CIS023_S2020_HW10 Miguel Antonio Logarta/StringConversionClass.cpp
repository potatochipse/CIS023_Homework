// Project:	StringConversionClass.cpp
// Author:	Miguel Antonio Logarta
// Date:	January 31, 2020
// Purpose:	Implementation file for StringConversion class

// #include "framework.h"
#include "CIS023_S2020_HW10 Miguel Antonio Logarta.h"

string StringConversionClass::ConvertTCHARtoString(TCHAR* szUserInput)
{
	string strUserInput;				// String to hold the return value

	// Convert TCHAR szUserInput into a string
	if (lstrlen(szUserInput) != 0)					// If it is not blank
	{
		wstring temp(szUserInput);					// Convert TCHAR to a wide string
		string str(temp.begin(), temp.end());		// Convert wstring to string
		strUserInput = str;							// Copy temporary string
	}

	// Return the string
	return strUserInput;
}

TCHAR* StringConversionClass::ConvertStringtoTCHAR(string strStringInput)
{
	size_t pReturnValue;							// for mbstowcs_s()

	// Convert string to TCHAR
	mbstowcs_s(										// Convert string to TCHAR
		&pReturnValue,								// Return value
		szReturn,									// Destination TCHAR
		TCHAR_SIZE,									// Size of TCHAR
		strStringInput.c_str(),						// Source string
		TCHAR_SIZE);								// Max Chars to convert

	return szReturn;
}
