package lab2;

import java.util.Scanner;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        int input = 0;
        ArrayList<Student> students = new ArrayList<Student>();
        ArrayList<Double> averages = new ArrayList<Double>();
        Scanner scan = new Scanner(System.in);
        do {
            System.out.println("Choose an option from 1-5\n\n");
            System.out.println("(1) Enter information for a new student\n");
            System.out.println(
                    "(2) Show all student information with program, year, and average grade on separate lines\n");
            System.out.println(
                    "(3) Print the average of the average grades for class and the total number of students\n");
            System.out.println("(4) Enter a specific program and show all student information for that program\n");
            System.out.println("(5) End the program\n");
            input = scan.nextInt();
            scan.nextLine();
            if (input == 1) {
                Student s = new Student(); // creating new student object
                s.setVals(); // all inputs handled here
                students.add(s); // adding properties into arraylist
                averages.add(s.getAvg()); // adding the average to seperate arraylist in order to calculate avg later
            }
            if (input == 2) {
                if (students.size() == 0) {
                    System.out.println("No info to show\n");
                } else {
                    for (int i = 0; i < students.size(); i++) {
                        System.out.println(students.get(i).toString());
                    }
                }
            }
            if (input == 3) {
                Student avg = new Student(); // new student object for averages
                System.out.println("Total Average Grade = " + avg.calculateAvg(averages));
                System.out.println("Total # of Students = " + students.size());
            }
            if (input == 4) {
                System.out.println("Enter a specific program: ");
                String program = scan.nextLine();
                // in the arraylist, if the index for program equals inputted program,
                // then use print method on that index
                for (int i = 0; i < students.size(); i++) {
                    if (students.get(i).getProgram().equals(program)) {
                        // students.get(i).toString();
                        System.out.println(students.get(i));
                    }
                }
            }
            if (input == 5) {
                break;
            }
        } while (input >= 1 && input <= 5);
        scan.close();
    }
}
