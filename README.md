# Rain_Alert_System

This Repository summarizes the work progress made in The RISC-V-based project.
<br />

## Motive

The motivation to create a Rain Alert System using raindrop sensors is driven by a commitment to safety, property protection, agricultural sustainability, resource management, scientific advancement, community resilience, energy efficiency, accessibility, education, and the overall welfare of society. This system represents a proactive approach to weather awareness, benefitting individuals and communities alike.

## Requirement

Here we will be using a Rain Drop Sensor. A rin drop sensor works on the principle of resistance. The raindrop sensor measures the moisture via analog output pins and it provides a digital output when a threshold of moisture exceeds.We also need a power supply and an alert mechanism, which in our case is a buzzer, which gets turned on when the moisture exceeds the threshold.

## Block Diagram

![1](https://github.com/mavi62/Rain_Alert_System/assets/57127783/cfa0af59-92ff-4983-8524-6959ff12167e)

## Testing the code

1. Open a terminal window
2. Navigate to the directory when the .c file is present
3. Compile the code designed using gcc and verify the output.

```
gcc rain_sensor.c
./a.out
```

## Spike Simulation

Commands to run spike: 

```

riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o out rain_sensor.c
spike pk out

```


![outputs](https://github.com/mavi62/Rain_Alert_System/assets/57127783/b0a24237-919f-4e77-9559-c03e43fd70f8)


## C code for the design

```

//#include <stdio.h>
//#include <stdlib.h>
int main(){
	int rain_input;	
	int roof_output=0; 
	int roof_reg;
	int i;
	int mask =0xFFFFFFFD;
	roof_reg = roof_output*2;

	asm volatile(
	"and x30, x30, %1\n\t"
    	"or x30, x30, %0\n\t"  
    	:
    	: "r" (roof_reg), "r"(mask)
	: "x30" 
	);

	//for(i=0;i<3;i++)
	while(1)
	{	
		asm volatile(
		"andi %0, x30, 0x01\n\t"
		: "=r" (rain_input)
		:
		:);
        //rain_input=0;
	if (rain_input)
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
 		//printf(Rain detected. Buzzer on.\n");
  		//printf("roof_output=%d \n", roof_output);
	}	
	
	else
	{
		roof_output = 0;
		mask =0xFFFFFFFD;
		roof_reg = roof_output*2;

		asm volatile(
		"and x30,x30, %1\n\t"
		"or x30,x30, %0\n\t"
		:
		: "r"(roof_reg), "r"(mask)
		: "x30"
		);

		//printf("Rain not detected. Buzzer off.\n");
		//printf("roof_output=%d \n", roof_output);
	}
	}

	return 0;

}

```

## Assembly code conversion

The above C program is compiled using the RISC-V GNU toolchain and the assembly code is dumped into a text file.

### Assembly code:

```

out:     file format elf32-littleriscv

Disassembly of section .text:

00010054 <main>:
   10054:       fe010113                addi    sp,sp,-32
   10058:       00812e23                sw      s0,28(sp)
   1005c:       02010413                addi    s0,sp,32
   10060:       fe042623                sw      zero,-20(s0)
   10064:       ffd00793                li      a5,-3
   10068:       fef42423                sw      a5,-24(s0)
   1006c:       fec42783                lw      a5,-20(s0)
   10070:       00179793                slli    a5,a5,0x1
   10074:       fef42223                sw      a5,-28(s0)
   10078:       fe442783                lw      a5,-28(s0)
   1007c:       fe842703                lw      a4,-24(s0)
   10080:       00ef7f33                and     t5,t5,a4
   10084:       00ff6f33                or      t5,t5,a5
   10088:       001f7793                andi    a5,t5,1
   1008c:       fef42023                sw      a5,-32(s0)
   10090:       fe042783                lw      a5,-32(s0)
   10094:       02078863                beqz    a5,100c4 <main+0x70>
   10098:       fe042623                sw      zero,-20(s0)
   1009c:       ffd00793                li      a5,-3
   100a0:       fef42423                sw      a5,-24(s0)
   100a4:       fec42783                lw      a5,-20(s0)
   100a8:       00179793                slli    a5,a5,0x1
   100ac:       fef42223                sw      a5,-28(s0)
   100b0:       fe442783                lw      a5,-28(s0)
   100b4:       fe842703                lw      a4,-24(s0)
   100b8:       00ef7f33                and     t5,t5,a4
   100bc:       00ff6f33                or      t5,t5,a5
   100c0:       fc9ff06f                j       10088 <main+0x34>
   100c4:       00100793                li      a5,1
   100c8:       fef42623                sw      a5,-20(s0)
   100cc:       ffd00793                li      a5,-3
   100d0:       fef42423                sw      a5,-24(s0)
   100d4:       fec42783                lw      a5,-20(s0)
   100d8:       00179793                slli    a5,a5,0x1
   100dc:       fef42223                sw      a5,-28(s0)
   100e0:       fe442783                lw      a5,-28(s0)
   100e4:       fe842703                lw      a4,-24(s0)
   100e8:       00ef7f33                and     t5,t5,a4
   100ec:       00ff6f33                or      t5,t5,a5
   100f0:       f99ff06f                j       10088 <main+0x34>

```

<br />
The above assembly code was run on a Python script to find the different instructions used:
<br />

```

Number of different instructions: 10
List of unique instructions:
beqz
sw
andi
slli
j
lw
and
li
addi
or

```

## Functional Simluation

* We will do the functional simulation for the processors that are being created for the assembly program that is being created for my application. The ```processor.v``` and the ```testbench.v``` is uploaded and those can be seen above.
* 
* Commands to run the verilog file

      iverilog -o test processor.v testbench.v
      ./test
      gtkwave waveform.vcd



* In the above figure, we can see the test results stating fails:0 which means that UART transmission is done without any error.


## Acknowledgement

1. Kunal Ghosh, VSD Corp. Pvt. Ltd.
2. Sumanto Kar,VSD Corp.
3. Mayank Kabra, IIIT-Bangalore
4. Emil Jayanth Lal, Colleague, IIIT-Bangalore

## References

1. https://github.com/SakethGajawada/RISCV-GNU
2. https://github.com/kunalg123
