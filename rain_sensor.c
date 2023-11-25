#include<stdio.h>

int main(){
	int rain_input;	
	int roof_output = 0; 
	int roof_reg;
	int mask =0xFFFFFFFD;
	roof_reg = roof_output*2;


	asm volatile(
	"and x30, x30, %1\n\t"
    	"or x30, x30, %0\n\t"  
    	:
    	: "r" (roof_reg), "r"(mask)
	: "x30" 
	);
	
	while(1)
	{	
		asm volatile(
		"andi %0, x30, 0x01\n\t"
		: "=r" (rain_input)
		:
		:);

	if (rain_input)
	{
		roof_output = 0; 
		mask =0xFFFFFFFD;
		roof_reg = roof_output*2;
		
		asm volatile(
		"and x30,x30, %1\n\t"  
		"or x30, x30, %0\n\t"   
		:
		: "r" (roof_reg), "r"(mask)
		: "x30" 
		);
 		printf("Rain not detected. Buzzer off.\n");
  		printf("roof_output=%d \n", roof_output);
	}	
	
	else
	{
		roof_output = 1; 
		mask =0xFFFFFFFD;
		roof_reg = roof_output*2;
		asm volatile(
		"and x30,x30, %1\n\t"  
	   	"or x30, x30, %0\n\t"  
	   	:
	   	: "r" (roof_reg), "r"(mask)
		: "x30" 
		);
		printf("Rain detected. Buzzer on.\n");
		printf("roof_output=%d \n", roof_output);
	}
	}

	return 0;

}
