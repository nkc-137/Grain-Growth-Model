# Grain-Growth-Model
A memory efficient implementation in C for phase-field modeling of grain growth in 2D based on a computationally efficient scheme developed by Kim et al.[1]. This implementation allows to carry out simulations for more than 500 grains in a system without hogging up of RAM. But the simulations can take hours together depending on the size of the system and the number of grains because all the computations are being carried out on one processor.

References:
1.Kim, Kim and Suzuki. "Computer simulations of two-dimensional and three-dimensional ideal grain growth"Phys Rev E Stat Nonlin Soft Matter Phys. 2006

## Getting Started
Make a clone of the folder in your local machine. 
### Pre-requisites
GCC compiler must be installed on your machine.
Optional: ffmpeg library must be installed inorder to convert images to videos. Installation instructions for the same will also be given.
### Installation
No installation is required! Open terminal/cmd in the folder and follow the instructions for carrying out simulations directly.

## Carrying out simulations
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
Check out the folder called 'your_data' because all the data obtained during simulations is contained in that folder in the form of .dat files. At the end of simulation a file called details.txt is also created in the same folder which contains the time taken by the program to run in seconds, minutes and hours.<br />

Now that you have obtained data, to plot the data you must run the following command:<br />
`$make plot`<br />
After executing this command all the plots will be available in 'plots' folder located inside your_data folder.
So the simulation process is finished at this point.<br />
In case you want to convert all the images to a video clip of your simulations you have to install 'ffmpeg' library. 
To install this library run this command:<br />
`sudo apt-get install ffmpeg`<br />
If you come across any error solutions can easily be found on https://stackoverflow.com/. <br />
After successful installation run the following command to make a video of the simulation:<br />
`make video`<br />
After this command executes you will find .mp4 file at the end in plots folder. This video has frame rate of 20 with a resolution of 1980X1080 in a YUV420p pixel format.<br />
You can store the data or videos in a separate folder on your local machine to make another simulation.
## Before making another simulation
Just before you start making another simulation you must clean all the files generated in the previous simulation to avoid mixing of data. To clean it simply use the following command:<br />
`make clean`<br />

## Notes
To get good results use more than 10000 time steps and output data for every 400 or 500 time steps. I have put 10000 time steps and data output for every 400 time steps as default.<br />
`make clean` command does not revert the changes made to 'Input_Data.txt' file.

