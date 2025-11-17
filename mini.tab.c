/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "mini.y"

/*
 * 语法分析器（Bison）
 * 定义 Mini 语言的语法、语义值联合体与结合/优先级，
 * 在各产生式动作中构造 TAC 中间代码。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"

int yylex();
void yyerror(char* msg);


#line 87 "mini.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "mini.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_CHAR = 4,                       /* CHAR  */
  YYSYMBOL_STRUCT = 5,                     /* STRUCT  */
  YYSYMBOL_DOT = 6,                        /* DOT  */
  YYSYMBOL_EQ = 7,                         /* EQ  */
  YYSYMBOL_NE = 8,                         /* NE  */
  YYSYMBOL_LT = 9,                         /* LT  */
  YYSYMBOL_LE = 10,                        /* LE  */
  YYSYMBOL_GT = 11,                        /* GT  */
  YYSYMBOL_GE = 12,                        /* GE  */
  YYSYMBOL_UMINUS = 13,                    /* UMINUS  */
  YYSYMBOL_UADDR = 14,                     /* UADDR  */
  YYSYMBOL_UDEREF = 15,                    /* UDEREF  */
  YYSYMBOL_IF = 16,                        /* IF  */
  YYSYMBOL_ELSE = 17,                      /* ELSE  */
  YYSYMBOL_WHILE = 18,                     /* WHILE  */
  YYSYMBOL_FUNC = 19,                      /* FUNC  */
  YYSYMBOL_INPUT = 20,                     /* INPUT  */
  YYSYMBOL_OUTPUT = 21,                    /* OUTPUT  */
  YYSYMBOL_RETURN = 22,                    /* RETURN  */
  YYSYMBOL_SWITCH = 23,                    /* SWITCH  */
  YYSYMBOL_CASE = 24,                      /* CASE  */
  YYSYMBOL_DEFAULT = 25,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 26,                     /* BREAK  */
  YYSYMBOL_INTEGER = 27,                   /* INTEGER  */
  YYSYMBOL_IDENTIFIER = 28,                /* IDENTIFIER  */
  YYSYMBOL_TEXT = 29,                      /* TEXT  */
  YYSYMBOL_CHARACTER = 30,                 /* CHARACTER  */
  YYSYMBOL_31_ = 31,                       /* '+'  */
  YYSYMBOL_32_ = 32,                       /* '-'  */
  YYSYMBOL_33_ = 33,                       /* '*'  */
  YYSYMBOL_34_ = 34,                       /* '/'  */
  YYSYMBOL_35_ = 35,                       /* '['  */
  YYSYMBOL_36_ = 36,                       /* '('  */
  YYSYMBOL_37_ = 37,                       /* '{'  */
  YYSYMBOL_38_ = 38,                       /* '}'  */
  YYSYMBOL_39_ = 39,                       /* ';'  */
  YYSYMBOL_40_ = 40,                       /* ','  */
  YYSYMBOL_41_ = 41,                       /* ']'  */
  YYSYMBOL_42_ = 42,                       /* ')'  */
  YYSYMBOL_43_ = 43,                       /* '='  */
  YYSYMBOL_44_ = 44,                       /* '&'  */
  YYSYMBOL_45_ = 45,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_program = 47,                   /* program  */
  YYSYMBOL_function_declaration_list = 48, /* function_declaration_list  */
  YYSYMBOL_function_declaration = 49,      /* function_declaration  */
  YYSYMBOL_struct_definition = 50,         /* struct_definition  */
  YYSYMBOL_field_list = 51,                /* field_list  */
  YYSYMBOL_field_declarators = 52,         /* field_declarators  */
  YYSYMBOL_declaration = 53,               /* declaration  */
  YYSYMBOL_54_1 = 54,                      /* $@1  */
  YYSYMBOL_55_2 = 55,                      /* $@2  */
  YYSYMBOL_56_3 = 56,                      /* $@3  */
  YYSYMBOL_struct_var_list = 57,           /* struct_var_list  */
  YYSYMBOL_struct_var_declaration = 58,    /* struct_var_declaration  */
  YYSYMBOL_variable_list = 59,             /* variable_list  */
  YYSYMBOL_variable_declaration = 60,      /* variable_declaration  */
  YYSYMBOL_array_dimensions = 61,          /* array_dimensions  */
  YYSYMBOL_function = 62,                  /* function  */
  YYSYMBOL_function_head = 63,             /* function_head  */
  YYSYMBOL_parameter_list = 64,            /* parameter_list  */
  YYSYMBOL_statement = 65,                 /* statement  */
  YYSYMBOL_block = 66,                     /* block  */
  YYSYMBOL_declaration_list = 67,          /* declaration_list  */
  YYSYMBOL_statement_list = 68,            /* statement_list  */
  YYSYMBOL_assignment_statement = 69,      /* assignment_statement  */
  YYSYMBOL_field_access = 70,              /* field_access  */
  YYSYMBOL_expression = 71,                /* expression  */
  YYSYMBOL_argument_list = 72,             /* argument_list  */
  YYSYMBOL_expression_list = 73,           /* expression_list  */
  YYSYMBOL_input_statement = 74,           /* input_statement  */
  YYSYMBOL_output_statement = 75,          /* output_statement  */
  YYSYMBOL_return_statement = 76,          /* return_statement  */
  YYSYMBOL_if_statement = 77,              /* if_statement  */
  YYSYMBOL_while_statement = 78,           /* while_statement  */
  YYSYMBOL_call_statement = 79,            /* call_statement  */
  YYSYMBOL_call_expression = 80,           /* call_expression  */
  YYSYMBOL_index_list = 81,                /* index_list  */
  YYSYMBOL_switch_statement = 82,          /* switch_statement  */
  YYSYMBOL_83_4 = 83,                      /* @4  */
  YYSYMBOL_84_5 = 84,                      /* @5  */
  YYSYMBOL_case_list = 85,                 /* case_list  */
  YYSYMBOL_case_clause = 86,               /* case_clause  */
  YYSYMBOL_default_opt = 87                /* default_opt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   322

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  113
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  225

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    44,     2,
      36,    42,    33,    31,    40,    32,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    45,    39,
       2,    43,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    35,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    73,    73,    82,    83,    89,    93,    97,   103,   109,
     114,   119,   124,   129,   134,   141,   145,   149,   153,   157,
     161,   169,   169,   173,   173,   178,   177,   190,   191,   197,
     201,   208,   209,   216,   220,   224,   231,   236,   248,   254,
     263,   273,   277,   282,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   301,   302,   311,   320,   323,   332,   335,
     343,   347,   351,   355,   361,   365,   369,   373,   383,   387,
     391,   395,   399,   403,   407,   411,   415,   419,   423,   427,
     431,   435,   439,   443,   447,   451,   455,   459,   463,   467,
     477,   480,   485,   486,   495,   503,   507,   515,   525,   529,
     537,   545,   553,   560,   565,   575,   574,   585,   584,   595,
     599,   605,   612,   615
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "CHAR",
  "STRUCT", "DOT", "EQ", "NE", "LT", "LE", "GT", "GE", "UMINUS", "UADDR",
  "UDEREF", "IF", "ELSE", "WHILE", "FUNC", "INPUT", "OUTPUT", "RETURN",
  "SWITCH", "CASE", "DEFAULT", "BREAK", "INTEGER", "IDENTIFIER", "TEXT",
  "CHARACTER", "'+'", "'-'", "'*'", "'/'", "'['", "'('", "'{'", "'}'",
  "';'", "','", "']'", "')'", "'='", "'&'", "':'", "$accept", "program",
  "function_declaration_list", "function_declaration", "struct_definition",
  "field_list", "field_declarators", "declaration", "$@1", "$@2", "$@3",
  "struct_var_list", "struct_var_declaration", "variable_list",
  "variable_declaration", "array_dimensions", "function", "function_head",
  "parameter_list", "statement", "block", "declaration_list",
  "statement_list", "assignment_statement", "field_access", "expression",
  "argument_list", "expression_list", "input_statement",
  "output_statement", "return_statement", "if_statement",
  "while_statement", "call_statement", "call_expression", "index_list",
  "switch_statement", "@4", "@5", "case_list", "case_clause",
  "default_opt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-195)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-114)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     155,  -195,  -195,  -195,    26,  -195,    28,   289,  -195,  -195,
    -195,  -195,    41,   -26,   -26,    47,  -195,  -195,    58,    63,
      86,   -21,  -195,    11,    89,    88,  -195,   -29,   104,    91,
    -195,  -195,   -26,  -195,   -23,   -23,   105,    19,    63,    56,
    -195,   116,   109,   107,   127,  -195,    63,   133,    69,   103,
     -23,   -23,   -23,   141,   132,    91,  -195,    88,  -195,  -195,
    -195,  -195,   138,    91,  -195,  -195,   -19,  -195,   124,   137,
     142,   -23,  -195,  -195,   108,  -195,    63,   156,  -195,  -195,
    -195,   147,   160,  -195,   129,    91,  -195,  -195,  -195,  -195,
     183,   189,   192,    30,    74,   195,   198,     2,   211,  -195,
    -195,  -195,   201,     0,   203,   204,   224,  -195,  -195,   225,
    -195,    74,    74,  -195,  -195,  -195,  -195,  -195,    54,  -195,
      74,    74,    74,   213,    20,   288,  -195,    74,  -195,   237,
      74,    55,    74,     9,   223,  -195,   239,    74,    74,  -195,
    -195,  -195,  -195,   184,   190,    55,    43,  -195,  -195,   196,
      70,    20,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,   202,  -195,   238,   288,   226,   233,   288,   246,
      74,    74,    74,  -195,   244,   288,   109,   109,   245,  -195,
      43,    40,    40,    40,    40,    40,    40,    95,    95,  -195,
    -195,  -195,  -195,  -195,    74,  -195,   250,   288,   288,  -195,
     263,  -195,  -195,   249,   251,   288,  -195,   109,   277,   278,
    -195,   275,   114,  -195,   259,   267,   261,  -195,   269,  -195,
    -195,  -195,  -195,   152,    99
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    39,    21,    23,     0,    40,     0,     0,     3,     7,
       6,     5,     0,     0,     0,    25,     1,     4,    43,    33,
       0,     0,    31,     0,     0,     0,    41,     0,     0,    35,
      34,    22,     0,    24,     0,     0,     0,     0,    29,     0,
      27,     0,     0,     0,     0,    32,    15,     0,     0,     0,
       0,     0,     0,     0,     0,    30,    26,     0,    42,    56,
      38,    36,     0,    17,    16,     9,     0,    10,     0,     0,
       0,     0,     8,    28,    58,    37,    18,     0,    11,    12,
      13,     0,     0,    57,     0,    20,    19,    14,    25,    54,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    55,
      59,    53,     0,     0,     0,     0,     0,    49,    50,     0,
      51,     0,     0,    94,    95,    96,    89,    80,    85,    81,
       0,     0,     0,     0,    87,    97,    88,     0,    52,     0,
       0,     0,     0,     0,     0,    44,     0,     0,     0,    45,
      46,    48,    47,     0,     0,     0,    86,    72,    84,     0,
      82,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,    92,     0,    91,    60,     0,
       0,     0,     0,    66,     0,    63,     0,     0,     0,    79,
       0,    73,    74,    75,    76,    77,    78,    68,    69,    70,
      71,   105,   103,   101,     0,    65,     0,    62,    61,    67,
      98,   100,   102,     0,     0,    93,   104,     0,     0,   112,
      99,     0,   112,   109,     0,     0,     0,   110,     0,    58,
     108,    58,   106,     0,     0
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -195,  -195,  -195,   301,  -195,  -195,   -18,   235,  -195,  -195,
    -195,  -195,   253,   297,   280,   -34,  -195,  -195,  -195,  -195,
     -42,  -195,  -194,  -195,   -83,   -91,   168,  -195,  -195,  -195,
    -195,  -195,  -195,  -195,  -195,  -102,  -195,  -195,  -195,  -195,
     102,   106
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     6,     7,     8,     9,    37,    48,    10,    13,    14,
      25,    39,    40,    21,    22,    29,    11,    12,    27,   100,
     101,    74,    84,   102,   124,   165,   166,   167,   104,   105,
     106,   107,   108,   109,   126,   133,   110,   203,   204,   212,
     213,   215
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      60,   103,    19,   125,    55,    46,   136,    20,   129,    76,
      47,    41,    63,    42,    77,   169,   146,    49,    31,    32,
     143,   144,    51,    52,    53,   223,   136,   224,    16,   147,
     148,   149,    68,    69,    70,   137,   162,   130,   131,   164,
     151,   168,    85,   138,   170,   132,   174,   175,   180,   169,
      33,    32,   171,    81,    15,   137,   116,    54,   114,   115,
     129,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   158,   159,   160,   161,   116,   129,    18,   170,   196,
     197,   198,   117,   118,    24,   119,    26,   120,   121,   130,
     145,   122,    34,    35,    36,    56,    57,   -90,    28,   123,
      89,   117,   118,   205,   119,   130,   120,   121,    65,    66,
     122,     2,     3,    82,    30,    90,    38,    91,   123,    92,
      93,    94,    95,  -111,  -111,    96,    44,    97,   160,   161,
      89,    43,    98,    50,   200,   201,    59,  -111,   211,   214,
     103,   103,    67,    66,    58,    90,    59,    91,    61,    92,
      93,    94,    95,    89,    62,    96,     1,    97,     2,     3,
       4,    64,    98,    78,    66,   210,    59,    99,    90,    71,
      91,    72,    92,    93,    94,    95,    79,    66,    96,    75,
      97,    80,    66,     5,    86,    98,    87,    66,    88,    59,
    -113,   152,   153,   154,   155,   156,   157,   152,   153,   154,
     155,   156,   157,   152,   153,   154,   155,   156,   157,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   111,
     113,   158,   159,   160,   161,   112,   176,   158,   159,   160,
     161,   127,   177,   158,   159,   160,   161,   128,   179,   134,
     135,   150,   139,   140,   191,   152,   153,   154,   155,   156,
     157,   152,   153,   154,   155,   156,   157,   152,   153,   154,
     155,   156,   157,   141,   142,   163,   172,   173,   193,   158,
     159,   160,   161,   194,   195,   158,   159,   160,   161,   192,
     207,   158,   159,   160,   161,   199,   208,   202,   209,    -2,
       1,   206,     2,     3,     4,   152,   153,   154,   155,   156,
     157,   211,   216,   214,   219,   220,   221,   222,    17,    83,
      73,    23,    45,   178,   217,     0,     0,     5,   218,   158,
     159,   160,   161
};

static const yytype_int16 yycheck[] =
{
      42,    84,    28,    94,    38,    28,     6,    33,     6,    28,
      33,    40,    46,    42,    33,     6,   118,    35,    39,    40,
     111,   112,     3,     4,     5,   219,     6,   221,     0,   120,
     121,   122,    50,    51,    52,    35,   127,    35,    36,   130,
     123,   132,    76,    43,    35,    43,   137,   138,   150,     6,
      39,    40,    43,    71,    28,    35,     1,    38,    28,    29,
       6,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,    31,    32,    33,    34,     1,     6,    36,    35,   170,
     171,   172,    27,    28,    37,    30,    28,    32,    33,    35,
      36,    36,     3,     4,     5,    39,    40,    42,    35,    44,
       1,    27,    28,   194,    30,    35,    32,    33,    39,    40,
      36,     3,     4,     5,    28,    16,    28,    18,    44,    20,
      21,    22,    23,    24,    25,    26,    35,    28,    33,    34,
       1,    27,    33,    28,   176,   177,    37,    38,    24,    25,
     223,   224,    39,    40,    28,    16,    37,    18,    41,    20,
      21,    22,    23,     1,    27,    26,     1,    28,     3,     4,
       5,    28,    33,    39,    40,   207,    37,    38,    16,    28,
      18,    39,    20,    21,    22,    23,    39,    40,    26,    41,
      28,    39,    40,    28,    28,    33,    39,    40,    28,    37,
      38,     7,     8,     9,    10,    11,    12,     7,     8,     9,
      10,    11,    12,     7,     8,     9,    10,    11,    12,     7,
       8,     9,    10,    11,    12,    31,    32,    33,    34,    36,
      28,    31,    32,    33,    34,    36,    42,    31,    32,    33,
      34,    36,    42,    31,    32,    33,    34,    39,    42,    28,
      39,    28,    39,    39,    42,     7,     8,     9,    10,    11,
      12,     7,     8,     9,    10,    11,    12,     7,     8,     9,
      10,    11,    12,    39,    39,    28,    43,    28,    42,    31,
      32,    33,    34,    40,    28,    31,    32,    33,    34,    41,
      17,    31,    32,    33,    34,    41,    37,    42,    37,     0,
       1,    41,     3,     4,     5,     7,     8,     9,    10,    11,
      12,    24,    27,    25,    45,    38,    45,    38,     7,    74,
      57,    14,    32,   145,   212,    -1,    -1,    28,   212,    31,
      32,    33,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,     5,    28,    47,    48,    49,    50,
      53,    62,    63,    54,    55,    28,     0,    49,    36,    28,
      33,    59,    60,    59,    37,    56,    28,    64,    35,    61,
      28,    39,    40,    39,     3,     4,     5,    51,    28,    57,
      58,    40,    42,    27,    35,    60,    28,    33,    52,    52,
      28,     3,     4,     5,    38,    61,    39,    40,    28,    37,
      66,    41,    27,    61,    28,    39,    40,    39,    52,    52,
      52,    28,    39,    58,    67,    41,    28,    33,    39,    39,
      39,    52,     5,    53,    68,    61,    28,    39,    28,     1,
      16,    18,    20,    21,    22,    23,    26,    28,    33,    38,
      65,    66,    69,    70,    74,    75,    76,    77,    78,    79,
      82,    36,    36,    28,    28,    29,     1,    27,    28,    30,
      32,    33,    36,    44,    70,    71,    80,    36,    39,     6,
      35,    36,    43,    81,    28,    39,     6,    35,    43,    39,
      39,    39,    39,    71,    71,    36,    81,    71,    71,    71,
      28,    70,     7,     8,     9,    10,    11,    12,    31,    32,
      33,    34,    71,    28,    71,    71,    72,    73,    71,     6,
      35,    43,    43,    28,    71,    71,    42,    42,    72,    42,
      81,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    42,    41,    42,    40,    28,    71,    71,    71,    41,
      66,    66,    42,    83,    84,    71,    41,    17,    37,    37,
      66,    24,    85,    86,    25,    87,    27,    86,    87,    45,
      38,    45,    38,    68,    68
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    49,    50,    51,
      51,    51,    51,    51,    51,    52,    52,    52,    52,    52,
      52,    54,    53,    55,    53,    56,    53,    57,    57,    58,
      58,    59,    59,    60,    60,    60,    61,    61,    62,    62,
      63,    64,    64,    64,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    66,    67,    67,    68,    68,
      69,    69,    69,    69,    70,    70,    70,    70,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      72,    72,    73,    73,    74,    75,    75,    76,    77,    77,
      78,    79,    80,    81,    81,    83,    82,    84,    82,    85,
      85,    86,    87,    87
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     6,     3,
       3,     4,     4,     4,     5,     1,     2,     2,     3,     4,
       4,     0,     4,     0,     4,     0,     5,     1,     3,     1,
       2,     1,     3,     1,     2,     2,     3,     4,     5,     1,
       1,     1,     3,     0,     2,     2,     2,     2,     2,     1,
       1,     1,     2,     1,     1,     4,     0,     2,     0,     2,
       3,     4,     4,     3,     3,     4,     3,     4,     3,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     2,     2,     2,     1,     2,     1,     1,     1,
       0,     1,     1,     3,     2,     2,     2,     2,     5,     7,
       5,     4,     4,     3,     4,     0,     9,     0,     8,     1,
       2,     4,     0,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: function_declaration_list  */
