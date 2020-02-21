
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
