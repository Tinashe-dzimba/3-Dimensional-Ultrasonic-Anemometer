
#include <ADC.h>
#include <ADC_util.h>
#include <SD.h>
File Sample_file;

const int readPin = A9; // ADC0

ADC *adc = new ADC(); // adc object

void setup() {


    pinMode(9, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(readPin, INPUT);
    

    Serial.begin(9600);

    Serial.print("Initializing SD card...");
        if (!SD.begin(BUILTIN_SDCARD)) {
                  Serial.println("initialization failed!");
                  while (1);
        }
    Serial.println("initialization done.");

    adc->adc0->setAveraging(0); // set number of averages
    adc->adc0->setResolution(16); // set bits of resolution

    // it can be any of the ADC_CONVERSION_SPEED enum: VERY_LOW_SPEED, LOW_SPEED, MED_SPEED, HIGH_SPEED_16BITS, HIGH_SPEED or VERY_HIGH_SPEED
    // see the documentation for more information
    // additionally the conversion speed can also be ADACK_2_4, ADACK_4_0, ADACK_5_2 and ADACK_6_2,
    // where the numbers are the frequency of the ADC clock in MHz and are independent on the bus speed.

    ///// ADC0 ////
    // reference can be ADC_REFERENCE::REF_3V3, ADC_REFERENCE::REF_1V2 (not for Teensy LC) or ADC_REFERENCE::REF_EXT.
    adc->adc0->setReference(ADC_REFERENCE::REF_1V2); // change all 3.3 to 1.2 if you change the reference to 1V2


    // always call the compare functions after changing the resolution!
    adc->adc0->enableCompare(1.0/3.3*adc->getMaxValue(), 0); // measurement will be ready if value < 1.0V

    
    adc->adc0->setConversionSpeed(ADC_CONVERSION_SPEED::ADACK_4_0); // change the conversion speed
    // it can be any of the ADC_MED_SPEED enum: VERY_LOW_SPEED, LOW_SPEED, MED_SPEED, HIGH_SPEED or VERY_HIGH_SPEED
    adc->adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED); // change the sampling speed 
    //Sampling speed of very high speed was used as it uses +0ADCK so it should be in synch with our clock.

     adc->adc0->startContinuous(readPin);

    // If you enable interrupts, notice that the isr will read the result, so that isComplete() will return false (most of the time)
    adc->adc0->enableInterrupts(adc0_isr);

 
}

int value = 0;
int count_exp;
const int num_samp = 20000;
void loop() {
            
            count_exp = 0;
            //Open the file in the SD card
            Sample_file = SD.open("new_test_0.txt", FILE_WRITE);
            adc->adc0->startContinuous(readPin);

            tone(9,40000,0.0001);
            delay(5000);
            Sample_file.close();
            
            Serial.println("You can take out the SD card now");
            delay(2000);
            
            }

void adc0_isr(void) {
    Sample_file.println((uint16_t)adc->adc0->analogReadContinuous()*3.3/adc->adc0->getMaxValue(),DEC);
    digitalWriteFast(LED_BUILTIN, !digitalReadFast(LED_BUILTIN)); // Toggle the led
}