#line 74 "mini.y"
{
	tac_last=(yyvsp[0].tac);
	tac_complete();
}
#line 1339 "mini.tab.c"
    break;

  case 4: /* function_declaration_list: function_declaration_list function_declaration  */
#line 84 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
}
#line 1347 "mini.tab.c"
    break;

  case 5: /* function_declaration: function  */
#line 90 "mini.y"
    {
        (yyval.tac) = (yyvsp[0].tac);  /* 返回 TAC* */
    }
#line 1355 "mini.tab.c"
    break;

  case 6: /* function_declaration: declaration  */
#line 94 "mini.y"
    {
        (yyval.tac) = (yyvsp[0].tac);  /* 返回 TAC* */
    }
#line 1363 "mini.tab.c"
    break;

  case 7: /* function_declaration: struct_definition  */
#line 98 "mini.y"
    {
        (yyval.tac) = NULL;  /* 结构体定义不生成 TAC，返回 NULL */
    }
#line 1371 "mini.tab.c"
    break;

  case 8: /* struct_definition: STRUCT IDENTIFIER '{' field_list '}' ';'  */
#line 104 "mini.y"
{
	(yyval.meta) = finalize_struct((yyvsp[-4].string), (yyvsp[-2].meta));
}
#line 1379 "mini.tab.c"
    break;

  case 9: /* field_list: INT field_declarators ';'  */
