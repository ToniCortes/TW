#include <pebble.h>
#include "date2textEng.h"


char *int2stringEng(int h, char* tmp_num){
  switch (h) {
    case 0: strncpy(tmp_num, "twelve", 20); break;
    case 1: strncpy(tmp_num, "one", 20); break;
    case 2: strncpy(tmp_num, "two", 20); break;
    case 3: strncpy(tmp_num, "three", 20); break;
    case 4: strncpy(tmp_num, "four", 20); break;
    case 5: strncpy(tmp_num, "five", 20); break;
    case 6: strncpy(tmp_num, "six", 20); break;
    case 7: strncpy(tmp_num, "seven", 20); break;
    case 8: strncpy(tmp_num, "eight", 20); break;
    case 9: strncpy(tmp_num, "nine", 20); break;
    case 10: strncpy(tmp_num, "ten", 20); break;
    case 11: strncpy(tmp_num, "eleven", 20); break;
    case 12: strncpy(tmp_num, "twelve", 20); break;
    case 13: strncpy(tmp_num, "thirteen", 20); break;
    case 14: strncpy(tmp_num, "fourteen", 20); break;
    case 15: strncpy(tmp_num, "fifteen", 20); break;
    case 16: strncpy(tmp_num, "sixteen", 20); break;
    case 17: strncpy(tmp_num, "seventeen", 20); break;
    case 18: strncpy(tmp_num, "eighteen", 20); break;
    case 19: strncpy(tmp_num, "nineteen", 20); break;
    case 20: strncpy(tmp_num, "twenty", 20); break;
    case 30: strncpy(tmp_num, "thirty", 20); break;
    case 40: strncpy(tmp_num, "forty", 20); break;
    case 50: strncpy(tmp_num, "fifty", 20); break;


  }
  return (tmp_num);
}

void date2textEng(struct tm *tick_time, char *line1, char* line2, char *line3, char *line4, char *day, bool ShowDate){
 
  char num[20];

  snprintf(line1, 20, " %s ", int2stringEng(tick_time->tm_hour%12, num));
  snprintf(line3, 20, " ");
  
  switch ((tick_time->tm_min)/10) {
    case 0: 
      switch ((tick_time->tm_min)%10) {
        case 0: snprintf(line2, 20, " o'clock "); break;
        default: snprintf(line2, 20, " %s ", int2stringEng(tick_time->tm_min, num)); break;
       }break;
    case 1: snprintf(line2, 20, " %s ", int2stringEng(tick_time->tm_min, num)); break;
    
    case 2: snprintf(line2, 20, " %s ", int2stringEng(20, num)); break;
    case 3: snprintf(line2, 20, " %s ", int2stringEng(30, num)); break;
    case 4: snprintf(line2, 20, " %s ", int2stringEng(40, num)); break;
    case 5: snprintf(line2, 20, " %s ", int2stringEng(50, num)); break;
  }
    
  if (((tick_time->tm_min)/10)>1){
    switch ((tick_time->tm_min)%10) {
      case 0: snprintf(line3, 20, " " ); break; 
      default: snprintf(line3, 20, " %s ", int2stringEng(tick_time->tm_min%10, num)); break;
    }
  } 
      
  if (tick_time->tm_min == 15){
       snprintf(line3, 20, " %s ", int2stringEng(tick_time->tm_hour%12, num));
       snprintf(line2, 20, " past " );
       snprintf(line1, 20, " quarter " );
  }
  
  if (tick_time->tm_min == 30){
       snprintf(line3, 20, " %s ", int2stringEng(tick_time->tm_hour%12, num));
       snprintf(line2, 20, " past " );
       snprintf(line1, 20, " half " );

  }
  if (tick_time->tm_min == 45){
       snprintf(line3, 20, " %s ", int2stringEng((tick_time->tm_hour%12)+1, num));
       snprintf(line2, 20, " to " );
       snprintf(line1, 20, " quarter " );
 }
  
    
  switch (tick_time->tm_mon) {
    case 0:strftime(day, 12, " jan %e ", tick_time); break;
    case 1:strftime(day, 12, " feb %e ", tick_time); break;
    case 2:strftime(day, 12, " mar %e ", tick_time); break;
    case 3:strftime(day, 12, " apr %e ", tick_time); break;
    case 4:strftime(day, 12, " mai %e ", tick_time); break;
    case 5:strftime(day, 12, " jun %e ", tick_time); break;
    case 6:strftime(day, 12, " jul %e ", tick_time); break;
    case 7:strftime(day, 12, " agu %e ", tick_time); break;
    case 8:strftime(day, 12, " sep %e ", tick_time); break;
    case 9:strftime(day, 12, " oct %e ", tick_time); break;
    case 10:strftime(day, 12, " nov %e ", tick_time); break;
    case 11:strftime(day, 12, " dec %e ", tick_time); break;
  }
}

void noBTtextEng(char *line1, char* line2, char *line3, char *line4){
  strncpy(line1, "Uops,  ", sizeof(" Uops, "));
  strncpy(line2, " and ", sizeof(" and "));
  strncpy(line3, " your ", sizeof(" your "));
  strncpy(line4, " iPhone? ", sizeof(" iPhone? "));
}