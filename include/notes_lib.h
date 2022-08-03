// header file for the "notes_lib" c file
// Encodes information created in Pd into a Lilypond score (lilypond.org)
// developed by Jaime Oliver La Rosa (la.rosa@nyu.edu)
// @ the NYU Waverly Labs in the Music Department - FAS. (nyu-waverlylabs.org)
// with contributions by Fede Camara Halac (fch226@nyu.edu)
// Released under the GNU General Public License.

#include "m_pd.h"
#include "g_canvas.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MXV 128 // Maximum number of voices (for mainscore)
#define MXS 4096 // Maximum size of arrays  ( or input messages or notes per score...)

#if  defined(__APPLE__) || defined(unix)
#define UNIX 1
#else
// We need this for getline() to work on windows. TODO: remove this dependency.
#include "getline.h"
#endif

// The following are the definitions for the Lilypond path in different platforms. Used in the compile() function in notes_lib.c
// The LYDIR path is the default value for lily_dir, settable from pd.
#ifdef __APPLE__
// assume the lilypond is in Applications...
#define LYDIR "/Applications/LilyPond.app"
#define LYBINDIR "/Contents/Resources/bin/"
//
// #elif defined _WIN32
// // assume lilypond is in Program Files (x86)...
// #define LYDIR "C:\Program Files (x86)\LilyPond"
// #define LYBINDIR "\\usr\\bin\\"

#else // Do not define LY paths for other platforms.
// assume the lilypond command exists in the Path
#define LYDIR ""
#define LYBINDIR ""
#endif

// these are defined in m_pd.h for file handling across platforms
#define fopen sys_fopen
#define fclose sys_fclose

#define NOTESLIBVERSION "0.2: 2022-08-02"

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
// score compiling and opening routines
int compile(char *buf, char *name, int debug, char *lily_dir);
void open_pdf(char *buf);
int compile_and_open(char *buf, char *name, int debug, int SLAVE, int render, int open, char *lily_dir);

// setup routines
void mainscore_setup();
void line2score_setup();
void notes_setup();
