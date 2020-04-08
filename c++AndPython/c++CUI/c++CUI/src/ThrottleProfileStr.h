#ifndef DEF_THROTTLECONFIG
#define DEF_THROTTLECONFIG

#define MAXNUMTHROTTLEENTRIES 21  // -10  0  +10

struct throttleEntry
{
	int ndx;  // -10  0  +10
	float rpm;
	float pitch;
};
typedef struct throttleEntry THROTTLEENTRY;

struct throttleProfileStr
{
	int profileType;
 	THROTTLEENTRY profile[MAXNUMTHROTTLEENTRIES];	
};
typedef struct throttleProfileStr THROTTLEPROFILESTR;

#endif
