//Cara Install Library 
//search dan install "Crypto" di MANAGE LIBRARY ARDUINO IDE 
//
//Library Yang Diinstall

//--Crypto
//--by Rhys Weatherley rhys.weatherley@gmail.com Version 0.2.0
//
//--Rhys Weatherley's arduinolibs Crypto library
//--https://rweather.github.io/arduinolibs/crypto.html

//--Fauzan Budi Setiawan
//--https://github.com/akhtarbs

#include <Crypto.h>
#include <AES.h>

AES128 aes128;
byte buffer[16];

String Aes128Enkripsi(BlockCipher *cipher,String stringkey,String stringtext){
    int i_key = stringkey.length() + 1;
    char key[i_key];
    stringkey.toCharArray(key,i_key);
    int i_text = stringtext.length() + 1;
    char text[i_text];
    stringtext.toCharArray(text,i_text);
    crypto_feed_watchdog();
    cipher->setKey(key, cipher->keySize());
    cipher->encryptBlock(buffer, text);
    String out_hex="";
    for (int i = 0; i <= sizeof(buffer)-1; i++) {
      String a = String(buffer[i],HEX);
      if(buffer[i]<10){
        a="0"+a;
      }
      out_hex = out_hex+a;
    }
    return out_hex;
}

String Aes128Dekripsi(BlockCipher *cipher, String stringkey,String stringtexthex){
    int i_key = stringkey.length() + 1;
    char key[i_key];
    stringkey.toCharArray(key,i_key);
    int p_aes = stringtexthex.length()+1;
    char AesArray[p_aes];
    stringtexthex.toCharArray(AesArray,p_aes);
    char cipheraes[32];
    int array_buff=0;
    for (int i = 0; i < p_aes-2; i++){
      if(i%2==0){
            String StrHex = String(AesArray[i])+String(AesArray[i+1]);
            char ArrayStrHex[3];
            StrHex.toCharArray(ArrayStrHex,3);
            int nilaiInt;
            char * nilaiChar;
            nilaiInt = strtol(ArrayStrHex,&nilaiChar,16);
            cipheraes[array_buff]=(char)nilaiInt;
            array_buff++;
        }
    }
    
    crypto_feed_watchdog();
    cipher->setKey(key, cipher->keySize());
    cipher->decryptBlock(buffer, cipheraes);
    String oAesPlain ="";
    for (int i = 0; i < 16; i++) {
      char str[3];
      sprintf(str, "%c", (char)buffer[i]);
      oAesPlain = oAesPlain+str;
    } 
    return oAesPlain;
}

void setup(){
    Serial.begin(9600);

//    Program Enkripsi dengan AES-128 Mode ECB
    String stringkey="abababababababab";
    String stringtext="pesanpesanpesana";
    String hasilaes = Aes128Enkripsi(&aes128,stringkey,stringtext);
    Serial.println("Hasil Enkripsi Dengan AES-128 ECB");
    Serial.println(hasilaes);

//    Program Dekripsi dengan AES-128 Mode ECB
    String dekripkey="abababababababab";
    String dekriptext = "57e7e9f2ce2a9915b6d4cb63f3283381";
    String hasildekripaes = Aes128Dekripsi(&aes128,dekripkey,dekriptext);
    Serial.println("Hasil Dekripsi Dengan AES-128 ECB");
    Serial.println(hasildekripaes);
}

void loop(){
}
