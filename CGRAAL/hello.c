#include <stdio.h>
#include <dlfcn.h>
#define config "./cv_configuration.json"
   typedef struct{
        int checkResult;
        int lastErrorInSession;
        int ResultLoadingSoSymbols;
    } ResultCheck;
int main(){
	char *mas[] = { "/home/roland/Downloads/download/.build_l64/tests_data/2DA902591716A4805E5505DC3CF728B50ABC2801B655A043BB8858E971F8F477.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/BB54C8AD9890DCA36407862F847D07D1C4A9E3F2C6C987CACA5E49C8A05B3B4E.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/095F4A958B42AFF13F0FBB7BCE49D1E287E0E2F10CB811A3923C0372D7769142.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/EE45AEAAD1A31B1B1A45F4B38C98BE62893E590A47C1166061B0B1C52163531C.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/4E9B4A2B2504FD5B2ED94647B081AE472F1F515D2E5B627D47A94D02E85E0111.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/31D6A5FDC46F4BB9AC325DD9262B1C8D981D01F2B7B6EE84642BE930D170C05B.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/4CBC030B78E92EF3564B6FD82835815135359B3D5B608C5A9C4D28DF7E6F29E7.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/5404CB45AEE52AC629B55B8BA6532F8B24C79E2C8BF59D98DD5D73215511A918.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/cond_audacity_2.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/90E394CD40ED5C9CED32D52432005ECD2AE343A24FCF5C5BD78955FB0B6077EA.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/S00000000001/web_logitech_back_50-dB.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/S00000000001/fujimi_0_dB_back_37-40-dB.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/S00000000001/web_logitech_back_65-dB.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/S00000000001/fujimi_-10_dB_back_50-dB.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/S00000000001/mic_logitech_back_37-40-dB.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/S00000000001/fujimi_0_dB_back_50-dB.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/S00000000001/web_logitech_back_37-40-dB.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/S00000000001/fujimi_-10_dB_back_65-dB.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/S00000000001/mic_logitech_back_65-dB.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/S00000000001/fujimi_0_dB_back_65-dB.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/S00000000001/mic_logitech_back_50-dB.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/S00000000001/fujimi_-10_dB_back_37-40-dB.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000002/2.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000002/9.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000002/3.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000002/6.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000002/5.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000002/7.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000002/4.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000002/0.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000002/8.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000002/1.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000001/2.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000001/9.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000001/3.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000001/6.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000001/5.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000001/7.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000001/4.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000001/0.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000001/8.wav",
"/home/roland/Downloads/download/.build_l64/tests_data/N00000000001/1.wav" };
	typedef ResultCheck* (*lets_check)(char *,  char *);
	void* handle = dlopen("./libGBP.so", RTLD_NOW);
        if (!handle){
            
            return 1;
        }       
        lets_check load = (lets_check)(dlsym(handle, "lets_check"));
        if (!load)
        {
            return 3;
        }     
	
	for ( int i = 0; i<  42; i++ )
	{
		ResultCheck* res = load(config, mas[i]);
		printf("\n\nITEM==>%s\n", mas[i]);
		printf("\n%d, CHECK RESULT\n",res -> checkResult);
		printf("\n%d, last error session\n",res -> lastErrorInSession);
		printf("\n%d, CODE LOAD SO\n",res -> ResultLoadingSoSymbols);
		
	};
	return 0;
}

