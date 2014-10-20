/*
Copyright (c) 2013-2014, UMR STMS 9912 - Ircam-Centre Pompidou / CNRS / UPMC
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**

Spatial acoustic data file format - AES X212 standard
http://www.aes.org

SOFA (Spatially Oriented Format for Acoustics)
http://www.sofaconventions.org

*/


/************************************************************************************/
/*  FILE DESCRIPTION                                                                */
/*----------------------------------------------------------------------------------*/
/*!
 *   @file       SOFAString.h
 *   @brief      Useful functions to manipulate strings
 *   @author     Thibaut Carpentier, UMR STMS 9912 - Ircam-Centre Pompidou / CNRS / UPMC
 *
 *   @date       10/05/2013
 * 
 */
/************************************************************************************/
#ifndef _SOFA_STRING_H__
#define _SOFA_STRING_H__

#include "../src/SOFAPlatform.h"
#include <sstream>
#include <iostream>

namespace sofa
{
    
    namespace String
    {
    
        inline const int String2Int(const std::string &str)
        {
            return atoi( str.c_str() );
        }
        
        inline const std::string Int2String(const int value)
        {
            std::ostringstream str;
            str << value;
            return str.str();
        }
        
        inline const bool IsInt(const char c)
        {
            return ( c >= '0' && c <= '9' );
        }    
        
        inline const std::string bool2string(const bool value)
        {
            return ( value == true ) ? ("true") : ("false");
        }

        inline const std::string bool2yesorno(const bool value)
        {
            return ( value == true ) ? ("yes") : ("no");
        }
        
        const std::string PadWith(const std::string &src,
                                  const std::size_t totalLength     = 30,
                                  const std::string &pad            = " ");
        
        void PrintSeparationLine(std::ostream & output = std::cout);
    }
}

#endif /* _SOFA_STRING_H__ */ 

