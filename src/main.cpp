//----------------------------------------------------Library yang digunakan----------------------------------------------------//
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fuzzy.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include "main.h"
#include "fuzzy_set.h"
//------------------------------------------------------------------------------------------------------------------------------//

//------------------------------------------------Definisi fungsi yang digunakan------------------------------------------------//
void TampilBPMtoOled();
void GetHeartRate();
void BPMindikator();
void DrawGraph();
void screen1();
void bacaDS();
void bacaGSR();
void TampilDStoOled();
//------------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------Fungsi Setup-------------------------------------------------------------//
void setup()
{
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  sensorDS.begin();
  display.clearDisplay();

  pinMode(Pb_UP, INPUT_PULLUP);
  pinMode(Pb_DOWN, INPUT_PULLUP);
  pinMode(Pb_OK, INPUT_PULLUP);
  pinMode(Pb_BACK, INPUT_PULLUP);

  pinMode(LED_A1, OUTPUT);
  digitalWrite(LED_A1, HIGH);

  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.reconnectWiFi(true);

  Firebase.begin(&config, &auth);

  fuzzySet();
  fuzzyRule();

  xTaskCreatePinnedToCore(
      TaskHandle1,
      "TaskHandle1",
      3072,
      NULL,
      1,
      &Task1,
      1);

  delay(200);
}
//---------------------------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------Pengambilan Nilai BPM dan ditampilkan di oLed-------------------------------------------------------------//
void TampilBPMtoOled()
{
  //----------------------------------------Process of reading heart rate.
  unsigned long currentMillisGetHR = millis();

  if (currentMillisGetHR - previousMillisGetHR >= intervalGetHR)
  {
    previousMillisGetHR = currentMillisGetHR;

    PulseSensorSignal = analogRead(Sen_PHR); //--> holds the incoming raw data. Signal value can range from 0-1024

    if (PulseSensorSignal > UpperThreshold && ThresholdStat == true)
    {
      cntHB++;
      ThresholdStat = false;
      digitalWrite(LED_A1, LOW);
    }

    if (PulseSensorSignal < LowerThreshold)
    {
      ThresholdStat = true;
      digitalWrite(LED_A1, HIGH);
    }

    DrawGraph(); //--> Calling the DrawGraph() subroutine
  }
  //----------------------------------------

  //----------------------------------------The process for getting the BPM value.
  unsigned long currentMillisResultHR = millis();

  if (currentMillisResultHR - previousMillisResultHR >= intervalResultHR)
  {
    previousMillisResultHR = currentMillisResultHR;

    BPMval = cntHB * 6; //--> The taken heart rate is for 10 seconds. So to get the BPM value, the total heart rate in 10 seconds x 6.
    Serial.print("BPM : ");
    Serial.println(BPMval);

    unsigned long previusMillis = 0;
    if (millis() - previusMillis >= 500)
    {
      previusMillis = millis();
      if (Firebase.setFloat(fbdo, "/DATA/BPM", BPMval))
      {
        Serial.println("Kirim data BPM berhasil");
        Serial.println("");
      }
      else
      {
        Serial.println("Kirim data BPM Gagal");
        Serial.println("");
      }
    }

    display.fillRect(20, 48, 108, 18, BLACK);

    display.drawBitmap(0, 47, Heart_Icon, 16, 16, WHITE); //--> display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
    display.drawLine(0, 43, 127, 43, WHITE);              //--> drawLine(x1, y1, x2, y2, color)

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(20, 48); //--> (x position, y position)
    display.print(": ");
    display.print(BPMval);
    display.print(" BPM");
    display.display();

    cntHB = 0;
  }
  //----------------------------------------
}

