// Filename: glmisc_src.h
// Created by:  drose (09Feb04)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) Carnegie Mellon University.  All rights reserved.
//
// All use of this software is subject to the terms of the revised BSD
// license.  You should have received a copy of this license along
// with this source code in a file named "LICENSE."
//
////////////////////////////////////////////////////////////////////

#include "pandabase.h"
#include "configVariableBool.h"
#include "configVariableInt.h"
#include "configVariableEnum.h"
#include "geomEnums.h"

// Define some macros to transparently map to the double or float
// versions of the OpenGL function names.
#ifndef GLf

#ifndef STDFLOAT_DOUBLE
#define GLf(name) name ## f
#define GLfv(name) name ## fv
#define GLfc(name) name ## fc
#define GLfr(name) name ## fr
#define GLf_str "f"
#else  // STDFLOAT_DOUBLE
#define GLf(name) name ## d
#define GLfv(name) name ## dv
#define GLfc(name) name ## dc
#define GLfr(name) name ## dr
#define GLf_str "d"
#endif  // STDFLOAT_DOUBLE

#endif  // GLf

//#define GSG_VERBOSE 1

extern ConfigVariableBool gl_cheap_textures;
extern ConfigVariableBool gl_ignore_clamp;
extern ConfigVariableBool gl_support_clamp_to_border;
extern ConfigVariableBool gl_ignore_filters;
extern ConfigVariableBool gl_ignore_mipmaps;
extern ConfigVariableBool gl_force_mipmaps;
extern ConfigVariableBool gl_show_texture_usage;
extern ConfigVariableInt gl_show_texture_usage_max_size;
extern ConfigVariableBool gl_color_mask;
extern ConfigVariableBool gl_support_occlusion_query;
extern ConfigVariableBool gl_compile_and_execute;
extern ConfigVariableBool gl_interleaved_arrays;
extern ConfigVariableBool gl_parallel_arrays;
extern ConfigVariableInt gl_max_errors;
extern ConfigVariableEnum<GeomEnums::UsageHint> gl_min_buffer_usage_hint;
extern ConfigVariableBool gl_debug_buffers;
extern ConfigVariableBool gl_finish;
extern ConfigVariableBool gl_force_depth_stencil;
extern ConfigVariableBool gl_matrix_palette;
extern ConfigVariableBool gl_force_no_error;
extern ConfigVariableBool gl_force_no_flush;
extern ConfigVariableBool gl_separate_specular_color;

extern EXPCL_GL void CLP(init_classes)();


#if !defined(WIN32) && defined(GSG_VERBOSE)
ostream &output_gl_enum(ostream &out, GLenum v);
INLINE ostream &operator << (ostream &out, GLenum v) {
  return output_gl_enum(out, v);
}
#endif


#ifdef DO_PSTATS
#define DO_PSTATS_STUFF(XX) XX;
#else
#define DO_PSTATS_STUFF(XX)
#endif

#define ISPOW2(X) (((X) & ((X)-1))==0)

#define report_my_gl_errors() \
  report_my_errors(__LINE__, __FILE__)

#define clear_my_gl_errors() \
  clear_my_errors(__LINE__, __FILE__)
