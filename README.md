# Race-Judgement-System
This program stores the data obtained from races and performs various operations on the data to obtain useful information.

Following is some info about the input format, and the functionality of the implemented functions:


First input is the sector times in a single race. A sector is one part (or section) of
a race track and race track is always divided into 3 sectors. So, when a driver completes all three
sectors of the track s/he completes one full lap. Consequently, one lap time equals to sum of the
sector times for that lap. 

This input only contains the sector times as floating point numbers with two digits after the
decimal point. It does not contain driver ID or lap number, those are inherent. You can think
of it as a three dimensional array; where firstdimension is the drivers, second dimension is laps 
and the third dimension is sectors. Thus, firstelement of the array holds sector times of
Driver0 grouped by laps. Similarly, second element ofthe first element of the array
contains the sector times of Driver0 for Lap 1.
Finally, each lap always consists of 3 sectors and all drivers completes the same number of laps.
The number of drivers and number of laps in a race may vary and they will be input before
the table itself. For convenience, driver IDs and lap numbers start from 0, so that they match
their corresponding array indices.



--float*** create sector times(unsigned int* n drivers, unsigned int* n laps):
This function will read sector times input from stdin. First two inputs will be the number of
drivers and number of laps. These inputs will be stored in n drivers and n laps (which
have been passed by reference) respectively. After allocating exactly the necessary memory
for the 3-dimensional array, sector times should be read from stdin. Each input line after the
first one consists of sector times of one lap. Once operations with reading inputs are complete,
this function returns the 3-dimensional array containing the sector times. First 3 times
are the sectors of the Lap 0 of Driver0, second 3 times are the Lap 1 of Driver0 and so on.
Example
input:
2 3
22.17 34.85 27.46
20.19 32.48 27.51
23.17 35.10 29.02
25.27 33.65 29.50
24.07 36.47 25.16
19.48 33.17 29.56


--unsigned int** create positions(unsigned int* p drivers, unsigned int* n races):
Similar to create sector times this function will first read number of drivers and number
of races and store them in their respective variables. Next, it will read finishing positions
of drivers and return the 2-dimensional array containing these positions (with exactly the
correct size). Each input line after the first one consists of finishing positions of one driver.
Again, all inputs will be taken from stdin. First line holds the positions of Driver0, second
line holds the positions of Driver1 and so on. 
Example input:
2 5
2 5 3 11 9
7 24 13 17 17


--float** calculate lap times(float*** sector times, unsigned int n drivers, unsigned int n laps):
Given sector times (sector times), number of drivers (n drivers) and number of laps
(n laps), this function will calculate lap times for all drivers. Finally, the function will
return 2-dimensional array containing the lap times. 


--unsigned int find fastest lap(float** lap times, unsigned int n drivers, unsigned int n laps):
Given lap times (lap times), number of drivers (n drivers) and number of laps (n laps)
this function will find the driver who completed the fastest lap in the race. This function will return the ID
of the driver who has the fastest lap time. ID of a driver corresponds to the driver’s index
in the first dimension of lap times. If times are the same for two drivers, it's assumed that the
driver with the smaller ID finishes before the other.


--unsigned int find driver fastest lap(float** sector times of driver, unsigned int n laps):
Given sector times of a single driver (sector times of driver) and number of laps (n laps),
this function will return the lap number of this driver’s fastest lap. If the laps have the same
time, it's assumed that the lap with the smaller lap number is completed faster.


--float* selection sort(float* arr, unsigned int len, char order): 
Given an array(arr), length of that array (len) and an ordering (order), this function will return a sorted
copy of arr (without modifying the original arr). Order ’A’ (ascending) or ’D’ (descending)
denotes the ordering of the sort operation.


--unsigned int* find finishing positions(float** lap times, unsigned int n drivers, unsigned int n laps): 
Given lap times (lap times), number of drivers (n drivers) and number of laps (n laps)
this function will find the race result, that is, the finishing position
of each driver. Finishing positions are based on the sum of lap times for each driver (shorter
time means higher ranking). The array this function will return, holds IDs of the drivers
sorted on their race completion time.


--float* find time diff(float** lap times, unsigned int n drivers, unsigned int n laps, unsigned int driver1, unsigned int driver2): 
Given lap times (lap times), number of drivers (n drivers), number of laps (n laps)
and two driver IDs (driver1 and driver2) this function will find the time difference
between two drivers for each lap. This will be done by subtracting driver2’s lap time
from driver1’s lap time. The function will return the array containing these differences.
Time differences for laps are accumulated (i.e. carries onto the next lap).


--unsigned int* calculate total points(unsigned int** positions, unsigned int p drivers, unsigned int n races): 
Given positions (positions), number of drivers (p drivers) and number of races (n races),
this function will read position-point mapping from stdin and
return the total point each driver received. For example if p drivers is 10 and finishing
positions for two drivers are:
Driver0: {1, 2, 2, 4}
Driver1: {3, 1, 5, 6},
and the position-point mapping read from stdin is:
25 18 15 12 10 8 6 4 2 1
Total points for Driver0 is (25+18+18+12 = 73), and for Driver1 it is (15+25+10+8 = 58).
The position-point mapping you are going to read from stdin will contain p drivers of
unsigned integer values where the first integer corresponds to points received for finishing
first, second integer for finishing second and so on. This function returns the array
containing total points for each driver in the index determined by driver’s ID (e.g. following
the above example, first element of the array should be 73 and the second element at index
1 should be 58).


--unsigned int find season ranking(unsigned int* total points, unsigned int p drivers, unsigned int id): 
Given total points (total points), number of drivers (p drivers) and
a driver ID (id) this function returns the season ranking of driver
with ID id. Higher total points means the driver finished at a higher ranking
and the driver with the highest points is ranked 1st. If points are the same for
two drivers, it's assumed that the driver with the smaller ID is ranked higher.


Happy coding :)
