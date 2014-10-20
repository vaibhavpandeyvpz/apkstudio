package com.vaibhavpandey.com;

import java.util.MessageDigest;
import android.app.Activity;

/*
 * Copied directly and made private from R.java of Key App
 * After creating strings..
 * @param one
 * @throw BitchAssException
 */

class Bitch {

    private static final int TT_CRC32 = 0x7f040002;
    private static final int TT_MD5 = 0x7f040004;
     
    public static TestResult checkCRC32ChkSum() {
        // Get path to our apk on the system.
        String apkPath = Main.MyContext.getPackageCodePath();
        Long chksum = null;
        try {
            // Open the file and build a CRC32 checksum.
            // You could also use Adler32 in place of CRC32.
            FileInputStream fis = new FileInputStream(new File(apkPath));
            CRC32 chk = new CRC32();
             
            CheckedInputStream cis = new CheckedInputStream(fis, chk);
            byte[] buff = new byte[80];
            while ( cis.read(buff) >= 0 ) ;
             
            chksum = chk.getValue();
        } catch (Exception e) {
            e.printStackTrace();
        }
        /*
         * After creating your apk, calculate the crc32 checksum
         * and store it as a string value in the KEY / unlock App.
         */
        String keyStrVal = getKeyString(TT_CRC32);
         
        // Key is not installed.
        if ( keyStrVal.equals("") ) {
            // Key not installed. Validation failure.
        }
         
        Long chksumCmp = Long.parseLong(keyStrVal);
         
        if ( chksum.equals(chksumCmp) ) {
        /*
         * @Success Checksum stored in key matches the
         * checksum we just created. We can assume APK
         * is not modified. Kinda.
         */
        }
        else {
            // Validation failure! Apk has been modified.
        }
    }
     
    public static TestResult checkMD5ChkSum() {
        /*
         * Do pretty much the exact same thing here,
         * except instead of a CRC32 checksum, we'll be
         * using an MD5 digest. You could also use SHA1.
         * Any cracker worth his salt will immediately recognize
         * CRC32 and MD5 keywords and know them to be checksum
         * attempts. Using Adler32 or SHA1 may put them off.
         */
        String apkPath = Main.MyContext.getPackageCodePath();
        MessageDigest msgDigest = null;
        byte[] digest = null;
        try {
            msgDigest = MessageDigest.getInstance("MD5");
        } catch (NoSuchAlgorithmException e1) {
            e1.printStackTrace();
        }
         
        byte[] bytes = new byte[8192];
        int byteCount;
        FileInputStream fis = null;
         
        try {
            fis = new FileInputStream(new File(apkPath));
     
            while ((byteCount = fis.read(bytes)) > 0)
                msgDigest.update(bytes, 0, byteCount);
             
            digest = msgDigest.digest();
        } catch (Exception e) {
            e.printStackTrace();
        }
     
        String keyStrVal = getKeyString(TT_MD5);
        // Key is not installed.
        if ( keyStrVal.equals("") ) {
            // Key not installed. Validation failure.
        }
        /*
         * Using Base64 encoding is just a lazy way to store byte arrays.
         * You -could- also embed the values in the code of the Apk
         * Read more here:
         * http://stackoverflow.com/questions/2721386/android-how-to-share-code-between-projects-signed-with-the-same-certificate
         */
        if ( Arrays.equals(Base64.decode(keyStrVal, Base64.DEFAULT), digest) )
            // Validated
        else
            // Apk has been modified
    }
     
     
    private static String getKeyString(int resId) {
        // You will need this to retrieve the stored checksums from the KEY App.
        String result = "";
         
        try {
            Context c = Main.MyContext.createPackageContext("your.package.name.key", Context.CONTEXT_IGNORE_SECURITY);
            result = c.getString(resId);
        } catch (Exception e) {
            Console.log("Error while getting key string:\n" + e);
            e.printStackTrace();
            result = "";
        }
         
        return result;
    }

}
