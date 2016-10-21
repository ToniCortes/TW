#include <time.h>
#include "pebble.h"
#include "annimation.h"
#include "date2textCat.h"
#include "date2textEsp.h"
#include "date2textEng.h"

#define SETTINGS_KEY 1

typedef struct ClaySettings {
  GColor TextColor;
  GColor BackGroundColor;
  int Language;
  bool BlueTooth;
  bool ShowDate;
} ClaySettings;

static ClaySettings Param;

static Window *window;
GRect b_screen, b_layer1, b_layer2, b_layer3, b_layer4;
TextLayer *layer1, *layer2, *layer3, *layer4;

char line1[20];
char line2[20];
char line3[20];
char day[20];

GBitmap *net_bitmap;
BitmapLayer *bottom_bm_layer;
TextLayer *top_bt_layer;
bool lastBTconnection = 0;
int no_bt_countdown = 0;



// This function decides how each layer will be Aligned

GTextAlignment RandomPlacement(){
  GTextAlignment i=GTextAlignmentRight;
  switch (rand()%3){
    case 0: i=GTextAlignmentRight; break;
    case 1: i=GTextAlignmentLeft; break;
    case 2: i=GTextAlignmentCenter; break;
  }
  return(i);
}

void date2text(struct tm *tick_time, char *line1, char* line2, char *line3, char *day, bool ShowDate)
{
  APP_LOG(0, "date2text %c %d\n", Param.Language, Param.Language);
  switch (Param.Language) {
    case 'C': date2textCat(tick_time, line1, line2, line3, day, ShowDate); break;
    case 'S': date2textEsp(tick_time, line1, line2, line3, day, ShowDate); break;
    case 'E': date2textEng(tick_time, line1, line2, line3, day, ShowDate); break;
  }
}

void noBTtext(char *line1, char* line2, char *line3)
{
  APP_LOG(0, "noBTtext %c %d\n", Param.Language, Param.Language);
  switch (Param.Language) {
    case 'C': noBTtextCat(line1, line2, line3); break;
    case 'S': noBTtextEsp(line1, line2, line3); break;
    case 'E': noBTtextEng(line1, line2, line3); break;
  }
}

static void prv_inbox_received_handler(DictionaryIterator *iter, void *context) {
  
  // Read color preferences

  Tuple *bg_color_t = dict_find(iter, MESSAGE_KEY_BackGroundColor);
  if(bg_color_t) {
      Param.BackGroundColor = GColorFromHEX(bg_color_t->value->int32);
      window_set_background_color(window, Param.BackGroundColor);
  }
    
  Tuple *fg_color_t = dict_find(iter, MESSAGE_KEY_TextColor);
  if(fg_color_t) {
      Param.TextColor = GColorFromHEX(fg_color_t->value->int32);
      text_layer_set_text_color(layer1, Param.TextColor );
      text_layer_set_text_color(layer2, Param.TextColor );
      text_layer_set_text_color(layer3, Param.TextColor );
      text_layer_set_text_color(layer4, Param.TextColor );
      text_layer_set_text_color(top_bt_layer, Param.TextColor );
      
  }

  Tuple *Language_t = dict_find(iter, MESSAGE_KEY_Language);
  if(Language_t) {
      Param.Language = (char) Language_t->value->int32;
      APP_LOG(0, "prv_inbox_received_handler %c %d\n", Param.Language, Param.Language);
        
      struct tm *t;
      time_t temp;
      temp = time(NULL);
      t = localtime(&temp);
    
      //Manually call the tick handler when the window is loading
      date2text(t, line1, line2, line3, day, Param.ShowDate);
      layer_mark_dirty((Layer *)layer1 );
      layer_mark_dirty((Layer *)layer2 );
      layer_mark_dirty((Layer *)layer3 );
      layer_mark_dirty((Layer *)layer4 );
      }

  // Read boolean preferences
  Tuple *blueTooth_t = dict_find(iter, MESSAGE_KEY_BlueTooth);
  if(blueTooth_t) {
      Param.BlueTooth = blueTooth_t->value->int32 == 1;
  }

  Tuple *showDate_t = dict_find(iter, MESSAGE_KEY_ShowDate);
  if(showDate_t) {
      Param.ShowDate = showDate_t->value->int32 == 1;

      layer_set_hidden((Layer *)layer4, !Param.ShowDate);
  }
  
  persist_write_data(SETTINGS_KEY, &Param, sizeof(Param)); 

}

