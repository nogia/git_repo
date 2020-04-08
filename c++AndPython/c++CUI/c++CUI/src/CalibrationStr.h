#ifndef DEF_THRUSTERCAL
#define DEF_THRUSTERCAL
typedef struct thrusterCalStr
{
	long   leverType;	
	float	dStopPos;
	float	dFullAheadPos;
	float	dFullAsternPos;

}THRUSTERCALSTR;
typedef struct throttleCalStr
{
	long   leverType;	
	float	dStopPos;
	float	dFullAheadPos;
	float	dFullAsternPos;

}THROTTLECALSTR;

typedef struct pitchCalStr
{
	float	dStopPos;
	float	dFullAheadPos;
	float	dFullAsternPos;

}PITCHCALSTR;

#endif
