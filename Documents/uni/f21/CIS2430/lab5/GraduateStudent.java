package lab5;

public class GraduateStudent extends Student {
    String supervisor;
    boolean isPhD;
    String undergraduateSchool;

    public GraduateStudent(String program, int year, String lastName, Double avg, Boolean isphd, String supervisor,
            String underGraduateSchool) throws Exception {
        super(program, year, lastName, avg);
        this.isPhD = isphd;
        this.supervisor = supervisor;
        this.undergraduateSchool = underGraduateSchool;
    }

    GraduateStudent() {
        supervisor = "";
        lastName = "";
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
                    + this.undergraduateSchool + "\n" + "lastName: " + this.lastName + "\n";
        } else if (this.isPhD == false) {
            // int tempMasters = 1;
            return "Program: " + this.program + "\n" + "Year: " + this.year + "\n" + "Average: " + this.avg + "\n"
                    + "Masters" + "\n" + "Supervisor: " + this.supervisor + "\n" + "undergraduateSchool: "
                    + this.undergraduateSchool + "\n" + "lastName: " + this.lastName + "\n";
        } else {
            return "Program: " + this.program + "\n" + "Year: " + this.year + "\n" + "Average: " + this.avg + "\n"
                    + "lastName: " + this.lastName + "\n";
        }
    }

    @Override
    public String printOutputFile() {
        if (this.isPhD == true) {
            int tempPhD = 1;
            return this.program + " " + this.year + " " + this.avg + " " + tempPhD + " " + this.supervisor + " "
                    + this.undergraduateSchool + " " + this.lastName;
        } else {
            int tempPhD = 0;
            return this.program + " " + this.year + " " + this.avg + " " + tempPhD + " " + this.supervisor + " "
                    + this.undergraduateSchool + " " + this.lastName;
        }
    }

    // public String askSuper() {

    // System.out.println("Enter supervisor: \n");
    // String supervisorInput = scan.nextLine();
    // setSupervisor(supervisorInput);
    // return this.supervisor;
    // }

    // public boolean askisPhd() {

    // System.out.println("isPhD? Enter 1 or 0: \n");
    // int phd = scan.nextInt();
    // while (phd != 0 && phd != 1) {
    // System.out.println("Error: Invalid Entry");
    // System.out.println("isPhD? Enter 1 or 0: \n");
    // phd = scan.nextInt();
    // }
    // if (phd == 1) {
    // this.isPhD = true;
    // setIsPhd(isPhD);
    // } else {
    // this.isPhD = false;
    // setIsPhd(isPhD);
    // }
    // return this.isPhD;
    // }

    // public String askUnder() {
    // System.out.println("Enter undergraduate school: \n");
    // String under = scan.nextLine();
    // setUndergraduateSchool(under);
    // return this.undergraduateSchool;
    // }

    public void setIsPhd(boolean isPhD) {
        this.isPhD = isPhD;
    }

    public void setSupervisor(String supervisor) {
        this.supervisor = supervisor;
    }

    public void setUndergraduateSchool(String undergraduateSchool) {
        this.undergraduateSchool = undergraduateSchool;
    }

    public boolean setIsPhd() {
        return this.isPhD;
    }

    public String setSupervisor() {
        return this.supervisor;
    }

    public String setUndergraduateSchool() {
        return this.undergraduateSchool;
    }
}
