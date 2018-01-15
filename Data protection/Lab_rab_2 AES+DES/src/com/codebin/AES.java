package com.codebin;

/**
 * Created by Guliutaras on 28.10.2017.
 */
import java.nio.CharBuffer;
import java.nio.charset.Charset;
import java.nio.ByteBuffer;
class AES {

    /** Статические данные алгоритма*/
    public static final int
            BLOCK_SIZE = 16;    // AES длина блока

    // Определение основных характеристик для установления ключа
    /** Количество раундов. */
    int numRounds;
    /** Ключи раундов зашифрования. */
    byte[][] Ke;
    /** Ключи раундов расшифрования */
    byte[][] Kd;

    /** AES таблица замен использиванная для шифрования
     *  Значения таблици переведены в десятичные для удобной спецификации.
     */
    static final byte[] S = {
            99, 124, 119, 123, -14, 107, 111, -59, 48, 1, 103, 43, -2, -41, -85, 118,
            -54, -126, -55, 125, -6, 89, 71, -16, -83, -44, -94, -81, -100, -92, 114, -64,
            -73, -3, -109, 38, 54, 63, -9, -52, 52, -91, -27, -15, 113, -40, 49, 21,
            4, -57, 35, -61, 24, -106, 5, -102, 7, 18, -128, -30, -21, 39, -78, 117,
            9, -125, 44, 26, 27, 110, 90, -96, 82, 59, -42, -77, 41, -29, 47, -124,
            83, -47, 0, -19, 32, -4, -79, 91, 106, -53, -66, 57, 74, 76, 88, -49,
            -48, -17, -86, -5, 67, 77, 51, -123, 69, -7, 2, 127, 80, 60, -97, -88,
            81, -93, 64, -113, -110, -99, 56, -11, -68, -74, -38, 33, 16, -1, -13, -46,
            -51, 12, 19, -20, 95, -105, 68, 23, -60, -89, 126, 61, 100, 93, 25, 115,
            96, -127, 79, -36, 34, 42, -112, -120, 70, -18, -72, 20, -34, 94, 11, -37,
            -32, 50, 58, 10, 73, 6, 36, 92, -62, -45, -84, 98, -111, -107, -28, 121,
            -25, -56, 55, 109, -115, -43, 78, -87, 108, 86, -12, -22, 101, 122, -82, 8,
            -70, 120, 37, 46, 28, -90, -76, -58, -24, -35, 116, 31, 75, -67, -117, -118,
            112, 62, -75, 102, 72, 3, -10, 14, 97, 53, 87, -71, -122, -63, 29, -98,
            -31, -8, -104, 17, 105, -39, -114, -108, -101, 30, -121, -23, -50, 85, 40, -33,
            -116, -95, -119, 13, -65, -26, 66, 104, 65, -103, 45, 15, -80, 84, -69, 22 };

    /** AES таблица замен использиванная для расшифрования S-box.
     *  Значения таблици переведены в десятичные для удобной спецификации.
     */
    static final byte[] Si = {
            82, 9, 106, -43, 48, 54, -91, 56, -65, 64, -93, -98, -127, -13, -41, -5,
            124, -29, 57, -126, -101, 47, -1, -121, 52, -114, 67, 68, -60, -34, -23, -53,
            84, 123, -108, 50, -90, -62, 35, 61, -18, 76, -107, 11, 66, -6, -61, 78,
            8, 46, -95, 102, 40, -39, 36, -78, 118, 91, -94, 73, 109, -117, -47, 37,
            114, -8, -10, 100, -122, 104, -104, 22, -44, -92, 92, -52, 93, 101, -74, -110,
            108, 112, 72, 80, -3, -19, -71, -38, 94, 21, 70, 87, -89, -115, -99, -124,
            -112, -40, -85, 0, -116, -68, -45, 10, -9, -28, 88, 5, -72, -77, 69, 6,
            -48, 44, 30, -113, -54, 63, 15, 2, -63, -81, -67, 3, 1, 19, -118, 107,
            58, -111, 17, 65, 79, 103, -36, -22, -105, -14, -49, -50, -16, -76, -26, 115,
            -106, -84, 116, 34, -25, -83, 53, -123, -30, -7, 55, -24, 28, 117, -33, 110,
            71, -15, 26, 113, 29, 41, -59, -119, 111, -73, 98, 14, -86, 24, -66, 27,
            -4, 86, 62, 75, -58, -46, 121, 32, -102, -37, -64, -2, 120, -51, 90, -12,
            31, -35, -88, 51, -120, 7, -57, 49, -79, 18, 16, 89, 39, -128, -20, 95,
            96, 81, 127, -87, 25, -75, 74, 13, 45, -27, 122, -97, -109, -55, -100, -17,
            -96, -32, 59, 77, -82, 42, -11, -80, -56, -21, -69, 60, -125, 83, -103, 97,
            23, 43, 4, 126, -70, 119, -42, 38, -31, 105, 20, 99, 85, 33, 12, 125 };