#line 110 "mini.y"
{
	(yyval.meta) = (yyvsp[-1].meta);
	set_field_type((yyval.meta), FIELD_INT);
}
#line 1388 "mini.tab.c"
    break;

  case 10: /* field_list: CHAR field_declarators ';'  */
#line 115 "mini.y"
{
	(yyval.meta) = (yyvsp[-1].meta);
	set_field_type((yyval.meta), FIELD_CHAR);
}
#line 1397 "mini.tab.c"
    break;

  case 11: /* field_list: STRUCT IDENTIFIER field_declarators ';'  */
#line 120 "mini.y"
{
	(yyval.meta) = (yyvsp[-1].meta);
	set_field_struct_type((yyval.meta), (yyvsp[-2].string));
}
#line 1406 "mini.tab.c"
    break;

  case 12: /* field_list: field_list INT field_declarators ';'  */
#line 125 "mini.y"
{
	(yyval.meta) = append_fields((yyvsp[-3].meta), (yyvsp[-1].meta));
	set_field_type((yyvsp[-1].meta), FIELD_INT);
}
#line 1415 "mini.tab.c"
    break;

  case 13: /* field_list: field_list CHAR field_declarators ';'  */
#line 130 "mini.y"
{
	(yyval.meta) = append_fields((yyvsp[-3].meta), (yyvsp[-1].meta));
	set_field_type((yyvsp[-1].meta), FIELD_CHAR);
}
#line 1424 "mini.tab.c"
    break;

  case 14: /* field_list: field_list STRUCT IDENTIFIER field_declarators ';'  */
