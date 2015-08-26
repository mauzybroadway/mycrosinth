/*
 * fifo.c
 *
 *  Created on: Aug 23, 2015
 *      Author: mauzy
 */
#include "fifo.h"

swevent_t getswitch();

int hw8stuff(void) {
	swevent_t out = getswitch();

	if(out.sw <= 13) {
		if(out.pr != 0) {
			switch(out.sw) {
				case 1 : if (vdisplay[0] < 15) vdisplay[0]++; break;
				case 3 : if (vdisplay[1] < 15) vdisplay[1]++; break;
				case 5 : if (vdisplay[2] < 15) vdisplay[2]++; break;
				case 7 : if (vdisplay[3] < 15) vdisplay[3]++; break;
			}
		} else {
			switch(out.sw) {
				case 2 : if (vdisplay[0] > 0) vdisplay[0]--; break;
				case 4 : if (vdisplay[1] > 0) vdisplay[1]--; break;
				case 6 : if (vdisplay[2] > 0) vdisplay[2]--; break;
				case 8 : if (vdisplay[3] > 0) vdisplay[3]--; break;
			}
		}
	}

	return 0;
}

/*int fifo_init(fifo_t * fifo) {
	fifo->head = NULL;
	fifo->tail = NULL;

	return 0; //add some error checking here maybe
}

int enq (fifo_t fifo, swevent_t * event) {
	qnode_t node;
	node->next = NULL;
	(node->data).pr = event->pr;
	(node->data).sw = event->sw;
	(node->data).msec = event->msec;

	if (fifo->head == NULL) {
		fifo->head =
	}
}

swevent_t * deq (fifo_t fifo) {

}*/


int enq(swevent_t * in) {
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

swevent_t deq() {
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
}

swevent_t getswitch(void)
{
	swevent_t out = deq();
	return out;
}

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
