/*
 * fifo.c
 *
 *  Created on: Aug 23, 2015
 *      Author: mauzy
 */
#include "fifo.h"


int queue(swevent_t * in) {
	if(in->sw <= 13) {
		if(in->pr != 0) {
			switch(in->sw) {
				case 1 : if (vdisplay[0] < 15) vdisplay[0]++; break;
				case 3 : if (vdisplay[1] < 15) vdisplay[1]++; break;
				case 5 : if (vdisplay[2] < 15) vdisplay[2]++; break;
				case 7 : if (vdisplay[3] < 15) vdisplay[3]++; break;
			}
		} else {
			switch(in->sw) {
				case 2 : if (vdisplay[0] > 0) vdisplay[0]--; break;
				case 4 : if (vdisplay[1] > 0) vdisplay[1]--; break;
				case 6 : if (vdisplay[2] > 0) vdisplay[2]--; break;
				case 8 : if (vdisplay[3] > 0) vdisplay[3]--; break;
			}
		}
	}
}


/*int queue(swevent_t * in) {
	if(tail < QSIZE){
		//fifo[tail].pr = in->pr;
		//fifo[tail].sw = in->sw;
		//fifo[tail++].msec = in->msec;
		fifo[tail++] = *in;
		return 0;
	} else {
		return -1;
	}
}

swevent_t dequeue() {
	unsigned int tmp = head, i;

	if(tail == 0) {
		swevent_t KILL;
		KILL.pr = 1;
		KILL.sw = 20;
		return KILL;			// return an invalid switch event
	}

	swevent_t tmpsw = fifo[0];

	//screw_it();

	for (i = 0; i < tail - 1; i++) {
		fifo[i] = fifo[i + 1];
	}

	tail--;

	return tmpsw;
}*/

/*swevent_t getswitch(void)
{
	swevent_t out = dequeue();
	return out;
}*/

/*void hw8stuff(void)
{
	static unsigned int things[4] = {0,0,0,0};
	swevent_t out = getswitch();

	if(out.sw <= 13) {
		if(out.pr != 0) {
			switch(out.sw) {
				case 1 : if (vdisplay[0] < 15) vdisplay[0]++; break;
				//case 3 : if (vdisplay[1] < 15) vdisplay[1]++; break;
				//case 5 : if (vdisplay[2] < 15) vdisplay[2]++; break;
				//case 7 : if (vdisplay[3] < 15) vdisplay[3]++; break;
			}
		} else {
			switch(out.sw) {
				case 2 : if (vdisplay[0] > 0) vdisplay[0]--; break;
				//case 4 : if (vdisplay[1] > 0) vdisplay[1]--; break;
				//case 6 : if (vdisplay[2] > 0) vdisplay[2]--; break;
				//case 8 : if (vdisplay[3] > 0) vdisplay[3]--; break;
			}
		}
	}
}

void synthstuff(void)
{
	swevent_t out = getswitch();

	if(out.sw <= 13) {
		if(out.pr != 0) {	// pressed
			//switch(out.sw) {
			//	case 1 : note[0] = 1;
			//}
			note[0] = out.sw;
			vdisplay[0] = out.sw;
		} else {					// released
			//switch(out.sw) {
			//	case 2 : note[0] = 0;
			//}
			note[0] = 0;
			vdisplay[0] = 0;
		}
	}
}*/
