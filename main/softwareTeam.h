/*

This is the header file I need done from software I will try my best to layout what I want with functions 
Feel free to change params returns need to stay the same and if you add other functions just make them static 

*/


void airflowSetup(int valveNumber) {
    /* 

    Will setup all objects or however you want to do it
    This one will be a beefy one since you need to do all the low level init 
        https://www.pjrc.com/teensy/td_libs_OneWire.html < will be real helpful for setup 

    */

   // CODE HERE

}

float airflowTemp(int valveNumber) {
    /*
    
    returns the temp reading of the corresponding valve
    
    */

   // CODE HERE

}

bool airflowIsReady(int valveNumber) { // might not include still debating
    /*
    
    Want to know if we are getting any weird values before we assume correct (very high or low temps)
    
    */

   // CODE HERE

}