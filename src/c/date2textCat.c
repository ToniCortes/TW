#include <pebble.h>
#include "date2textCat.h"


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
    case 17: strncpy(tmp_num, "disset", 20); break;
    case 18: strncpy(tmp_num, "divuit", 20); break;
    case 19: strncpy(tmp_num, "dinou", 20); break;
    case 20: if (opcio == 1) strncpy(tmp_num, "vint", 20); else strncpy(tmp_num, "vint-i", 20); break;
    case 30: strncpy(tmp_num, "trenta", 20); break;
    case 40: strncpy(tmp_num, "quaranta", 20); break;
    case 50: strncpy(tmp_num, "cinquanta", 20); break;


  }
  return (tmp_num);
}

void date2textCat(struct tm *tick_time, char *line1, char* line2, char *line3, char *line4, char *day, bool ShowDate){
 
  char num[20];

  snprintf(line1, 20, " %s ", int2stringCat(tick_time->tm_hour%12, num, 2));
  if (tick_time->tm_min == 0) snprintf(line2, 20, " "); else snprintf(line2, 20, " i ");
  if (tick_time->tm_min > 30){
    snprintf(line1, 20, " %s ", int2stringCat((tick_time->tm_hour%12)+1, num, 2));
    snprintf(line2, 20, " menys ");
    tick_time->tm_min = 60 - tick_time->tm_min;
  }
  snprintf(line4, 20, " ");
  
  switch ((tick_time->tm_min)/10) {
    case 0: 
      switch ((tick_time->tm_min)%10) {
        case 0:snprintf(line2, 20, " en "); 
               snprintf(line3, 20, " punt "); 
               break;
        default: snprintf(line3, 20, " %s ", int2stringCat(tick_time->tm_min, num, 1)); break;
       }break;
    case 1: snprintf(line3, 20, " %s ", int2stringCat(tick_time->tm_min, num, 1)); break;
    
    case 2: if  (tick_time->tm_min == 20 ) snprintf(line3, 20, " %s ", int2stringCat(20, num, 1)); 
            else snprintf(line3, 20, " %s- ", int2stringCat(20, num, 2));break;
    case 3: if (tick_time->tm_min == 30) snprintf(line3, 20, " %s ", int2stringCat(30, num, 1)); 
            else snprintf(line3, 20, " %s- ", int2stringCat(30, num, 1));break;
    case 4: if (tick_time->tm_min == 40) snprintf(line3, 20, " %s ", int2stringCat(40, num, 1)); 
            else snprintf(line3, 20, " %s- ", int2stringCat(40, num, 1));break;
    case 5: if (tick_time->tm_min == 50) snprintf(line3, 20, " %s ", int2stringCat(50, num, 1)); 
            else snprintf(line3, 20, " %s- ", int2stringCat(50, num, 1));break;
  }
    
  if (((tick_time->tm_min)/10)>1){
    switch ((tick_time->tm_min)%10) {
      case 0: snprintf(line4, 20, " " ); break; 
      default: snprintf(line4, 20, " %s ", int2stringCat(tick_time->tm_min%10, num, 1)); break;
    }
  } 
      
  if (tick_time->tm_min == 15){
       snprintf(line3, 20, " quart " );
  }
  
  if (tick_time->tm_min == 30){
       snprintf(line3, 20, " mitja " );
  }
  if (tick_time->tm_min == 45){
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


void date2textTCat(struct tm *tick_time, char *line1, char* line2, char *line3, char *line4, char *day, bool ShowDate){

  char num[20];


  snprintf(line4, 20, " ");
  
  switch (tick_time->tm_min) {
    case 0: snprintf(line1, 20, " %s ", int2stringCat(tick_time->tm_hour%12, num, 2));
            snprintf(line2, 20, " en ");
            snprintf(line3, 20, " punt ");
            break;
    case 1:
    case 2: 
    case 3:
    case 4: 
    case 5:
    case 6:
    case 7: snprintf(line1, 20, " %s ", int2stringCat(tick_time->tm_hour%12, num, 2));
            snprintf(line2, 20, " tocades ");
            break; 
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:snprintf(line1, 20, " mig ");
            snprintf(line2, 20, " quart ");
            snprintf(line3, 20, " de ");
            snprintf(line4, 20, " %s ", int2stringCat((tick_time->tm_hour%12)+1, num, 2));
            break;
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:snprintf(line1, 20, " un ");
            snprintf(line2, 20, " quart ");
            snprintf(line3, 20, " de ");
            snprintf(line4, 20, " %s ", int2stringCat((tick_time->tm_hour%12)+1, num, 2));
            break;
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:snprintf(line1, 20, " un ");
            snprintf(line2, 20, " quart ");
            snprintf(line3, 20, " i mig de ");
            snprintf(line4, 20, " %s ", int2stringCat((tick_time->tm_hour%12)+1, num, 2));
            break;
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:snprintf(line1, 20, " dos ");
            snprintf(line2, 20, " quarts ");
            snprintf(line3, 20, " de ");
            snprintf(line4, 20, " %s ", int2stringCat((tick_time->tm_hour%12)+1, num, 2));
            break;
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:snprintf(line1, 20, " dos ");
            snprintf(line2, 20, " quarts ");
            snprintf(line3, 20, " i mig de ");
            snprintf(line4, 20, " %s ", int2stringCat((tick_time->tm_hour%12)+1, num, 2));
            break;
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
    case 50: 
    case 51:
    case 52:snprintf(line1, 20, " tres ");
            snprintf(line2, 20, " quarts ");
            snprintf(line3, 20, " de ");
            snprintf(line4, 20, " %s ", int2stringCat((tick_time->tm_hour%12)+1, num, 2));
            break;
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:snprintf(line1, 20, " tres ");
            snprintf(line2, 20, " quarts ");
            snprintf(line3, 20, " i mig de ");
            snprintf(line4, 20, " %s ", int2stringCat((tick_time->tm_hour%12)+1, num, 2));
            break;
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

void noBTtextCat(char *line1, char* line2, char *line3, char * line4){
  strncpy(line1, " Aiiix, on ", sizeof(" Aiiix, on "));
  strncpy(line2, " tens ", sizeof(" tens "));
  strncpy(line3, " el teu ", sizeof(" el teu "));
  strncpy(line4, " iPhone? ", sizeof(" iPhone? "));
}


