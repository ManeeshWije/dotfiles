## 1) General problem

# The general problem I am trying to solve is making an easy to use ePortfolio which users can use in order to buy, sell, update, get gain, and search for their stocks and mutualfunds. This program makes it easy to keep track of your profits, losses and hopefully soon, will allow you to maximize profits. In this iteration of the problem, I will also be attempting to implement a hashmap in order to search for investments more efficiently as well as clean up the code by using 1 arraylist instead of 2.

## 2) Implementation

# To implement this, I have created an investment super class in which stocks and mutualfunds can go into. These subclasses inherit common methods such as getters and setters but override important methods that differ such as getgain and toString. An investment can be of either type stock or type mutualfund and contains a price, quantity, symbol as other attributes. A stock has a commission fee of $9.99 when buying and selling as well as a redemption fee of $45 when selling a mutualfund. I have also made sure to add to my hashmap everytime a user buys a new investment and delete from my map everytime the user sells all of the quantity available.

## 3) How to Compile and Run

# To compile and run my program, you will enter the ePortfolio directory, run javac \*.java to compile all files, go up one directory with cd .. and then then run java ePortfolio.Main <filename.txt>. Failure to enter a filename as a command line argument will result in an error message with the steps to correctly run the program. NOTE: filename MUST be inside the mkandage directory and not inside the ePortfolio directory

## 4) TEST PLAN

# Test case 1: Buy

    - Enter an invalid entry when asked for stock or mutualfund
    Example:
    Input: 4
    Output: "Error: invalid contents" will prompt again to enter correct input
    - Add a symbol that already exists
    Example:
    Input: Inputs a symbol name that's already taken
    Output: "Symbol already exists, enter new quantity"
    - Adding an invalid quantity
    Example:
    Input: After entering a name for the stock or mutualfund, enter a negative or value of 0
    Output: "Error, invalid quantity" it will prompt again
    - Adding an invalid price
    Example:
    Input: After entering a quantity, enter a price of 0 or negative value
    Output: "Error, invalid contents" it will prompt again
    - Adding a new stock
    Example:
    Input: b or buy, 0, MANEESh, maneesh, 40, 20
    Output: (Along with the stocks/mutualfunds loaded in), Symbol: MANEESH, Name: maneesh, Price: $20.0, Quantity: 40 shares, Book Value: $809.99
    - Adding a new mutualfund
    Example:
    Input: Same as above
    Output: Same as above except Quantity: 40 units and BookValue: $800.0

# Test case 2: Sell

    - Same error checking as Buy() for invalid prices and quantities
    - Selling an investment that does not exist
    Example:
    Input: After selecting 0 for stock, sell TORONTO
    Output: "Error: TORONTO does not exist"
    - Selling more of an investment that currently held
    Example:
    Input: After loading investments from file, sell 501 of AAPL
    Output: "Error: invalid quantity"
    - Sell all of an investment
    Example:
    Input: After loading investments from file, sell 500 of AAPl at any price. Then Buy any stock of your choosing in order to print list at the end
    Output: You will see the first investment you sold fully is now removed from the investment list
    - Calculating payment received
    Example:
    Input: After loading investments from file, choose sell, 0, AAPL, 200, 99
    Output: "Payment received: $19790.01

# Test case 3: getGain

    - Updating all prices to 200 and then calculating getGain
    Example:
    Input: After loading investments file, choose u for update, enter 200 for AAPL, enter 200 for SSETX, then choose g to getGain
    Output: Total gain: $110928.02

# Test case 4: fileInput

    - if file does not exist
    Example:
    Input: java ePortfolio.Main wronginput.txt
    Output: program will resume normally
    - if file exists
    Example:
    Input: java ePortfolio.Main input.txt
    Output: program will print 2 investments. First will be AAPL, Apple Inc., $142.23, 500 shares, $55049.99. Second will be SSETX, BNY Mellon Growth Fund Class I, $42.21, 450 units, $23967.0

# Test case 5: fileOutput

    - when file did not exist from the start
    Example:
    Input: java ePortfolio.Main wronginput.txt. Then choose b, 0, AAPL, apple, 50, 20. then choose q to quit
    Output: Should generate an output file called wronginput.txt which contains Type = "stock",Symbol = "AAPL", Name = "apple", Quantity = "50" Price = "20.0", BookValue = "1009.99".
    - when file exists from the start
    Example:
    Input: java ePortfolio.Main input.txt, Then choose b, 0, MANEESH, maneesh, 50, 20. then choose q to quit
    Output: Should overwrite existing input.txt file except appending Type = "stock", Symbol = "MANEESH", Name = "maneesh", Quantity = "50", Price = "20.0", BookValue = "1009.99".

# Test case 6: search (only could get done one keyword search using hashmap)

    - no symbol with one keyword and no range
    Example:
    Input: After loading investments from file, choose "" for symbol, mellon for keyword, and "" for range
    Output: "matching value from keyword in hashmap: [1]. Symbol: SSETX, Name: BNY Mellon Growth Fund Class I, Price: $42.21, Quantity: 450 units, Book Value: $23967.0

## 5)

# If I had more time to work on this assignment, I would try implementing my search fully with the hashmap I created. I did not properly understand how to search through the hashmap and pull relevant information so I had to fall back on how I did my search in A1 with its limited functionality. For now, I had done the searchkeyword() with one keyword fine however did not understand how to implement it further than that. Other than that, I would have also made my Portfolio code a bit cleaner by using methods that error check for me instead of error checking inside each method separately. This resulted in a lot of repetition of code that could have been reduced with a method. For example checking if quantity and price inputs are valid was being checked using a while loop when instead it could have been checked using a method.
