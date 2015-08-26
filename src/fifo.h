/*
 * fifo.h
 *
 *  Created on: Aug 23, 2015
 *      Author: mauzy
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "globals.h"

#define QSIZE 20 //realistically, this thing should never have more than 1 item at a time.

/*typedef struct qnode {
	qnode_t * next;
	swevent_t data;
} qnode_t;

typedef struct queue {
	qnode_t * head;
	qnode_t * tail;
} fifo_t;*/

swevent_t fifo[QSIZE];

uint8_t head = 0, tail = 0;

int hw8stuff(void);
int enq(swevent_t * in);
swevent_t deq();

/*int fifo_init(fifo_t * fifo);
int enq(fifo_t * fifo, swevent_t * event);
swevent_t deq(fifo_t * que);*/



#endif /* FIFO_H_ */