#line 135 "mini.y"
{
	(yyval.meta) = append_fields((yyvsp[-4].meta), (yyvsp[-1].meta));
	set_field_struct_type((yyvsp[-1].meta), (yyvsp[-2].string));
}
#line 1433 "mini.tab.c"
    break;

  case 15: /* field_declarators: IDENTIFIER  */
#line 142 "mini.y"
{
	(yyval.meta) = create_field((yyvsp[0].string), NULL, 0);
}
#line 1441 "mini.tab.c"
    break;

  case 16: /* field_declarators: '*' IDENTIFIER  */
#line 146 "mini.y"
{
	(yyval.meta) = create_field_ptr((yyvsp[0].string));
}
#line 1449 "mini.tab.c"
    break;

  case 17: /* field_declarators: IDENTIFIER array_dimensions  */
#line 150 "mini.y"
{
	(yyval.meta) = create_field((yyvsp[-1].string), (yyvsp[0].arr_dims).dims, (yyvsp[0].arr_dims).ndims);
}
#line 1457 "mini.tab.c"
    break;

  case 18: /* field_declarators: field_declarators ',' IDENTIFIER  */
#line 154 "mini.y"
{
	(yyval.meta) = append_field_name((yyvsp[-2].meta), (yyvsp[0].string), NULL, 0);
}
#line 1465 "mini.tab.c"
    break;

  case 19: /* field_declarators: field_declarators ',' '*' IDENTIFIER  */
