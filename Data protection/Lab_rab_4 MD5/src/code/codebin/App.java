package code.codebin;

import javax.swing.text.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.io.*;
import java.text.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.BasicFileAttributes;
/**
 * Created by Guliutaras on 16.11.2017.
 */
public class App {

    private JPanel mainPanel;
    private JTextArea textArea1;
    private JTextArea textArea2;
    private JButton вычеслитьХешСуммуButton;
    private JButton проверитьКоректностьButton;
    private JFormattedTextField FormattedTextField;
    private JButton Button;
    private JButton проверитьЕЦПДокументаButton;


    public App() {

        FormattedTextField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                try {
                    MaskFormatter dateMask = new MaskFormatter("##.##.####");
                    dateMask.install(FormattedTextField);
                } catch (ParseException ex) {}
            }
        });

        вычеслитьХешСуммуButton.addActionListener(new ActionListener() {
            @Override

            public void actionPerformed(ActionEvent e) {
                String Mes=textArea1.getText();
                String Data=FormattedTextField.getText();
                if(Mes.isEmpty()){JOptionPane.showMessageDialog(null, "Строка пуста!"); return;}
                if(!isValid(Data,"dd.MM.yyyy")){JOptionPane.showMessageDialog(null, "Неверная дата!"); return;}
                Mes=Mes+" "+Data;
                MD5 m=new MD5();
                String res = m.Encode(Mes);
                textArea2.setText(res);
                MD5.reset();
            }

            private boolean isValid(String value, String datePattern) {

                if (value == null || datePattern == null || datePattern.length() <= 0) {
                    return false;
                }
                SimpleDateFormat formatter = new SimpleDateFormat(datePattern);
                formatter.setLenient(false);
                try {
                    formatter.parse(value);
                } catch (ParseException e) {
                    return false;
                }
                return true;
            }
        });
        проверитьКоректностьButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String res1=textArea2.getText();
                String Mes=textArea1.getText();
                String Data=FormattedTextField.getText();
                if(Mes.isEmpty()||res1.isEmpty()){JOptionPane.showMessageDialog(null, "Строка пуста!"); return;}
                if(!isValid(Data,"dd.MM.yyyy")){JOptionPane.showMessageDialog(null, "Неверная дата!"); return;}
                Mes=Mes+" "+Data;
                MD5 m=new MD5();
                String res = m.Encode(Mes);
                if(res.equals(res1)){JOptionPane.showMessageDialog(null, "Хеш значения совпадают.");}
                else{JOptionPane.showMessageDialog(null, "Хеш значения не совпадают. Текст или дата были изменены!");}
                MD5.reset();
            }

            private boolean isValid(String value, String datePattern) {

                if (value == null || datePattern == null || datePattern.length() <= 0) {
                    return false;
                }
                SimpleDateFormat formatter = new SimpleDateFormat(datePattern);
                formatter.setLenient(false);
                try {
                    formatter.parse(value);
                } catch (ParseException e) {
                    return false;
                }
                return true;
            }
        });
        Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileopen = new JFileChooser();
                fileopen.setCurrentDirectory(new File("."));
                int ret = fileopen.showDialog(null, "Открыть файл");
                if (ret == JFileChooser.APPROVE_OPTION)
                {
                    File file = fileopen.getSelectedFile();
                    try
                    {
                        char[] buff = new char[(int) file.length()];
                        Reader reader = new InputStreamReader(new FileInputStream(file),"Cp1251");
                        int c = reader.read(buff);
                        String data = new String(buff, 0, c);
                        reader.close();
                        Path p = file.toPath();
                        BasicFileAttributes attr = Files.readAttributes(p, BasicFileAttributes.class);
                        String sysData=new String(""+attr.creationTime());
                        String Data=new String(""+sysData.charAt(8)+sysData.charAt(9)+"."+sysData.charAt(5)+sysData.charAt(6)+"."+sysData.charAt(0)+sysData.charAt(1)+sysData.charAt(2)+sysData.charAt(3));
                        if(data.isEmpty()){JOptionPane.showMessageDialog(null, "В файле нечего шифровать!"); return;}
                        System.out.println(data+" "+Data);
                        MD5 m= new MD5();
                        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file,true)));
                        writer.newLine();
                        writer.write(m.Encode(data+" "+Data));
                        MD5.reset();
                        writer.flush();
                        writer.close();
                    }
                    catch (FileNotFoundException d){JOptionPane.showMessageDialog(null,"Файл не найден!");}
                    catch (IOException i){JOptionPane.showMessageDialog(null,"Некоректный поток чтения!");}
                }
                JOptionPane.showMessageDialog(null,"Документ подписан дайджестом!");
            }
        });
        проверитьЕЦПДокументаButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileopen = new JFileChooser();
                fileopen.setCurrentDirectory(new File("."));
                int ret = fileopen.showDialog(null, "Открыть файл");
                if (ret == JFileChooser.APPROVE_OPTION)
                {
                    File file = fileopen.getSelectedFile();
                    try
                    {
                        char[] buff = new char[(int) file.length()];
                        Reader reader = new InputStreamReader(new FileInputStream(file),"Cp1251");
                        int c = reader.read(buff);
                        System.out.println(c);
                        String data = new String(buff,0,c);
                        String res1 =data.substring(data.length()-32);
                        System.out.println(data.length());
                        data=data.substring(0,data.length()-res1.length()-2);
                        System.out.println(data);
                        reader.close();
                        Path p = file.toPath();
                        BasicFileAttributes attr = Files.readAttributes(p, BasicFileAttributes.class);
                        String sysData=new String(""+attr.creationTime());
                        String Data=new String(""+sysData.charAt(8)+sysData.charAt(9)+"."+sysData.charAt(5)+sysData.charAt(6)+"."+sysData.charAt(0)+sysData.charAt(1)+sysData.charAt(2)+sysData.charAt(3));
                        if(data.isEmpty()){JOptionPane.showMessageDialog(null, "В файле нечего шифровать!"); return;}
                        System.out.println(data+" "+Data);
                        MD5 m= new MD5();
                        String res=m.Encode(data+" "+Data);
                        if(res1.equals(res)){JOptionPane.showMessageDialog(null, "Хеш значения совпадают.");}
                        else{JOptionPane.showMessageDialog(null, "Хеш значения не совпадают. Текст или дата были изменены!");}
                        MD5.reset();
                    }
                    catch (FileNotFoundException d){JOptionPane.showMessageDialog(null,"Файл не найден!");}
                    catch (IOException i){JOptionPane.showMessageDialog(null,"Некоректный поток чтения!");}
                }
            }
        });
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Lab_rab_4");
        frame.setContentPane(new App().mainPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.pack();
        frame.setVisible(true);
    }
}