void DrawGraph()
{
  //----------------------------------------Condition to reset the graphic display if it fills the width of the OLED screen
  if (x > 127)
  {
    display.fillRect(0, 0, 128, 42, BLACK);
    x = 0;
    lastx = 0;
  }
  //----------------------------------------

  //----------------------------------------Process signal data to be displayed on OLED in graphic form
  int ySignal = PulseSensorSignal;

  if (ySignal > 3000)
    ySignal = 3000;
  if (ySignal < 1200)
    ySignal = 1200;

  int ySignalMap = map(ySignal, 1200, 3000, 0, 40); //--> The y-axis used on OLEDs is from 0 to 40

  y = 40 - ySignalMap;
  //----------------------------------------

  //----------------------------------------Displays the heart rate graph
  display.writeLine(lastx, lasty, x, y, WHITE);
  display.display();
  //----------------------------------------

  lastx = x;
  lasty = y;

  x++;
}
//---------------------------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------Pengambilan Nilai BPM-------------------------------------------------------------//
void GetHeartRate()
{
  //----------------------------------------Process of reading heart rate.
  unsigned long currentMillisGetHR = millis();

  if (currentMillisGetHR - previousMillisGetHR >= intervalGetHR)
  {
    previousMillisGetHR = currentMillisGetHR;

    PulseSensorSignal = analogRead(Sen_PHR); //--> holds the incoming raw data. Signal value can range from 0-1024

    if (PulseSensorSignal > UpperThreshold && ThresholdStat == true)
    {
      cntHB++;
      ThresholdStat = false;
      digitalWrite(LED_A1, LOW);
    }

    if (PulseSensorSignal < LowerThreshold)
    {
      ThresholdStat = true;
      digitalWrite(LED_A1, HIGH);
    }
  }
  //----------------------------------------The process for getting the BPM value.
  unsigned long currentMillisResultHR = millis();

  if (currentMillisResultHR - previousMillisResultHR >= intervalResultHR)
  {
    previousMillisResultHR = currentMillisResultHR;

    BPMval = cntHB * 6; //--> The taken heart rate is for 10 seconds. So to get the BPM value, the total heart rate in 10 seconds x 6.
    cntHB = 0;
  }

  //----------------------------------------
}
//---------------------------------------------------------------------------------------------------------------------------------------------//
void BPMindikator()
{
  float signal = analogRead(Sen_PHR); //--> Read the PulseSensor's value. Assign this value to the "Signal" variable.

  if (signal > UpperThreshold)
  { //--> If the signal is above "550"(Threshold), then "turn-on" Arduino's on-Board LED.
    digitalWrite(LED_A1, LOW);
  }

  if (signal < LowerThreshold)
  {
    digitalWrite(LED_A1, HIGH); //--> Else, the sigal must be below "500", so "turn-off" this LED.
  }

  delay(20);
}

//--------------------------------------------Pembacaan Sensor DS18b20 dan Ditampilkan di oled--------------------------------------------//
void TampilDStoOled()
{
  sensorDS.setResolution(12);           // Sebelum melakukan pengukuran, atur resolusinya
  sensorDS.requestTemperatures();       // Perintah konversi suhu
  dataDS = sensorDS.getTempCByIndex(0); // Membaca data suhu dari sensor #0 dan mengkonversikannya ke nilai Celsius
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(20, 25);
  display.print(dataDS);
  display.print((char)247);
  display.print("C");
  display.display();

  unsigned long previusMillis = 0;
  if (millis() - previusMillis >= 500)
  {
    previusMillis = millis();
    if (Firebase.setFloat(fbdo, "/DATA/SUHU", dataDS))
    {
      Serial.println("Kirim data SUHU berhasil");
      Serial.println("");
    }
    else
    {
      Serial.println("Kirim data SUHU Gagal");
      Serial.println("");
    }
  }

  delay(100);
}
//---------------------------------------------------------------------------------------------------------------------------------//

//--------------------------------------------Pembacaan Sensor DS18b20 --------------------------------------------//

void bacaDS()
{
  sensorDS.setResolution(12);     // Sebelum melakukan pengukuran, atur resolusinya
  sensorDS.requestTemperatures(); // Perintah konversi suhu
  dataDS = sensorDS.getTempCByIndex(0);
  delay(100);
}
//---------------------------------------------------------------------------------------------------------------------------------//

//--------------------------------------------Pembacaan Sensor GSR--------------------------------------------//
void bacaGSR()
{
  long sum = 0;
  for (int i = 0; i < 10; i++) // Average the 10 measurements to remove the glitch
  {
    sensorValue = analogRead(Sen_GSR);
    sum += sensorValue;
    delay(5);
  }
  gsr_average = sum / 10;

  dataGSR = map(gsr_average, 2650, 500, 1, 7);
}
//-------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------Tampilan display di oled-------------------------------------------------//
void screen1()
{
//---------------------------MENU 1---------------------------//
setMENU1:
  if (digitalRead(Pb_OK) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_OK) == tekan)
    {
      display.clearDisplay();
      goto setScreenCekStress;
    }
  }
  else if (digitalRead(Pb_UP) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_UP) == tekan)
    {
      goto setMENU4;
    }
  }
  else if (digitalRead(Pb_DOWN) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_DOWN) == tekan)
    {
      goto setMENU2;
    }
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(30, 0);
  display.print("DAFTAR MENU");
  display.setCursor(5, 17);
  display.print("-> Cek Stress");
  display.setCursor(5, 27);
  display.print("   Cek BPM");
  display.setCursor(5, 37);
  display.print("   Cek Suhu Tubuh");
  display.setCursor(5, 47);
  display.print("   WiFi");
  display.display();

  goto setMENU1;
  //------------------------------------------------------------------------//

  //---------------------------MENU 2---------------------------//
