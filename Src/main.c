//LED CONNECTED
//PORT C 0x4001 1000
//PIN 13

#define PERIPH_BASE  		(0x40000000UL) // Definición de la dirección base para los periféricos

#define APB2PERIPH_OFFSET 	(0x00011000UL) // Definición del offset para el bus APB2 (Advanced Peripheral Bus 2)
#define APB2PERIPH_BASE 	(PERIPH_BASE + APB2PERIPH_OFFSET) //0x4001 1000 Cálculo de la dirección base para los periféricos en el bus APB2

#define GPIOC_OFFSET 		(0x0000UL)	   // Offset para el puerto GPIOC
#define GPIOC_BASE 			(APB2PERIPH_BASE + GPIOC_OFFSET) //0x4001 1000 Cálculo de la dirección base para GPIOC

#define RCC_OFFSET 			(0x00010000UL) // Offset para el registro RCC (Reset and Clock Control)
#define RCC_BASE    		(APB2PERIPH_BASE + RCC_OFFSET)  //0x4002 1000 Cálculo de la dirección base para el registro RCC

#define APB2_EN_R_OFFSET 	(0x18UL)       // Offset para el registro de habilitación del reloj del APB2
#define RCC_APB2EN_R		(*(volatile unsigned int *)(RCC_BASE + APB2_EN_R_OFFSET))//0x4002 1018  Registro para habilitar el reloj de GPIOC

#define MODE_R_OFFSET		(0x04)		  // Offset para el registro de modo de GPIOC
#define GPIOC_MODE_R		(*(volatile unsigned int *)(GPIOC_BASE + MODE_R_OFFSET)) //0x4001 1004 Registro de modo de GPIOC (Configura el modo de los pines)

#define OD_R_OFFSET			(0x0CUL)	 // Offset para el registro de salida de datos de GPIOC
#define GPIOC_OD_R			(*(volatile unsigned int *)(GPIOC_BASE + OD_R_OFFSET)) //0x4001 100C Registro de salida de datos de GPIOC

#define GPIOCEN 			(1U<<4)  //0000 0000 0000 0000 0000 0000 0001 0000 Máscara para habilitar el reloj de GPIOC (Bit 4 en el registro RCC)

#define PIN_13				(1U<<13) // Máscara para el pin 13 de GPIOC (Bit 13)
#define LED_PIN				PIN_13


int main(void){

	//Habilitar el reloj para GPIOC
	RCC_APB2EN_R |= GPIOCEN;

	// Configurar el pin 13 de GPIOC como salida (modo general de salida)
	//GPIOC_MODE_R |= 0x00200000; //SET BIT 21 IN 1 &=  ~^
	GPIOC_MODE_R |= (1U<<21); //SET BIT 21 IN 1 &=  ~^


	while(1){
		// Establecer el pin 13 en bajo para encender el LED
		//GPIOC_OD_R &=~ LED_PIN;

		 // Si quieres alternar el estado del LED
		 GPIOC_OD_R ^= LED_PIN; //0x00002000;
		 // La línea siguiente es para un retraso
		 for(int i = 0; i<100000; i++){}

	}
}


