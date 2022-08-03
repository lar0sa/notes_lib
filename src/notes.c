// code for the "notes" pd class.
// Encodes information created in Pd into a Lilypond score (lilypond.org)
// developed by Jaime Oliver La Rosa (la.rosa@nyu.edu)
// @ the NYU Waverly Labs in the Music Department - FAS. (nyu-waverlylabs.org)
// updated by Fede Camara Halac (fch226@nyu.edu)
// Released under the GNU General Public License.

#include "notes_lib.h"

////	____________________________________________________ MAIN STRUCT
typedef struct notes 													{
  t_object x_ob;
  t_outlet *x_outlet0, *x_outlet1, *x_outlet2, *x_outlet3;
  t_canvas *x_canvas;
  FILE *fp1;

////////////////// ******* RAW INPUT DATA:
// pitch, duration, articulation, tie, dynamics, articulation, tempo, meter, text, harp-pedals
// add rehearsal marks, tremolo

  int ri_index;
  int ri_cho[MXS], ri_dur[MXS], ri_tie[MXS], ri_clu[MXS], ri_clef[MXS], ri_acc[MXS], ri_trm[MXS], ri_arp[MXS];
  int ri_dyn_n[MXS], ri_art_n[MXS], ri_smn_n[MXS], ri_spa_n[MXS], ri_txt_n[MXS], ri_txt_spn_n[MXS], ri_hrm_n[MXS], ri_nhs_n[MXS], ri_hpp_n[MXS];
  float ri_pit[MXS][128], ri_spa_p[MXS];
  int ri_mtr[MXS][2], ri_tmp[MXS][2], ri_grc[MXS][2], ri_tup[MXS][3], ri_dyn[MXS][16], ri_art[MXS][16], ri_smn[MXS][8], ri_spa[MXS][8], ri_hrm[MXS][8], ri_nhs[MXS][16], ri_txt_spn[MXS][6];
  char ri_txt[MXS][32][64];
  char ri_hpp[MXS][16];

  int ri_index_sort[MXS];

////////////////// ******* CLEAN INPUT DATA:
  int i_index, i_rii[MXS];
  int i_cho[MXS], i_dur[MXS], i_mtr[MXS][2], i_tup[MXS], i_tie[MXS];

////////////////// ******* TUPLET DATA:
  int tp_info[MXS][5], tp_n;
  int tp_index, tp_dur[MXS], tp_i[MXS], tp_ri[MXS], tp_tie[MXS], tp_num[MXS];
  int b_tp_index, b_tp_dur[MXS], b_tp_i[MXS], b_tp_ri[MXS], b_tp_tie[MXS], b_tp_num[MXS];
  int sb_tp_index, sb_tp_dur[MXS], sb_tp_i[MXS], sb_tp_ri[MXS], sb_tp_tie[MXS], sb_tp_num[MXS];
  int sb_tp_start[MXS], sb_tp_end[MXS];
////////////////// ******* GRACE DATA:
  int g_index, g_rii[MXS], g_dur[MXS];

////////////////// ******* BAR DATA:
  int b_index, bar_n[MXS], b_tie[MXS], b_dur[MXS], b_i[MXS], b_mtr[MXS][2], b_tmp[MXS][2], b_rii[MXS], b_tup[MXS];
  int bar_info[MXS][8]; // 0 = initial position, 1 = num, 2 = den
////////////////// ******* BEAT DATA:
  int be_index, be_bar_n[MXS], be_beat_n[MXS], be_tie[MXS], be_dur[MXS], be_i[MXS], be_rii[MXS], be_tup[MXS];
////////////////// ******* SUB-BEAT DATA:
  int sb_index, sb_bar_n[MXS], sb_beat_n[MXS], sb_tie[MXS], sb_dur[MXS], sb_i[MXS], sb_rii[MXS], sb_tup[MXS];

  char title[64][130], sub_title[64][130], author[64][130], osname[130], lily_dir[MAXPDSTRING], barfile[MAXPDSTRING], inst[150];
  const char *dummysym; // const to remove warning
  int ii, refdur, debug, auth_n, titl_n, sub_title_n, tempo, OS, lastpit_ch, lastpit;
  int FOLLOW, inst_n, papersize, paperorientation, render, open;
}
t_notes;

////	____________________________________________________ INPUT
void notes_input(t_notes *x, t_symbol *s, int argcount, t_atom *argvec) {
	int a, i, j, input_check[21];
	float temp_f, temp_f_array[128];
	x->dummysym = s->s_name;

	t_symbol *nt_pitch 			= gensym("-pit"); // float = single note & list = chord
	t_symbol *nt_rhythm 		= gensym("-dur"); // float = duration
	t_symbol *nt_dynamics 		= gensym("-dyn"); // float = dynamics list (0 = nothing, 1 = pppp, etc..)
	t_symbol *nt_tuplet 		= gensym("-tup"); // 1 3 4 (3 1's in the place of 4)?
	t_symbol *nt_meter	 		= gensym("-mtr"); // meter num, denom
	t_symbol *nt_articulation	= gensym("-art"); // articulation, n
	t_symbol *nt_tempo			= gensym("-tmp"); // tempo 32 = msec
	t_symbol *nt_small_numbers	= gensym("-smn"); // small numbers, mostly for fingering.
	t_symbol *nt_clef			= gensym("-clf"); // Clef changes.
	t_symbol *nt_accidentals	= gensym("-acc"); // accidentals.
	t_symbol *nt_tremolo		= gensym("-trm"); // tremolo.
	t_symbol *nt_span			= gensym("-spa"); // tremolo.
	t_symbol *nt_grace			= gensym("-grc"); // grace notes
	t_symbol *nt_harmonic		= gensym("-hrm"); // stopped harmonics
	t_symbol *nt_noteheads		= gensym("-nhs"); // noteheads
	t_symbol *nt_tie			= gensym("-tie"); // tie
	t_symbol *nt_cluster		= gensym("-clu"); // clusters
	t_symbol *nt_arpeggio		= gensym("-arp"); // arpeggio
	t_symbol *nt_text			= gensym("-txt"); // text
    t_symbol *nt_harppedal 		= gensym("-hpp"); // harp_pedal

	if (x->debug >= 1) post("INDEX ========= %d", x->ri_index);
	for (a = 0; a < 21; a++) { input_check[a] = 0;	};
    for (a = 0; a < argcount; a++) {
    	if (x->debug >= 1) post("notes: Input index %d received", x->ri_index);
    	if (argvec[a].a_type == A_SYMBOL) {
    		x->ri_spa_p[x->ri_index] = 0;
//_____________________________________________________________________________
	    	if 		( argvec[a].a_w.w_symbol == nt_pitch)			{
	    		i = 0;
	    		while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_pit[x->ri_index][i] 		= argvec[a].a_w.w_float;
	    		//	post("pitch =\t%f", x->ri_pit[x->ri_index][i]);
	    			i++;
	    		}
	    		x->ri_cho[x->ri_index] = i;
	    		if (x->debug >= 1) post("chord size = %d", x->ri_cho[x->ri_index]);
	    		input_check[0] = 1;
	    		for (j=0; j<x->ri_cho[x->ri_index]; j++) {
	    			temp_f = 1000;
					for (i=0; i<x->ri_cho[x->ri_index]; i++) {
						if (j==0) {
							if (x->ri_pit[x->ri_index][i] <= temp_f) {
								temp_f = x->ri_pit[x->ri_index][i];
							}
						}
						else {
							if (x->ri_pit[x->ri_index][i] < temp_f &&
								x->ri_pit[x->ri_index][i] > temp_f_array[j-1]) {
								temp_f = x->ri_pit[x->ri_index][i];
							}
						}
					}
					temp_f_array[j] = temp_f;
					if (x->debug >= 1) post("o.pitch =\t%f", temp_f_array[j]);
				}
				for (j=0; j<x->ri_cho[x->ri_index]; j++) {
					x->ri_pit[x->ri_index][j]	= temp_f_array[j];
				}
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_rhythm)			{
	    		while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_dur[x->ri_index]	 	= argvec[a].a_w.w_float;
	    			if ( x->ri_dur[x->ri_index] == 0) {
	    				post("notes: ERROR: durations of 0 are not allowed, changing it to last duration");
	    				x->ri_dur[x->ri_index] = 0;
	    				input_check[1] = 0;
	    			}
	    			else {
	    			//	post("duration = %d", x->ri_dur[x->ri_index]);
	    				input_check[1] = 1;
	    			}
	    		}

	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_dynamics)		{
	    		i = 0;
	    		while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_dyn[x->ri_index][i]	 	= argvec[a].a_w.w_float;
	    			i++;
	    		}
	    		x->ri_dyn_n[x->ri_index] = i;
	    		if (x->debug >= 1) post("dynamics = %d", x->ri_dyn[x->ri_index]);
	    		input_check[2] = 1;
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_tuplet)			{
	    		i = 0;
	    		while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_tup[x->ri_index][i] 		= argvec[a].a_w.w_float;
	    			i++;
	    		}
	    		if (i != 3) post("notes: ERROR: not enough arguments for tuplet (need 3... see help file)");
	    		if (x->debug >= 1) post("tuplet = %d %d %d", x->ri_tup[x->ri_index][0], x->ri_tup[x->ri_index][1], x->ri_tup[x->ri_index][2]);
	    		input_check[3] = 1;
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_meter)			{
	    		i = 0;
	    		while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_mtr[x->ri_index][i] 		= argvec[a].a_w.w_float;
	    			i++;
	    		}
	    		if (i != 2) {
	    			post("notes: ERROR: not enough arguments for meter (need 2... see help file)");
	    			input_check[4] = 0;
	    		}
	    		else {
	    			if (x->debug >= 1) post("meter = %d / %d", x->ri_mtr[x->ri_index][0], x->ri_mtr[x->ri_index][1]);
	    			input_check[4] = 1;
	    		}
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_articulation)	{
	    		i = 0;
	    		while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_art[x->ri_index][i] 		= argvec[a].a_w.w_float;
	    			i++;
	    		}
	    		x->ri_art_n[x->ri_index] = i;
			    if (x->debug >= 1) 	post("articulation = %d", x->ri_art_n[x->ri_index]);//if (x->debug >= 1)
	    		input_check[5] = 1;
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_tempo)			{
	    		i = 0;
	    		while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_tmp[x->ri_index][i] 		= argvec[a].a_w.w_float;
	    			i++;
	    		}
	    		if (i != 2) {
	    			post("notes: ERROR: not enough arguments for tempo (need 2... see help file)");
	    			input_check[6] = 0;
	    		}
	    		else {
					if (x->debug >= 1) post("tempo: %d = %d", x->ri_tmp[x->ri_index][0], x->ri_tmp[x->ri_index][1]);
					input_check[6] = 1;
					x->tempo = 1;
				}
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_small_numbers)	{
	    		i = 0;
	    		while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_smn[x->ri_index][i] 		= argvec[a].a_w.w_float;
	    			if (x->debug >= 1) post("small number = %d", x->ri_smn[x->ri_index][i]);
	    			i++;
	    		}
	    		x->ri_smn_n[x->ri_index] = i;

	    		input_check[7] = 1;
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_clef)			{
	    		i = 0;
	    		while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_clef[x->ri_index] 		= argvec[a].a_w.w_float;
	    		}
	    		if (x->debug >= 1) post("clef = %d", x->ri_clef[x->ri_index]);
	    		input_check[8] = 1;
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_accidentals)		{
	    		i = 0;
	    		while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_acc[x->ri_index] 		= argvec[a].a_w.w_float;
	    		}
	    		if (x->ri_acc[x->ri_index] < 0) {x->ri_acc[x->ri_index] = 0; post("ERROR accidentals can only be 0 or 1");}
	    		else if (x->ri_acc[x->ri_index] > 1) {x->ri_acc[x->ri_index] = 1; post("ERROR accidentals can only be 0 or 1");}
	    		if (x->debug >= 1) post("accidentals = %d", x->ri_acc[x->ri_index]);
	    		input_check[9] = 1;
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_tremolo)			{
	    		i = 0;
	    		while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_trm[x->ri_index] 		= argvec[a].a_w.w_float;
	    		}
	    		i=x->ri_trm[x->ri_index];
	    		if(i==128||i==64||i==32||i==16||i==8) {
	    			if (x->debug >= 1) post("tremolo = %d", x->ri_trm[x->ri_index]); /// shouldn't this be trm instead of acc?
	    			input_check[10] = 1;
	    		}
	    		else {
	    			post("notes: ERROR: tremolo is %d, but it cannot be a different number than 16, 32, 64, etc...", x->ri_acc[x->ri_index]);
	    			post("notes: changing tremolo to default of 32");
	    			x->ri_trm[x->ri_index] = 32;
	    			input_check[10] = 1;
	    		}
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_span)			{
	    		i = 0;
	    		while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_spa[x->ri_index][i] 		= argvec[a].a_w.w_float;
	    			if ( x->ri_spa[x->ri_index][i] == 5 && argvec[a+1].a_type == A_FLOAT){
	    				a++;
	    				x->ri_spa_p[x->ri_index] = argvec[a].a_w.w_float;
	    			}
	    			if (x->debug >= 1) post("span=%d", (int) x->ri_spa[x->ri_index][i]);
	    			i++;
	    		}
	    		x->ri_spa_n[x->ri_index] = i;
				input_check[11] = 1;
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_harppedal)			{
                if (argvec[a+1].a_type == A_SYMBOL && a < argcount-1){
                    a++;
                    atom_string(argvec+a, x->ri_hpp[x->ri_index], 1000);
                    x->ri_hpp_n[x->ri_index] = 1;
                    input_check[20] = 1;
                //    post("pedal:");
                //    post(x->ri_hpp[x->ri_index]);
                }
            }
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_text)			{
	    		j = 0;
	    		x->ri_txt_n[x->ri_index] = x->ri_txt_spn_n[x->ri_index] = 0;
	    		for (i=0; i<5; i++) {x->ri_txt_spn[x->ri_index][i] = 0;}
	    		i = 0;
	    		if (argvec[a+1].a_type == A_FLOAT) {
	    		x->ri_txt_spn_n[x->ri_index] = 1;
	    			if (i==0) post("text_span!");
	    			if (argvec[a+1].a_w.w_float == 0 && j == 0) {
	    				post("first element is 0");
	    				x->ri_txt_spn[x->ri_index][0] = 1;
	    				j++;	a++;
						while (argvec[a+1].a_type == A_SYMBOL && a < argcount-1 && i < 32) {
							if (argvec[a+1].a_w.w_symbol != nt_pitch 	&& argvec[a+1].a_w.w_symbol != nt_rhythm
							 && argvec[a+1].a_w.w_symbol != nt_dynamics && argvec[a+1].a_w.w_symbol != nt_tuplet
							 && argvec[a+1].a_w.w_symbol != nt_meter 	&& argvec[a+1].a_w.w_symbol != nt_articulation
							 && argvec[a+1].a_w.w_symbol != nt_tempo 	&& argvec[a+1].a_w.w_symbol != nt_small_numbers
							 && argvec[a+1].a_w.w_symbol != nt_clef 	&& argvec[a+1].a_w.w_symbol != nt_accidentals
							 && argvec[a+1].a_w.w_symbol != nt_tremolo 	&& argvec[a+1].a_w.w_symbol != nt_span
							 && argvec[a+1].a_w.w_symbol != nt_grace	&& argvec[a+1].a_w.w_symbol != nt_harmonic
							 && argvec[a+1].a_w.w_symbol != nt_noteheads) {
								a++;
								atom_string(argvec+a, x->ri_txt[x->ri_index][i], 1000);
								post(x->ri_txt[x->ri_index][i]); // if (x->debug >= 1)
								i++;
							}
							else break;
						}
						x->ri_txt_spn[x->ri_index][1] = i;
						if (argvec[a+1].a_w.w_float == 1 && j == 1) {
							post("second element is 1");
							x->ri_txt_spn[x->ri_index][2] = 1;
							a++; j++;
							while (argvec[a+1].a_type == A_SYMBOL && a < argcount-1 && i < 32) {
							if (argvec[a+1].a_w.w_symbol != nt_pitch 	&& argvec[a+1].a_w.w_symbol != nt_rhythm
							 && argvec[a+1].a_w.w_symbol != nt_dynamics && argvec[a+1].a_w.w_symbol != nt_tuplet
							 && argvec[a+1].a_w.w_symbol != nt_meter 	&& argvec[a+1].a_w.w_symbol != nt_articulation
							 && argvec[a+1].a_w.w_symbol != nt_tempo 	&& argvec[a+1].a_w.w_symbol != nt_small_numbers
							 && argvec[a+1].a_w.w_symbol != nt_clef 	&& argvec[a+1].a_w.w_symbol != nt_accidentals
							 && argvec[a+1].a_w.w_symbol != nt_tremolo 	&& argvec[a+1].a_w.w_symbol != nt_span
							 && argvec[a+1].a_w.w_symbol != nt_grace	&& argvec[a+1].a_w.w_symbol != nt_harmonic
							 && argvec[a+1].a_w.w_symbol != nt_noteheads) {
								a++;
								atom_string(argvec+a, x->ri_txt[x->ri_index][i], 1000);
								post(x->ri_txt[x->ri_index][i]); // if (x->debug >= 1)
								i++;
							}
							else break;
						}
						x->ri_txt_spn[x->ri_index][3] = i;
						if (argvec[a+1].a_type == A_FLOAT && j == 2) {
							x->ri_txt_spn[x->ri_index][4] = argvec[a+1].a_w.w_float;
							post("third element is %d", x->ri_txt_spn[x->ri_index][4]);
							j++;
						}
						if (argvec[a+1].a_type == A_FLOAT && j == 3) {
							x->ri_txt_spn[x->ri_index][5] = argvec[a+1].a_w.w_float;
							post("fourth element is %d", x->ri_txt_spn[x->ri_index][5]);
							j++;
						}
					}
					}
					else if (argvec[a+1].a_w.w_float == 1 && j == 0) {
						x->ri_txt_spn[x->ri_index][0] = 2;
						post("SPAN END RECEIVED");
					//	x->ri_txt_n[x->ri_index] = 1;
					}
					else {
						post("ERROR: if you start a -txt with a number, it has to be 0 to start a text span or 1 to end it.");
					}
	    		}
	    		else {
					while (argvec[a+1].a_type == A_SYMBOL && a < argcount-1 && i < 32) {
						if (argvec[a+1].a_w.w_symbol != nt_pitch 	&& argvec[a+1].a_w.w_symbol != nt_rhythm
						 && argvec[a+1].a_w.w_symbol != nt_dynamics && argvec[a+1].a_w.w_symbol != nt_tuplet
						 && argvec[a+1].a_w.w_symbol != nt_meter 	&& argvec[a+1].a_w.w_symbol != nt_articulation
						 && argvec[a+1].a_w.w_symbol != nt_tempo 	&& argvec[a+1].a_w.w_symbol != nt_small_numbers
						 && argvec[a+1].a_w.w_symbol != nt_clef 	&& argvec[a+1].a_w.w_symbol != nt_accidentals
						 && argvec[a+1].a_w.w_symbol != nt_tremolo 	&& argvec[a+1].a_w.w_symbol != nt_span
						 && argvec[a+1].a_w.w_symbol != nt_grace	&& argvec[a+1].a_w.w_symbol != nt_harmonic
						 && argvec[a+1].a_w.w_symbol != nt_noteheads) {
							a++;
							if (i==0) if (x->debug >= 1) post("regular text");
							atom_string(argvec+a, x->ri_txt[x->ri_index][i], 1000);
							if (x->debug >= 1) post(x->ri_txt[x->ri_index][i]);
							i++;
						}
						else break;
					}
				}
				x->ri_txt_n[x->ri_index] = i; //
				if (x->ri_txt_n[x->ri_index] >= 1) input_check[15] = 1;
				if (x->ri_txt_spn_n[x->ri_index] >= 1) input_check[16] = 1;
				if (x->debug >= 1) post("text n = %d", x->ri_txt_n[x->ri_index]);
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_grace)			{
	    		i = 0;
	    		if (x->debug >= 1) post ("GRACE!");
				while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
					a++;
					x->ri_grc[x->ri_index][i] 		= argvec[a].a_w.w_float;
					i++;
				}
				if (x->ri_grc[x->ri_index][0] < 0) x->ri_grc[x->ri_index][0] = 0;
				if (x->ri_grc[x->ri_index][0] > 3) x->ri_grc[x->ri_index][0] = 3;
				if (x->ri_grc[x->ri_index][1] == 0) {
					post("grace duration == 0, this is a bug, fix me");
					x->ri_grc[x->ri_index][1] = 32;
				}

				i=x->ri_grc[x->ri_index][1];
				if(i==128||i==64||i==32||i==16||i==8) {
					if (x->debug >= 1) post("grace = %d", i);
					input_check[12] = 1;
				}
				else {
					post("notes: ERROR: grace is %d, but it cannot be a different number than 8, 16, 32, 64, or 128", i);
					post("notes: changing grace duration to default of 32");
					x->ri_grc[x->ri_index][1] = 32;
					input_check[12] = 1;
				}
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_harmonic)		{
	    		i = 0;

				while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
					a++;
					x->ri_hrm[x->ri_index][i] 		= argvec[a].a_w.w_float;

					i++;
				}
				x->ri_hrm_n[x->ri_index] = i;
				for (i=0; i<x->ri_hrm_n[x->ri_index]; i++){
					if 		(x->ri_hrm[x->ri_index][i]<=0) {x->ri_hrm[x->ri_index][i] = 1;post("ERROR, you asked for %d, but only harmonics 1 through 5 are allowed", x->ri_hrm[x->ri_index][i]);}
					else if (x->ri_hrm[x->ri_index][i]> 6) {x->ri_hrm[x->ri_index][i] = 6;post("ERROR, you asked for %d, but only harmonics 1 through 5 are allowed", x->ri_hrm[x->ri_index][i]);}
					if (x->debug >= 1) post ("HARMONIC! %d", x->ri_hrm[x->ri_index][i]);
				}
	    	//	post("harmonic = %d", x->ri_hrm_n[x->ri_index]);//if (x->debug >= 1)
	    		input_check[13] = 1;
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_noteheads)	{
	    		i = 0;
	    		if (x->debug >= 1) post ("NOTE HEADS!");
	    		while (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_nhs[x->ri_index][i] 		= argvec[a].a_w.w_float;
	    			i++;
	    		}
	    		x->ri_nhs_n[x->ri_index] = i;
	    		if (x->debug >= 1) post("noteheads = %d", x->ri_art_n[x->ri_index]);//if (x->debug >= 1)
	    		input_check[14] = 1;
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_tie)	{
	    		if (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_tie[x->ri_index] 		= argvec[a].a_w.w_float;
	    			if (x->debug >= 1) post("tie = %d", x->ri_tie[x->ri_index]);
	    		}
	    		input_check[17] = 1;
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_arpeggio)	{
	    		if (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_arp[x->ri_index] 		= argvec[a].a_w.w_float;
	    			if (x->debug >= 1) post("arp = %d", x->ri_arp[x->ri_index]);
	    		}
	    		input_check[19] = 1;
	    	}
