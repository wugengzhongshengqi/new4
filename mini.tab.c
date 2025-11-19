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
  YYSYMBOL_FOR = 27,                       /* FOR  */
  YYSYMBOL_CONTINUE = 28,                  /* CONTINUE  */
  YYSYMBOL_INTEGER = 29,                   /* INTEGER  */
  YYSYMBOL_IDENTIFIER = 30,                /* IDENTIFIER  */
  YYSYMBOL_TEXT = 31,                      /* TEXT  */
  YYSYMBOL_CHARACTER = 32,                 /* CHARACTER  */
  YYSYMBOL_33_ = 33,                       /* '+'  */
  YYSYMBOL_34_ = 34,                       /* '-'  */
  YYSYMBOL_35_ = 35,                       /* '*'  */
  YYSYMBOL_36_ = 36,                       /* '/'  */
  YYSYMBOL_37_ = 37,                       /* '['  */
  YYSYMBOL_38_ = 38,                       /* '('  */
  YYSYMBOL_39_ = 39,                       /* '{'  */
  YYSYMBOL_40_ = 40,                       /* '}'  */
  YYSYMBOL_41_ = 41,                       /* ';'  */
  YYSYMBOL_42_ = 42,                       /* ','  */
  YYSYMBOL_43_ = 43,                       /* ']'  */
  YYSYMBOL_44_ = 44,                       /* ')'  */
  YYSYMBOL_45_ = 45,                       /* '='  */
  YYSYMBOL_46_ = 46,                       /* '&'  */
  YYSYMBOL_47_ = 47,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_type_spec = 49,                 /* type_spec  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_function_declaration_list = 51, /* function_declaration_list  */
  YYSYMBOL_function_declaration = 52,      /* function_declaration  */
  YYSYMBOL_struct_definition = 53,         /* struct_definition  */
  YYSYMBOL_field_list = 54,                /* field_list  */
  YYSYMBOL_field_declarators = 55,         /* field_declarators  */
  YYSYMBOL_declaration = 56,               /* declaration  */
  YYSYMBOL_57_1 = 57,                      /* $@1  */
  YYSYMBOL_58_2 = 58,                      /* $@2  */
  YYSYMBOL_59_3 = 59,                      /* $@3  */
  YYSYMBOL_struct_var_list = 60,           /* struct_var_list  */
  YYSYMBOL_struct_var_declaration = 61,    /* struct_var_declaration  */
  YYSYMBOL_variable_list = 62,             /* variable_list  */
  YYSYMBOL_variable_declaration = 63,      /* variable_declaration  */
  YYSYMBOL_array_dimensions = 64,          /* array_dimensions  */
  YYSYMBOL_function = 65,                  /* function  */
  YYSYMBOL_function_head = 66,             /* function_head  */
  YYSYMBOL_parameter_list = 67,            /* parameter_list  */
  YYSYMBOL_parameter_list_typed = 68,      /* parameter_list_typed  */
  YYSYMBOL_statement = 69,                 /* statement  */
  YYSYMBOL_block = 70,                     /* block  */
  YYSYMBOL_declaration_list = 71,          /* declaration_list  */
  YYSYMBOL_statement_list = 72,            /* statement_list  */
  YYSYMBOL_assignment_statement = 73,      /* assignment_statement  */
  YYSYMBOL_field_access = 74,              /* field_access  */
  YYSYMBOL_expression = 75,                /* expression  */
  YYSYMBOL_argument_list = 76,             /* argument_list  */
  YYSYMBOL_expression_list = 77,           /* expression_list  */
  YYSYMBOL_input_statement = 78,           /* input_statement  */
  YYSYMBOL_output_statement = 79,          /* output_statement  */
  YYSYMBOL_return_statement = 80,          /* return_statement  */
  YYSYMBOL_if_statement = 81,              /* if_statement  */
  YYSYMBOL_while_statement = 82,           /* while_statement  */
  YYSYMBOL_83_4 = 83,                      /* $@4  */
  YYSYMBOL_call_statement = 84,            /* call_statement  */
  YYSYMBOL_call_expression = 85,           /* call_expression  */
  YYSYMBOL_index_list = 86,                /* index_list  */
  YYSYMBOL_switch_statement = 87,          /* switch_statement  */
  YYSYMBOL_88_5 = 88,                      /* @5  */
  YYSYMBOL_case_list_opt = 89,             /* case_list_opt  */
  YYSYMBOL_case_list = 90,                 /* case_list  */
  YYSYMBOL_case_clause = 91,               /* case_clause  */
  YYSYMBOL_default_opt = 92,               /* default_opt  */
  YYSYMBOL_for_statement = 93,             /* for_statement  */
  YYSYMBOL_94_6 = 94,                      /* $@6  */
  YYSYMBOL_for_init = 95,                  /* for_init  */
  YYSYMBOL_for_cond = 96,                  /* for_cond  */
  YYSYMBOL_for_iter = 97                   /* for_iter  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   402

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  132
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  260

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


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
       2,     2,     2,     2,     2,     2,     2,     2,    46,     2,
      38,    44,    35,    33,    42,    34,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    41,
       2,    45,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    37,     2,    43,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    82,    82,    87,    96,   105,   106,   112,   116,   120,
     126,   132,   137,   142,   147,   152,   157,   164,   168,   172,
     176,   180,   184,   192,   192,   196,   196,   201,   200,   213,
     214,   220,   224,   231,   232,   239,   243,   247,   254,   259,
     271,   278,   284,   293,   303,   307,   312,   318,   321,   325,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     346,   350,   351,   360,   369,   372,   381,   384,   392,   396,
     400,   404,   410,   414,   418,   422,   432,   436,   440,   444,
     448,   452,   456,   460,   464,   468,   472,   476,   480,   484,
     488,   492,   496,   500,   504,   508,   512,   516,   526,   529,
     534,   535,   544,   552,   556,   564,   574,   578,   587,   586,
     601,   609,   616,   621,   632,   631,   643,   646,   653,   657,
     664,   672,   675,   683,   682,   696,   699,   703,   710,   713,
     720,   723,   727
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
  "SWITCH", "CASE", "DEFAULT", "BREAK", "FOR", "CONTINUE", "INTEGER",
  "IDENTIFIER", "TEXT", "CHARACTER", "'+'", "'-'", "'*'", "'/'", "'['",
  "'('", "'{'", "'}'", "';'", "','", "']'", "')'", "'='", "'&'", "':'",
  "$accept", "type_spec", "program", "function_declaration_list",
  "function_declaration", "struct_definition", "field_list",
  "field_declarators", "declaration", "$@1", "$@2", "$@3",
  "struct_var_list", "struct_var_declaration", "variable_list",
  "variable_declaration", "array_dimensions", "function", "function_head",
  "parameter_list", "parameter_list_typed", "statement", "block",
  "declaration_list", "statement_list", "assignment_statement",
  "field_access", "expression", "argument_list", "expression_list",
  "input_statement", "output_statement", "return_statement",
  "if_statement", "while_statement", "$@4", "call_statement",
  "call_expression", "index_list", "switch_statement", "@5",
  "case_list_opt", "case_list", "case_clause", "default_opt",
  "for_statement", "$@6", "for_init", "for_cond", "for_iter", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-113)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-131)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     171,  -113,   -30,   -21,    -8,  -113,    35,    76,   342,  -113,
    -113,  -113,  -113,    41,   -22,   -22,    58,    73,  -113,  -113,
      84,    71,   106,    80,  -113,    86,   114,   110,    57,  -113,
      56,   116,   115,  -113,  -113,   -22,  -113,   -18,   -18,   117,
      23,    71,   101,  -113,  -113,  -113,   128,    95,   143,   148,
     146,   175,  -113,    71,   178,   127,   138,   -18,   -18,   -18,
     183,   165,   115,  -113,   110,  -113,    57,   148,  -113,  -113,
    -113,  -113,   172,   115,  -113,  -113,   -15,  -113,   140,   142,
     161,   -18,  -113,  -113,   187,  -113,   121,  -113,    71,   201,
    -113,  -113,  -113,   181,  -113,  -113,  -113,   202,  -113,   198,
     115,  -113,  -113,  -113,  -113,   196,   197,   206,   125,   132,
     203,   199,   205,   204,     0,   209,  -113,  -113,  -113,   210,
       5,   214,   216,   217,  -113,  -113,   218,  -113,  -113,   132,
     132,  -113,  -113,  -113,  -113,  -113,    -2,  -113,   132,   132,
     132,   220,     3,   366,  -113,   132,  -113,    61,  -113,   230,
     132,    48,   132,    78,   219,  -113,   232,   132,   132,  -113,
    -113,  -113,  -113,   260,   266,    48,    75,  -113,  -113,   272,
      79,     3,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   278,    10,   366,   222,  -113,   316,   366,   247,
     250,   366,   267,   132,   132,   132,  -113,   322,   366,   148,
    -113,   254,  -113,    75,    70,    70,    70,    70,    70,    70,
     176,   176,  -113,  -113,  -113,   132,   100,  -113,  -113,   132,
    -113,   328,   366,   366,  -113,   286,   148,  -113,   270,   366,
     366,   274,   366,  -113,   148,  -113,   293,   119,  -113,   289,
     294,   293,  -113,    19,   366,   276,   297,   301,   281,  -113,
     132,  -113,  -113,  -113,  -113,   366,   148,   170,   226,  -113
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    42,     2,     3,     0,    43,     0,     0,     0,     5,
       9,     8,     7,     0,     0,     0,    27,     0,     1,     6,
      46,    35,     0,     0,    33,     0,     0,     0,    47,    44,
       0,     0,    37,    36,    24,     0,    26,     0,     0,     0,
       0,    31,     0,    29,     2,     3,     0,     0,     0,     0,
       0,     0,    34,    17,     0,     0,     0,     0,     0,     0,
       0,     0,    32,    28,     0,    48,     0,     0,    45,    64,
      41,    38,     0,    19,    18,    11,     0,    12,     0,     0,
       0,     0,    10,    30,     0,    40,    66,    39,    20,     0,
      13,    14,    15,     0,    49,    23,    25,     0,    65,     0,
      22,    21,    16,    27,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,    67,    61,     0,
       0,     0,     0,     0,    55,    56,     0,    58,    57,     0,
       0,   102,   103,   104,    97,    88,    93,    89,     0,     0,
       0,     0,    95,   105,    96,     0,    59,     0,    60,     0,
       0,     0,     0,     0,     0,    50,     0,     0,     0,    51,
      52,    54,    53,     0,     0,     0,    94,    80,    92,     0,
      90,    91,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,   127,     0,    72,     0,   100,     0,
      99,    68,     0,     0,     0,     0,    74,     0,    71,     0,
     108,     0,    87,     0,    81,    82,    83,    84,    85,    86,
      76,    77,    78,    79,   114,     0,     0,   112,   110,     0,
      73,     0,    70,    69,    75,   106,     0,   111,     0,   126,
     129,     0,   101,   113,     0,   109,   116,     0,   107,     0,
     121,   117,   118,    93,   132,     0,     0,     0,     0,   119,
       0,   123,    66,    66,   115,   131,     0,     0,     0,   124
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -113,    -7,  -113,  -113,   333,  -113,  -113,   -28,   268,  -113,
    -113,  -113,  -113,   296,   338,   331,   -34,  -113,   361,  -113,
    -113,  -113,   -49,  -113,   -23,  -113,   -98,  -106,   215,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -112,  -113,
    -113,  -113,  -113,   129,  -113,  -113,  -113,  -113,  -113,  -113
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     6,     7,     8,     9,    10,    40,    55,    11,    14,
      15,    27,    42,    43,    23,    24,    32,    12,    13,    30,
      47,   117,   118,    86,    99,   119,   142,   188,   189,   190,
     121,   122,   123,   124,   125,   226,   126,   144,   166,   127,
     228,   240,   241,   242,   248,   128,   256,   185,   231,   245
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,   120,   153,   143,   149,   -23,   149,    62,    21,   156,
      56,   156,    53,    22,   -25,    88,   149,    54,    85,    73,
      89,    46,    16,   163,   164,   149,    58,    59,    60,    78,
      79,    80,   167,   168,   169,   150,   165,   150,   151,   182,
     157,   184,   157,   171,   187,   152,   191,   150,   165,   134,
     158,   197,   198,    93,   100,   215,   150,   165,   203,    84,
      44,    45,   134,    61,   250,     5,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,    18,   135,   136,    20,
     137,   192,   138,   139,   192,   149,   140,   221,   222,   223,
     135,   183,   -98,   137,   141,   138,   139,    26,    48,   140,
      49,   134,  -125,   178,   179,   180,   181,   141,    31,   229,
     230,    28,   193,   232,    29,   193,   150,    37,    38,    39,
     134,    34,    35,   194,    95,    96,    97,    36,    35,   135,
     136,   244,   137,   134,   138,   139,    33,    66,   140,    67,
      41,  -128,    63,    64,   255,    50,   141,    57,   135,   243,
     225,   137,    51,   138,   139,   132,   133,   140,    65,   120,
     120,   135,   136,  -130,   137,   141,   138,   139,    75,    76,
     140,   104,     1,    68,     2,     3,     4,   235,   141,    77,
      76,    90,    76,    91,    76,   238,   105,    69,   106,    71,
     107,   108,   109,   110,  -120,  -120,   111,   112,   113,   104,
     114,     5,    92,    76,    72,   115,    82,   259,    74,    69,
    -120,   180,   181,    81,   105,    87,   106,    94,   107,   108,
     109,   110,   102,    76,   111,   112,   113,   104,   114,   257,
     258,   101,   103,   115,   129,   130,   131,    69,   116,   154,
     146,   145,   105,   147,   106,   148,   107,   108,   109,   110,
     170,   155,   111,   112,   113,   159,   114,   160,   161,   162,
     186,   115,   196,   216,   195,    69,  -122,   172,   173,   174,
     175,   176,   177,   172,   173,   174,   175,   176,   177,   172,
     173,   174,   175,   176,   177,   172,   173,   174,   175,   176,
     177,   218,   219,   178,   179,   180,   181,   220,   227,   178,
     179,   180,   181,   234,   199,   178,   179,   180,   181,   236,
     200,   178,   179,   180,   181,   237,   202,   239,   246,   247,
     251,   254,   214,   172,   173,   174,   175,   176,   177,   172,
     173,   174,   175,   176,   177,   172,   173,   174,   175,   176,
     177,    19,    -4,     1,   252,     2,     3,     4,   253,   178,
     179,   180,   181,    25,    98,   178,   179,   180,   181,   217,
      83,   178,   179,   180,   181,   224,    52,    17,     0,     0,
     249,   233,     5,   172,   173,   174,   175,   176,   177,     0,
     201,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   178,
     179,   180,   181
};

static const yytype_int16 yycheck[] =
{
      49,    99,   114,   109,     6,    35,     6,    41,    30,     6,
      38,     6,    30,    35,    35,    30,     6,    35,    67,    53,
      35,    28,    30,   129,   130,     6,     3,     4,     5,    57,
      58,    59,   138,   139,   140,    37,    38,    37,    38,   145,
      37,   147,    37,   141,   150,    45,   152,    37,    38,     1,
      45,   157,   158,    81,    88,    45,    37,    38,   170,    66,
       3,     4,     1,    40,    45,    30,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,     0,    29,    30,    38,
      32,     6,    34,    35,     6,     6,    38,   193,   194,   195,
      29,    30,    44,    32,    46,    34,    35,    39,    42,    38,
      44,     1,    41,    33,    34,    35,    36,    46,    37,   215,
     216,    38,    37,   219,    30,    37,    37,     3,     4,     5,
       1,    41,    42,    45,     3,     4,     5,    41,    42,    29,
      30,   237,    32,     1,    34,    35,    30,    42,    38,    44,
      30,    41,    41,    42,   250,    29,    46,    30,    29,    30,
     199,    32,    37,    34,    35,    30,    31,    38,    30,   257,
     258,    29,    30,    44,    32,    46,    34,    35,    41,    42,
      38,     1,     1,    30,     3,     4,     5,   226,    46,    41,
      42,    41,    42,    41,    42,   234,    16,    39,    18,    43,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     1,
      30,    30,    41,    42,    29,    35,    41,   256,    30,    39,
      40,    35,    36,    30,    16,    43,    18,    30,    20,    21,
      22,    23,    41,    42,    26,    27,    28,     1,    30,   252,
     253,    30,    30,    35,    38,    38,    30,    39,    40,    30,
      41,    38,    16,    38,    18,    41,    20,    21,    22,    23,
      30,    41,    26,    27,    28,    41,    30,    41,    41,    41,
      30,    35,    30,    41,    45,    39,    40,     7,     8,     9,
      10,    11,    12,     7,     8,     9,    10,    11,    12,     7,
       8,     9,    10,    11,    12,     7,     8,     9,    10,    11,
      12,    44,    42,    33,    34,    35,    36,    30,    44,    33,
      34,    35,    36,    17,    44,    33,    34,    35,    36,    39,
      44,    33,    34,    35,    36,    41,    44,    24,    29,    25,
      44,    40,    44,     7,     8,     9,    10,    11,    12,     7,
       8,     9,    10,    11,    12,     7,     8,     9,    10,    11,
      12,     8,     0,     1,    47,     3,     4,     5,    47,    33,
      34,    35,    36,    15,    86,    33,    34,    35,    36,    43,
      64,    33,    34,    35,    36,    43,    35,     6,    -1,    -1,
     241,    43,    30,     7,     8,     9,    10,    11,    12,    -1,
     165,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    35,    36
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,     5,    30,    49,    50,    51,    52,
      53,    56,    65,    66,    57,    58,    30,    66,     0,    52,
      38,    30,    35,    62,    63,    62,    39,    59,    38,    30,
      67,    37,    64,    30,    41,    42,    41,     3,     4,     5,
      54,    30,    60,    61,     3,     4,    49,    68,    42,    44,
      29,    37,    63,    30,    35,    55,    55,    30,     3,     4,
       5,    40,    64,    41,    42,    30,    42,    44,    30,    39,
      70,    43,    29,    64,    30,    41,    42,    41,    55,    55,
      55,    30,    41,    61,    49,    70,    71,    43,    30,    35,
      41,    41,    41,    55,    30,     3,     4,     5,    56,    72,
      64,    30,    41,    30,     1,    16,    18,    20,    21,    22,
      23,    26,    27,    28,    30,    35,    40,    69,    70,    73,
      74,    78,    79,    80,    81,    82,    84,    87,    93,    38,
      38,    30,    30,    31,     1,    29,    30,    32,    34,    35,
      38,    46,    74,    75,    85,    38,    41,    38,    41,     6,
      37,    38,    45,    86,    30,    41,     6,    37,    45,    41,
      41,    41,    41,    75,    75,    38,    86,    75,    75,    75,
      30,    74,     7,     8,     9,    10,    11,    12,    33,    34,
      35,    36,    75,    30,    75,    95,    30,    75,    75,    76,
      77,    75,     6,    37,    45,    45,    30,    75,    75,    44,
      44,    76,    44,    86,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    44,    45,    41,    43,    44,    42,
      30,    75,    75,    75,    43,    70,    83,    44,    88,    75,
      75,    96,    75,    43,    17,    70,    39,    41,    70,    24,
      89,    90,    91,    30,    75,    97,    29,    25,    92,    91,
      45,    44,    47,    47,    40,    75,    94,    72,    72,    70
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    49,    50,    51,    51,    52,    52,    52,
      53,    54,    54,    54,    54,    54,    54,    55,    55,    55,
      55,    55,    55,    57,    56,    58,    56,    59,    56,    60,
      60,    61,    61,    62,    62,    63,    63,    63,    64,    64,
      65,    65,    65,    66,    67,    67,    67,    68,    68,    68,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    70,    71,    71,    72,    72,    73,    73,
      73,    73,    74,    74,    74,    74,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    76,    76,
      77,    77,    78,    79,    79,    80,    81,    81,    83,    82,
      84,    85,    86,    86,    88,    87,    89,    89,    90,    90,
      91,    92,    92,    94,    93,    95,    95,    95,    96,    96,
      97,    97,    97
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     2,     1,     1,     1,
       6,     3,     3,     4,     4,     4,     5,     1,     2,     2,
       3,     4,     4,     0,     4,     0,     4,     0,     5,     1,
       3,     1,     2,     1,     3,     1,     2,     2,     3,     4,
       6,     5,     1,     1,     1,     3,     0,     0,     2,     4,
       2,     2,     2,     2,     2,     1,     1,     1,     1,     2,
       2,     1,     1,     4,     0,     2,     0,     2,     3,     4,
       4,     3,     3,     4,     3,     4,     3,     3,     3,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       2,     2,     2,     1,     2,     1,     1,     1,     0,     1,
       1,     3,     2,     2,     2,     2,     5,     7,     0,     6,
       4,     4,     3,     4,     0,     9,     0,     1,     1,     2,
       4,     0,     3,     0,    10,     0,     3,     1,     0,     1,
       0,     3,     1
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
  case 2: /* type_spec: INT  */
