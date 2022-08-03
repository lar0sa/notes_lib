// code for the "notesLib" pd library. 
// Encodes information created in Pd into a Lilypond score (lilypond.org)
// developed by Jaime Oliver La Rosa (la.rosa@nyu.edu)
// @ the NYU Waverly Labs in the Music Department - FAS. (nyu-waverlylabs.org)
// updated by Fede Camara Halac (fch226@nyu.edu)
// Released under the GNU General Public License. 

#include "notes_lib.h"

typedef struct notesLib
{
  t_object t_ob;
} t_notesLib;

t_class *notesLib_class;


static void *notesLib_new(void)
{
  t_notesLib *x = (t_notesLib *)pd_new(notesLib_class);
  
  return (x);
}

void notesLib_setup(void) 
{
	notesLib_class = class_new(gensym("notesLib"), notesLib_new, 0, sizeof(t_notesLib), CLASS_PD, 0);

	post("notes:\t Pd external object library for encoding music notation in lilypond syntax");
	post("notesLib version %s", NOTESLIBVERSION);
  post("notes:\t developed by Jaime Oliver La Rosa with contributions by Fede Cámara Halac");
  post("notes:\t at NYU Waverly Labs");
  class_sethelpsymbol(notesLib_class, gensym("notes"));
	mainscore_setup();
	line2score_setup();
  notes_setup();
	
}