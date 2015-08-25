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

typedef struct qnode {

} qnode_t;


swevent_t fifo[QSIZE];
//unsigned int head = 0, tail = 0;

int queue(swevent_t * in);
swevent_t dequeue();



#endif /* FIFO_H_ */