    /** AES постоянный масив для каждого раунда
     *  Значения таблици переведены в десятичные для удобной спецификации.
     *  0- инициализация таблици 1- первое состояние
     */
    static final byte[] rcon = {
            0,
            1, 2, 4, 8, 16, 32,
            64, -128, 27, 54, 108, -40,
            -85, 77, -102, 47, 94, -68,
            99, -58, -105, 53, 106, -44,
            -77, 125, -6, -17, -59, -111 };

    /** Внутренние статические данные нужные AES */
    public static final int
            COL_SIZE = 4,                // глубина кажой колонки в переменнойй состояния
            NUM_COLS = BLOCK_SIZE / COL_SIZE;    // количество колонок

    /** Сдвиги кажой колонки для операции ShiftRows */
    static final int[] row_shift = {0, 1, 2, 3};

    /* alog специальная таблица для ускорения побидового умножения */
    static final int[] alog = new int[256];
    /* log специальная таблица для ускорения побидового умножения  */
    static final int[] log =  new int[256];

    /** инициализация log и alog
     */
    static {
        int i, j;
        alog[0] = 1;
        for (i = 1; i < 256; i++) {
            j = (alog[i-1] << 1) ^ alog[i-1];
            if ((j & 0x100) != 0) j ^= 0x11B;
            alog[i] = j;
        }
        for (i = 1; i < 255; i++) log[alog[i]] = i;
    }

    /** Конструктор */
    public AES() {}

    /** количество раундов в зависимости от ключа */
    public static int getRounds (int keySize) {
        switch (keySize) {
            case 16:    // 16 байт = 128 битный ключ
                return 10;
            case 24:    // 24 байта = 192 битный ключ
                return 12;
            default:    // 32 байт = 256 битный ключ
                return 14;
        }
    }

    /** умножение а и б по полиному GF(2^8). */
    static final int mul (int a, int b) {
        return (a != 0 && b != 0) ?
                alog[(log[a & 0xFF] + log[b & 0xFF]) % 255] :
                0;
    }

