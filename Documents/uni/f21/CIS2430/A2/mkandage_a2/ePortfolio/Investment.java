package ePortfolio;

/**
 * The class Investment holds all common getters and setters among a stock or
 * mutualfund as well as common variables
 */
public class Investment {
    protected String type;
    protected String symbol;
    protected String name;
    protected int quantity;
    protected double price;
    protected double bookValue;

    /**
     *
     * Sets the type whether that be stock or mutual fund
     *
     * @param type the type
     */
    public void setType(String type) {

        this.type = type;
    }

    /**
     *
     * Gets the type of investment
     *
     * @return the type
     */
    public String getType() {

        return this.type;
    }

    /**
     *
     * Sets the symbol
     *
     * @param symbol the symbol
     */
    public void setSymbol(String symbol) {

        this.symbol = symbol;
    }

    /**
     *
     * Sets the name
     *
     * @param name the name
     */
    public void setName(String name) {

        this.name = name;
    }

    /**
     *
     * Sets the quantity
     *
     * @param quantity the quantity
     */
    public void setQuantity(int quantity) {

        this.quantity = quantity;
    }

    /**
     *
     * Sets the price
     *
     * @param price the price
     */
    public void setPrice(double price) {

        this.price = price;
    }

    /**
     *
     * Gets the symbol
     *
     * @return the symbol
     */
    public String getSymbol() {

        return this.symbol;
    }

    /**
     *
     * Gets the name
     *
     * @return the name
     */
    public String getName() {

        return this.name;
    }

    /**
     *
     * Gets the quantity
     *
     * @return the quantity
     */
    public int getQuantity() {

        return this.quantity;
    }

    /**
     *
     * Gets the price
     *
     * @return the price
     */
    public double getPrice() {

        return this.price;
    }

    /**
     *
     * Gets the bookvalue
     *
     * @return the bookvalue
     */
    public double getBookvalue() {

        return this.bookValue;
    }

    /**
     *
     * Add quantity
     *
     * @param quantity the quantity to add
     */
    public void addQuantity(int quantity) {

        this.quantity += quantity;
    }

    /**
     *
     * Sets the book value
     *
     * @param quantity the quantity
     * @param price    the price
     */
    public void setBookValue(int quantity, double price) {

        bookValue = quantity * price;
    }

    /**
     *
     * Update book value
     *
     * @param oldBookValue the old book value
     * @param newBookValue the new book value
     */
    public void updateBookValue(double oldBookValue, double newBookValue) {

        bookValue = oldBookValue + newBookValue;
    }

    /**
     *
     * Sell quantity
     *
     * @param quantity the quantity to subtract
     */
    public void sellQuantity(int quantity) {

        this.quantity -= quantity;
    }

    /**
     *
     * Adjust book value
     *
     * @param oldBookValue the old book value
     * @param oldQuantity  the old quantity
     * @param newQuantity  the new quantity
     */
    public void adjustBookValue(double oldBookValue, int oldQuantity, int newQuantity) {

        bookValue = oldBookValue * ((double) newQuantity / (double) oldQuantity);
    }

    /**
     *
     * Sets the real book value
     *
     * @param bookValue the book value
     */
    public void setRealBookValue(double bookValue) {

        this.bookValue = bookValue;
    }

    /**
     *
     * Dummy method for stock and mutual fund gains
     *
     * @return the gain
     */
    public double getGains() {

        double gain = 0.00;
        gain = ((this.quantity * this.price) - this.bookValue);
        return gain;
    }

    /**
     *
     * Sell price
     *
     * @param price the price to subtract
     */
    public void sellPrice(double price) {

        this.price -= price;
    }

    /**
     *
     * To string returns the variables in a proper format
     *
     * @return String
     */
    public String toString() {

        return "Symbol: " + this.symbol + "\n" + "Name: " + this.name + "\n" + "Price: $" + this.price + "\n"
                + "Quantity: " + this.quantity + " shares" + "\n" + "Book Value: $" + this.bookValue;
    }

    /**
     *
     * Print output file
     *
     * @return String to be printed
     */
    public String printOutputFile() {

        return "type = " + '"' + this.type + '"' + "\n" + "symbol = " + '"' + this.symbol + '"' + "\n" + "name = " + '"'
                + this.name + '"' + "\n" + "quantity = " + '"' + this.quantity + '"' + "\n" + "price = " + '"'
                + this.price + '"' + "\n" + "bookValue = " + '"' + this.bookValue + '"' + "\n";
    }

}
