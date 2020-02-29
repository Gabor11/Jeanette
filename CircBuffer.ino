
#define TRACKED_SENSOR_STATES  22


struct CircBuf{
    struct SensorState *buffer;
    byte head;
    byte tail;
    byte size; //of the buffer
};

struct SensorState{
  byte regulatorValue;
  int regarr[5];
};

int CircBufDifferential(struct CircBuf *cbuf);

int CircBufSum(struct CircBuf *cbuf);

void CircBufPrint(struct CircBuf *cbuf);

int CircBufReset(struct CircBuf *cbuf);

bool CircBufEmpty(struct CircBuf *cbuf);

bool CircBufFull(struct CircBuf cbuf);

int CircBufPut(struct CircBuf * cbuf, int8_t data);

//int CircBufGet(struct CircBuf * cbuf, int8_t * data);

int CircBufLast(struct CircBuf *cbuf, int *data);

/* INITIALIZE CIRCULAR BUFFER */

void CircBufInit(struct CircBuf *cbuf);

CircBuf cbuf;

int CircBufDifferential(struct CircBuf *cbuf)
{
  int previous = (cbuf->head + TRACKED_SENSOR_STATES - 1) % cbuf->size;
  int beforeprevious = (cbuf->head + TRACKED_SENSOR_STATES - 2) % cbuf->size;

  return cbuf->buffer[previous].regulatorValue - cbuf->buffer[beforeprevious].regulatorValue;
}

int CircBufSum(struct CircBuf *cbuf)
{
    int position = 0;
    int sum = 0;

    for (int i = 0; i < TRACKED_SENSOR_STATES - 1; i++) {
      position = (cbuf->tail + i) % cbuf->size;
      if (position == cbuf->head)
        break;
        sum += cbuf->buffer[position].regulatorValue;
    }
    return sum;
}

void CircBufPrint(struct CircBuf *cbuf)
{
    int real_place;

    for (int i = 0; i < TRACKED_SENSOR_STATES - 1; i++) {
      real_place = (cbuf->tail + i) % cbuf->size;
//        printf("buf_data%d: %d\n", i, cbuf->buffer[real_place].regulatorValue);
    }
}

int CircBufReset(struct CircBuf *cbuf)
{
    int r = -1;

    if (cbuf) {
        cbuf->head = 0;
        cbuf->tail = 0;
        r = 0;
    }

    return r;
}

bool CircBufEmpty(struct CircBuf *cbuf)
{
    // We define empty as head == tail
    return (cbuf->head == cbuf->tail);
}

bool CircBufFull(struct CircBuf cbuf)
{
    // We determine "full" case by head being one position behind the tail
    // Note that this means we are wasting one space in the buffer!
    // Instead, you could have an "empty" flag and determine buffer full that way
    return ((cbuf.head + 1) % cbuf.size) == cbuf.tail;
}

int CircBufPut(struct CircBuf * cbuf, int8_t regulatorValue, int8_t regarr[5])
{
    int r = -1;

    if (cbuf) {
        cbuf->buffer[cbuf->head].regulatorValue = regulatorValue;
        for (int i = 0; i < 5; i++) {
          cbuf->buffer[cbuf->head].regarr[i] = regarr[i];
        }
        cbuf->head = (cbuf->head + 1) % cbuf->size;

        if (cbuf->head == cbuf->tail) {
            cbuf->tail = (cbuf->tail + 1) % cbuf->size;
        }

        r = 0;
    }

    return r;
}

//int CircBufGet(struct CircBuf * cbuf, int8_t * data)
//{
//    int r = -1;
//
//    if(cbuf && data && !CircBufempty(cbuf))
//    {
//        *data = cbuf->buffer[cbuf->tail];
//        cbuf->tail = (cbuf->tail + 1) % cbuf->size;
//
//        r = 0;
//    }
//
//    return r;
//}

int CircBufLast(struct CircBuf *cbuf, int8_t *data)
{
    int r = -1;
    int prevstuff;

    prevstuff = (cbuf->head + TRACKED_SENSOR_STATES - 1) % cbuf->size;

//    printf("prevstuff: %d\n", cbuf->buffer[prevstuff]);

    if(cbuf && data && !CircBufEmpty(cbuf))
    {
        *data = cbuf->buffer[prevstuff].regulatorValue;
        r = 0;
//        printf("Im here :) & the data is: %d\n", *data);
    }

    return r;
}

/* INITIALIZE CIRCULAR BUFFER */

void CircBufInit(struct CircBuf *cbuf)
{
    cbuf->size = TRACKED_SENSOR_STATES;
    cbuf->buffer = malloc(cbuf->size);
    CircBufReset(cbuf);
}
