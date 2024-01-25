//***************Islaklık****************
#define islaklikSensor1Pin 33 //HAZNE
#define islaklikSensor2Pin 32 //KAP
#define kirmiziLed 25 // SU KAP DOLUM LEDİ

//***************Mesafe2******************
#define arkatrigPin 16  //KAP
#define arkaechoPin 17
#define sariLed 26 // MAMA KAP DOLUM LEDİ

long sure2, mesafe2 ;
int yuzde_mama_kabi;

//***************Mesafe1******************
#define ontrigPin 12    // HAZNE
#define onechoPin 13

long sure1, mesafe1 ;
int yuzde_mama_hazne;

//***************Islaklık1*********************
int islaklik1 = 0; // Sensor pın 32 renk turuncu   !!KAP!!
bool su1 = 0 ;
int threshold1 = 100 ;
//***************Islaklık2*********************
int islaklik2 = 0; // Sensor pın 33 renk yeşil     !!HAZNE!!
bool su2 = 0 ;
int threshold2 = 100 ;

void setup() 
{
 Serial.begin(9600);
 pinMode(kirmiziLed, OUTPUT);
 pinMode(sariLed, OUTPUT);
 
 //*****************Mesafe1****************
 pinMode(ontrigPin, OUTPUT);
 pinMode(onechoPin, INPUT);
 delay(3000);

 //*****************Mesafe2****************
 pinMode(arkatrigPin, OUTPUT);
 pinMode(arkaechoPin, INPUT);
 delay(3000);
}

void loop() 
{
 Serial.println("******************************NEW DATA****************************") ; 
//*********** Led  Ayarı ************************
  digitalWrite(kirmiziLed,LOW);
  digitalWrite(sariLed, LOW);
  
//*****************Islaklık1***************
 islaklik1 = analogRead(islaklikSensor1Pin);

 if(islaklik1 > threshold1)
 {
   su1 = true ;
   Serial.print("Hazne su ile dolu.\n") ;
 }
 else
 {
   su1 = false ;
   Serial.print("Hazne bos durumda.\n") ;
 }

 /*Serial.print("Hazne islaklik verisi : ") ;
   Serial.print(islaklik1) ; 
   Serial.print("\n") ; */
//*****************Islaklık2***************
 islaklik2 = analogRead(islaklikSensor2Pin);

 if(islaklik2 > threshold2)
 {
   su2 = true ;
   Serial.print("Kap su ile dolu.\n") ;
 }
 else
 {
   su2 = false ;
   Serial.print("Kap bos durumda.\n") ;
   digitalWrite(kirmiziLed, HIGH);
   delay(1000);
   digitalWrite(kirmiziLed, LOW);
   delay(1000);
 }

 /*Serial.print("Kap islaklik verisi : ") ;
   Serial.print(islaklik2) ; 
   Serial.print("\n") ; */
//*****************Mesafe 1****************
 digitalWrite(ontrigPin, LOW);
 delayMicroseconds(3);
 digitalWrite(ontrigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(ontrigPin, LOW);

 sure1 = pulseIn(onechoPin, HIGH);
 mesafe1 = (sure1/2) * 0.0343;
 Serial.print("Hazne mesafesi :");
 Serial.print(mesafe1);
 Serial.print("\n") ;
 if( mesafe1==3)
{
  yuzde_mama_hazne=100;
}
else if( mesafe1 < 6 & mesafe1>=3)
{
  yuzde_mama_hazne=75;
}
else if( mesafe1 < 9 & mesafe1>=6)
{
  yuzde_mama_hazne=50;
}
else if( mesafe1 < 12 & mesafe1>9)
{
  yuzde_mama_hazne=25;
  delay(10);
}
  else
{
  yuzde_mama_hazne=0;
}
Serial.print("Mama Haznesi Doluluk % ");
Serial.print(yuzde_mama_hazne);
Serial.print("\n");
//*****************Mesafe 2***************
 digitalWrite(arkatrigPin, LOW);
 delayMicroseconds(3);
 digitalWrite(arkatrigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(arkatrigPin, LOW);

 sure2 = pulseIn(arkaechoPin, HIGH);
 mesafe2 = (sure2/2) * 0.0343;
 Serial.print("Kap mesafesi :");
 Serial.print(mesafe2);
 Serial.print("\n") ;
   if( mesafe2==3)
{
  yuzde_mama_kabi=100;
}
else if( mesafe2 < 6 & mesafe2>=3)
{
  yuzde_mama_kabi=75;
}
else if( mesafe2 < 9 & mesafe2>=6)
{
  yuzde_mama_kabi=50;
}
else if( mesafe2 < 12 & mesafe2>9)
{
  yuzde_mama_kabi=25;
  delay(10);
}
  else
{
  yuzde_mama_kabi=0;
  digitalWrite(sariLed, HIGH ); //------------------Kabı doldurmak için Sarı Ledi yak--------------------
  delay(1000);
  digitalWrite(sariLed , LOW );
  delay(1000);
}
Serial.print("Mama Kabı Doluluk % ");
Serial.print(yuzde_mama_kabi);
Serial.print("\n");
//*****************************************

 Serial.print("");
 delay(1500);
}
