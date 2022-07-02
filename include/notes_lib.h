// header file for the "notes_lib" c file
// Encodes information created in Pd into a Lilypond score (lilypond.org)
// developed by Jaime Oliver La Rosa (la.rosa@nyu.edu)
// @ the NYU Waverly Labs in the Music Department - FAS. (nyu-waverlylabs.org)
// updated by Fede Camara Halac (fch226@nyu.edu)
// Released under the GNU General Public License. 

#include "m_pd.h"
#include "g_canvas.h" 
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MXV 128 // Maximum number of voices (for mainscore)
#define MXS 2048 // Maximum size of arrays  ( or input messages...)

#if  defined(__APPLE__) || defined(unix)
#define UNIX 1 
#endif

// these are defined in m_pd.h for file handling across platforms
#define fopen sys_fopen
#define fclose sys_fclose

#define NOTESLIBVERSION "Testing version: 2021-07-03"

// helper functions in notes_lib.c
float reduce_meter(int a);
int get_beatsize(int a, int b, int c);
int pow2test(int a);
int pow2dottest(int a);
int pow2ordot(int a);
void find_relative(int a, FILE *f);
void find_pitch(float a, int b, char g[]);
int  find_jump(int a, int b, int c, char g[]);
void find_clef(int a, FILE *f);
void find_articulation(int a, FILE *f);
void find_dynamics(int a, FILE *f);
void find_small_numbers(int a, FILE *f);
void find_span(int a, FILE *f);
void find_stafftext(int a, char g[]);
void find_grace(int a, FILE *f);
void find_arpeggio(int a, FILE *f);
void find_notehead(int a, FILE *f);
int readbarfile(int a[][8], FILE *f);
void copyfiles(FILE *f, FILE *g);

// setup routines
void mainscore_setup();
void line2score_setup();
void notes_setup();

