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

int main(){
int rain_sensor_ip;
int roof_status_op;
int dummy;
    while(1){
    // Simulated rain sensor input (1: No rain, 0: Rain)
 // rain_sensor_ip = digital_read(0);
 int rain_sensor_ip;
 asm volatile(
            "and %0, x30, 1\n\t"
            : "=r"(rain_sensor_ip)
        );
        


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
    return(0);
}


 //assuming sensors gives 0 if it detects rain
    //sensors to detect rain :    0    
    //gpio's for buzzer  : 2

```

## Assembly code conversion

The above C program is compiled using the RISC-V GNU toolchain and the assembly code is dumped into a text file.

### Assembly code:

```

out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fe010113          	addi	sp,sp,-32
   10058:	00812e23          	sw	s0,28(sp)
   1005c:	02010413          	addi	s0,sp,32
   10060:	001f7793          	andi	a5,t5,1
   10064:	fef42623          	sw	a5,-20(s0)
   10068:	fec42703          	lw	a4,-20(s0)
   1006c:	00100793          	li	a5,1
   10070:	00f70e63          	beq	a4,a5,1008c <main+0x38>
   10074:	ffb00793          	li	a5,-5
   10078:	fef42423          	sw	a5,-24(s0)
   1007c:	fe842783          	lw	a5,-24(s0)
   10080:	00ff7f33          	and	t5,t5,a5
   10084:	004f6f13          	ori	t5,t5,4
   10088:	fd9ff06f          	j	10060 <main+0xc>
   1008c:	ffb00793          	li	a5,-5
   10090:	fef42423          	sw	a5,-24(s0)
   10094:	fe842783          	lw	a5,-24(s0)
   10098:	00ff7f33          	and	t5,t5,a5
   1009c:	000f6f13          	ori	t5,t5,0
   100a0:	fc1ff06f          	j	10060 <main+0xc>

```

<br />
The above assembly code was run on a Python script to find the different instructions used:
<br />

```
Number of different instructions: 9
List of unique instructions:
addi
j
andi
lw
beq
ori
sw
li
and

```

## Acknowledgement

1. Kunal Ghosh, VSD Corp. Pvt. Ltd.
2. Sumanto Kar,VSD Corp.
3. Mayank Kabra, IIIT-Bangalore
4. Emil Jayanth Lal, Colleague, IIIT-Bangalore

## References

1. https://github.com/SakethGajawada/RISCV-GNU
2. https://github.com/kunalg123
