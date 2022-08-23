## CSPB 2270 – Data Structures - Term Project

# Circular Buffer
The circular buffer is a specialized ADT that is used to store and retreive large streams of data.  A key feature of the Circular Buffer is that once the buffer fills, old data is replaced by new data.  This is advantageous when working with a high volume of data but limited space to store it in.  The circular buffer often also utilizes the first in, first out princple where the first data that is added to the buffer is the first data to exit.  This is true both when reading and overwriting the data. 

The circular buffer has a wide range of applications in different devices.  It can be used to store video or audio 'frames' enabling smoother playback.  For example, a buffer on a streaming platform might hold 60 seconds of previous video frames so that if the user missed something, they could go back without the platform having to reload all those frames.  As the user continues to watch a show, the old frames are thrown out and replaced by newer ones.  

The advantage of the circular buffer over other data types is that it is contstant time complexity for all of its functions.  Unlike a more general array, it is more specialized in that it only writes at the head location and reads at the tail location.  This feature makes it a better candidate for specific applications that need to store and retrieve data on a first in first out basis.  

# Compiling the code
The code is split into a .h and .cpp file in the code_1 folder.

The code can be compiled with CMAKE.  Navigate to the build folder and run CMAKE .. on the current directory.  Next, run make which will build the executable files.  This will create a test executable file called "run_tests" which can be run with ./run_tests while still in the build folder.