#line 83 "mini.y"
{
    decl_dtype = DT_INT;
    (yyval.dtype) = DT_INT;
}
#line 1382 "mini.tab.c"
    break;

  case 3: /* type_spec: CHAR  */
#line 88 "mini.y"
{
    decl_dtype = DT_CHAR;
    (yyval.dtype) = DT_CHAR;
}
#line 1391 "mini.tab.c"
    break;

  case 4: /* program: function_declaration_list  */
#line 97 "mini.y"
{
	tac_last=(yyvsp[0].tac);
	tac_complete();
}
#line 1400 "mini.tab.c"
    break;

  case 6: /* function_declaration_list: function_declaration_list function_declaration  */
#line 107 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
}
#line 1408 "mini.tab.c"
    break;

  case 7: /* function_declaration: function  */
#line 113 "mini.y"
    {
        (yyval.tac) = (yyvsp[0].tac);  /* 返回 TAC* */
    }
#line 1416 "mini.tab.c"
    break;

  case 8: /* function_declaration: declaration  */
#line 117 "mini.y"
    {
        (yyval.tac) = (yyvsp[0].tac);  /* 返回 TAC* */
    }
#line 1424 "mini.tab.c"
    break;

  case 9: /* function_declaration: struct_definition  */
#line 121 "mini.y"
    {
        (yyval.tac) = NULL;  /* 结构体定义不生成 TAC，返回 NULL */
    }
