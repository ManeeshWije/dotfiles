package lab4;

import java.util.*;

public class Student {
    Scanner scan = new Scanner(System.in);
    ArrayList<Double> averages = new ArrayList<Double>();
    String program;
    String lastName;
    int year;
    double avg = 0.00;
    double sum = 0.00;

    public Student(String program, int year, String lastName, double avg) throws Exception {
        if (program != null && !program.equals("") && year != 0 && lastName != null && !lastName.equals("") && avg >= 0
                && avg <= 100) {
            this.program = program;
            this.avg = avg;
            this.lastName = lastName;
            this.year = year;
        } else {
            throw new Exception("Error: invalid inputs");
        }
    }

    Student() {
        lastName = "";
        program = "";
        year = 0;
        avg = 0.0;
    }

    public String askProgram() {
        System.out.println("Enter program: ");
        String[] split = scan.nextLine().split("\\s+"); // this regex line allows us to have as many spaces between
                                                        // splits
        while (split.length <= 0) { // error checking for invalid input
            System.out.println("Invalid input, try again\n");
            System.out.println("Enter student program: \n");
            split = scan.nextLine().split("\\s+");
        }
        setProgram(split[0]); // setting inputed program
        return this.program;
    }

    public int askYear() {
        System.out.println("Enter year: ");
        int yr = scan.nextInt();
        scan.nextLine();
        setYear(yr);
        return this.year;
    }

    public String askLastName() {
        System.out.println("Enter lastname: \n");
        String last = scan.nextLine();
        setLastName(last);
        return this.lastName;
    }

    public Double askAvg() {
        System.out.println("Enter average grade, or leave blank: \n");
        String stringAvg = scan.nextLine(); // using string here for ease of use
        if (stringAvg.equals("") || stringAvg.equals(" ")) { // checking if empty input and if so, set avg to 0.00
                                                             // specified
            this.avg = 0.00;
        } else { // converting inputted string into a double in order to add to average arraylist
            this.avg = Double.parseDouble(stringAvg);
        }
        averages.add(this.avg); // adding to averages arraylist
        return this.avg;
    }

    public void setProgram(String program) {
        this.program = program;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public void setAvg(double avg) {
        this.avg = avg;
    }

    public String toString() {
        return "Program: " + this.program + "\n" + "Year: " + this.year + "\n" + "Average: " + this.avg + "\n"
                + "lastName: " + this.lastName + "\n";
    }

    public String getProgram() {
        return this.program;
    }

    public Double getAvg() {
        return this.avg;
    }

    public String getLastName() {
        return this.lastName;
    }

    public int getYear() {
        return this.year;
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
        return this.program + " " + this.year + " " + this.avg + " " + this.lastName;
    }

    public String hashString() {
        return (this.program + this.year + this.lastName).toLowerCase();
    }

}
