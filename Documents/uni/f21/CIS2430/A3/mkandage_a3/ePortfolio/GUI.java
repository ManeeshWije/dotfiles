package ePortfolio;

import javax.swing.JFrame;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.PrintWriter;
import java.util.*;
import javax.swing.*;

/**
 * The class GUI extends JFrame implements action listener
 */
public class GUI extends JFrame implements ActionListener {
  // final values
  public static final int WIDTH = 650;
  public static final int HEIGHT = 700;
  public static final int STRLENGTH = 10;
  public static final int LINES = 8;
  public static final int CHARS_PER_LINE = 50;

  // helper variables
  int counter = 0;
  int j;
  String temp = "";

  HashMap<String, ArrayList<Integer>> map = new HashMap<String, ArrayList<Integer>>();
  ArrayList<Investment> investments = new ArrayList<Investment>();
  // creating stock and mutualfund
  Stock s = new Stock();
  MutualFund m = new MutualFund();

  // initializing needed panels, labels, etc
  private JTextArea outputText;
  private JComboBox<String> invType;
  private JLabel invTypeLabel;
  private JLabel welcome;
  private JLabel welcomeDescription;
  private JLabel symbolLabel;
  private JLabel nameLabel;
  private JLabel quantityLabel;
  private JLabel priceLabel;
  private JLabel outputLabel;
  private JPanel outputPanel;
  private JPanel welcomePanel;
  private JPanel leftPanel;
  private JTextField symbolTextField;
  private JTextField nameTextField;
  private JTextField quantityTextField;
  private JTextField priceTextField;
  private JButton buyBtn;
  private JButton resetBtn;
  private JButton prevBtn;
  private JButton sellBtn;
  private JButton nextBtn;
  private JButton saveBtn;
  private JButton searchBtn;
  private JPanel rightPanel;
  private JPanel upperPanel;

