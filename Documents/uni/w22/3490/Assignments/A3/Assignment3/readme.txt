NAME: MANEESH WIJEWARDHANA
ID: 1125828
DUE DATE: MARCH 14, 2022
COURSE: CIS*3490

ASSIGNMENT 3 - README

- Compilation and Running
  - To compile, simply run make
  - To run, type ./A3 and choose a menu option
  - For part 1, you will have to enter the filename you are using exactly
  - For part 2, it uses a hardcoded file name as per the pdf instructions and relies on it having the same format and counts as the test files

- 2.4 Analysis 
  - Brute Force
    PATTERN       # OF SHIFTS       TIME       COUNT
    to            3281348           28ms       15252
    the           3268261           26ms       28338
    this          3295215           29ms       1383
    course        3294976           23ms       1620
    student       3288866           25ms       7729
    academic      3294822           26ms       1772
    excluding     3296589           15ms       4
    information   3296420           26ms       171
    interruption  3296589           27ms       1
    responsibilities  3296565       26ms       21

    TOTAL SHIFTS = 29956347
    TOTAL TIME = 251ms
  
  - Horspool
    PATTERN       # OF SHIFTS       TIME
    to            1692492           24ms
    the           1113682           19ms
    this          887188            13ms
    course        613134            9ms
    student       557738            8ms
    academic      494013            6ms
    excluding     440869            5ms
    information   390931            6ms
    interruption  360158            7ms
    responsibilities 287587         3ms

    TOTAL SHIFTS = 6860073
    TOTAL TIME = 100ms

    SHIFT RATIO (horspool / brute) = 6860073 shifts / 29956347 shifts = 0.23
    TIME RATIO (horspool / brute) = 100ms / 251ms = 0.40

    Based on this information, we can say that the brute force approach always usually has the same number of shifts no matter the length of the pattern as well as the time for execution. 
    This matters because the number of shifts needed for a longer pattern length will slow down the algorithm.
    However, in the Horspool approach, we can see that the number of shifts decreases as the pattern length increases which also results in the time cutting down as well. This shows the efficiency 
    of Horspool being much more than the brute force approach. When looking at the ratios, we see that the Horspool algorithm takes 40% of the time that the brute force takes which means it is more efficient
    and takes 20% of the shifts as brute force which ties in as well. Along with this, the time complexity of the brute force algorithm on average is O(n^2) where n is the length of the pattern whereas for the horspool algorithm,
    it is O(n) on average but can become O(n*m) at its worst case.