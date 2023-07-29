### NOTE: After reaching out to TA's and searching online about my package issue, I decided to not add a package statement at the top of each of my .java files. Doing it causes me many errors and also does not allow me to run my program. However, without having a package statement, my program runs flawlessly so please follow the instructions provided on how to compile and run my program before trying it your way

## 1) General problem
# The general problem I am trying to solve is making an easy to use ePortfolio which users can use in order to buy, sell, update, get gain, and search for their stocks and mutualfunds. This program makes it easy to keep track of your profits, losses and hopefully soon, will allow you to maximize profits.

## 2) Implementation
# To implement this, I created a Stock and MutualFund class which contains all of the variables and methods needed for each. For example, price, quantity, name, symbol, etc. Some assumptions I made for this are having distinct symbols across stocks and mutualfunds, a commission fee of $9 when buying and selling a stock, and a redemption fee of $45 when selling a mutualfund. 

## 3) How to Compile and Run
# To compile and run my program, you will enter the ePortfolio directory, run javac *.java to compile all files, then run java Main. The reason for this is noted in the NOTE above. I do believe normally, you have to go up a directory and run java ePortfolio.Main. This can only be done with a package statement.

## 4) Test Plan
## Main.java
# You can enter the commands buy, sell, etc case-insensitive or use the first letter EXCEPT for search which will be talked about more in 5). Wrong string inputs will reprompt the menu.

## Portfolio.java
# accounted for buying an already existing symbol so symbols are unique across all investments. Also accounted for choosing wrong input 0 or 1 for stock and mutualfund respectively. When selling, accounted for a valid symbol input. Also selling an investment to 0 will delete from list. Accounted for proper bookvalue and gain calculations in each command. When searching, accounted for all possible inputs and combinations except one which is given in more detail in 5). 

## 5)
# If I had more time to work on this assignment, I would first start of by fixing my search function. Currently, when using the searchKeyword function, the order in which the words are inputted matters. For example, TORONTO BANK and BANK TORONTO are two different keywords in my function. In the assignment PDF, it treats it as the same and this is where my problem occurs. I think going through the keyword string and checking if it includes each word one at a time would solve it. Obviously this method is very ineffiecnt as we would have to go though every single word by checking each split which is not ideal. I would also do more error checking than I already have. For example, I error check when asking for the first inputs but not there after. Also in my Main.java, since I use strings as input, you are able to use the word command or just the first letter. Since search and sell have the same first letter, it conflicts and had to remove the || for search. Another improvement I would do is overall make my Portfolio.java more clean as I have many conditions nested into eachother and would be more cleaner if I had made more methods. 

