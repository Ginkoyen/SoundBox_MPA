#include <SPI.h>
#include <SD.h>

/* - 16 Bits (Mono) - */
#define bitSound0 22
#define bitSound1 23
#define bitSound2 24
#define bitSound3 25
#define bitSound4 26
#define bitSound5 27
#define bitSound6 28
#define bitSound7 29

#define bitSound8 32
#define bitSound9 33
#define bitSound10 34
#define bitSound11 35
#define bitSound12 36
#define bitSound13 37
#define bitSound14 38
#define bitSound15 39

/* - Commande - */
#define bitStart 4

/* - SD Card - */
#define SD_SCK 13
#define SD_MISO 50
#define SD_MOSI 51
#define SD_SS 53
#define SD_CS 53

File Fichier;

typedef enum AudioMode 
{ 
  MONO = 1, STEREO = 2 
} AudioMode;

typedef struct SoundState
{
  File SoundFile;
  AudioMode audioMode = MONO;
  
  bool readStereo = true;
  
  int bitNumber = 0;
  int cursorPos = 0;
  
  // State Parseur
} SoundState;

// Retourne puissance d'une valeur
int puis(int val, int pui)
{
    int valPui = 1;

    for (int i = 0; i < pui; i++)
    {
        valPui *= val;
    }
    return valPui;
}

// Ecriture sur les bits son
void writeSoundBits(int bitw[16])
{
  digitalWrite(bitSound0, bitw[0]);
  digitalWrite(bitSound1, bitw[1]);
  digitalWrite(bitSound2, bitw[2]);
  digitalWrite(bitSound3, bitw[3]);
  digitalWrite(bitSound4, bitw[4]);
  digitalWrite(bitSound5, bitw[5]);
  digitalWrite(bitSound6, bitw[6]);
  digitalWrite(bitSound7, bitw[7]);
  delayMicroseconds(1000000/176400);
  digitalWrite(bitSound8, bitw[8]);
  digitalWrite(bitSound9, bitw[9]);
  digitalWrite(bitSound10, bitw[10]);
  digitalWrite(bitSound11, bitw[11]);
  digitalWrite(bitSound12, bitw[12]);
  digitalWrite(bitSound13, bitw[13]);
  digitalWrite(bitSound14, bitw[14]);
  digitalWrite(bitSound15, bitw[15]);
  delayMicroseconds(1000000/176400);
}

// Decode et lit un fichier son désencoder
int audioDecode(File *Fichier, int bitNumber, AudioMode audioMode, bool readStereo = true)
{
  int bytes, bitw[16] = {0};
  
  // Remplacer par pos curseur
  while (Fichier->available())
  {
    for (int i = 0; i < audioMode; i++)
    {
      for (int j = 0; j < (bitNumber/8); j++)
      {
        bytes = Fichier->read();

        for (int k = 7; k >= 0; k--)
        {
          bitw[k +(8*j)] = bytes%2;
          bytes = bytes / 2;
          
          if(bitw[k +(8*j)] == -1)
          {
            Serial.println("Erreur de communication !!");
            return -1;
          }
        }
      }
      /*if (bitNumber == 16)
        bitw[15] = (bitw[15] + 1) % 2;*/
      
      if (readStereo || (!readStereo && i == 0))
        writeSoundBits(bitw);
    }
  }
  if (!(Fichier->available()))
    return 1;
  return 0;
}


// Lecture d'un fichier son sur 16bits
int lecture_ecriture(char nomFichier[])
{
  if (!SD.begin(SD_CS))
    Serial.println("Communication impossible");
  else
    Serial.println("Communication Ok !");

  Fichier = SD.open(nomFichier);

  if(SD.exists(nomFichier))
    Serial.println("Existe !");

  if (Fichier)
  {
    Serial.println("Play !!");

    audioDecode(&Fichier, 16, STEREO, false);

    Serial.println("End !!");
    Fichier.close();
  }
  else
    Serial.println("Ouverture impossible du fichier");
}


void setup()
{
  pinMode(bitSound0, OUTPUT);
  pinMode(bitSound1, OUTPUT);
  pinMode(bitSound2, OUTPUT);
  pinMode(bitSound3, OUTPUT);
  pinMode(bitSound4, OUTPUT);
  pinMode(bitSound5, OUTPUT);
  pinMode(bitSound6, OUTPUT);
  pinMode(bitSound7, OUTPUT);
  pinMode(bitSound8, OUTPUT);
  pinMode(bitSound9, OUTPUT);
  pinMode(bitSound10, OUTPUT);
  pinMode(bitSound11, OUTPUT);
  pinMode(bitSound12, OUTPUT);
  pinMode(bitSound13, OUTPUT);
  pinMode(bitSound14, OUTPUT);
  pinMode(bitSound15, OUTPUT);
  
  digitalWrite(bitSound0, LOW);
  digitalWrite(bitSound1, LOW);
  digitalWrite(bitSound2, LOW);
  digitalWrite(bitSound3, LOW);
  digitalWrite(bitSound4, LOW);
  digitalWrite(bitSound5, LOW);
  digitalWrite(bitSound6, LOW);
  digitalWrite(bitSound7, LOW);
  digitalWrite(bitSound8, LOW);
  digitalWrite(bitSound9, LOW);
  digitalWrite(bitSound10, LOW);
  digitalWrite(bitSound11, LOW);
  digitalWrite(bitSound12, LOW);
  digitalWrite(bitSound13, LOW);
  digitalWrite(bitSound14, LOW);
  digitalWrite(bitSound15, LOW);
  
  pinMode(bitStart, INPUT);
  //Serial.begin(9600);
}
void loop()
{
  lecture_ecriture("1.wav");
}




void parseWAVFile ()
{
  
}



    /*int i, bytes, bitw, binMot;
    bool bit8Select = false, bitRight = false;

    while (Fichier.available())
    {
      if (bitStereo == true)
      {
        bytes = Fichier.read();

        for (i = 0; i < 8; i++)
        {
          bitw = bytes%2;
          bytes = bytes / 2;

          if (bitRight = false && bit8Select == false)
            if (bitw = 0)
              digitalWrite(bitSound0 + i, LOW);
            else if (bitw = 1)
              digitalWrite(bitSound0 + i, HIGH);
          else if (bitRight = false && bit8Select == true)
            if (bitw = 0)
              digitalWrite(bitSound8 + i, LOW);
            else if (bitw = 1)
              digitalWrite(bitSound8 + i, HIGH);
        }

        if (bitRight = false && bit8Select == false)
          bit8Select = true;
        else if (bitRight = false && bit8Select == true)
        {
          bit8Select = false;
          bitRight = true;
        }
        else if (bitRight = true && bit8Select == false)
          bit8Select = true;
        else if (bitRight = true && bit8Select == true)
        {
          bit8Select = false;
          bitRight = false;
        }
      }
    }*/
