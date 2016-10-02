package main.java.org.xxtea;

import main.java.org.xxtea.XXTEA;

public class Main {
    public static void main(String[] args) {
        String str = "32.8856, -117.2395";
        String key = "1234567890";
        String encrypt_data = XXTEA.encryptToBase64String(str, key);
        System.out.println(encrypt_data);
        assert("82E9784B6BEC98F2846A58FDDBC60A7C88E9C0D4".equals(encrypt_data));
        String decrypt_data = XXTEA.decryptBase64StringToString(encrypt_data, key);
        assert(str.equals(decrypt_data));
        System.out.println(decrypt_data);
    }
}
