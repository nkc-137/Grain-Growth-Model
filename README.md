# Grain-Growth-Model
A memory efficient implementation in C for phase-field modeling of grain growth in 2D based on a computationally efficient scheme developed by Kim et al.[1]. This implementation allows to carry out simulations for more than 500 grains in a system without hogging up of RAM. But the simulations can take hours together depending on the size of the system and the number of grains because all the computations are being carried out on one processor.

References:
1.Kim, Kim and Suzuki. "Computer simulations of two-dimensional and three-dimensional ideal grain growth"Phys Rev E Stat Nonlin Soft Matter Phys. 2006

## Getting Started
Make a clone of the folder in your local machine. 
### Pre-requisites
GCC compiler must be installed on your machine.
### Installation
No installation is required! Open a terminal/cmd in the folder and follow the instructions for carrying out simulations directly.

## Carrying out of simulations
Before starting off with simulations first open the Input_Data.txt file which contains initial parameters to be given as input
1. Number of grains
2. Size of the system
3. Output data after n time steps
4. Total number of time steps of the simulation
After entering the desired values save the file and brace yourself to run the code.

To run simulations first you have to convert C code to machine language and then to an executable. To do this use this command: <br />
`$make` <br />
To run the executable and start simulations, use this command:<br />
`$make run`<br />
Or you could even do this:<br />
`$./executable`<br />
The simulations take time depending upon the parameters given in Input_Data.txt. After every 1000 time steps a statement appears on the command line saying that so and so number of time steps are finished, just to make sure that the code is running.

## What to do next?
All the data obtained during simulations is contained in a folder called 'your_data' in the form of .dat files. At the end of simulation a file called details.txt is created in the same folder which contains the time taken by the program to run in seconds, minutes and hours.

