#ifndef DEF_LOGGER
#define DEF_LOGGER
#include "LoggingStr.h"

int BellLogEntry(BELLLOGSTR *);
int MachPlantStatusLogEntry(int, MACHPLANTSTATUSLOGSTR *);
int LogRetrieval(LOGRETRIEVALSTR *);
int DigitalAlarmVariableModEntry(DIGITALALARMVARLOGMODSTR *);
int AnalogAlarmVariableModEntry(ANALOGALARMVARLOGMODSTR *);
int CommentLogEntry(int type, char *operatorName, char *commentText);
int AlarmChangeLogEntry(ALARMCHANGELOGSTR *);
int StatusChangeLogEntry(STATUSCHANGELOGSTR *);

// TODO
int DigitalAlarmLogEntry(DIGITALALARMLOGSTR *);
int AnalogAlarmLogEntry(ANALOGALARMLOGSTR *);

int initDDSLogging(int domain);

#endif

