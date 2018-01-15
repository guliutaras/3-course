package com.codebine;


import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;

public class App{
    private Chipher Chip=new Chipher();
    private JButton button1;
    private JPanel panelMain;
    private JTextArea textArea1;
    private JTextArea textArea2;
    private JButton button2;
    private JRadioButton RadioButton1;
    private JRadioButton RadioButton2;
    private JTextField textField1;
    private JButton файлЗашифроватьButton;
    private JButton файлРасшифроватьButton;

    public App() {
        button1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                if(RadioButton1.isSelected())
                {
                    if((textField1.getText()).isEmpty())
                    {
                        JOptionPane.showMessageDialog(null,"Ключи для шифра не задан!");
                        return;
                    }
                    if(Chip.isEngl((textArea1.getText()).charAt(0))) {textArea2.setText(Chip.enChipherVijen(textArea1.getText(),textField1.getText()));}
                    else {textArea2.setText(Chip.ruChipherVijen(textArea1.getText(),textField1.getText()));}
                }
                else
                {
                    textArea2.setText(Chip.ChipherSkital(textArea1.getText()));
                }
            }
        });
        button2.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                if(RadioButton1.isSelected())
                {
                    if((textField1.getText()).isEmpty())
                    {
                        JOptionPane.showMessageDialog(null,"Ключи для шифра не задан!");
                        return;
                    }
                    if(Chip.isEngl((textArea2.getText()).charAt(0))) {textArea1.setText(Chip.enDeChipherVijen(textArea2.getText(),textField1.getText()));}
                    else{textArea1.setText(Chip.ruDeChipherVijen(textArea2.getText(),textField1.getText()));}
                }
                else
                {
                    textArea1.setText(Chip.DeChipherSkital(textArea2.getText()));
                }

            }
        });
        файлЗашифроватьButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                JFileChooser fileopen= new JFileChooser();
                fileopen.setCurrentDirectory(new File("."));
                int ret =fileopen.showDialog(null,"Открыть файл");
                if(ret==JFileChooser.APPROVE_OPTION)
                {
                    File file = fileopen.getSelectedFile();
                    try{
                        char [] buff = new char [(int) file.length()];
                        Reader reader = new InputStreamReader(new FileInputStream(file), "Cp1251");
                        int c=reader.read(buff);
                        String encoded= new String(buff,0,c);
                        reader.close();
                        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file),"Cp1251"));
                    if(RadioButton1.isSelected())
                    {
                        if((textField1.getText()).isEmpty())
                        {
                            JOptionPane.showMessageDialog(null,"Ключи для шифра не задан!");
                            return;
                        }
                        if(Chip.isEngl((encoded).charAt(0)))
                        {
                            writer.write(Chip.enChipherVijen(encoded,textField1.getText()));

                        }
                        else {writer.write(Chip.ruChipherVijen(encoded,textField1.getText()));}
                    }
                    else
                    {
                        writer.write(Chip.ChipherSkital(encoded));
                    }
                        writer.flush();
                        writer.close();
                    }
                    catch (FileNotFoundException d){JOptionPane.showMessageDialog(null,"Файл не найден!");}
                    catch (IOException i){JOptionPane.showMessageDialog(null,"Некоректный поток чтения!");}

                    JOptionPane.showMessageDialog(null,"Шифрование завершено!");
                }

            }
        });
        файлРасшифроватьButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                JFileChooser fileopen= new JFileChooser();
                fileopen.setCurrentDirectory(new File("."));
                int ret =fileopen.showDialog(null,"Открыть файл");
                if(ret==JFileChooser.APPROVE_OPTION)
                {
                    File file = fileopen.getSelectedFile();
                    try{
                        char [] buff = new char [(int) file.length()];
                        Reader reader = new InputStreamReader(new FileInputStream(file), "Cp1251");
                        int c=reader.read(buff);
                        String encoded= new String(buff,0,c);
                        reader.close();
                        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file),"Cp1251"));
                        if(RadioButton1.isSelected())
                        {
                            if((textField1.getText()).isEmpty())
                            {
                                JOptionPane.showMessageDialog(null,"Ключи для шифра не задан!");
                                return;
                            }
                            if(Chip.isEngl((encoded).charAt(0)))
                            {
                                writer.write(Chip.enDeChipherVijen(encoded,textField1.getText()));

                            }
                            else {writer.write(Chip.ruDeChipherVijen(encoded,textField1.getText()));}
                        }
                        else
                        {
                            writer.write(Chip.DeChipherSkital(encoded));
                        }
                        writer.flush();
                        writer.close();
                    }
                    catch (FileNotFoundException d){JOptionPane.showMessageDialog(null,"Файл не найден!");}
                    catch (IOException i){JOptionPane.showMessageDialog(null,"Некоректный поток чтения!");}

                    JOptionPane.showMessageDialog(null,"Дешифрование завершено!");
                }

            }
        });
    }

    private void createUIComponents() {
        // TODO: place custom component creation code here
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("App");
        frame.setContentPane(new App().panelMain);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.pack();
        frame.setVisible(true);
    }
}
