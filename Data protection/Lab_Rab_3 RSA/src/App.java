import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.math.BigInteger;
import java.security.SecureRandom;
/**
 * Created by Guliutaras on 31.10.2017.
 */
public class App {
    private JPanel panelMain;
    private JTextArea textArea1;
    private JTextArea textArea2;
    private JButton EncryptButton;
    private JButton DecryptButton;
    private JTextArea textArea3;
    private JTextArea textArea4;
    private JButton FileEncryptButton;
    private JButton FileDecryptButton;
    private JTextField textField1;
    private JTextField textField2;
    private JButton сгенерироватьButton;
    private JButton вычеслитьКлючиButton;
    private JTextField textField3;

    public App() {
        EncryptButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e)
            {
               RSA rsa=new RSA();
               String nstr=textField3.getText();
               String okstr=textArea3.getText();
               if(!nstr.isEmpty()||!okstr.isEmpty())
               {
               BigInteger ok=new BigInteger(okstr);
               BigInteger n=new BigInteger(nstr);
                   try {
                       String msg= new String(textArea1.getText());
                       String Chipher = rsa.encrypt(msg,ok,n);
                       textArea2.setText(Chipher);
                   }
                   catch(Exception l) {
                       System.out.println("Exception" );
                       l.printStackTrace();
                   };
               }else{JOptionPane.showMessageDialog(null,"Вы ничего не ввели!");}

            }
        });
        DecryptButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                RSA rsa=new RSA();
                String nstr=textField3.getText();
                String pkstr=textArea4.getText();
                if(!nstr.isEmpty()||!pkstr.isEmpty())
                {
                    BigInteger n=new BigInteger(nstr);
                    BigInteger pk=new BigInteger(pkstr);
                        try {
                            String msg=new String (textArea2.getText());
                            String Input = rsa.decrypt(msg,pk,n);
                            textArea1.setText(Input);
                        }
                        catch(Exception l) {
                            System.out.println("Exception" );
                            l.printStackTrace();
                        };
                }else{JOptionPane.showMessageDialog(null,"Вы ничего не ввели!");}
            }
        });
        сгенерироватьButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                int N=32;
                RSA rsa =new RSA();
                SecureRandom S=new SecureRandom();
                BigInteger P= BigInteger.probablePrime(N/2,S);
                BigInteger Q= BigInteger.probablePrime(N/2,S);
                rsa.set(P,Q);
                textField1.setText(P.toString());
                textField2.setText(Q.toString());
                textField3.setText(P.multiply(Q).toString());
                textArea3.setText(String.valueOf(rsa.getPublicKey()));
                textArea4.setText(String.valueOf(rsa.getPrivatKey()));
            }
        });
        вычеслитьКлючиButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                RSA rsa =new RSA();
                try {
                BigInteger P= new BigInteger(textField1.getText());
                BigInteger Q= new BigInteger(textField2.getText());
                    if (rsa.IsTheNumberSimple(P) && rsa.IsTheNumberSimple(Q)) {
                        rsa.set(P, Q);
                        textArea3.setText(String.valueOf(rsa.getPublicKey()));
                        textArea4.setText(String.valueOf(rsa.getPrivatKey()));
                        textField3.setText(P.multiply(Q).toString());
                    } else {
                        JOptionPane.showMessageDialog(null, "Простые числа вовсе не простые!");
                    }
                }catch (NumberFormatException e1){JOptionPane.showMessageDialog(null, "Вы оставили пустое поле");}
            }
        });
        FileEncryptButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileopen= new JFileChooser();
                fileopen.setCurrentDirectory(new File("."));
                int ret =fileopen.showDialog(null,"Открыть файл");
                if(ret==JFileChooser.APPROVE_OPTION)
                {
                    File file = fileopen.getSelectedFile();
                    try{
                        char [] buff = new char [(int) file.length()];
                        Reader reader = new InputStreamReader(new FileInputStream(file), "UTF-8");
                        int c=reader.read(buff);
                        String encoded= new String(buff,0,c);
                        reader.close();
                        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file),"UTF-8"));
                        RSA rsa=new RSA();
                        String nstr=textField3.getText();
                        String okstr=textArea3.getText();
                        if(!nstr.isEmpty()||!okstr.isEmpty())
                        {
                            BigInteger ok=new BigInteger(okstr);
                            BigInteger n=new BigInteger(nstr);
                                try {
                                    String Chipher = rsa.encrypt(encoded,ok,n);
                                    writer.write(Chipher);
                                    writer.flush();
                                    writer.close();
                                }
                                catch(Exception l) {
                                    System.out.println("Exception" );
                                    l.printStackTrace();
                                };
                        }else{JOptionPane.showMessageDialog(null,"Вы ничего не ввели!");}
                    }
                    catch (FileNotFoundException d){JOptionPane.showMessageDialog(null,"Файл не найден!");}
                    catch (IOException i){JOptionPane.showMessageDialog(null,"Некоректный поток чтения!");}

                    JOptionPane.showMessageDialog(null,"Шифрование завершено!");
                }
            }
        });
        FileDecryptButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileopen= new JFileChooser();
                fileopen.setCurrentDirectory(new File("."));
                int ret =fileopen.showDialog(null,"Открыть файл");
                if(ret==JFileChooser.APPROVE_OPTION)
                {
                    File file = fileopen.getSelectedFile();
                    try{
                        char [] buff = new char [(int) file.length()];
                        Reader reader = new InputStreamReader(new FileInputStream(file), "UTF-8");
                        int c=reader.read(buff);
                        String encoded= new String(buff,0,c);
                        reader.close();
                        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file),"UTF-8"));
                        RSA rsa=new RSA();
                        String nstr=textField3.getText();
                        String pkstr=textArea4.getText();
                        if(!nstr.isEmpty()||!pkstr.isEmpty())
                        {
                            BigInteger n=new BigInteger(nstr);
                            BigInteger pk=new BigInteger(pkstr);
                                try {
                                    String Messege = rsa.decrypt(encoded,pk,n);
                                    writer.write(Messege);
                                    writer.flush();
                                    writer.close();
                                }
                                catch(Exception l) {
                                    System.out.println("Exception" );
                                    l.printStackTrace();
                                };
                        }else{JOptionPane.showMessageDialog(null,"Вы ничего не ввели!");}
                    }
                    catch (FileNotFoundException d){JOptionPane.showMessageDialog(null,"Файл не найден!");}
                    catch (IOException i){JOptionPane.showMessageDialog(null,"Некоректный поток чтения!");}

                    JOptionPane.showMessageDialog(null,"Расшифрование завершено!");
                }
            }
        });
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Lab_rab_3");
        frame.setContentPane(new App().panelMain);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.pack();
        frame.setVisible(true);
    }
}
