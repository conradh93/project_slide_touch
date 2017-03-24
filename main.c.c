#include <stdio.h>

void stateMachine(int state, int timethreshold, int DruckAktion, int SlideAktion, int counter, int max_index1, int max_wert1, int max_index2, int max_wert2, int array[])
{
  switch(state)
  {                           
    
    // state 0 kein Signal 
    case 0:                             
      
      printf("state 0 kein Signal\n");
      
      DruckAktion = 0;                                  
      
      // Funktion, um Array mit 8 Taxel-Werten durchzugehen und Taxel mit maximalem Wert zu bestimmen
      max_index1 = 0;                                   
      max_wert1 = 0;                                    
      
      for (int i=0; i<8; i++)                     
      {
        if (array[i] > max_wert1)                  
        {
          max_index1 = i;                     
          max_wert1 = array[i];
          printf("max_index: %i\n", max_index1);
          printf("max_wert1: %i\n", max_wert1);
        }
      }
      // Funktion Ende
      
      // Wenn max_wert gleich null, dann ist kein Signal vorhanden --> state 0 kein Signal
      if (max_wert1 == 0)                        
      {
        state = 0;
        stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
      }
      // sonst ist ein Signal vorhanden --> state 1 Signal
      else                                       
      {
        state = 1;
        stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
      }
    
    // state 1 Signal
    case 1:
      
      printf("state 1 Signal\n");
      
      // Wenn Signal im Taxel mit maximalem Wert wahrgenommen wird, zaehle counter hoch und bleibe in state 1 --> state 1 Signal
      if (array[max_index1] != 0)                
      {
        counter++;
        
        // Wenn counter groesser timethreshold --> state 2 Druck 
        if (counter > timethreshold)
        {
          state = 2;
          stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
        }
        
        state = 1;
        stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
      }
      // Es wird kein Signal mehr im Taxel mit maximalem Wert wahrgenommen
      else                                        
      {
        // Funktion, um Array mit 8 Taxel-Werten durchzugehen und Taxel mit maximalem Wert zu bestimmen
        max_index2 = 0;
        max_wert2 = 0;
        
        for (int i=0; i<8; i++)                   
        {
          if (array[i] > max_wert2)               
          {
            max_index2 = i;                     
            max_wert2 = array[i];
          }
        }
        // Funktion Ende
        
        // Wenn max_wert gleich null, dann ist in keinem Taxel ein Signal vorhanden --> state 2 Druck
        if (max_wert2 == 0)                       
        {
          state = 2;
          stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
        }
        // In einem anderen Taxel ist ein Signal vorhanden --> Slide
        else                                      
        {
          // Wenn max_index2 größer max_index1 --> state 3 Slide nach unten um eins
          if (max_index2 > max_index1)           
          {
            state = 3;
            stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
          }
          // --> state 4 Slide nach oben um eins
          else                                
          {
            state = 4;
            stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
          }
        }
      }
    
    // state 2 Druck  
    case 2:
      
      printf("state 2 Druck\n");
      
      // Wenn Druck Funktion noch nicht ausgefuehrt wurde, dann fuehre sie aus
      if (DruckAktion == 0)                     
      {
        // Fuehre Druck Funktion aus, z.B. Auswahl
        printf("Druck Funktion\n");
        DruckAktion = 1;
      }
      
      // Funktion, um Array mit 8 Taxel-Werten durchzugehen und Taxel mit maximalem Wert zu bestimmen
      max_index1 = 0;
      max_wert1 = 0;
        
      for (int i=0; i<8; i++)                   
      {
        if (array[i] > max_wert1)        
        {
          max_index1 = i;                     
          max_wert1 = array[i];
        }
      }
      // Funktion Ende
      
      // Wenn max_wert gleich null, dann ist kein Signal vorhanden --> state 0 kein Signal
      if (max_wert1 == 0)                       
      {
        state = 0;
        stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
      }
      // sonst ist ein Signal vorhanden und der User drueckt noch immer --> state 1 Signal
      else                                      
      {
        state = 2;
        stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
      }
    
    // state 3 Slide nach unten um eins
    case 3:
        
      printf("state 3 Slide nach unten um eins\n");
      
      // Wenn Slide Funktion noch nicht ausgefuehrt wurde, dann fuehre sie aus
      if (SlideAktion == 0)                     
      {
        // Fuehre Slide Funktion aus, z.B. Slide nach unten im Menue
        printf("Slide Funktion\n");
        SlideAktion = 1;
      }
      
      // Wenn Signal im Taxel mit maximalem Wert wahrgenommen wird, bleibe in state 3 --> state 3 Slide nach unten um eins
      if (array[max_index2] != 0)               
      {
        state = 3;
        stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
      }
      // Es wird kein Signal im Taxel mit maximalem Wert wahrgenommen
      else                                      
      {
        // Funktion, um Array mit 8 Taxel-Werten durchzugehen und Taxel mit maximalem Wert zu bestimmen
        max_index1 = 0;
       max_wert1 = 0;
        
        for (int i=0; i<8; i++)                  
        {
          if (array[i] > max_wert1)               
          {
            max_index1 = i;                     
            max_wert1 = array[i];
          }
        }
        // Funktion Ende
        
        // Wenn max_wert gleich null, dann ist in keinem Taxel ein Signal vorhanden --> state 0 kein Signal
        if (max_wert1 == 0)                        
        {
          state = 0;
          stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
        }
        // In einem anderen Taxel ist ein Signal vorhanden --> Slide
        else                                      
        {
          // Wenn max_index1 größer max_index2 --> state 3 Slide nach unten um eins
          if (max_index1 > max_index2)          
          {
            SlideAktion = 0;
            state = 3;
            stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
          }
          // --> state 4 Slide nach oben um eins
          else                                  
          {
            SlideAktion = 0;
            state = 4;
            stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
          }
        }
      }  
        
    // state 4 Slide nach oben um eins
    case 4:
        
      printf("state 4 Slide nach oben um eins\n");
      
      // Wenn Slide Funktion noch nicht ausgefuehrt wurde, dann fuehre sie aus
      if (SlideAktion == 0)                     
      {
        // Fuehre Slide Funktion aus, z.B. Slide nach oben im Menue
        printf("Slide Funktion\n");
        SlideAktion = 1;
      }
      
      // Wenn Signal im Taxel mit maximalem Wert wahrgenommen wird, bleibe in state 4 --> state 4 Slide nach unten um eins
      if (array[max_index2] != 0)               
      {
        state = 4;
        stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
      }
      // Es wird kein Signal im Taxel mit maximalem Wert wahrgenommen
      else                                      
      {
        // Funktion, um Array mit 8 Taxel-Werten durchzugehen und Taxel mit maximalem Wert zu bestimmen
        max_index1 = 0;
        max_wert1 = 0;
        
        for (int i=0; i<8; i++)                  
        {
          if (array[i] > max_wert1)               
          {
            max_index1 = i;                     
            max_wert1 = array[i];
          }
        }
        // Funktion Ende
        
        // Wenn max_wert gleich null, dann ist in keinem Taxel ein Signal vorhanden --> state 0 kein Signal
        if (max_wert1 == 0)                        
        {
          state = 0;
          stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
        }
        // In einem anderen Taxel ist ein Signal vorhanden --> Slide
        else                                      
        {
          // Wenn max_index1 größer max_index2 --> state 3 Slide nach unten um eins
          if (max_index1 > max_index2)          
          {
            SlideAktion = 0;
            state = 3;
            stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
          }
          // --> state 4 Slide nach oben um eins
          else                                  
          {
            SlideAktion = 0;
            state = 4;
            stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array);
          }
        }
      }
  }
}