// Bluetooth handler. 
// It will also be called every minute, because some events get lost. 
// For this reason we will keep the status of the connection as a variable of the program.
void bt_handler(bool connected){
  
  // If no real changes, we can leave. No changes needed.
  if (connected == lastBTconnection) return;
  
  lastBTconnection = connected;
  if (connected){
     uint32_t const segments[] = { 200};
    VibePattern pat = {
      .durations = segments,
      .num_segments = ARRAY_LENGTH(segments),
    };
    if (Param.BlueTooth) {vibes_enqueue_custom_pattern(pat);};
    //layer_set_hidden((Layer *)bottom_bm_layer, false);
    layer_set_hidden ((Layer *) top_bt_layer, true);
  }
  else {
    uint32_t const segments[] = { 200, 100, 400, 100, 400, 100, 400, 100, 400};
    VibePattern pat = {
      .durations = segments,
      .num_segments = ARRAY_LENGTH(segments),
    };
    //layer_set_hidden((Layer *)bottom_bm_layer, true);
    layer_set_hidden ((Layer *) top_bt_layer, false);
    if (Param.BlueTooth) {
      no_bt_countdown = 10;
      window_set_background_color(window, GColorFolly);
      text_layer_set_text_color(layer1, GColorWhite);
      text_layer_set_text_color(layer2, GColorWhite);
      text_layer_set_text_color(layer3, GColorWhite);
      text_layer_set_text_color(layer4, GColorFolly);
      
      noBTtext(line1, line2, line3);
      
      vibes_enqueue_custom_pattern(pat);};
  }
}

// Clock handler
void tick_handler(struct tm *tick_time, TimeUnits units_changed){

  if (no_bt_countdown > 0) {
    no_bt_countdown --;
    if (no_bt_countdown == 0) {
      date2text(tick_time, line1, line2, line3, day, Param.ShowDate);
      window_set_background_color(window, Param.BackGroundColor);
      text_layer_set_text_color(layer1, Param.TextColor );
      text_layer_set_text_color(layer2, Param.TextColor );
      text_layer_set_text_color(layer3, Param.TextColor );
      text_layer_set_text_color(layer4, Param.TextColor );
      text_layer_set_text_color(top_bt_layer, Param.TextColor);
      text_layer_set_text(layer1, line1);
      text_layer_set_text(layer2, line2);
      text_layer_set_text(layer3, line3);
      text_layer_set_text(layer4, day);
    }
    return;
  } 
  // In the last second of the minute, we need to move old text out
  if(tick_time->tm_sec  == 59)
  {
    // The last layer is always moving out
    GRect start = b_layer3;
    GRect finish = GRect(b_layer3.origin.x+180, b_layer3.origin.y, b_layer3.size.h, b_layer3.size.w);
    animate_layer((Layer *)(layer3), &start, &finish, 300, 500);
    
    start = b_layer2;
    finish = GRect(b_layer2.origin.x+180, b_layer2.origin.y, b_layer2.size.h, b_layer2.size.w);
    animate_layer((Layer *)(layer2), &start, &finish, 300, 500);
  
    start = b_layer1;
    finish = GRect(b_layer1.origin.x+180, b_layer1.origin.y, b_layer1.size.h, b_layer1.size.w);;
    animate_layer((Layer *)(layer1), &start, &finish, 300, 500);
     
  }
  
  // In the start of the minute, the new text has to be set and annimated in
  // Change the TextLayer text to show the new time!
  if (tick_time->tm_sec  == 00) {
    // Check again the BT connection (some evnts get lost)
    bt_handler( bluetooth_connection_service_peek ());

    // Update the strings
    date2text(tick_time, line1, line2, line3, day, Param.ShowDate);
    text_layer_set_text_alignment(layer1, RandomPlacement());
    text_layer_set_text_alignment(layer2, RandomPlacement());
    text_layer_set_text_alignment(layer3, RandomPlacement());
    text_layer_set_text_alignment(layer4, RandomPlacement());

    text_layer_set_text(layer1, line1);
    text_layer_set_text(layer2, line2);
    text_layer_set_text(layer3, line3);
    text_layer_set_text(layer4, day);
  
    GRect start = GRect(b_layer3.origin.x+180, b_layer3.origin.y, b_layer3.size.h, b_layer3.size.w);
    GRect finish = b_layer3;
    animate_layer((Layer *)(layer3), &start, &finish, 300, 500);
    
    start = GRect(b_layer2.origin.x+180, b_layer2.origin.y, b_layer2.size.h, b_layer2.size.w);
    finish = b_layer2;
    animate_layer((Layer *)(layer2), &start, &finish, 300, 500);
    
    start = GRect(b_layer1.origin.x+180, b_layer1.origin.y, b_layer1.size.h, b_layer1.size.w);
    finish = b_layer1;
    animate_layer((Layer *)(layer1), &start, &finish, 300, 500);
  }
}

