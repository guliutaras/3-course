package com.codebin;

import javax.swing.*;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;

/**
 * Created by Guliutaras on 21.10.2017.
 */
public class App {
    private JTextArea textArea1;
    private JTextArea textArea2;
    private JButton decryptButton;
    private JButton encryptButton;
    private JButton encryptFileButton;
    private JPanel panelMain;
    private JButton decryptFileButton;
    private JTextField textField1;


    public App() {
        decryptButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                AES aes= new AES();
                String key=textField1.getText();
                if(!(key.length() == 16 || key.length() == 24 || key.length() == 32)) {
                    JOptionPane.showMessageDialog(null, "Ключ для шифра задан неверно!");
                    return;
                }
                aes.setKey(aes.static_stringToByteArray(key));
                String data = new String(textArea1.getText());
                textArea2.setText(aes.Encrypt(data));
            }
        });
        encryptButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                AES aes= new AES();
                String key=textField1.getText();
                if(!(key.length() == 16 || key.length() == 24 || key.length() == 32||!(key.isEmpty()))) {
                    JOptionPane.showMessageDialog(null, "Ключ для шифра задан неверно!");
                    return;
                }
                aes.setKey(aes.static_stringToByteArray(key));
                String data = new String(textArea2.getText());
                textArea1.setText(aes.Decrypt(data));
            }
        });
        encryptFileButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                AES aes= new AES();
                String key=textField1.getText();
                if(!(key.length() == 16 || key.length() == 24 || key.length() == 32)) {
                    JOptionPane.showMessageDialog(null, "Ключ для шифра задан неверно!");
                    return;
                }
                aes.setKey(aes.static_stringToByteArray(key));
                JFileChooser fileopen = new JFileChooser();
                fileopen.setCurrentDirectory(new File("."));
                int ret = fileopen.showDialog(null, "Открыть файл");
                if (ret == JFileChooser.APPROVE_OPTION)
                {
                    File file = fileopen.getSelectedFile();
                    try
                    {
                        char[] buff = new char[(int) file.length()];
                        Reader reader = new InputStreamReader(new FileInputStream(file), "Cp866");
                        int c = reader.read(buff);
                        String data = new String(buff, 0, c);
                        reader.close();
                        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file), "Cp866"));
                        writer.write(aes.Encrypt(data));
                        writer.flush();
                        writer.close();
                    }
                    catch (FileNotFoundException d){JOptionPane.showMessageDialog(null,"Файл не найден!");}
                    catch (IOException i){JOptionPane.showMessageDialog(null,"Некоректный поток чтения!");}
                }
                JOptionPane.showMessageDialog(null,"Шифрование завершено!");
            }
        });
        decryptFileButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                AES aes= new AES();
                String key=textField1.getText();
                if(!(key.length() == 16 || key.length() == 24 || key.length() == 32)) {
                    JOptionPane.showMessageDialog(null, "Ключ для шифра задан неверно!");
                    return;
                }
                aes.setKey(aes.static_stringToByteArray(key));
                JFileChooser fileopen = new JFileChooser();
                fileopen.setCurrentDirectory(new File("."));
                int ret = fileopen.showDialog(null, "Открыть файл");
                if (ret == JFileChooser.APPROVE_OPTION)
                {
                    File file = fileopen.getSelectedFile();
                    try {
                        char[] buff = new char[(int) file.length()];
                        Reader reader = new InputStreamReader(new FileInputStream(file), "Cp866");
                        int c = reader.read(buff);
                        String data = new String(buff, 0, c);
                        reader.close();
                        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file), "Cp866"));
                        writer.write(aes.Decrypt(data));
                        writer.flush();
                        writer.close();
                    } catch (FileNotFoundException d) {
                        JOptionPane.showMessageDialog(null, "Файл не найден!");
                    } catch (IOException i) {
                        JOptionPane.showMessageDialog(null, "Некоректный поток чтения!");
                    }
                }
                JOptionPane.showMessageDialog(null,"Дешифрование завершено!");
            }
        });
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("AES");
        frame.setContentPane(new App().panelMain);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.pack();
        frame.setVisible(true);
    }

    private void createUIComponents() {
        // TODO: place custom component creation code here
    }
}
