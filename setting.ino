void set_par(){
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("SETTING DURASI ");
  tunggu();
  bacatombol();
  durasi=EEPROM.read(1);
  lcd.setCursor(0,1);
  lcd.print("Durasi:");
  lcd.print(durasi);
  lcd.print(" Mnt");
  delay(200);
  while(!yes){
    bacatombol();
    if (up){
      durasi++;
      delay(200);
      }
    else if (down){
      durasi--;
      delay(200);
   }
  lcd.setCursor(0,1);
  lcd.print("Durasi:");
  lcd.print(durasi);
  lcd.print(" Mnt   ");
    
  }
  EEPROM.write(1,durasi);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("DATA TERSIMPAN...!!!");
  delay(2000);
}

void setTime() {
  tunggu();
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("JAM= 00:00" );
 int flag = 1;
 byte tunggu=0;
  byte nilai[5]={0,0,0,0,0};
  String sjam;
  String smenit;
  String sdetik;
  String stahun;
  String sbulan;
  String shari;
  time_read();
  nilai[1]=hour;
  nilai[2]=minute;
  nilai[3]=second;
  if (nilai[1]>24){nilai[1]=24;}
  if (nilai[2]>59){nilai[2]=59;}
  if (nilai[3]>59){nilai[3]=59;}
  
  while (flag <=3){
    bacatombol();
    
    if (up){nilai[flag]=nilai[flag]+1;delay(200);}
    else if (down){nilai[flag]=nilai[flag]-1;delay(200);}
    else if(yes){nilai[flag]=nilai[flag];tunggu=0;flag++;delay(200);}
    if (nilai[1]>24){nilai[1]=24;}
    if (nilai[2]>59){nilai[2]=59;}
    if (nilai[3]>59){nilai[3]=59;}
    
    if(flag==1){
    sjam=karakter(nilai[flag]);
    lcd.setCursor(0,0);
    lcd.print("JAM= ");
    lcd.print(sjam);
    lcd.print(":00:00");
    lcd.setCursor(0,1);
    lcd.print("_____^^");
    }else if(flag==2){
    smenit=karakter(nilai[flag]);
    lcd.setCursor(0,0);
    lcd.print("JAM= ");
    lcd.print(sjam);
    lcd.print(":");
    lcd.print(smenit);
    lcd.print(":00 ");
    lcd.setCursor(0,1);
    lcd.print("________^^");}
    else if(flag==3){
    sdetik=karakter(nilai[flag]);
    lcd.setCursor(0,0);
    lcd.print("JAM= ");
    lcd.print(sjam);
    lcd.print(":");
    lcd.print(smenit);
    lcd.print(":");
    lcd.print(sdetik);
    lcd.print(" ");
    lcd.setCursor(0,1);
    lcd.print("___________^^");
    
    } 
    
  }

 flag = 1;
 tunggu=0;
 byte nilai2[10]={0,0,0,0,0,0,0,0,0,0};
 lcd.clear();
  time_read();
  nilai2[1]=monthday;
  nilai2[2]=month;
  nilai2[3]=year;
  if (nilai2[1]>31){nilai2[1]=31;}
  if (nilai2[2]>12){nilai2[2]=12;}
  if (nilai2[3]>99){nilai2[3]=99;}
  
 while (flag <=3){
    bacatombol();
    if (up){nilai2[flag]=nilai2[flag]+1;delay(200);}
    else if (down){nilai2[flag]=nilai2[flag]-1;delay(200);}
    else if(yes){nilai2[flag]=nilai2[flag];flag++;tunggu=0;delay(200);}
    if (nilai2[1]>31){nilai2[1]=31;}
    if (nilai2[2]>12){nilai2[2]=12;}
    if (nilai2[3]>99){nilai2[3]=99;}
  
    if(flag==3){
    stahun=karakter(nilai2[flag]);
    lcd.setCursor(0,0);
    lcd.print("TGL= ");
    lcd.print(shari);
    lcd.print("/");
    lcd.print(sbulan);
    lcd.print("/");
    lcd.print(stahun);
    lcd.print(" ");
    lcd.setCursor(0,1);
    lcd.print("___________^^");
    }else  if(flag==2){
    sbulan=karakter(nilai2[flag]);
    lcd.setCursor(0,0);
    lcd.print("TGL= ");
    lcd.print(shari);
    lcd.print("/");
    lcd.print(sbulan);
    lcd.print("/00 ");
    lcd.setCursor(0,1);
    lcd.print("________^^");
    } if(flag==1){
    shari=karakter(nilai2[flag]);
    lcd.setCursor(0,0);
    lcd.print("TGL= ");
    lcd.print(shari);
    lcd.print("/00/00 ");
    lcd.setCursor(0,1);
    lcd.print("_____^^");
    }

  }

  
 second = nilai[3];
 minute=nilai[2];
 hour=nilai[1];

 monthday=nilai2[1];
 month=nilai2[2];
 year=nilai2[3];

// Kode untuk mentransmisikan atau mengirimkan data ke RTC
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(weekday));
  Wire.write(decToBcd(monthday));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.write(byte(0));
  Wire.endTransmission();
  // Ends transmission of data
}
