## 1) General problem

# The general problem I am trying to solve is making an easy-to-use ePortfolio that users can use in order to buy, sell, update, get gain, and search for their stocks and mutualfunds. This program makes it easy to keep track of your profits, losses and hopefully soon, will allow you to maximize profits. In the second iteration of the problem, I will also be attempting to implement a hashmap in order to search for investments more efficiently as well as clean up the code by using 1 ArrayList instead of 2. In the last iteration of this problem, I will be implementing a GUI interface for this program in order to have ease of use and more functionality. This way, users can see their investments visually, and do all the actions necessary. These include buying, selling, updating, getting gain, and searching. Along with this, the finer details will be perfected which include proper overriding techniques, use of abstract methods/classes, polymorphism, exception handling, and privacy leak checking.

## 2) Implementation

# To implement this, I have created an investment superclass in which stocks and mutualfunds can go into. These subclasses inherit common methods such as getters and setters but override important methods that differ such as toString and equals. I used true overriding as well as used abstract classes and methods when necessary. For example, methods such as getGain are considered to be abstract in the abstract investment class but are well defined in their corresponding subclass. Along with this, An investment can be of either type stock or type mutualfund and contains a price, quantity, symbol as well as other attributes. A stock has a commission fee of $9.99 when buying and selling as well as a redemption fee of $45 when selling a mutualfund. Using Swing and Awt, I implemented a GUI interface for doing each of the menu options instead of using the terminal. I made different panels with parent panels to organize the interface. in order to switch between different interfaces, I simply manipulated setVisible() and renamed certain fields to match what was expected. To organize the layout of my GUI, I used a GridLayout for the parent and left panel but used FlowLayout for the right and output panel. I also made sure that there were no odd bugs that resulted from either setting visibility, making new buttons, or setting new text on a certain label. Apart from the GUI itself, I also implemented robust error checking meaning exceptions were thrown to their respective constructor when a text field was left blank for a necessary field, or when a certain value was expected such as > 0 for quantity and price. I also created a copy constructor to avoid any privacy leaks and made sure to effectively use polymorphism by using an investment ArrayList which contains both stocks and mutualfunds. This significantly reduced the redundancy of the code written by instead writing general code which can be used throughout. This also allowed me to not have to check the class type but instead use investments.get(i) in order to display the details for stocks and mutualfunds.

## 3) How to Compile and Run

# To compile and run my program, you will enter the ePortfolio directory, run javac \*.java to compile all files, go up one directory with cd .. and then run java ePortfolio.Main <filename.txt>. Failure to enter a filename as a command-line argument will result in an error message with the steps to correctly run the program. NOTE: filename MUST be inside the mkandage directory and not inside the ePortfolio directory

## 4) TEST PLAN

# Test case 1: Buying an Investment

    - Empty symbol when buying (either stock or mutualfund)
    Example:
    Input: Commands->Buy an Investment->Type: stock, Symbol: "", Name: maneesh, Quantity: 50, Price: 50->Buy
    Output: "Error: invalid inputs" and investment is not created

    - Negative or 0 value for quantity (either stock or mutualfund)
    Example:
    Input: Commands->Buy an Investment->Type: stock, Symbol: MANEESH, Name: maneesh, Quantity: -50, Price: 50->Buy
    Output: "Error: invalid inputs" and investment is not created

    - Negative or 0 value for price (either stock or mutualfund)
    Example:
    Input: Commands->Buy an Investment->Type: stock, Symbol: MANEESH, Name: maneesh, Quantity: 50, Price: -50->Buy
    Output: "Error: invalid inputs" and investment is not created

    - Add a symbol that already exists
    Example:
    Input: Inputs a symbol name that's already in the investments ArrayList
    Output: "Investment already exists, updating existing..." This will not create a new investment but just update the existing one with the values provided before hitting the Buy button

    - Populate text fields but want to clear all
    Example:
    Input: (Reset if needed) Commands->Buy->Type: stock, Symbol: MANEESH, Name: maneesh, Quantity: 50, Price: 50->Reset
    Output: all text fields, as well as output field, clears

    - Adding a new stock with correct values
    Example:
    Input: (Reset if needed) Commands->Buy->type: Stock, Symbol: MANEESH, Name: maneesh, Quantity: 50, Price: 50->Buy
    Output: (Along with the stocks/mutualfunds loaded in from file) Symbol: MANEESH, Name: maneesh, Price: $20.0, Quantity: 40 shares, Book Value: $809.99

    - Adding a new mutualfund with correct values
    Example:
    Input: (Reset if needed) Commands->Buy->Type: mutualfund, Symbol: GME, Name: GameStop, Quantity: 40, Price: 20->Buy
    Output: Symbol: GME, Name: GameStop, Price: $20.0, Quantity: 40 units, Book Value $800.0

