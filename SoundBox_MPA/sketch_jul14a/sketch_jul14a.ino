
/* ################
 *  NOTES
 *
 *  les chaines de characters C se terminent toujours par '\0' donc les programmes connaisssent leurs tailles
 *  
 *  main (argc = nombre d`arguments passes, argv = valeurs d`arguments)
 *  fread (buffer, nb_elem, size_of_one_elem, file_descriptor)
 *
 * ################
 */

#include <SPI.h>
#include <SD.h>

/* - SD Card - */
#define SD_SCK 13
#define SD_MISO 50
#define SD_MOSI 51
#define SD_SS 53
#define SD_CS 53

#define WAVE_HEADER_SIZE 44
struct WaveHeader {
    
    /* - Bloc de déclaration d'un fichier au format WAVE - */
    uint32_t FileTypeBlocID;  ///< Const "RIFF" 
    uint32_t FileSize;        ///< Size of File minus 8 bytes
    uint32_t FileFormatUD;    ///< Format name "WAVE"
    /* - Bloc décrivant le format audio - */
    uint32_t FormatBlocID;    ///< ID "fmt "
    uint32_t BlocSize;        ///<
    uint16_t AudioFormat;     ///<
    uint16_t NbrCanaux;       ///<
    uint16_t Frequence;       ///<
    uint32_t BytePerSec;      ///<
    uint16_t BytePerBloc;     ///<
    uint16_t BitsPerSample;   ///<
    /* - Bloc des donnée"s - */
    uint32_t DataBlockID;     ///< Const "data
    uint32_t DataSize;        ///<

};

// --- read a wave header from a file on SDCard ---
void readWavHeaderFromSDFile (void* data, const char* inputFile) { 
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    
    // TODO close existing file if any, to check !
    
    Serial.println("ok !!"); 
    File dataFile = SD.open(inputFile);

   // if the file is available, write to it:
   if (dataFile) {
     dataFile.read(data, WAVE_HEADER_SIZE);
     dataFile.close();
   }
   // if the file isn't open, pop up an error:
   else {
     Serial.println("error opening datalog.txt");
   }
}

/*
// --- x86 read Wave Header ---
void readHeader (void* data, const char* inputName) {
    File* f = fopen (inputName, "rb");
    if (! f ) {
        fprintf (stderr, "error opening file : %s\n", inputName);
        exit (-1);
    }
    fread (data, 1, WAVE_HEADER_SIZE, f);
    fclose (f);
}
*/

// --- call when arduino is booting ---
void setup() {
   // Open serial communications and wait for port to open:
   Serial.begin(9600);
}
void loop () {
    Serial.println("Initializing SD card...");
    
    if (!SD.begin(SD_CS))
      Serial.println("Communication impossible");
    else
      Serial.println("Communication Ok !");

    if(SD.exists("1.wav"))
      Serial.println("Existe !");   
    
    WaveHeader header;
    readWavHeaderFromSDFile (&header, "1.wav");

    Serial.print("Frequence : ");
    Serial.println(header.Frequence, DEC);

    Serial.print("Size of File : ");
    Serial.println(header.FileSize, DEC);
}



/*
// --- x86 main ---
int main (int argc, char** argv) {
    WaveHeader header;
    if (argc <= 2) {
        fprintf (stderr, "invalid number of arguments \n");
        exit (-1);
    }
    readHeader (&header, argv[1]);

    return (0);    
}
*/
