package lab5;

import javax.swing.JFrame;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.PrintWriter;
import java.util.*;
import javax.swing.*;

public class GUI extends JFrame implements ActionListener {
    // default sizes
    public static final int WIDTH = 700;
    public static final int HEIGHT = 1000;
    public static final int STRLENGTH = 10;
    public static final int LINES = 15;
    public static final int CHARS_PER_LINE = 30;

    ArrayList<Student> students = new ArrayList<Student>();
    ArrayList<Double> averages = new ArrayList<Double>();
    HashMap<String, Student> map = new HashMap<String, Student>();
    Student s = new Student();
    GraduateStudent g = new GraduateStudent();

    // components used
    private JTextArea outputText;
    private JComboBox<Boolean> isphd;
    private JLabel supervisorLabel;
    private JLabel undergraduateLabel;
    private JLabel isphdLabel;
    private JLabel welcome;
    private JLabel p;
    private JLabel y;
    private JLabel l;
    private JLabel gr;
    private JPanel outputPanel;
    private JPanel welcomePanel;
    private JPanel leftPanel;
    private JTextField programName;
    private JTextField studentYear;
    private JTextField studentLastName;
    private JTextField studentGrade;
    private JTextField supervisor;
    private JTextField undergradSchool;
    private JButton confirmStudent;
    private JButton resetStudent;
    private JButton confirm;
    private JButton confirmGradStudent;
    private JButton importFile;
    private JButton exportFile;
    private JButton searchBtn;
    private JPanel rightPanel;
    private JPanel upperPanel;