#line 158 "mini.y"
{
	(yyval.meta) = append_field_name_ptr((yyvsp[-3].meta), (yyvsp[0].string));
}
#line 1473 "mini.tab.c"
    break;

  case 20: /* field_declarators: field_declarators ',' IDENTIFIER array_dimensions  */
#line 162 "mini.y"
{
	(yyval.meta) = append_field_name((yyvsp[-3].meta), (yyvsp[-1].string), (yyvsp[0].arr_dims).dims, (yyvsp[0].arr_dims).ndims);
}
#line 1481 "mini.tab.c"
    break;

  case 21: /* $@1: %empty  */
#line 169 "mini.y"
                  { decl_dtype=DT_INT; }
#line 1487 "mini.tab.c"
    break;

  case 22: /* declaration: INT $@1 variable_list ';'  */
#line 170 "mini.y"
{
    (yyval.tac)=(yyvsp[-1].tac);
}
#line 1495 "mini.tab.c"
    break;

  case 23: /* $@2: %empty  */
#line 173 "mini.y"
       { decl_dtype=DT_CHAR; }
#line 1501 "mini.tab.c"
    break;

  case 24: /* declaration: CHAR $@2 variable_list ';'  */
#line 174 "mini.y"
{
    (yyval.tac)=(yyvsp[-1].tac);
}
#line 1509 "mini.tab.c"
    break;

  case 25: /* $@3: %empty  */
#line 178 "mini.y"
{
	decl_struct = lookup_struct((yyvsp[0].string));
	if(!decl_struct) {
		yyerror("Undefined struct");
	}
}
#line 1520 "mini.tab.c"
    break;

  case 26: /* declaration: STRUCT IDENTIFIER $@3 struct_var_list ';'  */
#line 185 "mini.y"
{
	(yyval.tac)=(yyvsp[-1].tac);
}
#line 1528 "mini.tab.c"
    break;

  case 28: /* struct_var_list: struct_var_list ',' struct_var_declaration  */
#line 192 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-2].tac), (yyvsp[0].tac));
}
#line 1536 "mini.tab.c"
    break;

  case 29: /* struct_var_declaration: IDENTIFIER  */
#line 198 "mini.y"
{
	(yyval.tac)=declare_struct_var((yyvsp[0].string), decl_struct);
}
#line 1544 "mini.tab.c"
    break;

  case 30: /* struct_var_declaration: IDENTIFIER array_dimensions  */
#line 202 "mini.y"
{
	(yyval.tac)=declare_struct_array((yyvsp[-1].string), decl_struct, (yyvsp[0].arr_dims).dims, (yyvsp[0].arr_dims).ndims);
}
#line 1552 "mini.tab.c"
    break;

  case 32: /* variable_list: variable_list ',' variable_declaration  */
#line 210 "mini.y"
{
    (yyval.tac)=join_tac((yyvsp[-2].tac), (yyvsp[0].tac));
}
#line 1560 "mini.tab.c"
    break;

  case 33: /* variable_declaration: IDENTIFIER  */
#line 217 "mini.y"
{
    (yyval.tac)=declare_var((yyvsp[0].string));
}
#line 1568 "mini.tab.c"
    break;

  case 34: /* variable_declaration: '*' IDENTIFIER  */