void window_load(Window *window){
  
    int  sizex, sizey, screen_h;
  
    b_screen = layer_get_bounds(window_get_root_layer(window)); 
  
    sizex=b_screen.size.h;
    sizey=b_screen.size.w;
  
    screen_h = sizey/5;


    net_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NET);

    //bottom_bm_layer = bitmap_layer_create(GRect((sizex-20)/2, 0, 20, 20));
    //bitmap_layer_set_bitmap(bottom_bm_layer, net_bitmap);
    //bitmap_layer_set_background_color(bottom_bm_layer, GColorRed);
 
    top_bt_layer = text_layer_create(GRect((sizex-30)/2, 0, 30, 30));
    text_layer_set_background_color(top_bt_layer, GColorClear);
    text_layer_set_text_color(top_bt_layer, Param.TextColor);
    text_layer_set_text_alignment(top_bt_layer, GTextAlignmentCenter);
    text_layer_set_font(top_bt_layer, fonts_load_custom_font  (resource_get_handle (RESOURCE_ID_FONT_TW_15)));   
    layer_add_child(window_get_root_layer(window), (Layer*) top_bt_layer);

    // Set the initial state of the bluetooth
    // An insert the layer of the net icon
    
    //layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bottom_bm_layer));
  
    bt_handler( bluetooth_connection_service_peek ());

  
    // Create the layers for the text
    b_layer1= GRect(screen_h/2,0.75*screen_h, sizey-screen_h, screen_h);
    layer1 = text_layer_create(b_layer1);
    text_layer_set_background_color(layer1, GColorClear);
    text_layer_set_text_color(layer1, Param.TextColor);
    text_layer_set_text_alignment(layer1, RandomPlacement());
    text_layer_set_font(layer1, fonts_load_custom_font  (resource_get_handle (RESOURCE_ID_FONT_TW_27)));   
    layer_add_child(window_get_root_layer(window), (Layer*) layer1);
    
    b_layer2 = GRect(screen_h/5,1.75*screen_h, sizey-screen_h*2/5, screen_h);
    layer2 = text_layer_create(b_layer2);
    text_layer_set_background_color(layer2, GColorClear);
    text_layer_set_text_color(layer2, Param.TextColor);
    text_layer_set_text_alignment(layer2, RandomPlacement());
    text_layer_set_font(layer2, fonts_load_custom_font (resource_get_handle (RESOURCE_ID_FONT_TW_27)));
    layer_add_child(window_get_root_layer(window), (Layer*) layer2);
    
    b_layer3 = GRect(screen_h/2,2.75*screen_h, sizey-screen_h, screen_h);
    layer3 = text_layer_create(b_layer3);
    text_layer_set_background_color(layer3, GColorClear);
    text_layer_set_text_color(layer3, Param.TextColor);
    text_layer_set_text_alignment(layer3, RandomPlacement());
    text_layer_set_font(layer3, fonts_load_custom_font (resource_get_handle (RESOURCE_ID_FONT_TW_27)));
    layer_add_child(window_get_root_layer(window), (Layer*) layer3);
     
    b_layer4 = GRect(screen_h,4*screen_h, sizey-2*screen_h, screen_h);
    layer4 = text_layer_create(b_layer4);
    text_layer_set_background_color(layer4, GColorClear);
    text_layer_set_text_color(layer4, Param.TextColor);
    text_layer_set_text_alignment(layer3, RandomPlacement());
    text_layer_set_font(layer4, fonts_load_custom_font (resource_get_handle (RESOURCE_ID_FONT_TW_19)));
    layer_add_child(window_get_root_layer(window), (Layer*) layer4);
  
    //Get a time structure so that the face doesn't start blank
    struct tm *t;
    time_t temp;
    temp = time(NULL);
    t = localtime(&temp);
    
    
    //Manually call the tick handler when the window is loading
    date2text(t, line1, line2, line3, day, Param.ShowDate);
    text_layer_set_text(layer1, line1);
    text_layer_set_text(layer2, line2);
    text_layer_set_text(layer3, line3);
    text_layer_set_text(layer4, day);
    text_layer_set_text(top_bt_layer, "bt?");
}

void window_unload(Window *window)
{
    text_layer_destroy(layer1);
    text_layer_destroy(layer2);
    text_layer_destroy(layer3);
    text_layer_destroy(layer4);
    text_layer_destroy(top_bt_layer);

    // bitmap_layer_destroy(bottom_bm_layer);
}

static void init(void) {
  //Initialize the app elements here! 
  // Open AppMessage connection
  
  Param.TextColor = GColorBlack;
  Param.BackGroundColor = GColorWhite;
  Param.Language = 'C'; // Catalan
  Param.BlueTooth = true;
  Param.ShowDate = true;
  
  persist_read_data(SETTINGS_KEY, &Param, sizeof(Param)); 


  app_message_register_inbox_received(prv_inbox_received_handler);
  app_message_open(128, 128);
  
  window = window_create();
    window_set_background_color(window, Param.BackGroundColor);
    window_set_window_handlers(window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
//      .appear = ???
//      .disappear = ???

    });
    window_stack_push(window, true);
    tick_timer_service_subscribe(SECOND_UNIT, (TickHandler) tick_handler);
    bluetooth_connection_service_subscribe((BluetoothConnectionHandler) bt_handler);
  
}

static void deinit(void) {
    //De-initialize elements here to save memory!
    tick_timer_service_unsubscribe();
    bluetooth_connection_service_unsubscribe();
    window_destroy(window);
}

int main(void) {

    init();
    app_event_loop();
    deinit();
}
