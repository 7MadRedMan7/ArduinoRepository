 #include <init_variables.h>
 #include <change_panel_digits.h>
 #include <display_digits.h>
 #include <display_leds.h>
 #include <init_devices.h>
 #include <read_keyboard.h>
 #include <set_out.h>
 #include <send_data.h>
 #include <LittleFS_Mbed_RP2040.h>

 change_panel_dig change_panel_digits;
init_var init_variables;
 display_d display;
 display_l display_leds;
 init_d init_devices;
 read_kb read_keyboard;
 set_out set_out;
 send_d send_data;

#define LFS_MBED_RP2040_VERSION_MIN_TARGET      "LittleFS_Mbed_RP2040 v1.1.0"
#define LFS_MBED_RP2040_VERSION_MIN             1001000

#define _LFS_LOGLEVEL_          1
#define RP2040_FS_SIZE_KB       1024

#define FILE_QUAN 10

#define FORCE_REFORMAT          false

LittleFS_MBED *myFS;

// #define LFS_MBED_RP2040_VERSION_MIN_TARGET      "LittleFS_Mbed_RP2040 v1.1.0"
// #define LFS_MBED_RP2040_VERSION_MIN             1001000
// #define _LFS_LOGLEVEL_          1
// #define RP2040_FS_SIZE_KB       1024
// #define FILE_QUAN 10

// #define FORCE_REFORMAT          false

// extern void deleteFile(const char* path);
// extern void readFile(const char * path);
// extern void writeFile(const char * path, const char * message, size_t messageSize);

void read_kb::deleteFile(const char* path)
{
	Serial.print("Deleting file: ");
	Serial.print(path);

	if (remove(path) == 0)
	{
		Serial.println(" => OK");
	}
	else
	{
		Serial.println(" => Failed");
		return;
	}
}
void read_kb::readFile(const char * path)
{
  Serial.print("Reading file: ");
  Serial.print(path);

  FILE *file = fopen(path, "r");

  if (file)
  {
    Serial.println(" => Open OK");
  }
  else
  {
    Serial.println(" => Open Failed");
    return;
  }

  
  uint32_t numRead = 1;
  
  while (numRead)
  {
    numRead = fread( &init_variables.panel_data[0][0], sizeof(uint8_t), 8800, file);
   Serial.print(numRead);
   Serial.print("\n");
   if (numRead){
   for(int i =0; i<100; i++){
    for(int j =0; j<88; j++){
      Serial.print(init_variables.panel_data[i][j]);
    }
    Serial.print("\n");
   }
    
     
   }
  }

  fclose(file);
}
void read_kb::writeFile(const char * path, const char * message, size_t messageSize)
{
  Serial.print("Writing file: ");
  Serial.print(path);

  FILE *file = fopen(path, "w");

  if (file)
  {
    Serial.println(" => Open OK");
  }
  else
  {
    Serial.println(" => Open Failed");
    return;
  }

  if (fwrite((uint8_t *) message, 1, messageSize, file))
  {
    Serial.println("* Writing OK");
  }
  else
  {
    Serial.println("* Writing failed");
  }

  fclose(file);
}
void setup() {
  Serial.begin(115200);

 // while (!Serial)  {
    delay(1000);
  //}
  Serial.print("\nStart LittleFS_Test on ");
  Serial.println(BOARD_NAME);
  Serial.println(LFS_MBED_RP2040_VERSION);

#if defined(LFS_MBED_RP2040_VERSION_MIN)

	if (LFS_MBED_RP2040_VERSION_INT < LFS_MBED_RP2040_VERSION_MIN)
	{
		Serial.print("Warning. Must use this example on Version equal or later than : ");
		Serial.println(LFS_MBED_RP2040_VERSION_MIN_TARGET);
	}

#endif

	myFS = new LittleFS_MBED();

	if (!myFS->init())
	{
		Serial.println("LITTLEFS Mount Failed");

		return;
	}
  init_variables.init_variables();
  init_devices.init_devices();
  init_variables.test_sygnal = 0xF;
  init_devices.clear_leds();
  init_devices.clear_digits();

    //  for (int i=0; i<10; i++){
    //    sprintf(init_variables.fileName, "/littlefs/Panel_%d.txt", i);
    //    Serial.println(init_variables.fileName);
    //    for(int j =0; j<PANEL_PER_FILE; j++){
    //       for(int g =0; g<TESTS_IN_FILE; g++){
    //        init_variables.panel_data[j][g] = 0;
    //        }
    //    }
    //    read_keyboard.writeFile(init_variables.fileName, (const char*)init_variables.panel_data, sizeof(init_variables.panel_data));
    //    Serial.print("\n");
    //    Serial.print(sizeof(init_variables.panel_data));
    //    read_keyboard.readFile(init_variables.fileName);
    //    Serial.print("\n");
    //  }
//  for (uint8_t i; i < 10; i++) {
//          sprintf(init_variables.fileName, "/littlefs/Panel_%d.txt", i);
//          Serial.println(init_variables.fileName);
//          read_keyb.deleteFile(init_variables.fileName);
//      }
  
     
  change_panel_digits.change_panel_digits();
  Serial.println("0");

                init_variables.num_panel = 0;
                digitalWrite(PIN_WORK, 1);
                init_variables.ctrl_led = 0;
                display_leds.display_mod();

                for (int i = 3; i >= 0; i--) {
                    init_variables.num_panel = init_variables.num_panel * 10 + init_variables.num_panel_arr[i];
                }
                Serial.println("Saved to panel");

                init_variables.saved_panel = 1;
                display_leds.display_mod();
                Serial.println(init_variables.num_panel);
                sprintf(init_variables.fileName, "/littlefs/Panel_%d.txt", init_variables.num_panel / 100);
                Serial.println(init_variables.fileName);
                read_keyboard.readFile(init_variables.fileName);
                init_variables.work_on = 0;
               init_variables.key_enable = 0x1;
                init_variables.saved_panel = 0;
                display_leds.display_mod();
                Serial.println("Edit mode:  ");
                change_panel_digits.change_num_digits();
                display_leds.display_leds(init_variables.panel_data[init_variables.num_panel%100][init_variables.num_pin]);
                for (int i = 0; i < 88; i++) {
                    init_variables.one_panel_data[i] = init_variables.panel_data[init_variables.num_panel % 100][i];
                    Serial.print(init_variables.one_panel_data[i]);
                    Serial.print(", ");
                }
                for (int i = 0; i < 16; i++) {
                    if (init_variables.panel_data[init_variables.num_panel % 100][72+i] == init_variables.num_pin) {
                        init_variables.num_ch_la = i;
                        break;
                    }
                    else {
                        init_variables.num_ch_la = 0;
                    }
                }
                change_panel_digits.change_la_digits();

                
                //Wire.beginTransmission(ADDR_KEY);
                ////      Wire.write(0x0f);
                //Wire.write(0xff & ((init_variables.work_mode_led) ? 0x7F : 0xFF);
                //Wire.write(scan[i]);
                //Wire.endTransmission();
                //Wire.requestFrom(ADDR_KEY, 2);
                
                if (init_variables.work_on == false) {

                }
                Serial.println("save");
}

void loop() {

  read_keyboard.read_keyboard();
 // display_leds.display_leds(1);
}
