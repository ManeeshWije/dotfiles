package lab1;

import java.util.Scanner;

public class Lab1 {
  public static void main(String[] args) {
    Scanner scannerObj = new Scanner(System.in);
    int input = 0;
    int limit = 0;
    int total = 0;
    int totalChars = 0;
    int vowels = 0;
    String[] strArr = new String[10];
    // main menu
    do {
      System.out.println("\n\n");
      System.out.println("Choose an option from 1-9\n\n");
      System.out.println("(1) Enter a full sentence\n");
      System.out.println("(2) Print out all sentences entered so far in the given order\n");
      System.out.println("(3) Print out all sentences entered thus far in the reverse order\n");
      System.out.println("(4) Print out the number of sentences that have been entered so far\n");
      System.out.println("(5) Print out the number of characters in all sentences combined\n");
      System.out.println("(6) Calculate the total number of vowels contained in all stored sentences\n");
      System.out.println("(7) Perform search for a given word using case sensitive comparisons\n");
      System.out.println("(8) Perform search for a given word using case insensitive comparisons\n");
      System.out.println("(9) End program\n");

      // user input
      input = scannerObj.nextInt();
      scannerObj.nextLine();

      if (input == 1) {
        System.out.println("Enter Sentence: ");
        if (limit >= 10) {
          System.out.println("Error: Can only enter 10 sentences into array\n");
        }
        // storing entered sentence into array
        else {
          strArr[limit] = scannerObj.nextLine();
          limit++;
          total++;
        }
      }
      if (input == 2) {
        for (int i = 0; i < total; i++) {
          System.out.println(strArr[i]);
        }
      }
      if (input == 3) {
        for (int i = total - 1; i >= 0; i--) {
          System.out.println(strArr[i]);
        }
      }
      if (input == 4) {
        System.out.println("There are " + total + " sentences in total\n");
      }
      if (input == 5) {
        for (int i = 0; i < total; i++) {
          totalChars += strArr[i].length();
        }
        System.out.println("There are " + totalChars + " characters in total\n");
      }
      if (input == 6) {
        String[] tempString = strArr;
        // making strings loweracase for ease of use
        for (int i = 0; i < total; i++) {
          tempString[i] = tempString[i].toLowerCase();
        }
        for (int j = 0; j < total; j++) {
          // first looping through entire array
          // then looping through each individual string
          for (int k = 0; k < tempString[j].length(); k++) {
            // using charat to check what character is present at the index
            char ch = tempString[j].charAt(k);
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
              vowels++;
            }
          }
        }
        System.out.println("There are " + vowels + " vowels in total\n");
        vowels = 0;
      }
      if (input == 7) {
        System.out.println("Enter word to be searched: ");
        String word = scannerObj.nextLine();
        for (int i = 0; i < total; i++) {
          if (strArr[i].contains(word)) {
            System.out.println("\n" + strArr[i]);
          }
        }
      }
      if (input == 8) {
        System.out.println("Enter word to be searched: ");
        String word = scannerObj.nextLine();
        for (int i = 0; i < total; i++) {
          // using .contains but since it is case sensitive, we use tolowercase
          // to bypass that
          if (strArr[i].toLowerCase().contains(word.toLowerCase())) {
            System.out.println("\n" + strArr[i]);
          }
        }
      }
      if (input == 9) {
        break;
      }
    } while (input >= 1 && input <= 9);
    scannerObj.close();
  }
}
