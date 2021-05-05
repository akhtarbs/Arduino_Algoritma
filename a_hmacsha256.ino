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

#include <SHA256.h>

#define HASH_SIZE 32
#define BLOCK_SIZE 64

SHA256 sha256;
byte buffer[128];
String hmacsha256(Hash *hash, String stringkey, String stringtext){  
    int i_key = stringkey.length() + 1;
    char key[i_key];
    stringkey.toCharArray(key,i_key);
    int i_text = stringtext.length() + 1;
    char text[i_text];
    stringtext.toCharArray(text,i_text);
    uint8_t result[HASH_SIZE];
    hash->resetHMAC(key, strlen(key));
    hash->update(text, strlen(text));
    hash->finalizeHMAC(key, strlen(key), result, sizeof(result));
    String out_hex="";
    for (int i = 0; i <= sizeof(result)-1; i++) {
      String a = String(result[i],HEX);
      if(result[i]<10){
        a="0"+a;
      }
      out_hex = out_hex+a;
    }
    return out_hex;
}

void setup(){
    Serial.begin(9600);
    String i_data = "budi";
    String i_key = "fauzan";
    
    String output = hmacsha256(&sha256,i_key,i_data);
    Serial.print("Hasil Output  = ");
    Serial.println(output);
    Serial.println();
}

void loop(){
}
