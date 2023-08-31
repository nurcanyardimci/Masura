#define baslatbuton 2
#define masura1 6
#define masura2 5
#define masura3 4
#define direnc1 A0
#define direnc2 A1
#define direnc3 A2

void setup()
{
  pinMode(baslatbuton, INPUT);
  pinMode(masura1, OUTPUT);
  pinMode(masura2, OUTPUT);
  pinMode(masura3, OUTPUT);
  pinMode(direnc1, INPUT);
  pinMode(direnc2, INPUT);
  pinMode(direnc3, INPUT);
  Serial.begin(9600);
  Serial.println("Butona basildiginda masuralar calisacaktir.");
  Serial.println("**************");
  Serial.println(" ");
}
void loop()
{
  if (baslatButonDurum())
  {
    Serial.println(" ");
    Serial.println("Masuralar 20 sn boyunca calisacaktir.");
    Serial.println(" ");
    digitalWrite(masura1, HIGH);
    digitalWrite(masura2, HIGH);
    digitalWrite(masura3, HIGH);
    delay(20000);
    digitalWrite(masura1, LOW);
    digitalWrite(masura2, LOW);
    digitalWrite(masura3, LOW);
    Serial.println(" ");
    Serial.println("Masuralar durdu, olcum yapmak icin sensor degerleri okunuyor.");
    Serial.println(" ");
    delay(3000);
    int sensorOkunan = analogRead(direnc1);
    sensorOlcumu(sensorOkunan, "1");
    
    sensorOkunan = analogRead(direnc2);
    sensorOlcumu(sensorOkunan, "2");
    
    sensorOkunan = analogRead(direnc3);
    sensorOlcumu(sensorOkunan, "3");
    delay(3000);

    Serial.println(" ");
    Serial.println("Masuralarin olcum degerleri okundu.");
    Serial.println(" ");
  }
}
bool baslatButonDurum()
{
  int durum = digitalRead(baslatbuton);
  if (durum == HIGH) {
    return true;
  }
  return false;
}
void sensorOlcumu(int sensor, String masura)
{
  float gerilim = map(sensor, 0, 1023, 0, 500);
  float agirlik = gerilim / 5;
  
  float fark = 0;
 
  if (agirlik < 70) {
    fark = 70 - agirlik;
    MesajiYazdir(masura, agirlik, fark, false,"daha az.");
  }
  else if (agirlik > 75) {
    fark = agirlik - 75;
    MesajiYazdir(masura, agirlik, fark, false,"daha cok.");
  }
  else {
    MesajiYazdir(masura, agirlik, 0, true, "");
  }
}

void MesajiYazdir(String masura, float agirlik, float fark, bool durum, String farks)
{
  if (durum==true) {
    Serial.println(" ");
    Serial.println(" ");
    Serial.println(masura + ". masura agirligi dogrudur.");
    Serial.println(" ");
    Serial.print(masura +". agirligi :");
    Serial.print(agirlik);
    Serial.print("gr");
    Serial.println(" ");
    return;
  }
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(masura + ". Masurada hata meydana geldi ! ");
  Serial.println(" ");
  Serial.print(masura +". agirligi :");
  Serial.print(agirlik);
  Serial.print("gr");
  Serial.println(masura + ". masuranin agirligi olmasi gerekenden ");
  Serial.print(fark);
  Serial.print("gr " + farks);
  Serial.println(" ");
}