#line 1432 "mini.tab.c"
    break;

  case 10: /* struct_definition: STRUCT IDENTIFIER '{' field_list '}' ';'  */
#line 127 "mini.y"
{
	(yyval.meta) = finalize_struct((yyvsp[-4].string), (yyvsp[-2].meta));
}
#line 1440 "mini.tab.c"
    break;

  case 11: /* field_list: INT field_declarators ';'  */
#line 133 "mini.y"
{
	(yyval.meta) = (yyvsp[-1].meta);
	set_field_type((yyval.meta), FIELD_INT);
}
#line 1449 "mini.tab.c"
    break;

  case 12: /* field_list: CHAR field_declarators ';'  */
#line 138 "mini.y"
{
	(yyval.meta) = (yyvsp[-1].meta);
	set_field_type((yyval.meta), FIELD_CHAR);
}
#line 1458 "mini.tab.c"
    break;

  case 13: /* field_list: STRUCT IDENTIFIER field_declarators ';'  */
#line 143 "mini.y"
{
	(yyval.meta) = (yyvsp[-1].meta);
	set_field_struct_type((yyval.meta), (yyvsp[-2].string));
}
#line 1467 "mini.tab.c"
    break;

  case 14: /* field_list: field_list INT field_declarators ';'  */
#line 148 "mini.y"
{
	(yyval.meta) = append_fields((yyvsp[-3].meta), (yyvsp[-1].meta));
	set_field_type((yyvsp[-1].meta), FIELD_INT);
}
#line 1476 "mini.tab.c"
    break;

  case 15: /* field_list: field_list CHAR field_declarators ';'  */
