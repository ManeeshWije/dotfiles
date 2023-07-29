package ePortfolio;

import java.util.*;

/**
 * The class Main contains a Portfolio object which calls on those methods. It
 * also has userinputs for them along with a robust search parameter inputs
 */
public class Main {

    /**
     *
     * Main
     *
     * @param args the args
     */
    public static void main(String[] args) {

        Scanner scan = new Scanner(System.in);
        String choice = "";
        Portfolio p = new Portfolio();
        do {
            System.out.println("Choose an option\n\n");
            System.out.println("buy: own a new investment or add more quantity to an existing investment\n");
            System.out.println("sell: reduce some quantity of an existing investment\n");
            System.out.println("update: refresh the prices of all existing investments\n");
            System.out.println(
                    "getGain: compute the total gain of the portfolio by accumulating the gains of all individual investments\n");
            System.out.println(
                    "search: find all investments that match a search request and display all attributes of these investments\n");
            System.out.println("quit: quit the program or press enter\n");
            choice = scan.nextLine();
            if (choice.equalsIgnoreCase("buy") || choice.equalsIgnoreCase("b")) {
                p.Buy();
            }
            if (choice.equalsIgnoreCase("sell") || choice.equalsIgnoreCase("s")) {
                p.Sell();
            }
            if (choice.equalsIgnoreCase("update") || choice.equalsIgnoreCase("u")) {
                p.Update();
            }
            if (choice.equalsIgnoreCase("getgain") || choice.equalsIgnoreCase("gain") || choice.equalsIgnoreCase("g")) {
                p.getGain();
            }
            if (choice.equalsIgnoreCase("search")) {
                int input1 = 0;
                int input2 = 0;
                int input3 = 0; // conditions for search
                String symbol;
                String keyword;

                System.out.println("Enter the symbol for investment:");
                symbol = scan.nextLine();
                if (!symbol.equals("")) {
                    input1 = 1;
                }

                System.out.println("Enter the keyword:");
                keyword = scan.nextLine();
                if (!keyword.equals("")) {
                    input2 = 1;
                    keyword = keyword.toLowerCase();
                }

                double min = 0;
                double max = Double.POSITIVE_INFINITY;
                String temp;
                System.out.println("Enter search range, or leave blank to print all:");
                temp = scan.nextLine();
                if (!temp.equals("")) {
                    input3 = 1;
                    if (temp.contains("-")) { // 10-20 -10 20- 15
                        if (temp.charAt(0) == '-') {
                            temp = temp.replace("-", ""); // -20
                            min = 0;
                            max = Double.parseDouble(temp);
                        } else if (temp.charAt(temp.length() - 1) == '-') {
                            temp = temp.replace("-", ""); // 20-
                            min = Double.parseDouble(temp);
                            max = Double.POSITIVE_INFINITY;
                        } else {
                            String[] numbers = temp.split("-");
                            min = Double.parseDouble(numbers[0]);
                            max = Double.parseDouble(numbers[1]);
                        }
                    } else {
                        min = Double.parseDouble(temp);
                        max = Double.parseDouble(temp);
                    }
                }

                // comparing input values in order to call the correct method in
                // Portfolio
                if (input1 == 1 && input2 == 0 && input3 == 0) {
                    p.searchSymbol(symbol);
                } else if (input1 == 0 && input2 == 1 && input3 == 0) {
                    p.searchKeyword(keyword);
                } else if (input1 == 0 && input2 == 0 && input3 == 1) {
                    p.searchPrice(min, max);
                } else if (input1 == 1 && input2 == 1 && input3 == 0) {
                    p.searchSymbolAndKeyword(symbol, keyword);
                } else if (input1 == 1 && input2 == 0 && input3 == 1) {
                    p.searchSymbolAndPrice(symbol, min, max);
                } else if (input1 == 0 && input2 == 1 && input3 == 1) {
                    p.searchKeywordAndPrice(keyword, min, max);
                } else if (input1 == 1 && input2 == 1 && input3 == 1) {
                    p.searchAll(symbol, keyword, min, max);
                } else { // if empty input, print whole lists
                    p.searchNone();
                }
            }
            if (choice.equalsIgnoreCase("quit") || choice.equalsIgnoreCase("q")) {
                break;
            }
        } while (choice != "");
        scan.close();
    }
}
