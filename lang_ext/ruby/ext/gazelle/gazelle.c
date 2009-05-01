#ifndef GAZELLE_RUBY_PARSE
#define GAZELLE_RUBY_PARSE

#include <ruby.h>
#include <gazelle/dynarray.h>
#include "bc_read_stream.c"
#include "load_grammar.c"
#include "parse.c"

struct gzlparse_state {
  DEFINE_DYNARRAY(first_child, bool);
};

static int terminal_error = 0;

void error_char_callback() {
  // do something intelligent here
}

void error_terminal_callback() {
  terminal_error = 1;
}

VALUE rb_gazelle_parse_p(VALUE self, VALUE input) {
  VALUE compiled_file_stream = rb_iv_get(self, "@filename");
  char *filename     = RSTRING(compiled_file_stream)->ptr;
  char *input_string = RSTRING(input)->ptr;
  
  struct bc_read_stream *s = bc_rs_open_file(filename);

  // TODO: Spec ME
  // if (!s) {
  //   printf("Couldn't open bitcode file '%s'!\n\n", filename);
  //   return Qfalse;
  // }
  // 
  struct gzl_grammar *g = gzl_load_grammar(s);
  bc_rs_close_stream(s);
  
  struct gzl_parse_state *state = gzl_alloc_parse_state();
  struct gzl_bound_grammar bg = {
    .grammar           = g,
    .error_char_cb     = error_char_callback,
    .error_terminal_cb = error_terminal_callback
  };
  
  gzl_init_parse_state(state, &bg);
  
  gzl_parse(state, input_string, strlen(input_string) + 1);
  gzl_finish_parse(state);
  
  if (terminal_error) {
    return Qfalse;
  } else {
    return Qtrue;
  }
}

void Init_gazelle() {
  VALUE Gazelle         = rb_const_get(rb_cObject, rb_intern("Gazelle"));
  VALUE Gazelle_Parser  = rb_const_get_at(Gazelle, rb_intern("Parser"));

  rb_define_method(Gazelle_Parser, "parse?", rb_gazelle_parse_p, 1);
}

#endif /* GAZELLE_RUBY_PARSE */