    public GUI() {
        super();
        // menu bar
        options();
        setTitle("Student Class Management System");
        setSize(WIDTH, HEIGHT);
        // using parent grid layout
        setLayout(new GridLayout(3, 1));

        upperPanel = new JPanel();
        upperPanel.setLayout(new GridLayout(1, 3));

        welcomePanel = new JPanel();
        welcomePanel.setLayout(new FlowLayout());
        welcome = new JLabel(
                "<html> Welcome to Student Class Management System. <br> Use the command menu in the top left to choose an option.<br> </html>");
        welcomePanel.add(welcome);
        add(welcomePanel);

        // grid layout for labels and text fields
        leftPanel = new JPanel();
        leftPanel.setLayout(new GridLayout(8, 2));

        // all labels here
        p = new JLabel("Enter Program");
        leftPanel.add(p);
        programName = new JTextField(STRLENGTH);
        leftPanel.add(programName);

        y = new JLabel("Enter Year");
        leftPanel.add(y);
        studentYear = new JTextField(STRLENGTH);
        leftPanel.add(studentYear);

        l = new JLabel("Enter LastName");
        leftPanel.add(l);
        studentLastName = new JTextField(STRLENGTH);
        leftPanel.add(studentLastName);

        gr = new JLabel("Enter Grade");
        leftPanel.add(gr);
        studentGrade = new JTextField(STRLENGTH);
        leftPanel.add(studentGrade);

        Boolean[] phd = { true, false };
        isphd = new JComboBox<Boolean>(phd);
        isphdLabel = new JLabel("Is Phd?");
        leftPanel.add(isphdLabel);
        leftPanel.add(isphd);

        supervisorLabel = new JLabel("Enter Supervisor");
        leftPanel.add(supervisorLabel);
        supervisor = new JTextField(STRLENGTH);
        leftPanel.add(supervisor);

        undergraduateLabel = new JLabel("Enter underGraduate School");
        leftPanel.add(undergraduateLabel);
        undergradSchool = new JTextField(STRLENGTH);
        leftPanel.add(undergradSchool);

        upperPanel.add(leftPanel);

        rightPanel = new JPanel();
        rightPanel.setLayout(new FlowLayout());

        // all buttons used
        confirmStudent = new JButton("CONFIRM STUDENT");
        confirmStudent.setForeground(Color.GREEN);
        confirmStudent.setPreferredSize(new Dimension(200, 50));
        confirmStudent.addActionListener(this);

        confirmGradStudent = new JButton("CONFIRM GRADSTUDENT");
        confirmGradStudent.setForeground(Color.GREEN);
        confirmGradStudent.setPreferredSize(new Dimension(200, 50));
        confirmGradStudent.addActionListener(this);

        confirm = new JButton("CONFIRM");
        confirm.setForeground(Color.GREEN);
        confirm.setPreferredSize(new Dimension(200, 50));
        confirm.addActionListener(this);

        resetStudent = new JButton("RESET");
        resetStudent.setForeground(Color.RED);
        resetStudent.setPreferredSize(new Dimension(200, 50));
        resetStudent.addActionListener(this);

        importFile = new JButton("IMPORT");
        importFile.setForeground(Color.GREEN);
        importFile.setPreferredSize(new Dimension(200, 50));
        importFile.addActionListener(this);

        exportFile = new JButton("EXPORT");
        exportFile.setForeground(Color.GREEN);
        exportFile.setPreferredSize(new Dimension(200, 50));
        exportFile.addActionListener(this);

        searchBtn = new JButton("SEARCH");
        searchBtn.setForeground(Color.GREEN);
        searchBtn.setPreferredSize(new Dimension(200, 50));
        searchBtn.addActionListener(this);

        // adding buttons to right panel
        rightPanel.add(resetStudent);
        rightPanel.add(confirmStudent);
        rightPanel.add(confirmGradStudent);
        rightPanel.add(confirm);
        rightPanel.add(importFile);
        rightPanel.add(exportFile);
        rightPanel.add(searchBtn);

        // adding right panel to upper panel
        upperPanel.add(rightPanel);

        // output panel
        outputPanel = new JPanel();
        JLabel outputLabel = new JLabel("Output:");
        outputText = new JTextArea(LINES, CHARS_PER_LINE);
        outputText.setEditable(false);
        outputText.setBackground(Color.WHITE);
        outputPanel.add(outputLabel);
        JScrollPane scrolledText = new JScrollPane(outputText);
        scrolledText.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        scrolledText.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        outputPanel.add(scrolledText);

        add(upperPanel);
        add(outputPanel);

        // setting false at first and will update when menu option is chosen
        upperPanel.setVisible(false);
        outputPanel.setVisible(false);

        // default closing
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    // menu items and menu bar
    public void options() {
        JMenu menu = new JMenu("Commands");
        JMenuItem newStudent = new JMenuItem("Enter info about a new Student");
        newStudent.addActionListener(this);
        menu.add(newStudent);

        JMenuItem newGrad = new JMenuItem("Enter info about a new GraduateStudent");
        newGrad.addActionListener(this);
        menu.add(newGrad);

        JMenuItem printOut = new JMenuItem("Print out all student info");
        printOut.addActionListener(this);
        menu.add(printOut);

        JMenuItem printAvg = new JMenuItem("Print total average and # of students");
        printAvg.addActionListener(this);
        menu.add(printAvg);

        JMenuItem searchProgram = new JMenuItem("Show info for specific program");
        searchProgram.addActionListener(this);
        menu.add(searchProgram);

        JMenuItem readInputFile = new JMenuItem("Read input file");
        readInputFile.addActionListener(this);
        menu.add(readInputFile);

        JMenuItem readOutputFile = new JMenuItem("File Data output");
        readOutputFile.addActionListener(this);
        menu.add(readOutputFile);

        JMenuItem search = new JMenuItem("Lookup via a HashMap key");
        search.addActionListener(this);
        menu.add(search);

        JMenuItem quit = new JMenuItem("End Program");
        quit.addActionListener(this);
        menu.add(quit);

        JMenuBar bar = new JMenuBar();
        bar.add(menu);

        setJMenuBar(bar);
    }

    // all functionality code based on what menu option, and what button is clicked
    @Override
    public void actionPerformed(ActionEvent e) {
        String str = e.getActionCommand();
        String studentButtonStr = e.getActionCommand();
        String gradStudentButtonStr = e.getActionCommand();
        String resetStr = e.getActionCommand();
        String confirmButtonStr = e.getActionCommand();
        String importButtonStr = e.getActionCommand();
        String exportButtonStr = e.getActionCommand();
        String searchBtnStr = e.getActionCommand();
        // entering new student
        if (str.equals("Enter info about a new Student")) {
            confirmGradStudent.setVisible(false);
            confirmStudent.setVisible(true);
            upperPanel.setVisible(true);
            outputPanel.setVisible(true);
            isphdLabel.setVisible(false);
            isphd.setVisible(false);
            supervisor.setVisible(false);
            supervisorLabel.setVisible(false);
            undergradSchool.setVisible(false);
            undergraduateLabel.setVisible(false);
            p.setVisible(true);
            p.setText("Program Name");
            y.setVisible(true);
            l.setVisible(true);
            gr.setVisible(true);
            programName.setVisible(true);
            studentYear.setVisible(true);
            studentGrade.setVisible(true);
            studentLastName.setVisible(true);
            confirm.setVisible(false);
            importFile.setVisible(false);
            exportFile.setVisible(false);
            searchBtn.setVisible(false);

            // adding student to arraylist
        } else if (studentButtonStr.equals("CONFIRM STUDENT")) {
            String inputProgram = programName.getText();
            String inputYear = studentYear.getText();
            String inputGrade = studentGrade.getText();
            String inputLastName = studentLastName.getText();
            boolean valid;
            do {
                valid = true;
                try {
                    Student st = new Student(inputProgram, Integer.parseInt(inputYear), inputLastName,
                            Double.parseDouble(inputGrade));
                    String key = st.hashString();
                    if (!map.containsKey(key)) {
                        students.add(st); // adding properties into arraylist
                        averages.add(st.getAvg()); // adding the average to seperate arraylist
                        map.put(key, st);
                        st = new Student();
                    } else {
                        students.remove(st);
                        outputText.append("Error: Key already exists\n");
                    }
                    System.out.println(map);
                } catch (Exception f) {
                    outputText.append(f.getMessage());
                    valid = false;
                }
            } while (!valid);
            // clearing all text fields
        } else if (resetStr.equals("RESET")) {
            programName.setText("");
            studentYear.setText("");
            studentGrade.setText("");
            studentLastName.setText("");
            supervisor.setText("");
            undergradSchool.setText("");
            outputText.setText("");
            // interface for entering graduate student
        } else if (str.equals("Enter info about a new GraduateStudent")) {
            upperPanel.setVisible(true);
            confirmGradStudent.setVisible(true);
            confirmStudent.setVisible(false);
            outputPanel.setVisible(true);
            isphdLabel.setVisible(true);
            isphd.setVisible(true);
            supervisor.setVisible(true);
            supervisorLabel.setVisible(true);
            undergradSchool.setVisible(true);
            undergraduateLabel.setVisible(true);
            p.setVisible(true);
            p.setText("Program Name");
            y.setVisible(true);
            l.setVisible(true);
            gr.setVisible(true);
            programName.setVisible(true);
            studentYear.setVisible(true);
            studentGrade.setVisible(true);
            studentLastName.setVisible(true);
            confirm.setVisible(false);
            importFile.setVisible(false);
            exportFile.setVisible(false);
            searchBtn.setVisible(false);
            // adding grad student
        } else if (gradStudentButtonStr.equals("CONFIRM GRADSTUDENT")) {
            String inputProgram = programName.getText();
            String inputYear = studentYear.getText();
            String inputGrade = studentGrade.getText();
            String inputLastName = studentLastName.getText();
            String inputSupervisor = supervisor.getText();
            String inputUndergrad = undergradSchool.getText();
            Boolean bool = (Boolean) isphd.getSelectedItem();
            boolean valid;
            do {
                valid = true;
                try {
                    GraduateStudent gt = new GraduateStudent(inputProgram, Integer.parseInt(inputYear), inputLastName,
                            Double.parseDouble(inputGrade), bool, inputSupervisor, inputUndergrad);
                    String key = gt.hashString();
                    if (!map.containsKey(key)) {
                        students.add(gt); // adding properties into arraylist
                        averages.add(gt.getAvg()); // adding the average to seperate arraylist
                        map.put(key, gt);
                        gt = new GraduateStudent();
                    } else {
                        students.remove(gt);
                        outputText.append("Error: Key already exists");
                    }
                    System.out.println(map);
                } catch (Exception f) {
                    outputText.append(f.getMessage());
                    valid = false;
                }
            } while (!valid);
            // printing out all student info into output text area
        } else if (str.equals("Print out all student info")) {
            outputPanel.setVisible(true);
            if (students.isEmpty()) {
                outputText.append("No info to show\n");
            }
            for (int i = 0; i < students.size(); i++) {
                outputText.append(students.get(i).toString());
            }
            // printing calculated averages and # of students into output text area
        } else if (str.equals("Print total average and # of students")) {
            outputPanel.setVisible(true);
            Student avg = new Student(); // new student object for averages
            outputText.append("Total Average Grade = " + avg.calculateAvg(averages) + "\n");
            outputText.append("Total # of Students = " + students.size() + "\n");
            // interface for showing a specific program info
        } else if (str.equals("Show info for specific program")) {
            upperPanel.setVisible(true);
            outputPanel.setVisible(true);
            leftPanel.setVisible(true);
            rightPanel.setVisible(true);
            studentYear.setVisible(false);
            y.setVisible(false);
            l.setVisible(false);
            gr.setVisible(false);
            studentGrade.setVisible(false);
            studentLastName.setVisible(false);
            supervisor.setVisible(false);
            supervisorLabel.setVisible(false);
            isphdLabel.setVisible(false);
            isphd.setVisible(false);
            undergradSchool.setVisible(false);
            undergraduateLabel.setVisible(false);
            confirmGradStudent.setVisible(false);
            confirmStudent.setVisible(false);
            confirm.setVisible(true);
            importFile.setVisible(false);
            exportFile.setVisible(false);
            programName.setVisible(true);
            searchBtn.setVisible(false);
            p.setText("Program Name");
            // printing specific program student info into output text area
        } else if (confirmButtonStr.equals("CONFIRM")) {
            String inputProgram = programName.getText();
            // in the arraylist, if the index for program equals inputted program,
            // then use print method on that index
            if (students.isEmpty()) {
                outputText.append("List is empty\n");
            }
            for (int i = 0; i < students.size(); i++) {
                if (students.get(i).getProgram().equals(inputProgram)) {
                    outputText.append(students.get(i).toString());
                } else {
                    outputText.append("No info to show for that program\n");
                }
            }
            // interface for reading input file
        } else if (str.equals("Read input file")) {
            upperPanel.setVisible(true);
            outputPanel.setVisible(true);
            leftPanel.setVisible(true);
            rightPanel.setVisible(true);
            studentYear.setVisible(false);
            y.setVisible(false);
            l.setVisible(false);
            gr.setVisible(false);
            studentGrade.setVisible(false);
            studentLastName.setVisible(false);
            supervisor.setVisible(false);
            supervisorLabel.setVisible(false);
            isphdLabel.setVisible(false);
            isphd.setVisible(false);
            undergradSchool.setVisible(false);
            undergraduateLabel.setVisible(false);
            confirmGradStudent.setVisible(false);
            confirmStudent.setVisible(false);
            confirm.setVisible(false);
            programName.setVisible(true);
            p.setText("Name of Input File");
            rightPanel.add(importFile);
            exportFile.setVisible(false);
            confirmGradStudent.setVisible(false);
            confirmStudent.setVisible(false);
            importFile.setVisible(true);
            searchBtn.setVisible(false);
            // reading file and importing when button is pressed
        } else if (importButtonStr.equals("IMPORT")) {
            String inputFileStr = programName.getText();
            try {
                String fileName = inputFileStr;
                File f = new File(fileName);
                Scanner inputFile = new Scanner(f);
                while (inputFile.hasNextLine()) {
                    String read = inputFile.nextLine();
                    String[] contents = read.split(" ");
                    if (contents.length == 4) { // we know its a regular student
                        Student st = new Student(contents[0], Integer.parseInt(contents[1]), contents[3],
                                Double.parseDouble(contents[2]));
                        st.setProgram(contents[0]);
                        st.setYear(Integer.parseInt(contents[1]));
                        st.setAvg(Double.parseDouble(contents[2]));
                        st.setLastName(contents[3]);
                        String key = st.hashString();
                        if (!map.containsKey(key)) {
                            students.add(st);
                            averages.add(st.getAvg());
                            map.put(key, st);
                            outputText.append("Imported successfully\n");
                            st = new Student();
                        } else {
                            students.remove(st);
                            outputText.append("Error: Key already exists\n");
                        }
                    } else if (contents.length == 7) { // we know its a graduate student
                        GraduateStudent gt = new GraduateStudent(contents[0], Integer.parseInt(contents[1]),
                                contents[6], Double.parseDouble(contents[2]), Boolean.parseBoolean(contents[4]),
                                contents[3], contents[5]);
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
                            outputText.append("Imported successfully\n");
                            gt = new GraduateStudent();
                        } else {
                            students.remove(gt);
                            outputText.append("Error: Key already exists\n");
                        }
                    }
                }
                inputFile.close();
            } catch (Exception f) {
                // i do getmessage but also if the file doesnt exist this message will also
                // appear
                outputText.append(f.getMessage());
            }
            // interface for outputting info to a file
        } else if (str.equals("File Data output")) {
            upperPanel.setVisible(true);
            outputPanel.setVisible(true);
            leftPanel.setVisible(true);
            rightPanel.setVisible(true);
            studentYear.setVisible(false);
            y.setVisible(false);
            l.setVisible(false);
            gr.setVisible(false);
            studentGrade.setVisible(false);
            studentLastName.setVisible(false);
            supervisor.setVisible(false);
            supervisorLabel.setVisible(false);
            isphdLabel.setVisible(false);
            isphd.setVisible(false);
            undergradSchool.setVisible(false);
            undergraduateLabel.setVisible(false);
            confirmGradStudent.setVisible(false);
            confirmStudent.setVisible(false);
            confirm.setVisible(false);
            programName.setVisible(true);
            p.setText("Name of Output File");
            rightPanel.add(importFile);
            exportFile.setVisible(true);
            confirmGradStudent.setVisible(false);
            confirmStudent.setVisible(false);
            importFile.setVisible(false);
            searchBtn.setVisible(false);
            // exporting file when button is clicked
        } else if (exportButtonStr.equals("EXPORT")) {
            String outputFileInput = programName.getText();
            try {
                String outputFile = outputFileInput;
                PrintWriter fileWriter = new PrintWriter(outputFile, "UTF-8");
                for (int i = 0; i < students.size(); i++) {
                    fileWriter.println(students.get(i).printOutputFile());
                }
                outputText.append("Data outputted successfully\n");
                fileWriter.close();
            } catch (Exception f) {
                outputText.append(f.getMessage());
            }
            // interface for searching via a hashmap key
        } else if (str.equals("Lookup via a HashMap key")) {
            upperPanel.setVisible(true);
            outputPanel.setVisible(true);
            leftPanel.setVisible(true);
            rightPanel.setVisible(true);
            studentYear.setVisible(false);
            y.setVisible(false);
            l.setVisible(false);
            gr.setVisible(false);
            studentGrade.setVisible(false);
            studentLastName.setVisible(false);
            supervisor.setVisible(false);
            supervisorLabel.setVisible(false);
            isphdLabel.setVisible(false);
            isphd.setVisible(false);
            undergradSchool.setVisible(false);
            undergraduateLabel.setVisible(false);
            confirmGradStudent.setVisible(false);
            confirmStudent.setVisible(false);
            confirm.setVisible(false);
            programName.setVisible(true);
            p.setText("Enter Hashmap Key");
            rightPanel.add(importFile);
            searchBtn.setVisible(true);
            exportFile.setVisible(false);
            confirmGradStudent.setVisible(false);
            confirmStudent.setVisible(false);
            importFile.setVisible(false);
            // when search button is clicked, output hashmap result
        } else if (searchBtnStr.equals("SEARCH")) {
            String searchInput = programName.getText();
            String search = searchInput;
            if (map.containsKey(search)) {
                outputText.append(map.get(search).toString());
            } else {
                outputText.append("Invalid search key or no info for key\n");
            }
            // end program using menu option
        } else if (str.equals("End Program")) {
            System.exit(0);
            // if any option doesnt run, error occured
        } else {
            System.out.println("Unexpected error");
        }
    }
}