#line 153 "mini.y"
{
	(yyval.meta) = append_fields((yyvsp[-3].meta), (yyvsp[-1].meta));
	set_field_type((yyvsp[-1].meta), FIELD_CHAR);
}
#line 1485 "mini.tab.c"
    break;

  case 16: /* field_list: field_list STRUCT IDENTIFIER field_declarators ';'  */
#line 158 "mini.y"
{
	(yyval.meta) = append_fields((yyvsp[-4].meta), (yyvsp[-1].meta));
	set_field_struct_type((yyvsp[-1].meta), (yyvsp[-2].string));
}
#line 1494 "mini.tab.c"
    break;

  case 17: /* field_declarators: IDENTIFIER  */
#line 165 "mini.y"
{
	(yyval.meta) = create_field((yyvsp[0].string), NULL, 0);
}
#line 1502 "mini.tab.c"
    break;

  case 18: /* field_declarators: '*' IDENTIFIER  */
#line 169 "mini.y"
{
	(yyval.meta) = create_field_ptr((yyvsp[0].string));
}
#line 1510 "mini.tab.c"
    break;

  case 19: /* field_declarators: IDENTIFIER array_dimensions  */
#line 173 "mini.y"
{
	(yyval.meta) = create_field((yyvsp[-1].string), (yyvsp[0].arr_dims).dims, (yyvsp[0].arr_dims).ndims);
}
#line 1518 "mini.tab.c"
    break;

  case 20: /* field_declarators: field_declarators ',' IDENTIFIER  */
