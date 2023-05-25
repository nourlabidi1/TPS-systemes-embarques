# include <stdint.h>
# define SYSTICK_BASE 0xE000E010
# define RCCENR_BASE 0x40023830
#define GPIOD_BASE 0X40020C00

 
typedef struct {
volatile uint32_t control;
volatile uint32_t reload;
volatile uint32_t current;
} SYSTICK_TYPE;


 typedef struct
{volatile uint32_t AHB1ENR; 
 volatile uint32_t AHB2ENR; 
 volatile uint32_t AHB3ENR;  
 uint32_t  RESERVED;                                                                     
 volatile uint32_t APB1ENR;  
 volatile uint32_t APB2ENR; 
} RCCENR_Type;

typedef struct 
{
	volatile uint32_t  GPIO_MODER;
	volatile uint32_t GPIO_OSPEEDR;
	volatile uint32_t GPIO_OTYPER;
	volatile uint32_t GPIOx_PUPDR;
	volatile uint32_t GPIO_IDR;
	volatile uint16_t GPIO_ODR;
	volatile uint32_t GPIO_BSRR;
	
}GPIO_TYPE;
void GPIO_configure(GPIO_TYPE* ptr, uint32_t pin, uint32_t mode, uint32_t otype, uint32_t ospeed,
uint32_t updown);
void RCC_GPIO_enable(RCCENR_Type* ptr, uint32_t mask);
void pinWrite(GPIO_TYPE* ptr,uint32_t pin, uint32_t val);
void Systick_configure(SYSTICK_TYPE* ptr, uint32_t cycles, uint32_t source, uint32_t irq);

# define Systick ((SYSTICK_TYPE*) SYSTICK_BASE)
# define RCCENR ((RCCENR_Type*) RCCENR_BASE)
#define GPIOD ((GPIO_TYPE*) GPIOD_BASE)

void GPIO_configure(GPIO_TYPE* ptr, uint32_t pin, uint32_t mode, uint32_t otype, uint32_t ospeed,uint32_t updown)
{
	ptr->GPIO_MODER=(ptr->GPIO_MODER&~(uint32_t)(3<<pin*2))|(mode<<2*pin);
	ptr->GPIO_OTYPER=(ptr->GPIO_OTYPER&~(uint32_t)(1<<pin))|(otype<<pin);
	ptr->GPIO_OSPEEDR=(ptr->GPIO_OSPEEDR&~(uint32_t)(3<<pin*2))|(ospeed<<2*pin);
	ptr->GPIOx_PUPDR=(ptr->GPIOx_PUPDR&~(uint32_t)(3<<pin*2))|(updown<<2*pin);
	
}
void Systick_configure(SYSTICK_TYPE* ptr, uint32_t cycles, uint32_t source, uint32_t irq){
	ptr -> control = 0;
	ptr -> current = 0;
	ptr -> reload = cycles;
	ptr -> control = ptr -> control |(source<<2)|(irq<<1)|1;}
void pinWrite(GPIO_TYPE* ptr,uint32_t pin, uint32_t val){
	ptr->GPIO_BSRR |=1<< (pin +16*!val); }

void RCC_GPIO_enable(RCCENR_Type* ptr, uint32_t mask){
		ptr->AHB1ENR |= mask;
 }