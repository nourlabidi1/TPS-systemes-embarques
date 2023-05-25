
#include "tp1.h"

int counter=0;
int leds[4]={12,13,14,15};


int main(void){
	
RCC_GPIO_enable(RCCENR, 8);
Systick_configure(Systick, 16000000, 1,1 );
for ( int i=0; i<4 ; i++ )
GPIO_configure(GPIOD ,leds[i], 1 ,0  , 0, 1 );
while (1) {
	

}



return 0;
}
void SysTick_Handler(){
int j = counter%4;
	int k= j-1;
	if (j==0) k=3;
pinWrite(GPIOD, leds[j],1);
pinWrite(GPIOD, leds[k],0);
counter++;

}