  /**
   *
   * GUI initializes main frame
   *
   * 
   */
  public GUI() {

    super();
    options();
    setTitle("ePortfolio");
    setSize(WIDTH, HEIGHT);
    setLayout(new GridLayout(3, 1));
    setResizable(false);

    // upper panels holds multiple child panels
    upperPanel = new JPanel();
    upperPanel.setLayout(new GridLayout(1, 3));

    // welcome panel holds the welcome message and description
    welcomePanel = new JPanel();
    welcomePanel.setLayout(new FlowLayout());
    welcome = new JLabel("<html> Welcome to ePortfolio.<br> </html>");
    welcomeDescription = new JLabel(
        "<html> Choose a command from the \"Commands\" menu to buy or sell <br> an investment, update prices for all investments, get gain for the <br> portfolio, search for relevant investments, or quit the program.");
    welcome.setFont(new Font("Trebuchet", Font.BOLD, 19));
    welcomeDescription.setFont(new Font("Trebuchet", Font.PLAIN, 15));
    welcomePanel.add(welcome);
    welcomePanel.add(welcomeDescription);
    add(welcomePanel);

    // left panel holds the text fields and labels for inputting values
    leftPanel = new JPanel();
    leftPanel.setLayout(new GridLayout(5, 2));

    // combobox for type
    String[] type = { "stock", "mutualfund" };
    invType = new JComboBox<String>(type);
    invTypeLabel = new JLabel("Type");
    leftPanel.add(invTypeLabel);
    leftPanel.add(invType);

    // symbol label and text field
    symbolLabel = new JLabel("Symbol");
    leftPanel.add(symbolLabel);
    symbolTextField = new JTextField(10);
    leftPanel.add(symbolTextField);

    // name label and text field
    nameLabel = new JLabel("Name");
    leftPanel.add(nameLabel);
    nameTextField = new JTextField(20);
    leftPanel.add(nameTextField);

    // quantity label and text field
    quantityLabel = new JLabel("Quantity");
    leftPanel.add(quantityLabel);
    quantityTextField = new JTextField(5);
    leftPanel.add(quantityTextField);

    // price label and text field
    priceLabel = new JLabel("Price");
    leftPanel.add(priceLabel);
    priceTextField = new JTextField(5);
    leftPanel.add(priceTextField);

    // adding left panel to parent upper panel
    upperPanel.add(leftPanel);

    // right panel holds the buttons
    rightPanel = new JPanel();
    rightPanel.setLayout(new FlowLayout());

    // buy button
    buyBtn = new JButton("Buy");
    buyBtn.setForeground(Color.GREEN);
    buyBtn.setPreferredSize(new Dimension(200, 50));
    buyBtn.addActionListener(this);

    // sell button
    sellBtn = new JButton("Sell");
    sellBtn.setForeground(Color.GREEN);
    sellBtn.setPreferredSize(new Dimension(200, 50));
    sellBtn.addActionListener(this);

    // reset button
    resetBtn = new JButton("Reset");
    resetBtn.setForeground(Color.RED);
    resetBtn.setPreferredSize(new Dimension(200, 50));
    resetBtn.addActionListener(this);

    // prev button
    prevBtn = new JButton("Prev");
    prevBtn.setForeground(Color.ORANGE);
    prevBtn.setPreferredSize(new Dimension(200, 50));
    prevBtn.addActionListener(this);

    // next button
    nextBtn = new JButton("Next");
    nextBtn.setForeground(Color.BLUE);
    nextBtn.setPreferredSize(new Dimension(200, 50));
    nextBtn.addActionListener(this);

    // save button
    saveBtn = new JButton("Save");
    saveBtn.setForeground(Color.GREEN);
    saveBtn.setPreferredSize(new Dimension(200, 50));
    saveBtn.addActionListener(this);

    // search button
    searchBtn = new JButton("Search");
    searchBtn.setForeground(Color.GREEN);
    searchBtn.setPreferredSize(new Dimension(200, 50));
    searchBtn.addActionListener(this);

    // adding all buttons to right panel
    rightPanel.add(resetBtn);
    rightPanel.add(buyBtn);
    rightPanel.add(sellBtn);
    rightPanel.add(prevBtn);
    rightPanel.add(nextBtn);
    rightPanel.add(saveBtn);
    rightPanel.add(searchBtn);

    // adding right panel to parent upper panel
    upperPanel.add(rightPanel);

    // output panel holds the message box with scrollable area
    outputPanel = new JPanel();
    outputLabel = new JLabel("Messages");
    outputText = new JTextArea(LINES, CHARS_PER_LINE);
    outputText.setEditable(false);
    outputText.setBackground(Color.WHITE);
    outputPanel.add(outputLabel);
    JScrollPane scrolledText = new JScrollPane(outputText);
    scrolledText.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
    scrolledText.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
    outputPanel.add(scrolledText);

    // adding upper panel and output panel to JFrame
    add(upperPanel);
    add(outputPanel);

    // setting visible to false in order to set true in action listeners
    upperPanel.setVisible(false);
    outputPanel.setVisible(false);

    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
  }

  /**
   *
   * Options sets the menu bar with its menu items along with actionlisteners
   *
   */
  public void options() {
    // all menu options
    JMenu menu = new JMenu("Commands");
    JMenuItem buyMenu = new JMenuItem("Buy an Investment");
    buyMenu.addActionListener(this);
    menu.add(buyMenu);

    JMenuItem sellMenu = new JMenuItem("Sell an Investment");
    sellMenu.addActionListener(this);
    menu.add(sellMenu);

    JMenuItem updateMenu = new JMenuItem("Update Investments");
    updateMenu.addActionListener(this);
    menu.add(updateMenu);

    JMenuItem gainMenu = new JMenuItem("Get Total Gain");
    gainMenu.addActionListener(this);
    menu.add(gainMenu);

    JMenuItem searchMenu = new JMenuItem("Search Investments");
    searchMenu.addActionListener(this);
    menu.add(searchMenu);

    JMenuItem quit = new JMenuItem("End Program (Output Data)");
    quit.addActionListener(this);
    menu.add(quit);

    JMenuBar bar = new JMenuBar();
    bar.add(menu);

    setJMenuBar(bar);
  }

