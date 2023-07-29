package ePortfolio;

import java.util.*;

/**
 * The class Portfolio includes all investment commands
 */
public class Portfolio {
    ArrayList<Stock> stock = new ArrayList<Stock>();
    ArrayList<MutualFund> mutualFund = new ArrayList<MutualFund>();
    Scanner scan = new Scanner(System.in);

    // creating stock and mutual fund objects
    Stock s = new Stock();
    MutualFund m = new MutualFund();

    /**
     *
     * Buy allows you to own an investment or add into an existing one
     *
     */
    public void Buy() {

        System.out.println("What type of investment would you like to buy? Enter 0 for stock or 1 for mutualfund");
        int input = scan.nextInt();
        scan.nextLine();
        while (input != 0 && input != 1) { // error checking for invalid input
            System.out.println("Error: invalid input");
            System.out.println("What type of investment would you like to buy? Enter 0 for stock or 1 for mutualfund");
            input = scan.nextInt();
            scan.nextLine();
        }
        if (input == 0) { // for stock

            System.out.println("Enter symbol of stock: ");
            String symbol = scan.nextLine();

            // checking if symbol already exists in other investment
            for (int i = 0; i < mutualFund.size(); i++) {
                if (symbol.equalsIgnoreCase(mutualFund.get(i).getSymbol())) {
                    System.out.println("Error: symbol exists in mutualfunds");
                    return;
                }
            }

            if (checkEqualsSymbolStock(symbol) == -1) { // making sure symbol doesnt exist already in stock list
                s.setSymbol(symbol); // using setters on user input
                System.out.println("Enter name for stock:");
                String name = scan.nextLine();
                s.setName(name);
                System.out.println("Enter quantity:");
                int quantity = scan.nextInt();
                s.setQuantity(quantity);

                System.out.println("Enter price:");
                double price = scan.nextDouble();
                s.setPrice(price);

                s.setBookValue(quantity, price);
                stock.add(s); // adding object into stock list
                s = new Stock();
            } else { // if first if-statement did not return -1, then it means symbol exists
                System.out.println("Symbol already exists, enter new quantity:");

                int index = checkEqualsSymbolStock(symbol); // getting index of symbol
                double oldBookValue = stock.get(index).getBookvalue(); // getting old bookvalue

                int quantity = scan.nextInt();

                stock.get(index).addQuantity(quantity); // adding quantity to original

                System.out.println("Enter new price:");
                double price = scan.nextDouble(); // setting new price
                stock.get(index).setPrice(price);

                stock.get(index).setBookValue(quantity, price); // setting new bookvalue
                stock.get(index).updateBookValue(oldBookValue, stock.get(index).getBookvalue()); // adding old bookvalue
                                                                                                 // to new
                                                                                                 // one
            }
        } else if (input == 1) { // this means user wants to enter mutualfund
            System.out.println("Enter symbol of mutual fund: ");
            String symbol = scan.nextLine();

            // checking if symbol already exists in other investment
            for (int i = 0; i < stock.size(); i++) {
                if (symbol.equalsIgnoreCase(stock.get(i).getSymbol())) {
                    System.out.println("Error: symbol exists in stocks");
                    return;
                }
            }

            if (checkEqualsSymbolMutual(symbol) == -1) { // checking if symbol exists in mutual fund list
                m.setSymbol(symbol); // using setters for user inputs
                System.out.println("Enter name for mutual fund:");
                String name = scan.nextLine();
                m.setName(name);

                System.out.println("Enter quantity:");
                int quantity = scan.nextInt();
                m.setQuantity(quantity);

                System.out.println("Enter price:");
                double price = scan.nextDouble();
                m.setPrice(price);

                m.setBookValue(quantity, price);
                mutualFund.add(m); // adding mutualfund to list
                m = new MutualFund();

            } else { // means symbol exists already
                int index = checkEqualsSymbolMutual(symbol); // getting index of symbol

                System.out.println("Symbol alread exists, enter new quantity:");
                int quantity = scan.nextInt();
                m.setQuantity(quantity);
                mutualFund.get(index).addQuantity(quantity); // updating quantity

                System.out.println("Enter new price:"); // updating price
                double price = scan.nextDouble();
                mutualFund.get(index).setPrice(price);

                mutualFund.get(index).setBookValue(quantity, price); // setting new bookvalue

            }
        }
        // printing for testing
        printListStock();
        printListMutual();
    }

