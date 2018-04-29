#define MAILBOX_BASE (0x3F00B880)
#define LED_CHANNEL 8

typedef struct {
  unsigned int * size;
  int req_code;
  int hdr_tag;
  int tag_data_size;
  int req_res_size;
  int pin_number;
  int pin_state;
  int gpu_signal;
} mailmsg;

unsigned int size = sizeof(mailmsg);

mailmsg message __attribute__((aligned(4))) =
{ &size,
  0,
  0x00038041,
  8,
  0,
  130,
  1,
  0 };


void
delay (void)
{
  unsigned int counter = 0xF00000;
  
  while (counter)
    counter--;

  return;
}

void
mailbox_write (unsigned int msg)
{
  char * mailbase = (char *) MAILBOX_BASE;
  unsigned int res;

  do {
    res =  *((unsigned int *)(mailbase+0x38));
  } while  (res & 0x80000000);

  *((unsigned int *)(mailbase+0x20)) = msg;
  
  return;
}

unsigned int
mailbox_read (unsigned int chn)
{
  char * mailbase = (char *) MAILBOX_BASE;
  unsigned int mailstatus;
  unsigned int response;
  unsigned int chn2;

  do {
    do {
      mailstatus =  *((unsigned int *)(mailbase+0x18));
    } while (mailstatus & 0x40000000);

    response = *((unsigned int *) mailbase);
    chn2 = response & 0x0F;
  } while (chn2 != chn);

  return response & ~(0x0000000F);
}

void
set_led_state(unsigned int st)
{
  unsigned int readret;
  
  message.req_code = message.req_res_size = 0;
  message.pin_number = 130;
  message.pin_state = st;

  mailbox_write(((unsigned int)&message) | LED_CHANNEL);
  readret = mailbox_read(LED_CHANNEL);
}

void
notmain (void)
{

  /* uart_init(); */
  /* uart_string("Me cago en dios\r\n"); */
	
  while (1)
    {
      delay();
      set_led_state(1);
      delay();
      set_led_state(0);
    }

  while (1){;}
	
}
