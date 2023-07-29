package ePortfolio;

import java.util.*;

/**
 * The class Mutual fund contains all getters and setters as well as variables
 * associated with the mutualfund object
 */
public class MutualFund {
    private String symbol;
    private String name;
    private int quantity;
    private double price;
    private double bookValue;
    private int redemption = 45;

    MutualFund() {
        symbol = "";
        name = "";
        quantity = 0;
        price = 0;
        bookValue = 0;
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
     * Sets the book value
     *
     * @param quantity the quantity
     * @param price    the price
     */
    public void setBookValue(int quantity, double price) {

        this.bookValue += quantity * price;
    }

    /**
     *
     * Update book value is the same as setting but we subtract a redemption fee of
     * $45
     *
     * @param quantity the quantity
     * @param price    the price
     */
    public void updateBookValue(int quantity, double price) {

        this.bookValue += quantity * price - redemption;
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
     * To string outputs the variables associated with the object in a formatted way
     *
     * @return String
     */
    public String toString() {

        return "Symbol: " + this.symbol + "\n" + "Name: " + this.name + "\n" + "Price: $" + this.price + "\n"
                + "Quantity: " + this.quantity + " units" + "\n" + "Book Value: $" + this.bookValue;
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
     * Sell quantity
     *
     * @param quantity the quantity to subtract
     */
    public void sellQuantity(int quantity) {

        this.quantity -= quantity;
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
     * Gets the mutual gain
     *
     * @return the mutual gain
     */
    public double getMutualGain() {

        double gain = 0.00;
        gain = ((this.quantity * this.price - redemption) - this.bookValue);
        return gain;
    }
}