  /**
   *
   * Action performed
   *
   * @param e is the event listener which will listen for button clicks and menu
   *          option clicks
   */
  @Override
  public void actionPerformed(ActionEvent e) {
    outputText.setText("");
    nextBtn.setVisible(true);
    prevBtn.setVisible(true);
    String str = e.getActionCommand();
    String buyBtnStr = e.getActionCommand();
    String resetBtnStr = e.getActionCommand();
    String sellBtnStr = e.getActionCommand();
    String nextBtnStr = e.getActionCommand();
    String prevBtnStr = e.getActionCommand();
    String saveBtnStr = e.getActionCommand();
    String searchBtnStr = e.getActionCommand();
    // interface for buying an investment
    if (str.equals("Buy an Investment")) {
      invType.setVisible(true);
      invTypeLabel.setVisible(true);
      sellBtn.setVisible(false);
      buyBtn.setVisible(true);
      upperPanel.setVisible(true);
      outputPanel.setVisible(true);
      welcomeDescription.setVisible(false);
      welcome.setText("Buying an investment");
      nameLabel.setText("Name");
      symbolLabel.setVisible(true);
      nameLabel.setVisible(true);
      quantityLabel.setVisible(true);
      quantityLabel.setText("Quantity");
      priceLabel.setVisible(true);
      symbolTextField.setVisible(true);
      nameTextField.setVisible(true);
      priceTextField.setVisible(true);
      quantityTextField.setVisible(true);
      prevBtn.setVisible(false);
      nextBtn.setVisible(false);
      saveBtn.setVisible(false);
      searchBtn.setVisible(false);
      resetBtn.setVisible(true);
      outputLabel.setText("Messages");
      symbolTextField.setEditable(true);
      nameTextField.setEditable(true);
      symbolLabel.setText("Symbol");
      priceLabel.setText("Price");
      // what do do when buy button is clicked
    } else if (buyBtnStr.equals("Buy")) {
      nextBtn.setVisible(false);
      prevBtn.setVisible(false);
      String inputType = (String) invType.getSelectedItem();
      String inputSymbol = symbolTextField.getText();
      String inputName = nameTextField.getText();
      String inputPrice = priceTextField.getText();
      String inputQuantity = quantityTextField.getText();
      boolean valid;
      do {
        valid = true;
        try {
          if (inputType.equals("stock")) {
            s = new Stock(inputSymbol, inputName, Integer.parseInt(inputQuantity),
                Double.parseDouble(inputPrice));
            // new stock
            if (checkEqualsSymbol(inputSymbol) == -1) {
              s.setType(inputType);
              s.setSymbol(inputSymbol);
              s.setName(inputName);
              s.setQuantity(Integer.parseInt(inputQuantity));
              s.setPrice(Double.parseDouble(inputPrice));
              s.setBookValue(Integer.parseInt(inputQuantity), Double.parseDouble(inputPrice));
              investments.add(s);
              hashBuy(s.getName());
              s = new Stock();
            } else {
              outputText.append("Investment already exists, updating existing...\n");
              // getting index of symbol
              int index = checkEqualsSymbol(inputSymbol);
              // getting old bookvalue
              double oldBookValue = investments.get(index).getBookvalue();
              s.setQuantity(Integer.parseInt(inputQuantity));
              // update quantity
              investments.get(index).addQuantity(Integer.parseInt(inputQuantity));
              s.setPrice(Double.parseDouble(inputPrice));
              investments.get(index).setPrice(Double.parseDouble(inputPrice));
              investments.get(index).setBookValue(Integer.parseInt(inputQuantity),
                  Double.parseDouble(inputPrice));
              investments.get(index).updateBookValue(oldBookValue, investments.get(index).getBookvalue());
            }
          } else if (inputType.equals("mutualfund")) {
            m = new MutualFund(inputSymbol, inputName, Integer.parseInt(inputQuantity),
                Double.parseDouble(inputPrice));
            if (checkEqualsSymbol(inputSymbol) == -1) {
              m.setType("mutualfund");
              m.setSymbol(inputSymbol);
              m.setName(inputName);
              m.setQuantity(Integer.parseInt(inputQuantity));
              m.setPrice(Double.parseDouble(inputPrice));
              m.setBookValue(Integer.parseInt(inputQuantity), Double.parseDouble(inputPrice));
              investments.add(m);
              hashBuy(m.getName());
              m = new MutualFund();
            } else {
              int index = checkEqualsSymbol(inputSymbol);
              // getting old bookvalue
              double oldBookValue = investments.get(index).getBookvalue();
              m.setQuantity(Integer.parseInt(inputQuantity));
              // update quantity
              investments.get(index).addQuantity(Integer.parseInt(inputQuantity));
              investments.get(index).setPrice(Double.parseDouble(inputPrice));
              investments.get(index).setBookValue(Integer.parseInt(inputQuantity),
                  Double.parseDouble(inputPrice));
              investments.get(index).updateBookValue(oldBookValue, investments.get(index).getBookvalue());
            }
          }
          outputText.append(printList());
          System.out.println(map);
        } catch (Exception f) {
          outputText.append(f.getMessage());
        }
      } while (!valid);
      // what to do when reset button is clicked
    } else if (resetBtnStr.equals("Reset")) {
      nextBtn.setVisible(false);
      prevBtn.setVisible(false);
      symbolTextField.setText("");
      nameTextField.setText("");
      quantityTextField.setText("");
      priceTextField.setText("");
    } else if (str.equals("Sell an Investment")) {
      // interface for selling an investment
      upperPanel.setVisible(true);
      outputPanel.setVisible(true);
      welcome.setText("Selling an investment");
      welcomeDescription.setVisible(false);
      invType.setVisible(false);
      invTypeLabel.setVisible(false);
      nameLabel.setVisible(true);
      nameTextField.setVisible(true);
      nameLabel.setText("Quantity");
      buyBtn.setVisible(false);
      prevBtn.setVisible(false);
      nextBtn.setVisible(false);
      saveBtn.setVisible(false);
      searchBtn.setVisible(false);
      sellBtn.setVisible(true);
      resetBtn.setVisible(true);
      symbolLabel.setVisible(true);
      symbolTextField.setVisible(true);
      quantityLabel.setVisible(true);
      quantityTextField.setVisible(true);
      quantityLabel.setText("Price");
      priceLabel.setVisible(false);
      priceTextField.setVisible(false);
      outputLabel.setText("Messages");
      symbolTextField.setEditable(true);
      nameTextField.setEditable(true);
      symbolLabel.setText("Symbol");
    } else if (sellBtnStr.equals("Sell")) {
      // what to do when sell button is clicked
      nextBtn.setVisible(false);
      prevBtn.setVisible(false);
      String inputSymbol = symbolTextField.getText();
      String inputPrice = quantityTextField.getText();
      String inputQuantity = nameTextField.getText();
      // error checking to see if symbol actually exists
      if (checkEqualsSymbol(inputSymbol) == -1) {
        outputText.append("Error: " + inputSymbol + " does not exist\n");
      } else {
        // getting old values
        int index = checkEqualsSymbol(inputSymbol);
        int oldQuantity = investments.get(index).getQuantity();
        // error checking to see if inputquantity is smaller than old
        if (Integer.parseInt(inputQuantity) > oldQuantity || Integer.parseInt(inputQuantity) <= 0) {
          outputText.append("Error: invalid quantity\n");
        } else {
          // getting old bookvalue
          double oldBookValue = investments.get(index).getBookvalue();
          investments.get(index).sellQuantity(Integer.parseInt(inputQuantity));
          // if after selling, quantity is 0, update price and remove investment
          if (investments.get(index).getQuantity() == 0) {
            // error checking price to make sure it is > 0
            if (Double.parseDouble(inputPrice) > 0) {
              // calculating new bookvalue
              investments.get(index).setPrice(Double.parseDouble(inputPrice));
              investments.get(index).adjustBookValue(oldBookValue, oldQuantity,
                  oldQuantity - Integer.parseInt(inputQuantity));
              // calculating payment recieved
              if (investments.get(index).getType().equals("stock")) {
                double payment = Integer.parseInt(inputQuantity) * Double.parseDouble(inputPrice)
                    - 9.99;
                outputText.append("Payment Received: $" + String.valueOf(payment) + "\n");
              } else {
                double payment = Integer.parseInt(inputQuantity) * Double.parseDouble(inputPrice)
                    - 45;
                outputText.append("Payment Received: $" + String.valueOf(payment) + "\n");
              }
              investments.remove(index);
              outputText.append("Investment has been removed\n");
              hashSell();
            } else {
              outputText.append("Error: invalid price\n");
            }
          } else {
            // error checking price to make sure it is > 0
            if (Double.parseDouble(inputPrice) > 0) {
              // calculating new bookvalue
              investments.get(index).setPrice(Double.parseDouble(inputPrice));
              investments.get(index).adjustBookValue(oldBookValue, oldQuantity,
                  oldQuantity - Integer.parseInt(inputQuantity));
              // calculating payment recieved
              if (investments.get(index).getType().equals("stock")) {
                double payment = Integer.parseInt(inputQuantity) * Double.parseDouble(inputPrice)
                    - 9.99;
                outputText.append("Payment Received: $" + String.valueOf(payment) + "\n");
              } else {
                double payment = Integer.parseInt(inputQuantity) * Double.parseDouble(inputPrice)
                    - 45;
                outputText.append("Payment Received: $" + String.valueOf(payment) + "\n");
              }
              hashSell();
            } else {
              outputText.append("Error: invalid price\n");
            }
          }
        }
      }
    } else if (str.equals("Update Investments")) {
      // interface for updating investments
      j = 0;
      upperPanel.setVisible(true);
      outputPanel.setVisible(true);
      welcome.setText("Updating Investments");
      welcomeDescription.setVisible(false);
      invType.setVisible(false);
      invTypeLabel.setVisible(false);
      nameLabel.setVisible(true);
      nameTextField.setVisible(true);
      nameLabel.setText("Name");
      buyBtn.setVisible(false);
      prevBtn.setVisible(true);
      nextBtn.setVisible(true);
      saveBtn.setVisible(true);
      searchBtn.setVisible(false);
      sellBtn.setVisible(false);
      resetBtn.setVisible(false);
      symbolLabel.setVisible(true);
      symbolTextField.setVisible(true);
      quantityLabel.setVisible(true);
      quantityTextField.setVisible(true);
      quantityLabel.setText("Price");
      priceLabel.setVisible(false);
      priceTextField.setVisible(false);
      symbolTextField.setEditable(false);
      nameTextField.setEditable(false);
      outputLabel.setText("Messages");
      symbolLabel.setText("Symbol");
    } else if (nextBtnStr.equals("Next")) {
      // move forward in list when next is clicked
      if (j < investments.size() - 1) {
        j++;
        nextBtn.setVisible(true);
        symbolTextField.setText(investments.get(j).getSymbol());
        nameTextField.setText(investments.get(j).getName());
      } else {
        // remove button when end is reached
        nextBtn.setVisible(false);
        outputText.append("No more investments\n");
      }
    } else if (prevBtnStr.equals("Prev")) {
      // move backwards in list when prev is clicked
      if (j > 0) {
        j--;
        prevBtn.setVisible(true);
        symbolTextField.setText(investments.get(j).getSymbol());
        nameTextField.setText(investments.get(j).getName());
      } else {
        // remove button when end is reached
        prevBtn.setVisible(false);
        outputText.append("No more investments\n");
      }
    } else if (saveBtnStr.equals("Save")) {
      // set price when save button is clicked
      String inputPriceStr = quantityTextField.getText();
      if (Double.parseDouble(inputPriceStr) < 0 || inputPriceStr.isEmpty()) {
        outputText.append("Error: invalid price\n");
      } else {
        investments.get(j).setPrice(Double.parseDouble(inputPriceStr));
        outputText.append(printList());
      }
      outputText.append("Prices updated succesfully\n");
    } else if (str.equals("Get Total Gain")) {
      // interface for getting total gain
      upperPanel.setVisible(true);
      outputPanel.setVisible(true);
      welcome.setText("Getting Total Gain");
      welcomeDescription.setVisible(false);
      invType.setVisible(false);
      invTypeLabel.setVisible(false);
      nameLabel.setVisible(false);
      nameTextField.setVisible(false);
      nameLabel.setText("Name");
      buyBtn.setVisible(false);
      prevBtn.setVisible(false);
      nextBtn.setVisible(false);
      saveBtn.setVisible(false);
      searchBtn.setVisible(false);
      sellBtn.setVisible(false);
      resetBtn.setVisible(false);
      symbolLabel.setVisible(true);
      symbolTextField.setVisible(true);
      symbolLabel.setText("Total gain");
      quantityLabel.setVisible(false);
      quantityTextField.setVisible(false);
      quantityLabel.setText("Quantity");
      priceLabel.setVisible(false);
      priceTextField.setVisible(false);
      symbolTextField.setEditable(false);
      nameTextField.setEditable(true);
      outputLabel.setText("Individual Gains");
      double totalGain = 0.0;
      double indivGain = 0.0;
      // go thru list and calculate total gain as well as individual gains and output
      // them
      for (int i = 0; i < investments.size(); i++) {
        indivGain = investments.get(i).getGains();
        outputText.append(investments.get(i).getSymbol() + ": $" + String.valueOf(indivGain) + "\n");
        totalGain += indivGain;
      }
      symbolTextField.setText(String.valueOf(totalGain));
    } else if (str.equals("Search Investments")) {
      // interface for searching investments
      upperPanel.setVisible(true);
      outputPanel.setVisible(true);
      welcome.setText("Searching Investments");
      welcomeDescription.setVisible(false);
      invType.setVisible(false);
      invTypeLabel.setVisible(false);
      nameLabel.setVisible(true);
      nameTextField.setVisible(true);
      nameLabel.setText("Name Keywords");
      buyBtn.setVisible(false);
      prevBtn.setVisible(false);
      nextBtn.setVisible(false);
      saveBtn.setVisible(false);
      searchBtn.setVisible(true);
      sellBtn.setVisible(false);
      resetBtn.setVisible(true);
      symbolLabel.setVisible(true);
      symbolTextField.setVisible(true);
      symbolLabel.setText("Symbol");
      quantityLabel.setVisible(true);
      quantityTextField.setVisible(true);
      quantityLabel.setText("Low Price");
      priceLabel.setVisible(true);
      priceTextField.setVisible(true);
      priceLabel.setText("High Price");
      symbolTextField.setEditable(true);
      nameTextField.setEditable(true);
      outputLabel.setText("Search Results");
    } else if (searchBtnStr.equals("Search")) {
      // what to do when search button is clicked
      nextBtn.setVisible(false);
      prevBtn.setVisible(false);

      String symbol = symbolTextField.getText();
      String keyword = nameTextField.getText();

      if (!keyword.equals("")) {
        keyword = keyword.toLowerCase();
      }

      // comparing input values in order to call the correct methods
      if (nameTextField.getText().equals("") && quantityTextField.getText().equals("")
          && priceTextField.getText().equals("") && !(symbolTextField.getText().equals(""))) {
        searchSymbol(symbol);
      } else if (symbolTextField.getText().equals("") && quantityTextField.getText().equals("")
          && priceTextField.getText().equals("") && !nameTextField.getText().equals("")) {
        searchKeyword(keyword);
      } else if (symbolTextField.getText().equals("") && nameTextField.getText().equals("")
          && (!quantityTextField.getText().equals("") || !priceTextField.getText().equals(""))) {
        double min = Double.parseDouble(quantityTextField.getText());
        double max = Double.parseDouble(priceTextField.getText());
        searchPrice(min, max);
      } else if (quantityTextField.getText().equals("") && priceTextField.getText().equals("")
          && !symbolTextField.getText().equals("") && !nameTextField.getText().equals("")) {
        searchSymbolAndKeyword(symbol, keyword);
      } else if (!symbolTextField.getText().equals("") && nameTextField.getText().equals("")
          && (!quantityTextField.getText().equals("") || !priceTextField.getText().equals(""))) {
        double min = Double.parseDouble(quantityTextField.getText());
        double max = Double.parseDouble(priceTextField.getText());
        searchSymbolAndPrice(symbol, min, max);
      } else if (symbolTextField.getText().equals("") && !nameTextField.getText().equals("")
          && (!quantityTextField.getText().equals("") || !priceTextField.getText().equals(""))) {
        double min = Double.parseDouble(quantityTextField.getText());
        double max = Double.parseDouble(priceTextField.getText());
        searchKeywordAndPrice(keyword, min, max);
      } else if (!symbolTextField.getText().equals("") && !nameTextField.getText().equals("")
          && (!quantityTextField.getText().equals("") || !priceTextField.getText().equals(""))) {
        double min = Double.parseDouble(quantityTextField.getText());
        double max = Double.parseDouble(priceTextField.getText());
        searchAll(symbol, keyword, min, max);
        // if no inputs are filled
      } else {
        searchNone();
      }
    } else if (str.equals("End Program (Output Data)")) {
      // output to file when chosen. using temp as i used my save method in main to
      // save the filename
      outputFile(temp);
      System.exit(0);
    }
  }

