package ePortfolio;

import java.util.*;
import java.io.*;

/**
 * The class Portfolio includes all investment commands
 */
public class Portfolio {
    HashMap<String, ArrayList<Integer>> map = new HashMap<String, ArrayList<Integer>>();
    ArrayList<Investment> investments = new ArrayList<Investment>();
    Scanner scan = new Scanner(System.in);

    // creating stock, mutualfund, and investment objects
    Stock s = new Stock();
    MutualFund m = new MutualFund();
    Investment i = new Investment();

    /**
     *
     * Read file parses the contents of file and adds the information to either a
     * stock or mutual fund object which goes into the investment list
     *
     * @param filename the filename
     */
    public void readFile(String filename) {

        int counter = 0;
        try {
            File f = new File(filename);
            Scanner inputFile = new Scanner(f);
            while (inputFile.hasNextLine()) {
                String read = inputFile.nextLine();
                // splitting on quotation marks
                String[] contents = read.split("\"");
                // set counter to 0 if no contents
                if (read.equals("")) {
                    counter = 0;
                } else if (!read.equals("")) {
                    // setting initial values
                    if (counter == 0) {
                        i.setType(contents[1]);
                    } else if (counter == 1) {
                        i.setSymbol(contents[1]);
                    } else if (counter == 2) {
                        i.setName(contents[1]);
                    } else if (counter == 3) {
                        i.setQuantity(Integer.parseInt(contents[1]));
                    } else if (counter == 4) {
                        i.setPrice(Double.parseDouble(contents[1]));
                    } else if (counter == 5) {
                        i.setRealBookValue(Double.parseDouble(contents[1]));
                    }
                    counter++;
                    // after setting, we can add to our investment
                    if (counter == 6) {
                        if (i.getType().equals("stock")) {
                            s.setType(i.getType());
                            s.setSymbol(i.getSymbol());
                            s.setName(i.getName());
                            s.setQuantity(i.getQuantity());
                            s.setPrice(i.getPrice());
                            s.setRealBookValue(i.getBookvalue());
                            investments.add(s);
                            hashBuy(s);
                            s = new Stock();
                        }
                        if (i.getType().equals("mutualfund")) {
                            m.setType(i.getType());
                            m.setSymbol(i.getSymbol());
                            m.setName(i.getName());
                            m.setQuantity(i.getQuantity());
                            m.setPrice(i.getPrice());
                            m.setRealBookValue(i.getBookvalue());
                            investments.add(m);
                            hashBuy(m);
                            m = new MutualFund();
                        }
                    }
                }
            }
            inputFile.close();
        } catch (Exception e) {
            System.out.println("Error: file not found");
        }
    }

    /**
     *
     * Output file goes through the investment lists and prints the objects into the
     * same text file used in arg[0]
     *
     * @param outputFile the output file
     */
    public void outputFile(String outputFile) {

        try {
            PrintWriter fileWriter = new PrintWriter(outputFile, "UTF-8");
            for (int i = 0; i < investments.size(); i++) {
                fileWriter.println(investments.get(i).printOutputFile());
            }
            fileWriter.close();
        } catch (Exception e) {
            System.out.println("Error: could not write to file");
        }
    }

