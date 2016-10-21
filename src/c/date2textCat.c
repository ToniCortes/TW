#include <pebble.h>
#include "date2textCat.h"


char num[20];

char *int2stringCat(int h, char* tmp_num, int opcio){
  switch (h) {
    case 0: strncpy(tmp_num, "dotze", 20); break;
    case 1: if (opcio == 1) strncpy(tmp_num, "un", 20); else strncpy(tmp_num, "una", 20); break;
    case 2: if (opcio == 1) strncpy(tmp_num, "dos", 20);  else strncpy(tmp_num, "dues", 20); break;
    case 3: strncpy(tmp_num, "tres", 20); break;
    case 4: strncpy(tmp_num, "quatre", 20); break;
    case 5: strncpy(tmp_num, "cinc", 20); break;
    case 6: strncpy(tmp_num, "sis", 20); break;
    case 7: strncpy(tmp_num, "set", 20); break;
    case 8: strncpy(tmp_num, "vuit", 20); break;
    case 9: strncpy(tmp_num, "nou", 20); break;
    case 10: strncpy(tmp_num, "deu", 20); break;
    case 11: strncpy(tmp_num, "onze", 20); break;
    case 12: strncpy(tmp_num, "dotze", 20); break;
    case 13: strncpy(tmp_num, "tretze", 20); break;
    case 14: strncpy(tmp_num, "catorze", 20); break;
    case 15: strncpy(tmp_num, "quinze", 20); break;
    case 16: strncpy(tmp_num, "setze", 20); break;
    case 17: strncpy(tmp_num, "diset", 20); break;
    case 18: strncpy(tmp_num, "divut", 20); break;
    case 19: strncpy(tmp_num, "dinou", 20); break;
    case 20: if (opcio == 1) strncpy(tmp_num, "vint", 20); else strncpy(tmp_num, "vint-i-", 20); break;
    case 30: strncpy(tmp_num, "trenta", 20); break;
    case 40: strncpy(tmp_num, "quaranta", 20); break;
    case 50: strncpy(tmp_num, "cincuanta", 20); break;


  }
  return (tmp_num);
}

void date2textCat(struct tm *tick_time, char *line1, char* line2, char *line3, char *day, bool ShowDate){
 
  snprintf(line1, 20, " %s ", int2stringCat(tick_time->tm_hour%12, num, 2));
  snprintf(line3, 20, " ");
  
  switch ((tick_time->tm_min)/10) {
    case 0: 
      switch ((tick_time->tm_min)%10) {
        case 0: snprintf(line2, 20, " en punt "); break;
        default: snprintf(line2, 20, " i %s ", int2stringCat(tick_time->tm_min, num, 1)); break;
       }break;
    case 1: snprintf(line2, 20, " i %s ", int2stringCat(tick_time->tm_min, num, 1)); break;
    
    case 2: if  (tick_time->tm_min == 20 ) snprintf(line2, 20, " %s ", int2stringCat(20, num, 1)); 
            else snprintf(line2, 20, " %s ", int2stringCat(20, num, 2));break;
    case 3: snprintf(line2, 20, " %s ", int2stringCat(30, num, 1)); break;
    case 4: snprintf(line2, 20, " %s ", int2stringCat(40, num, 1)); break;
    case 5: snprintf(line2, 20, " %s ", int2stringCat(50, num, 1)); break;
  }
    
  if (((tick_time->tm_min)/10)>1){
    switch ((tick_time->tm_min)%10) {
      case 0: snprintf(line3, 20, " " ); break; 
      default: snprintf(line3, 20, " %s ", int2stringCat(tick_time->tm_min%10, num, 1)); break;
    }
  } 
      
  if (tick_time->tm_min == 15){
       snprintf(line1, 20, " %s ", int2stringCat(tick_time->tm_hour%12, num, 2));
       snprintf(line2, 20, " i " );
       snprintf(line3, 20, " quart " );
  }
  
  if (tick_time->tm_min == 30){
       snprintf(line1, 20, " %s ", int2stringCat(tick_time->tm_hour%12, num, 2));
       snprintf(line2, 20, " i " );
       snprintf(line3, 20, " mitja " );

  }
  if (tick_time->tm_min == 45){
       snprintf(line1, 20, " %s ", int2stringCat((tick_time->tm_hour%12)+1, num, 2));
       snprintf(line2, 20, " menys " );
       snprintf(line3, 20, " quart " );
 }
  
    
  switch (tick_time->tm_mon) {
    case 0:strftime(day, 12, " %e de gen ", tick_time); break;
    case 1:strftime(day, 12, " %e de feb ", tick_time); break;
    case 2:strftime(day, 12, " %e de mar ", tick_time); break;
    case 3:strftime(day, 12, " %e d'abr ", tick_time); break;
    case 4:strftime(day, 12, " %e de mai ", tick_time); break;
    case 5:strftime(day, 12, " %e de jun ", tick_time); break;
    case 6:strftime(day, 12, " %e de jul ", tick_time); break;
    case 7:strftime(day, 12, " %e d'ago ", tick_time); break;
    case 8:strftime(day, 12, " %e de set ", tick_time); break;
    case 9:strftime(day, 12, " %e d'oct ", tick_time); break;
    case 10:strftime(day, 12, " %e de nov ", tick_time); break;
    case 11:strftime(day, 12, " %e de des ", tick_time); break;
  }
}

void noBTtextCat(char *line1, char* line2, char *line3){
  strncpy(line1, "Aiiix, i ", sizeof(" Aiiix, i "));
  strncpy(line2, " el teu ", sizeof(" el teu "));
  strncpy(line3, " iPhone? ", sizeof(" iPhone? "));
}


