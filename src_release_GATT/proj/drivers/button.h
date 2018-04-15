


#define BUTTON_DISAPPEAR_SHAKE_TIMER   300000

#define MAX_BUTTON_NUM                 5
 
typedef void (*buttonPressedCb_t)(u32 pin);

void button_config(u32 pin);
void button_registerCb(buttonPressedCb_t cb);