#line 177 "mini.y"
{
	(yyval.meta) = append_field_name((yyvsp[-2].meta), (yyvsp[0].string), NULL, 0);
}
#line 1526 "mini.tab.c"
    break;

  case 21: /* field_declarators: field_declarators ',' '*' IDENTIFIER  */
#line 181 "mini.y"
{
	(yyval.meta) = append_field_name_ptr((yyvsp[-3].meta), (yyvsp[0].string));
}
#line 1534 "mini.tab.c"
    break;

  case 22: /* field_declarators: field_declarators ',' IDENTIFIER array_dimensions  */
#line 185 "mini.y"
{
	(yyval.meta) = append_field_name((yyvsp[-3].meta), (yyvsp[-1].string), (yyvsp[0].arr_dims).dims, (yyvsp[0].arr_dims).ndims);
}
#line 1542 "mini.tab.c"
    break;

  case 23: /* $@1: %empty  */
#line 192 "mini.y"
                  { decl_dtype=DT_INT; }
#line 1548 "mini.tab.c"
    break;

  case 24: /* declaration: INT $@1 variable_list ';'  */
#line 193 "mini.y"
{
    (yyval.tac)=(yyvsp[-1].tac);
}
#line 1556 "mini.tab.c"
    break;

  case 25: /* $@2: %empty  */
#line 196 "mini.y"
       { decl_dtype=DT_CHAR; }
#line 1562 "mini.tab.c"
    break;

  case 26: /* declaration: CHAR $@2 variable_list ';'  */
#line 197 "mini.y"
{
    (yyval.tac)=(yyvsp[-1].tac);
}
#line 1570 "mini.tab.c"
    break;

  case 27: /* $@3: %empty  */
#line 201 "mini.y"
{
	decl_struct = lookup_struct((yyvsp[0].string));
	if(!decl_struct) {
		yyerror("Undefined struct");
	}
}
#line 1581 "mini.tab.c"
    break;

  case 28: /* declaration: STRUCT IDENTIFIER $@3 struct_var_list ';'  */
#line 208 "mini.y"
{
	(yyval.tac)=(yyvsp[-1].tac);
}
#line 1589 "mini.tab.c"
    break;

  case 30: /* struct_var_list: struct_var_list ',' struct_var_declaration  */
#line 215 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-2].tac), (yyvsp[0].tac));
}
#line 1597 "mini.tab.c"
    break;

  case 31: /* struct_var_declaration: IDENTIFIER  */
#line 221 "mini.y"
{
	(yyval.tac)=declare_struct_var((yyvsp[0].string), decl_struct);
}
#line 1605 "mini.tab.c"
    break;

  case 32: /* struct_var_declaration: IDENTIFIER array_dimensions  */
#line 225 "mini.y"
{
	(yyval.tac)=declare_struct_array((yyvsp[-1].string), decl_struct, (yyvsp[0].arr_dims).dims, (yyvsp[0].arr_dims).ndims);
}
#line 1613 "mini.tab.c"
    break;

  case 34: /* variable_list: variable_list ',' variable_declaration  */
#line 233 "mini.y"
{
    (yyval.tac)=join_tac((yyvsp[-2].tac), (yyvsp[0].tac));
}
#line 1621 "mini.tab.c"
    break;

  case 35: /* variable_declaration: IDENTIFIER  */
#line 240 "mini.y"
{
    (yyval.tac)=declare_var((yyvsp[0].string));
}
#line 1629 "mini.tab.c"
    break;

  case 36: /* variable_declaration: '*' IDENTIFIER  */
#line 244 "mini.y"
{
    (yyval.tac)=declare_ptr_var((yyvsp[0].string));
}
#line 1637 "mini.tab.c"
    break;

  case 37: /* variable_declaration: IDENTIFIER array_dimensions  */
#line 248 "mini.y"
{
    (yyval.tac)=declare_array_var((yyvsp[-1].string), (yyvsp[0].arr_dims).dims, (yyvsp[0].arr_dims).ndims);
}
#line 1645 "mini.tab.c"
    break;

  case 38: /* array_dimensions: '[' INTEGER ']'  */
#line 255 "mini.y"
{
    (yyval.arr_dims).dims[0] = atoi((yyvsp[-1].string));
    (yyval.arr_dims).ndims = 1;
}
#line 1654 "mini.tab.c"
    break;

  case 39: /* array_dimensions: array_dimensions '[' INTEGER ']'  */
#line 260 "mini.y"
{
    if ((yyvsp[-3].arr_dims).ndims >= 16) {
        yyerror("Array dimensions exceed maximum (16)");
    }
    (yyval.arr_dims) = (yyvsp[-3].arr_dims);
    (yyval.arr_dims).dims[(yyval.arr_dims).ndims++] = atoi((yyvsp[-1].string));
}
#line 1666 "mini.tab.c"
    break;

  case 40: /* function: type_spec function_head '(' parameter_list_typed ')' block  */
#line 272 "mini.y"
{
    /* 带返回类型的函数 */
    (yyval.tac)=do_func((yyvsp[-4].sym), (yyvsp[-2].tac), (yyvsp[0].tac));
    scope=0; /* Leave local scope. */
    sym_tab_local=NULL; /* Clear local symbol table. */
}
#line 1677 "mini.tab.c"
    break;

  case 41: /* function: function_head '(' parameter_list ')' block  */
