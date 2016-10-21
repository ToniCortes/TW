#include <pebble.h>
#include "date2textEsp.h"

char num[20];

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
    case 20: if (opcio == 1) strncpy(tmp_num, "veinte", 20); else strncpy(tmp_num, "veinti", 20); break;
    case 30: strncpy(tmp_num, "treinta", 20); break;
    case 40: strncpy(tmp_num, "cuarenta", 20); break;
    case 50: strncpy(tmp_num, "cincuenta", 20); break;


  }
  return (tmp_num);
}

void date2textEsp(struct tm *tick_time, char *line1, char* line2, char *line3, char *day, bool ShowDate){
 
  snprintf(line1, 20, " %s ", int2stringEsp(tick_time->tm_hour%12, num, 2));
  snprintf(line3, 20, " ");
  
  switch ((tick_time->tm_min)/10) {
    case 0: 
      switch ((tick_time->tm_min)%10) {
        case 0: snprintf(line2, 20, " en punto "); break;
        default: snprintf(line2, 20, " y %s ", int2stringEsp(tick_time->tm_min, num, 1)); break;
       }break;
    case 1: snprintf(line2, 20, " y %s ", int2stringEsp(tick_time->tm_min, num, 1)); 
            if (tick_time->tm_min>15) {
              snprintf(line2, 20, " dieci- ");
              snprintf(line3, 20, " y %s ", int2stringEsp(tick_time->tm_min, num, 1));
            }; break;
    
    case 2: if  (tick_time->tm_min == 20 ) snprintf(line2, 20, " %s ", int2stringEsp(20, num, 1)); 
            else snprintf(line2, 20, " %s ", int2stringEsp(20, num, 2));break;
    case 3: snprintf(line2, 20, " %s ", int2stringEsp(30, num, 1)); break;
    case 4: snprintf(line2, 20, " %s ", int2stringEsp(40, num, 1)); break;
    case 5: snprintf(line2, 20, " %s ", int2stringEsp(50, num, 1)); break;
  }
    
  if (((tick_time->tm_min)/10)>1){
    switch ((tick_time->tm_min)%10) {
      case 0: snprintf(line3, 20, " " ); break; 
      default: snprintf(line3, 20, " %s ", int2stringEsp(tick_time->tm_min%10, num, 1)); break;
    }
  } 
      
  if (tick_time->tm_min == 15){
       snprintf(line1, 20, " %s ", int2stringEsp(tick_time->tm_hour%12, num, 2));
       snprintf(line2, 20, " y " );
       snprintf(line3, 20, " cuarto " );
  }
  
  if (tick_time->tm_min == 30){
       snprintf(line1, 20, " %s ", int2stringEsp(tick_time->tm_hour%12, num, 2));
       snprintf(line2, 20, " y " );
       snprintf(line3, 20, " media " );

  }
  if (tick_time->tm_min == 45){
       snprintf(line1, 20, " %s ", int2stringEsp((tick_time->tm_hour%12)+1, num, 2));
       snprintf(line2, 20, " menos " );
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

void OLDdate2textEsp(struct tm *tick_time, char *hour_text, char* minute_text_dec, char *minute_text_uni, char *day, bool ShowDate){
  
  
  strncpy(minute_text_uni, "", sizeof("")); 
  
  switch (tick_time->tm_hour) {
    case 0: strncpy(hour_text, " doce ", sizeof(" doce ")); break;
    case 1: strncpy(hour_text, " una ", sizeof(" una ")); break;
    case 2: strncpy(hour_text, " dos ", sizeof(" dos ")); break;
    case 3: strncpy(hour_text, " tres ", sizeof(" tres ")); break;
    case 4: strncpy(hour_text, " cuatro ", sizeof(" cuatro ")); break;
    case 5: strncpy(hour_text, " cinco ", sizeof(" cinco ")); break;
    case 6: strncpy(hour_text, " seis ", sizeof(" seis ")); break;
    case 7: strncpy(hour_text, " siete ", sizeof(" siete ")); break;
    case 8: strncpy(hour_text, " ocho ", sizeof(" ocho ")); break;
    case 9: strncpy(hour_text, " nueve ", sizeof(" nueve ")); break;
    case 10: strncpy(hour_text, " diez ", sizeof(" diez ")); break;
    case 11: strncpy(hour_text, " once ", sizeof(" once ")); break;
    case 12: strncpy(hour_text, " doce ", sizeof(" doce ")); break;
    case 13: strncpy(hour_text, " una ", sizeof(" una ")); break;
    case 14: strncpy(hour_text, " dos ", sizeof(" dos ")); break;
    case 15: strncpy(hour_text, " tres ", sizeof(" tres ")); break;
    case 16: strncpy(hour_text, " cuatro ", sizeof(" cuatro ")); break;
    case 17: strncpy(hour_text, " cinco ", sizeof(" cinco ")); break;
    case 18: strncpy(hour_text, " seis ", sizeof(" seis ")); break;
    case 19: strncpy(hour_text, " siete ", sizeof(" siete ")); break;
    case 20: strncpy(hour_text, " ocho ", sizeof(" ocho ")); break;
    case 21: strncpy(hour_text, " nueve ", sizeof(" nueve ")); break;
    case 22: strncpy(hour_text, " diez ", sizeof(" diez ")); break;
    case 23: strncpy(hour_text, " once ", sizeof(" once ")); break;

  }
  
   switch ((tick_time->tm_min)/10) {
     case 0: switch ((tick_time->tm_min)%10) {
       case 0: strncpy(minute_text_dec, " en punto ", sizeof(" en punto ")); break;
       case 1: strncpy(minute_text_dec, " y un ", sizeof(" y un ")); break;
       case 2: strncpy(minute_text_dec, " y dos ", sizeof(" y dos ")); break;
       case 3: strncpy(minute_text_dec, " y tres ", sizeof(" y tres ")); break;
       case 4: strncpy(minute_text_dec, " y cuatro ", sizeof(" y cuatro ")); break;
       case 5: strncpy(minute_text_dec, " y cinco ", sizeof(" y cinco ")); break;
       case 6: strncpy(minute_text_dec, " y seis ", sizeof(" y seis ")); break;
       case 7: strncpy(minute_text_dec, " y siete ", sizeof(" y siete ")); break;
       case 8: strncpy(minute_text_dec, " y ocho ", sizeof(" y ocho ")); break;
       case 9: strncpy(minute_text_dec, " y nueve ", sizeof(" y nueve ")); break;    
     }break;
     case 1: switch ((tick_time->tm_min)%10) {
       case 0: strncpy(minute_text_dec, " y diez ", sizeof(" y diez ")); break;
       case 1: strncpy(minute_text_dec, " y once ", sizeof(" y once ")); break;
       case 2: strncpy(minute_text_dec, " y doce ", sizeof(" y doce ")); break;
       case 3: strncpy(minute_text_dec, " y trece ", sizeof(" y trece ")); break;
       case 4: strncpy(minute_text_dec, " y catorce ", sizeof(" y catorce ")); break;
       case 5: strncpy(minute_text_dec, " y quince ", sizeof(" y quince ")); break;
       case 6: strncpy(minute_text_dec, " y dieci- ", sizeof( " y dieci- ")); 
               strncpy(minute_text_uni, " seis ", sizeof(" seis "));break;
       case 7: strncpy(minute_text_dec, " y dieci- ", sizeof( " y dieci- "));  
               strncpy(minute_text_uni, " siete ", sizeof(" siete "));break;
       case 8: strncpy(minute_text_dec, " y dieci- ", sizeof( " y dieci- "));  
               strncpy(minute_text_uni, " ocho ", sizeof(" ocho "));break;
       case 9: strncpy(minute_text_dec, " y dieci- ", sizeof(" y dieci- "));  
               strncpy(minute_text_uni, " nueve ", sizeof(" nueve "));break;
     } break;
     case 2:strncpy(minute_text_dec, " venti ", sizeof(" venti "));
            if (tick_time->tm_min == 20) strncpy(minute_text_dec, " i vint ", sizeof(" i vint ")); break;
    case 3: strncpy(minute_text_dec, " treinta ", sizeof(" treinta ")); break;
    case 4: strncpy(minute_text_dec, " cuarenta ", sizeof(" cuarenta ")); break;
    case 5: strncpy(minute_text_dec, " cincuenta ", sizeof(" cincuenta ")); break;    
  }
    
  if (((tick_time->tm_min)/10)==2){
    switch ((tick_time->tm_min)%10) {
      case 0: strncpy(minute_text_uni, "", sizeof("")); break;
      case 1: strncpy(minute_text_uni, " un ", sizeof(" y un ")); break;
      case 2: strncpy(minute_text_uni, " dos ", sizeof(" y dos ")); break;
      case 3: strncpy(minute_text_uni, " tres ", sizeof(" y tres ")); break;
      case 4: strncpy(minute_text_uni, " cuatro ", sizeof(" y cuatro ")); break;
      case 5: strncpy(minute_text_uni, " cinco ", sizeof(" y cinco ")); break;
      case 6: strncpy(minute_text_uni, " seis ", sizeof(" y seis ")); break;
      case 7: strncpy(minute_text_uni, " siete ", sizeof(" y siete ")); break;
      case 8: strncpy(minute_text_uni, " ocho ", sizeof(" y ocho ")); break;
      case 9: strncpy(minute_text_uni, " nueve ", sizeof(" y nueve ")); break;
    }
  } 
   if (((tick_time->tm_min)/10)>2){
    switch ((tick_time->tm_min)%10) {
      case 0: strncpy(minute_text_uni, "", sizeof("")); break;
      case 1: strncpy(minute_text_uni, " y uno ", sizeof(" y uno ")); break;
      case 2: strncpy(minute_text_uni, " y dos ", sizeof(" y dos ")); break;
      case 3: strncpy(minute_text_uni, " y tres ", sizeof(" y tres ")); break;
      case 4: strncpy(minute_text_uni, " y cuatro ", sizeof(" y cuatro ")); break;
      case 5: strncpy(minute_text_uni, " y cinco ", sizeof(" y cinco ")); break;
      case 6: strncpy(minute_text_uni, " y seis ", sizeof(" y seis ")); break;
      case 7: strncpy(minute_text_uni, " y siete ", sizeof(" y siete ")); break;
      case 8: strncpy(minute_text_uni, " y ocho ", sizeof(" y ocho ")); break;
      case 9: strncpy(minute_text_uni, " y nueve ", sizeof(" y nueve ")); break;
    }
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

      
  if (tick_time->tm_min == 15){
       strncpy(minute_text_dec, " y cuarto ", sizeof(" y cuarto "));
       strncpy(minute_text_uni, "  ", sizeof("  ")); 
  }
  if (tick_time->tm_min == 30){
       strncpy(minute_text_dec, " y media ", sizeof(" y media "));
       strncpy(minute_text_uni, "  ", sizeof("  ")); 
  }
}

void noBTtextEsp(char *line1, char* line2, char *line3){
  strncpy(line1, "Aiiix,  ", sizeof(" Aiiix, "));
  strncpy(line2, " y tu ", sizeof(" y tu "));
  strncpy(line3, " iPhone? ", sizeof(" iPhone? "));
}