# Test case 2: Selling an Investment

    - Empty symbol when selling
    Example:
    Input: Commands->Sell an Investment->Symbol: "", Quantity: 10, Price: 10->Sell
    Output: "Error: does not exist" and no investment quantity gets sold

    - Negative or 0 value for quantity
    Example:
    Input: Load investments from file containing AAPL or buy 500 AAPL at 142.23-> Commands->Sell an Investment->Symbol: "AAPL", Quantity: <= 0, Price: 10->Sell
    Output: "Error: invalid quantity" and no investment quantity gets sold

    - Negative or 0 value for price
    Example:
    Input: Load investments from file containing AAPL or buy 500 AAPL at 142.23-> Commands->Sell an Investment->Symbol: "AAPL", Quantity: 10, Price: <= 0->Sell
    Output: "Error: invalid price" and no investment quantity gets sold

    - Selling an investment that does not exist
    Example:
    Input: Commands->Sell an Investment->Symbol: "TORONTO", Quantity: 10, Price: 10->Sell
    Output: "Error: TORONTO does not exist"

    - Selling more of an investment that currently held
    Example:
    Input: Load investments from file containing AAPL or buy 500 AAPL at 142.23-> Commands->Sell an Investment->Symbol: "AAPL", Quantity: 501, Price: 10->Sell
    Output: "Error: invalid quantity"

    - Sell all of an investment
    Example:
    Input: Load investments from file containing AAPL or buy 500 AAPL at 142.23-> Commands->Sell an Investment->Symbol: "AAPL", Quantity: 500, Price: 10->Sell
    Output: "Payment Received: $4990.01, Investment has been removed" and after ending the program file does not contain AAPL

# Test case 3: Update Investments

    - Updating price for an investment loaded in or bought
    Example:
    Input: Load investments from file containing AAPL or buy 500 AAPL at 142.23-> Commands->Update Investments->Next or Prev until AAPL is shown->Price: 200->Save
    Output: "Symbol: AAPL, Name: Apple Inc., Price: $200.0, Quantity: 500 shares, Book Value: $55049.99"

    - Navigation buttons when moving through investments
    Example:
    Input: Load investments from file or buy investments->Click "Next" until last investment or click "Prev" until the first investment
    Output: "No more investments" and each respective button will disappear indicating the end

# Test case 4: Get Total Gain

    - Updating all prices to 200 and then calculating getGain
    Example:
    Input: Load investments from file or buy containing 500 AAPL @ 142.23 and 450 SSETX @ 42.21->Commands->Get Total Gain
    Output: Total gain: $110928.02 and individual gains: "AAPL: $44940.02, SSETX: $65988.0"

