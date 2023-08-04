TaskHandle_t Task1;
TaskHandle_t Task2;

void TaskHandle1(void *pvParameters);
void TaskHandle2(void *pvParameters);

//----------------------oled display-------------------------//
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET 4        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//--------Segala PerTombolan--------//
#define Pb_UP 18
#define Pb_DOWN 17
#define Pb_OK 16
#define Pb_BACK 19

#define BOUNCE 100

bool tekan = LOW;

bool Pb_UP_State = false;
bool Pb_DOWN_State = false;
bool Pb_OK_State = false;
bool Pb_BACK_State = false;

bool Pb_UP_Last_State = false;
bool Pb_DOWN_Last_State = false;
bool Pb_OK_Last_State = false;
bool Pb_BACK_Last_State = false;

bool UP = false;
bool DOWN = false;
bool OKE = false;
bool BACK = false;

byte halaman = 1;
byte menuItem = 1;

//---------------------- Segala Persensoran-------------------//
#define Sen_GSR 34
#define Sen_PHR 36

//------------------------------------------- PHR-------------------------------------------//
unsigned long previousMillisGetHR = 0; //--> will store the last time Millis (to get Heartbeat) was updated.
unsigned long previousMillisResultHR = 0;

const long intervalGetHR = 20; //--> Interval for reading heart rate (Heartbeat) = 10ms.
const long intervalResultHR = 10000;
const int LED_A1 = 2;

int PulseSensorSignal;

int UpperThreshold = 2300; //--> Determine which Signal to "count as a beat", and which to ingore.
int LowerThreshold = 2000;

int cntHB = 0;                //--> Variable for counting the number of heartbeats.
boolean ThresholdStat = true; //--> Variable for triggers in calculating heartbeats.
int BPMval = 0;

int x = 0;     //--> Variable axis x graph values to display on OLED
int y = 0;     //--> Variable axis y graph values to display on OLED
int lastx = 0; //--> The graph's last x axis variable value to display on the OLED
int lasty = 0;

// I drew this heart icon at : http://dotmatrixtool.com/
const unsigned char Heart_Icon[] PROGMEM = {
    0x00, 0x00, 0x18, 0x30, 0x3c, 0x78, 0x7e, 0xfc, 0xff, 0xfe, 0xff, 0xfe, 0xee, 0xee, 0xd5, 0x56,
    0x7b, 0xbc, 0x3f, 0xf8, 0x1f, 0xf0, 0x0f, 0xe0, 0x07, 0xc0, 0x03, 0x80, 0x01, 0x00, 0x00, 0x00};

//------------------------------------------- DS18b20-------------------------------------------//
#define ONE_WIRE_BUS 27
OneWire oneWire(ONE_WIRE_BUS);        // Membuat variabel oneWire berdasarkan PIN yang telah didefinisikan
DallasTemperature sensorDS(&oneWire); // Membuat variabel untuk menyimpan hasil pengukuran
float dataDS;

//------------------------------------------- GSR-------------------------------------------//
int sensorValue = 0;
int gsr_average = 0;
int dataGSR;

//------------------------------------------- Waktu-------------------------------------------//
unsigned long waktuSebelum = 0;
unsigned long interval = 200;

unsigned long waktuSebelum1 = 0;
unsigned long interval1 = 200;

unsigned long waktuSebelum2 = 0;
unsigned long interval2 = 1000;

byte CNTR = 0;
byte CNTR1 = 10;
byte CNTR2 = 10;

bool cekBPM_State = false;
bool cekGSR_State = false;
bool cekSUHU_State = false;
bool fuzzy_State = false;
bool DisplayFuzzy_State = false;

//-----------------------------------------------Firebase-----------------------------------------//
#define FIREBASE_HOST "stresstester-cb210-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "oIKMvcSWoH1GqlIuNt5X4olc3oA6NkZBil591EGe"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

String path = "/DATA";

//--------------------------------------------Connect to wifi----------------------------------//

const char *ssid = "KOST 82 KMR 1215161718";
const char *password = "1215161718";

bool wifiState = false;

//---------------------------------------------------------------------Perffuzzyan-------------------------------------//
int BPM = 0;
int GSR = 0;
float SUHU = 0;

float FuzzyOut = 0;

// Fuzzy
Fuzzy *fuzzy = new Fuzzy();

// FuzzyInput PHR
FuzzySet *Lambat = new FuzzySet(60, 60, 70, 80);
FuzzySet *Normal = new FuzzySet(70, 80, 80, 90);
FuzzySet *AgakCepat = new FuzzySet(80, 90, 90, 100);
FuzzySet *Cepat = new FuzzySet(90, 100, 110, 110);

// FuzzyInput GSR
FuzzySet *Kecil = new FuzzySet(1, 1, 2, 3);
FuzzySet *Sedang = new FuzzySet(2, 3, 3, 4);
FuzzySet *Besar = new FuzzySet(3, 4, 4, 5);
FuzzySet *SangatBesar = new FuzzySet(4, 5, 7, 7);

// FuzzyInput Suhu
FuzzySet *SangatDingin = new FuzzySet(32, 32, 33, 34);
FuzzySet *Dingin = new FuzzySet(33, 34, 34, 35);
FuzzySet *AgakDingin = new FuzzySet(34, 35, 35, 36);
FuzzySet *Normal1 = new FuzzySet(35, 36, 37, 37);

// FuzzyOutput TingkatSress
FuzzySet *Rileks = new FuzzySet(0, 12.5, 12.5, 25);
FuzzySet *Tenang = new FuzzySet(25, 37.5, 37.5, 50);
FuzzySet *Cemas = new FuzzySet(50, 62.5, 62.5, 75);
FuzzySet *Stress = new FuzzySet(75, 87.5, 87.5, 100);
//----------------------------------------------------------------------------------------------------------------------------//

// Jika di tekan akan mengubah status Pb UP
void TekanUp()
{
    if (Pb_UP_State != Pb_UP_Last_State)
    {
        if (Pb_UP_State == 0)
        {
            UP = true;
        }
        delay(50);
    }
    Pb_UP_Last_State = Pb_UP_State;
}

// Jika di tekan akan mengubah status Pb DOWN
void TekanDown()
{
    if (Pb_DOWN_State != Pb_DOWN_Last_State)
    {
        if (Pb_DOWN_State == 0)
        {
            DOWN = true;
        }
        delay(50);
    }
    Pb_DOWN_Last_State = Pb_DOWN_State;
}

// Jika di tekan akan mengubah status Pb OK
void TekanOk()
{
    if (Pb_OK_State != Pb_OK_Last_State)
    {
        if (Pb_OK_State == 0)
        {
            OKE = true;
        }
        delay(50);
    }
    Pb_OK_Last_State = Pb_OK_State;
}  

// Jika di tekan akan mengubah status Pb BACK
void TekanBack()
{
    if (Pb_BACK_State != Pb_BACK_Last_State)
    {
        if (Pb_BACK_State == 0)
        {
            BACK = true;
        }
        delay(50);
    }
    Pb_BACK_Last_State = Pb_BACK_State;
}
