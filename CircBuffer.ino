
#define TRACKED_SENSOR_STATES  22


struct CircBuf{
    byte *buffer;
    byte head;
    byte tail;
    byte size; //of the buffer
};

int CircBufDifferential(CircBuf *cbuf);

int CircBufSum(CircBuf *cbuf);

void CircBufPrint(CircBuf *cbuf);

int CircBufReset(CircBuf *cbuf);

int CircBufEmpty(CircBuf *cbuf);

int CircBufFull(CircBuf cbuf);

int CircBufPut(CircBuf * cbuf, int8_t data);

//int CircBufGet(CircBuf * cbuf, int8_t * data);

int CircBufLast(CircBuf *cbuf, int *data);

/* INITIALIZE CIRCULAR BUFFER */

void CircBufInit(CircBuf *cbuf);

CircBuf cbuf;

int CircBufDifferential(CircBuf *cbuf)
{
  int previous = (cbuf->head + TRACKED_SENSOR_STATES - 1) % cbuf->size;
  int beforeprevious = (cbuf->head + TRACKED_SENSOR_STATES - 2) % cbuf->size;

  return cbuf->buffer[previous] - cbuf->buffer[beforeprevious];
}

int CircBufSum(CircBuf *cbuf)
{
    int position = 0;
    int sum = 0;

    for (int i = 0; i < TRACKED_SENSOR_STATES - 1; i++) {
      position = (cbuf->tail + i) % cbuf->size;
      if (position == cbuf->head)
        break;
        sum += cbuf->buffer[position];
    }
    return sum;
}

void CircBufPrint(CircBuf *cbuf)
{
    int real_place;

    for (int i = 0; i < TRACKED_SENSOR_STATES - 1; i++) {
      real_place = (cbuf->tail + i) % cbuf->size;
//        printf("buf_data%d: %d\n", i, cbuf->buffer[real_place]);
    }
}

int CircBufReset(CircBuf *cbuf)
{
    int r = -1;

    if (cbuf) {
        cbuf->head = 0;
        cbuf->tail = 0;
        r = 0;
    }

    return r;
}

int CircBufEmpty(CircBuf *cbuf)
{
    // We define empty as head == tail
    return (cbuf->head == cbuf->tail);
}

int CircBufFull(CircBuf cbuf)
{
    // We determine "full" case by head being one position behind the tail
    // Note that this means we are wasting one space in the buffer!
    // Instead, you could have an "empty" flag and determine buffer full that way
    return ((cbuf.head + 1) % cbuf.size) == cbuf.tail;
}

int CircBufPut(CircBuf * cbuf, int8_t data)
{
    int r = -1;

    if (cbuf) {
        cbuf->buffer[cbuf->head] = data;
        cbuf->head = (cbuf->head + 1) % cbuf->size;

        if (cbuf->head == cbuf->tail) {
            cbuf->tail = (cbuf->tail + 1) % cbuf->size;
        }

        r = 0;
    }

    return r;
}

//int CircBufGet(CircBuf * cbuf, int8_t * data)
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

int CircBufLast(CircBuf *cbuf, int *data)
{
    int r = -1;
    int prevstuff;

    prevstuff = (cbuf->head + TRACKED_SENSOR_STATES - 1) % cbuf->size;

//    printf("prevstuff: %d\n", cbuf->buffer[prevstuff]);

    if(cbuf && data && !CircBufEmpty(cbuf))
    {
        *data = cbuf->buffer[prevstuff];
        r = 0;
//        printf("Im here :) & the data is: %d\n", *data);
    }

    return r;
}

/* INITIALIZE CIRCULAR BUFFER */

void CircBufInit(CircBuf *cbuf)
{
    cbuf->size = TRACKED_SENSOR_STATES;
    cbuf->buffer = malloc(cbuf->size);
    CircBufReset(cbuf);
}
