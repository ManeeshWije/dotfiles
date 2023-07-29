package ePortfolio;

import java.util.*;

/**
 * The class Stock holds all variables that correspond to a Stock object as well
 * as the getters/setters
 */
public class Stock {
    private String symbol;
    private String name;
    private int quantity;
    private double price;
    private double bookValue;
    private double commission = 9.99;

    Stock() {
        symbol = "";
        name = "";
        quantity = 0;
        price = 0.00;
        bookValue = 0.00;
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

        bookValue = quantity * price + commission;
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
     * Gets the bookvalue
     *
     * @return the bookvalue
     */
    public double getBookvalue() {

        return this.bookValue;
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
     * Gets the stock gain
     *
     * @return the stock gain
     */
    public double getStockGain() {

        double gain = 0.00;
        gain = ((this.quantity * this.price - commission) - this.bookValue);
        return gain;
    }

}
