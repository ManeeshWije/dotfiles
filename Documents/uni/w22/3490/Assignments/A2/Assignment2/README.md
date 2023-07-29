# Assignment 2

- NAME: Maneesh Wijewardhana
- COURSE: CIS\*3490
- ID: 1125828
- DUE DATE: FEB 14, 2022
- Assignment 2 - Counting Inversions & Finding Shortest Path Around

## Compilation and Running

- To compile, run make, this will create an A2 executable. Then run ./A2 to run the executable which will prompt a menu for you to choose what you would like to see. The file names are hard coded into the program so just make sure data_A2_Q1.txt and data_A2_Q2.txt are in the same directory as the source files.
- For Part 2, the program will compute the hull and list the points in it along with the time it took in ms. Using that information, you will be able to enter a point s1 and another point s2 in order to find the shortest path around.
- After this, the program will display the number of points on the shortest path, distance, and points on the path.

## Notes

- Created an A2Header.h just to keep all function prototypes in as well as struct for Points in Part 2.

### Runtimes were tested on an M1 Macbook Pro and the times were as follows:

- Brute Force Inversions: ~3669ms
- Recursive Divide-and-Conquer Inversions: ~15ms
- Brute Force Convex Hull: ~24869ms
- Recursive Divide-and-Conquer Convex Hull: ~14ms
