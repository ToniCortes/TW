#include <pebble.h>
#include "date2textEsp.h"

char *int2stringEsp(int h, char* tmp_num, int opcio){
  switch (h) {
    case 0: strncpy(tmp_num, "doce", 20); break;
    case 1: if (opcio == 1) strncpy(tmp_num, "un", 20); else strncpy(tmp_num, "una", 20); break;
    case 2: strncpy(tmp_num, "dos", 20); break;
    case 3: strncpy(tmp_num, "tres", 20); break;
    case 4: strncpy(tmp_num, "cuatro", 20); break;
    case 5: strncpy(tmp_num, "cinco", 20); break;
    case 6: strncpy(tmp_num, "seis", 20); break;
    case 7: strncpy(tmp_num, "siete", 20); break;
    case 8: strncpy(tmp_num, "ocho", 20); break;
    case 9: strncpy(tmp_num, "nueve", 20); break;
    case 10: strncpy(tmp_num, "diez", 20); break;
    case 11: strncpy(tmp_num, "once", 20); break;
    case 12: strncpy(tmp_num, "doce", 20); break;
    case 13: strncpy(tmp_num, "trece", 20); break;
    case 14: strncpy(tmp_num, "catorce", 20); break;
    case 15: strncpy(tmp_num, "quince", 20); break;
    case 16: strncpy(tmp_num, "seis", 20); break;
    case 17: strncpy(tmp_num, "siete", 20); break;
    case 18: strncpy(tmp_num, "ocho", 20); break;
    case 19: strncpy(tmp_num, "nueve", 20); break;
    case 20: if (opcio == 1) strncpy(tmp_num, "veinte", 20); else strncpy(tmp_num, "veinti-", 20); break;
    case 30: strncpy(tmp_num, "treinta", 20); break;
    case 40: strncpy(tmp_num, "cuarenta", 20); break;
    case 50: strncpy(tmp_num, "cincuenta", 20); break;


  }
  return (tmp_num);
}

void date2textEsp(struct tm *tick_time, char *line1, char* line2, char *line3, char *line4, char *day, bool ShowDate){

  char num[20];

  snprintf(line1, 20, " %s ", int2stringEsp(tick_time->tm_hour%12, num, 2));
  if (tick_time->tm_min == 0) snprintf(line2, 20, " "); else snprintf(line2, 20, " y ");
  if (tick_time->tm_min > 30){
    snprintf(line1, 20, " %s ", int2stringEsp((tick_time->tm_hour%12)+1, num, 2));
    snprintf(line2, 20, " menos ");
    tick_time->tm_min = 60 - tick_time->tm_min;
  }
  snprintf(line4, 20, " ");

  switch ((tick_time->tm_min)/10) {
    case 0: 
      switch ((tick_time->tm_min)%10) {
        case 0: snprintf(line2, 20, " en "); 
                snprintf(line3, 20, " punto "); 
                break;
        default: snprintf(line3, 20, " %s ", int2stringEsp(tick_time->tm_min, num, 1)); break;
       }break;
    case 1: if (tick_time->tm_min>15) {
              snprintf(line3, 20, " dieci- ");
              snprintf(line4, 20, " %s ", int2stringEsp(tick_time->tm_min, num, 1));
            } 
            else snprintf(line3, 20, " %s ", int2stringEsp(tick_time->tm_min, num, 1));
            break; 
    case 2: if  (tick_time->tm_min == 20 ) snprintf(line3, 20, " %s ", int2stringEsp(20, num, 1)); 
            else snprintf(line3, 20, " %s ", int2stringEsp(20, num, 2));break;
    case 3: snprintf(line3, 20, " %s ", int2stringEsp(30, num, 1)); break;
    case 4: snprintf(line3, 20, " %s ", int2stringEsp(40, num, 1)); break;
    case 5: snprintf(line3, 20, " %s ", int2stringEsp(50, num, 1)); break;
  }
    
  if (((tick_time->tm_min)/10)>1){
    switch ((tick_time->tm_min)%10) {
      case 0: snprintf(line4, 20, " " ); break; 
      default: if (tick_time->tm_min/10 == 2) snprintf(line4, 20, " %s ", int2stringEsp(tick_time->tm_min%10, num, 1));
              else snprintf(line4, 20, " y %s ", int2stringEsp(tick_time->tm_min%10, num, 1)); 
              break;
    }
  } 
      
  if (tick_time->tm_min == 15){
       snprintf(line3, 20, " cuarto " );
  }
  
  if (tick_time->tm_min == 30){
       snprintf(line3, 20, " media " );

  }
  if (tick_time->tm_min == 45){
       snprintf(line3, 20, " cuarto " );
 }
  
    
    switch (tick_time->tm_mon) {
    case 0:strftime(day, 12, " %e de ene ", tick_time); break;
    case 1:strftime(day, 12, " %e de feb ", tick_time); break;
    case 2:strftime(day, 12, " %e de mar ", tick_time); break;
    case 3:strftime(day, 12, " %e de abr ", tick_time); break;
    case 4:strftime(day, 12, " %e de may ", tick_time); break;
    case 5:strftime(day, 12, " %e de jun ", tick_time); break;
    case 6:strftime(day, 12, " %e de jul ", tick_time); break;
    case 7:strftime(day, 12, " %e de ago ", tick_time); break;
    case 8:strftime(day, 12, " %e de set ", tick_time); break;
    case 9:strftime(day, 12, " %e de oct ", tick_time); break;
    case 10:strftime(day, 12, " %e de nov ", tick_time); break;
    case 11:strftime(day, 12, " %e de dic ", tick_time); break;
  }
}

void noBTtextEsp(char *line1, char* line2, char *line3, char *line4){
  strncpy(line1, " Aiiix,  ", sizeof(" Aiiix, "));
  strncpy(line2, " y ", sizeof(" y "));
  strncpy(line3, " tu ", sizeof(" tu "));
  strncpy(line4, " iPhone? ", sizeof(" iPhone? "));
}

