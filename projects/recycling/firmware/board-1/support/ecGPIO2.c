/*----------------------------------------------------------------\
@ Embedded Controller by course instructor (name redacted) - Handong Global University
Author           : team-member variant (name redacted)
Created          : 05-03-2021
Modified         : 09-23-2024
Language/ver     : C++ in Keil uVision
/----------------------------------------------------------------*/



#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "ecGPIO2.h"

void GPIO_init(PinName_t pinName, uint32_t mode){
    GPIO_TypeDef * Port;
    unsigned int pin;
    ecPinmap(pinName, &Port, &pin);

    // mode  : Input(0), Output(1), AlterFunc(2), Analog(3)

    if (Port == GPIOA)
        RCC_GPIOA_enable();
    if (Port == GPIOC)
        RCC_GPIOC_enable();

    //[TO-DO] YOUR CODE GOES HERE
    // Make it for GPIOB, GPIOD..GPIOH
    if (Port == GPIOB)
        RCC_GPIOB_enable();
    if (Port == GPIOD)
        RCC_GPIOD_enable();
    if (Port == GPIOE)
        RCC_GPIOE_enable();
    if (Port == GPIOH)
        RCC_GPIOH_enable();
    // You can also make a more general function of
    // void RCC_GPIO_enable(GPIO_TypeDef *Port);
    GPIO_mode(pinName, mode);
}

// GPIO Mode          : Input(00), Output(01), AlterFunc(10), Analog(11)
void GPIO_mode(PinName_t pinName, uint32_t mode){
   GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);
   Port->MODER &= ~(3UL<<(2*pin));
   Port->MODER |= mode<<(2*pin);
}

// GPIO Speed          : Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
void GPIO_ospeed(PinName_t pinName, int speed){
    GPIO_TypeDef * Port;
    unsigned int pin;
    ecPinmap(pinName, &Port, &pin);
    Port->OSPEEDR &= ~(3UL<<2*pin);
    Port->OSPEEDR |= speed<<(2*pin);
}

// GPIO Output Type: Output push-pull (0, reset), Output open drain (1)
void GPIO_otype(PinName_t pinName, int type){
    GPIO_TypeDef * Port;
    unsigned int pin;
    ecPinmap(pinName, &Port, &pin);
    Port->OTYPER &= ~(1<<pin);
    Port->OTYPER |= type<<pin;
}

// GPIO Push-Pull    : No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
void GPIO_pupd(PinName_t pinName, int pupd){
    GPIO_TypeDef * Port;
    unsigned int pin;
    ecPinmap(pinName, &Port, &pin);
    Port->PUPDR &= ~(3UL<<2*pin);
    Port->PUPDR |= pupd<<(2*pin);
}
void GPIO_write(PinName_t pinName, int Output){
    GPIO_TypeDef * Port;
    unsigned int pin;
    ecPinmap(pinName, &Port, &pin);
    Port->ODR &= ~(1<<pin);
    Port->ODR |= Output<<pin;
}

int GPIO_read(PinName_t pinName){
    GPIO_TypeDef * Port;
    unsigned int pin;
    ecPinmap(pinName, &Port, &pin);
    unsigned int btval;
    btval=(Port->IDR) & (1UL<<pin);

    return btval;
}


PinName_t pin_count[4]; // Makes it available in display_init and display.


void sevensegment_display_init(PinName_t pinNameA, PinName_t pinNameB, PinName_t pinNameC, PinName_t pinNameD){
    pin_count[0]=pinNameA;
    pin_count[1]=pinNameB;
    pin_count[2]=pinNameC;
    pin_count[3]=pinNameD; // saving pin names

    for(int i=0;i<4;i++){
        GPIO_init(pin_count[i],OUTPUT); // pin setting
    }
}


void sevensegment_display(uint8_t  num){
    for(int i=0; i<4; i++){
        GPIO_write(pin_count[i], num%2); // Writing data using reminders
        num=num/2; // Decimal to Binary --> a%2 --> (a/2)%2 --> ...
    }
}

PinName_t sevenseg_dec[8] = {PA_5, PA_6, PA_7, PB_6, PC_7, PA_9, PA_8, PB_10}; // pin definition for 7-segment decoder
void sevensegment_decoder_init(void){

    for(int i=0;i<8;i++){
        GPIO_init(sevenseg_dec[i],OUTPUT);
        GPIO_otype(sevenseg_dec[i],PUSH_PULL);
        GPIO_pupd(sevenseg_dec[i], NPUPD);
        GPIO_ospeed(sevenseg_dec[i], MS); // Output setting & type setting
    }
}


void sevensegment_decoder(uint8_t  num){
    unsigned int sevenseg_decoder_array[10] ={
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000011, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10011000  // 9
    }; // define 7segment decoder read--> last to first (with dp LED)

    for (int i=0; i<8; i++){

        GPIO_write(sevenseg_dec[i], (sevenseg_decoder_array[num]>>i) & 1);// Set the same number as the decoder (bit by bit)
    }


}