setMENU2:

  if (digitalRead(Pb_OK) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_OK) == tekan)
    {
      display.clearDisplay();
      goto setScreenCekBPM;
    }
  }
  else if (digitalRead(Pb_UP) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_UP) == tekan)
    {
      goto setMENU1;
    }
  }
  else if (digitalRead(Pb_DOWN) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_DOWN) == tekan)
    {
      goto setMENU3;
    }
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(30, 0);
  display.print("DAFTAR MENU");
  display.setCursor(5, 17);
  display.print("   Cek Stress");
  display.setCursor(5, 27);
  display.print("-> Cek BPM");
  display.setCursor(5, 37);
  display.print("   Cek Suhu Tubuh");
  display.setCursor(5, 47);
  display.print("   WiFi");
  display.display();

  goto setMENU2;
  //------------------------------------------------------------------------//

  //---------------------------MENU 3---------------------------//
setMENU3:

  if (digitalRead(Pb_OK) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_OK) == tekan)
    {
      display.clearDisplay();
      goto setScreenCekSuhu;
    }
  }
  else if (digitalRead(Pb_UP) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_UP) == tekan)
    {
      goto setMENU2;
    }
  }
  else if (digitalRead(Pb_DOWN) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_DOWN) == tekan)
    {
      goto setMENU4;
    }
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(30, 0);
  display.print("DAFTAR MENU");
  display.setCursor(5, 17);
  display.print("   Cek Stress");
  display.setCursor(5, 27);
  display.print("   Cek BPM");
  display.setCursor(5, 37);
  display.print("-> Cek Suhu Tubuh");
  display.setCursor(5, 47);
  display.print("   WiFi");
  display.display();

  goto setMENU3;
  //------------------------------------------------------------------------//

  //---------------------------MENU 4---------------------------//
setMENU4:

  if (digitalRead(Pb_OK) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_OK) == tekan)
    {
      goto setScreenConnectWiFi;
    }
  }
  else if (digitalRead(Pb_UP) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_UP) == tekan)
    {
      goto setMENU3;
    }
  }
  else if (digitalRead(Pb_DOWN) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_DOWN) == tekan)
    {
      goto setMENU1;
    }
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(30, 0);
  display.print("DAFTAR MENU");
  display.setCursor(5, 17);
  display.print("   Cek Stress");
  display.setCursor(5, 27);
  display.print("   Cek BPM");
  display.setCursor(5, 37);
  display.print("   Cek Suhu Tubuh");
  display.setCursor(5, 47);
  display.print("-> WiFi");
  display.display();

  goto setMENU4;
  //------------------------------------------------------------------------//

  //---------------------------Screen Cek Stress---------------------------//
setScreenCekStress:

  if (digitalRead(Pb_OK) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_OK) == tekan)
    {
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.setCursor(20, 10);
      display.print("Tunggu 20 detik");
      display.setCursor(0, 20);
      display.print("Untuk Mendapatkan BPM");
      display.setCursor(90, 50);
      display.print("Next");
      display.display();
      delay(2000);
      display.clearDisplay();

      goto setScreenStressTesterBPM;
    }
  }
  else if (digitalRead(Pb_BACK) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_BACK) == tekan)
    {
      display.clearDisplay();
      goto setMENU1;
    }
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.print("Tes Tingkat Stress ");
  display.setCursor(10, 50);
  display.print("Back");
  display.setCursor(90, 50);
  display.print("Next");

  display.display();
  goto setScreenCekStress;
  //------------------------------------------------------------------------//

