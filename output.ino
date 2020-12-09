void beep(int a,int delayy){
  for (int x=0;x<a;x++){
    digitalWrite(buzzer,HIGH);
    delay(delayy);
    digitalWrite(buzzer,LOW);
    delay(delayy);
    
  }
}

void tampilan(){
lcd.setCursor(0,0);
lcd.print("");
lcd.print(suhu);
lcd.print("'C");
lcd.print("|");
lcd.print("level");
lcd.print(level);
lcd.print("|");
lcd.print(tanah);
lcd.print("%");
lcd.print("  ");
lcd.setCursor(1,1);
lcd.print(karakter(hour));
lcd.print(":");
lcd.print(karakter(minute));
lcd.print(":");
lcd.print(karakter(second));
lcd.print("|");
lcd.print(durasi_sekarang);
lcd.print("|");
lcd.print("G:");
lcd.print(started);
}