# Test case 5: Search Investments

    - Search symbol
    Example:
    Input: Load investments from file or buy containing 500 AAPL @ 142.23 and 450 SSETX @ 42.21->Commands->Search Investments->Symbol: AAPL, Name keywords: "", Low Price: "", High Price:""->Search
    Output: "Symbol: AAPL, Name: Apple Inc., Price: $142.32, Quantity: 500 shares, Book Value: $55049.99"

    - Search keyword
    Example:
    Input: Load investments from file or buy containing 500 AAPL (Apple Inc.) @ 142.23 and 450 SSETX (BNY Mellon Growth Fund Class I) @ 42.21->Commands->Search Investments->Symbol: "", Name keywords: "apple", Low Price: "", High Price:""->Search
    Output: "matching value from keyword in hashmap: [0]
    Symbol: AAPL, Name: Apple Inc., Price: $142.32, Quantity: 500 shares, Book Value: $55049.99"

    - Search price
    Example:
    Input: Load investments from file or buy containing 500 AAPL @ 142.23 and 450 SSETX @ 42.21->Commands->Search Investments->Symbol: "", Name keywords: "", Low Price: "100", High Price:"200"->Search
    Output: "Symbol: AAPL, Name: Apple Inc., Price: $142.32, Quantity: 500 shares, Book Value: $55049.99"

    - Search symbol and keyword
    Example:
    Input: Load investments from file or buy containing 500 AAPL @ 142.23 and 450 SSETX @ 42.21->Commands->Search Investments->Symbol: "SSETX", Name keywords: "Mellon", Low Price: "", High Price:""->Search
    Output: "Symbol: SSETX, Name: BNY Mellon Growth Fund Class I, Price: $42.21, Quantity: 450 units, Book Value: $23967.0"

    - Search symbol and price
    Example:
    Input: Load investments from file or buy containing 500 AAPL @ 142.23 and 450 SSETX @ 42.21->Commands->Search Investments->Symbol: "AAPL", Name keywords: "", Low Price: "100", High Price:"200"->Search
    Output: "Symbol: AAPL, Name: Apple Inc., Price: $142.32, Quantity: 500 shares, Book Value: $55049.99"

    - Search keyword and price
    Example:
    Input: Load investments from file or buy containing 500 AAPL @ 142.23 and 450 SSETX @ 42.21->Commands->Search Investments->Symbol: "", Name keywords: "Mellon", Low Price: "0", High Price:"50"->Search
    Output: "Symbol: SSETX, Name: BNY Mellon Growth Fund Class I, Price: $42.21, Quantity: 450 units, Book Value: $23967.0"

    - Search all
    Example:
    Input: Load investments from file or buy containing 500 AAPL @ 142.23 and 450 SSETX @ 42.21->Commands->Search Investments->Symbol: "SSETX", Name keywords: "bny", Low Price: "0", High Price:"50"->Search
    Output: "Symbol: SSETX, Name: BNY Mellon Growth Fund Class I, Price: $42.21, Quantity: 450 units, Book Value: $23967.0"

    - Search none
    Example:
    Input: Load investments from file or buy containing 500 AAPL @ 142.23 and 450 SSETX @ 42.21->Commands->Search Investments->Symbol: "", Name keywords: "", Low Price: "", High Price:""->Search
    Output: "Symbol: AAPL, Name: Apple Inc., Price: $142.32, Quantity: 500 shares, Book Value: $55049.99
    Symbol: SSETX, Name: BNY Mellon Growth Fund Class I, Price: $42.21, Quantity: 450 units, Book Value: $23967.0"

# Test case 6: fileInput

    - If no file given
    Example:
    Input: java ePortfolio.Main
    Output: "Error, no file entered in as command line arg. Please do java ePortfolio.Main input.txt"

    - If file is given
    Example:
    Input: java ePortfolio.Main input.txt
    Output: Program will read investments given in the format as A2 and the user can use commands on them. If the file is empty, the program will resume normally

# Test case 7: fileOutput

    - Empty file from the start
    Example:
    Input: java ePortfolio.Main input.txt->Commands->Buy an Investment->Type: stock, Symbol: AAPL, Name: Apple Inc., Quantity: 50, Price: 20->Buy->End Program (Output File)
    Output: Should generate an output file called input.txt which contains Type = "stock", Symbol = "AAPL", Name = "Apple Inc.", Quantity = "50" Price = "20.0", BookValue = "1009.99".

    - Populated file from the start
    Example:
    Input: java ePortfolio.Main input.txt->Commands->Buy an Investment->Type: stock, Symbol: MANEESH, Name: maneesh, Quantity: 50, Price: 20->Buy->End Program
    Output: Should overwrite existing input.txt file except appending Type = "stock", Symbol = "MANEESH", Name = "maneesh", Quantity = "50", Price = "20.0", BookValue = "1009.99".

## 5)

# If I had more time to do this assignment, I would try and fix my text fields to look more like the ones in the PDF. Currently, after using a GridLayout, my text boxes are at uniform length despite concretely changing the length of the field. This is due to using a GridLayout however changing to FlowLayout altered the design even more so I decided to stick with GridLayout. Another thing I would fix is the repetition in my code when it came to my ActionListeners. The way I handled this was by either creating new buttons for each panel and setting earlier ones to setVisible(false), renaming certain labels to match the pdf format, and etc. All of these actions did make the code repetitive and at times hard to debug as certain buttons or fields would disappear when switching from 1 menu to another. This forced me to review each individual button, label, and text field to make sure that they were being changed back to their original states after leaving a certain option. I feel as though there would have been a more elegant way to go about this by using anonymous action listeners of some sort. Lastly, if I were to fix all of those concerns, I would try to make the window responsive for different screen sizes.