  /**
   *
   * Leave is a helper function that tells when to call outputfile function
   *
   * @return Boolean
   */
  public Boolean leave() {
    if (counter == 1) {
      return true;
    } else {
      return false;
    }
  }

  /**
   *
   * Print list prints the investment array list
   * 
   * @return result which is formatted tostring with a new line seperator
   */
  public String printList() {
    String result = "";
    for (int i = 0; i < investments.size(); i++) {
      result += investments.get(i).toString();
    }
    return result + "\n";

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
   * @param name which is the user inputted name
   */
  public void hashBuy(String name) {
    String[] token = name.split("[ ]+");
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
      hashBuy(investments.get(j).getName());
    }
  }

  /**
   *
   * Read file parses the contents of the file and adds the information to either
   * a
   * stock or mutual fund object which goes into the investment list
   *
   * @param filename the filename
   */
  public void readFile(String filename) {
    try {
      int counter = 0;
      String type = "";
      File f = new File(filename);
      Scanner inputFile = new Scanner(f);
      while (inputFile.hasNextLine()) {
        String read = inputFile.nextLine();
        // splitting on quotation marks
        String[] contents = read.split("\"");
        if (counter < 6) {
          // getting type of investment
          if (counter == 0) {
            type = contents[1];
          }
          // parsing stock
          if (type.equals("stock")) {
            s.setType("stock");
            if (counter == 1) {
              s.setSymbol(contents[1]);
            }
            if (counter == 2) {
              s.setName(contents[1]);
            }
            if (counter == 3) {
              s.setQuantity(Integer.parseInt(contents[1]));
            }
            if (counter == 4) {
              s.setPrice(Double.parseDouble(contents[1]));
            }
            if (counter == 5) {
              // adding
              s.setRealBookValue(Double.parseDouble(contents[1]));
              investments.add(s);
              hashBuy(s.getName());
              s = new Stock();
            }
            // parsing mutualfund
          } else if (type.equals("mutualfund")) {
            m.setType("mutualfund");
            if (counter == 1) {
              m.setSymbol(contents[1]);
            }
            if (counter == 2) {
              m.setName(contents[1]);
            }
            if (counter == 3) {
              m.setQuantity(Integer.parseInt(contents[1]));
            }
            if (counter == 4) {
              m.setPrice(Double.parseDouble(contents[1]));
            }
            if (counter == 5) {
              // adding
              m.setRealBookValue(Double.parseDouble(contents[1]));
              investments.add(m);
              hashBuy(m.getName());
              m = new MutualFund();
            }
          }
          counter += 1;
        } else if (counter == 6) {
          // resetting
          if (type.equals("stock")) {
            counter = 0;
          } else if (type.equals("mutualfund")) {
            counter = 0;
          }
        }
      }
      System.out.println(map);
      inputFile.close();
    } catch (Exception f) {
      outputText.append(f.getMessage());
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
    } catch (Exception f) {
      outputText.append(f.getMessage());
    }
  }