//---------------------------Screen Stress tester Ambil BPM---------------------------//
setScreenStressTesterBPM:

  if (digitalRead(Pb_OK) == tekan && cekBPM_State == true)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_OK) == tekan && cekBPM_State == true)
    {
      display.clearDisplay();
      goto setScreenStressTesterGSR;
    }
  }
  else if (digitalRead(Pb_BACK) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_BACK) == tekan)
    {
      goto setScreenCekStress;
    }
  }

  if (cekBPM_State == false)
  {
    BPMindikator();
    if (digitalRead(Pb_OK) == tekan)
    {
      OKE = true;

      while (OKE == true && cekBPM_State == false)
      {
        GetHeartRate();
        if ((millis() - waktuSebelum) >= interval)
        {
          waktuSebelum = millis();

          if (CNTR <= 100)
          {
            waktuSebelum1 = millis();
            display.clearDisplay();
            display.drawRoundRect(12, 20, 104, 20, 10, WHITE);
            display.fillRoundRect(14, 23, CNTR, 14, 10, WHITE);
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(15, 5);
            display.print("Pengambilan data ");
            display.setCursor(30, 50);
            display.print("loading ");
            display.print(CNTR);
            display.print("%");
            display.display();
            CNTR++;
          }
          else
          {
            BPM = BPMval;
            cekBPM_State = true;
            OKE = false;
            CNTR = 0;
          }
        }
      }
    }
  }

  else if (cekBPM_State == true)
  {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(5, 20);
    display.print("Cek Konduktasi Kulit");
    display.setCursor(90, 50);
    display.print("Next");

    display.display();
  }

  goto setScreenStressTesterBPM;
  //------------------------------------------------------------------------//

  //---------------------------Screen Cek Stress ambil GSR---------------------------//
setScreenStressTesterGSR:
  if (digitalRead(Pb_OK) == tekan && cekGSR_State == true)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_OK) == tekan && cekGSR_State == true)
    {
      display.clearDisplay();
      goto setScreenStressTesterSUHU;
    }
  }
  else if (digitalRead(Pb_BACK) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_BACK) == tekan)
    {
      goto setScreenCekStress;
    }
  }

  if (cekGSR_State == false)
  {

    for (int i = 0; i <= 100; i++)
    {
      bacaGSR();
      display.clearDisplay();
      display.drawRoundRect(12, 20, 104, 20, 10, WHITE);
      display.fillRoundRect(14, 23, i, 14, 10, WHITE);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(15, 5);
      display.print("Pengambilan data ");
      display.setCursor(30, 50);
      display.print("loading ");
      display.print(i);
      display.print("%");
      display.display();
      delay(100);
    }
    GSR = dataGSR;
    cekGSR_State = true;
    display.clearDisplay();
  }

  else if (cekGSR_State == true)
  {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(10, 20);
    display.print("Cek Suhu Tubuh");
    display.setCursor(90, 50);
    display.print("Next");

    display.display();
  }

  goto setScreenStressTesterGSR;
  //----------------------------------------------------------------------------------//

  //---------------------------Screen Cek Stress ambil SUHU---------------------------//
setScreenStressTesterSUHU:
  if (digitalRead(Pb_BACK) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_BACK) == tekan )
    {
      goto setScreenCekStress;
    }
  }
  if (cekSUHU_State == true)
  {
    goto setScreenDefuzzyfikasi;
  }

  else if (cekSUHU_State == false)
  {

    for (int i = 0; i <= 100; i++)
    {
      bacaDS();
      display.clearDisplay();
      display.drawRoundRect(12, 20, 104, 20, 10, WHITE);
      display.fillRoundRect(14, 23, i, 14, 10, WHITE);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(15, 5);
      display.print("Pengambilan data ");
      display.setCursor(30, 50);
      display.print("loading ");
      display.print(i);
      display.print("%");
      display.display();
      delay(100);
    }
    display.clearDisplay();
    SUHU = dataDS;
    cekSUHU_State = true;
  }
  goto setScreenStressTesterSUHU;
  //--------------------------------------------------------------------------------------------//

  //---------------------------Screen Cek Stress Proses defuzzyfikasi---------------------------//
