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

## C code for the design

```


void read();
void buzzer();
int main(){
    while(1){
        read();
    }
    return(0);
}


 //assuming sensors gives 0 if it detects rain
    //sensors to detect rain :    0    
    //gpio's for buzzer  : 2

void buzzer() {
int rain_sensor_ip;
int roof_status_op;
int dummy;

    if (rain_sensor_ip!=1) {
        
       dummy = 0xFFFFFFFB;
        asm volatile(
            "and x30, x30, %0\n\t"     
            "or x30, x30, 4\n\t"    // output at 3rd bit, that switches on the buzzer(........000100)
            :
            :"r"(dummy)
            :"x30"
            );

        
    } else {
       
       dummy = 0xFFFFFFFB;
       asm volatile(
            "and x30, x30, %0\n\t"    
            "or x30, x30, 0\n\t"       // output at 3rd bit , that switches off the buzzer(........000)
            :
            :"r"(dummy)
            :"x30"
        );
    }
}

void read(){
// Simulated rain sensor input (1: No rain, 0: Rain)
 // rain_sensor_ip = digital_read(0);
 int rain_sensor_ip;
 asm volatile(
            "and %0, x30, 1\n\t"
            : "=r"(rain_sensor_ip)
        );
        
buzzer();
}

```

## Assembly code conversion

The above C program is compiled using the RISC-V GNU toolchain and the assembly code is dumped into a text file.

### Assembly code:

```


out:     file format elf32-littleriscv


Disassembly of section .text:

00010074 <main>:
   10074:	ff010113          	add	sp,sp,-16
   10078:	00112623          	sw	ra,12(sp)
   1007c:	00812423          	sw	s0,8(sp)
   10080:	01010413          	add	s0,sp,16
   10084:	05c000ef          	jal	100e0 <read>
   10088:	ffdff06f          	j	10084 <main+0x10>

0001008c <buzzer>:
   1008c:	fe010113          	add	sp,sp,-32
   10090:	00812e23          	sw	s0,28(sp)
   10094:	02010413          	add	s0,sp,32
   10098:	fec42703          	lw	a4,-20(s0)
   1009c:	00100793          	li	a5,1
   100a0:	00f70e63          	beq	a4,a5,100bc <buzzer+0x30>
   100a4:	ffb00793          	li	a5,-5
   100a8:	fef42423          	sw	a5,-24(s0)
   100ac:	fe842783          	lw	a5,-24(s0)
   100b0:	00ff7f33          	and	t5,t5,a5
   100b4:	004f6f13          	or	t5,t5,4
   100b8:	0180006f          	j	100d0 <buzzer+0x44>
   100bc:	ffb00793          	li	a5,-5
   100c0:	fef42423          	sw	a5,-24(s0)
   100c4:	fe842783          	lw	a5,-24(s0)
   100c8:	00ff7f33          	and	t5,t5,a5
   100cc:	000f6f13          	or	t5,t5,0
   100d0:	00000013          	nop
   100d4:	01c12403          	lw	s0,28(sp)
   100d8:	02010113          	add	sp,sp,32
   100dc:	00008067          	ret

000100e0 <read>:
   100e0:	fe010113          	add	sp,sp,-32
   100e4:	00112e23          	sw	ra,28(sp)
   100e8:	00812c23          	sw	s0,24(sp)
   100ec:	02010413          	add	s0,sp,32
   100f0:	001f7793          	and	a5,t5,1
   100f4:	fef42623          	sw	a5,-20(s0)
   100f8:	f95ff0ef          	jal	1008c <buzzer>
   100fc:	00000013          	nop
   10100:	01c12083          	lw	ra,28(sp)
   10104:	01812403          	lw	s0,24(sp)
   10108:	02010113          	add	sp,sp,32
   1010c:	00008067          	ret

```

<br />
The above assembly code was run on a Python script to find the different instructions used:
<br />

```
Number of different instructions: 11
List of unique instructions:
add
sw
and
ret
jal
or
beq
j
nop
lw
li

```

## Acknowledgement

1. Kunal Ghosh, VSD Corp. Pvt. Ltd.
2. Sumanto Kar,VSD Corp.
3. Mayank Kabra, IIIT-Bangalore
4. Emil Jayanth Lal, Colleague, IIIT-Bangalore

## References

1. https://github.com/SakethGajawada/RISCV-GNU
2. https://github.com/kunalg123