#line 221 "mini.y"
{
    (yyval.tac)=declare_ptr_var((yyvsp[0].string));
}
#line 1576 "mini.tab.c"
    break;

  case 35: /* variable_declaration: IDENTIFIER array_dimensions  */
#line 225 "mini.y"
{
    (yyval.tac)=declare_array_var((yyvsp[-1].string), (yyvsp[0].arr_dims).dims, (yyvsp[0].arr_dims).ndims);
}
#line 1584 "mini.tab.c"
    break;

  case 36: /* array_dimensions: '[' INTEGER ']'  */
#line 232 "mini.y"
{
    (yyval.arr_dims).dims[0] = atoi((yyvsp[-1].string));
    (yyval.arr_dims).ndims = 1;
}
#line 1593 "mini.tab.c"
    break;

  case 37: /* array_dimensions: array_dimensions '[' INTEGER ']'  */
#line 237 "mini.y"
{
    if ((yyvsp[-3].arr_dims).ndims >= 16) {
        yyerror("Array dimensions exceed maximum (16)");
    }
    (yyval.arr_dims) = (yyvsp[-3].arr_dims);
    (yyval.arr_dims).dims[(yyval.arr_dims).ndims++] = atoi((yyvsp[-1].string));
}
#line 1605 "mini.tab.c"
    break;

  case 38: /* function: function_head '(' parameter_list ')' block  */
#line 249 "mini.y"
{
	(yyval.tac)=do_func((yyvsp[-4].sym), (yyvsp[-2].tac), (yyvsp[0].tac));
	scope=0; /* Leave local scope. */
	sym_tab_local=NULL; /* Clear local symbol table. */
}
#line 1615 "mini.tab.c"
    break;

  case 39: /* function: error  */
#line 255 "mini.y"
{
	error("Bad function syntax");
	(yyval.tac)=NULL;
}
#line 1624 "mini.tab.c"
    break;

  case 40: /* function_head: IDENTIFIER  */
#line 264 "mini.y"
{
	(yyval.sym)=declare_func((yyvsp[0].string));
	scope=1; /* Enter local scope. */
	sym_tab_local=NULL; /* Init local symbol table. */
}
#line 1634 "mini.tab.c"
    break;

  case 41: /* parameter_list: IDENTIFIER  */
#line 274 "mini.y"
{
	(yyval.tac)=declare_para((yyvsp[0].string));
}
#line 1642 "mini.tab.c"
    break;

  case 42: /* parameter_list: parameter_list ',' IDENTIFIER  */
#line 278 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-2].tac), declare_para((yyvsp[0].string)));
}
#line 1650 "mini.tab.c"
    break;

  case 43: /* parameter_list: %empty  */
#line 282 "mini.y"
{
	(yyval.tac)=NULL;
}
#line 1658 "mini.tab.c"
    break;

  case 52: /* statement: BREAK ';'  */
#line 298 "mini.y"
{
	(yyval.tac) = do_break();
}
#line 1666 "mini.tab.c"
    break;

  case 54: /* statement: error  */
#line 303 "mini.y"
{
	error("Bad statement syntax");
	(yyval.tac)=NULL;
}
#line 1675 "mini.tab.c"
    break;

  case 55: /* block: '{' declaration_list statement_list '}'  */
#line 312 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-2].tac), (yyvsp[-1].tac));
}
#line 1683 "mini.tab.c"
    break;

  case 56: /* declaration_list: %empty  */
#line 320 "mini.y"
{
	(yyval.tac)=NULL;
}
#line 1691 "mini.tab.c"
    break;

  case 57: /* declaration_list: declaration_list declaration  */
#line 324 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
}
#line 1699 "mini.tab.c"
    break;

  case 58: /* statement_list: %empty  */
#line 332 "mini.y"
{
	(yyval.tac) = NULL;
}
#line 1707 "mini.tab.c"
    break;

  case 59: /* statement_list: statement_list statement  */
#line 336 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
}
#line 1715 "mini.tab.c"
    break;

  case 60: /* assignment_statement: IDENTIFIER '=' expression  */
#line 344 "mini.y"
{
    (yyval.tac)=do_assign(get_var((yyvsp[-2].string)), (yyvsp[0].exp));
}
#line 1723 "mini.tab.c"
    break;

  case 61: /* assignment_statement: '*' IDENTIFIER '=' expression  */
#line 348 "mini.y"
{
    (yyval.tac)=do_deref_write(get_var((yyvsp[-2].string)), (yyvsp[0].exp));
}
#line 1731 "mini.tab.c"
    break;

  case 62: /* assignment_statement: IDENTIFIER index_list '=' expression  */
#line 352 "mini.y"
{
	(yyval.tac) = do_array_write(get_var((yyvsp[-3].string)),(yyvsp[-2].exp_list),(yyvsp[0].exp));
}
#line 1739 "mini.tab.c"
    break;

  case 63: /* assignment_statement: field_access '=' expression  */
#line 356 "mini.y"
{
	(yyval.tac) = do_field_write((yyvsp[-2].field_chain).chain, (yyvsp[0].exp));
}
#line 1747 "mini.tab.c"
    break;

  case 64: /* field_access: IDENTIFIER DOT IDENTIFIER  */
#line 362 "mini.y"
{
	(yyval.field_chain).chain = create_field_access((yyvsp[-2].string), (yyvsp[0].string));
}
#line 1755 "mini.tab.c"
    break;

  case 65: /* field_access: IDENTIFIER index_list DOT IDENTIFIER  */
