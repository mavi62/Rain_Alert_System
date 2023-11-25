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


![out spike](https://github.com/mavi62/Rain_Alert_System/assets/57127783/be21932d-56fc-4485-b162-6137d7d60652)


## C code for the design

```
//#include <stdio.h>
//#include <stdlib.h>
int main(){
	int rain_input;	
	int buzzer_output=0; 
	int buzzer_reg;
	int i;
	int mask =0xFFFFFFFD;
	buzzer_reg = buzzer_output*2;


	asm volatile(
	"and x30, x30, %1\n\t"
    	"or x30, x30, %0\n\t"  
    	:
    	: "r" (buzzer_reg), "r"(mask)
	: "x30" 
	);
	// rain_input=0;
	// for(i=0;i<8;i++)
	while(1)
	{	
		asm volatile(
		"andi %0, x30, 0x01\n\t"
		: "=r" (rain_input)
		:
		:);
       
	if (rain_input)
	{
		buzzer_output = 1; 
		
		buzzer_reg = buzzer_output*2;
		
		asm volatile(
		"and x30,x30, %1\n\t"  
		"or x30, x30, %0\n\t"   
		:
		: "r" (buzzer_reg), "r"(mask)
		: "x30" 
		);
 		//printf("Rain detected. Buzzer on.\n");
  		//printf("buzzer_output=%d \n", buzzer_output);
		// rain_input=0; 
		
	}	
	
	else
	{
		buzzer_output = 0;
		
		buzzer_reg = buzzer_output*2;

		asm volatile(
		"and x30,x30, %1\n\t"
		"or x30,x30, %0\n\t"
		:
		: "r"(buzzer_reg), "r"(mask)
		: "x30"
		);

		//printf("Rain not detected. Buzzer off.\n");
		//printf("buzzer_output=%d \n", buzzer_output);
		// rain_input=1; 
	}
	}

	return 0;

}
```

## Assembly code conversion

The above C program is compiled using the RISC-V GNU toolchain and the assembly code is dumped into a text file.

```
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o out rain_sensor.c 
riscv64-unknown-elf-objdump -d -r out > asm.txt
```

### Assembly code:

```
out:     file format elf32-littleriscv

Disassembly of section .text:

00010054 <main>:
   10054:	fe010113          	addi	sp,sp,-32
   10058:	00812e23          	sw	s0,28(sp)
   1005c:	02010413          	addi	s0,sp,32
   10060:	fe042623          	sw	zero,-20(s0)
   10064:	ffd00793          	li	a5,-3
   10068:	fef42423          	sw	a5,-24(s0)
   1006c:	fec42783          	lw	a5,-20(s0)
   10070:	00179793          	slli	a5,a5,0x1
   10074:	fef42223          	sw	a5,-28(s0)
   10078:	fe442783          	lw	a5,-28(s0)
   1007c:	fe842703          	lw	a4,-24(s0)
   10080:	00ef7f33          	and	t5,t5,a4
   10084:	00ff6f33          	or	t5,t5,a5
   10088:	001f7793          	andi	a5,t5,1
   1008c:	fef42023          	sw	a5,-32(s0)
   10090:	fe042783          	lw	a5,-32(s0)
   10094:	02078663          	beqz	a5,100c0 <main+0x6c>
   10098:	00100793          	li	a5,1
   1009c:	fef42623          	sw	a5,-20(s0)
   100a0:	fec42783          	lw	a5,-20(s0)
   100a4:	00179793          	slli	a5,a5,0x1
   100a8:	fef42223          	sw	a5,-28(s0)
   100ac:	fe442783          	lw	a5,-28(s0)
   100b0:	fe842703          	lw	a4,-24(s0)
   100b4:	00ef7f33          	and	t5,t5,a4
   100b8:	00ff6f33          	or	t5,t5,a5
   100bc:	fcdff06f          	j	10088 <main+0x34>
   100c0:	fe042623          	sw	zero,-20(s0)
   100c4:	fec42783          	lw	a5,-20(s0)
   100c8:	00179793          	slli	a5,a5,0x1
   100cc:	fef42223          	sw	a5,-28(s0)
   100d0:	fe442783          	lw	a5,-28(s0)
   100d4:	fe842703          	lw	a4,-24(s0)
   100d8:	00ef7f33          	and	t5,t5,a4
   100dc:	00ff6f33          	or	t5,t5,a5
   100e0:	fa9ff06f          	j	10088 <main+0x34>
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

For the processors being developed for the assembly program for my project, we will carry out the functional simulation. 

### Commands to run the verilog file

```
iverilog -o test processor.v testbench.v
./test
gtkwave waveform.vcd
```


![spike_1](https://github.com/mavi62/Rain_Alert_System/assets/57127783/8e348b6a-1835-48de-90c5-26d7e99dfa86)


![spike_2](https://github.com/mavi62/Rain_Alert_System/assets/57127783/2fed78e0-6efa-4808-8f18-654e053c6d96)


Given that the UART was omitted, write_done is becoming 1 at t=o, and the ID_instruction begins to run after the reset is made 0.


![spike_signal_30-1](https://github.com/mavi62/Rain_Alert_System/assets/57127783/1ac2349c-4541-488e-87ed-aaebf9709c89)


In reality, the ```$signal[31:0]``` is a representation of the x30 register, which stores inputs from the sensor after retrieving the values needed to calculate the output and then stores those values back in the register.

The ```ID_instruction``` is broken down into individual instructions, and only then do the subsequent stages one at a time.


![02078663](https://github.com/mavi62/Rain_Alert_System/assets/57127783/33b81395-31f7-4dce-83fa-979a7f25517c)


When the ID_instruction in the preceding figure is ```02078863```, the pc jumps to a specific instruction. This is because the instruction checks if the input is a 1, and if it isn't, the computer value doesn't increase by one; instead, it jumps to a different location.


![00ff6f33](https://github.com/mavi62/Rain_Alert_System/assets/57127783/e3faa21e-1614-4598-8100-ee6e419b6056)


Output is changing from 0 to 1 after the execution of instruction ```00FF6F33```.


![00ef7f33](https://github.com/mavi62/Rain_Alert_System/assets/57127783/746f9007-381d-4d56-b904-164136101714)


Output is changing from 1 to 0 after the execution of instruction ```00ef7f33```.

## Synthesis(Yosys) and GLS

### Commands to run synthesis

The ```processor.v``` file is modified before the synthesis is executed.

* Commenting the module definitions of both ```sky130_sram_2kbyte_1rw1r_32x256_8_data``` and ```sky130_sram_2kbyte_1rw1r_32x256_8_inst```.

* Since the CPU doesn't truly need 2k ram, the already instantiated sram modules are also modified from ```sky130_sram_2kbyte_1rw1r_32x256_8_data``` and ```sky130_sram_2kbyte_1rw1r_32x256_8_inst``` to ```sky130_sram_1kbyte_1rw1r_32x256_8```.

* Using ```writing_inst_done=1``` and ```writing_inst_done=0```, perform synthesis twice. and two netlists, dubbed ```synth_test.v``` and ```synth_processor.v```, respectively, are obtained. When ```writing_inst_done=1```, it indicates that simulation and verification are carried out using the matching netlist gate level and that the uart is passed in order to prevent the.vcd file from taking up more than 20 GB.

```
yosys
read_liberty -lib sky130_fd_sc_hd__tt_025C_1v80_256.lib 
read_verilog processor.v 
synth -top wrapper 
dfflibmap -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib
abc -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib
write_verilog synth_processor.v
```

Use the commands provided above to implement the design.


![yosys-1](https://github.com/mavi62/Rain_Alert_System/assets/57127783/70835809-bd0b-45f2-a6f9-c815217073c0)


### Gate level Simulation

Some modifications are done to the synthesised netlist file prior to doing gate level simulation utilizing the synthesised netlist.

* We modified the sram module instantiation names to match the standard cell before beginning synthesis, but since this is a simulation and not a cell, we must instantiate the module names exactly as they appear in the file ```sky130_sram_1kbyte_1rw1r_32x256_8.v```, which contains the sine module definition. Particularly, ```sky130_sram_1kbyte_1rw1r_32x256_8_data``` and ```sky130_sram_1kbyte_1rw1r_32x256_8_inst```.

* Additionally, replace the mem instructions in the ```sky130_sram_1kbyte_1rw1r_32x256_8.v``` file with our processor instructions, which are derived from the ```processor.v```.

Use the command below to launch the simulation once the modifications have been made.

```
iverilog -o synth_test testbench.v synth_test.v sky130_sram_1kbyte_1rw1r_32x256_8.v sky130_fd_sc_hd.v primitives.v
```

![gls_verify](https://github.com/mavi62/Rain_Alert_System/assets/57127783/6a8ce793-2739-4b28-b09b-a23db8876b89)


We can see some numbers underneath the dut on the left side of the above screenshot, which suggests that we used the synthesized netlist to simulate. Additionally, the behavior of the output matches that of the RTL functional simulation. Therefore, we can now continue with the OpenLane flow.

The wrapper module is seen in the following snapshot running the command in Yosys.

![yosys_fault](https://github.com/mavi62/Rain_Alert_System/assets/57127783/87c042c2-af87-4bb5-8130-bc029e89431a)


## Physical Design using OPENLANE 

***OVERVIEW OF PHYSICAL DESIGN***

Place and Route (PnR) is the core of any ASIC implementation and Openlane flow integrates into it several key open source tools which perform each of the respective stages of PnR. Below are the stages and the respective tools that are called by openlane for the functionalities as described:

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/c66ac9cb-2793-4c0b-a84d-66409d9c07ec)

Below are the stages and the respective tools that are called by openlane for the functionalities as described:

- Synthesis Generating gate-level netlist (yosys). Performing cell mapping (abc). Performing pre-layout STA (OpenSTA).

-  Floorplanning Defining the core area for the macro as well as the cell sites and the tracks (init_fp). Placing the macro input and output ports (ioplacer). Generating the power distribution network (pdn).

- Placement Performing global placement (RePLace). Perfroming detailed placement to legalize the globally placed components (OpenDP).

- Clock Tree Synthesis (CTS) Synthesizing the clock tree (TritonCTS).

- Routing Performing global routing to generate a guide file for the detailed router (FastRoute). Performing detailed routing (TritonRoute).

- GDSII Generation Streaming out the final GDSII layout file from the routed def (Magic).

***OPENLANE***

OpenLane is an automated RTL to GDSII flow based on several components including OpenROAD, Yosys, Magic, Netgen, CVC, SPEF-Extractor, CU-GR, Klayout and a number of custom scripts for design exploration and optimization. The flow performs full ASIC implementation steps from RTL all the way down to GDSII.

More about Openlane at : https://github.com/The-OpenROAD-Project/OpenLane

***MAGIC***

Magic is a venerable VLSI layout tool, written in the 1980's at Berkeley by John Ousterhout, now famous primarily for writing the scripting interpreter language Tcl. Due largely in part to its liberal Berkeley open-source license, magic has remained popular with universities and small companies. The open-source license has allowed VLSI engineers with a bent toward programming to implement clever ideas and help magic stay abreast of fabrication technology. However, it is the well thought-out core algorithms which lend to magic the greatest part of its popularity. Magic is widely cited as being the easiest tool to use for circuit layout, even for people who ultimately rely on commercial tools for their product design flow.

More about magic at http://opencircuitdesign.com/magic/index.html

## Preparing the Design
Preparing the design and including the lef files: The commands to prepare the design and overwite in a existing run folder the reports and results along with the command to include the lef files is given below:

```bash
sed -i's/max_transition   :0.04/max_transition   :0.75'*/*.lib
```
*OpenLane Interactive Flow:*

***The openlane flow is performed on Emil Jayanth Lal's system.***

```bash
make mount
%./flow.tcl -interactive
% package require openlane 0.9
% prep -design project
% run_synthesis; run_floorplan; run_placement; run_cts; gen_pdn; run_routing

```

![Screenshot from 2023-11-14 13-17-10](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/d1206f14-e263-4925-88f8-918e229b217f)

Completion of routing 

![Screenshot from 2023-11-14 13-17-22](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/8eaea1dc-a4d7-42f0-9c2f-4c4e15d3e81b)

Sign off steps 

```bash
run_magic
run_magic_spice_export
run_magic_drc
run_antenna_check
```

![Screenshot from 2023-11-14 13-46-36](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/88a55c5f-eaa4-4b91-900d-5a363e030011)


## Reports 

***SYNTHESIS***

- Logic synthesis uses the RTL netlist to perform HDL technology mapping. The synthesis process is normally performed in two major steps:
  - GTECH Mapping – Consists of mapping the HDL netlist to generic gates what are used to perform logical optimization based on AIGERs and other topologies created from the generic mapped netlist
  - Technology Mapping – Consists of mapping the post-optimized GTECH netlist to standard cells described in the PDK.

- To synthesize the code run the following command.
```bash
run_synthesis
```

![Screenshot from 2023-11-14 20-30-06](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/fda5e990-c067-4c4a-8dda-f28258a6d1a1)

***FLOORPLAN***

- Goal is to plan the silicon area and create a robust power distribution network (PDN) to power each of the individual components of the synthesized netlist. In addition, macro placement and blockages must be defined before placement occurs to ensure a legalized GDS file. In power planning we create the ring which is connected to the pads which brings power around the edges of the chip. We also include power straps to bring power to the middle of the chip using higher metal layers which reduces IR drop and electro-migration problem.

- Following command helps to run floorplan:

```bash
run_floorplan
```

- to view the floorplan on Magic from ```results/floorplan```

```bash
 magic -T ~/.volare/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &
```
![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/0713e283-106d-49a3-9bc0-f11bab45d481)

- Core Area after floorplan

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/18eba386-cc1f-4d3e-a299-8415428cd6cc)

- Die Area after floorplan

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/7d892f9b-6c5b-49e1-bc4f-849808ac5a9e)


***PLACEMENT***

- Place the standard cells on the floorplane rows, aligned with sites defined in the technology lef file. Placement is done in two steps: Global and Detailed. In Global placement tries to find optimal position for all cells but they may be overlapping and not aligned to rows, detailed placement takes the global placement and legalizes all of the placements trying to adhere to what the global placement wants. The next step in the OpenLANE ASIC flow is placement. The synthesized netlist is to be placed on the floorplan. Placement is perfomed in 2 stages:
  - Global Placement
  - Detailed Placement

- Run the following command to run the placement:

```bash
run_placement
```

- to view the placement on Magic from ```results/placement```

```bash
 magic -T ~/.volare/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &
```

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/6763b55d-9035-4153-adb7-fa9b1544b5a0)


***CLOCK TREE SYNTHESIS***

Clock tree synteshsis is used to create the clock distribution network that is used to deliver the clock to all sequential elements. The main goal is to create a network with minimal skew across the chip. H-trees are a common network topology that is used to achieve this goal.

The purpose of building a clock tree is enable the clock input to reach every element and to ensure a zero clock skew. H-tree is a common methodology followed in CTS.
Following command is used to run CTS.

```bash
run_cts
```

- Timimg Report

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/39ac231d-b3a6-4e6a-bc34-3a659cb41f4a)

- Area Report

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/ccaf0213-777a-4854-95c7-2141bcd67ad1)

- Skew Report

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/d1baeba3-99a1-4b61-9435-25b951e42e38)

- Power Report

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/3808c1c2-1070-4060-af5e-412e54f930e6)


***POWER NETWORK DISTRIBUTION***

- The commmand to establish power distribution network is as follows

```bash
gen_pdn
```

***ROUTING***

- Implements the interconnect system between standard cells using the remaining available metal layers after CTS and PDN generation. The routing is performed on routing grids to ensure minimal DRC errors.
- OpenLANE uses the TritonRoute tool for routing. There are 2 stages of routing:
  - Global Routing
  - Detailed Routing

- In Global Routing Routing region is divided into rectangle grids which are represented as course 3D routes (Fastroute tool).
- In Detailed Finer grids and routing guides used to implement physical wiring (TritonRoute tool).

- Run the following command to run the routing

```bash
run_routing
```
- The layout can be viewed using MAGIC in ```results/routing```

```bash
 magic -T ~/.volare/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &
```

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/bf1121d8-5196-4a59-b7ce-ea1dd2e92703)

- Area of Design

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/74dc28ae-a53a-444c-b213-1ad8c6c9f81b)

- Post Routing Reports
  
  -  Timing

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/2a166a15-8430-4bae-b9ea-e512418ca475)

  -  Area
 
![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/ff4cadde-06b1-45be-8760-13f277def0bd)
 
  -  Power

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/e4bdc3a3-d2e7-4f05-a09b-3395f700911f)
 
  -  Design Rule Check (DRC)

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/a971d705-9e57-499d-82b7-012206d12555)




## Word of Thanks
I would take this opportunity to sciencerly thank Mr. Kunal Gosh(Founder/VSD) for helping me out to complete this flow smoothly.

I would take this opportunity to Emil Jayanth Lal, for his assistance in the completion of the Physical Design under OpenLane flow.

## Acknowledgement
- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Skywater Foundry
- OpenAI Chatgpt
- Alwin Shaju, MTech, IIITB
- Emil Jayanth Lal, MTech, IIITB
- N Sai Sampath, MTech, IIITB
- Mayank Kabra, Founder, Chipcron Pvt.Ltd.

## Reference
- https://github.com/The-OpenROAD-Project/OpenSTA.git
- https://github.com/The-OpenROAD-Project/OpenLane
- https://github.com/kunalg123
- https://www.vsdiat.com
- https://openlane.readthedocs.io/en/latest
- https://github.com/SakethGajawada/RISCV-GNU

## Acknowledgement

1. Kunal Ghosh, VSD Corp. Pvt. Ltd.
2. Mayank Kabra, IIIT-Bangalore
3. Emil Jayanth Lal, Colleague, IIIT-Bangalore

## References

1. https://github.com/SakethGajawada/RISCV-GNU
2. https://github.com/kunalg123