    /**
     *
     * Sell allows you to reduce quantity of an existing stock or fund
     *
     */
    public void Sell() {

        System.out.println("What type of investment would you like to sell? Enter 0 for stock or 1 for mutualfund");
        int input = scan.nextInt();
        scan.nextLine();
        while (input != 0 && input != 1) { // error checking for wrong input
            System.out.println("Error: invalid entry");
            System.out.println("What type of investment would you like to sell? Enter 0 for stock or 1 for mutualfund");
            input = scan.nextInt();
            scan.nextLine();
        }
        if (input == 0) { // selling stock
            System.out.println("Enter symbol of stock: ");
            String symbol = scan.nextLine();
            while (checkEqualsSymbolStock(symbol) == -1) { // error checking for symbol not being in list already
                System.out.println("Error: " + symbol + " does not exist");
                System.out.println("Enter symbol of stock: ");
                symbol = scan.nextLine();
            }
            int index = checkEqualsSymbolStock(symbol); // getting index of symbol
            int oldQuantity = stock.get(index).getQuantity(); // getting old values
            double oldBookValue = stock.get(index).getBookvalue();

            System.out.println("How many shares of " + symbol + " would you like to sell?");
            int quantity = scan.nextInt();
            while (quantity > oldQuantity) { // error checking for greater user quantity than real quantity
                System.out.println("Error: invalid quantity");
                System.out.println("How many shares of " + symbol + " would you like to sell?");
                quantity = scan.nextInt();
            }
            stock.get(index).sellQuantity(quantity); // subtracting quantity

            if (stock.get(index).getQuantity() == 0) { // after subtraction, if quantity is 0, delete the whole stock
                stock.remove(index);
            } else {
                System.out.println("What price would you like to sell at?");
                double price = scan.nextDouble();
                stock.get(index).setPrice(price); // updating price
                stock.get(index).adjustBookValue(oldBookValue, oldQuantity, oldQuantity - quantity); // adjusting
                                                                                                     // bookvalue
                                                                                                     // based on
                                                                                                     // quantity
                double payment = quantity * price - 9.99; // calcualting payment recieved
                System.out.println("Payment received: $" + payment);
            }
            printListStock(); // testing list
        } else if (input == 1) { // for mutualfund
            System.out.println("Enter symbol of mutualfund: ");
            String symbol = scan.nextLine();
            while (checkEqualsSymbolMutual(symbol) == -1) { // error checking for if symbol does not exist
                System.out.println("Error: " + symbol + " does not exist");
                System.out.println("Enter symbol of mutualfund: ");
                symbol = scan.nextLine();
            }
            int index = checkEqualsSymbolMutual(symbol); // getting index of symbol
            int oldQuantity = mutualFund.get(index).getQuantity(); // getting old values
            double oldBookValue = mutualFund.get(index).getBookvalue();

            System.out.println("How many shares of " + symbol + " would you like to sell?");
            int quantity = scan.nextInt();
            while (quantity > oldQuantity) { // error checking if entered quantity is greater than existing quantity
                System.out.println("Error: invalid quantity");
                System.out.println("How many shares of " + symbol + " would you like to sell?");
                quantity = scan.nextInt();
                scan.nextLine();
            }
            mutualFund.get(index).sellQuantity(quantity); // updating quantity

            if (mutualFund.get(index).getQuantity() == 0) { // if after update, quantity is 0, delete the fund
                mutualFund.remove(index);
            } else {
                System.out.println("What price would you like to sell at?");
                double price = scan.nextDouble();
                mutualFund.get(index).setPrice(price); // setting new price
                mutualFund.get(index).adjustBookValue(oldBookValue, oldQuantity, oldQuantity - quantity); // adjusting
                                                                                                          // bookvalue
                                                                                                          // based on
                                                                                                          // quantity
                double payment = quantity * price - 45; // calculating payment recieved
                System.out.println("Payment recieved: " + payment);
            }
            printListMutual(); // testing list
        }
    }

