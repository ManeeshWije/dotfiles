package ePortfolio;

/**
 * The class Stock holds all variables that correspond to a Stock object as well
 * as the getters/setters
 */
public class Stock extends Investment {
    double commission = 9.99;

    Stock() {
        symbol = "";
        name = "";
        quantity = 0;
        price = 0.00;
        bookValue = 0.00;
    }

    /**
     *
     * Sets the book value
     *
     * @param quantity the quantity
     * @param price    the price
     */
    @Override
    public void setBookValue(int quantity, double price) {
        bookValue = quantity * price + commission;
    }

    /**
     *
     * Gets the stock gain
     *
     * @return the stock gain
     */
    @Override
    public double getGains() {
        double gain = 0.00;
        gain = ((this.quantity * this.price - commission) - this.bookValue);
        return gain;
    }

}
