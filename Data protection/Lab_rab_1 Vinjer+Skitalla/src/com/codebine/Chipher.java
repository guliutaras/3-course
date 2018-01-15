package com.codebine;
import javax.swing.*;

/**
 * Created by Guliutaras on 17.10.2017.
 */
class Chipher {
    String strcharactersEN = new String("abcdefghijklmnopqrstuvwxyz");
    int Nen=26;
    String strcharactersRU= new String("абвгдеёжзийклмнопрстуфхцчшщъыьэюя");
    int Nru=33;
    int m=3;
    public boolean isEngl(char  letter)
    {
        return (letter>='a' && letter<='z')||(letter>='A' && letter<='Z');
    }
    public String ruChipherVijen(String text, String key)
    {
        char[] input=text.toLowerCase().toCharArray();
        char[] keyword=key.toLowerCase().toCharArray();

        String result=new String ();
        int keyword_index=0;

        for (int i=0; i<input.length; i++) {
            if(strcharactersRU.indexOf(input[i])==-1){result=result+input[i]; keyword_index++; if((keyword_index)==key.length()) keyword_index=0;  continue;}
            int c = (strcharactersRU.indexOf(input[i]) + strcharactersRU.indexOf(keyword[keyword_index])) % Nru;
            result = result + strcharactersRU.charAt(c);
            keyword_index++;
            if((keyword_index)==key.length()) keyword_index=0;
        }
        return result;
    }
    public String ruDeChipherVijen(String text, String key)
    {
        char[] input=text.toLowerCase().toCharArray();
        char[] keyword=key.toLowerCase().toCharArray();

        String result=new String ();
        int keyword_index=0;

        for (int i=0; i<input.length; i++) {
            if(strcharactersRU.indexOf(input[i])==-1){result=result+input[i]; keyword_index++; if((keyword_index)==key.length()) keyword_index=0;  continue;}
            int c = (strcharactersRU.indexOf(input[i]) + Nru - strcharactersRU.indexOf(keyword[keyword_index])) % Nru;
            result = result + strcharactersRU.charAt(c);
            keyword_index++;
            if((keyword_index)==key.length()) keyword_index=0;
        }
        return result;

    }
    public String enChipherVijen(String text, String key)
    {
        char[] input=text.toLowerCase().toCharArray();
        char[] keyword=key.toLowerCase().toCharArray();

        String result=new String ();
        int keyword_index=0;

        for (int i=0; i<input.length; i++) {
            if(strcharactersEN.indexOf(input[i])==-1){result=result+input[i]; keyword_index++; if((keyword_index)==key.length()) keyword_index=0;  continue;}
            int c = (strcharactersEN.indexOf(input[i]) + strcharactersEN.indexOf(keyword[keyword_index])) % Nen;
            result = result + strcharactersEN.charAt(c);
            keyword_index++;
            if((keyword_index)==key.length()) keyword_index=0;
        }
        return result;
    }
    public String enDeChipherVijen(String text, String key)
    {
            char[] input=text.toLowerCase().toCharArray();
            char[] keyword=key.toLowerCase().toCharArray();

            String result=new String ();
            int keyword_index=0;

            for (int i=0; i<input.length; i++) {
                if(strcharactersEN.indexOf(input[i])==-1){result=result+input[i]; keyword_index++; if((keyword_index)==key.length()) keyword_index=0;  continue;}
                int c = (strcharactersEN.indexOf(input[i])+Nen- strcharactersEN.indexOf(keyword[keyword_index])) % Nen;
                result = result + strcharactersEN.charAt(c);
                keyword_index++;
                if((keyword_index)==key.length()) keyword_index=0;
            }
            return result;
    }
    public String ChipherSkital(String Text)
    {
        int n=((Text.length()-1)/m)+1;
        String result=new String ();
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                try{result=result+Text.charAt(i+n*j);}
                catch (IndexOutOfBoundsException e){result=result+' ';}
            }
        }
        return result;

    }
    public String DeChipherSkital(String Text)
    {
        int n=((Text.length()-1)/m)+1;
        char[] s=new char[Text.length()];
        int number=0;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                s[i+n*j]=Text.charAt(number);
                number++;
            }
        }
        String result=new String(s);
        return result;

    }
}
