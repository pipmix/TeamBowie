#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

	struct js_event {
		unsigned int    time;
		short           value;
		unsigned char   type;
		unsigned char   number;
	};

int main(){

    int fd = open ("/dev/input/js0", O_RDONLY | O_NONBLOCK);
    struct js_event e;

    if (fd == 0) printf("Gamepad not found.\n");

    bool first = true;
    int startTime;


    while(true){

        usleep(1000);

 		while (read(fd, &e, sizeof(e)) > 0) {

                if (first) {
                    startTime = e.time;
                    first = false;
                }

                if (e.type == 0x01){

                    switch (e.number){
                        case 0:
                            cout << "Button 1       ";
                            break;
                        case 1:
                            cout << "Button 2       ";
                            break;
                        case 2:
                            cout << "Button 3       ";
                            break;
                        case 3:
                            cout << "Button 4       ";
                            break;
                        case 4:
                            cout << "L1             ";
                            break;
                        case 5:
                            cout << "R1             ";
                            break;
                        case 6:
                            cout << "L2             ";
                            break;
                        case 7:
                            cout << "R2             ";
                            break;
                        case 8:
                            cout << "Select         ";
                            break;
                        case 9:
                            cout << "Start          ";
                            break;
                        case 10:
                            cout << "L3             ";
                            break;
                        case 11:
                            cout << "R3             ";
                            break;
                    }

                    if (e.value == 0)cout << "Released   " ;
                    else cout <<             "Pressed    " ;
                    cout  << "\t at Time: " << e.time - startTime<< endl;

                }
                else if (e.type == 0x02){
                    switch (e.number){
                        case 0:
                            cout << "Left X-Axis:  ";
                            break;
                        case 1:
                            cout << "Left Y-Axis:  ";
                            break;
                        case 2:
                            cout << "Right X-Axis: ";
                            break;
                        case 3:
                            cout << "Right Y-Axis: ";
                            break;
                    }
                    if ( e.value == 0 )cout << "\t";
                    cout << e.value ;
                    cout  << "\t at Time: " << e.time - startTime<< endl;
                }
                else if (e.type == 0x80){
                }
        }
    }
    return 0;
}
