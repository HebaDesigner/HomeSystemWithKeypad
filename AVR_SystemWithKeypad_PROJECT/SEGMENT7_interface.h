#ifndef SEGMENT7_INTERFACE_H_
#define SEGMENT7_INTERFACE_H_

#define ComCathode 		0
#define ComAnode		1

#define zero    0x3f
#define one     0x06
#define two     0x5b
#define three   0x4f
#define four    0x66
#define five    0x6d
#define six     0x7d
#define seven   0x07
#define eight   0x7f
#define nine    0x6f



void Segment7_VoidInit(void);

void Segment7_VidSetDisplay(u8 u8ArrCopy);

void Segment7_VidClearDisplay(void);

void Segment7_VidEnableDisplayOne(void);
void Segment7_VidEnableDisplayTwo(void);

void Segment7_VidDisableDisplayOne(void);
void Segment7_VidDisableDisplayTwo(void);


#endif /* SEGMENT7_INTERFACE_H_ */