//_____________________________________________________________________________
	    	else if ( argvec[a].a_w.w_symbol == nt_cluster)	{
	    		if (argvec[a+1].a_type == A_FLOAT && a < argcount-1) {
	    			a++;
	    			x->ri_clu[x->ri_index] 		= argvec[a].a_w.w_float;
	    			if (x->debug >= 1) post("tuplet = %d", x->ri_clu[x->ri_index]);
	    		}
	    		input_check[18] = 1;
	    	}
//_____________________________________________________________________________
	    	else if (argvec[a].a_type == A_FLOAT) post("WARNING::::::: this float escaped: %f", argvec[a].a_w.w_float);
	    }
	}
	// post("INPUT CHECKs");
    ////CHECK INPUT
	if (input_check[0] == 0) 	{ // if no pitch value is provided then the previous one is kept.
		if (x->ri_index == 0) {
			x->ri_pit[x->ri_index][0] = 60;
			x->ri_cho[x->ri_index] 	= 1;
		}
		else {
			for (i = 0; i < x->ri_cho[x->ri_index - 1]; i++) {
				x->ri_pit[x->ri_index][i] = x->ri_pit[x->ri_index - 1][i];
			}
			x->ri_cho[x->ri_index] 	= x->ri_cho[x->ri_index - 1];
		}
	} // Pitch
	if (input_check[1] == 0) 	{ // if no rhythmic value is provided then the previous one is kept.
		if 	(x->ri_index == 0)	x->ri_dur[x->ri_index]	= 8;
		else					x->ri_dur[x->ri_index] 	= x->ri_dur[x->ri_index - 1];
	} // Duration
	if (input_check[2] == 0) 	{
		x->ri_dyn_n[x->ri_index]	= 0;
	} // Dynamics
	if (input_check[3] == 0) 	{
		x->ri_tup[x->ri_index][0] = x->ri_tup[x->ri_index][1] = x->ri_tup[x->ri_index][2] = 0;
	} // Tuplet
	if (input_check[4] == 0) 	{
		if (x->ri_index == 0) {
			x->ri_mtr[x->ri_index][0] = 4;
			x->ri_mtr[x->ri_index][1] = 4;
		}
		else {
			x->ri_mtr[x->ri_index][0] = x->ri_mtr[x->ri_index-1][0];
			x->ri_mtr[x->ri_index][1] = x->ri_mtr[x->ri_index-1][1];
		}
	} // Meter
	if (input_check[5] == 0) 	{
		x->ri_art_n[x->ri_index] = 0;
	} // Articulation
	if (input_check[6] == 0) 	{
		if (x->ri_index == 0) {
			x->ri_tmp[x->ri_index][0] = 8;
			x->ri_tmp[x->ri_index][1] = 60;
		}
		else {
			x->ri_tmp[x->ri_index][0] = x->ri_tmp[x->ri_index-1][0];
			x->ri_tmp[x->ri_index][1] = x->ri_tmp[x->ri_index-1][1];
		}
	//	post("wrote tempo");
	} // Tempo
	if (input_check[7] == 0) 	{
		x->ri_smn_n[x->ri_index] = 0;
	//	post("no small numbers");
	} // small numbers
	if (input_check[8] == 0) 	{
		if (x->ri_index == 0) {
			x->ri_clef[x->ri_index] = 0;
		}
		else {
			x->ri_clef[x->ri_index] = x->ri_clef[x->ri_index-1];
		}
	//	post("wrote clef");
	} // Clef
	if (input_check[9] == 0) 	{
		if (x->ri_index == 0) {
			x->ri_acc[x->ri_index] = 0;
		}
		else {
			x->ri_acc[x->ri_index] = x->ri_acc[x->ri_index-1];
		}
	//	post("wrote clef");
	} // accidentals
	if (input_check[10] == 0) 	{
			x->ri_trm[x->ri_index] = 0;
	//	post("wrote tremolo");
	} // tremolo
	if (input_check[11] == 0) 	{
		x->ri_spa_n[x->ri_index] = 0;
	} // Spans
	if (input_check[12] == 0) 	{
		x->ri_grc[x->ri_index][0] = 0;
	} // grace notes
	if (input_check[13] == 0) 	{
		x->ri_hrm_n[x->ri_index] = 0;
	} // harmonics
	if (input_check[14] == 0) 	{
		x->ri_nhs_n[x->ri_index] = 0;
	} // note heads
	if (input_check[15] == 0) 	{
		x->ri_txt_n[x->ri_index] = 0;
	} // text
	if (input_check[16] == 0) 	{
		x->ri_txt_spn_n[x->ri_index] = 0;
	} // text span
	if (input_check[17] == 0) 	{
		x->ri_tie[x->ri_index] = 0;
	} // tie
	if (input_check[18] == 0) 	{
		x->ri_clu[x->ri_index] = 0;
	} // cluster
	if (input_check[19] == 0) 	{
		x->ri_arp[x->ri_index] = 0;
	} // arpeggio
    if (input_check[20] == 0) 	{
		x->ri_hpp_n[x->ri_index] = 0;
	} // harp-pedal
	x->ri_index++;
}
////	____________________________________________________ WRITE
void notes_write(t_notes *x, t_symbol *s)								{
	int i, j, k, barcount, barsize, beatsize, dur_remainder, bar_number, beatcount, beat_number, sub_beatsize, subdiv;
	int pow2dot_array[18] = {0, 1, 2, 3, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128, 192, 256, 384};
	int harmonics[6][2] = { {12, 12}, {7, 19}, {5, 24}, {4, 28}, {3, 31}, {2, 34}};
	float temp_f=0;//, temp_f2;
	bar_number=beatcount=barcount=dur_remainder=beat_number = j= i=k= 0;
	x->sb_tp_index = x->i_index = x->tp_index = x->tp_n = x->b_index = x->be_index = x->sb_index = 0;

	if (x->ri_index > 0) 					{
		post("notes: Generating Score ...");
	//// ____________________________________________________________ INPUT SORTING
		if (x->debug >= 1) 				{
			post("\nRAW INPUT LIST :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
			post("i\tdur\ttup\ttup\ttup\tmtr\tmtr");
		 }
		for(i=0; i<x->ri_index; i++) 	{
			if (x->ri_cho[i] == 1 && x->ri_pit[i][0] < 0){
				temp_f = -1000;
				for (j=i; j>0; j--) {
					if (x->ri_pit[j][0] > 0) temp_f = x->ri_pit[j][0];
				}
				if (temp_f == -1000) {
					for (j=i; j<x->ri_index; j++) {
						if (x->ri_pit[j][0] > 0) temp_f = x->ri_pit[j][0];
					}
				}
				if (temp_f == -1000) post("notes: all pitches are negative you should know...");
				else x->ri_pit[x->ri_index][0] = temp_f;
			}
			if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t rawrawraw1", i, (int) x->ri_dur[i], x->ri_tup[i][0], x->ri_tup[i][1], x->ri_tup[i][2], x->ri_mtr[i][0], x->ri_mtr[i][1]);
		}
		post("notes: Sorting Input ...");
		if (x->debug >= 1) 				{
			post("\nSORTING INPUT :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
		}
		x->tp_index = x->tp_n = 0;

		// SORT INTO TUPLETS, GRACE NOTES, AND REGULAR NOTES
		for(i=0; i<x->ri_index; i++) 	{
			if (x->ri_tup[i][0] != 0) {
				//if (x->debug >= 3)
				if (x->debug >= 1) post("TUP");
				x->ri_index_sort[i] = 2;
				x->tp_info[x->tp_n][0] = x->ri_tup[i][0]; // reference beat duration
				x->tp_info[x->tp_n][1] = x->ri_tup[i][1]; // fit
				x->tp_info[x->tp_n][2] = x->ri_tup[i][2]; // into
				x->tp_info[x->tp_n][3] = i; // starting tp index************

				x->i_mtr[x->i_index][0] = x->ri_mtr[i][0];
				x->i_mtr[x->i_index][1] = x->ri_mtr[i][1];
				x->i_tup[x->i_index]	= x->tp_n;
				x->i_dur[x->i_index]	= x->refdur/x->ri_tup[i][0] * x->ri_tup[i][2]; //(added / refdur
				x->i_tie[x->i_index]	= 0;
				dur_remainder 			= x->refdur/x->ri_tup[i][0] * x->ri_tup[i][1];
				x->i_rii[x->i_index]	= i;

				x->tp_i[x->tp_index]	= x->i_index; // reference to clean/precessed input or just "input"
				x->tp_ri[x->tp_index]	= i; // reference to raw input indexes
				x->tp_dur[x->tp_index]	= x->ri_dur[i];
				x->tp_num[x->tp_index]	= x->tp_n;
				beatcount 				= x->tp_dur[x->tp_index];
				//post("a");
				x->tp_index++;
				if (x->debug >= 1) post("PRE  While Fx: beatcount=%d\tdur_remainder=%d", beatcount, dur_remainder);
				while (  (beatcount + x->ri_dur[i+1]) <= dur_remainder && i < x->ri_index && beatcount-dur_remainder !=0) {
					i++;
					if (x->ri_grc[i][0] > 0) {
						if (x->debug >= 1) post("GRACE");
						x->ri_index_sort[i]  = 3;
						x->g_rii[x->i_index] = i;
						x->g_dur[x->i_index] = x->ri_grc[i][1];
						x->g_index++;
					}		//// GRACE NOTES
					else {
						x->tp_i[x->tp_index]	= x->i_index; // reference to clean/precessed input or just "input"
						x->tp_ri[x->tp_index]	= i; // reference to raw input indexes
						x->ri_index_sort[i]  	= 1;
						x->tp_dur[x->tp_index]	= x->ri_dur[i];
						x->tp_tie[x->tp_index]	= 0;
						x->tp_num[x->tp_index]	= x->tp_n;
						beatcount 				+= x->tp_dur[x->tp_index];
						x->tp_index++;
					}
				//	post("b");
				}
				x->i_index++;
				if (x->debug >= 1) post("POST While Fx: beatcount=%d\tdur_remainder=%d", beatcount, dur_remainder);
				if (beatcount < dur_remainder) {
					post("¡¡¡¡¡¡¡WARNING!!!!!! Tuplet no. %d has a longer duration than declared length, tied to regular beat", x->tp_n);

					i++;
					x->tp_i[x->tp_index]	= x->i_index; // reference to clean/precessed input or just "input"
					x->tp_ri[x->tp_index]	= i; // reference to raw input indexes
					x->tp_dur[x->tp_index]	= dur_remainder - beatcount;
					x->tp_tie[x->tp_index]	= 1;
					x->tp_num[x->tp_index]	= x->tp_n;

					x->i_mtr[x->i_index][0] = x->i_mtr[x->i_index-1][0];
					x->i_mtr[x->i_index][1] = x->i_mtr[x->i_index-1][1];
					x->i_dur[x->i_index]	= x->ri_dur[i] - x->tp_dur[x->tp_index];
					x->i_rii[x->i_index]	= i;
					x->i_tie[x->i_index]	= 1;
					x->i_tup[x->i_index]	= -1;
				//	x->tp_info[x->tp_n][4] = x->tp_index; // ending tp index
					//post("c");
					x->i_index++;
					x->tp_index++;
				}
				x->tp_info[x->tp_n][4] = i; // ending tp index
				x->tp_n++;
			}      	//// TUPLETS
			else if (x->ri_grc[i][0] > 0) {
			//	if (x->debug >= 3)
				if (x->debug >= 1) post("GRACE");
				x->ri_index_sort[i]  = 3;
				x->g_rii[x->i_index] = i;
				x->g_dur[x->i_index] = x->ri_grc[i][1];
				x->g_index++;
			}		//// GRACE NOTES
			else {
				//if (x->debug >= 3)
				if (x->debug >= 1) post("NO TUP");
				x->ri_index_sort[i] = 2;
				x->i_mtr[x->i_index][0] = x->ri_mtr[i][0];
				x->i_mtr[x->i_index][1] = x->ri_mtr[i][1];
				x->i_dur[x->i_index]	= x->ri_dur[i];
				x->i_tie[x->i_index]	= x->ri_tie[i];
				x->i_rii[x->i_index]	= i;
				x->i_tup[x->i_index]	= -1;
				x->i_index++;
			}        						//// REGULAR NOTES
		}
		if (x->debug >= 1) post("INPUT TYPES\t(1:normal, 2:tuplet, 3:grace)\nrawi\ttype");
		for (i=0; i<x->ri_index; i++) 	{
			if (x->debug >= 1) post("%d\t%d", i, x->ri_index_sort[i]);
		}
	//// ____________________________________________________________  GRACE PROGRAM
		for(i=0; i<x->g_index; i++){

		}
	//// ____________________________________________________________  TUPLET PROGRAM
		if (x->debug >= 1) 				{
			post("\nRAW TUPLET INFO :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
			post("i\trefdur\tfit\tinto\tstart\tend");
		}
		if (x->tp_n == 0) post("no tuplets!");
		for(i=0; i<x->tp_n; i++) 		{
			if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d", i, x->tp_info[i][0], x->tp_info[i][1], x->tp_info[i][2], x->tp_info[i][3], x->tp_info[i][4]);
		}
		if (x->debug >= 1) 				{
			post("\nRAW TUPLET LIST :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
			post("i\ttp_n\traw_i\tclean_i\tdur\ttie");
		}
		x->b_tp_index = x->tp_index;
		for(i=0; i<x->tp_index; i++) 	{
			if (x->tp_num[i] != x->tp_num[i-1]) post("-   -   -   -   -   -   -   -   -   -   -   -   ");
			if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d", i, x->tp_num[i], x->tp_ri[i], x->tp_i[i], (int) x->tp_dur[i], x->tp_tie[i]);
			x->b_tp_dur[i] 		= x->tp_dur[i];
			x->b_tp_ri[i]		= x->tp_ri[i];
			x->b_tp_i[i]		= x->tp_i[i];
			x->b_tp_tie[i]		= x->tp_tie[i];
			x->b_tp_num[i]		= x->tp_num[i];
		} /// RAW TUPLET LIST
		if (x->debug >= 1) 				{
			post("\nSORTING TUPLET RHYTHMS :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
		}
		if (x->tp_n > 0) {
			for (k=0; k<4; k++) 			{
				beatcount = 0;
				subdiv = (int) exp2( (float) k );
				if (x->debug >= 3) post("subdiv=%d", subdiv);
				beatsize = x->refdur/x->tp_info[0][0]; // i.e. 32 / 16
				sub_beatsize = beatsize / subdiv;
				if (sub_beatsize <= 2) break;
				x->sb_tp_index = 0;
				if (x->debug >= 3) post("beatsize=%d\tsubdiv=%d\tsub_beatsize=%d", beatsize, subdiv, sub_beatsize);
				i = 0;
				if (x->debug >= 3) post("%d 1***************   TUPLET %d   *************** %d", i, i, i);
				for(i=0; i<x->b_tp_index; i++) {
					while (beatcount >= beatsize) {
						beatcount -= beatsize;
					}
					if (i>0 && x->b_tp_num[i] != x->b_tp_num[i-1]) {
						if (x->debug >= 3) post("CASE 1");
						if (x->debug >= 3) post("%d 2***************   TUPLET %d   *************** %d", x->b_tp_num[i], x->b_tp_num[i], x->b_tp_num[i]);
						beatsize = x->tp_info[x->b_tp_num[i]][0];
						sub_beatsize = beatsize / subdiv;
						if (x->debug >= 3) post("beatsize=%d\tsubdiv=%d\tsub_beatsize=%d", beatsize, subdiv, sub_beatsize);
						beatcount = 0;
					}
					if (sub_beatsize >= 4) {
					//	if (x->debug >= 3) post("CASE 2");
						if 	(((beatcount + x->b_tp_dur[i]) <= sub_beatsize)) {
							if (x->debug >= 3) post("CASE 2.1\tsub_beatsize=\t%d\tbeatcount=\t%d", sub_beatsize, beatcount);
							x->sb_tp_dur[x->sb_tp_index] 	= x->b_tp_dur[i];
							x->sb_tp_ri[x->sb_tp_index]		= x->b_tp_ri[i];
							x->sb_tp_i[x->sb_tp_index]		= x->b_tp_i[i];
							x->sb_tp_tie[x->sb_tp_index]	= x->b_tp_tie[i];
							x->sb_tp_num[x->sb_tp_index] 	= x->b_tp_num[i];
							if (x->debug >= 3) post("%d\t%d\t%d\t%d\t%d\t%d", 	x->sb_tp_index, x->sb_tp_num[x->sb_tp_index], x->sb_tp_ri[x->sb_tp_index], x->sb_tp_i[x->sb_tp_index], x->sb_tp_dur[x->sb_tp_index], x->sb_tp_tie[x->sb_tp_index]);
							beatcount 			+= x->b_tp_dur[i];
							while (beatcount >= sub_beatsize) {
								beatcount -= sub_beatsize;
							}
							if (x->debug >= 3 && beatcount % beatsize == 0) post("-   -   -   -   -   -   -   -   -   -   -   -   ");
							x->sb_tp_index++;
						}
						else if	((beatcount == 0) && ((x->b_tp_dur[i] % sub_beatsize) == 0)) {
							if (x->debug >= 3) post("CASE 2.2\tsub_beatsize=\t%d\tbeatcount=\t%d", sub_beatsize, beatcount);
							for(j=0; j<32; j++){
								if (x->tp_dur[i] == sub_beatsize * j) {
									x->sb_tp_dur[x->sb_tp_index] 	= x->b_tp_dur[i];
									x->sb_tp_ri[x->sb_tp_index]		= x->b_tp_ri[i];
									x->sb_tp_i[x->sb_tp_index]		= x->b_tp_i[i];
									x->sb_tp_tie[x->sb_tp_index]	= x->b_tp_tie[i];
									x->sb_tp_num[x->sb_tp_index] 	= x->b_tp_num[i];
									if (x->debug >= 3) post("%d\t%d\t%d\t%d\t%d\t%d", 	x->sb_tp_index, x->sb_tp_num[x->sb_tp_index], x->sb_tp_ri[x->sb_tp_index], x->sb_tp_i[x->sb_tp_index], x->sb_tp_dur[x->sb_tp_index], x->sb_tp_tie[x->sb_tp_index]);
									beatcount 			+= x->b_tp_dur[i];
									while (beatcount >= sub_beatsize) {
										beatcount -= sub_beatsize;
									}
									if (x->debug >= 3 && beatcount % beatsize == 0) post("-   -   -   -   -   -   -   -   -   -   -   -   ");
									x->sb_tp_index++;
									break;
								}
							}
						}
						else if (sub_beatsize == beatcount || (sub_beatsize + x->b_tp_dur[i]) == beatcount) {
							if (x->debug >= 3) post("CASE 2.3\tsub_beatsize=\t%d\tbeatcount=\t%d", sub_beatsize, beatcount);
								x->sb_tp_dur[x->sb_tp_index] 	= x->b_tp_dur[i];
								x->sb_tp_ri[x->sb_tp_index]		= x->b_tp_ri[i];
								x->sb_tp_i[x->sb_tp_index]		= x->b_tp_i[i];
								x->sb_tp_tie[x->sb_tp_index]	= x->b_tp_tie[i];
								x->sb_tp_num[x->sb_tp_index] 	= x->b_tp_num[i];
								if (x->debug >= 3) post("%d\t%d\t%d\t%d\t%d\t%d", 	x->sb_tp_index, x->sb_tp_num[x->sb_tp_index], x->sb_tp_ri[x->sb_tp_index], x->sb_tp_i[x->sb_tp_index], x->sb_tp_dur[x->sb_tp_index], x->sb_tp_tie[x->sb_tp_index]);
								beatcount 			+= x->b_tp_dur[i];
								while (beatcount >= sub_beatsize) {
									beatcount -= sub_beatsize;
								}
								if (x->debug >= 3 && beatcount % beatsize == 0) post("-   -   -   -   -   -   -   -   -   -   -   -   ");
								x->sb_tp_index++;
						}
						else {
							if (x->debug >= 3) post("CASE 2.4\tsub_beatsize=\t%d\tbeatcount=\t%d", sub_beatsize, beatcount);
							if (sub_beatsize != beatcount) {
								if (x->debug >= 3) post("CASE 2.4.1");
								x->sb_tp_dur[x->sb_tp_index] 	= abs(sub_beatsize - beatcount);
								x->sb_tp_ri[x->sb_tp_index]		= x->b_tp_ri[i];
								x->sb_tp_i[x->sb_tp_index]		= x->b_tp_i[i];
								x->sb_tp_tie[x->sb_tp_index]	= 1;
								x->sb_tp_num[x->sb_tp_index] 	= x->b_tp_num[i];
								if (x->debug >= 3) {post("%d\t%d\t%d\t%d\t%d\t%d", 	x->sb_tp_index, x->sb_tp_num[x->sb_tp_index], x->sb_tp_ri[x->sb_tp_index], x->sb_tp_i[x->sb_tp_index], x->sb_tp_dur[x->sb_tp_index], x->sb_tp_tie[x->sb_tp_index]); post("-   -   -   -   -   -   -   -   -   -   -   -   ");}
								x->sb_tp_index++;
								dur_remainder = x->b_tp_dur[i] - x->sb_tp_dur[x->sb_tp_index-1];
							}
							else {
								if (x->debug >= 3) post("CASE 2.4.2~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
								dur_remainder = x->b_tp_dur[i];
							}
							while (dur_remainder > sub_beatsize) {
								x->sb_tp_dur[x->sb_tp_index] 	= sub_beatsize;
								x->sb_tp_ri[x->sb_tp_index]		= x->b_tp_ri[i];
								x->sb_tp_i[x->sb_tp_index]		= x->b_tp_i[i];
								x->sb_tp_tie[x->sb_tp_index]	= 1;
								x->sb_tp_num[x->sb_tp_index] 	= x->b_tp_num[i];

								if (x->debug >= 3){ post("%d\t%d\t%d\t%d\t%d\t%d", 	x->sb_tp_index, x->sb_tp_num[x->sb_tp_index], x->sb_tp_ri[x->sb_tp_index], x->sb_tp_i[x->sb_tp_index], x->sb_tp_dur[x->sb_tp_index], x->sb_tp_tie[x->sb_tp_index]); post("-   -   -   -   -   -   -   -   -   -   -   -   ");}
								x->sb_tp_index++;

								dur_remainder 					-= sub_beatsize;
							}

							x->sb_tp_dur[x->sb_tp_index] 	= dur_remainder;
							x->sb_tp_ri[x->sb_tp_index]		= x->b_tp_ri[i];
							x->sb_tp_i[x->sb_tp_index]		= x->b_tp_i[i];
							x->sb_tp_tie[x->sb_tp_index]	= x->b_tp_tie[i];
							x->sb_tp_num[x->sb_tp_index] 	= x->b_tp_num[i];

							beatcount 			+= x->b_tp_dur[i];
							while (beatcount >= sub_beatsize) {
								beatcount -= sub_beatsize;
							}
							if (x->debug >= 3)post("%d\t%d\t%d\t%d\t%d\t%d", 	x->sb_tp_index, x->sb_tp_num[x->sb_tp_index], x->sb_tp_ri[x->sb_tp_index], x->sb_tp_i[x->sb_tp_index], x->sb_tp_dur[x->sb_tp_index], x->sb_tp_tie[x->sb_tp_index]);
							if (x->debug >= 3 && beatcount % beatsize == 0) post("-   -   -   -   -   -   -   -   -   -   -   -   ");
							x->sb_tp_index++;
						}
					}
					else {
						if (x->debug >= 3) post("CASE else");
						x->sb_tp_dur[x->sb_tp_index] 	= x->b_tp_dur[i];
						x->sb_tp_ri[x->sb_tp_index]		= x->b_tp_ri[i];
						x->sb_tp_i[x->sb_tp_index]		= x->b_tp_i[i];
						x->sb_tp_tie[x->sb_tp_index]	= x->b_tp_tie[i];
						x->sb_tp_num[x->sb_tp_index] 	= x->b_tp_num[i];
						if (x->debug >= 3) post("%d\t%d\t%d\t%d\t%d\t%d", 	x->sb_tp_index, x->sb_tp_num[x->sb_tp_index], x->sb_tp_ri[x->sb_tp_index], x->sb_tp_i[x->sb_tp_index], x->sb_tp_dur[x->sb_tp_index], x->sb_tp_tie[x->sb_tp_index]);
						beatcount 			+= x->b_tp_dur[i];
						if (x->debug >= 3 && beatcount % beatsize == 0) post("-   -   -   -   -   -   -   -   -   -   -   -   ");
						x->sb_tp_index++;
					}

				}
				for(i=0; i<x->sb_tp_index; i++){
					x->b_tp_dur[i] 		= x->sb_tp_dur[i];
					x->b_tp_ri[i]		= x->sb_tp_ri[i];
					x->b_tp_i[i]		= x->sb_tp_i[i];
					x->b_tp_tie[i]		= x->sb_tp_tie[i];
					x->b_tp_num[i]		= x->sb_tp_num[i];
				}
				x->b_tp_index 	= x->sb_tp_index;
			}
		}
		if (x->debug >= 1) 				{
			post("\nFINAL TUPLET LIST :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
			post("i\ttp_n\traw_i\tclean_i\tdur\ttie");
		}
		post("subbeat index = %d", x->sb_tp_index);
		for(i=0; i<x->sb_tp_index; i++) {
			if (x->sb_tp_num[i] != x->sb_tp_num[i-1]) if (x->debug >= 1) post("-   -   -   -   -   -   -   -   -   -   -   -   ");
			if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d", i, x->sb_tp_num[i], x->sb_tp_ri[i], x->sb_tp_i[i], (int) x->sb_tp_dur[i], x->sb_tp_tie[i]);
		}

	//// ____________________________________________________________ BAR and BEAT Programs
		if (x->debug >= 1) 				{
			post("\nCLEAN INPUT LIST :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
			post("i\traw_i\tdur\ttie\ttup");
		}
		for(i=0; i<x->i_index; i++) 	{
			if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d", i, x->i_rii[i], (int) x->i_dur[i], x->i_tie[i], x->i_tup[i]);
			if ( x->i_tup[i] >= 0) {
				if (x->debug >= 1) post("Tuplet will replace last line");
			}
		}
	//	/*
	//// ____________________________________________________________  BAR SUBDIVISION
		if (x->debug >= 1) post(".\nBAR PROGRAMs ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n.");
/////////////////////// BREAK INPUT INTO BARS
		int ii;
		if (x->FOLLOW == 0) {
			beatsize = exp2f( (float) (log2f((float) x->refdur) - log2f((float) x->i_mtr[0][1])));
			barsize = (int) x->i_mtr[0][0] * beatsize;
			x->bar_info[0][0] = 0;
			x->bar_info[0][1] = x->i_mtr[0][0];
			x->bar_info[0][2] = x->i_mtr[0][1];
			x->bar_info[0][3] = beatsize;
			x->bar_info[0][4] = barsize;
			if (x->debug >= 1) 				{
				post("num=%d", (int) x->i_mtr[0][0]);
				post("refdur=%d denom=%d beatsize=%d", x->refdur, x->i_mtr[0][1], beatsize);
				post("barsize=%d\n", barsize);
				post("i\tbar no.\tclean i\traw i\tdur\ttie\ttuplet");
				post("BAR %d - - - - - - - - - - - - - - - - - - - - - - - - - - - - ", bar_number);
			}
			barcount = 0;
			for(i=0; i<x->i_index; i++) 	{
				if		(i > 1 && (x->i_mtr[i][0] != x->i_mtr[i-1][0] || x->i_mtr[i][1] != x->i_mtr[i-1][1])) {
					if 	(barcount != 0) {
						x->bar_info[bar_number][1] = barcount;
						x->bar_info[bar_number][2] = 32;
						temp_f = reduce_meter(x->bar_info[bar_number][1]);
						if (temp_f != 0) {
							x->bar_info[bar_number][1] = (int) temp_f;
							temp_f = ((temp_f - (int) temp_f) * 100.) + 0.02;
							x->bar_info[bar_number][2] = (int) temp_f;
						}
						beatsize = exp2f( (float) (log2f((float) x->refdur) - log2f((float) x->bar_info[bar_number][2])));
						barsize = (int) x->bar_info[bar_number][1] * beatsize;
						beatsize = get_beatsize(x->bar_info[bar_number][1], x->bar_info[bar_number][2], x->refdur);
						x->bar_info[bar_number][3] = beatsize;
						x->bar_info[bar_number][4] = barsize;
						if (x->debug >= 1) post("Meter change::: %d / %d", x->bar_info[bar_number][1], x->bar_info[bar_number][2]);
						bar_number++;
						x->bar_info[bar_number][0] = x->b_index;
						if (x->debug >= 1) post("BAR %d - - - - - - - - - - - - - - - - - - - - - - - - - - - - ", bar_number);
					}
					beatsize = exp2f( (float) (log2f((float) x->refdur) - log2f((float) x->i_mtr[0][1])));
					barsize = (int) x->i_mtr[i][0] * beatsize;
					beatsize = get_beatsize(x->i_mtr[i][0], x->i_mtr[i][1], x->refdur);
					x->bar_info[bar_number][1] = x->i_mtr[i][0];
					x->bar_info[bar_number][2] = x->i_mtr[i][1];
					x->bar_info[bar_number][3] = beatsize;
					x->bar_info[bar_number][4] = barsize;
					barcount = 0;
					if (x->debug >= 1) post("Meter change::: %d / %d", x->bar_info[bar_number][1], x->bar_info[bar_number][2]);
				}
				if		(barcount + x->i_dur[i] <= barsize){
					x->b_dur[x->b_index] 	= x->i_dur[i]; //duration
					x->b_tie[x->b_index] 	= x->i_tie[i]; // tie
					x->b_i[x->b_index] 		= i; // clean input number
					x->bar_n[x->b_index] 	= bar_number; // bar number
					x->b_rii[x->b_index]	= x->i_rii[i]; //raw input number
					x->b_tup[x->b_index] 	= x->i_tup[i]; //tuplet
					barcount += x->i_dur[i];
					if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d", x->b_index, x->bar_n[x->b_index], x->b_i[x->b_index], x->b_rii[x->b_index], x->b_dur[x->b_index], x->b_tie[x->b_index], x->b_tup[x->b_index]);
					x->b_index++;
					if (barcount == barsize) {
						bar_number++;
						barcount 					= 0;
						x->bar_info[bar_number][0] 	= x->b_index;
						x->bar_info[bar_number][1] 	= x->i_mtr[i][0];
						x->bar_info[bar_number][2] 	= x->i_mtr[i][1];
						x->bar_info[bar_number][3] 	= beatsize;
						x->bar_info[bar_number][4] 	= barsize;
						if (x->debug >= 1) post("BAR %d - - - - - - - - - - - - - - - - - - - - - - - - - - - - ", bar_number);
					}
				}
				else 	{
					x->b_dur[x->b_index] 	= barsize - barcount;
					barcount 				= 0;
					dur_remainder 			= x->i_dur[i] - x->b_dur[x->b_index];
					x->b_tie[x->b_index] 	= 1;
					x->b_i[x->b_index] 		= i;
					x->bar_n[x->b_index] 	= bar_number;
					x->b_rii[x->b_index]	= x->i_rii[i]; //raw input number
					x->b_tup[x->b_index] 	= x->i_tup[i]; //tuplet
					if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d", x->b_index, x->bar_n[x->b_index], x->b_i[x->b_index], x->b_rii[x->b_index], x->b_dur[x->b_index], x->b_tie[x->b_index], x->b_tup[x->b_index]);
					x->b_index++;
					bar_number++;
					x->bar_info[bar_number][0] = x->b_index;
					x->bar_info[bar_number][1] = x->i_mtr[i][0];
					x->bar_info[bar_number][2] = x->i_mtr[i][1];
					x->bar_info[bar_number][3] = beatsize;
					x->bar_info[bar_number][4] = barsize;
					if (x->debug >= 1) post("BAR %d - - - - - - - - - - - - - - - - - - - - - - - - - - - - ", bar_number);

					while (dur_remainder > 0) {
						if		(barcount + dur_remainder <= barsize) {
							x->b_dur[x->b_index] 	= dur_remainder;
							x->b_tie[x->b_index]	= x->i_tie[i];
							x->b_i[x->b_index] 		= i;
							x->b_rii[x->b_index]	= x->i_rii[i]; ////raw input number
							x->b_tup[x->b_index] 	= x->i_tup[i]; //tuplet
							x->bar_n[x->b_index] 	= bar_number;
							barcount += dur_remainder;
							if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d", x->b_index, x->bar_n[x->b_index], x->b_i[x->b_index], x->b_rii[x->b_index], x->b_dur[x->b_index], x->b_tie[x->b_index], x->b_tup[x->b_index]);
							x->b_index++;
							if (barcount == barsize) {
								barcount 					= 0;
								bar_number++;
								x->bar_info[bar_number][0] 	= x->b_index;
								x->bar_info[bar_number][1] 	= x->i_mtr[i][0];
								x->bar_info[bar_number][2] 	= x->i_mtr[i][1];
								x->bar_info[bar_number][3] 	= beatsize;
								x->bar_info[bar_number][4] 	= barsize;
								if (x->debug >= 1) post("BAR %d - - - - - - - - - - - - - - - - - - - - - - - - - - - - ", bar_number);
							}
							dur_remainder = 0;
						}
						else {
							// copy pitches
							x->b_dur[x->b_index] 	= barsize;
							barcount 				= 0;
							dur_remainder 			-= barsize;
							x->b_tie[x->b_index] 	= 1;
							x->b_i[x->b_index] 		= i;
							x->b_rii[x->b_index]	= x->i_rii[i]; //raw input number
							x->b_tup[x->b_index] 	= x->i_tup[i]; //tuplet
							x->bar_n[x->b_index] 	= bar_number;
							if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d", x->b_index, x->bar_n[x->b_index], x->b_i[x->b_index], x->b_rii[x->b_index], x->b_dur[x->b_index], x->b_tie[x->b_index], x->b_tup[x->b_index]);
							x->b_index++;
							bar_number++;
							x->bar_info[bar_number][0] = x->b_index;
							x->bar_info[bar_number][1] = x->i_mtr[i][0];
							x->bar_info[bar_number][2] = x->i_mtr[i][1];
							x->bar_info[bar_number][3] = beatsize;
							x->bar_info[bar_number][4] = barsize;
							if (x->debug >= 1) post("BAR %d - - - - - - - - - - - - - - - - - - - - - - - - - - - - ", bar_number);
						}
					}
				}
			}
		}
	////////// BREAK INPUT INTO THE (imported) MASTER BARS
		else {
		//////// READ BARFILE
			FILE *fp3;
			fp3 = fopen( x->barfile, "r");
			if(!fp3) {
				pd_error(x, "%s: couldn't read barfile, send one to the second inlet", x->barfile);
				return;
			}
			else 	ii = readbarfile(x->bar_info, (FILE *) fp3); //////sdsdfsdfsdfsdf
//////sdsdfsdfsdfsdf//////sdsdfsdfsdfsdf//////sdsdfsdfsdfsdf//////sdsdfsdfsdfsdf
//////sdsdfsdfsdfsdf//////sdsdfsdfsdfsdf//////sdsdfsdfsdfsdf//////sdsdfsdfsdfsdf
//////sdsdfsdfsdfsdf//////sdsdfsdfsdfsdf//////sdsdfsdfsdfsdf//////sdsdfsdfsdfsdf
//////sdsdfsdfsdfsdf//////sdsdfsdfsdfsdf//////sdsdfsdfsdfsdf//////sdsdfsdfsdfsdf
			if (x->debug >= 1){
				post("Reading Master Bar File");
				post("i\tnum\tdenom\tbeatsize\tbarsize\t");
				for (i=0;i<ii;i++){
					post("%d\t%d\t%d\t%d\t%d\t", i, x->bar_info[i][1], x->bar_info[i][2], x->bar_info[i][3], x->bar_info[i][4]);
				}
			}
		//////// BREAK INPUT BY BARFILE
			beatsize 	= x->bar_info[0][3];
			barsize 	= x->bar_info[0][4];
			x->bar_info[0][0] = 0;
			if (x->debug >= 1) 				{
				post("num=%d", (int) x->bar_info[0][1]);
				post("refdur=%d denom=%d beatsize=%d", x->refdur, x->bar_info[0][2], beatsize);
				post("barsize=%d\n", barsize);
				post("i\tbar no.\tclean i\traw i\tdur\ttie\ttuplet");
				post("BAR %d - - - - - - - - - - - - - - - - - - - - - - - - - - - - ", bar_number);
			}
			barcount = 0;
			x->bar_info[bar_number][0] = x->b_index;
			for(i=0; i<x->i_index; i++) 	{
				if		(barcount + x->i_dur[i] <= barsize){
					x->b_dur[x->b_index] 	= x->i_dur[i]; //duration
					x->b_tie[x->b_index] 	= x->i_tie[i]; // tie
					x->b_i[x->b_index] 		= i; // clean input number
					x->bar_n[x->b_index] 	= bar_number; // bar number
					x->b_rii[x->b_index]	= x->i_rii[i]; //raw input number
					x->b_tup[x->b_index] 	= x->i_tup[i]; //tuplet
					barcount += x->i_dur[i];
					if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d", x->b_index, x->bar_n[x->b_index], x->b_i[x->b_index], x->b_rii[x->b_index], x->b_dur[x->b_index], x->b_tie[x->b_index], x->b_tup[x->b_index]);
					x->b_index++;
					if (barcount == barsize) {
						bar_number++;
						barcount 					= 0;
						x->bar_info[bar_number][0] 	= x->b_index;
						beatsize 	= x->bar_info[bar_number][3];
						barsize 	= x->bar_info[bar_number][4];
						if (bar_number >= ii) {
							x->bar_info[bar_number][1] 	= x->bar_info[bar_number-1][1];
							x->bar_info[bar_number][2] 	= x->bar_info[bar_number-1][2];
							x->bar_info[bar_number][3] 	= x->bar_info[bar_number-1][3];
							x->bar_info[bar_number][4] 	= x->bar_info[bar_number-1][4];
							beatsize 					= x->bar_info[bar_number][3];
							barsize 					= x->bar_info[bar_number][4];
						}
						if (x->debug >= 1) post("BAR %d - - - - - - - - - - - - - - - - - - - - - - - - - - - - ", bar_number);
					}
				}
				else 	{
					x->b_dur[x->b_index] 	= barsize - barcount;
					barcount 				= 0;
					dur_remainder 			= x->i_dur[i] - x->b_dur[x->b_index];
					x->b_tie[x->b_index] 	= 1;
					x->b_i[x->b_index] 		= i;
					x->bar_n[x->b_index] 	= bar_number;
					x->b_rii[x->b_index]	= x->i_rii[i]; //raw input number
					x->b_tup[x->b_index] 	= x->i_tup[i]; //tuplet
					if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d", x->b_index, x->bar_n[x->b_index], x->b_i[x->b_index], x->b_rii[x->b_index], x->b_dur[x->b_index], x->b_tie[x->b_index], x->b_tup[x->b_index]);
					x->b_index++;
					bar_number++;
					x->bar_info[bar_number][0] = x->b_index;
					beatsize 	= x->bar_info[bar_number][3];
					barsize 	= x->bar_info[bar_number][4];
					if (bar_number >= ii) {
						x->bar_info[bar_number][1] 	= x->bar_info[bar_number-1][1];
						x->bar_info[bar_number][2] 	= x->bar_info[bar_number-1][2];
						x->bar_info[bar_number][3] 	= x->bar_info[bar_number-1][3];
						x->bar_info[bar_number][4] 	= x->bar_info[bar_number-1][4];
						beatsize 					= x->bar_info[bar_number][3];
						barsize 					= x->bar_info[bar_number][4];
					}
					if (x->debug >= 1) post("BAR %d - - - - - - - - - - - - - - - - - - - - - - - - - - - - ", bar_number);

					while (dur_remainder > 0) {
						if		(barcount + dur_remainder <= barsize) {
							x->b_dur[x->b_index] 	= dur_remainder;
							x->b_tie[x->b_index]	= x->i_tie[i];
							x->b_i[x->b_index] 		= i;
							x->b_rii[x->b_index]	= x->i_rii[i]; ////raw input number
							x->b_tup[x->b_index] 	= x->i_tup[i]; //tuplet
							x->bar_n[x->b_index] 	= bar_number;
							barcount += dur_remainder;
							if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d", x->b_index, x->bar_n[x->b_index], x->b_i[x->b_index], x->b_rii[x->b_index], x->b_dur[x->b_index], x->b_tie[x->b_index], x->b_tup[x->b_index]);
							x->b_index++;
							if (barcount == barsize) {
								barcount 					= 0;
								bar_number++;
								x->bar_info[bar_number][0] 	= x->b_index;
								beatsize 	= x->bar_info[bar_number][3];
								barsize 	= x->bar_info[bar_number][4];
								if (bar_number >= ii) {
									x->bar_info[bar_number][1] 	= x->bar_info[bar_number-1][1];
									x->bar_info[bar_number][2] 	= x->bar_info[bar_number-1][2];
									x->bar_info[bar_number][3] 	= x->bar_info[bar_number-1][3];
									x->bar_info[bar_number][4] 	= x->bar_info[bar_number-1][4];
									beatsize 					= x->bar_info[bar_number][3];
									barsize 					= x->bar_info[bar_number][4];
								}
								if (x->debug >= 1) post("BAR %d - - - - - - - - - - - - - - - - - - - - - - - - - - - - ", bar_number);
							}
							dur_remainder = 0;
						}
						else {
							// copy pitches
							x->b_dur[x->b_index] 	= barsize;
							barcount 				= 0;
							dur_remainder 			-= barsize;
							x->b_tie[x->b_index] 	= 1;
							x->b_i[x->b_index] 		= i;
							x->b_rii[x->b_index]	= x->i_rii[i]; //raw input number
							x->b_tup[x->b_index] 	= x->i_tup[i]; //tuplet
							x->bar_n[x->b_index] 	= bar_number;
							if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d", x->b_index, x->bar_n[x->b_index], x->b_i[x->b_index], x->b_rii[x->b_index], x->b_dur[x->b_index], x->b_tie[x->b_index], x->b_tup[x->b_index]);
							x->b_index++;
							bar_number++;
							x->bar_info[bar_number][0] = x->b_index;
							beatsize 	= x->bar_info[bar_number][3];
							barsize 	= x->bar_info[bar_number][4];
							if (bar_number >= ii) {
								x->bar_info[bar_number][1] 	= x->bar_info[bar_number-1][1];
								x->bar_info[bar_number][2] 	= x->bar_info[bar_number-1][2];
								x->bar_info[bar_number][3] 	= x->bar_info[bar_number-1][3];
								x->bar_info[bar_number][4] 	= x->bar_info[bar_number-1][4];
								beatsize 					= x->bar_info[bar_number][3];
								barsize 					= x->bar_info[bar_number][4];
							}
							if (x->debug >= 1) post("BAR %d - - - - - - - - - - - - - - - - - - - - - - - - - - - - ", bar_number);
						}
					}
				}
			}
		}
		if (x->debug >= 1) 				{
			post("\nChecking for tuplet errors\n");
		} //// Check for tuplet errors
		for(i=0; i<x->i_index; i++) 	{
			if (x->bar_n[i] != x->bar_n[i-1] && x->b_tup[i] == x->b_tup[i-1] && x->b_tup[i] > 0) post("¡¡¡¡¡¡¡ERROR!!!!!! Tuplet No. %d crosses the bar line between bars %d and %d", x->b_tup[i], x->bar_n[i-1], x->bar_n[i]);
		} //// Print Tuplet Errors
	//	x->debug = 1;
		if (x->debug >= 1) 				{
			post("\nBAR INFORMATION\n");
			post("i\tinit\telems\tnum\tden\tbeatsize\tbarsize");
		} //// Print bar info headers
		if (x->FOLLOW == 0) 				{
			char bar_buf[MAXPDSTRING];
			FILE *fp;

			canvas_makefilename(x->x_canvas, s->s_name, bar_buf, MAXPDSTRING); /// This is a Pd function to get the path relative to the canvas
			sys_bashfilename(bar_buf, bar_buf);
			strcat( bar_buf, "_barinfo.txt");
			t_symbol *masterbar = gensym(bar_buf);
			outlet_symbol(x->x_outlet1, masterbar);
			fp = fopen(bar_buf, "w");
			if(!fp)	{
				pd_error(x, "%s: couldn't create", bar_buf);
				return;
			}
			else {
				for(i=0; i<=bar_number; i++) {
					j = x->bar_info[i+1][0] - x->bar_info[i][0];
					if (i == bar_number) j = x->b_index - x->bar_info[i][0];
					if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t", i, x->bar_info[i][0], j, x->bar_info[i][1], x->bar_info[i][2], x->bar_info[i][3], x->bar_info[i][4]);
					if (x->FOLLOW == 0) fprintf(fp, "%d %d %d %d %d\n", i, x->bar_info[i][1], x->bar_info[i][2], x->bar_info[i][3], x->bar_info[i][4]);
				}
			}
			fclose(fp);
		} //// GENERATE A BAR INFO FILE
		else 							{
			for(i=0; i<=bar_number; i++) {
				j = x->bar_info[i+1][0] - x->bar_info[i][0];
				if (i == bar_number) j = x->b_index - x->bar_info[i][0];
				if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d", i, x->bar_info[i][0], j, x->bar_info[i][1], x->bar_info[i][2], x->bar_info[i][3], x->bar_info[i][4]);
			}
		} //// Print BAR INFOR
	//	x->debug = 0;
	//// _______________________________________________ BEAT SUBDIVISION
		if (x->debug >= 1) 				{
			post(".\nBEAT PROGRAM :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n.");
			post("beatsize=%d\n", beatsize);
			post("i\tbar_n\tbeat_n\tclean_i\traw_i\tdur\ttie\ttuplet");
			post("METER = %d/%d\t beatsize = %d", x->bar_info[x->be_bar_n[0]][1], x->bar_info[x->be_bar_n[0]][2], beatsize);
			post("BAR %d ===============================================", 0);
		}
		beatcount = beat_number = 0;
		beatsize 	= x->bar_info[0][3];
		barsize		= x->bar_info[0][4];
		for(i=0; i<x->b_index; i++) 	{
		///// CHECK METER
			if 		(i > 0	&&	x->bar_n[i] != x->bar_n[i-1]) 	{
				if (x->debug >= 1) post("BAR %d ===============================================", x->bar_n[i]);
				beatcount = 0;
				beat_number = 0;
				if (x->debug >= 1) post("beatsize = %d", beatsize);
				if (x->bar_info[x->bar_n[i]][1] != x->bar_info[x->bar_n[i-1]][1] ||
					x->bar_info[x->bar_n[i]][2] != x->bar_info[x->bar_n[i-1]][2] ) {
					beatsize 	= x->bar_info[x->bar_n[i]][3];
					barsize		= x->bar_info[x->bar_n[i]][4];
					if (x->debug >= 1) post("METER = %d/%d\t beatsize = %d", x->bar_info[x->bar_n[i]][1], x->bar_info[x->bar_n[i]][2], beatsize);
				}
			}
		///// ASSIGN DURATIONS
			/// less than beat?
			if		((beatcount + x->b_dur[i]) <= beatsize) {
				x->be_dur[x->be_index] 		= x->b_dur[i];
				x->be_tie[x->be_index] 		= x->b_tie[i];
				x->be_i[x->be_index] 		= x->b_i[i];   // clean input number (original input index)
				x->be_rii[x->be_index]		= x->b_rii[i]; // raw input number
				x->be_tup[x->be_index] 		= x->b_tup[i]; // tuplet
				x->be_bar_n[x->be_index]	= x->bar_n[i]; // bar number
				beatcount 					+= x->b_dur[i];
				x->be_beat_n[x->be_index]	= beat_number / x->bar_info[x->bar_n[i]][3];
				beat_number					+= x->b_dur[i];
				if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", x->be_index, x->be_bar_n[x->be_index], x->be_beat_n[x->be_index], x->be_i[x->be_index], x->be_rii[x->be_index], x->be_dur[x->be_index], x->be_tie[x->be_index], x->be_tup[x->be_index]);
				if (x->debug >= 3) post("<<<<<<<<< beatcount = %d", beatcount);
				if (beatcount == beatsize) {
					beatcount = 0;
					if (x->debug >= 1) post("-      -      -      -      -      -      -      -      -      -      -      -      -      -");
				}
				x->be_index++;
			}
			else if	(beatcount == 0 && x->b_dur[i]%beatsize == 0)	{
				dur_remainder = x->b_dur[i];
				if (x->debug >= 3) post("durem=%d\tbarsize=%d", dur_remainder, barsize);
				////// EXACTLY EQUAL to A MULTIPLE
				for(j=0; j<32; j++){
					if (dur_remainder == beatsize * j) {
						if (pow2ordot(dur_remainder) == 1) {
							x->be_dur[x->be_index] 		= dur_remainder;
							dur_remainder 				= 0;
							beatcount 					= 0;
							x->be_tie[x->be_index] 		= x->b_tie[i];
							x->be_i[x->be_index] 		= x->b_i[i]; // input number (original input index)
							x->be_rii[x->be_index]		= x->b_rii[i]; // raw input number
							x->be_tup[x->be_index] 		= x->b_tup[i]; // tuplet
							x->be_bar_n[x->be_index]	= x->bar_n[i]; // bar number
							x->be_beat_n[x->be_index]	= beat_number / x->bar_info[x->bar_n[i]][3];
							beat_number					+= x->be_dur[x->be_index];
							if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", x->be_index, x->be_bar_n[x->be_index], x->be_beat_n[x->be_index], x->be_i[x->be_index], x->be_rii[x->be_index], x->be_dur[x->be_index], x->be_tie[x->be_index], x->be_tup[x->be_index]);
							if (x->debug >= 3) post("BEAT:::: EXACT-2orDOT beatcount = %d,\tdur:%d", beatcount, x->be_dur[x->be_index]);
							if (x->debug >= 1) post("-      -      -      -      -      -      -      -      -      -      -      -      -      -");
							x->be_index++;
						} // If it is exactly power or dot
						else {
							beatcount += x->b_dur[i] % beatsize;
							while (dur_remainder > 0) {
								if (dur_remainder >= beatsize) {
									for(j=0; j<18; j++){
										if 	(dur_remainder < pow2dot_array[j])	{
											if (x->debug >= 3) post("%d, temp=%d", j, (int) temp_f);
											break;
										}
									}
									if (x->debug >= 3) post("rem=%d\tj=%d\tdur=%d", dur_remainder, j-1, pow2dot_array[j-1]);
									x->be_dur[x->be_index] 		= pow2dot_array[j-1];
									dur_remainder 				-= x->be_dur[x->be_index];
								}
								else {
									x->be_dur[x->be_index] 		= dur_remainder;
									dur_remainder 				= 0;
								}
								if (dur_remainder == 0) {	x->be_tie[x->be_index] 	= x->b_tie[i];	}
								else 					{	x->be_tie[x->be_index] 	= 1; 			}
								x->be_i[x->be_index] 		= x->b_i[i]; // input number (original input index)
								x->be_rii[x->be_index]		= x->b_rii[i]; // raw input number
								x->be_tup[x->be_index] 		= x->b_tup[i]; // tuplet
								x->be_bar_n[x->be_index]	= x->bar_n[i]; // bar number
								x->be_beat_n[x->be_index]	= beat_number / x->bar_info[x->bar_n[i]][3];
								beat_number					+= x->be_dur[x->be_index];
								if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", x->be_index, x->be_bar_n[x->be_index], x->be_beat_n[x->be_index], x->be_i[x->be_index], x->be_rii[x->be_index], x->be_dur[x->be_index], x->be_tie[x->be_index], x->be_tup[x->be_index]);
								if (x->debug >= 3) post("BEAT:::: ==0 Closest 2ordot beatcount = %d\tdur=%d", beatcount, x->be_dur[x->be_index]);
								if (x->debug >= 1) post("-      -      -      -      -      -      -      -      -      -      -      -      -      -");
								x->be_index++;
							}
						}
						break;
					}
				}
			}
			else if	(beatcount == 0 && x->b_dur[i]%beatsize != 0)	{
				dur_remainder = x->b_dur[i];
				while (dur_remainder > 0) {
					if (dur_remainder >= beatsize) {
						for(j=0; j<18; j++){
							if 	(dur_remainder < pow2dot_array[j])	{
								if (x->debug >= 3) post("%d, temp=%d", j, (int) temp_f);
								break;
							}
						}
						if (x->debug >= 3) post("rem=%d\tj=%d\tdur=%d", dur_remainder, j-1, pow2dot_array[j-1]);
						x->be_dur[x->be_index] 		= pow2dot_array[j-1];
						dur_remainder 				-= x->be_dur[x->be_index];
					}
					else{
						x->be_dur[x->be_index] 		= dur_remainder;
						dur_remainder 				= 0;
					}
					if (dur_remainder == 0) {	x->be_tie[x->be_index] 	= x->b_tie[i];	}
					else 					{	x->be_tie[x->be_index] 	= 1; 			}
					x->be_i[x->be_index] 		= x->b_i[i]; // input number (original input index)
					x->be_rii[x->be_index]		= x->b_rii[i]; // raw input number
					x->be_tup[x->be_index] 		= x->b_tup[i]; // tuplet
					x->be_bar_n[x->be_index]	= x->bar_n[i]; // bar number
					x->be_beat_n[x->be_index]	= beat_number / x->bar_info[x->bar_n[i]][3];
					beat_number					+= x->be_dur[x->be_index];
					if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", x->be_index, x->be_bar_n[x->be_index], x->be_beat_n[x->be_index], x->be_i[x->be_index], x->be_rii[x->be_index], x->be_dur[x->be_index], x->be_tie[x->be_index], x->be_tup[x->be_index]);
					if (x->debug >= 3) post("BEAT:::: !=0 Closest 2ordot beatcount = %d\tdur=%d", beatcount, x->be_dur[x->be_index]);
					beatcount += x->be_dur[x->be_index] % beatsize;
					if (beatcount == 0) if (x->debug >= 1) post("-      -      -      -      -      -      -      -      -      -      -      -      -      -");
					x->be_index++;
				}
			}
			////// NOT ZERO
			else 											{
				x->be_dur[x->be_index] 		= beatsize - beatcount;
				dur_remainder 				= x->b_dur[i] - x->be_dur[x->be_index];
				x->be_tie[x->be_index] 		= 1;
				x->be_i[x->be_index] 		= x->b_i[i];
				x->be_rii[x->be_index]		= x->b_rii[i]; // raw input number
				x->be_tup[x->be_index] 		= x->b_tup[i]; // tuplet
				x->be_bar_n[x->be_index]	= x->bar_n[i]; // bar number
				beatcount 					= 0;
				x->be_beat_n[x->be_index]	= beat_number / x->bar_info[x->bar_n[i]][3];
				beat_number					+= x->be_dur[x->be_index];
				if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", x->be_index, x->be_bar_n[x->be_index], x->be_beat_n[x->be_index], x->be_i[x->be_index], x->be_rii[x->be_index], x->be_dur[x->be_index], x->be_tie[x->be_index], x->be_tup[x->be_index]);
				if (x->debug >= 3) post("BEAT::::not zero beatcount = %d", beatcount);
				if (x->debug >= 1) post("-      -      -      -      -      -      -      -      -      -      -      -      -      -");
				x->be_index++;
				while (dur_remainder > 0) {
					if	(dur_remainder <= beatsize) {
						x->be_dur[x->be_index] 		= dur_remainder;
						x->be_tie[x->be_index] 		= x->b_tie[i];
						x->be_i[x->be_index] 		= x->b_i[i]; // input number (original input index)
						x->be_rii[x->be_index]		= x->b_rii[i]; // raw input number
						x->be_tup[x->be_index] 		= x->b_tup[i]; // tuplet
						x->be_bar_n[x->be_index]	= x->bar_n[i]; // bar number
						beatcount 					+= dur_remainder;
						x->be_beat_n[x->be_index]	= beat_number / x->bar_info[x->bar_n[i]][3];
						beat_number					+= x->be_dur[x->be_index];
						if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", x->be_index, x->be_bar_n[x->be_index], x->be_beat_n[x->be_index], x->be_i[x->be_index], x->be_rii[x->be_index], x->be_dur[x->be_index], x->be_tie[x->be_index], x->be_tup[x->be_index]);
						if (x->debug >= 3) post("BEAT::::ELSE while <= beatcount = %d", beatcount);
						if (beatcount == beatsize) {
							beatcount = 0;
							if (x->debug >= 1) post("-      -      -      -      -      -      -      -      -      -      -      -      -      -");
						}
						dur_remainder = 0;
						x->be_index++;
					}
					else {
						for(j=0; j<32; j++){
							if (dur_remainder < (beatsize * j)) { //&& pow2ordot(beatsize * j) == 1) {
								x->be_dur[x->be_index] 		= beatsize * (j - 1);
								break;
							}
						}
						dur_remainder 				-= x->be_dur[x->be_index];
						x->be_tie[x->be_index] 		= 1;
						x->be_i[x->be_index] 		= x->b_i[i]; // input number (original input index)
						x->be_rii[x->be_index]		= x->b_rii[i]; // raw input number
						x->be_tup[x->be_index] 		= x->b_tup[i]; // tuplet
						x->be_bar_n[x->be_index]	= x->bar_n[i]; // bar number
						x->be_beat_n[x->be_index]	= beat_number / x->bar_info[x->bar_n[i]][3];
						beat_number					+= x->be_dur[x->be_index];
						beatcount 					= 0;
						if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", x->be_index, x->be_bar_n[x->be_index], x->be_beat_n[x->be_index], x->be_i[x->be_index], x->be_rii[x->be_index], x->be_dur[x->be_index], x->be_tie[x->be_index], x->be_tup[x->be_index]);
						if (x->debug >= 3) post("BEAT::::while else beatcount 	= %d", beatcount);
						if (x->debug >= 1) post("-      -      -      -      -      -      -      -      -      -      -      -      -      -");
						x->be_index++;
					}
				}
			}
		}
	//// _______________________________________________ SUB-BEAT SUBDIVISION
		for (j=1; j<3; j++) 			{
			if (x->debug >= 1) post("SUB-BEAT PROGRAM %d :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::", j);
			beatsize = x->bar_info[x->be_bar_n[0]][3];
			if (x->debug >= 1) post("....\nbeatsize=%d\n", beatsize);
			if (x->debug >= 1) post("i\tbar_n\tbeat_n\tclean_i\traw_i\tdur\ttie\ttuplet");
			if (x->debug >= 1) post("METER = %d/%d\t beatsize = %d", x->bar_info[x->be_bar_n[0]][1], x->bar_info[x->be_bar_n[0]][2], beatsize);
			if (x->debug >= 1) post("BAR %d ===============================================", 0);
			x->sb_index = beatcount = 0;
			subdiv = j*2; if (x->debug >= 1) post("j=%d",j);
			sub_beatsize = beatsize / subdiv;
			for(i=0; i<x->be_index; i++){
				if 		(i > 0	&&	x->be_bar_n[i] 		!= x->be_bar_n[i-1]) {
					if (x->debug >= 1) post("BAR %d ============================================ BAR %d", x->be_bar_n[i], x->be_bar_n[i]);
					if (x->debug >= 1) post("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - %d", x->be_beat_n[i]);
					if (x->bar_info[x->be_bar_n[i]][1] != x->bar_info[x->be_bar_n[i-1]][1] ||
						x->bar_info[x->be_bar_n[i]][2] != x->bar_info[x->be_bar_n[i-1]][2] ) {
						beatsize = x->bar_info[x->be_bar_n[i]][3];
						sub_beatsize = beatsize / subdiv;
						if (sub_beatsize < 2) sub_beatsize = 2;
						if (x->debug >= 1) post("METER = %d/%d\t beatsize = %d\t sub_beatsize = %d", x->bar_info[x->be_bar_n[i]][1], x->bar_info[x->be_bar_n[i]][2], beatsize, sub_beatsize);
						beatcount = 0;
					}
					while (beatcount >= sub_beatsize) {
						beatcount -= sub_beatsize;
					//	post("beatcount =\t%d", beatcount);
					}
				}
				else if (i > 0	&&	x->be_beat_n[i] 	!= x->be_beat_n[i-1] ) {
					if (x->debug >= 1) post("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - %d", x->be_beat_n[i]);
					while (beatcount >= sub_beatsize) {
						beatcount -= sub_beatsize;
					}
				}
				if (sub_beatsize < 4) {
					x->sb_dur[x->sb_index] 		=	x->be_dur[i];
					x->sb_tie[x->sb_index] 		= 	x->be_tie[i];
					x->sb_i[x->sb_index] 		= 	x->be_i[i]; // input number (original input index)
					x->sb_rii[x->sb_index]		= 	x->be_rii[i]; // raw input number
					x->sb_tup[x->sb_index] 		= 	x->be_tup[i]; // tuplet
					x->sb_bar_n[x->sb_index]	= 	x->be_bar_n[i]; // bar number
					x->sb_beat_n[x->sb_index]	= 	x->be_beat_n[i];
					if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", x->sb_index, x->sb_bar_n[x->sb_index], x->sb_beat_n[x->sb_index], x->sb_i[x->sb_index], x->sb_rii[x->sb_index], x->sb_dur[x->sb_index], x->sb_tie[x->sb_index], x->sb_tup[x->sb_index]);
					x->sb_index++;
					beatcount += x->be_dur[i];
					if( (((beatcount + x->be_dur[i]) == sub_beatsize) || ((beatcount + x->be_dur[i]) % sub_beatsize == 0)) && (sub_beatsize > 2) ) {
						if (x->debug >= 1) post(".   .    .    .    .    .    .    .    .    .    .    .    .    .    .   .    .    .    .    .    .    .    .    .    .    .    .    .    .%d", sub_beatsize);
					}
					while (beatcount >= sub_beatsize) {
						beatcount -= sub_beatsize;
					}
				}
				else {
					if	( ((beatcount + x->be_dur[i]) <= sub_beatsize)  ) {
						x->sb_dur[x->sb_index] 		=	x->be_dur[i];
						x->sb_tie[x->sb_index] 		= 	x->be_tie[i];
						x->sb_i[x->sb_index] 		= 	x->be_i[i]; // input number (original input index)
						x->sb_rii[x->sb_index]		= 	x->be_rii[i]; // raw input number
						x->sb_tup[x->sb_index] 		= 	x->be_tup[i]; // tuplet
						x->sb_bar_n[x->sb_index]	= 	x->be_bar_n[i]; // bar number
						x->sb_beat_n[x->sb_index]	= 	x->be_beat_n[i];
						if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", x->sb_index, x->sb_bar_n[x->sb_index], x->sb_beat_n[x->sb_index], x->sb_i[x->sb_index], x->sb_rii[x->sb_index], x->sb_dur[x->sb_index], x->sb_tie[x->sb_index], x->sb_tup[x->sb_index]);
						x->sb_index++;
						beatcount += x->be_dur[i];
						if( (((beatcount + x->be_dur[i]) == sub_beatsize) || ((beatcount + x->be_dur[i]) % sub_beatsize == 0)) && (sub_beatsize > 2) ) {
							if (x->debug >= 1) post(".   .    .    .    .    .    .    .    .    .    .    .    .    .    .   .    .    .    .    .    .    .    .    .    .    .    .    .    .%d", sub_beatsize);
						}
						while (beatcount >= sub_beatsize) {
							beatcount -= sub_beatsize;
						}
					} /// less than sub_beatsize
					else if ( (((beatcount % sub_beatsize) == 0) && (((beatcount + x->be_dur[i]) % sub_beatsize) == 0)) 		&& (sub_beatsize > 2) ) {
						x->sb_dur[x->sb_index] 		=	x->be_dur[i];
						x->sb_tie[x->sb_index] 		= 	x->be_tie[i];
						x->sb_i[x->sb_index] 		= 	x->be_i[i]; // input number (original input index)
						x->sb_rii[x->sb_index]		= 	x->be_rii[i]; // raw input number
						x->sb_tup[x->sb_index] 		= 	x->be_tup[i]; // tuplet
						x->sb_bar_n[x->sb_index]	= 	x->be_bar_n[i]; // bar number
						x->sb_beat_n[x->sb_index]	= 	x->be_beat_n[i];
						if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", x->sb_index, x->sb_bar_n[x->sb_index], x->sb_beat_n[x->sb_index], x->sb_i[x->sb_index], x->sb_rii[x->sb_index], x->sb_dur[x->sb_index], x->sb_tie[x->sb_index], x->sb_tup[x->sb_index]);
						x->sb_index++;
						beatcount += x->be_dur[i];
						if (beatcount % sub_beatsize == 0) if (x->debug >= 1) post(".   .    .    .    .    .    .    .    .    .    .    .    .    .    .   .    .    .    .    .    .    .    .    .    .    .    .    .    .%d", sub_beatsize);
						while (beatcount >= sub_beatsize) {
							beatcount -= sub_beatsize;
						//	post("beatcount =\t%d", beatcount);
						}
					} /// for cases like 4 12 or 8 24 in a subbeat of 8 or 16 OR if beatcount = 0 and duration == 48, 64, 16, etc...
					else if ( (((beatcount % (sub_beatsize/2)) == 0) && (((beatcount + x->be_dur[i]) % (sub_beatsize/2)) == 0)) && (sub_beatsize > 2) ) {
						x->sb_dur[x->sb_index] 		=	x->be_dur[i];
						x->sb_tie[x->sb_index] 		= 	x->be_tie[i];
						x->sb_i[x->sb_index] 		= 	x->be_i[i]; // input number (original input index)
						x->sb_rii[x->sb_index]		= 	x->be_rii[i]; // raw input number
						x->sb_tup[x->sb_index] 		= 	x->be_tup[i]; // tuplet
						x->sb_bar_n[x->sb_index]	= 	x->be_bar_n[i]; // bar number
						x->sb_beat_n[x->sb_index]	= 	x->be_beat_n[i];
						if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", x->sb_index, x->sb_bar_n[x->sb_index], x->sb_beat_n[x->sb_index], x->sb_i[x->sb_index], x->sb_rii[x->sb_index], x->sb_dur[x->sb_index], x->sb_tie[x->sb_index], x->sb_tup[x->sb_index]);

						x->sb_index++;
						beatcount += x->be_dur[i];
						if (beatcount % sub_beatsize == 0) 	if (x->debug >= 1) post(".   .    .    .    .    .    .    .    .    .    .    .    .    .    .   .    .    .    .    .    .    .    .    .    .    .    .    .    .%d", sub_beatsize);
						while (beatcount >= sub_beatsize) {
							beatcount -= sub_beatsize;
						//	post("beatcount =\t%d", beatcount);
						}
					} /// for cases like 4 12 or 8 24 in a subbeat of 8 or 16 OR if beatcount = 0 and duration == 48, 64, 16, etc...
					else {
						if (sub_beatsize > 2) {
							x->sb_dur[x->sb_index] 		= sub_beatsize - beatcount;
							dur_remainder				= x->be_dur[i] - x->sb_dur[x->sb_index];
							x->sb_tie[x->sb_index] 		= 1;
							x->sb_i[x->sb_index] 		= x->be_i[i]; // input number (original input index)
							x->sb_rii[x->sb_index]		= 	x->be_rii[i]; // raw input number
							x->sb_tup[x->sb_index] 		= 	x->be_tup[i]; // tuplet
							x->sb_bar_n[x->sb_index]	= x->be_bar_n[i]; // bar number
							x->sb_beat_n[x->sb_index]	= x->be_beat_n[i];
							if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", x->sb_index, x->sb_bar_n[x->sb_index], x->sb_beat_n[x->sb_index], x->sb_i[x->sb_index], x->sb_rii[x->sb_index], x->sb_dur[x->sb_index], x->sb_tie[x->sb_index], x->sb_tup[x->sb_index]);
							if ((beatcount + x->sb_dur[x->sb_index]) % sub_beatsize == 0) if (x->debug >= 1)  post(".   .    .    .    .    .    .    .    .    .    .    .    .    .    .   .    .    .    .    .    .    .    .    .    .    .    .    .    .%d", sub_beatsize);
							x->sb_index++;

							x->sb_dur[x->sb_index] 		= dur_remainder;
							x->sb_tie[x->sb_index] 		= x->be_tie[i];
							x->sb_i[x->sb_index] 		= x->be_i[i]; // input number (original input index)
							x->sb_rii[x->sb_index]		= 	x->be_rii[i]; // raw input number
							x->sb_tup[x->sb_index] 		= 	x->be_tup[i]; // tuplet
							x->sb_bar_n[x->sb_index]	= x->be_bar_n[i]; // bar number
							x->sb_beat_n[x->sb_index]	= x->be_beat_n[i];
							if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", x->sb_index, x->sb_bar_n[x->sb_index], x->sb_beat_n[x->sb_index], x->sb_i[x->sb_index], x->sb_rii[x->sb_index], x->sb_dur[x->sb_index], x->sb_tie[x->sb_index], x->sb_tup[x->sb_index]);
							x->sb_index++;

							beatcount 					+= x->be_dur[i];
							if (beatcount % sub_beatsize == 0) 	if (x->debug >= 1) post(".   .    .    .    .    .    .    .    .    .    .    .    .    .    .   .    .    .    .    .    .    .    .    .    .    .    .    .    .%d", sub_beatsize);
							while (beatcount >= sub_beatsize) {
								beatcount -= sub_beatsize;
							//	post("beatcount =\t%d", beatcount);
							}
						}
					}
				}
			}
			for( i=0; i<x->sb_index; i++ ){
				x->be_dur[i] 	= x->sb_dur[i];
				x->be_tie[i] 	= x->sb_tie[i];
				x->be_i[i]		= x->sb_i[i]; // input number (original input index)
				x->be_rii[i]	= x->sb_rii[i]; // raw input number
				x->be_tup[i] 	= x->sb_tup[i]; // tuplet
				x->be_bar_n[i]	= x->sb_bar_n[i]; // bar number
				x->be_beat_n[i]	= x->sb_beat_n[i];
				x->be_index		= x->sb_index;
			}
		}
		post("notes: ... Rhythmic computation done");
	//// ____________________________________   produce a single final list
		if (x->debug >= 1) post("\n......... beginning final list!!!!! ");
		ii = 0;
		x->sb_index = 0;
		if (x->debug >= 1) post("i\tbar_n\tbeat_n\tclean_i\traw_i\tdur\ttie\ttuplet");
		for(i=0; i<x->be_index; i++)	{
		//	post("i=%d", i);
			if (x->be_bar_n[i] != x->be_bar_n[i-1]) if (x->debug >= 1) post("_______________________________________________________________________________________");
			if (x->be_beat_n[i] != x->be_beat_n[i-1]) if (x->debug >= 1) post("-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -");
			if (x->be_tup[i] >= 0) {
				while( x->sb_tp_num[ii] == x->be_tup[i] && ii<x->sb_tp_index) {
		//			post("ii=%d", ii);
					x->sb_dur[x->sb_index]		= x->sb_tp_dur[ii];
					x->sb_tie[x->sb_index]		= x->sb_tp_tie[ii];
					x->sb_i[x->sb_index]		= x->sb_tp_i[ii];
					x->sb_rii[x->sb_index]		= x->sb_tp_ri[ii];
					x->sb_tup[x->sb_index]		= x->sb_tp_num[ii];
					x->sb_bar_n[x->sb_index]	= x->be_bar_n[i];
					x->sb_beat_n[x->sb_index]	= x->be_beat_n[i];
					if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\ttuplet_loop", x->sb_index, x->sb_bar_n[x->sb_index], x->sb_beat_n[x->sb_index], x->sb_i[x->sb_index], x->sb_rii[x->sb_index], x->sb_dur[x->sb_index], x->sb_tie[x->sb_index], x->sb_tup[x->sb_index]);
					x->sb_index++;
					ii++;
				}
			}
			else {
				x->sb_dur[x->sb_index] 		= x->be_dur[i];
				x->sb_tie[x->sb_index] 		= x->be_tie[i];
				x->sb_i[x->sb_index]		= x->be_i[i]; // input number (original input index)
				x->sb_rii[x->sb_index]		= x->be_rii[i]; // raw input number
				x->sb_tup[x->sb_index] 		= x->be_tup[i]; // tuplet
				x->sb_bar_n[x->sb_index]	= x->be_bar_n[i]; // bar number
				x->sb_beat_n[x->sb_index]	= x->be_beat_n[i];
				if (x->debug >= 1) post("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\tregular_loop", x->sb_index, x->sb_bar_n[x->sb_index], x->sb_beat_n[x->sb_index], x->sb_i[x->sb_index], x->sb_rii[x->sb_index], x->sb_dur[x->sb_index], x->sb_tie[x->sb_index], x->sb_tup[x->sb_index]);
				x->sb_index++;
			}
		}
		post("notes: ... Formatting Score... ");
	//// _______________________________________________ ENGRAVING Programs
		char o_pitch[10], o_jump[15], o_text[64];
		int o_dur, t, f, tp;
		char buf[MAXPDSTRING], partname[MAXPDSTRING], scorename[MAXPDSTRING], linename[MAXPDSTRING];
		int m, tempint, span_switch, gliss_switch, clu_switch, gliss_break_switch;
		int jj = t= m = tempint = tp = span_switch = gliss_switch = clu_switch = gliss_break_switch = 0;
		f = 1;


		FILE *fp1, *fp2;
	//// _______________________________________________ OPEN FILE
		canvas_makefilename(x->x_canvas, s->s_name, buf, MAXPDSTRING); /// This is a Pd function to get the path relative to the canvas
		sys_bashfilename(buf, buf);
		strcpy( scorename, buf);
		strcat( scorename, ".ly");
		fp1 = fopen(scorename, "w");
		if(!fp1)						{
			pd_error(x, "%s: couldn't create", buf);
			return;
		}
	//// _______________________________________________ WRITE SCORE
		else 							{
			post("notes: writing into %s", scorename);
			fprintf(fp1, "%% [notes] external for Pure Data\n%% development-version August 16, 2018 \n%% by Jaime E. Oliver La Rosa\n%% la.rosa@nyu.edu\n%% @ the Waverly Labs in NYU MUSIC FAS\n%% Open this file with Lilypond\n%% more information is available at lilypond.org\n%% Released under the GNU General Public License.\n\n");
			fprintf(fp1, "%% HEADERS\n\nglissandoSkipOn = {\n\t\\override NoteColumn.glissando-skip = ##t\n\t\\hide NoteHead\n\t\\hide Accidental\n\t\\hide Tie\n\t\\override NoteHead.no-ledgers = ##t\n}\n\nglissandoSkipOff = {\n\t\\revert NoteColumn.glissando-skip\n\t\\undo \\hide NoteHead\n\t\\undo \\hide Tie\n\t\\undo \\hide Accidental\n\t\\revert NoteHead.no-ledgers\n}\n");

			if (x->auth_n > 0 || x->titl_n > 0 || x->sub_title_n > 0) {
				fprintf(fp1, "\n\\header {");
				if (x->auth_n 		> 0) {
					fprintf(fp1, "\n\tcomposer = \"");
					for(i=0; i<x->auth_n; i++){
						fprintf(fp1, "%1.32s ", x->author[i]);
					}
					fprintf(fp1, "\"");
				}
				if (x->titl_n 		> 0) {
					fprintf(fp1, "\n\ttitle = \"");
					for(i=0; i<x->titl_n; i++){
						fprintf(fp1, "%1.32s ", x->title[i]);
					}
					fprintf(fp1, "\"");
				}
				if (x->sub_title_n 	> 0) {
					fprintf(fp1, "\n\tsubtitle = \"");
					for(i=0; i<x->sub_title_n; i++){
						fprintf(fp1, "%1.32s ", x->sub_title[i]);
					}
					fprintf(fp1, "\"");
				}
				fprintf(fp1, "\n}\n\n");
			} //	HEADER Title, subtitle, and Author
		//// ___________________________________________________ OPEN PART FILE
			strcpy( partname, buf);
			strcat( partname, "_part.ly");
			fp2 = fopen(partname, "w");
			if(!fp2)						{
				pd_error(x, "%s: couldn't create", buf);
				return;
			}
			else {
				strcpy(linename, x->inst);
				strcat(linename, "_part = ");
				fprintf(fp2, "%s", linename);
				for (i=0; i<x->sb_index; i++)	{
					j = x->sb_rii[i];
				//	post("%d, pittttt=%f", j, x->ri_pit[j][0]);
					if (x->ri_pit[j][0] > 0) {
				//		post("found first pitch");
						temp_f = x->ri_pit[j][0];
						find_relative((int) temp_f, (FILE *) fp2);
						x->lastpit = (int) temp_f;
						break;
					}
				} 				// find relative
				fprintf(fp2, "\\time %i/%i\n\n", x->bar_info[0][1], x->bar_info[0][2]); // METER
				if(x->tempo == 1) 				{
					for(k=0; k<64; k++){
						t = (int) exp2( (float) k );
						if 		( x->ri_tmp[0][0] == t ) {
						k=t;
						t=0;
						k = x->refdur / k;
						fprintf(fp2, "\\tempo %i = %i\n\n", k, x->ri_tmp[0][1]);
						break;
					}
						else if ( x->ri_tmp[0][0] == t / 2 * 3) {
						k=t;
						t=1;
						k = x->refdur / k;
						fprintf(fp2, "\\tempo %i. = %i\n\n", k, x->ri_tmp[0][1]);
						break;
					}
					}
				} 								// TEMPO
				find_clef((int) x->ri_clef[0], (FILE *) fp2);		//	CLEF
//// __________________________________________//// __________________________________________|
//// ________________________ WRITE SOME NOTES //// __________________________________________|
//// __________________________________________//// __________________________________________V
				fprintf(fp2, "\n%% ________________________________________bar 1 :\n");
				for (i=0; i<x->sb_index; i++)	{
					jj=j+1;
					j = x->sb_rii[i];
			///////////////////////////// SEPARATION
				// close tupletttt: ________________________________________________________
					if (i>0 &&((x->sb_tup[i] > x->sb_tup[i-1] && x->sb_tup[i-1] > -1) || (x->sb_tup[i]==-1 && x->sb_tup[i-1] > -1))	) {
						fprintf(fp2, "} ");
						tp = 0;
					}
				// GRACES NOTES
					if (i>0 && j!=jj && x->ri_index_sort[jj]==3 && x->sb_tie[i-1] != 1) {
					//	if (x->ri_index_sort[0]==3) jj=0;
					//	post("GRACEEEEEEEEEE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
						tempint=j;
						find_grace((int) x->ri_grc[jj][0], (FILE *) fp2);
					//	post("j=%d\tjj=%d", j, jj);
						for (j = jj; j < tempint; j++) {
							if (x->ri_index_sort[j]!=3) {
								post("breaking grace");
								j=jj+1;
								break;
							}
						//	post("grace loop=%d\t x->ri_index_sort[j] == %d", j, x->ri_index_sort[j]);
						// text Spans_____________________________________________________
								if (x->ri_txt_spn[j][0] == 1 && x->ri_txt_spn_n[j] > 0) {
									if (i==0 || j != x->sb_rii[i-1]) {
										fprintf(fp2, "\n\t\\once \\override TextSpanner.bound-details.left.text = #\"" );
										for (k=0; k<x->ri_txt_spn[j][1]; k++){
											strcpy( o_text, x->ri_txt[j][k]);
											fprintf(fp2, "%1.32s ", o_text);
										}
										fprintf(fp2, "\" ");
									}
								}
								if (x->ri_txt_spn[j][2] == 1 && x->ri_txt_spn_n[j] > 0) {
									if (i==0 || j != x->sb_rii[i-1]) {
										fprintf(fp2, "\n\t\\once \\override TextSpanner.bound-details.right.text = #\" " );
										for (k=x->ri_txt_spn[j][1]; k<x->ri_txt_spn[j][3]; k++){
											strcpy( o_text, x->ri_txt[j][k]);
											fprintf(fp2, "%1.32s ", o_text);
										}
										fprintf(fp2, "\" ");
									}
								}
								if (x->ri_txt_spn[j][0] == 1 && x->ri_txt_spn_n[j] > 0) {
									if (i==0 || j != x->sb_rii[i-1]) {
										if 		(x->ri_txt_spn[j][4] == 4)fprintf(fp2, "\n\t\\once \\override TextSpanner.style = #'line ");
										else if (x->ri_txt_spn[j][4] == 2 || x->ri_txt_spn[j][4] == 5) {
											if (x->ri_txt_spn[j][4] == 2) fprintf(fp2, "\n\t\\once \\override TextSpanner.style = #'dashed-line ");
											if (x->ri_txt_spn[j][4] == 5) fprintf(fp2, "\n\t\\once \\override TextSpanner.style = #'line ");
											fprintf(fp2, "\n\t\\once \\override TextSpanner.bound-details.right.padding = #-2 ");
											fprintf(fp2, "\n\t\\once \\override TextSpanner.bound-details.right.stencil-align-dir-y = #UP ");
											fprintf(fp2, "\n\t\\once \\override TextSpanner.bound-details.right.text = \\markup { \\draw-line #'(0 . -1) \" ");
											for (k=x->ri_txt_spn[j][1]; k<x->ri_txt_spn[j][3]; k++){
												strcpy( o_text, x->ri_txt[j][k]);
												fprintf(fp2, "%1.32s ", o_text);
											}
											fprintf(fp2, "\"} ");
										}
										else if (x->ri_txt_spn[j][4] == 3 || x->ri_txt_spn[j][4] == 6) {
											fprintf(fp2, "\n\t\\once \\override TextSpanner.bound-details.right.arrow = ##t ");
											if (x->ri_txt_spn[j][4] == 3) fprintf(fp2, "\n\t\\once \\override TextSpanner.style = #'dashed-line ");
											if (x->ri_txt_spn[j][4] == 6) fprintf(fp2, "\n\t\\once \\override TextSpanner.style = #'line ");
										}
										else fprintf(fp2, "\n\t\\once \\override TextSpanner.style = #'dashed-line ");
										fprintf(fp2, "\n");
									}
								}
						// chord run ________________________________________________________
							if (x->ri_cho[j]>1 || x->ri_hrm_n[j]>0) fprintf(fp2, "<");
							for (k=0; k<x->ri_cho[j]; k++) {
								// note heads
								if (x->ri_nhs_n[j]>0)
								find_notehead((int) x->ri_nhs[j][0], (FILE *) fp2);
								// pitch
								find_pitch(x->ri_pit[j][k], x->ri_acc[j], o_pitch);
								fprintf(fp2, "%1.8s", o_pitch);
								// jumps
								if (i>0) { // interval jumps
									if (k==0) {
										if (find_jump((int) x->ri_pit[j][k], (int) x->lastpit, (int) x->ri_acc[j], o_jump)==1)
										fprintf(fp2, "%1.8s", o_jump);
									}
									else	{
										if (find_jump((int) x->ri_pit[j][k], (int) x->lastpit_ch, (int) x->ri_acc[j], o_jump)==1)
										fprintf(fp2, "%1.8s", o_jump);
									}
								}
								else {
									if (k==0) {
										if (find_jump((int) x->ri_pit[j][k], (int) x->lastpit, (int) x->ri_acc[j], o_jump)==1)
										fprintf(fp2, "%1.8s", o_jump);
									}
									else	{
										if (find_jump((int) x->ri_pit[j][k], (int) x->lastpit_ch, (int) x->ri_acc[j], o_jump)==1)
										fprintf(fp2, "%1.8s", o_jump);
									}
								}
								// stopped harmonics
								m=0;
								if (x->ri_hrm_n[j]>0) {
									m = (int) x->ri_hrm[j][k] - 1;
									temp_f = (float) harmonics[m][0];
									temp_f += x->ri_pit[j][k];
									fprintf(fp2, " ");
									find_pitch(temp_f, x->ri_acc[j], o_pitch);
									fprintf(fp2, "%1.8s", o_pitch);
									if (find_jump((int) temp_f, (int) x->ri_pit[j][k], (int) x->ri_acc[j], o_jump)==1)
										fprintf(fp2, "%1.8s", o_jump);
									fprintf(fp2, "\\harmonic ");

								/*	temp_f2 = (float) harmonics[m][1];
									temp_f2 += x->ri_pit[j][k];
									fprintf(fp2, " \\parenthesize ");
									find_pitch(temp_f2, x->ri_acc[j], o_pitch);
									fprintf(fp2, "%1.8s", o_pitch);
									if (find_jump((int) temp_f2, (int) temp_f, (int) x->ri_acc[j], o_jump)==1)
										fprintf(fp2, "%1.8s", o_jump);*/
								}
								if (x->ri_cho[j]>1) fprintf(fp2, " ");
								if (x->ri_pit[j][0] > 0)	x->lastpit 		= x->ri_pit[j][0];
								if (x->ri_pit[j][k] > 0)	x->lastpit_ch 	= x->ri_pit[j][k];
							}
							if (x->ri_cho[j]>1 || x->ri_hrm_n[j]>0) {
								if (x->ri_art_n[j] > 0 && j != x->sb_rii[i-1]) {
									for (k=0; k<x->ri_art_n[j]; k++){
										if (x->ri_art[j][k]==25)find_articulation((int) x->ri_art[j][k], (FILE *) fp2);
									}
								}
								else if (i == 0 && x->ri_art_n[j] > 0) {
									for (k=0; k<x->ri_art_n[j]; k++){
										if (x->ri_art[j][k]==25)find_articulation((int) x->ri_art[j][k], (FILE *) fp2);
									}
								}
								fprintf(fp2, ">");
							}
						// GRACE duration _________________________________________
							o_dur = x->ri_grc[j][1];
							fprintf(fp2, "%i", o_dur);
						// tie ________________________________________________________
							if (x->sb_tie[i] == 1) fprintf(fp2, "~");
						// smallnumbers ________________________________________________________
							if (x->ri_smn_n[j] > 0 && j != x->sb_rii[i-1]) {
								for (k=0; k<x->ri_smn_n[j]; k++){
									find_small_numbers((int) x->ri_smn[j][k], (FILE *) fp2);
								}
							}
							else if (i == 0 && x->ri_smn_n[j] > 0) {
								for (k=0; k<x->ri_smn_n[j]; k++){
									find_small_numbers((int) x->ri_smn[j][k], (FILE *) fp2);
								}
							}
						// articulation ________________________________________________________
							if (x->ri_art_n[j] > 0 && j != x->sb_rii[i-1]) {
								for (k=0; k<x->ri_art_n[j]; k++){
		//							post("JK:\tj=%d\tk=%d", j, k);
									find_articulation((int) x->ri_art[j][k], (FILE *) fp2); //if (x->ri_art[j][k]!=24 || (x->ri_cho[j]>1 && x->ri_art[j][k]!=25))
								}
							}
						// dynamics ________________________________________________________
							if (x->ri_dyn_n[j] > 0 && j != x->sb_rii[i-1]) for (k=0; k<x->ri_dyn_n[j]; k++) find_dynamics((int) x->ri_dyn[j][k], (FILE *) fp2);
							else if (i == 0 && x->ri_dyn_n[j] > 0) {
								for (k=0; k<x->ri_dyn_n[j]; k++){
									find_dynamics((int) x->ri_dyn[j][k], (FILE *) fp2);
								}
							}
                        // harp-pedal ________________________________________________________
							if (x->ri_hpp_n[j] > 0 && j != x->sb_rii[i-1]) {
								fprintf(fp2, "_\\markup { \\combine \\arrow-head #Y #UP ##t \\draw-line #'(0 . -2)}_\\markup { \\harp-pedal ");
                                strcpy( o_text, x->ri_hpp[j]);
								fprintf(fp2, "%s", o_text);
                                fprintf(fp2, " }");
                            }
                        // texts ________________________________________________________
							if (x->ri_txt_n[j] > 0 && j != x->sb_rii[i-1]) {
								fprintf(fp2, "-\\markup {");
								for (k=0; k<x->ri_txt_n[j]; k++){
									strcpy( o_text, x->ri_txt[j][k]);
									fprintf(fp2, "%1.32s ", o_text);
								}
								fprintf(fp2, "}");
							}
							else if (i == 0 && x->ri_txt_n[j] > 0) {
								fprintf(fp2, "_\\markup {");
								for (k=0; k<x->ri_txt_n[j]; k++){
									strcpy( o_text, x->ri_txt[j][k]);
									fprintf(fp2, "%1.32s ", o_text);
								}
								fprintf(fp2, "}");
							}

						// text Spans_____________________________________________________
							if 		(x->ri_txt_spn[j][0] == 1 && x->ri_txt_spn_n[j] > 0) {
								if (i==0 || j != x->sb_rii[i-1]) {
									if (span_switch == 0) {
										fprintf(fp2, "\\startTextSpan" );
										span_switch = 1;
									}
								}
							}
							else if (x->ri_txt_spn[j][0] == 2 && x->ri_txt_spn_n[j] > 0) {
								if (i==0 || j != x->sb_rii[i-1]) {
									if (span_switch == 1) {
										fprintf(fp2, "\\stopTextSpan" );
										span_switch = 0;
									}
								}
							}

						// spans ________________________________________________________
							if (x->ri_spa_n[j] > 0 && j != x->sb_rii[i-1]) {
								for (k=0; k<x->ri_spa_n[j]; k++){
									//post("BANG");
									find_span((int) x->ri_spa[j][k], (FILE *) fp2);
								}
							}
							else if (i == 0 && x->ri_spa_n[j] > 0) {
								for (k=0; k<x->ri_spa_n[j]; k++){
									//post("BONG");
									find_span((int) x->ri_spa[j][k], (FILE *) fp2);
								}
							}
							fprintf(fp2, " ");
						}
						fprintf(fp2, "} ");
						fprintf(fp2, " ");
					//	post("close grace");
						//j+=1;
						j=tempint;
					}
				// BAR BREAK ________________________________________________________
					if (i>0 && x->sb_bar_n[i] != x->sb_bar_n[i-1]) {
					//	if(f==2) fprintf(fp2, "]");
						fprintf(fp2, " |\n%% ________________________________________bar %i :\n", x->sb_bar_n[i]+1);
						f = 1;
					// write meter
						if (	(i>0) && (x->bar_info[x->sb_bar_n[i]][1] != x->bar_info[x->sb_bar_n[i-1]][1] || x->bar_info[x->sb_bar_n[i]][2] != x->bar_info[x->sb_bar_n[i-1]][2] )	)  {
							fprintf(fp2, "\\time %i/%i\n\n", x->bar_info[x->sb_bar_n[i]][1], x->bar_info[x->sb_bar_n[i]][2]);
						}
					}
				// BEAT Tab ________________________________________________________
					else if (i>0 && x->sb_beat_n[i] != x->sb_beat_n[i-1]) {
					//	if(f==2) fprintf(fp2, "]");
						fprintf(fp2, "\n");
						for (k=0; k<x->sb_beat_n[i]; k++) {
							fprintf(fp2, "\t");
						}
						f = 1;
					}
				// SPACE ________________________________________________________
					else {
						fprintf(fp2, " ");
					}
				// write tempo
					if(x->tempo == 1) {
						if (	(x->ri_tmp[j][0] != x->ri_tmp[j-1][0] || x->ri_tmp[j][1] != x->ri_tmp[j-1][1]) && j != x->sb_rii[i-1] )	{
							for(k=0; k<64; k++){
								t = (int) exp2( (float) k );
								if 		( x->ri_tmp[j][0] == t ) {
									k=t;
									t=0;
									k = x->refdur / k;
									fprintf(fp2, " \\tempo %i = %i ", k, x->ri_tmp[j][1]);
									break;
								}
								else if ( x->ri_tmp[j][0] == t / 2 * 3) {
									k=t;
									t=1;
									k = x->refdur / k;
									fprintf(fp2, " \\tempo %i. = %i ", k, x->ri_tmp[j][1]);
									break;
								}
							}
						}
					}
			//////////////////////////// NOTE EXPRESSION
				// Clef
					if (i>0 && x->ri_clef[j] != x->ri_clef[j-1]) {
						find_clef((int) x->ri_clef[j], (FILE *) fp2);
					}
				// Pitched Trill
					if (x->ri_spa_p[j] > 0 && ( i==0 || j != x->sb_rii[i-1] ))
						fprintf(fp2, "\\pitchedTrill ");
				// text Spans_____________________________________________________
					if (x->ri_txt_spn[j][0] == 1 && x->ri_txt_spn_n[j] > 0) {
						if (i==0 || j != x->sb_rii[i-1]) {
							fprintf(fp2, "\n\t\\once \\override TextSpanner.bound-details.left.text = #\"" );
							for (k=0; k<x->ri_txt_spn[j][1]; k++){
								strcpy( o_text, x->ri_txt[j][k]);
								fprintf(fp2, "%1.32s ", o_text);
							}
							fprintf(fp2, "\" ");
						}
					}
					if (x->ri_txt_spn[j][2] == 1 && x->ri_txt_spn_n[j] > 0) {
						if (i==0 || j != x->sb_rii[i-1]) {
							fprintf(fp2, "\n\t\\once \\override TextSpanner.bound-details.right.text = #\" " );
							for (k=x->ri_txt_spn[j][1]; k<x->ri_txt_spn[j][3]; k++){
								strcpy( o_text, x->ri_txt[j][k]);
								fprintf(fp2, "%1.32s ", o_text);
							}
							fprintf(fp2, "\" ");
						}
					}
					if (x->ri_txt_spn[j][0] == 1 && x->ri_txt_spn_n[j] > 0) {
						if (i==0 || j != x->sb_rii[i-1]) {
							if 		(x->ri_txt_spn[j][4] == 4)fprintf(fp2, "\n\t\\once \\override TextSpanner.style = #'line ");
							else if (x->ri_txt_spn[j][4] == 2 || x->ri_txt_spn[j][4] == 5) {
								if (x->ri_txt_spn[j][4] == 2) fprintf(fp2, "\n\t\\once \\override TextSpanner.style = #'dashed-line ");
								if (x->ri_txt_spn[j][4] == 5) fprintf(fp2, "\n\t\\once \\override TextSpanner.style = #'line ");
								fprintf(fp2, "\n\t\\once \\override TextSpanner.bound-details.right.padding = #-2 ");
								fprintf(fp2, "\n\t\\once \\override TextSpanner.bound-details.right.stencil-align-dir-y = #UP ");
								fprintf(fp2, "\n\t\\once \\override TextSpanner.bound-details.right.text = \\markup { \\draw-line #'(0 . -1) \" ");
								for (k=x->ri_txt_spn[j][1]; k<x->ri_txt_spn[j][3]; k++){
									strcpy( o_text, x->ri_txt[j][k]);
									fprintf(fp2, "%1.32s ", o_text);
								}
								fprintf(fp2, "\"} ");
							}
							else if (x->ri_txt_spn[j][4] == 3 || x->ri_txt_spn[j][4] == 6) {
								fprintf(fp2, "\n\t\\once \\override TextSpanner.bound-details.right.arrow = ##t ");
								if (x->ri_txt_spn[j][4] == 3) fprintf(fp2, "\n\t\\once \\override TextSpanner.style = #'dashed-line ");
								if (x->ri_txt_spn[j][4] == 6) fprintf(fp2, "\n\t\\once \\override TextSpanner.style = #'line ");
							}
							else fprintf(fp2, "\n\t\\once \\override TextSpanner.style = #'dashed-line ");
							fprintf(fp2, "\n");
						}
					}
				// tuplet start ________________________________________________________
					if (x->sb_tup[i] > -1 && x->sb_tup[i] != x->sb_tup[i-1] ) {
						fprintf(fp2, " \\tuplet %i/%i { ", x->tp_info[x->sb_tup[i]][1], x->tp_info[x->sb_tup[i]][2]);
						tp = 1;
					}
			/////// PITCH ________________________________________________________
				// note heads
					if (x->ri_nhs_n[j]>0)
					find_notehead((int) x->ri_nhs[j][0], (FILE *) fp2);
				// Chord? ________________________________________________________
					//cluster
					if (x->ri_clu[j]==1 && clu_switch == 0) {
						fprintf(fp2, "\\makeClusters {");
						clu_switch = 1;
					}
					else if (x->ri_clu[j]==0 && clu_switch == 1) {
						fprintf(fp2, "}");
						clu_switch = 0;
					}
					//arpeggio
					if (x->ri_cho[j]>1 && x->ri_arp[j]>0) {
						if (i==0 || j != x->sb_rii[i-1]) {
							find_arpeggio((int) x->ri_arp[j], (FILE *) fp2);
						}
					}
				// actual chord
					if (x->ri_cho[j]>1 || x->ri_hrm_n[j]>0) fprintf(fp2, "<");
				//pitch, jumps, harmonics
					for (k=0; k<x->ri_cho[j]; k++) {
					// pitch
						find_pitch(x->ri_pit[j][k], x->ri_acc[j], o_pitch);
						fprintf(fp2, "%1.8s", o_pitch);
					// jumps
						if (i>0) { // interval jumps
							if (k==0) {
								if (find_jump((int) x->ri_pit[j][k], (int) x->lastpit, (int) x->ri_acc[j], o_jump)==1)
								fprintf(fp2, "%1.8s", o_jump);
							}
							else	{
								if (find_jump((int) x->ri_pit[j][k], (int) x->lastpit_ch, (int) x->ri_acc[j], o_jump)==1)
								fprintf(fp2, "%1.8s", o_jump);
							}
						}
						else {
							if (k==0) {
								if (find_jump((int) x->ri_pit[j][k], (int) x->lastpit, (int) x->ri_acc[j], o_jump)==1)
								fprintf(fp2, "%1.8s", o_jump);
							}
							else	{
								if (find_jump((int) x->ri_pit[j][k], (int) x->lastpit_ch, (int) x->ri_acc[j], o_jump)==1)
								fprintf(fp2, "%1.8s", o_jump);
							}
						}
					// harmonics
						if (x->ri_hrm_n[j]>0) {
							m = (int) x->ri_hrm[j][k] - 1;
							temp_f = (float) harmonics[m][0];
							temp_f += x->ri_pit[j][k];
							fprintf(fp2, " ");
							find_pitch(temp_f, x->ri_acc[j], o_pitch);
							fprintf(fp2, "%1.8s", o_pitch);
							if (find_jump((int) temp_f, (int) x->ri_pit[j][k], (int) x->ri_acc[j], o_jump)==1)
								fprintf(fp2, "%1.8s", o_jump);
							fprintf(fp2, "\\harmonic ");

					/*		temp_f2 = (float) harmonics[m][1];
							temp_f2 += x->ri_pit[j][k];
							fprintf(fp2, " \\parenthesize ");
							find_pitch(temp_f2, x->ri_acc[j], o_pitch);
							fprintf(fp2, "%1.8s", o_pitch);
							if (find_jump((int) temp_f2, (int) temp_f, (int) x->ri_acc[j], o_jump)==1)
								fprintf(fp2, "%1.8s", o_jump); */
						}
					//prepare for next loop cycle
						if (x->ri_cho[j]>1 || x->ri_hrm_n[j]>0) fprintf(fp2, " ");
						if (x->ri_pit[j][0] > 0)	x->lastpit 		= x->ri_pit[j][0];
						if (x->ri_pit[j][k] > 0)	x->lastpit_ch 	= x->ri_pit[j][k];
					}
				// close chord
					if (x->ri_cho[j]>1|| x->ri_hrm_n[j]>0) {
						if (x->ri_art_n[j] > 0) {
							if (i==0 || j != x->sb_rii[i-1]) {
								for (k=0; k<x->ri_art_n[j]; k++){
									if (x->ri_art[j][k]==25)find_articulation((int) x->ri_art[j][k], (FILE *) fp2);
								}
							}
						}
						fprintf(fp2, ">");
					}
			/////// DURATION ________________________________________________________
					for(k=0; k<64; k++){
						t = (int) exp2( (float) k );
						if 		( x->sb_dur[i] == t ) {
							k=t;
							t=0;
							break;
						}
						else if ( x->sb_dur[i] == t / 2 * 3) {
							k=t;
							t=1;
							break;
						}
					}
					o_dur = x->refdur / k;
		/*		// If Glissing, break quarter notes or longer into 8th notes
					gliss_break_switch = 0;
					if (i==0 || j != x->sb_rii[i-1]) {
						for (k=0; k<x->ri_spa_n[j]; k++){
							if (	x->ri_spa[j][k] == 8 ||
									(gliss_switch == 1 && j != x->sb_rii[i+1])
								){
								gliss_break_switch = 1;
							}
						}
					}
					if (gliss_switch != 0 && gliss_break_switch == 0) {
	//					post("------------------------ o_dur = %d", o_dur);
						if (o_dur == 4){
							o_dur = 8;
							fprintf(fp2, "%i", o_dur);
							fprintf(fp2, " %1.8s", o_pitch);
							if( t == 1) {
								fprintf(fp2, " %1.8s", o_pitch);
							}
						}
						else if (o_dur == 2) {
							o_dur = 8;
							fprintf(fp2, "%i", o_dur);
							for (k=0; k<3; k++) {
								fprintf(fp2, " %1.8s", o_pitch);
							}
							if( t == 1) {
								for (k=0; k<2; k++) {
									fprintf(fp2, " %1.8s", o_pitch);
								}
							}
						}
						else if (o_dur == 1) {
							o_dur = 8;
							fprintf(fp2, "%i", o_dur);
							for (k=0; k<7; k++) {
								fprintf(fp2, " %1.8s", o_pitch);
							}
							if( t == 1) {
								for (k=0; k<4; k++) {
									fprintf(fp2, " %1.8s", o_pitch);
								}
							}
						}
					}
					else {
						fprintf(fp2, "%i", o_dur);
				// dot ________________________________________________________
					if (t==1) fprintf(fp2, ".");
					}*/
					fprintf(fp2, "%i", o_dur);
				// dot ________________________________________________________
					if (t==1) fprintf(fp2, "."); //replace till here when enabling gliss breaking
				// tremolo ________________________________________________________
					if (x->ri_trm[j] > 0) fprintf(fp2, ":%i", x->ri_trm[j]);
				// tie ________________________________________________________
					if 	((x->ri_pit[j][0] > 0) &&
						(x->sb_tie[i] == 1  ) ) {
						tempint = 1;
						if (x->ri_spa_n[j] > 0) {
							for (k=0; k<x->ri_spa_n[j]; k++){
								if (x->ri_spa[j][k] == 0 || x->ri_spa[j][k] == 7) {
									tempint = 0;
								}
							}
						} // && (x->ri_pit[i][0] == x->ri_pit[i+1][0])
						if (tempint == 1 )	fprintf(fp2, "~");
					}
				// arpeggio
					if ((x->ri_cho[j]>1 || x->ri_hrm_n[j]>0) && x->ri_arp[j]>0) {
						if (i==0 || j != x->sb_rii[i-1]) {
							fprintf(fp2, "\\arpeggio");
						}
					}
				// Close group at BAR and BEAT BREAK _________________________________________
					if ( (i>0 && x->sb_bar_n[i] != x->sb_bar_n[i+1]) || (i>0 && x->sb_beat_n[i] != x->sb_beat_n[i+1]) ) {
					//	if(f==2) fprintf(fp2, "]");
					}
			/////// ARTICULATION, DYNAMICS, PHRASING, MARKUPS, ETC.
				// smallnumbers ________________________________________________________
					if (x->ri_smn_n[j] > 0) {
						if (i==0 || j != x->sb_rii[i-1]) {
							for (k=0; k<x->ri_smn_n[j]; k++){
								find_small_numbers((int) x->ri_smn[j][k], (FILE *) fp2);
							}
						}
					}
				// articulation ________________________________________________________
					if (x->ri_art_n[j] > 0) {
						if (i==0 || j != x->sb_rii[i-1]) {
							for (k=0; k<x->ri_art_n[j]; k++){
								find_articulation((int) x->ri_art[j][k], (FILE *) fp2); //if (x->ri_art[j][k]!=24 || (x->ri_cho[j]>1 && x->ri_art[j][k]!=25))
							}
						}
					}
				// dynamics ________________________________________________________
					if (x->ri_dyn_n[j] > 0) {
						if (i==0 || j != x->sb_rii[i-1]) {
							for (k=0; k<x->ri_dyn_n[j]; k++){
								find_dynamics((int) x->ri_dyn[j][k], (FILE *) fp2);
							}
						}
					}
                // harp-pedal ________________________________________________________
                    if (x->ri_hpp_n[j] > 0 && j != x->sb_rii[i-1]) {
                        fprintf(fp2, "_\\markup { \\combine \\arrow-head #Y #UP ##t \\draw-line #'(0 . -2)}_\\markup { \\harp-pedal ");
                        strcpy( o_text, x->ri_hpp[j]);
                        fprintf(fp2, "%s", o_text);
                        fprintf(fp2, " }");
                    }
				// texts ________________________________________________________
					if (x->ri_txt_n[j] > 0 && x->ri_txt_spn[j][0] == 0) {
						if (i==0 || j != x->sb_rii[i-1]) {
							fprintf(fp2, "^\\markup {");
							for (k=0; k<x->ri_txt_n[j]; k++){
								strcpy( o_text, x->ri_txt[j][k]);
								fprintf(fp2, "%1.32s ", o_text);
							}
							fprintf(fp2, "}");
						}
					}
				// text Spans_____________________________________________________
					if 		(x->ri_txt_spn[j][0] == 1 && x->ri_txt_spn_n[j] > 0) {
						if (i==0 || j != x->sb_rii[i-1]) {
							if (span_switch == 0) {
								fprintf(fp2, "\\startTextSpan" );
								span_switch = 1;
							}
						}
					}
					else if (x->ri_txt_spn[j][0] == 2 && x->ri_txt_spn_n[j] > 0) {
						if (i==0 || j != x->sb_rii[i-1]) {
							if (span_switch == 1) {
								fprintf(fp2, "\\stopTextSpan" );
								span_switch = 0;
							}
						}
					}
				// beat grouping ________________________________________________________
					if (f == 1 && tp != 1) {
						if ( x->sb_beat_n[i] == x->sb_beat_n[i+1] && x->sb_bar_n[i] == x->sb_bar_n[i+1] ) {
						//	fprintf(fp2, "[");
							f = 2;
						}
						else f = 0;
					}
				// spans ________________________________________________________
					if (x->ri_spa_n[j] > 0) {
						if (i==0 || j != x->sb_rii[i-1]) {
							for (k=0; k<x->ri_spa_n[j]; k++){
								if (x->ri_spa[j][k] == 0 && j == x->sb_rii[i+1]) {
									x->ri_spa[j][k] = 7;
									gliss_switch = 1;
								}
								find_span((int) x->ri_spa[j][k], (FILE *) fp2);
								if (x->ri_spa[j][k] == 8) gliss_switch = 0;
							}
							if (x->ri_spa_p[j] > 0) {
								// pitch
									find_pitch(x->ri_spa_p[j], x->ri_acc[j], o_pitch);
									fprintf(fp2, " %1.8s", o_pitch);
								// jumps
									if (find_jump((int) x->ri_spa_p[j], (int) x->lastpit, (int) x->ri_acc[j], o_jump)==1)
										fprintf(fp2, "%1.8s ", o_jump);
							}
						}
					}
					if (gliss_switch == 1 && j != x->sb_rii[i+1]) {
						gliss_switch = 8;
						find_span((int) gliss_switch, (FILE *) fp2);
						gliss_switch = 0;
					}
					if (gliss_switch == 1 && ( i==0 || j != x->sb_rii[i-1] )) {
						fprintf(fp2, "\\glissandoSkipOn ");
					}
					else {
						for (k=0; k<x->ri_spa_n[j]; k++){
							if (x->ri_spa[j][k] == 7 && ( i==0 || j != x->sb_rii[i-1] )) {
								fprintf(fp2, "\\glissandoSkipOn ");
								gliss_switch = 2;
							}
						}
					}
					fprintf(fp2, " ");
				}
				if(tp == 1) fprintf(fp2, "}");
			//	if(f  == 2) fprintf(fp2, "]");
				fprintf(fp2, "\n}\n");
				fclose( fp2);
			//// _______________________________________ COPY PART TO MAIN SCORE
				fp2 = fopen(partname, "r");
				char a;
				a = fgetc(fp2);
				if (a != EOF) fputc(a,  fp1);
				while(a != EOF)	{
					a = fgetc(fp2);
					if (a != EOF) fputc(a,  fp1);
				}
				fclose(fp2);
			//// __________________________________________ SCORE EXPRESSION
				strcpy(linename, x->inst);
				strcat(linename, "_part");
				fprintf(fp1, "\n\\score {\n\t\\new Staff ");
				if (x->inst_n == 1) fprintf(fp1, "\\with { instrumentName = \"%s\" } ", x->inst);
				fprintf(fp1, "{\n\t\t\\new Voice {\n\t\t\t\\%s\n\t\t}\n\t}\n\t\\layout {", linename);
				fprintf(fp1, "\n\t\t\\mergeDifferentlyHeadedOn");
				fprintf(fp1, "\n\t\t\\mergeDifferentlyDottedOn");
				fprintf(fp1, "\n\t\t\\set harmonicDots = ##t");
				fprintf(fp1, "\n\t\t\\override Glissando.thickness = #4");
				fprintf(fp1, "\n\t\t\\set Staff.pedalSustainStyle = #'mixed");
				fprintf(fp1, "\n\t\t\\override TextSpanner.bound-padding = #1.0");
			    fprintf(fp1, "\n\t\t\\override TextSpanner.bound-details.right.padding = #1.3");
			  	fprintf(fp1, "\n\t\t\\override TextSpanner.bound-details.right.stencil-align-dir-y = #CENTER");
			  	fprintf(fp1, "\n\t\t\\override TextSpanner.bound-details.left.stencil-align-dir-y = #CENTER");
			  	fprintf(fp1, "\n\t\t\\override TextSpanner.bound-details.right-broken.text = ##f");
				fprintf(fp1, "\n\t\t\\override TextSpanner.bound-details.left-broken.text = ##f");
				fprintf(fp1, "\n\t\t\\override Glissando.minimum-length = #4");
				fprintf(fp1, "\n\t\t\\override Glissando.springs-and-rods = #ly:spanner::set-spacing-rods");
				fprintf(fp1, "\n\t\t\\override Glissando.breakable = ##t");
				fprintf(fp1, "\n\t\t\\override Glissando.after-line-breaking = ##t");
				fprintf(fp1, "\n\t\t\\set baseMoment = #(ly:make-moment 1/8)");
				fprintf(fp1, "\n\t\t\\set beatStructure = #'(2 2 2 2)");
				fprintf(fp1, "\n\t\t#(set-default-paper-size \"a%i", x->papersize);
				if(x->paperorientation==1) fprintf(fp1, "landscape\")");
				else fprintf(fp1, "\")");
				fprintf(fp1, "\n\t}\n\t\\midi { }\n}");
			//// ____________________________________________________________ CLOSE SCORE
				fprintf(fp1, "\n\n\\version \"2.18.2\"\n%% notes Pd External testing version  \n");
				fclose(fp1);
				post("notes: .ly score finished");

				t_atom paths[MAXPDSTRING];
				SETSYMBOL(&paths[0], gensym(x->inst));
				SETSYMBOL(&paths[1], gensym(partname));
   				outlet_list(x->x_outlet0, 0, 2, paths);
			}

    }
    // compile and open
    if(compile_and_open(buf,scorename,x->debug,x->FOLLOW,x->render,x->open, x->lily_dir)){
      pd_error(x, "notes: error compiling score");
    }
	} // if a file is correctly provided.
	else 									{
		post("notes: ERROR: Can't flush because no input has been provided... you have to enter some notes!");
	} //exit(1);
	outlet_bang(x->x_outlet2);
}
////	____________________________________________________ CLEAR
void notes_clear(t_notes *x)											{
	x->auth_n = x->titl_n = x->sb_tp_index = x->i_index = x->ri_index = x->tp_index = x->tp_n = x->b_index = x->be_index = x->sb_index = 0;
	x->refdur = 32;
 //   x->debug = 0;
    x->tempo = 0;
    x->auth_n = x->titl_n = x->sub_title_n = 0;
    x->ri_mtr[x->ri_index][0] = x->ri_mtr[x->ri_index][1] = 4;
	post("notes: Cleared");
}
////	____________________________________________________ PRINT
void notes_print(t_notes *x)											{
	post("notes: x->sb_tp_index = %d\nx->i_index = %d\nx->ri_index = %d\nx->tp_index = %d\nx->tp_n = %d\nx->b_index = %d\nx->be_index = %d\nx->sb_index = %d\n", x->sb_tp_index, x->i_index, x->ri_index, x->tp_index, x->tp_n, x->b_index, x->be_index, x->sb_index);
}
////	____________________________________________________ REFERENCE DURATION
void notes_refdur(t_notes *x, t_floatarg f) 							{
	x->refdur = f;
	post("notes: Reference duration set to a 1/%i note", x->refdur);
}
////	____________________________________________________ RENDERING SWITCH
void notes_render(t_notes *x, t_floatarg f) 							{
	int i;
	if (f == 0) {
		i = 0;
		post("notes: score rendering off");
	}
	else {
		i = 1;
		post("notes: score rendering on");
	}
	x->render = i;
}
////	____________________________________________________ OPENING SWITCH
void notes_open(t_notes *x, t_floatarg f) 							{
	int i;
	if (f == 0) {
		i = 0;
		post("notes: score opening off");
	}
	else {
		i = 1;
		post("notes: score opening on");
	}
	x->open = i;
}
////	____________________________________________________ DEBUG
void notes_debug(t_notes *x, t_floatarg f) 								{
	x->debug = (int) f;
	post("debugging level = %d", x->debug);
}
////	____________________________________________________ TITLE
void notes_title(t_notes *x, t_symbol *s, int argc, t_atom *argv) 		{
	x->dummysym = s->s_name;
	int i;
	for(i=0;i<argc;i++){
		atom_string(argv+i, x->title[i], 1000);
	//	post(x->title[i]);
	}
	x->titl_n = argc;
}
////	____________________________________________________ SUB_TITLE
void notes_sub_title(t_notes *x, t_symbol *s, int argc, t_atom *argv) 	{
	x->dummysym = s->s_name;
	int i;
	for(i=0;i<argc;i++){
		atom_string(argv+i, x->sub_title[i], 1000);
	//	post(x->sub_title[i]);
	}
	x->sub_title_n = argc;
}
////	____________________________________________________ AUTHOR
void notes_author(t_notes *x, t_symbol *s, int argc, t_atom *argv) 		{
	x->dummysym = s->s_name;
	int i;
	for(i=0;i<argc;i++){
		atom_string(argv+i, x->author[i], 1000);
	//	post(x->author[i]);
	}
	x->auth_n = argc;
}
////	____________________________________________________ AUTHOR
void notes_inst(t_notes *x, t_symbol *s) 		{
	strcpy (x->inst, s->s_name);
	post("notes: instrument name = %s", x->inst);
	x->inst_n = 1;
}
////	____________________________________________________ Lilypond Location
void notes_lily_dir(t_notes *x, t_symbol *s, int argc, t_atom *argv) 	{
	int i; i = argc; i++;
	x->dummysym = s->s_name;
	atom_string(argv, x->lily_dir, MAXPDSTRING);
	post("notes: Lilypond directory set to: %s", x->lily_dir);
}
////	____________________________________________________ READFILE
void notes_readfile(t_notes *x, t_symbol *s)							{
	char filename[100];
	strcpy( filename, s->s_name);
	strcpy( x->barfile, filename);
	post("notes: Master Bar File RECEIVED at %s", x->barfile);
}
////	____________________________________________________ PAPER SIZE
void notes_paper(t_notes *x, t_floatarg f, t_floatarg g) 								{
	x->papersize 		= (int) f;
	x->paperorientation = (int) g;
}

t_class *notes_class;
void *notes_new(t_floatarg ff)												{
    t_notes *x = (t_notes *)pd_new(notes_class);
	inlet_new(&x->x_ob, &x->x_ob.ob_pd, gensym("symbol"), gensym("readfile"));
  	x->x_outlet0 = outlet_new(&x->x_ob, &s_symbol);
  	x->x_outlet1 = outlet_new(&x->x_ob, &s_symbol);
  	x->x_outlet2 = outlet_new(&x->x_ob, &s_symbol);
  	x->x_outlet3 = outlet_new(&x->x_ob, gensym("float"));
    x->x_canvas = canvas_getcurrent();
    x->FOLLOW 			= (int) ff;
    x->sb_tp_index = x->i_index = x->ri_index = x->tp_index = x->tp_n = x->b_index = x->be_index = 0;
    x->debug = 0;
    x->inst_n = x->tempo = x->auth_n = x->titl_n = 0;
    x->refdur 			= 32;
    x->render 			= 1;
    x->open         = 1;
    x->papersize 		= 4;
	x->paperorientation = 0;
	strcpy(x->lily_dir, LYDIR); // see notes_lib.h
    strcpy(x->inst, "inst");
    return (void *)x;
}
void notes_setup(void)														{
    notes_class = class_new(gensym("notes"), (t_newmethod)notes_new, 0, sizeof(t_notes), 0, A_DEFFLOAT, 0);
  
	class_addmethod(notes_class, (t_method)notes_input, 	gensym("input"), 	A_GIMME, 	0);
	class_addmethod(notes_class, (t_method)notes_write, 	gensym("write"), 	A_SYMBOL,	0);
	class_addmethod(notes_class, (t_method)notes_title, 	gensym("title"), 	A_GIMME, 	0);
	class_addmethod(notes_class, (t_method)notes_sub_title, gensym("sub_title"),A_GIMME, 	0);
	class_addmethod(notes_class, (t_method)notes_author, 	gensym("author"), 	A_GIMME, 	0);
	class_addmethod(notes_class, (t_method)notes_inst, 		gensym("inst"), 	A_SYMBOL, 	0);
	class_addmethod(notes_class, (t_method)notes_lily_dir, 	gensym("lily_dir"), A_GIMME,	0);
	class_addmethod(notes_class, (t_method)notes_clear, 	gensym("clear"), 				0);
	class_addmethod(notes_class, (t_method)notes_readfile, 	gensym("readfile"),	A_SYMBOL, 	0);
	class_addmethod(notes_class, (t_method)notes_print, 	gensym("print"), 				0);
	class_addmethod(notes_class, (t_method)notes_refdur, 	gensym("refdur"), 	A_DEFFLOAT, 0);
	class_addmethod(notes_class, (t_method)notes_render, 	gensym("render"), 	A_DEFFLOAT, 0);
	class_addmethod(notes_class, (t_method)notes_debug, 	gensym("debug"), 	A_DEFFLOAT, 0);
	class_addmethod(notes_class, (t_method)notes_paper, 	gensym("paper"), 	A_DEFFLOAT, A_DEFFLOAT, 0);
	class_addmethod(notes_class, (t_method)notes_open, 	gensym("open"), 	A_DEFFLOAT, 0);
}