    public byte[] encrypt(byte[] plain) {
        // определяем рабочие переменые
        byte [] a = new byte[BLOCK_SIZE];    // AES переменная состояния
        byte [] ta = new byte[BLOCK_SIZE];    // AES временная переменная состояния
        byte [] Ker;                // ключи шифрования конкретного раунда
        int    i, j, k, row, col;


        // проверяем дурные аргументы
        if (plain == null)
            throw new IllegalArgumentException("Empty plaintext");//нет исходного текста
        if (plain.length != BLOCK_SIZE)
            throw new IllegalArgumentException("Incorrect plaintext length");//некоректная длинна исходного текста

        // копирует исходный текст в таблице состояний и инициализируем AddRoundKey(state)
        Ker = Ke[0];
        for (i = 0; i < BLOCK_SIZE; i++)    a[i] = (byte)(plain[i] ^ Ker[i]);
        // для каждого раунда кроме последнего применяем такие трансформации
        for (int r = 1; r < numRounds; r++) {
            Ker = Ke[r];            // берем ключ ранунда

            // SubBytes(state) неленеяная замена временной переменной
            for (i = 0; i < BLOCK_SIZE; i++) ta[i] = S[a[i] & 0xFF];

            // ShiftRows(state) сдвиг строк для переменной сосотояния
            for (i = 0; i < BLOCK_SIZE; i++) {
                row = i % COL_SIZE;
                k = (i + (row_shift[row] * COL_SIZE)) % BLOCK_SIZE;    // берем сдвиг с row_shift
                a[i] = ta[k];
            }
            // MixColumns(state) смешивнаие данных для получение новых столбцов временной переменной
            // Для умножение используеться функция ускорения
            for (col = 0; col < NUM_COLS; col++) {
                i = col * COL_SIZE;        // start index for this col
                ta[i]   = (byte)(mul(2,a[i]) ^ mul(3,a[i+1]) ^ a[i+2] ^ a[i+3]);
                ta[i+1] = (byte)(a[i] ^ mul(2,a[i+1]) ^ mul(3,a[i+2]) ^ a[i+3]);
                ta[i+2] = (byte)(a[i] ^ a[i+1] ^ mul(2,a[i+2]) ^ mul(3,a[i+3]));
                ta[i+3] = (byte)(mul(3,a[i]) ^ a[i+1] ^ a[i+2] ^ mul(2,a[i+3]));
            }

            // AddRoundKey(state) ключ раунда XOR-иться с временной переменнойи все записываеться в переменную сосотояния
            for (i = 0; i < BLOCK_SIZE; i++)    a[i] = (byte)(ta[i] ^ Ker[i]);
        }

        // последний раунд без MixColumns
        Ker = Ke[numRounds];            // берем ключ раунда

        // SubBytes(state) неленеяная замена временной переменной
        for (i = 0; i < BLOCK_SIZE; i++) a[i] = S[a[i] & 0xFF];

        // ShiftRows(state) сдвиг строк для переменной сосотояния
        for (i = 0; i < BLOCK_SIZE; i++) {
            row = i % COL_SIZE;
            k = (i + (row_shift[row] * COL_SIZE)) % BLOCK_SIZE;    // берем сдвиг с row_shift
            ta[i] = a[k];
        }

        // AddRoundKey(state) ключ раунда XOR-иться с временной переменнойи все записываеться в переменную сосотояния
        for (i = 0; i < BLOCK_SIZE; i++)    a[i] = (byte)(ta[i] ^ Ker[i]);
        return (a);
    }


