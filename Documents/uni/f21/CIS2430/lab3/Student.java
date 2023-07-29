package lab3;

import java.util.*;
import java.io.*;

public class Student {
    Scanner scan = new Scanner(System.in);
    ArrayList<Double> averages = new ArrayList<Double>();
    String program;
    int year;
    double avg = 0.00;
    double sum = 0.00;

    Student() {
        program = "";
        year = 0;
        avg = 0;
    }

    public void setVals() {
        System.out.println("Enter student program and year: \n");
        String[] split = scan.nextLine().split("\\s+"); // this regex line allows us to have as many spaces between
                                                        // splits
        while (split.length <= 1) { // error checking for invalid input
            System.out.println("Invalid input, try again\n");
            System.out.println("Enter student program and year: \n");
            split = scan.nextLine().split("\\s+");
        }
        System.out.println("Enter average grade, or leave blank: \n");
        String stringAvg = scan.nextLine(); // using string here for ease of use
        if (stringAvg.equals("") || stringAvg.equals(" ")) { // checking if empty input and if so, set avg to 0.00
                                                             // specified
            this.avg = 0.00;
        } else { // converting inputted string into a double in order to add to average arraylist
            this.avg = Double.parseDouble(stringAvg);
        }
        averages.add(this.avg); // adding to averages arraylist
        this.program = split[0]; // setting inputed program
        this.year = Integer.parseInt(split[1]); // setting inputted year value but converting string to int
    }

    public void setProgram(String program) {
        this.program = program;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public void setAvg(double avg) {
        this.avg = avg;
    }

    public String toString() {
        return "Program: " + this.program + "\n" + "Year: " + this.year + "\n" + "Average: " + this.avg + "\n";
    }

    public String getProgram() {
        return this.program;
    }

    public Double getAvg() {
        return this.avg;
    }

    public Double calculateAvg(ArrayList<Double> averages) {
        // looping through averages arraylist and adding each index to sum
        for (int i = 0; i < averages.size(); i++) {
            sum += averages.get(i);
        }
        // dividing sum by number of indices which whill give us the average grade
        // amongst entire arraylist
        return (double) sum / averages.size();
    }

    public String printOutputFile() {
        return this.program + " " + this.year + " " + this.avg;
    }

}
