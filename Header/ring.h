#include <reg51.h>


#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef UINT 
#define UINT unsigned int
#endif

#ifndef ULONG
#define ULONG unsigned long
#endif

sbit BUZZ = P2^0;

extern UCHAR T0RH,T0RL;
extern bit enable, TimeFlag;
extern UINT code Fre[],Tone[];
extern UCHAR code music[],Die[];



void PlayMusic(UCHAR speed);  //speed ≤•∑≈ÀŸ∂»	 */