    public byte[] decrypt(byte[] cipher) {
        // определяем рабочие переменые
        byte [] a = new byte[BLOCK_SIZE];    // AES переменная состояния
        byte [] ta = new byte[BLOCK_SIZE];    // AES временная переменная состояния
        byte [] Kdr;                // ключи расшифрования конкретного раунда
        int    i, j, k, row, col;


        // проверяем на дурные аргументы
        if (cipher == null)
            throw new IllegalArgumentException("Empty ciphertext");
        if (cipher.length != BLOCK_SIZE)
            throw new IllegalArgumentException("Incorrect ciphertext length");

        // копирует исходный текст в таблице состояний и инициализируем AddRoundKey(state) и ключ расшифровки
        Kdr = Kd[0];
        for (i = 0; i < BLOCK_SIZE; i++)    a[i] = (byte)(cipher[i] ^ Kdr[i]);

        // для каждого раунда кроме последнего применяем такие трансформации
        for (int r = 1; r < numRounds; r++) {
            Kdr = Kd[r];            // get session keys for this round

            // InvShiftRows(state) обратное смещение строк
            for (i = 0; i < BLOCK_SIZE; i++) {
                row = i % COL_SIZE;
                // get shifted byte index
                k = (i + BLOCK_SIZE - (row_shift[row] * COL_SIZE)) % BLOCK_SIZE;
                ta[i] = a[k];
            }

            // InvSubBytes(state) обратная замена с обратным S-box
            for (i = 0; i < BLOCK_SIZE; i++) a[i] = Si[ta[i] & 0xFF];

            // AddRoundKey(state) складываем по модулю 2
            for (i = 0; i < BLOCK_SIZE; i++)    ta[i] = (byte)(a[i] ^ Kdr[i]);

            // InvMixColumns(state) обратное смешывание данных
            for (col = 0; col < NUM_COLS; col++) {
                i = col * COL_SIZE;        // start index for this col
                a[i]   = (byte)(mul(0x0e,ta[i]) ^ mul(0x0b,ta[i+1]) ^ mul(0x0d,ta[i+2]) ^ mul(0x09,ta[i+3]));
                a[i+1] = (byte)(mul(0x09,ta[i]) ^ mul(0x0e,ta[i+1]) ^ mul(0x0b,ta[i+2]) ^ mul(0x0d,ta[i+3]));
                a[i+2] = (byte)(mul(0x0d,ta[i]) ^ mul(0x09,ta[i+1]) ^ mul(0x0e,ta[i+2]) ^ mul(0x0b,ta[i+3]));
                a[i+3] = (byte)(mul(0x0b,ta[i]) ^ mul(0x0d,ta[i+1]) ^ mul(0x09,ta[i+2]) ^ mul(0x0e,ta[i+3]));
            }
        }

        // последний раунд без смешывания InvMixColumns(state)
        Kdr = Kd[numRounds];

        // InvSubBytes(state) обратная замена с обратным S-box
        for (i = 0; i < BLOCK_SIZE; i++) {
            row = i % COL_SIZE;
            k = (i + BLOCK_SIZE - (row_shift[row] * COL_SIZE)) % BLOCK_SIZE;
            ta[i] = a[k];
        }

        // InvSubBytes(state) обратная замена с обратным S-box
        for (i = 0; i < BLOCK_SIZE; i++) ta[i] = Si[ta[i] & 0xFF];

        // AddRoundKey(state) складываем по модулю 2
        for (i = 0; i < BLOCK_SIZE; i++)    a[i] = (byte)(ta[i] ^ Kdr[i]);
        return (a);
    }