    /**
     *
     * Buy allows you to own an investment or add into an existing one
     *
     */
    public void Buy() {
        System.out.println("What type of investment would you like to buy? Enter 0 for stock or 1 for mutualfund");
        int contents = scan.nextInt();
        scan.nextLine();
        while (contents != 0 && contents != 1) { // error checking for invalid contents
            System.out.println("Error: invalid contents");
            System.out.println("What type of investment would you like to buy? Enter 0 for stock or 1 for mutualfund");
            contents = scan.nextInt();
            scan.nextLine();
        }
        if (contents == 0) { // for stock
            s.setType("stock");
            System.out.println("Enter symbol of stock: ");
            String symbol = scan.nextLine();

            if (checkEqualsSymbol(symbol) == -1) { // making sure symbol doesnt exist already in stock list
                s.setSymbol(symbol); // using setters on user contents
                System.out.println("Enter name for stock:");
                String name = scan.nextLine();
                s.setName(name);
                System.out.println("Enter quantity:");
                int quantity = scan.nextInt();
                while (quantity <= 0) {
                    System.out.println("Error: invalid contents");
                    System.out.println("Enter quantity:");
                    quantity = scan.nextInt();
                }
                s.setQuantity(quantity);

                System.out.println("Enter price:");
                double price = scan.nextDouble();
                while (price <= 0) {
                    System.out.println("Error: invalid contents");
                    System.out.println("Enter price:");
                    price = scan.nextDouble();
                }
                s.setPrice(price);

                s.setBookValue(quantity, price);
                investments.add(s); // adding object into investment list
                hashBuy(s);
                s = new Stock();
            } else { // if first if-statement did not return -1, then it means symbol exists
                System.out.println("Symbol already exists, enter new quantity:");

                int index = checkEqualsSymbol(symbol); // getting index of symbol
                double oldBookValue = investments.get(index).getBookvalue(); // getting old bookvalue
                int quantity = scan.nextInt();

                while (quantity <= 0) {
                    System.out.println("Error: invalid contents");
                    System.out.println("Symbol already exists, enter new quantity:");
                    quantity = scan.nextInt();
                }

                investments.get(index).addQuantity(quantity); // adding quantity to original

                System.out.println("Enter new price:");
                double price = scan.nextDouble(); // setting new price

                while (price <= 0) {
                    System.out.println("Error: invalid contents");
                    System.out.println("Enter new price:");
                    price = scan.nextInt();
                }

                investments.get(index).setPrice(price);

                investments.get(index).setBookValue(quantity, price); // setting new bookvalue
                investments.get(index).updateBookValue(oldBookValue, investments.get(index).getBookvalue());
            }
        } else if (contents == 1) { // this means user wants to enter mutualfund
            m.setType("mutualfund");
            System.out.println("Enter symbol of mutual fund: ");
            String symbol = scan.nextLine();

            if (checkEqualsSymbol(symbol) == -1) { // checking if symbol exists in mutual fund list
                m.setSymbol(symbol); // using setters for user inputs
                System.out.println("Enter name for mutual fund:");
                String name = scan.nextLine();
                m.setName(name);

                System.out.println("Enter quantity:");
                int quantity = scan.nextInt();
                while (quantity <= 0) {
                    System.out.println("Error: invalid contents");
                    System.out.println("Enter quantity:");
                    quantity = scan.nextInt();
                }
                m.setQuantity(quantity);

                System.out.println("Enter price:");
                double price = scan.nextDouble();
                while (price <= 0) {
                    System.out.println("Error: invalid contents");
                    System.out.println("Enter price:");
                    price = scan.nextDouble();
                }
                m.setPrice(price);

                m.setBookValue(quantity, price);
                investments.add(m); // adding mutualfund to list
                hashBuy(m);
                m = new MutualFund();
            } else { // means symbol exists already
                int index = checkEqualsSymbol(symbol); // getting index of symbol

                System.out.println("Symbol already exists, enter new quantity:");

                double oldBookValue = investments.get(index).getBookvalue(); // getting old bookvalue

                int quantity = scan.nextInt();
                while (quantity <= 0) {
                    System.out.println("Error: invalid contents");
                    System.out.println("Symbol already exists, enter new quantity:");
                    quantity = scan.nextInt();
                }
                m.setQuantity(quantity);
                investments.get(index).addQuantity(quantity); // updating quantity

                System.out.println("Enter new price:"); // updating price
                double price = scan.nextDouble();
                while (price <= 0) {
                    System.out.println("Error: invalid contents");
                    System.out.println("Enter new price:");
                    price = scan.nextInt();
                }
                investments.get(index).setPrice(price);

                investments.get(index).setBookValue(quantity, price); // setting new bookvalue
                investments.get(index).updateBookValue(oldBookValue, investments.get(index).getBookvalue());
            }
        }
        // printing for testing
        printList();
        System.out.println(map);
    }

