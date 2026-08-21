/*----------------------------------------------------------------\
@ Embedded Controller by course instructor (name redacted) - Handong Global University
Author           : team-member variant (name redacted)
Created          : 05-03-2021
Modified         : 09-23-2024
Language/ver     : C++ in Keil uVision
/----------------------------------------------------------------*/

#ifndef __ECGPIO2_H
#define __ECGPIO2_H

#include "stm32f411xe.h"
#include "ecRCC2.h"
#include "ecPinNames.h"

#define INPUT  0x00
#define OUTPUT 0x01
#define AF     0x02
#define ANALOG 0x03

#define PUSH_PULL 0
#define open_drain 1

#define LS 0x00
#define MS 0x01
#define FS 0x02
#define HS 0x03

#define NPUPD 0x00
#define PU 0x01
#define PD 0x10
#define RE 0x03

#define HIGH 1
#define LOW  0


#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

void GPIO_init(PinName_t pinName, uint32_t mode);
void GPIO_write(PinName_t pinName, int Output);
int  GPIO_read(PinName_t pinName);
void GPIO_mode(PinName_t pinName, uint32_t mode);
void GPIO_ospeed(PinName_t pinName, int speed);
void GPIO_otype(PinName_t pinName, int type);
void GPIO_pupd(PinName_t pinName, int pupd);

void sevensegment_display_init(PinName_t pinNameA, PinName_t pinNameB, PinName_t pinNameC, PinName_t pinNameD);
void sevensegment_display(uint8_t  num);

void sevensegment_decoder_init(void);
void sevensegment_decoder(uint8_t  num);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __ECGPIO2_H
