#pragma once

/// USER_SECTION_START 1

/// USER_SECTION_END

// Debugging
#ifdef NDEBUG
#define RW_CONSOLE(msg)
#define RW_CONSOLE_FUNCTION(msg)
#else
#include <iostream>

#define RW_DEBUG
#define RW_CONSOLE_STREAM std::cout

#define RW_CONSOLE(msg) RW_CONSOLE_STREAM << msg;
#define RW_CONSOLE_FUNCTION(msg) RW_CONSOLE_STREAM << __PRETTY_FUNCTION__ << " " << msg;
#endif

/// USER_SECTION_START 2

/// USER_SECTION_END

#ifdef RW_PROFILING
#include "easy/profiler.h"
#include <easy/arbitrary_value.h> // EASY_VALUE, EASY_ARRAY are defined here

#define RW_PROFILING_BLOCK_C(text, color) EASY_BLOCK(text, color)
#define RW_PROFILING_NONSCOPED_BLOCK_C(text, color) EASY_NONSCOPED_BLOCK(text, color)
#define RW_PROFILING_END_BLOCK EASY_END_BLOCK
#define RW_PROFILING_FUNCTION_C(color) EASY_FUNCTION(color)
#define RW_PROFILING_BLOCK(text, colorStage) RW_PROFILING_BLOCK_C(text,profiler::colors::  colorStage)
#define RW_PROFILING_NONSCOPED_BLOCK(text, colorStage) RW_PROFILING_NONSCOPED_BLOCK_C(text,profiler::colors::  colorStage)
#define RW_PROFILING_FUNCTION(colorStage) RW_PROFILING_FUNCTION_C(profiler::colors:: colorStage)
#define RW_PROFILING_THREAD(name) EASY_THREAD(name)

#define RW_PROFILING_VALUE(name, value) EASY_VALUE(name, value)
#define RW_PROFILING_TEXT(name, value) EASY_TEXT(name, value)

#else
#define RW_PROFILING_BLOCK_C(text, color)
#define RW_PROFILING_NONSCOPED_BLOCK_C(text, color)
#define RW_PROFILING_END_BLOCK
#define RW_PROFILING_FUNCTION_C(color)
#define RW_PROFILING_BLOCK(text, colorStage)
#define RW_PROFILING_NONSCOPED_BLOCK(text, colorStage)
#define RW_PROFILING_FUNCTION(colorStage)
#define RW_PROFILING_THREAD(name)

#define RW_PROFILING_VALUE(name, value)
#define RW_PROFILING_TEXT(name, value)
#endif

// Special expantion tecniques are required to combine the color name
#define CONCAT_SYMBOLS_IMPL(x, y) x##y
#define CONCAT_SYMBOLS(x, y) CONCAT_SYMBOLS_IMPL(x, y)



// Different color stages
#define RW_COLOR_STAGE_1 50
#define RW_COLOR_STAGE_2 100
#define RW_COLOR_STAGE_3 200
#define RW_COLOR_STAGE_4 300
#define RW_COLOR_STAGE_5 400
#define RW_COLOR_STAGE_6 500
#define RW_COLOR_STAGE_7 600
#define RW_COLOR_STAGE_8 700
#define RW_COLOR_STAGE_9 800
#define RW_COLOR_STAGE_10 900
#define RW_COLOR_STAGE_11 A100 
#define RW_COLOR_STAGE_12 A200 
#define RW_COLOR_STAGE_13 A400 
#define RW_COLOR_STAGE_14 A700 


// General
#define RW_GENERAL_PROFILING_COLORBASE Cyan
#define RW_GENERAL_PROFILING_BLOCK_C(text, color) RW_PROFILING_BLOCK_C(text, color)
#define RW_GENERAL_PROFILING_NONSCOPED_BLOCK_C(text, color) RW_PROFILING_NONSCOPED_BLOCK_C(text, color)
#define RW_GENERAL_PROFILING_END_BLOCK RW_PROFILING_END_BLOCK;
#define RW_GENERAL_PROFILING_FUNCTION_C(color) RW_PROFILING_FUNCTION_C(color)
#define RW_GENERAL_PROFILING_BLOCK(text, colorStage) RW_PROFILING_BLOCK(text, CONCAT_SYMBOLS(RW_GENERAL_PROFILING_COLORBASE, colorStage))
#define RW_GENERAL_PROFILING_NONSCOPED_BLOCK(text, colorStage) RW_PROFILING_NONSCOPED_BLOCK(text, CONCAT_SYMBOLS(RW_GENERAL_PROFILING_COLORBASE, colorStage))
#define RW_GENERAL_PROFILING_FUNCTION(colorStage) RW_PROFILING_FUNCTION(CONCAT_SYMBOLS(RW_GENERAL_PROFILING_COLORBASE, colorStage))
#define RW_GENERAL_PROFILING_VALUE(name, value) RW_PROFILING_VALUE(name, value)
#define RW_GENERAL_PROFILING_TEXT(name, value) RW_PROFILING_TEXT(name, value)


/// USER_SECTION_START 3

/// USER_SECTION_END
