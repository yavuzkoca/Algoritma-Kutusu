#include <windows.h>

#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880

int main() {
   
    Beep( a, 500); 
    Beep( a, 500);     
    Beep( a, 500); 
    Beep( f, 350); 
    Beep( cH, 150);
    
    Beep( a, 500);
    Beep( f, 350);
    Beep( cH, 150);
    Beep( a, 1000);
    
    
    Beep( eH, 500);
    Beep( eH, 500);
    Beep( eH, 500);    
    Beep( fH, 350); 
    Beep( cH, 150);
    
    Beep(gS, 500);
    Beep( f, 350);
    Beep( cH, 150);
    Beep( a, 1000);
    
    
    Beep( aH, 500);
    Beep( a, 350); 
    Beep( a, 150);
    Beep( aH, 500);
    Beep( gSH, 250); 
    Beep( gH, 250);
    
    Beep( fSH, 125);
    Beep( fH, 125);    
    Beep( fSH, 250);
    Beep(1,250);
    Beep( aS, 250);    
    Beep( dSH, 500);  
    Beep( dH, 250);  
    Beep( cSH, 250);  
    
    
    Beep(cH, 125);  
    Beep( b, 125);  
    Beep( cH, 250);      
    Beep(1,250);
    Beep( f, 125);  
    Beep( gS, 500);  
    Beep( f, 375);  
    Beep( a, 125); 
    
    Beep( cH, 500); 
    Beep( a, 375);  
    Beep( cH, 125); 
    Beep(eH, 1000); 
    
    Beep( aH, 500);
    Beep( a, 350); 
    Beep( a, 150);
    Beep( aH, 500);
    Beep( gSH, 250); 
    Beep(gH, 250);
    
    Beep(fSH, 125);
    Beep( fH, 125);    
    Beep( fSH, 250);
    Beep(1,250);
    Beep(aS, 250);    
    Beep( dSH, 500);  
    Beep( dH, 250);  
    Beep( cSH, 250);  
    
    
    Beep( cH, 125);  
    Beep( b, 125);  
    Beep( cH, 250);      
    Beep(1,250);
    Beep( f, 250);  
    Beep( gS, 500);  
    Beep( f, 375);  
    Beep( cH, 125); 
           
    Beep(a, 500);            
    Beep(f, 375);            
    Beep( c, 125);            
    Beep( a, 1000); 
}