setScreenDefuzzyfikasi:
  if (digitalRead(Pb_BACK) == tekan && fuzzy_State == true)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_BACK) == tekan && fuzzy_State == true)
    {
      cekBPM_State = false;
      cekGSR_State = false;
      cekSUHU_State = false;
      fuzzy_State = false;
      DisplayFuzzy_State = false;
      goto setMENU1;
    }
  }

  fuzzy->setInput(1, BPM);
  fuzzy->setInput(2, GSR);
  fuzzy->setInput(3, SUHU);

  fuzzy->fuzzify();

  FuzzyOut = fuzzy->defuzzify(1);
  fuzzy_State = true;

  if (DisplayFuzzy_State == false)
  {
    DisplayFuzzy_State = true;
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(40, 15);
    display.print(BPM);
    display.setCursor(40, 25);
    display.print(GSR);
    display.setCursor(40, 35);
    display.print(SUHU);
    display.display();
    delay(5000);
  }

  else if ((FuzzyOut >= 0 && FuzzyOut <= 25) && DisplayFuzzy_State == true)
  {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(40, 10);
    display.print("Anda");
    display.setCursor(40, 35);
    display.print("Rileks");
    String data2 = "Rileks";
    Firebase.setString(fbdo, "/DATA/StressVal", data2);
  }
  else if ((FuzzyOut >= 25 && FuzzyOut <= 50) && DisplayFuzzy_State == true)
  {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(40, 10);
    display.print("Anda");
    display.setCursor(40, 35);
    display.print("Tenang");
    String data2 = "Tenang";
    Firebase.setString(fbdo, "/DATA/StressVal", data2);
  }
  else if ((FuzzyOut >= 50 && FuzzyOut <= 75) && DisplayFuzzy_State == true)
  {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(40, 10);
    display.print("Anda");
    display.setCursor(40, 35);
    display.print("Cemas");
    String data2 = "Cemas";
    Firebase.setString(fbdo, "/DATA/StressVal", data2);
  }
  else if ((FuzzyOut >= 75 && FuzzyOut <= 100) && DisplayFuzzy_State == true)
  {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(40, 10);
    display.print("Anda");
    display.setCursor(40, 35);
    display.print("Stress");
    String data2 = "Stress";
    Firebase.setString(fbdo, "/DATA/StressVal", data2);
  }

  display.display();

  Firebase.setFloat(fbdo, "/DATA/BPM", BPM);
  Firebase.setFloat(fbdo, "/DATA/GSR", GSR);
  Firebase.setFloat(fbdo, "/DATA/SUHU", SUHU);
  Firebase.setFloat(fbdo, "/DATA/StressVariable", FuzzyOut);

  goto setScreenDefuzzyfikasi;
  //----------------------------------------------------------------------------------//

  //----------------------------------Screen Cek BPM---------------------------------//
setScreenCekBPM:
  if (digitalRead(Pb_BACK) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_BACK) == tekan)
    {
      goto setMENU2;
    }
  }

  //--> for Clearing the display
  TampilBPMtoOled();

  goto setScreenCekBPM;
  //----------------------------------------------------------------------//

  //---------------------------Screen Cek Suhu Tubuh---------------------------//
setScreenCekSuhu:
  if (digitalRead(Pb_BACK) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_BACK) == tekan)
    {
      goto setMENU3;
    }
  }
  TampilDStoOled();

  goto setScreenCekSuhu;
  //------------------------------------------------------------------------//

  //---------------------------Screen Connect WiFi---------------------------//
setScreenConnectWiFi:
  if (digitalRead(Pb_BACK) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_BACK) == tekan)
    {
      goto setMENU4;
    }
  }
  if (wifiState == false)
  {
    Serial.printf("Connecting to %s ", ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
      wifiState = false;
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.setCursor(0, 15);
      display.print("Harap Tunggu Sebentar");
      display.display();
    }
    wifiState = true;
  }
  else
  {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(20, 15);
    display.print("Terkoneksi ke ");
    display.setCursor(20, 25);
    display.print(ssid);
    display.display();
  }

  goto setScreenConnectWiFi;
  //------------------------------------------------------------------------//
}
//---------------------------------------------------------------------------------------------------------------------------------//

//--------------------------------------------------------Fungsi Loop--------------------------------------------------------//
void loop()
{
  if (digitalRead(Pb_OK) == tekan)
  {
    delay(BOUNCE);
    while (digitalRead(Pb_OK) == tekan)
    {
      display.clearDisplay();
      screen1();
    }
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(40, 25);
  display.print("HAI");
  display.display();

  Serial.println(Pb_OK_State);
  // Serial.println("");
  // Serial.println(halaman);
  // delay(BOUNCE);
}
//---------------------------------------------------------------------------------------------------------------------------------//

/*--------------------------------------------------*/
/*-------------- Tasks Handle 1 --------------*/
/*--------------------------------------------------*/

void TaskHandle1(void *pvParameters)
{
  (void)pvParameters;

  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for (;;)
  {
    if (OKE == true && cekBPM_State == false)
    {
      GetHeartRate();
    }
  }
}
