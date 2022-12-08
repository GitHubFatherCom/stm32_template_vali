#include <stdint.h>
#include <stdbool.h>
#include <stm32f10x.h>
#define MIN(a,b)((a)<(b)?(a):(b))

void delay_us(uint32_t ticks) {
	for (int i=0; i<ticks; i++) {
		__NOP();
	}
}

// int __attribute((noreturn)) main(void) {
// 	// Enable clock for AFIO
// 	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
// 	// Enable clock for GPIOC
// 	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
// 	// Enable PC13 push-pull mode
// 	GPIOC->CRH &= ~GPIO_CRH_CNF13; //clear cnf bits
// 	GPIOC->CRH |= GPIO_CRH_MODE13_0; //Max speed = 10Mhz

// 	//CHANGE FREQ TO 24kHz
//     while (1) {
// 	    GPIOC->ODR |= (1U<<13U); //U -- unsigned suffix (to avoid syntax warnings in IDE)
// 		delay(100000);
// 	    GPIOC->ODR &= ~(1U<<13U);
// 	    delay(100000);
//     }
// }

#if 0
int main(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPAEN;
	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7) | GPIO_CRL_CNF7_1;
	GPIOA->ODR |= GPIO_ODR_ODR7;
	GPIOC->CRH = GPIOC->CRH & ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13) | GPIO_CRH_MODE13_0;
	uint32_t i;
	uint8_t button_state = 0x00;
	uint32_t t = 10000;
	uint32_t btnPeriod = 10000, ledPeriod = 100000;
	uint32_t btnPhase = btnPeriod, ledPhase = ledPeriod;
	bool ledEnable=true, buR1_CEN; // Start timer
while (1) {ttonPrevState = GPIO_IDR_IDR7 & (1 << 7);
	while (t){
		uint32_t tau = MIN(btnPhase,btnPhase);
		delay_us(tau);
		ledPhase -=tau; btnPhase -=tau;
		if (btnPhase==0) {
			btnPhase=btnPeriod;
		}
		if (ledPhase==0) {
			ledPhase=ledPeriod;
		
		}
		t--;
		}	
	
	

	while(1) {
			if(!(GPIOA->IDR & GPIO_IDR_IDR7)){ // Button is pressed
				button_state = ~button_state;
				while(!(GPIOA->IDR & GPIO_IDR_IDR7));
			}
			if(button_state){
				GPIOC->ODR &= ~GPIO_ODR_ODR13;
				for(i=0; i<300000; i++){ __NOP(); };

				GPIOC->ODR |= GPIO_ODR_ODR13;
				for(i=0; i<300000; i++){ __NOP(); };
			}

	}
	}
#endif



//turning on/off the leg on switching the button
#if 0
int main(void) {
GPIOC->CRH = GPIOC->CRH & ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13) | GPIO_CRH_MODE13_0; //PC13 = output
GPIOC->CRH = GPIOC->CRH & ~(GPIO_CRH_CNF14 | GPIO_CRH_MODE14) | GPIO_CRH_CNF14_1; //PC14 = input
RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
//RESET TIMER
RCC->APB1RSTR |= RCC_APB1RSTR_TIM2RST;
RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM2RST;
TIM2->PSC = 1023;
TIM2->ARR = 8000;
//36MHZ/1023/8000=4.39HZ
TIM2->DIER |= TIM_DIER_UIE;

NVIC_ClearPendingIRQ(TIM2_IRQn);
NVIC_EnableIRQ(TIM2_IRQn);
TIM2->CR1 |= TIM_CR1_CEN;
while(1){
	__NOP();
}

}

#endif

void TIM2_IRQHandler(void) {
if (TIM2->SR & TIM_SR_UIF) {
/* Toggle GPIO here */
if(GPIOC->ODR & GPIO_ODR_ODR13){
	GPIOC->ODR &= ~GPIO_ODR_ODR13;
} else {
	GPIOC->ODR |= GPIO_ODR_ODR13;
}


//Clear Interrupt flag
TIM2->SR &= ~TIM_SR_UIF;
}
}



int main(void) {
GPIOC->CRH = GPIOC->CRH & ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13) | GPIO_CRH_MODE13_0; //PC13 = output
GPIOC->CRH = GPIOC->CRH & ~(GPIO_CRH_CNF14 | GPIO_CRH_MODE14) | GPIO_CRH_CNF14_1; //PC14 = input

RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
RCC->APB1RSTR |= RCC_APB1RSTR_TIM2RST;
RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM2RST;
TIM2->PSC = 1023;
TIM2->ARR = 4095;
TIM2->DIER |= TIM_DIER_UIE; // Enable Update Interrupt
NVIC_ClearPendingIRQ(TIM2_IRQn);
NVIC_EnableIRQ(TIM2_IRQn); // Enable IRQ in NVIC
TIM2->CR1 |= TIM_CR1_CEN; // Start timer
while (1) {
__asm volatile ("nop");
} 

}