    /**
     *
     * Update allows you to enter a new price for each existing stock or fund
     *
     */
    public void Update() {

        System.out.println("Updating price for stocks...");
        // looping through stock list and asking for new price for each stock
        for (int i = 0; i < stock.size(); i++) {
            System.out.println("Enter updated price for " + stock.get(i).getSymbol());
            double price = scan.nextDouble();
            stock.get(i).setPrice(price);
        }

        System.out.println("Updating price for mutualfunds...");
        // same as stock
        for (int i = 0; i < mutualFund.size(); i++) {
            System.out.println("Enter updated price for " + mutualFund.get(i).getSymbol());
            double price = scan.nextDouble();
            mutualFund.get(i).setPrice(price);
        }

        // testing lists
        printListStock();
        printListMutual();
    }

    /**
     *
     * Gets the gain of all investments so far
     *
     */
    public void getGain() {

        double totalGainStock = 0.00;
        double totalGainMutual = 0.00;
        System.out.println("Calculating total gain for stocks...");
        for (int i = 0; i < stock.size(); i++) {
            totalGainStock += stock.get(i).getStockGain();
        }
        System.out.println("Calculating total gain for mutualfunds...");
        for (int i = 0; i < mutualFund.size(); i++) {
            totalGainMutual += mutualFund.get(i).getMutualGain();
        }
        double masterTotal = totalGainStock + totalGainMutual;
        System.out.println("Total gain: $" + masterTotal);
    }

    /**
     *
     * Search symbol searches for stock and mutualfund using user inputted symbol
     *
     * @param symbol the user entered symbol
     */
    public void searchSymbol(String symbol) {

        // searching stock list
        for (int i = 0; i < stock.size(); i++) {
            if (symbol.equals(stock.get(i).getSymbol())) {
                System.out.println(stock.get(i).toString());
            }
        }
        // searching mutualfunds
        for (int i = 0; i < mutualFund.size(); i++) {
            if (symbol.equals(mutualFund.get(i).getSymbol())) {
                System.out.println(mutualFund.get(i).toString());
            }
        }
    }

    /**
     *
     * Search keyword searches for stock and mutualfund that contains user inputted
     * keyword
     *
     * @param keyword the keyword
     */
    public void searchKeyword(String keyword) {

        // searching through stocks
        for (int i = 0; i < stock.size(); i++) {
            if (stock.get(i).getName().toLowerCase().contains(keyword)) {
                System.out.println(stock.get(i).toString());
            }
        }
        // searching through mutualfunds
        for (int i = 0; i < mutualFund.size(); i++) {
            if (mutualFund.get(i).getName().toLowerCase().contains(keyword)) {
                System.out.println(mutualFund.get(i).toString());
            }
        }
    }

    /**
     *
     * Search price searches through stock and mutualfund for a given minimum and
     * maximum price value
     *
     * @param min the min
     * @param max the max
     */
    public void searchPrice(double min, double max) {

        for (int i = 0; i < stock.size(); i++) {
            if (stock.get(i).getPrice() <= max && stock.get(i).getPrice() >= min) {
                System.out.println(stock.get(i).toString());
            }
        }
        // compare all mutual funds
        for (int i = 0; i < mutualFund.size(); i++) {
            if (mutualFund.get(i).getPrice() <= max && mutualFund.get(i).getPrice() >= min) {
                System.out.println(mutualFund.get(i).toString());
            }
        }
    }

    /**
     *
     * Search symbol and keyword
     *
     * @param symbol  the symbol
     * @param keyword the keyword
     */
    public void searchSymbolAndKeyword(String symbol, String keyword) {

        // searching through stocks
        for (int i = 0; i < stock.size(); i++) {
            if (symbol.equals(stock.get(i).getSymbol()) && stock.get(i).getName().toLowerCase().contains(keyword)) {
                System.out.println(stock.get(i).toString());
            }
        }
        // searching through mutualfunds
        for (int i = 0; i < mutualFund.size(); i++) {
            if (symbol.equals(mutualFund.get(i).getSymbol())
                    && mutualFund.get(i).getName().toLowerCase().contains(keyword)) {
                System.out.println(mutualFund.get(i).toString());
            }
        }
    }

