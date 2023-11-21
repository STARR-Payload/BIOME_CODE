/*
 Copyright 2023 STARR Student Group at University of ALberta
 Lead: 2023, Christiaan Lemmer Venter, christiaanlemmer@hotmail.com
  
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
 
  1. Redistributions of source code must retain the above copyright notice,
     this list of conditions and the disclaimer below in the documentation
     and/or other materials provided with the distribution.
 
  2. Neither the name of the copyright holder nor the names of its
     contributors may be used to endorse or promote products derived from this
     software without specific prior written permission.
     
  3. Explict permission has been granted by an official current member of the STARR 
     student group at the University of ALberta that has granted authority over this 
     code and affiliated works. 
 
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))
#define MAX_QUEUE_SIZE 15
#define MAXGTHRESHOLD 13 // G's that trigger launch condition


struct Queue {
    float data[MAX_QUEUE_SIZE];
    int front;
    int rear;
    unsigned int size;
};

bool isFull(struct Queue *queue) {
    return queue->size == MAX_QUEUE_SIZE;
}

bool isEmpty(struct Queue *queue) {
    return queue->size == 0;
}

float pop(struct Queue *queue) {
    float value = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    queue->size--;
    return value;
}

void push(struct Queue *queue, float value) {
    if (isFull(queue)) {
        pop(queue);
    }
    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    queue->size++;
}


void printQueue(struct Queue *queue) {
    Serial.println("Queue Contents:");
    int index = queue->front;
    for (unsigned int i = 0; i < queue->size; ++i) {
        Serial.print(queue->data[index]);
        Serial.print(" ");
        index = (index + 1) % MAX_QUEUE_SIZE;
    }
    Serial.println();
}

/*
 * Function:  convolve 
 * --------------------
 *  Takes average of 25 most recent acceleration data
 *
 *  x[]: 25 most recent acceleration data
 *
 *  returns: Average of acceleration 
 */
float convolve(float x[]) {
  float y;
  for (int i = 0; i<MAX_QUEUE_SIZE; i++) {
    y += x[i];
  }
  y = (y/MAX_QUEUE_SIZE) - 9.81;
  return abs(y) / 9.81;
}

int launchDetecter(float *accelarray) {
  return convolve(accelarray) > MAXGTHRESHOLD ? 1 : 0;
}