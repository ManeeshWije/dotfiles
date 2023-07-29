package ePortfolio;

import java.util.*;

/**
 * The class Main contains a GUI object which sets the visibility of it and
 * commences readfile/outputfile
 * 
 */
public class Main {
  /**
   *
   * Main
   *
   * @param args the args
   */
  public static void main(String[] args) {
    GUI window = new GUI();
    window.setVisible(true);
    // error checking if no command line arg is given
    if (args.length == 0 || args == null) {
      System.out
          .println("Error, no file entered in as command line arg. Please do java ePortfolio.Main input.txt");
    }
    // calling inputfile method and then saving outputfile name to be used in gui
    window.readFile(args[0]);
    window.save(args[0]);
  }

}
