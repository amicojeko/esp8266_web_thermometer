/*
* MIT License
* 
* Copyright (c) 2017 Stefano Guglielmetti
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

void sendToLCD(int v, int d) {  
    int ones;  
    int tens;  
    int hundreds; 
    // d = 0: right display (last 4 digits from the left)
    // d = 1: left display (first 4 digits from the left)
    int shift = d * 4; 

    boolean negative=false;

    if(v < -999 || v > 999)  
        return;  
    if(v<0) {  
        negative=true; 
        v=v*-1;  
    }
    
    ones     = v%10;  
    v        = v/10;  
    tens     = v%10;  
    v        = v/10; 
    hundreds = v;  
    
    if(negative) {  
        //print character '-' in the leftmost column  
        lc.setChar(0,3 + shift,'-',false);  } 
    else {
        //print a blank in the sign column  
        lc.setChar(0,3 + shift,' ',false);  
    }  
    
    //Now print the number digit by digit 
    lc.setDigit(0,2 + shift,(byte)hundreds,false);
    lc.setDigit(0,1 + shift,(byte)tens,true); 
    lc.setDigit(0,0 + shift,(byte)ones,false); 
} 
