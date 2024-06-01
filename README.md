# Wuthering Waves Boss Drop Simulation
## Overview
This program simulates the drop rates of echos from bosses in WW. It calculates the drop rates from farming one boss, or making use of the pity system with farming two. After the simulation, the drop rates are printed.

There exists a "pity system" for echo drops from bosses. If you do not recieve an echo drop, you are guaranteed to recieve an echo drop from the next boss you defeat, if it is from the same class. This can be used to achieve a 100% drop rate on a specific boss.

The purpose of this simulator/calculator is to determine if it is more efficient to farm one boss, or use the 100% drop rate pity system by farming two bosses.

## Features
- Simulates item drops from one and two bosses.
- Configurable drop probablity, number of times to simulate, and time to defeat each boss.
- Uses multi-threading to perform each simulation in its own thread.

## Requirements
- __Compiler__: `clang`
- Support for POSIX threads (`pthread`)

## Compilation
Using the provided Makefile:
```bash
make
```
This will create the `calc` executable in the project root directory.

## Usage
Run the program with the following options:
```bash
./calc [options]
```

- `-r <seed>`: Set the random seed (default is current time).
- `-p <probability>`: Set the drop probability (default is 0.2).
- `-f <first_time_units>`: Set the "time units" it takes to defeat the first boss (default is 1.0).
- `-s <second_time_units>`: Set the "time units" it takes to defeat the second boss (default is 0.8).
- `-t <simulation_times>`: Set the number of drops to simulate (default is 1,000,000).

## Cleaning Up
Using the provided Makefile:
```bash
make clean
```