/* standard stuff
 as of 24 jul 2021
written to count up observations and sort by satellite number
 now runs in Terminal and asks which parameter to sort by
 */

#include <stdio.h>
#include <ctype.h>  // page 1062 in book
#include <string.h> // strtok, strcpy stuff not even used yet
#include <stdlib.h> // atoi, atof not used yet
#include <math.h>  // math functions

#include <fstream>  // moving towards better C++ file handling
// does NOT like fstream.h!!

#define SATELLITE_LENGTH 30  // length of each line of satellite report

using namespace std;

class Observation  // this is what is in each observation line
{
public:
    // three fields: satellite number, telescope, # obs
    char line[SATELLITE_LENGTH];  // this is a observation line
    char satnumber ;
    char telescope[10];
    int number_observations ;
    
  /*  float tleStrToFloat(char * in)  // need this for anything? sense text in file?
    {
        char temp[10];
        if(in[0] == '-') temp[0] = '-';
        else temp[0] = ' ';
        int offset = 1;
        if(isdigit(in[0])) offset = 0;
        temp[1] = '.';
        for (int i = 0; i < 4; i++){
            temp[2+i] = in[offset+i];
        };
        temp[6] = 'e';
        temp[7] = in[offset+5];
        temp[8] = in[offset+6];
        temp[9] = '\0'; // null character
        float b = atof(temp);
        return(b);
    }
   */
    
    Observation(){}; // empty constructor
    Observation(char *event)  // fill in observation structure - event is one observation
    {
        strncpy(line, event, sizeof(line));
       
        int linenum;
       // scan observation line
        sscanf( line, "%d %s %s %4d",
               &linenum,
               &satnumber,
               &telescope, &number_observations);

        sscanf(line, "%s %s %d", &satnumber, &telescope, &number_observations);
        
    }  // end Observation definition
    
   void print(FILE* spOutput)  // print to output file for parameters
    { //if no file given prints to stdout (i.e. terminal)
        fprintf(spOutput, "Satno %c\n", satnumber);
        fprintf(spOutput, "Observations: %d\n", number_observations );
      
        //        fprintf(stdout, "", );
    }  // end of print function - need this later?
    
    
}; // odd to see } then ; end of Tle thing
 
int compareObservationsSatelliteNumber(const void * a, const void * b) // sort satellite number
{
    if (((Observation*)a)->satnumber  < ((Observation*)b)->satnumber) return -1;
    if (((Observation*)a)->satnumber == ((Observation*)b)->satnumber) return  0;
    if (((Observation*)a)->satnumber  > ((Observation*)b)->satnumber) return  1;
    return 0; //gets rid of compiler warning, should never get here
}

int main()
{
    
    FILE* spInputObs;  // a file of all the observations
    
    FILE* spOutput = nullptr; // output points to file to write calculate results to
    
   // spInputTLE = fopen(“~/Desktop/analyses/input_tle.txt", "r");
  //  spOutput = fopen(“~/Desktop/analyses/selected_satellite.txt", "w”);

    spInputObs = fopen("/Users/Charles/Desktop/analyses/input_obs.txt", "r");
   // each case has a unique spOutput
   
    char name_card[SATELLITE_LENGTH];
    
    Observation satellites[500];  // structure of 500 lines?
   // printf("sat number\n", &sattellites[0].satnumber); // can access fields?
    
  //  spInputTLE = fopen("tle_cards.txt", "r");  // read data from marston
  //  spOutput = fopen("tle_output.txt", "w");  // put satellite in marston
    
    int i = 0;
    while (feof(spInputObs) == 0) // read in all three cards
    {
        fgets(name_card, sizeof(name_card), spInputObs);  // get first line of TLE
        
        satellites[i] = Observation(name_card); //
        // printf("test", sattellites[0].satnumber);  // how to point at satnumber?
        // need to look for satnumber here and print to files
        i++;   // increment i
        
    }  // end of while loop, reads observations
    
    
    /*  original code
    for(int j = 0; j < numSats; j++) fprintf(spOutput, "record %d\t satno %d\t epochyr %d\t epochday %f\t inclin %f\t perigee: %f\t apogee: %f\n", j, sattellites[j].satnumber, sattellites[j].epoch_year, sattellites[j].epoch_day, sattellites[j].inclination, sattellites[j].perigee, sattellites[j].apogee);
    // prints record number (j), sat number, and inclination
  
     */
        
    fclose(spInputObs);
    fclose(spOutput);
    // close all inputs and outputs, did not have that before

    }  // end of main

