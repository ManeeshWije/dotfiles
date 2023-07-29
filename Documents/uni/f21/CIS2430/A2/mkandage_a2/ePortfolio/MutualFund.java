package ePortfolio;

/**
 * The class Mutual fund contains all getters and setters as well as variables
 * associated with the mutualfund object
 */
public class MutualFund extends Investment {
    int redemption = 45;

    MutualFund() {
        symbol = "";
        name = "";
        quantity = 0;
        price = 0;
        bookValue = 0;
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
        this.bookValue = quantity * price;
    }

    /**
     *
     * To string outputs the variables associated with the object in a formatted way
     *
     * @return String
     */
    @Override
    public String toString() {

        return "Symbol: " + this.symbol + "\n" + "Name: " + this.name + "\n" + "Price: $" + this.price + "\n"
                + "Quantity: " + this.quantity + " units" + "\n" + "Book Value: $" + this.bookValue;
    }

    /**
     *
     * Gets the mutual gain
     *
     * @return the mutual gain
     */
    @Override
    public double getGains() {
        double gain = 0.00;
        gain = ((this.quantity * this.price - redemption) - this.bookValue);
        return gain;
    }
}
