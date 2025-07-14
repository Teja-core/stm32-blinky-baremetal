#include <stdint.h>
#include<stdio.h>


#define PERIPH_BASE       (0x40000000UL)
//#define AHB1PERIPH_OFFSET    (0x0002 0000UL)
//#define AHB1PERIPH_BASE     ( PERIPH_BASE + AHB1PERIPH_OFFSET)
#define AHB1PERIPH_BASE     (0x40020000UL)

//#define GPIOD_OFFSET         ( 0x0000 0C00UL)
//#define GPIOD_BASE        (AHB1PERIPH_BASE + GPIOD_OFFSET)
#define GPIOD_BASE        (0x40020C00UL)

//#define RCC_OFFSET        ( 0x0000 3800 UL )
//#define RCC_BASE          (GPIOD_BASE + RCC_OFFSET)
#define RCC_BASE         ( 0x40023800UL)

#define RCC_AHB1ENR_OFFSET  (0x30UL)
#define RCC_AHB1ENR_R     (*( volatile unsigned int*) (RCC_BASE + RCC_AHB1ENR_OFFSET ))

#define GPIOD_MODE_OFFSET    (0x00UL)
#define GPIOD_MODE_R        (*(volatile unsigned int *)(GPIOD_BASE + GPIOD_MODE_OFFSET))

#define GPIOD_OD_OFFSET      (0x014UL)
#define GPIOD_OD_R          (*(volatile unsigned int*)(GPIOD_BASE + GPIOD_OD_OFFSET))

#define GPIODEN        (1U << 3)

#define LED_PIN1    (1U << 12)
#define LED_PIN2    (1U << 13)
#define LED_PIN3    (1U << 14)
#define LED_PIN4    (1U << 15)

void delay(void){
	unsigned int i=0;
	for(i=0;i<200000;i++);
}

int main(void)
{
	RCC_AHB1ENR_R |= GPIODEN;                                             // enbale clock for GPIOD Port

	GPIOD_MODE_R |= (1U<< 24 |1U<<26 | 1U<<28 | 1U<<30);		   // enable GPIO pins as Input/output mode
	GPIOD_MODE_R &= ~(1U<<25 | 1U<<27 | 1U<<29 | 1U<<31);

	while(1){
		GPIOD_OD_R |= (LED_PIN1 | LED_PIN2 |LED_PIN3 | LED_PIN4);  //set pin 12,13,14,15 as 1 (LED's on)
		delay();						   //delay to observe output on hardware
		GPIOD_OD_R &= ~(LED_PIN1 | LED_PIN2 |LED_PIN3 | LED_PIN4);// set pin as 12,13,14,15, as 0 (LED's OFF)
		delay();                                                 // delay to observe output on hardware
	}

}

