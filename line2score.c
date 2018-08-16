/* code for the "line2score" pd class.  This adds a creation argument, of
type "float".  */

#include "m_pd.h"
#define MXS 128
 
typedef struct line2score
{
  t_object x_ob;
  t_outlet *x_outlet;
  t_outlet *x_outlet2, *x_outlet3;
  float pit[MXS], o_pit[MXS], last_pit, o_grc[MXS];
  int dur[MXS], gli[MXS], o_dur[MXS], o_tie[MXS], o_gli[MXS], o_bounds[MXS], index;
  char *dummysym;
  
} t_line2score;

void line2score_input(t_line2score *x, t_symbol *s, int argcount, t_atom *argvec) {
	int i;
	x->dummysym = s->s_name;
	for(i=0;i<argcount;i++){
		if		(i==0) x->pit[x->index] = argvec[i].a_w.w_float;
		else if	(i==1) x->dur[x->index] = argvec[i].a_w.w_float;
		else if	(i==2) x->gli[x->index] = argvec[i].a_w.w_float;
	}
	x->index++;
}

void line2score_output(t_line2score *x)
{
   	int i;
   	t_atom at[4], ax[4];
   	
   	SETFLOAT(&ax[0], 1);
	outlet_list(x->x_outlet3, 0, 1, ax);
   	
   	for (i=0;i<x->index;i++){
   		x->o_grc[i] = x->o_tie[i] = 0; x->o_gli[i] = 0;
   		if(x->last_pit == 0 && i==0) x->last_pit = x->pit[i];
   		x->o_dur[i] = x->dur[i];
   		x->o_pit[i] = x->pit[i];
   		if(x->gli[i] > 0) {
   			x->o_gli[i] = 1;
   			x->o_pit[i] = x->last_pit;
   			x->o_grc[i] = x->pit[i];
		}
		x->last_pit = x->pit[i];
		
   	}
   	for (i=0;i<x->index;i++){
   		if(i+1 == x->index) SETFLOAT(&ax[0], 0);
   		if(i<(x->index-1) && x->o_grc[i] == x->o_pit[i+1]) x->o_grc[i] = 0;
		if(i<(x->index-1) && x->o_pit[i] == x->o_pit[i+1]) x->o_tie[i] = 1;
		SETFLOAT(&at[0], x->o_pit[i]);
		SETFLOAT(&at[1], x->o_dur[i]);
		SETFLOAT(&at[2], x->o_tie[i]);
		SETFLOAT(&at[3], x->o_gli[i]);
		if(i+1 == x->index) outlet_list(x->x_outlet3, 0, 1, ax);
		outlet_list(x->x_outlet, 0, 4, at);
		
		if (x->o_grc[i] > 0) {
			SETFLOAT(&at[0], x->o_grc[i]);
			if(i+1 == x->index) outlet_list(x->x_outlet3, 0, 1, ax);
			outlet_list(x->x_outlet2, 0, 1, at);
		}
	}
   	x->index = 0;
}

void line2score_ft1(t_line2score *x, t_floatarg g)
{
    x->last_pit = g;
}

void line2score_clear(t_line2score *x) {
	int i;
	for (i=0; i<x->index; i++) {
		x->pit[i] = x->last_pit = 0; 
		x->gli[i] = x->dur[i] = 0;	
		x->o_grc[i] = x->o_pit[i] = x->last_pit = 0; 
		x->o_gli[i] = x->o_dur[i] = 0;	
	}
	x->index = 0;
}

t_class *line2score_class;


void *line2score_new()
{
    t_line2score *x = (t_line2score *)pd_new(line2score_class);
    inlet_new(&x->x_ob, &x->x_ob.ob_pd, gensym("float"), gensym("ft1"));
    x->x_outlet 	= outlet_new(&x->x_ob, gensym("list"));
    x->x_outlet2 	= outlet_new(&x->x_ob, gensym("list"));
    x->x_outlet3 	= outlet_new(&x->x_ob, gensym("float"));
    x->index = 0;
    return (void *)x;
}

void line2score_setup(void)
{
    line2score_class = class_new(gensym("line2score"), (t_newmethod)line2score_new,
    	0, sizeof(t_line2score), 0, A_DEFFLOAT, 0);
	class_addmethod(line2score_class, (t_method)line2score_input, 	gensym("input"), 	A_GIMME, 0);
	class_addmethod(line2score_class, (t_method)line2score_output, 	gensym("output"), 			 0);
	class_addmethod(line2score_class, (t_method)line2score_clear, 	gensym("clear"), 			 0);
	class_addmethod(line2score_class, (t_method)line2score_ft1, 	gensym("ft1"),		A_FLOAT, 0);
}

