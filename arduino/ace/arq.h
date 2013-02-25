#ifndef ARQ_H
#define ARQ_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <inttypes.h>

#include "framing.h"


typedef enum {
  RECEIVED = 0,
  SEND_SUCCESS = 1,
  NO_ACK = 3,
  BAD_ACK = 4,
  SIZE_ERROR = 5,
  BUSY = 6
} message_event;

typedef void (*send_frame_function)(int16_t size, uint8_t* data);
typedef void (*message_event_function)(message_event e, int16_t size, const uint8_t* const message);
typedef void (*void_function)();

typedef struct {
  uint8_t last_sent_buffer[MAX_FRAME_SIZE];
  int16_t last_sent_size;
  uint8_t last_received_seq;
  uint8_t resends;
  bool awaiting_ack;
  
  send_frame_function sender;
  message_event_function event_handler;
  void_function start_timer;
  void_function stop_timer;
  
} arq;

void init_arq(arq* a);
void receive_frame(arq* a, int16_t size, uint8_t* data);
void timeout(arq* a);
void send_message(arq* a, int16_t size, const uint8_t * const message);



#ifdef __cplusplus
} // extern "C"
#endif

#endif /* ARQ_H */