    //......................................................................
    /** Расширение ключа*/
    public void setKey(byte[] key) {
        // внедрение внутренних констант
        final int BC = BLOCK_SIZE / 4;
        final int Klen = key.length;
        final int Nk = Klen / 4;

        int i, j, r;


        // проверям плохие аргументы
        if (key == null)
            throw new IllegalArgumentException("Empty key");
        if (!(key.length == 16 || key.length == 24 || key.length == 32))
            throw new IllegalArgumentException("Incorrect key length");

        // задаем количество раунлво в зависимости от ключа
        numRounds = getRounds(Klen);
        final int ROUND_KEY_COUNT = (numRounds + 1) * BC;

        // оперделяем 4 масива которые буду хранить значения ключа
        byte[] w0 = new byte[ROUND_KEY_COUNT];
        byte[] w1 = new byte[ROUND_KEY_COUNT];
        byte[] w2 = new byte[ROUND_KEY_COUNT];
        byte[] w3 = new byte[ROUND_KEY_COUNT];

        // опеределяем для каждого раунда сесии за/расшифровки ключи
        Ke = new byte[numRounds + 1][BLOCK_SIZE]; // ключи раундов зашифровки
        Kd = new byte[numRounds + 1][BLOCK_SIZE]; // ключи раундов расшифровки

        // копируем ключи в начало кажого ключевого слова
        for (i=0, j=0; i < Nk; i++) {
            w0[i] = key[j++]; w1[i] = key[j++]; w2[i] = key[j++]; w3[i] = key[j++];
        }

        // запускаем алгоритм расширения ключа
        byte t0, t1, t2, t3, old0;        // временные значения байта каждого слова
        for (i = Nk; i < ROUND_KEY_COUNT; i++) {
            t0 = w0[i-1]; t1 = w1[i-1]; t2 = w2[i-1]; t3 = w3[i-1];    // temp = w[i-1]
            if (i % Nk == 0) {
                // temp = SubWord(RotWord(temp)) ^ Rcon[i/Nk]
                old0 = t0;            // сохраняем старый первый байт для следующего шага алгоритма для t3
                t0 = (byte)(S[t1 & 0xFF] ^ rcon[i/Nk]);    // постоянное сложение по модулю 2 первго байта
                t1 = (byte)(S[t2 & 0xFF]);
                t2 = (byte)(S[t3 & 0xFF]);    // RotWord реализовано перестановкой байт
                t3 = (byte)(S[old0 & 0xFF]);
            }
            else if ((Nk > 6) && (i % Nk == 4)) {
                // temp = SubWord(temp)
                t0 = S[t0 & 0xFF]; t1 = S[t1 & 0xFF]; t2 = S[t2 & 0xFF]; t3 = S[t3 & 0xFF];
            }
            // w[i] = w[i-Nk] ^ temp
            w0[i] = (byte)(w0[i-Nk] ^ t0);
            w1[i] = (byte)(w1[i-Nk] ^ t1);
            w2[i] = (byte)(w2[i-Nk] ^ t2);
            w3[i] = (byte)(w3[i-Nk] ^ t3);
        }

        // теперь копирует значение в переменную для ключей шифрования расшифрования
        for (r = 0, i = 0; r < numRounds + 1; r++) {    // для каждого раунда
            for (j = 0; j < BC; j++) {        // для каждого слова в раунде
                Ke[r][4*j] = w0[i];
                Ke[r][4*j+1] = w1[i];
                Ke[r][4*j+2] = w2[i];
                Ke[r][4*j+3] = w3[i];
                Kd[numRounds - r][4*j] = w0[i];
                Kd[numRounds - r][4*j+1] = w1[i];
                Kd[numRounds - r][4*j+2] = w2[i];
                Kd[numRounds - r][4*j+3] = w3[i];
                i++;
            }
        }
    }


    public String static_byteArrayToString(byte[] data) {//перевод байтов в строку
        Charset cset = Charset.forName("Cp866");
        ByteBuffer buff = ByteBuffer.wrap(data);
        CharBuffer chbuf = cset.decode(buff);
        String start = chbuf.toString();
        buff.clear();
        return start;
    }

    public byte[] static_stringToByteArray(String s){//перевод строки в байты
        Charset cset = Charset.forName("Cp866");
        ByteBuffer buf = cset.encode(s);
        byte[] b = buf.array();
        buf.clear();
        return  b;
    }

    public String _cryptAll(String data, int mode)  {//общяя фукнция шифровки/расшифроки текста (mode указывает на шифровку/расшифровку)
        AES aes = this;
        int rest=0;
        if(data.length()%16!=0) {
            if (data.length() > 16) rest = 16 - (data.length() % 16);
            else {
                rest = 16 - data.length();
            }
            for (int i = 0; i < rest; i++) data = data + " ";//дополняем пробелами до полного блока остаток
        }
        int nParts = (int) data.length()/16;
        byte[] res = new byte[data.length()];
        String partStr = "";
        byte[] partByte = new byte[16];
        for(int p=0; p<nParts; p++) {
            partStr = data.substring(p*16, p*16+16);
            partByte = static_stringToByteArray(partStr);//переводим в байты
            if(mode==1) partByte = aes.encrypt(partByte);//шифруем блоки
            if(mode==2) partByte = aes.decrypt(partByte);//расшифруем блоки
            for(int b=0; b<16; b++)
                res[p*16+b] = partByte[b];
        }
        return static_byteArrayToString(res);//переводим в строку
    }

    public String Encrypt(String data) {//шифруем текс
        return _cryptAll(data, 1);
    }
    public String Decrypt(String data) {//расшифруем текст
        return _cryptAll(data, 2);
    }

    public void setKey(String key) {//расширение ключа
        setKey(static_stringToByteArray(key));
    }
}