#line 279 "mini.y"
{
	(yyval.tac)=do_func((yyvsp[-4].sym), (yyvsp[-2].tac), (yyvsp[0].tac));
	scope=0; /* Leave local scope. */
	sym_tab_local=NULL; /* Clear local symbol table. */
}
#line 1687 "mini.tab.c"
    break;

  case 42: /* function: error  */
#line 285 "mini.y"
{
	error("Bad function syntax");
	(yyval.tac)=NULL;
}
#line 1696 "mini.tab.c"
    break;

  case 43: /* function_head: IDENTIFIER  */
#line 294 "mini.y"
{
	(yyval.sym)=declare_func((yyvsp[0].string));
	scope=1; /* Enter local scope. */
	sym_tab_local=NULL; /* Init local symbol table. */
}
#line 1706 "mini.tab.c"
    break;

  case 44: /* parameter_list: IDENTIFIER  */
#line 304 "mini.y"
{
	(yyval.tac)=declare_para((yyvsp[0].string));
}
#line 1714 "mini.tab.c"
    break;

  case 45: /* parameter_list: parameter_list ',' IDENTIFIER  */
#line 308 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-2].tac), declare_para((yyvsp[0].string)));
}
#line 1722 "mini.tab.c"
    break;

  case 46: /* parameter_list: %empty  */
#line 312 "mini.y"
{
	(yyval.tac)=NULL;
}
#line 1730 "mini.tab.c"
    break;

  case 47: /* parameter_list_typed: %empty  */
#line 318 "mini.y"
{
    (yyval.tac)=NULL;
}
#line 1738 "mini.tab.c"
    break;

  case 48: /* parameter_list_typed: type_spec IDENTIFIER  */
#line 322 "mini.y"
{
    (yyval.tac)=declare_para((yyvsp[0].string));
}
#line 1746 "mini.tab.c"
    break;

  case 49: /* parameter_list_typed: parameter_list_typed ',' type_spec IDENTIFIER  */
#line 326 "mini.y"
{
    (yyval.tac)=join_tac((yyvsp[-3].tac), declare_para((yyvsp[0].string)));
}
#line 1754 "mini.tab.c"
    break;

  case 59: /* statement: BREAK ';'  */
#line 343 "mini.y"
{
	(yyval.tac) = do_break();
}
#line 1762 "mini.tab.c"
    break;

  case 60: /* statement: CONTINUE ';'  */
#line 347 "mini.y"
{
	(yyval.tac) = do_continue();
}
#line 1770 "mini.tab.c"
    break;

  case 62: /* statement: error  */
#line 352 "mini.y"
{
	error("Bad statement syntax");
	(yyval.tac)=NULL;
}
#line 1779 "mini.tab.c"
    break;

  case 63: /* block: '{' declaration_list statement_list '}'  */
#line 361 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-2].tac), (yyvsp[-1].tac));
}
#line 1787 "mini.tab.c"
    break;

  case 64: /* declaration_list: %empty  */
#line 369 "mini.y"
{
	(yyval.tac)=NULL;
}
#line 1795 "mini.tab.c"
    break;

  case 65: /* declaration_list: declaration_list declaration  */
#line 373 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
}
#line 1803 "mini.tab.c"
    break;

  case 66: /* statement_list: %empty  */
#line 381 "mini.y"
{
    (yyval.tac) = NULL;
}
#line 1811 "mini.tab.c"
    break;

  case 67: /* statement_list: statement_list statement  */
