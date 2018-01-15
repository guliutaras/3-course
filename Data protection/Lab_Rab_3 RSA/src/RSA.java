import java.math.BigInteger;
import java.util.Random;
/**
 * Created by Guliutaras on 31.10.2017.
 */
public class RSA {
    String charset = new String("-+#abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ \n1234567890!?%.,:;[]()");
    BigInteger OpenKey;
    BigInteger PrivatKey;
    BigInteger P;
    BigInteger Q;
    BigInteger Module;

    public boolean IsTheNumberSimple(BigInteger n) {
        if (n.compareTo(new BigInteger("2")) == -1)
            return false;
        if (n.compareTo(new BigInteger("2")) == 0)
            return true;
        for (long i = 2; i < n.longValue(); i++)
            if (n.longValue() % i == 0)
                return false;
        return true;
    }

    public boolean set(BigInteger p, BigInteger q) {
        if (IsTheNumberSimple(p) && IsTheNumberSimple(q)) {
            P = p;
            Q = q;
            BigInteger d;
            BigInteger phi = (P.subtract(BigInteger.ONE)).multiply(Q.subtract(BigInteger.ONE));
            Module = P.multiply(Q);
            Random rand = new Random();
            BigInteger e = new BigInteger(phi.bitLength(), rand);
            while (phi.gcd(e).intValue() > 1) e = e.add(new BigInteger("1"));
            d = e.modInverse(phi);
            OpenKey = e;
            PrivatKey = d;
            return true;
        }
        return false;
    }

    public BigInteger getPublicKey() {
        return OpenKey;
    }

    public BigInteger getPrivatKey() {
        return PrivatKey;
    }

    public String encrypt(String message, BigInteger OP, BigInteger M) throws Exception {

        String sb = new String();
        for (int i = 0; i < message.length(); i++) {
            sb = sb + (BigInteger.valueOf(charset.indexOf(message.charAt(i))).modPow(OP, M).toString(16)) + " ";
        }
        return sb;
    }

    public String decrypt(String encrypted, BigInteger PP, BigInteger M) throws Exception {

        String result=new String();
        BigInteger block;
        int i = 0;
        int j = 0;
        while (i < (encrypted.length() - 1)) {
            i++;
            if (encrypted.charAt(i) == ' ') {
                block = new BigInteger(encrypted.substring(j, i), 16);
                block = block.modPow(PP, M);
                result=result+charset.charAt(block.intValue());
                j = i + 1;
            }
        }
        return  result;
    }

}
