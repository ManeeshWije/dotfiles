package lab3;

import java.util.*;
import java.io.*;

public class GraduateStudent extends Student {
    String supervisor;
    boolean isPhD;
    String undergraduateSchool;

    GraduateStudent() {
        supervisor = "";
        isPhD = false;
        undergraduateSchool = "";
        program = "";
        year = 0;
        avg = 0;
    }

    @Override
    public String toString() {
        if (this.isPhD == true) {
            // int tempPhd = 1;
            return "Program: " + this.program + "\n" + "Year: " + this.year + "\n" + "Average: " + this.avg + "\n"
                    + "PhD" + "\n" + "Supervisor: " + this.supervisor + "\n" + "undergraduateSchool: "
                    + this.undergraduateSchool + "\n";
        } else if (this.isPhD == false) {
            // int tempMasters = 1;
            return "Program: " + this.program + "\n" + "Year: " + this.year + "\n" + "Average: " + this.avg + "\n"
                    + "Masters" + "\n" + "Supervisor: " + this.supervisor + "\n" + "undergraduateSchool: "
                    + this.undergraduateSchool + "\n";
        } else {
            return "Program: " + this.program + "\n" + "Year: " + this.year + "\n" + "Average: " + this.avg + "\n";
        }
    }

    @Override
    public String printOutputFile() {
        if (this.isPhD == true) {
            int tempPhD = 1;
            return this.program + " " + this.year + " " + this.avg + " " + tempPhD + " " + this.supervisor + " "
                    + this.undergraduateSchool;
        } else {
            int tempPhD = 0;
            return this.program + " " + this.year + " " + this.avg + " " + tempPhD + " " + this.supervisor + " "
                    + this.undergraduateSchool;
        }
    }

    @Override
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
        System.out.println("isPhD? Enter 1 or 0: \n");
        int phd = scan.nextInt();
        while (phd != 0 && phd != 1) {
            System.out.println("Error: Invalid Entry");
            System.out.println("isPhD? Enter 1 or 0: \n");
            phd = scan.nextInt();
        }
        if (phd == 1) {
            this.isPhD = true;
            setIsPhd(isPhD);
        } else {
            this.isPhD = false;
            setIsPhd(isPhD);
        }
        scan.nextLine();
        System.out.println("Enter supervisor: \n");
        String supervisorInput = scan.nextLine();
        setSupervisor(supervisorInput);
        System.out.println("Enter undergraduate school: \n");
        String under = scan.nextLine();
        setUndergraduateSchool(under);
    }

    public void setIsPhd(boolean isPhD) {
        this.isPhD = isPhD;
    }

    public void setSupervisor(String supervisor) {
        this.supervisor = supervisor;
    }

    public void setUndergraduateSchool(String undergraduateSchool) {
        this.undergraduateSchool = undergraduateSchool;
    }
}