    /**
     *
     * Sell allows you to reduce quantity of an existing stock or fund
     *
     */
    public void Sell() {
        System.out.println("What type of investment would you like to sell? Enter 0 for stock or 1 for mutualfund");
        int contents = scan.nextInt();
        scan.nextLine();
        while (contents != 0 && contents != 1) { // error checking for wrong contents
            System.out.println("Error: invalid entry");
            System.out.println("What type of investment would you like to sell? Enter 0 for stock or 1 for mutualfund");
            contents = scan.nextInt();
            scan.nextLine();
        }
        if (contents == 0) { // selling stock
            System.out.println("Enter symbol of stock: ");
            String symbol = scan.nextLine();
            while (checkEqualsSymbol(symbol) == -1) { // error checking for symbol not being in list already
                System.out.println("Error: " + symbol + " does not exist");
                System.out.println("Enter symbol of stock: ");
                symbol = scan.nextLine();
            }
            int index = checkEqualsSymbol(symbol); // getting index of symbol
            int oldQuantity = investments.get(index).getQuantity(); // getting old values
            double oldBookValue = investments.get(index).getBookvalue();

            System.out.println("How many shares of " + symbol + " would you like to sell?");
            int quantity = scan.nextInt();
            while (quantity > oldQuantity) { // error checking for greater user quantity than real quantity
                System.out.println("Error: invalid quantity");
                System.out.println("How many shares of " + symbol + " would you like to sell?");
                quantity = scan.nextInt();
            }
            investments.get(index).sellQuantity(quantity); // subtracting quantity

            if (investments.get(index).getQuantity() == 0) { // after subtraction, if quantity is 0, delete the whole
                System.out.println("What price would you like to sell at?");
                double price = scan.nextDouble();
                while (price <= 0) {
                    System.out.println("Error: invalid contents");
                    System.out.println("What price would you like to sell at?");
                    price = scan.nextDouble();
                }
                investments.get(index).setPrice(price); // updating price
                investments.get(index).adjustBookValue(oldBookValue, oldQuantity, oldQuantity - quantity);
                double payment = quantity * price - 9.99; // calcualting payment recieved
                System.out.println("Payment received: $" + payment); // stock
                investments.remove(index);
                hashSell();
            } else {
                System.out.println("What price would you like to sell at?");
                double price = scan.nextDouble();
                while (price <= 0) {
                    System.out.println("Error: invalid contents");
                    System.out.println("What price would you like to sell at?");
                    price = scan.nextDouble();
                }
                investments.get(index).setPrice(price); // updating price
                investments.get(index).adjustBookValue(oldBookValue, oldQuantity, oldQuantity - quantity);
                double payment = quantity * price - 9.99; // calcualting payment recieved
                System.out.println("Payment received: $" + payment);
            }
        } else if (contents == 1) { // for mutualfund
            System.out.println("Enter symbol of mutualfund: ");
            String symbol = scan.nextLine();
            while (checkEqualsSymbol(symbol) == -1) { // error checking for if symbol does not exist
                System.out.println("Error: " + symbol + " does not exist");
                System.out.println("Enter symbol of mutualfund: ");
                symbol = scan.nextLine();
            }
            int index = checkEqualsSymbol(symbol); // getting index of symbol
            int oldQuantity = investments.get(index).getQuantity(); // getting old values
            double oldBookValue = investments.get(index).getBookvalue();

            System.out.println("How many shares of " + symbol + " would you like to sell?");
            int quantity = scan.nextInt();
            while (quantity > oldQuantity) { // error checking if entered quantity is greater than existing quantity
                System.out.println("Error: invalid quantity");
                System.out.println("How many shares of " + symbol + " would you like to sell?");
                quantity = scan.nextInt();
                scan.nextLine();
            }
            investments.get(index).sellQuantity(quantity); // updating quantity

            if (investments.get(index).getQuantity() == 0) { // if after update, quantity is 0, delete the fund
                System.out.println("What price would you like to sell at?");
                double price = scan.nextDouble();
                while (price <= 0) {
                    System.out.println("Error: invalid contents");
                    System.out.println("What price would you like to sell at?");
                    price = scan.nextDouble();
                }
                investments.get(index).setPrice(price); // setting new price
                investments.get(index).adjustBookValue(oldBookValue, oldQuantity, oldQuantity - quantity); // adjusting
                double payment = quantity * price - 45; // calculating payment recieved
                System.out.println("Payment recieved: " + payment);
                investments.remove(index);
                hashSell();
            } else {
                System.out.println("What price would you like to sell at?");
                double price = scan.nextDouble();
                while (price <= 0) {
                    System.out.println("Error: invalid contents");
                    System.out.println("What price would you like to sell at?");
                    price = scan.nextDouble();
                }
                investments.get(index).setPrice(price); // setting new price
                investments.get(index).adjustBookValue(oldBookValue, oldQuantity, oldQuantity - quantity); // adjusting
                double payment = quantity * price - 45; // calculating payment recieved
                System.out.println("Payment recieved: " + payment);
            }
        }
        printList(); // testing list
        System.out.println(map); // testing map
    }

    /**
     *
     * Update allows you to enter a new price for each existing stock or fund
     *
     */
    public void Update() {
        System.out.println("Updating price for investments...");
        // looping through stock list and asking for new price for each stock
        for (int i = 0; i < investments.size(); i++) {
            System.out.println("Enter updated price for " + investments.get(i).getSymbol());
            double price = scan.nextDouble();
            while (price <= 0) {
                System.out.println("Error: invalid contents");
                System.out.println("Enter updated price for " + investments.get(i).getSymbol());
                price = scan.nextDouble();
            }
            investments.get(i).setPrice(price);
        }
        // testing lists
        printList();
    }

