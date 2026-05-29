import javax.swing.*;
import java.awt.*;

public class StudentRegistrationApp extends JFrame {

    private JTextField txtId, txtName;
    private JRadioButton rbMale, rbFemale;
    private JComboBox<String> cbCourse;
    private JTextArea taRecords;
    
    public StudentRegistrationApp() {
        setTitle("Student Registration");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Menu Bar
        JMenuBar menuBar = new JMenuBar();
        JMenu menuFile = new JMenu("File");
        JMenuItem itemExit = new JMenuItem("Exit");
        menuFile.add(itemExit);
        menuBar.add(menuFile);
        setJMenuBar(menuBar);

        // Input Panel
        JPanel inputPanel = new JPanel(new GridLayout(4, 2));
        inputPanel.add(new JLabel("ID:"));
        txtId = new JTextField();
        inputPanel.add(txtId);

        inputPanel.add(new JLabel("Name:"));
        txtName = new JTextField();
        inputPanel.add(txtName);

        inputPanel.add(new JLabel("Gender:"));
        JPanel genderPanel = new JPanel();
        rbMale = new JRadioButton("Male");
        rbFemale = new JRadioButton("Female");
        ButtonGroup bg = new ButtonGroup();
        bg.add(rbMale); bg.add(rbFemale);
        genderPanel.add(rbMale); genderPanel.add(rbFemale);
        inputPanel.add(genderPanel);

        inputPanel.add(new JLabel("Course:"));
        cbCourse = new JComboBox<>(new String[]{"Computer Science", "IT", "Engineering"});
        inputPanel.add(cbCourse);
        
        // Button Panel
        JPanel btnPanel = new JPanel();
        JButton btnSave = new JButton("Save");
        JButton btnClear = new JButton("Clear");
        btnPanel.add(btnSave);
        btnPanel.add(btnClear);

        // Output Panel
        taRecords = new JTextArea();
        JScrollPane scrollPane = new JScrollPane(taRecords);

        // Add to Frame
        add(inputPanel, BorderLayout.NORTH);
        add(btnPanel, BorderLayout.CENTER);
        add(scrollPane, BorderLayout.SOUTH);

        // Actions
        btnSave.addActionListener(e -> saveAction());
        btnClear.addActionListener(e -> clearAction());
        itemExit.addActionListener(e -> System.exit(0));
    }

    private void saveAction() {
        String id = txtId.getText();
        String name = txtName.getText();
        if(id.isEmpty() || name.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Fields cannot be empty", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }
        // In reality, save to MySQL DB via JDBC here...
        String gender = rbMale.isSelected() ? "Male" : "Female";
        String course = cbCourse.getSelectedItem().toString();
        taRecords.append(id + " | " + name + " | " + gender + " | " + course + "\n");
        JOptionPane.showMessageDialog(this, "Saved Successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
    }

    private void clearAction() {
        txtId.setText("");
        txtName.setText("");
        rbMale.setSelected(false);
        rbFemale.setSelected(false);
        cbCourse.setSelectedIndex(0);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new StudentRegistrationApp().setVisible(true));
    }
}