#line 366 "mini.y"
{
    (yyval.field_chain).chain = create_field_access_array((yyvsp[-3].string), (yyvsp[-2].exp_list), (yyvsp[0].string));
}
#line 1763 "mini.tab.c"
    break;

  case 66: /* field_access: field_access DOT IDENTIFIER  */
#line 370 "mini.y"
{
	(yyval.field_chain).chain = append_field_access((yyvsp[-2].field_chain).chain, (yyvsp[0].string));
}
#line 1771 "mini.tab.c"
    break;

  case 67: /* field_access: field_access '[' expression ']'  */
#line 374 "mini.y"
{
    EXP *single_index = (yyvsp[-1].exp);
    single_index->next = NULL;  /* 确保是单元素列表 */
    (yyval.field_chain).chain = append_array_access((yyvsp[-3].field_chain).chain, single_index);
}
#line 1781 "mini.tab.c"
    break;

  case 68: /* expression: expression '+' expression  */
#line 384 "mini.y"
{
	(yyval.exp)=do_bin(TAC_ADD, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1789 "mini.tab.c"
    break;

  case 69: /* expression: expression '-' expression  */
#line 388 "mini.y"
{
	(yyval.exp)=do_bin(TAC_SUB, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1797 "mini.tab.c"
    break;

  case 70: /* expression: expression '*' expression  */
#line 392 "mini.y"
{
	(yyval.exp)=do_bin(TAC_MUL, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1805 "mini.tab.c"
    break;

  case 71: /* expression: expression '/' expression  */
#line 396 "mini.y"
{
	(yyval.exp)=do_bin(TAC_DIV, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1813 "mini.tab.c"
    break;

  case 72: /* expression: '-' expression  */
#line 400 "mini.y"
{
	(yyval.exp)=do_un(TAC_NEG, (yyvsp[0].exp));
}
#line 1821 "mini.tab.c"
    break;

  case 73: /* expression: expression EQ expression  */
#line 404 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_EQ, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1829 "mini.tab.c"
    break;

  case 74: /* expression: expression NE expression  */
#line 408 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_NE, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1837 "mini.tab.c"
    break;

  case 75: /* expression: expression LT expression  */
#line 412 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_LT, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1845 "mini.tab.c"
    break;

  case 76: /* expression: expression LE expression  */
#line 416 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_LE, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1853 "mini.tab.c"
    break;

  case 77: /* expression: expression GT expression  */
#line 420 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_GT, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1861 "mini.tab.c"
    break;

  case 78: /* expression: expression GE expression  */
#line 424 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_GE, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1869 "mini.tab.c"
    break;

  case 79: /* expression: '(' expression ')'  */
#line 428 "mini.y"
{
	(yyval.exp)=(yyvsp[-1].exp);
}
#line 1877 "mini.tab.c"
    break;

  case 80: /* expression: INTEGER  */
#line 432 "mini.y"
{
    (yyval.exp)=mk_exp(NULL, mk_const(atoi((yyvsp[0].string))), NULL);
}
#line 1885 "mini.tab.c"
    break;

  case 81: /* expression: CHARACTER  */
#line 436 "mini.y"
{
    (yyval.exp)=mk_exp(NULL, mk_const((int)(yyvsp[0].character)), NULL);
}
#line 1893 "mini.tab.c"
    break;

  case 82: /* expression: '&' IDENTIFIER  */
#line 440 "mini.y"
{
    (yyval.exp)=do_addr(get_var((yyvsp[0].string)));
}
#line 1901 "mini.tab.c"
    break;

  case 83: /* expression: '&' field_access  */
#line 444 "mini.y"
{
    (yyval.exp)=do_field_addr((yyvsp[0].field_chain).chain);
}
#line 1909 "mini.tab.c"
    break;

  case 84: /* expression: '*' expression  */
#line 448 "mini.y"
{
    (yyval.exp)=do_deref_read((yyvsp[0].exp));
}
#line 1917 "mini.tab.c"
    break;

  case 85: /* expression: IDENTIFIER  */
#line 452 "mini.y"
{
    (yyval.exp)=mk_exp(NULL, get_var((yyvsp[0].string)), NULL);
}
#line 1925 "mini.tab.c"
    break;

  case 86: /* expression: IDENTIFIER index_list  */
#line 456 "mini.y"
{
	(yyval.exp) = do_array_read(get_var((yyvsp[-1].string)), (yyvsp[0].exp_list));
}
#line 1933 "mini.tab.c"
    break;

  case 87: /* expression: field_access  */
#line 460 "mini.y"
{
	(yyval.exp) = do_field_read((yyvsp[0].field_chain).chain);
}
#line 1941 "mini.tab.c"
    break;

  case 88: /* expression: call_expression  */
#line 464 "mini.y"
{
	(yyval.exp)=(yyvsp[0].exp);
}
#line 1949 "mini.tab.c"
    break;

  case 89: /* expression: error  */
#line 468 "mini.y"
{
	error("Bad expression syntax");
	(yyval.exp)=mk_exp(NULL, NULL, NULL);
}
#line 1958 "mini.tab.c"
    break;

  case 90: /* argument_list: %empty  */
#line 477 "mini.y"
{
	(yyval.exp)=NULL;
}
#line 1966 "mini.tab.c"
    break;

  case 93: /* expression_list: expression_list ',' expression  */
#line 487 "mini.y"
{
	(yyvsp[0].exp)->next=(yyvsp[-2].exp);
	(yyval.exp)=(yyvsp[0].exp);
}
#line 1975 "mini.tab.c"
    break;

  case 94: /* input_statement: INPUT IDENTIFIER  */
#line 496 "mini.y"
{
	(yyval.tac)=do_input(get_var((yyvsp[0].string)));
}
#line 1983 "mini.tab.c"
    break;

  case 95: /* output_statement: OUTPUT IDENTIFIER  */
#line 504 "mini.y"
{
	(yyval.tac)=do_output(get_var((yyvsp[0].string)));
}
#line 1991 "mini.tab.c"
    break;

  case 96: /* output_statement: OUTPUT TEXT  */
#line 508 "mini.y"
{
	(yyval.tac)=do_output(mk_text((yyvsp[0].string)));
}
#line 1999 "mini.tab.c"
    break;

  case 97: /* return_statement: RETURN expression  */
#line 516 "mini.y"
{
	TAC *t=mk_tac(TAC_RETURN, (yyvsp[0].exp)->ret, NULL, NULL);
	t->prev=(yyvsp[0].exp)->tac;
	(yyval.tac)=t;
}
#line 2009 "mini.tab.c"
    break;

  case 98: /* if_statement: IF '(' expression ')' block  */
#line 526 "mini.y"
{
	(yyval.tac)=do_if((yyvsp[-2].exp), (yyvsp[0].tac));
}
#line 2017 "mini.tab.c"
    break;

  case 99: /* if_statement: IF '(' expression ')' block ELSE block  */
#line 530 "mini.y"
{
	(yyval.tac)=do_test((yyvsp[-4].exp), (yyvsp[-2].tac), (yyvsp[0].tac));
}
#line 2025 "mini.tab.c"
    break;

  case 100: /* while_statement: WHILE '(' expression ')' block  */
#line 538 "mini.y"
{
	(yyval.tac)=do_while((yyvsp[-2].exp), (yyvsp[0].tac));
}
#line 2033 "mini.tab.c"
    break;

  case 101: /* call_statement: IDENTIFIER '(' argument_list ')'  */
#line 546 "mini.y"
{
	(yyval.tac)=do_call((yyvsp[-3].string), (yyvsp[-1].exp));
}
#line 2041 "mini.tab.c"
    break;

  case 102: /* call_expression: IDENTIFIER '(' argument_list ')'  */
#line 554 "mini.y"
{
	(yyval.exp)=do_call_ret((yyvsp[-3].string), (yyvsp[-1].exp));
}
#line 2049 "mini.tab.c"
    break;

  case 103: /* index_list: '[' expression ']'  */
#line 561 "mini.y"
{
    (yyval.exp_list) = (yyvsp[-1].exp);
    (yyval.exp_list)->next = NULL;
}
#line 2058 "mini.tab.c"
    break;

  case 104: /* index_list: index_list '[' expression ']'  */
#line 566 "mini.y"
{
    (yyval.exp_list) = (yyvsp[-1].exp);
    (yyval.exp_list)->next = (yyvsp[-3].exp_list);  /* 逆向链接，后续需要反转 */
}
#line 2067 "mini.tab.c"
    break;

  case 105: /* @4: %empty  */
#line 575 "mini.y"
{
    /* 进入 switch 前预分配结束标签 */
    (yyval.sym) = enter_switch();
}
#line 2076 "mini.tab.c"
    break;

  case 106: /* switch_statement: SWITCH '(' expression ')' @4 '{' case_list default_opt '}'  */
#line 580 "mini.y"
{
    /* 退出 switch 时生成完整 TAC */
    (yyval.tac) = exit_switch((yyvsp[-6].exp), (yyvsp[-2].case_list), (yyvsp[-1].tac), (yyvsp[-4].sym));
}
#line 2085 "mini.tab.c"
    break;

  case 107: /* @5: %empty  */
#line 585 "mini.y"
{
    (yyval.sym) = enter_switch();
}
#line 2093 "mini.tab.c"
    break;

  case 108: /* switch_statement: SWITCH '(' expression ')' @5 '{' default_opt '}'  */
#line 589 "mini.y"
{
    /* 只有 default 的 switch */
    (yyval.tac) = exit_switch((yyvsp[-5].exp), NULL, (yyvsp[-1].tac), (yyvsp[-3].sym));
}
#line 2102 "mini.tab.c"
    break;

  case 109: /* case_list: case_clause  */
#line 596 "mini.y"
{
	(yyval.case_list) = (yyvsp[0].case_list);
}
#line 2110 "mini.tab.c"
    break;

  case 110: /* case_list: case_list case_clause  */
#line 600 "mini.y"
{
	(yyval.case_list) = append_case((yyvsp[-1].case_list), (yyvsp[0].case_list));
}
#line 2118 "mini.tab.c"
    break;

  case 111: /* case_clause: CASE INTEGER ':' statement_list  */
#line 606 "mini.y"
{
	(yyval.case_list) = mk_case(atoi((yyvsp[-2].string)), (yyvsp[0].tac));  /* $4 可能是 NULL，由 statement_list 处理 */
}
#line 2126 "mini.tab.c"
    break;

  case 112: /* default_opt: %empty  */
#line 612 "mini.y"
{
	(yyval.tac) = NULL;
}
#line 2134 "mini.tab.c"
    break;

  case 113: /* default_opt: DEFAULT ':' statement_list  */
#line 616 "mini.y"
{
	(yyval.tac) = (yyvsp[0].tac);  /* $3 可能是 NULL */
}
#line 2142 "mini.tab.c"
    break;


#line 2146 "mini.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 621 "mini.y"


/* 语法错误输出：包含行号 */
void yyerror(char* msg) 
{
	fprintf(stderr, "%s: line %d\n", msg, yylineno);
	exit(0);
}
