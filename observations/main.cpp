/* standard stuff
 as of 30 jul 2021
written to count up observations and sort by satellite number
Mike fixed this version
 */

#include <stdio.h>
#include <ctype.h>  // page 1062 in book
#include <string.h> // strtok, strcpy stuff not even used yet
#include <stdlib.h> // atoi, atof not used yet
#include <math.h>  // math functions
#include <wordexp.h>

#include <fstream>  // moving towards better C++ file handling
// does NOT like fstream.h!!

#define SATELLITE_LENGTH 30  // length of each line of satellite report

using namespace std;

FILE* fileOpen(const char* filename, const char* openmode)
{
    wordexp_t expandedName;
    FILE* fileHandle; // output points to file to write calculate results to
    wordexp(filename, &expandedName, 0);
    fileHandle = fopen(expandedName.we_wordv[0], openmode);
    wordfree(&expandedName);
    return fileHandle;
}  // this apparently lets ~/ work

class Observation  // this is what is in each observation line
{
public:
    // three fields: satellite number, telescope, # obs
    char line[SATELLITE_LENGTH];  // this is an observation line
    char satnumber[9];
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
    Observation(char *ob_line)  // fill in observation structure - event is one observation
    {
        strncpy(line, ob_line, sizeof(line));
        //strncpy(satnumber, line, sizeof(satnumber));
       
       // scan observation line
        sscanf(line, "%s %s %d", &satnumber, &telescope, &number_observations);
     
    }  // end Observation definition
    
   void print(FILE* spOutputObs)  // print to output file for parameters
    { //if no file given prints to stdout (i.e. terminal)
        fprintf(spOutputObs, "Satno %s\n", satnumber);
        fprintf(spOutputObs, "Observations: %d\n", number_observations );
      
        //        fprintf(stdout, "", );
    }  // end of print function - need this later?
    
    
}; // odd to see } then ; end of Tle thing
 
int compareObservationsSatelliteNumber(const void * a, const void * b) // sort satellite number
{
//    if (((Observation*)a)->satnumber  < ((Observation*)b)->satnumber) return -1;
//    if (((Observation*)a)->satnumber == ((Observation*)b)->satnumber) return  0;
//    if (((Observation*)a)->satnumber  > ((Observation*)b)->satnumber) return  1;
/** MSM - satnumber is an array of char's  NOT a number so < and > aren't really valid.  need to use strcmp instead **/
    return strcmp((const char*)(((Observation*)a)->satnumber), (const char*)(((Observation*)b)->satnumber));
}

int main()
{
    FILE* spInputObs;  // a file of all the observations
    FILE* spOutputObs; // output points to file to write calculate results to
 
    spInputObs = fileOpen("~/Dropbox/Projects/Charles/input_obs.txt", "r");
    spOutputObs = fileOpen("~/Dropbox/Projects/Charles/output_observations.txt", "w");
    
    char line[SATELLITE_LENGTH];
    
    Observation satellites[500];  // fill structure named satellites of 500 lines?
    
    int i = 0;
    while (feof(spInputObs) == 0) // read in all observations
    {
        fgets(line, sizeof(line), spInputObs);  // get first line of observations
        printf("the line: %s", line);  // debug
        
        satellites[i] = Observation(line); //
          //printf("satnumber %s\t", satellites[i].satnumber);

        i++;   // increment i
        
    }  // end of while loop, reads observations

    int numObs = i;
    qsort(&satellites[0], numObs, sizeof(Observation), compareObservationsSatelliteNumber);
    
    for(int i = 0; i < numObs; i++)
        fprintf(spOutputObs, "record %d\t satno %s\t telescope %s\t number observations %d\n", i, satellites[i].satnumber, satellites[i].telescope, satellites[i].number_observations);
//        fprintf(spOutputObs, "the line: %s\n", satellites[i].line);
    
    fclose(spInputObs);
    fclose(spOutputObs);
    // close all inputs and outputs, did not have that before

    }  // end of main
