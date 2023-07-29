package lab3;

import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        int input = 0;
        ArrayList<Student> students = new ArrayList<Student>();
        ArrayList<Double> averages = new ArrayList<Double>();
        Scanner scan = new Scanner(System.in);
        do {
            System.out.println("Choose an option from 1-8\n\n");
            System.out.println("(1) Enter information for a new student\n");
            System.out.println("(2) Enter information for a new Graduate student\n");
            System.out.println(
                    "(3) Show all student information with program, year, and average grade on separate lines\n");
            System.out.println(
                    "(4) Print the average of the average grades for class and the total number of students\n");
            System.out.println("(5) Enter a specific program and show all student information for that program\n");
            System.out.println("(6) Load student information from an input file\n");
            System.out.println("(7) Save all student information to an output file\n");
            System.out.println("(8) End the program\n");
            input = scan.nextInt();
            scan.nextLine();
            if (input == 1) {
                Student s = new Student(); // creating new student object
                s.setVals(); // all inputs handled here
                students.add(s); // adding properties into arraylist
                averages.add(s.getAvg()); // adding the average to seperate arraylist in order to calculate avg later
            }
            if (input == 2) {
                GraduateStudent g = new GraduateStudent();
                g.setVals();
                students.add(g);
                averages.add(g.getAvg());
            }
            if (input == 3) {
                if (students.size() == 0) {
                    System.out.println("No info to show\n");
                } else {
                    for (int i = 0; i < students.size(); i++) {
                        System.out.println(students.get(i).toString());
                    }
                }
            }
            if (input == 4) {
                Student avg = new Student(); // new student object for averages
                System.out.println("Total Average Grade = " + avg.calculateAvg(averages));
                System.out.println("Total # of Students = " + students.size());
            }
            if (input == 5) {
                System.out.println("Enter a specific program: ");
                String program = scan.nextLine();
                // in the arraylist, if the index for program equals inputted program,
                // then use print method on that index
                for (int i = 0; i < students.size(); i++) {
                    if (students.get(i).getProgram().equals(program)) {
                        System.out.println(students.get(i).toString());
                    }
                }
            }
            if (input == 6) {
                try {
                    System.out.println("Please enter the name of the input file: ");
                    String fileName = scan.nextLine();
                    File f = new File(fileName);
                    Scanner inputFile = new Scanner(f);
                    while (inputFile.hasNextLine()) {
                        String read = inputFile.nextLine();
                        String[] contents = read.split(" ");
                        if (contents.length == 3) { // we know its a regular student
                            Student s = new Student();
                            s.setProgram(contents[0]);
                            s.setYear(Integer.parseInt(contents[1]));
                            s.setAvg(Double.parseDouble(contents[2]));
                            students.add(s);
                            averages.add(s.getAvg());
                        } else if (contents.length == 6) { // we know its a graduate student
                            GraduateStudent g = new GraduateStudent();
                            g.setProgram(contents[0]);
                            g.setYear(Integer.parseInt(contents[1]));
                            g.setAvg(Double.parseDouble(contents[2]));
                            g.setSupervisor(contents[3]);
                            if (Integer.parseInt(contents[4]) == 1) {
                                g.setIsPhd(true);
                            } else if (Integer.parseInt(contents[4]) == 0) {
                                g.setIsPhd(false);
                            }
                            g.setUndergraduateSchool(contents[5]);
                            students.add(g);
                            averages.add(g.getAvg());
                        }
                    }
                } catch (Exception e) {
                    System.out.println("ERROR: could not open file");
                }
            }
            if (input == 7) {
                try {
                    System.out.println("Please enter the name of the output file: ");
                    String outputFile = scan.nextLine();
                    PrintWriter fileWriter = new PrintWriter(outputFile, "UTF-8");
                    for (int i = 0; i < students.size(); i++) {
                        fileWriter.println(students.get(i).printOutputFile());
                    }
                    fileWriter.close();
                } catch (Exception e) {
                    System.out.println("Error: could not write to file");
                }
            }
            if (input == 8) {
                break;
            }
        } while (input >= 1 && input <= 8);
        scan.close();
    }
}
