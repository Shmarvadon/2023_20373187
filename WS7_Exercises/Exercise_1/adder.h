// A better way of header guarding.
#pragma once

#if defined(WIN32)|defined(_WIN32)
	#ifdef maths_STATIC
		#define MATHSLIB_API
	#else
		#ifdef maths_EXPORTS
			#define MATHSLIB_API __declspec( dllexport )
		#else 
			#define MATHSLIB_API __declspec( dllimport )
		#endif
	#endif
#else 
	#define MATHSLIB_API
#endif

/** @file
* This file contains the declerations of all exported functions in the maths library.
*/

/** Adding funciton
* This function adds 2 numbers
* @param a is the first number
* @param b is the second number
* @return sum of a and b
*/
MATHSLIB_API int add(int a, int b);
