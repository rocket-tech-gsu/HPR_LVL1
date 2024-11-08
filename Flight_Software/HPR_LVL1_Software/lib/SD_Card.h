#include <SD.h>
#include <SPI.h>

class SD_card{
    private:
    public:
        File myfile;
        String data;
        int cs=4;
        void startup();
        void Write(String Input);
        String Read(String File_name);
};

void SD_card::startup(){
  try{
    // Initilizing the SD card:
    if (!SD.begin(cs))
    {
      delay(500);
      Serial.println("Card failed, or not present");
    }
    else
    {
        Serial.println("card initialized.");
    }

    // W R I T I N G   D A T A:
    myfile = SD.open("data.csv",FILE_WRITE | O_TRUNC);
    String val1 = "Testing";
    String val2 = "Storing String";
    String val3 = val1 + "," + val2;
    if (myfile) {
      myfile.println(val3);
      myfile.close();
      // print to the serial port too:
      Serial.println("The following data has been added to your file:");
      // Serial.println(val3);
    }
    else {
      Serial.println("error opening data.csv");
    }

    // R E A D I N G   D A T A:
    myfile= SD.open("data.csv", FILE_READ);
    if(myfile){
      while (myfile.available()) {
      Serial.println(myfile.readString());
      }
    }
    else {
      Serial.println("Reading File Doesn't Work! \nor\nThe file you're trying to read doesn't exist");
    }
    }
    catch{
      Serial.printf("\n\nAbort Recommendation! – SD card is not working\n\n ");
    }
}

void SD_card::Write(String input){
  // W R I T I N G   D A T A:
  myfile = SD.open("data.csv",FILE_WRITE | O_TRUNC);
  if (myfile) {
    myfile.println(input);
    myfile.close();
    Serial.println("SD Card Logging Successfully ...");
  }
  else {
    Serial.println("Error opening data.csv");
  }
}

String SD_card::Read(String File_name)
{
  // R E A D I N G   D A T A:
  myfile= SD.open("data.csv", FILE_READ);
  if(myfile){
    while (myfile.available()) {
    Serial.println(myfile.readString());
    }
  }
  else {
    Serial.println("File Might Not Exist!");
  }
}