    /**
     *
     * Search symbol and price
     *
     * @param symbol the symbol entered by user
     * @param min    the minimum price that user wants
     * @param max    the maximum price that the user wants
     */
    public void searchSymbolAndPrice(String symbol, double min, double max) {

        // searching through stocks
        for (int i = 0; i < stock.size(); i++) {
            if (symbol.equals(stock.get(i).getSymbol()) && stock.get(i).getPrice() <= max
                    && stock.get(i).getPrice() >= min) {
                System.out.println(stock.get(i).toString());
            }
        }
        // searching through mutualfunds
        for (int i = 0; i < mutualFund.size(); i++) {
            if (symbol.equals(mutualFund.get(i).getSymbol()) && mutualFund.get(i).getPrice() <= max
                    && mutualFund.get(i).getPrice() >= min) {
                System.out.println(mutualFund.get(i).toString());
            }
        }
    }

    /**
     *
     * Search keyword and price
     *
     * @param keyword the keyword that user inputs
     * @param min     the minimum value for price that the user wants
     * @param max     the maximum value for price that the user wants
     */
    public void searchKeywordAndPrice(String keyword, double min, double max) {

        // searching through stocks
        for (int i = 0; i < stock.size(); i++) {
            if (stock.get(i).getName().toLowerCase().contains(keyword) && stock.get(i).getPrice() <= max
                    && stock.get(i).getPrice() >= min) {
                System.out.println(stock.get(i).toString());
            }
        }
        // searching through mutualfunds
        for (int i = 0; i < mutualFund.size(); i++) {
            if (mutualFund.get(i).getName().toLowerCase().contains(keyword) && mutualFund.get(i).getPrice() <= max
                    && mutualFund.get(i).getPrice() >= min) {
                System.out.println(mutualFund.get(i).toString());
            }
        }
    }

    /**
     *
     * Search all
     *
     * @param symbol  the symbol that the user inputs to search from
     * @param keyword the keyword that the user inputs to search from
     * @param min     the minimum price that the user wants to search from
     * @param max     the maximum price that the user wants to search from
     */
    public void searchAll(String symbol, String keyword, double min, double max) {

        // searching through stocks
        for (int i = 0; i < stock.size(); i++) {
            if (symbol.equals(stock.get(i).getSymbol()) && stock.get(i).getName().toLowerCase().contains(keyword)
                    && stock.get(i).getPrice() <= max && stock.get(i).getPrice() >= min) {
                System.out.println(stock.get(i).toString());
            }
        }
        // searching through mutualfunds
        for (int i = 0; i < mutualFund.size(); i++) {
            if (symbol.equals(stock.get(i).getSymbol()) && mutualFund.get(i).getName().toLowerCase().contains(keyword)
                    && mutualFund.get(i).getPrice() <= max && mutualFund.get(i).getPrice() >= min) {
                System.out.println(mutualFund.get(i).toString());
            }
        }
    }

    /**
     *
     * Search none searches through both stocks and mutualfunds based on no user
     * input
     *
     */
    public void searchNone() {

        // searching through stocks
        for (int i = 0; i < stock.size(); i++) {
            System.out.println(stock.get(i).toString());
        }
        // searching through mutualfunds
        for (int i = 0; i < mutualFund.size(); i++) {
            System.out.println(mutualFund.get(i).toString());
        }
    }

    /**
     *
     * Print list stock prints the stock arraylist
     *
     */
    public void printListStock() {
        System.out.println(stock.toString());
    }

    /**
     *
     * printListMutual prints the mutalfund arraylist
     *
     */
    public void printListMutual() {
        System.out.println(mutualFund.toString());
    }

    /**
     *
     * Check equals symbol for stocks
     *
     * @param symbol the user entered symbol
     * @return int
     */
    public int checkEqualsSymbolStock(String symbol) {

        for (int i = 0; i < stock.size(); i++) {
            if (stock.get(i).getSymbol().equals(symbol)) {
                return i;
            }
        }
        return -1;
    }

    /**
     *
     * Check equals symbol for mutual funds
     *
     * @param symbol the user entered symbol
     * @return int
     */
    public int checkEqualsSymbolMutual(String symbol) {

        for (int i = 0; i < mutualFund.size(); i++) {
            if (mutualFund.get(i).getSymbol().equals(symbol)) {
                return i;
            }
        }
        return -1;
    }

    /**
     *
     * Check two symbols in both arraylists
     *
     * @param symbol the user entered symbol
     */
    public void checkTwoSymbols(String symbol) {

        for (int i = 0; i < stock.size(); i++) {
            if (stock.get(i).getSymbol().equals(mutualFund.get(i).getSymbol())) {
                System.out.println("Error: symbol already exists");
            }
        }
    }
}
