void sendsms(String protokol)
{
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Send SMS ...");
 protokol.toCharArray(sms_text1, protokol.length()+1);
 
 for (int i=0;i<jumlahnomor;i++)
  {
  sms.SendSMS(myphone[i],sms_text1 );
  Serial.print(myphone[i]);
  Serial.print("  ");
  Serial.print(sms_text1);
  Serial.println();
  delay(2000);
  }
  lcd.clear();
} 
