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
       //#include <stdio.h>

int main(){
    while(1){
        read();
    }
    return(0);
}

void read();
void control_roof();
 //assuming sensors gives 0 if it detects rain
    //sensors to detect rain :    0    
    //gpio's for buzzer  : 2

void control_roof() {
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
        
control_roof();
}


```

## Assembly code conversion

The above C program is compiled using the RISC-V GNU toolchain and the assembly code is dumped into a text file.<br />

Below codes are run on the terminal to get the assembly code.<br />