int main()
{
  int state = 0;

  // Wenn man eine bestimmte Zeit auf ein Taxel drueckt, wird das als Druck gezählt
  int timethreshold = 10;                

  // Nötig, um zu verhindern, dass Funktion bei Druck nur einmal ausgeführt wird, auch wenn Benutzer laenger drueckt
  int DruckAktion = 0;
  // Nötig, um zu verhindern, dass Funktion bei Slide nur einmal ausgeführt wird, auch wenn Benutzer langsam slidet
  int SlideAktion = 0;                    

  int counter = 0;

  // Variable um Index des Taxel mit maximalem Wert zu speichern
  int max_index1 = 0;
  // Variable um maximalen Wert der Taxel zu speichern
  int max_wert1 = 0;
  // Variable um Index des Taxel mit maximalem Wert zu speichern
  int max_index2 = 0;
  // Variable um Index des Taxel mit maximalem Wert zu speichern
  int max_wert2 = 0;                        

  
  int array[15][8]= 
  {{0,0,0,0,0,0,0,0},
   {0,5,2,1,0,0,0,0},
   {0,0,5,2,1,0,0,0},
   {0,0,0,5,2,1,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,5,2,1,0,0},
   {0,0,5,2,1,0,0,0},
   {0,5,2,1,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,5,2,1,0,0,0,0},
   {0,0,5,2,1,0,0,0},
   {0,0,0,5,2,1,0,0},
   {0,0,0,5,2,1,0,0},
   {0,0,5,2,1,0,0,0},
   {0,5,2,1,0,0,0,0}};

  int array2[] = {0,5,2,1,0,0,0,0};
  
  
  
  stateMachine(state, timethreshold, DruckAktion, SlideAktion, counter, max_index1, max_wert1, max_index2, max_wert2, array[4]);
  
  return 0;
}