    /**
     *
     * Gets the gain of all investments so far
     *
     */
    public void getGain() {
        double totalGain = 0.00;
        // double totalGainMutual = 0.00;
        System.out.println("Calculating total gain for investments...");
        for (int i = 0; i < investments.size(); i++) {
            totalGain += investments.get(i).getGains();
        }
        System.out.println("Total gain: $" + totalGain);
    }

    /**
     *
     * Search symbol searches for stock and mutualfund using user inputted symbol
     *
     * @param symbol the user entered symbol
     */
    public void searchSymbol(String symbol) {
        // searching investment list
        for (int i = 0; i < investments.size(); i++) {
            if (symbol.equalsIgnoreCase((investments.get(i).getSymbol()))) {
                System.out.println(investments.get(i).toString());
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
        ArrayList<Integer> values = new ArrayList<Integer>();
        String[] token = keyword.split("[ ]+");

        for (int i = 0; i < token.length; i++) {
            if (map.containsKey(token[i])) {
                values = map.get(token[i]);
                System.out.println("matching value from keyword in hashmap: " + values);
                System.out.println(investments.get(values.get(i)));
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

        for (int i = 0; i < investments.size(); i++) {
            if (investments.get(i).getPrice() <= max && investments.get(i).getPrice() >= min) {
                System.out.println(investments.get(i).toString());
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
        // searching through investments
        for (int i = 0; i < investments.size(); i++) {
            if (symbol.equalsIgnoreCase(investments.get(i).getSymbol())
                    && investments.get(i).getName().toLowerCase().contains(keyword)) {
                System.out.println(investments.get(i).toString());
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

        // searching through investments
        for (int i = 0; i < investments.size(); i++) {
            if (symbol.equalsIgnoreCase(investments.get(i).getSymbol()) && investments.get(i).getPrice() <= max
                    && investments.get(i).getPrice() >= min) {
                System.out.println(investments.get(i).toString());
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

        // searching through investments
        for (int i = 0; i < investments.size(); i++) {
            if (investments.get(i).getName().toLowerCase().contains(keyword) && investments.get(i).getPrice() <= max
                    && investments.get(i).getPrice() >= min) {
                System.out.println(investments.get(i).toString());
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

        // searching through investments
        for (int i = 0; i < investments.size(); i++) {
            if (symbol.equalsIgnoreCase(investments.get(i).getSymbol())
                    && investments.get(i).getName().toLowerCase().contains(keyword)
                    && investments.get(i).getPrice() <= max && investments.get(i).getPrice() >= min) {
                System.out.println(investments.get(i).toString());
            }
        }
    }

    /**
     *
     * Search none searches through both stocks and mutualfunds based on no user
     * contents
     *
     */
    public void searchNone() {

        // searching through investments
        for (int i = 0; i < investments.size(); i++) {
            System.out.println(investments.get(i).toString());
        }
    }

    /**
     *
     * Print list prints the investment array list
     *
     */
    public void printList() {

        for (int j = 0; j < investments.size(); j++) {
            System.out.println(investments.get(j).toString());
            System.out.println("\n");
        }
    }

    /**
     *
     * Check equals symbol for investments
     *
     * @param symbol the user entered symbol
     * @return int
     */
    public int checkEqualsSymbol(String symbol) {

        for (int i = 0; i < investments.size(); i++) {
            if (investments.get(i).getSymbol().equals(symbol)) {
                return i;
            }
        }
        return -1;
    }

    /**
     *
     * Hash buy checks if a word is in the map or not and either adds it to the map
     * or updates the index of an existing key
     *
     * @param i which is the investment object and is used to getName()
     */
    public void hashBuy(Investment i) {

        String[] token = i.getName().split("[ ]+");
        ArrayList<Integer> values = new ArrayList<Integer>();
        for (int j = 0; j < token.length; j++) {
            // word is a key in map
            if (map.containsKey(token[j])) {
                // get the value pointed to by key
                values = map.get(token[j]);
                // adding last investment added
                values.add(investments.size() - 1);
                // replacing
                map.replace(token[j].toLowerCase(), values);
                values = new ArrayList<Integer>();
            } else { // new entry
                values.add(investments.size() - 1);
                map.put(token[j].toLowerCase(), values);
                values = new ArrayList<Integer>();
            }
        }
    }

    /**
     *
     * Hash sell clears the map and redos using the hash buy function. This is used
     * for when deleting an investment from the list
     *
     */
    public void hashSell() {

        // empty the map
        map.clear();
        // get, parse, and add names to hashmap
        for (int j = 0; j < investments.size(); j++) {
            hashBuy(i);
        }
    }
}