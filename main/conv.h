#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))
#define MAX_QUEUE_SIZE 25
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
    if (isEmpty(queue)) {
        return -1; // Return a sentinel value or handle the error as needed.
    }

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


float convolve(float x[])
{
  float y;
  for (int i = 0; i<MAX_QUEUE_SIZE; i++)
  {
    y += x[i];
  }
  return ((y*-1)/25) - 9.8;
}

int launchDetecter(float *accelarray) {
  return convolve(accelarray) > MAXGTHRESHOLD ? 1 : 0;
}