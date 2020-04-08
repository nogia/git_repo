#ifndef DEF_ALARMS
#define DEF_ALARMS

struct AlarmSetpoints
{
	float setPointLowLow;
	float setPointLow;
	float setPointHigh;
	float setPointHighHigh;
};
typedef struct AlarmSetpoints ALARMSETPOINTS;

struct AlarmReset
{
	float resetLowLow;
	float resetLow;
	float resetHigh;
	float resetHighHigh;
};
typedef struct AlarmReset ALARMRESET;

#endif
