#ifndef SQUARE_MAX_75_AT_16384_1024INT8_H_
#define SQUARE_MAX_75_AT_16384_1024INT8_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "mozzi_pgmspace.h"


#define SQUARE_MAX_75_AT_16384_1024_NUM_CELLS 1024
#define SQUARE_MAX_75_AT_16384_1024_SAMPLERATE 1024

CONSTTABLE_STORAGE(int8_t) SQUARE_MAX_75_AT_16384_1024_DATA [] = 
{
0, 45, 84, 111, 125, 127, 120, 111, 102, 98, 99, 103, 109, 114, 115, 114, 110, 106, 103, 103, 105, 108, 111, 112, 112, 110, 107, 105, 104, 105, 107, 110, 111, 
111, 110, 108, 106, 105, 106, 107, 109, 110, 111, 110, 109, 107, 106, 106, 107, 108, 110, 110, 110, 109, 108, 107, 106, 107, 108, 109, 110, 110, 109, 108, 107, 
107, 107, 108, 109, 109, 110, 109, 108, 107, 107, 107, 107, 108, 109, 109, 109, 109, 108, 107, 107, 107, 108, 109, 109, 109, 109, 108, 107, 107, 107, 108, 109, 
109, 109, 109, 108, 108, 107, 107, 108, 108, 109, 109, 109, 108, 108, 107, 107, 107, 108, 109, 109, 109, 109, 108, 107, 107, 107, 108, 109, 109, 109, 109, 108, 
108, 107, 107, 108, 108, 109, 109, 109, 108, 108, 107, 107, 108, 108, 109, 109, 109, 108, 108, 107, 107, 108, 108, 108, 109, 109, 109, 108, 108, 107, 107, 108, 
108, 109, 109, 109, 108, 108, 107, 107, 108, 108, 109, 109, 109, 108, 108, 108, 107, 108, 108, 108, 109, 109, 109, 108, 108, 107, 108, 108, 108, 109, 109, 109, 
108, 108, 107, 107, 108, 108, 109, 109, 109, 108, 108, 108, 107, 108, 108, 108, 109, 109, 108, 108, 108, 107, 108, 108, 108, 109, 109, 109, 108, 108, 108, 108, 
108, 108, 109, 109, 109, 108, 108, 108, 107, 108, 108, 109, 109, 109, 108, 108, 108, 107, 108, 108, 108, 109, 109, 109, 108, 108, 108, 108, 108, 108, 109, 109, 
109, 108, 108, 108, 108, 108, 108, 109, 109, 109, 108, 108, 108, 107, 108, 108, 108, 109, 109, 109, 108, 108, 107, 108, 108, 108, 109, 109, 109, 108, 108, 108, 
108, 108, 108, 109, 109, 109, 108, 108, 108, 107, 108, 108, 108, 109, 109, 108, 108, 108, 107, 108, 108, 108, 109, 109, 109, 108, 108, 107, 107, 108, 108, 109, 
109, 109, 108, 108, 108, 107, 108, 108, 109, 109, 109, 108, 108, 108, 107, 108, 108, 108, 109, 109, 109, 108, 108, 107, 107, 108, 108, 109, 109, 109, 108, 108, 
107, 107, 108, 108, 109, 109, 109, 108, 108, 108, 107, 107, 108, 108, 109, 109, 109, 108, 108, 107, 107, 108, 108, 109, 109, 109, 108, 108, 107, 107, 108, 108, 
109, 109, 109, 109, 108, 107, 107, 107, 108, 109, 109, 109, 109, 108, 107, 107, 107, 108, 108, 109, 109, 109, 108, 108, 107, 107, 108, 108, 109, 109, 109, 109, 
108, 107, 107, 107, 108, 109, 109, 109, 109, 108, 107, 107, 107, 108, 109, 109, 109, 109, 108, 107, 107, 107, 107, 108, 109, 110, 109, 109, 108, 107, 107, 107, 
108, 109, 110, 110, 109, 108, 107, 106, 107, 108, 109, 110, 110, 110, 108, 107, 106, 106, 107, 109, 110, 111, 110, 109, 107, 106, 105, 106, 108, 110, 111, 111, 
110, 107, 105, 104, 105, 107, 110, 112, 112, 111, 108, 105, 103, 103, 106, 110, 114, 115, 114, 109, 103, 99, 98, 102, 111, 120, 127, 125, 111, 84, 45, 0, 
-45, -84, -111, -125, -127, -120, -111, -102, -98, -99, -103, -109, -114, -115, -114, -110, -106, -103, -103, -105, -108, -111, -112, -112, -110, -107, -105, -104, -105, -107, -110, -111, 
-111, -110, -108, -106, -105, -106, -107, -109, -110, -111, -110, -109, -107, -106, -106, -107, -108, -110, -110, -110, -109, -108, -107, -106, -107, -108, -109, -110, -110, -109, -108, -107, 
-107, -107, -108, -109, -109, -110, -109, -108, -107, -107, -107, -107, -108, -109, -109, -109, -109, -108, -107, -107, -107, -108, -109, -109, -109, -109, -108, -107, -107, -107, -108, -109, 
-109, -109, -109, -108, -108, -107, -107, -108, -108, -109, -109, -109, -108, -108, -107, -107, -107, -108, -109, -109, -109, -109, -108, -107, -107, -107, -108, -109, -109, -109, -109, -108, 
-108, -107, -107, -108, -108, -109, -109, -109, -108, -108, -107, -107, -108, -108, -109, -109, -109, -108, -108, -107, -107, -108, -108, -108, -109, -109, -109, -108, -108, -107, -107, -108, 
-108, -109, -109, -109, -108, -108, -107, -107, -108, -108, -109, -109, -109, -108, -108, -108, -107, -108, -108, -108, -109, -109, -109, -108, -108, -107, -108, -108, -108, -109, -109, -109, 
-108, -108, -107, -107, -108, -108, -109, -109, -109, -108, -108, -108, -107, -108, -108, -108, -109, -109, -108, -108, -108, -107, -108, -108, -108, -109, -109, -109, -108, -108, -108, -108, 
-108, -108, -109, -109, -109, -108, -108, -108, -107, -108, -108, -109, -109, -109, -108, -108, -108, -107, -108, -108, -108, -109, -109, -109, -108, -108, -108, -108, -108, -108, -109, -109, 
-109, -108, -108, -108, -108, -108, -108, -109, -109, -109, -108, -108, -108, -107, -108, -108, -108, -109, -109, -109, -108, -108, -107, -108, -108, -108, -109, -109, -109, -108, -108, -108, 
-108, -108, -108, -109, -109, -109, -108, -108, -108, -107, -108, -108, -108, -109, -109, -108, -108, -108, -107, -108, -108, -108, -109, -109, -109, -108, -108, -107, -107, -108, -108, -109, 
-109, -109, -108, -108, -108, -107, -108, -108, -109, -109, -109, -108, -108, -108, -107, -108, -108, -108, -109, -109, -109, -108, -108, -107, -107, -108, -108, -109, -109, -109, -108, -108, 
-107, -107, -108, -108, -109, -109, -109, -108, -108, -108, -107, -107, -108, -108, -109, -109, -109, -108, -108, -107, -107, -108, -108, -109, -109, -109, -108, -108, -107, -107, -108, -108, 
-109, -109, -109, -109, -108, -107, -107, -107, -108, -109, -109, -109, -109, -108, -107, -107, -107, -108, -108, -109, -109, -109, -108, -108, -107, -107, -108, -108, -109, -109, -109, -109, 
-108, -107, -107, -107, -108, -109, -109, -109, -109, -108, -107, -107, -107, -108, -109, -109, -109, -109, -108, -107, -107, -107, -107, -108, -109, -110, -109, -109, -108, -107, -107, -107, 
-108, -109, -110, -110, -109, -108, -107, -106, -107, -108, -109, -110, -110, -110, -108, -107, -106, -106, -107, -109, -110, -111, -110, -109, -107, -106, -105, -106, -108, -110, -111, -111, 
-110, -107, -105, -104, -105, -107, -110, -112, -112, -111, -108, -105, -103, -103, -106, -110, -114, -115, -114, -109, -103, -99, -98, -102, -111, -120, -127, -125, -111, -84, -45, 
 };

#endif