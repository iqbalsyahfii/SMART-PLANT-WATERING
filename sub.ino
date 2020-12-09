void time_read(){
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);
  second = bcdToDec(Wire.read());
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read());
  weekday = bcdToDec(Wire.read());
  monthday = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
}

bool tombol(int pin){
bool nilai=false;
if (digitalRead(pin)==1){
  nilai=false;
}else if (digitalRead(pin)==0){
  nilai=true;
  beep(1,200);
}
return nilai;
 
}

void bacatombol(){
  yes=tombol(pinyes);
  up=tombol(pinup);
  down=tombol(pindown);
  
}


String karakter(int jumlahbilangan){
  String stringdata = String(jumlahbilangan);
  if (jumlahbilangan < 10){
    stringdata = "0" + stringdata;
  }

  return stringdata;
}


byte decToBcd(byte val) {
  return ((val/10*16) + (val%10));
}
byte bcdToDec(byte val) {
  return ((val/16*10) + (val%16));
}


String tampil(int data){
  String show=String(data);
  if(data<10){
    show="0"+show;
  }
  return show;
}
byte reade(int address){
byte data= EEPROM.read(address);
return data;
}

void writee(int address, int data){
EEPROM.write(address,data);
}

double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
