package lab4;

import java.util.*;
import java.io.*;

public class Main {

    public static void main(String[] args) {
        int input = 0;
        ArrayList<Student> students = new ArrayList<Student>();
        ArrayList<Double> averages = new ArrayList<Double>();
        HashMap<String, Student> map = new HashMap<String, Student>();
        Student s = new Student();
        Student g = new GraduateStudent();
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
            System.out.println("(8) Lookup via HashMap with program, year, and lastName\n");
            System.out.println("(9) End the program\n");
            input = scan.nextInt();
            scan.nextLine();

            if (input == 1) {
                boolean valid;
                do {
                    valid = true;
                    try {
                        Student st = new Student(s.askProgram(), s.askYear(), s.askLastName(), s.askAvg());
                        String key = st.hashString();
                        if (!map.containsKey(key)) {
                            students.add(st); // adding properties into arraylist
                            averages.add(st.getAvg()); // adding the average to seperate arraylist in order to calculate
                                                       // avg
                                                       // later
                            map.put(key, st);
                            st = new Student();
                        } else {
                            students.remove(st);
                            System.out.println("Error: Key already exists");
                        }
                        // System.out.println(map);
                    } catch (Exception e) {
                        System.out.println(e.getMessage());
                        valid = false;
                    }
                } while (!valid);
            }
            if (input == 2) {
                boolean valid;
                do {
                    valid = true;
                    try {
                        GraduateStudent gt = new GraduateStudent(g.askProgram(), g.askYear(), g.askLastName(),
                                g.askAvg());
                        gt.askisPhd();
                        gt.askSuper();
                        gt.askUnder();
                        String key = gt.hashString();
                        if (!map.containsKey(key)) {
                            students.add(gt); // adding properties into arraylist
                            averages.add(gt.getAvg()); // adding the average to seperate arraylist in order to
                                                       // calculate// avg // later
                            map.put(key, gt);
                            gt = new GraduateStudent();
                        } else {
                            students.remove(gt);
                            System.out.println("Error: Key already exists");
                        }
                        // System.out.println(map);
                    } catch (Exception e) {
                        System.out.println(e.getMessage());
                        valid = false;
                    }
                } while (!valid);
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
                        if (contents.length == 4) { // we know its a regular student
                            Student st = new Student(s.program, s.year, s.lastName, s.avg);
                            st.setProgram(contents[0]);
                            st.setYear(Integer.parseInt(contents[1]));
                            st.setAvg(Double.parseDouble(contents[2]));
                            st.setLastName(contents[3]);
                            String key = st.hashString();
                            if (!map.containsKey(key)) {
                                students.add(st);
                                averages.add(st.getAvg());
                                map.put(key, st);
                                st = new Student();
                            } else {
                                students.remove(st);
                                System.out.println("Error: Key already exists");
                            }
                        } else if (contents.length == 7) { // we know its a graduate student
                            GraduateStudent gt = new GraduateStudent(s.program, s.year, s.lastName, s.avg);
                            gt.setProgram(contents[0]);
                            gt.setYear(Integer.parseInt(contents[1]));
                            gt.setAvg(Double.parseDouble(contents[2]));
                            gt.setSupervisor(contents[3]);
                            if (Integer.parseInt(contents[4]) == 1) {
                                gt.setIsPhd(true);
                            } else if (Integer.parseInt(contents[4]) == 0) {
                                gt.setIsPhd(false);
                            }
                            gt.setUndergraduateSchool(contents[5]);
                            gt.setLastName(contents[6]);
                            String key = gt.hashString();
                            if (!map.containsKey(key)) {
                                students.add(gt);
                                averages.add(gt.getAvg());
                                map.put(key, gt);
                                gt = new GraduateStudent();
                            } else {
                                students.remove(gt);
                                System.out.println("Key already exists");
                            }
                        }
                    }
                    inputFile.close();
                } catch (Exception e) {
                    // i do getmessage but also if the file doesnt exist this message will also
                    // appear
                    System.out.println(e.getMessage());
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
                System.out.println("Enter search key: ");
                String search = scan.nextLine();
                if (map.containsKey(search)) {
                    System.out.println(map.get(search));
                }
            }
            if (input == 9) {
                break;
            }
        } while (input >= 1 && input <= 9);
        scan.close();
    }
}