  /**
   *
   * Save takes in a filename and saves it to a variable. Used in main for calling
   * output file function
   *
   * @param filename the filename
   */
  public void save(String filename) {
    temp = filename;
  }

  /**
   *
   * Search symbol
   *
   * @param symbol the symbol
   */
  public void searchSymbol(String symbol) {
    // searching investment list
    int counter = 0;
    for (int i = 0; i < investments.size(); i++) {
      if (symbol.equalsIgnoreCase((investments.get(i).getSymbol()))) {
        outputText.append(investments.get(i).toString());
        counter++;
      }
    }
    if (counter == 0) {
      outputText.append("No results (searchSymbol)\n");
    }
  }

  /**
   *
   * Search keyword searches for stock and mutualfund that contains user
   * inputted
   * keyword
   *
   * @param keyword the keyword
   */
  public void searchKeyword(String keyword) {
    int counter = 0;
    ArrayList<Integer> values = new ArrayList<Integer>();
    String[] token = keyword.split("[ ]+");
    for (int i = 0; i < token.length; i++) {
      if (map.containsKey(token[i])) {
        values = map.get(token[i]);
        outputText.append("matching value from keyword in hashmap: " + values + "\n");
        outputText.append(investments.get(values.get(i)).toString());
        counter++;
      }
    }
    if (counter == 0) {
      outputText.append("No results (searchKeyword)\n");
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
    int counter = 0;
    for (int i = 0; i < investments.size(); i++) {
      if (investments.get(i).getPrice() <= max && investments.get(i).getPrice() >= min) {
        outputText.append(investments.get(i).toString());
        counter++;
      }
    }
    if (counter == 0) {
      outputText.append("No results (searchPrice)\n");
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
    int counter = 0;
    for (int i = 0; i < investments.size(); i++) {
      if (symbol.equalsIgnoreCase(investments.get(i).getSymbol())
          && investments.get(i).getName().toLowerCase().contains(keyword)) {
        outputText.append(investments.get(i).toString());
        counter++;
      }
    }
    if (counter == 0) {
      outputText.append("No results (searchSymbolAndKeyword)\n");
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
    int counter = 0;
    for (int i = 0; i < investments.size(); i++) {
      if (symbol.equalsIgnoreCase(investments.get(i).getSymbol()) &&
          investments.get(i).getPrice() <= max
          && investments.get(i).getPrice() >= min) {
        outputText.append(investments.get(i).toString());
        counter++;
      }
    }
    if (counter == 0) {
      outputText.append("No results (searchSymbolAndPrice)\n");
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
    int counter = 0;
    for (int i = 0; i < investments.size(); i++) {
      if (investments.get(i).getName().toLowerCase().contains(keyword) &&
          investments.get(i).getPrice() <= max
          && investments.get(i).getPrice() >= min) {
        outputText.append(investments.get(i).toString());
        counter++;
      }
    }
    if (counter == 0) {
      outputText.append("No results (searchKeywordAndPrice)\n");
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
    int counter = 0;
    for (int i = 0; i < investments.size(); i++) {
      if (symbol.equalsIgnoreCase(investments.get(i).getSymbol())
          && investments.get(i).getName().toLowerCase().contains(keyword)
          && investments.get(i).getPrice() <= max && investments.get(i).getPrice() >= min) {
        outputText.append(investments.get(i).toString());
        counter++;
      }
    }
    if (counter == 0) {
      outputText.append("No results (searchAll)\n");
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
    int counter = 0;
    for (int i = 0; i < investments.size(); i++) {
      outputText.append(investments.get(i).toString());
      counter++;
    }
    if (counter == 0) {
      outputText.append("No results (searchNone)\n");
    }
  }
}