#line 385 "mini.y"
{
	(yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
}
#line 1819 "mini.tab.c"
    break;

  case 68: /* assignment_statement: IDENTIFIER '=' expression  */
#line 393 "mini.y"
{
    (yyval.tac)=do_assign(get_var((yyvsp[-2].string)), (yyvsp[0].exp));
}
#line 1827 "mini.tab.c"
    break;

  case 69: /* assignment_statement: '*' IDENTIFIER '=' expression  */
#line 397 "mini.y"
{
    (yyval.tac)=do_deref_write(get_var((yyvsp[-2].string)), (yyvsp[0].exp));
}
#line 1835 "mini.tab.c"
    break;

  case 70: /* assignment_statement: IDENTIFIER index_list '=' expression  */
#line 401 "mini.y"
{
	(yyval.tac) = do_array_write(get_var((yyvsp[-3].string)),(yyvsp[-2].exp_list),(yyvsp[0].exp));
}
#line 1843 "mini.tab.c"
    break;

  case 71: /* assignment_statement: field_access '=' expression  */
#line 405 "mini.y"
{
	(yyval.tac) = do_field_write((yyvsp[-2].field_chain).chain, (yyvsp[0].exp));
}
#line 1851 "mini.tab.c"
    break;

  case 72: /* field_access: IDENTIFIER DOT IDENTIFIER  */
#line 411 "mini.y"
{
	(yyval.field_chain).chain = create_field_access((yyvsp[-2].string), (yyvsp[0].string));
}
#line 1859 "mini.tab.c"
    break;

  case 73: /* field_access: IDENTIFIER index_list DOT IDENTIFIER  */
#line 415 "mini.y"
{
    (yyval.field_chain).chain = create_field_access_array((yyvsp[-3].string), (yyvsp[-2].exp_list), (yyvsp[0].string));
}
#line 1867 "mini.tab.c"
    break;

  case 74: /* field_access: field_access DOT IDENTIFIER  */
#line 419 "mini.y"
{
	(yyval.field_chain).chain = append_field_access((yyvsp[-2].field_chain).chain, (yyvsp[0].string));
}
#line 1875 "mini.tab.c"
    break;

  case 75: /* field_access: field_access '[' expression ']'  */
#line 423 "mini.y"
{
    EXP *single_index = (yyvsp[-1].exp);
    single_index->next = NULL;  /* 确保是单元素列表 */
    (yyval.field_chain).chain = append_array_access((yyvsp[-3].field_chain).chain, single_index);
}
#line 1885 "mini.tab.c"
    break;

  case 76: /* expression: expression '+' expression  */
#line 433 "mini.y"
{
	(yyval.exp)=do_bin(TAC_ADD, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1893 "mini.tab.c"
    break;

  case 77: /* expression: expression '-' expression  */
#line 437 "mini.y"
{
	(yyval.exp)=do_bin(TAC_SUB, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1901 "mini.tab.c"
    break;

  case 78: /* expression: expression '*' expression  */
#line 441 "mini.y"
{
	(yyval.exp)=do_bin(TAC_MUL, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1909 "mini.tab.c"
    break;

  case 79: /* expression: expression '/' expression  */
#line 445 "mini.y"
{
	(yyval.exp)=do_bin(TAC_DIV, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1917 "mini.tab.c"
    break;

  case 80: /* expression: '-' expression  */
#line 449 "mini.y"
{
	(yyval.exp)=do_un(TAC_NEG, (yyvsp[0].exp));
}
#line 1925 "mini.tab.c"
    break;

  case 81: /* expression: expression EQ expression  */
#line 453 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_EQ, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1933 "mini.tab.c"
    break;

  case 82: /* expression: expression NE expression  */
#line 457 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_NE, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1941 "mini.tab.c"
    break;

  case 83: /* expression: expression LT expression  */
#line 461 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_LT, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1949 "mini.tab.c"
    break;

  case 84: /* expression: expression LE expression  */
#line 465 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_LE, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1957 "mini.tab.c"
    break;

  case 85: /* expression: expression GT expression  */
#line 469 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_GT, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1965 "mini.tab.c"
    break;

  case 86: /* expression: expression GE expression  */
#line 473 "mini.y"
{
	(yyval.exp)=do_cmp(TAC_GE, (yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1973 "mini.tab.c"
    break;

  case 87: /* expression: '(' expression ')'  */
#line 477 "mini.y"
{
	(yyval.exp)=(yyvsp[-1].exp);
}
#line 1981 "mini.tab.c"
    break;

  case 88: /* expression: INTEGER  */
#line 481 "mini.y"
{
    (yyval.exp)=mk_exp(NULL, mk_const(atoi((yyvsp[0].string))), NULL);
}
#line 1989 "mini.tab.c"
    break;

  case 89: /* expression: CHARACTER  */
#line 485 "mini.y"
{
    (yyval.exp)=mk_exp(NULL, mk_const((int)(yyvsp[0].character)), NULL);
}
#line 1997 "mini.tab.c"
    break;

  case 90: /* expression: '&' IDENTIFIER  */
#line 489 "mini.y"
{
    (yyval.exp)=do_addr(get_var((yyvsp[0].string)));
}
#line 2005 "mini.tab.c"
    break;

  case 91: /* expression: '&' field_access  */
#line 493 "mini.y"
{
    (yyval.exp)=do_field_addr((yyvsp[0].field_chain).chain);
}
#line 2013 "mini.tab.c"
    break;

  case 92: /* expression: '*' expression  */
#line 497 "mini.y"
{
    (yyval.exp)=do_deref_read((yyvsp[0].exp));
}
#line 2021 "mini.tab.c"
    break;

  case 93: /* expression: IDENTIFIER  */
#line 501 "mini.y"
{
    (yyval.exp)=mk_exp(NULL, get_var((yyvsp[0].string)), NULL);
}
#line 2029 "mini.tab.c"
    break;

  case 94: /* expression: IDENTIFIER index_list  */
#line 505 "mini.y"
{
	(yyval.exp) = do_array_read(get_var((yyvsp[-1].string)), (yyvsp[0].exp_list));
}
#line 2037 "mini.tab.c"
    break;

  case 95: /* expression: field_access  */
#line 509 "mini.y"
{
	(yyval.exp) = do_field_read((yyvsp[0].field_chain).chain);
}
#line 2045 "mini.tab.c"
    break;

  case 96: /* expression: call_expression  */
#line 513 "mini.y"
{
	(yyval.exp)=(yyvsp[0].exp);
}
#line 2053 "mini.tab.c"
    break;

  case 97: /* expression: error  */
#line 517 "mini.y"
{
	error("Bad expression syntax");
	(yyval.exp)=mk_exp(NULL, NULL, NULL);
}
#line 2062 "mini.tab.c"
    break;

  case 98: /* argument_list: %empty  */
#line 526 "mini.y"
{
	(yyval.exp)=NULL;
}
#line 2070 "mini.tab.c"
    break;

  case 101: /* expression_list: expression_list ',' expression  */
#line 536 "mini.y"
{
	(yyvsp[0].exp)->next=(yyvsp[-2].exp);
	(yyval.exp)=(yyvsp[0].exp);
}
#line 2079 "mini.tab.c"
    break;

  case 102: /* input_statement: INPUT IDENTIFIER  */
#line 545 "mini.y"
{
	(yyval.tac)=do_input(get_var((yyvsp[0].string)));
}
#line 2087 "mini.tab.c"
    break;

  case 103: /* output_statement: OUTPUT IDENTIFIER  */
#line 553 "mini.y"
{
	(yyval.tac)=do_output(get_var((yyvsp[0].string)));
}
#line 2095 "mini.tab.c"
    break;

  case 104: /* output_statement: OUTPUT TEXT  */
#line 557 "mini.y"
{
	(yyval.tac)=do_output(mk_text((yyvsp[0].string)));
}
#line 2103 "mini.tab.c"
    break;

  case 105: /* return_statement: RETURN expression  */
#line 565 "mini.y"
{
	TAC *t=mk_tac(TAC_RETURN, (yyvsp[0].exp)->ret, NULL, NULL);
	t->prev=(yyvsp[0].exp)->tac;
	(yyval.tac)=t;
}
#line 2113 "mini.tab.c"
    break;

  case 106: /* if_statement: IF '(' expression ')' block  */
#line 575 "mini.y"
{
	(yyval.tac)=do_if((yyvsp[-2].exp), (yyvsp[0].tac));
}
#line 2121 "mini.tab.c"
    break;

  case 107: /* if_statement: IF '(' expression ')' block ELSE block  */
#line 579 "mini.y"
{
	(yyval.tac)=do_test((yyvsp[-4].exp), (yyvsp[-2].tac), (yyvsp[0].tac));
}
#line 2129 "mini.tab.c"
    break;

  case 108: /* $@4: %empty  */
#line 587 "mini.y"
{
    /* 中间动作：在解析 block 之前设置循环上下文 */
    enter_loop_context();
}
#line 2138 "mini.tab.c"
    break;

  case 109: /* while_statement: WHILE '(' expression ')' $@4 block  */
#line 592 "mini.y"
{
    /* 生成 TAC 并退出上下文 */
    (yyval.tac) = do_while((yyvsp[-3].exp), (yyvsp[0].tac));
    exit_loop_context();
}
#line 2148 "mini.tab.c"
    break;

  case 110: /* call_statement: IDENTIFIER '(' argument_list ')'  */
#line 602 "mini.y"
{
	(yyval.tac)=do_call((yyvsp[-3].string), (yyvsp[-1].exp));
}
#line 2156 "mini.tab.c"
    break;

  case 111: /* call_expression: IDENTIFIER '(' argument_list ')'  */
#line 610 "mini.y"
{
	(yyval.exp)=do_call_ret((yyvsp[-3].string), (yyvsp[-1].exp));
}
#line 2164 "mini.tab.c"
    break;

  case 112: /* index_list: '[' expression ']'  */
#line 617 "mini.y"
{
    (yyval.exp_list) = (yyvsp[-1].exp);
    (yyval.exp_list)->next = NULL;
}
#line 2173 "mini.tab.c"
    break;

  case 113: /* index_list: index_list '[' expression ']'  */
#line 622 "mini.y"
{
    (yyval.exp_list) = (yyvsp[-1].exp);
    (yyval.exp_list)->next = (yyvsp[-3].exp_list);  /* 逆向链接，后续需要反转 */
}
#line 2182 "mini.tab.c"
    break;

  case 114: /* @5: %empty  */
#line 632 "mini.y"
{
    (yyval.sym) = enter_switch();
}
#line 2190 "mini.tab.c"
    break;

  case 115: /* switch_statement: SWITCH '(' expression ')' @5 '{' case_list_opt default_opt '}'  */
#line 636 "mini.y"
{
    (yyval.tac) = exit_switch((yyvsp[-6].exp), (yyvsp[-2].case_list), (yyvsp[-1].tac), (yyvsp[-4].sym));
}
#line 2198 "mini.tab.c"
    break;

  case 116: /* case_list_opt: %empty  */
#line 643 "mini.y"
{
    (yyval.case_list) = NULL;
}
#line 2206 "mini.tab.c"
    break;

  case 117: /* case_list_opt: case_list  */
#line 647 "mini.y"
{
    (yyval.case_list) = (yyvsp[0].case_list);
}
#line 2214 "mini.tab.c"
    break;

  case 118: /* case_list: case_clause  */
#line 654 "mini.y"
{
    (yyval.case_list) = (yyvsp[0].case_list);
}
#line 2222 "mini.tab.c"
    break;

  case 119: /* case_list: case_list case_clause  */
#line 658 "mini.y"
{
    (yyval.case_list) = append_case((yyvsp[-1].case_list), (yyvsp[0].case_list));
}
#line 2230 "mini.tab.c"
    break;

  case 120: /* case_clause: CASE INTEGER ':' statement_list  */
#line 665 "mini.y"
{
    (yyval.case_list) = mk_case(atoi((yyvsp[-2].string)), (yyvsp[0].tac));
}
#line 2238 "mini.tab.c"
    break;

  case 121: /* default_opt: %empty  */
#line 672 "mini.y"
{
    (yyval.tac) = NULL;
}
#line 2246 "mini.tab.c"
    break;

  case 122: /* default_opt: DEFAULT ':' statement_list  */
#line 676 "mini.y"
{
    (yyval.tac) = (yyvsp[0].tac);
}
#line 2254 "mini.tab.c"
    break;

  case 123: /* $@6: %empty  */
#line 683 "mini.y"
{
    /* 中间动作：在解析 block 之前设置循环上下文 */
    enter_loop_context();
}
#line 2263 "mini.tab.c"
    break;

  case 124: /* for_statement: FOR '(' for_init ';' for_cond ';' for_iter ')' $@6 block  */
#line 688 "mini.y"
{
    /* 生成 TAC 并退出上下文 */
    (yyval.tac) = do_for((yyvsp[-7].tac), (yyvsp[-5].exp), (yyvsp[-3].tac), (yyvsp[0].tac));
    exit_loop_context();
}
#line 2273 "mini.tab.c"
    break;

  case 125: /* for_init: %empty  */
#line 696 "mini.y"
{
    (yyval.tac) = NULL;
}
#line 2281 "mini.tab.c"
    break;

  case 126: /* for_init: IDENTIFIER '=' expression  */
#line 700 "mini.y"
{
    (yyval.tac) = do_assign(get_var((yyvsp[-2].string)), (yyvsp[0].exp));
}
#line 2289 "mini.tab.c"
    break;

  case 127: /* for_init: expression  */
#line 704 "mini.y"
{
    (yyval.tac) = (yyvsp[0].exp)->tac;
}
#line 2297 "mini.tab.c"
    break;

  case 128: /* for_cond: %empty  */
#line 710 "mini.y"
{
    (yyval.exp) = NULL;
}
#line 2305 "mini.tab.c"
    break;

  case 129: /* for_cond: expression  */
#line 714 "mini.y"
{
    (yyval.exp) = (yyvsp[0].exp);
}
#line 2313 "mini.tab.c"
    break;

  case 130: /* for_iter: %empty  */
#line 720 "mini.y"
{
    (yyval.tac) = NULL;
}
#line 2321 "mini.tab.c"
    break;

  case 131: /* for_iter: IDENTIFIER '=' expression  */
#line 724 "mini.y"
{
    (yyval.tac) = do_assign(get_var((yyvsp[-2].string)), (yyvsp[0].exp));
}
#line 2329 "mini.tab.c"
    break;

  case 132: /* for_iter: expression  */
#line 728 "mini.y"
{
    (yyval.tac) = (yyvsp[0].exp)->tac;
}
#line 2337 "mini.tab.c"
    break;


#line 2341 "mini.tab.c"

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

#line 734 "mini.y"


/* 语法错误输出：包含行号 */
void yyerror(char* msg) 
{
	fprintf(stderr, "%s: line %d\n", msg, yylineno);
	exit(0);
}
