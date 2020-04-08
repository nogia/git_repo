#pragma once
#ifndef VDT_POSITION_H_
#define VDT_POSITION_H_

#define VDT_MSCC     20
#define VDT_QTR_DECK 21
#define VDT_ECCC_1   23
#define VDT_ECCC_2   24
#define VDT_ECCC_3   25
  

class CVdtPosition
{

public:

  CVdtPosition();
  CVdtPosition(char *sDefaultIP);

  ~CVdtPosition();

  int  GetVdtPosition();

protected:
  int iVdtPositionNumber;

  void SetVdtPosition(char *IPAddr, char * szEterInterface);
  void InitVdtPosition();

};

#endif /* VDT_POSITION_H_ */
