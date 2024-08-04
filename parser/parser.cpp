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
#line 4 "parser.y"

    #include "../include/AST.hpp"
    #define m_s make_shared
    // #include <cstdio>
    extern int yylex(void);
    extern void yyerror(const char *s);
    extern FILE *yyin;
    extern YYLTYPE yylloc;
    extern CompUnit* root;
    CompUnit* root = nullptr;

#line 83 "parser.cpp"

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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ADD = 3,                        /* ADD  */
  YYSYMBOL_SUB = 4,                        /* SUB  */
  YYSYMBOL_MUL = 5,                        /* MUL  */
  YYSYMBOL_DIV = 6,                        /* DIV  */
  YYSYMBOL_MOD = 7,                        /* MOD  */
  YYSYMBOL_ASSIGN = 8,                     /* ASSIGN  */
  YYSYMBOL_EQ = 9,                         /* EQ  */
  YYSYMBOL_NEQ = 10,                       /* NEQ  */
  YYSYMBOL_LT = 11,                        /* LT  */
  YYSYMBOL_LTE = 12,                       /* LTE  */
  YYSYMBOL_GT = 13,                        /* GT  */
  YYSYMBOL_GTE = 14,                       /* GTE  */
  YYSYMBOL_AND = 15,                       /* AND  */
  YYSYMBOL_OR = 16,                        /* OR  */
  YYSYMBOL_NOT = 17,                       /* NOT  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_ELSE = 19,                      /* ELSE  */
  YYSYMBOL_WHILE = 20,                     /* WHILE  */
  YYSYMBOL_BREAK = 21,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 22,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 23,                    /* RETURN  */
  YYSYMBOL_CONST = 24,                     /* CONST  */
  YYSYMBOL_INT = 25,                       /* INT  */
  YYSYMBOL_VOID = 26,                      /* VOID  */
  YYSYMBOL_FLOAT = 27,                     /* FLOAT  */
  YYSYMBOL_LEFT_PARENTHESES = 28,          /* LEFT_PARENTHESES  */
  YYSYMBOL_RIGHT_PARENTHESES = 29,         /* RIGHT_PARENTHESES  */
  YYSYMBOL_LEFT_BRACKETS = 30,             /* LEFT_BRACKETS  */
  YYSYMBOL_RIGHT_BRACKETS = 31,            /* RIGHT_BRACKETS  */
  YYSYMBOL_LEFT_BRACES = 32,               /* LEFT_BRACES  */
  YYSYMBOL_RIGHT_BRACES = 33,              /* RIGHT_BRACES  */
  YYSYMBOL_COMMA = 34,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 35,                 /* SEMICOLON  */
  YYSYMBOL_IDENTIFIER = 36,                /* IDENTIFIER  */
  YYSYMBOL_INTVAL = 37,                    /* INTVAL  */
  YYSYMBOL_FLOATVAL = 38,                  /* FLOATVAL  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_CompUnit = 40,                  /* CompUnit  */
  YYSYMBOL_Decl = 41,                      /* Decl  */
  YYSYMBOL_ConstDecl = 42,                 /* ConstDecl  */
  YYSYMBOL_ConstDefs = 43,                 /* ConstDefs  */
  YYSYMBOL_BaseType = 44,                  /* BaseType  */
  YYSYMBOL_ConstDef = 45,                  /* ConstDef  */
  YYSYMBOL_ArrayDim = 46,                  /* ArrayDim  */
  YYSYMBOL_VarDecl = 47,                   /* VarDecl  */
  YYSYMBOL_VarDefs = 48,                   /* VarDefs  */
  YYSYMBOL_VarDef = 49,                    /* VarDef  */
  YYSYMBOL_InitVals = 50,                  /* InitVals  */
  YYSYMBOL_ArrayInitVal = 51,              /* ArrayInitVal  */
  YYSYMBOL_FuncDef = 52,                   /* FuncDef  */
  YYSYMBOL_FuncFParams = 53,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 54,                /* FuncFParam  */
  YYSYMBOL_ParamArrayDim = 55,             /* ParamArrayDim  */
  YYSYMBOL_Block = 56,                     /* Block  */
  YYSYMBOL_BlockItems = 57,                /* BlockItems  */
  YYSYMBOL_Stmt = 58,                      /* Stmt  */
  YYSYMBOL_Exp = 59,                       /* Exp  */
  YYSYMBOL_LVal = 60,                      /* LVal  */
  YYSYMBOL_Number = 61,                    /* Number  */
  YYSYMBOL_UnaryExp = 62,                  /* UnaryExp  */
  YYSYMBOL_FuncRParams = 63,               /* FuncRParams  */
  YYSYMBOL_MulExp = 64,                    /* MulExp  */
  YYSYMBOL_AddExp = 65,                    /* AddExp  */
  YYSYMBOL_RelExp = 66,                    /* RelExp  */
  YYSYMBOL_EqExp = 67,                     /* EqExp  */
  YYSYMBOL_LAndExp = 68,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 69,                    /* LOrExp  */
  YYSYMBOL_ConstExp = 70                   /* ConstExp  */
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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   235

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  166

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   124,   124,   129,   134,   140,   147,   153,   161,   168,
     173,   179,   183,   187,   194,   201,   210,   215,   267,   274,
     279,   287,   295,   303,   311,   330,   335,   340,   346,   353,
     359,   367,   377,   391,   396,   403,   410,   419,   424,   431,
     436,   442,   447,   452,   457,   462,   475,   484,   492,   498,
     506,   516,   526,   535,   541,   547,   555,   565,   573,   580,
     600,   608,   620,   624,   628,   632,   641,   649,   653,   659,
     680,   685,   692,   696,   705,   714,   725,   728,   737,   748,
     752,   761,   770,   779,   790,   794,   803,   814,   818,   829,
     833,   844
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
  "\"end of file\"", "error", "\"invalid token\"", "ADD", "SUB", "MUL",
  "DIV", "MOD", "ASSIGN", "EQ", "NEQ", "LT", "LTE", "GT", "GTE", "AND",
  "OR", "NOT", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "RETURN",
  "CONST", "INT", "VOID", "FLOAT", "LEFT_PARENTHESES", "RIGHT_PARENTHESES",
  "LEFT_BRACKETS", "RIGHT_BRACKETS", "LEFT_BRACES", "RIGHT_BRACES",
  "COMMA", "SEMICOLON", "IDENTIFIER", "INTVAL", "FLOATVAL", "$accept",
  "CompUnit", "Decl", "ConstDecl", "ConstDefs", "BaseType", "ConstDef",
  "ArrayDim", "VarDecl", "VarDefs", "VarDef", "InitVals", "ArrayInitVal",
  "FuncDef", "FuncFParams", "FuncFParam", "ParamArrayDim", "Block",
  "BlockItems", "Stmt", "Exp", "LVal", "Number", "UnaryExp", "FuncRParams",
  "MulExp", "AddExp", "RelExp", "EqExp", "LAndExp", "LOrExp", "ConstExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-91)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     193,   183,   -91,   -91,   -91,    38,   -91,   -91,   -25,   -91,
     -91,   -22,   -91,   -91,   -91,    48,    60,   -91,    27,   115,
     -91,   178,    76,   178,    45,   -13,   -91,   178,    50,   -22,
     -91,   178,   178,   178,   178,    -7,   -91,   -91,   -91,    10,
     -91,   -91,   216,   190,    19,    18,    -9,   -91,   190,    36,
      37,   178,    51,   -91,   -91,    37,   -91,   -91,   -91,   -91,
      42,   148,   178,   178,   178,   178,   178,   178,   110,   -91,
      47,    19,   183,   -91,    79,   -91,    56,   -91,   -91,   -91,
     -91,    55,    59,   -91,   -91,   -91,   216,   216,    69,    81,
      83,    94,   163,   -91,   -91,   -91,   -13,   -91,   136,   -91,
     106,    58,    73,   114,   -91,   -91,   -91,   171,   -91,   -91,
     -91,   -91,   178,   -91,   178,   178,   -91,   -91,   -91,   120,
     -91,   -91,   -91,   -91,   -91,   178,   -91,   178,   -91,   175,
     -91,   190,   176,   187,   155,   -10,    23,   -91,   140,   152,
     -91,   -91,   178,   178,   178,   178,   178,   178,   178,   178,
       9,     9,   -91,   -91,   190,   190,   190,   190,   176,   176,
     187,   155,   209,   -91,     9,   -91
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    11,    13,    12,     0,     4,     6,     0,     7,
       5,     0,     1,     2,     3,    21,     0,    19,     0,     0,
       9,     0,     0,     0,    23,     0,    18,     0,     0,     0,
       8,     0,     0,     0,     0,    58,    60,    61,    22,    63,
      64,    72,    76,    57,     0,     0,     0,    33,    91,     0,
       0,     0,    21,    20,    14,     0,    10,    67,    68,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
      35,     0,     0,    16,     0,    24,     0,    15,    62,    65,
      70,     0,     0,    73,    74,    75,    77,    78,     0,     0,
       0,     0,     0,    39,    48,    41,     0,    49,     0,    42,
       0,    63,     0,    36,    31,    34,    30,     0,    26,    25,
      17,    66,     0,    59,     0,     0,    53,    54,    55,     0,
      40,    45,    43,    44,    47,     0,    37,     0,    29,     0,
      71,    79,    84,    87,    89,     0,     0,    56,     0,     0,
      28,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    46,    38,    80,    82,    81,    83,    85,    86,
      88,    90,    50,    52,     0,    51
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -91,   -91,     2,   -91,   -91,     0,   173,   211,   -91,   -91,
     205,   -91,   -50,   226,   -91,   160,   -91,   -35,   -91,   -90,
     -19,   -65,   -91,   -15,   -91,   158,   -23,    80,    85,    86,
     119,   -17
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,    19,     8,    20,    24,     9,    16,
      17,   107,    75,    10,    46,    47,   103,    97,    98,    99,
     100,    39,    40,    41,    81,    42,    43,   132,   133,   134,
     135,    49
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      48,    11,    38,   101,    48,    77,   149,    13,   123,    69,
      54,    15,    31,    32,    18,    60,    57,    58,    59,   150,
      71,    61,    45,    52,   108,    72,    33,    88,    48,    89,
      90,    91,    92,   101,    76,    27,   104,    34,    12,   149,
      62,    68,    80,    82,    94,    35,    36,    37,    83,    84,
      85,    68,   151,    50,    70,   109,    21,    23,    55,    21,
     162,   163,     1,     2,     3,     4,   125,    73,    96,    74,
      95,    78,    45,   119,   165,    51,    22,   102,    23,   140,
      51,    23,    31,    32,   111,   101,   101,   110,    62,   112,
     113,   131,   131,   130,    25,    26,    33,   114,    96,   101,
     122,     2,     3,     4,   126,    44,   138,    34,   139,   115,
     141,    74,   106,    31,    32,    35,    36,    37,   116,   154,
     155,   156,   157,   131,   131,   131,   131,    33,    88,   117,
      89,    90,    91,    92,     1,     2,     3,     4,    34,    31,
      32,   124,    68,    93,   127,    94,    35,    36,    37,    29,
      30,    31,    32,    33,    88,   137,    89,    90,    91,    92,
       1,     2,     3,     4,    34,    33,    31,    32,    68,   120,
     148,   121,    35,    36,    37,   152,    34,    79,    31,    32,
      33,    31,    32,   153,    35,    36,    37,   142,   143,   144,
     145,    34,    33,    66,    67,    33,   146,   147,   118,    35,
      36,    37,    56,    34,   128,   129,    34,    74,     2,     3,
       4,    35,    36,    37,    35,    36,    37,     1,     2,     3,
       4,    63,    64,    65,    86,    87,   158,   159,   164,    28,
      53,    14,   105,   160,   136,   161
};

static const yytype_uint8 yycheck[] =
{
      23,     1,    21,    68,    27,    55,    16,     5,    98,    44,
      27,    36,     3,     4,    36,    34,    31,    32,    33,    29,
      29,    28,    22,    36,    74,    34,    17,    18,    51,    20,
      21,    22,    23,    98,    51,     8,    71,    28,     0,    16,
      30,    32,    61,    62,    35,    36,    37,    38,    63,    64,
      65,    32,    29,     8,    36,    74,     8,    30,     8,     8,
     150,   151,    24,    25,    26,    27,     8,    31,    68,    32,
      68,    29,    72,    92,   164,    30,    28,    30,    30,   129,
      30,    30,     3,     4,    29,   150,   151,    31,    30,    34,
      31,   114,   115,   112,    34,    35,    17,    28,    98,   164,
      98,    25,    26,    27,    31,    29,   125,    28,   127,    28,
     129,    32,    33,     3,     4,    36,    37,    38,    35,   142,
     143,   144,   145,   146,   147,   148,   149,    17,    18,    35,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     3,
       4,    35,    32,    33,    30,    35,    36,    37,    38,    34,
      35,     3,     4,    17,    18,    35,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    17,     3,     4,    32,    33,
      15,    35,    36,    37,    38,    35,    28,    29,     3,     4,
      17,     3,     4,    31,    36,    37,    38,    11,    12,    13,
      14,    28,    17,     3,     4,    17,     9,    10,    35,    36,
      37,    38,    29,    28,    33,    34,    28,    32,    25,    26,
      27,    36,    37,    38,    36,    37,    38,    24,    25,    26,
      27,     5,     6,     7,    66,    67,   146,   147,    19,    18,
      25,     5,    72,   148,   115,   149
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    24,    25,    26,    27,    40,    41,    42,    44,    47,
      52,    44,     0,    41,    52,    36,    48,    49,    36,    43,
      45,     8,    28,    30,    46,    34,    35,     8,    46,    34,
      35,     3,     4,    17,    28,    36,    37,    38,    59,    60,
      61,    62,    64,    65,    29,    44,    53,    54,    65,    70,
       8,    30,    36,    49,    70,     8,    45,    62,    62,    62,
      59,    28,    30,     5,     6,     7,     3,     4,    32,    56,
      36,    29,    34,    31,    32,    51,    70,    51,    29,    29,
      59,    63,    59,    62,    62,    62,    64,    64,    18,    20,
      21,    22,    23,    33,    35,    41,    44,    56,    57,    58,
      59,    60,    30,    55,    56,    54,    33,    50,    51,    59,
      31,    29,    34,    31,    28,    28,    35,    35,    35,    59,
      33,    35,    41,    58,    35,     8,    31,    30,    33,    34,
      59,    65,    66,    67,    68,    69,    69,    35,    59,    59,
      51,    59,    11,    12,    13,    14,     9,    10,    15,    16,
      29,    29,    35,    31,    65,    65,    65,    65,    66,    66,
      67,    68,    58,    58,    19,    58
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    40,    40,    40,    41,    41,    42,    43,
      43,    44,    44,    44,    45,    45,    46,    46,    47,    48,
      48,    49,    49,    49,    49,    50,    50,    50,    50,    51,
      51,    52,    52,    53,    53,    54,    54,    55,    55,    56,
      56,    57,    57,    57,    57,    57,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    59,    60,    60,
      61,    61,    62,    62,    62,    62,    62,    62,    62,    62,
      63,    63,    64,    64,    64,    64,    65,    65,    65,    66,
      66,    66,    66,    66,    67,    67,    67,    68,    68,    69,
      69,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     1,     4,     1,
       3,     1,     1,     1,     3,     4,     3,     4,     3,     1,
       3,     1,     3,     2,     4,     1,     1,     3,     3,     3,
       2,     6,     5,     1,     3,     2,     3,     2,     4,     2,
       3,     1,     1,     2,     2,     2,     4,     2,     1,     1,
       5,     7,     5,     2,     2,     2,     3,     1,     1,     4,
       1,     1,     3,     1,     1,     3,     4,     2,     2,     2,
       1,     3,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1
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
  case 2: /* CompUnit: CompUnit Decl  */
#line 124 "parser.y"
                       {
        (yyval.compUnit) = (yyvsp[-1].compUnit);
        (yyvsp[-1].compUnit) -> addDecl(DeclPtr((yyvsp[0].decl)));
        printf("CompUnit Decl Find\n");
    }
#line 1270 "parser.cpp"
    break;

  case 3: /* CompUnit: CompUnit FuncDef  */
#line 129 "parser.y"
                      {
        (yyval.compUnit) = (yyvsp[-1].compUnit);
        (yyvsp[-1].compUnit) -> addFuncDef(FuncDefPtr((yyvsp[0].funcDef)));
        printf("CompUnit FuncDef Find\n");
    }
#line 1280 "parser.cpp"
    break;

  case 4: /* CompUnit: Decl  */
#line 134 "parser.y"
          {
        root = new CompUnit();
        (yyval.compUnit) = root;
        (yyval.compUnit) -> addDecl(DeclPtr((yyvsp[0].decl)));
        printf("Decl Find\n");
    }
#line 1291 "parser.cpp"
    break;

  case 5: /* CompUnit: FuncDef  */
#line 140 "parser.y"
             {
        root = new CompUnit();
        (yyval.compUnit) = root;
        (yyval.compUnit) -> addFuncDef(FuncDefPtr((yyvsp[0].funcDef)));
        printf("FuncDef Find\n");
    }
#line 1302 "parser.cpp"
    break;

  case 6: /* Decl: ConstDecl  */
#line 147 "parser.y"
               {
        (yyval.decl) = new Decl();
        (yyval.decl) -> _node_type = NodeType::NT_DECL;
        (yyval.decl) -> addConstDecl(ConstDeclPtr((yyvsp[0].constDecl)));
        printf("ConstDecl Find\n");
    }
#line 1313 "parser.cpp"
    break;

  case 7: /* Decl: VarDecl  */
#line 153 "parser.y"
              {
        (yyval.decl) = new Decl();
        (yyval.decl) -> _node_type = NodeType::NT_DECL;
        (yyval.decl) -> addVarDecl(VarDeclPtr((yyvsp[0].varDecl)));
        printf("VarDecl Find\n");
    }
#line 1324 "parser.cpp"
    break;

  case 8: /* ConstDecl: CONST BaseType ConstDefs SEMICOLON  */
#line 161 "parser.y"
                                             {
        (yyval.constDecl) = new ConstDecl();
        (yyval.constDecl) -> addType((yyvsp[-2].type));
        (yyval.constDecl) -> addConstDef(ConstDefsPtr((yyvsp[-1].constDefs)));
        printf("ConstDecl Find\n");
    }
#line 1335 "parser.cpp"
    break;

  case 9: /* ConstDefs: ConstDef  */
#line 168 "parser.y"
                    {
        (yyval.constDefs) = new ConstDefs();
        (yyval.constDefs)->addConstDef(ConstDefPtr((yyvsp[0].constDef)));
        printf("ConstDefs Find\n");
    }
#line 1345 "parser.cpp"
    break;

  case 10: /* ConstDefs: ConstDefs COMMA ConstDef  */
#line 173 "parser.y"
                               {
        (yyval.constDefs) = (yyvsp[-2].constDefs);
        (yyvsp[-2].constDefs) -> addConstDef(ConstDefPtr((yyvsp[0].constDef)));
        printf("ConstDefs Find\n");
    }
#line 1355 "parser.cpp"
    break;

  case 11: /* BaseType: INT  */
#line 179 "parser.y"
             {
        (yyval.type) = BaseType::B_INT;
        printf("INT Token Find\n");
    }
#line 1364 "parser.cpp"
    break;

  case 12: /* BaseType: FLOAT  */
#line 183 "parser.y"
           {
        (yyval.type) = BaseType::B_FLOAT;
        printf("FLOAT Token Find\n");
    }
#line 1373 "parser.cpp"
    break;

  case 13: /* BaseType: VOID  */
#line 187 "parser.y"
           {
        (yyval.type) = BaseType::B_VOID;
        printf("VOID Token Find\n");

    }
#line 1383 "parser.cpp"
    break;

  case 14: /* ConstDef: IDENTIFIER ASSIGN ConstExp  */
#line 194 "parser.y"
                                    {
        (yyval.constDef) = new ConstDef();
        (yyval.constDef) -> addIdentifier((yyvsp[-2].identifier));
        (yyval.constDef) -> addArray(false);
        (yyval.constDef) -> addInitVal(ConstExpPtr((yyvsp[0].constExp)));
        printf("ConstDef Find\n");
    }
#line 1395 "parser.cpp"
    break;

  case 15: /* ConstDef: IDENTIFIER ArrayDim ASSIGN ArrayInitVal  */
#line 201 "parser.y"
                                              {
        (yyval.constDef) = new ConstDef();
        (yyval.constDef) -> addIdentifier((yyvsp[-3].identifier));
        (yyval.constDef) -> addArray(true);
        (yyval.constDef) -> addArrayDim(ArrayDimPtr((yyvsp[-2].arrayDim)));
        (yyval.constDef) -> addArrayInitVal(ArrayInitValPtr((yyvsp[0].arrayInitVal)));
        printf("ConstDef Find\n");
    }
#line 1408 "parser.cpp"
    break;

  case 16: /* ArrayDim: LEFT_BRACKETS ConstExp RIGHT_BRACKETS  */
#line 210 "parser.y"
                                                {
        (yyval.arrayDim) = new ArrayDim();
        (yyval.arrayDim) -> addDim (ConstExpPtr((yyvsp[-1].constExp)));
        printf("ArrayDim Find\n");
    }
#line 1418 "parser.cpp"
    break;

  case 17: /* ArrayDim: ArrayDim LEFT_BRACKETS ConstExp RIGHT_BRACKETS  */
#line 215 "parser.y"
                                                     {
        (yyval.arrayDim) = (yyvsp[-3].arrayDim);
        (yyval.arrayDim) -> addDim(ConstExpPtr((yyvsp[-1].constExp)));
        printf("ArrayDim Find\n");
    }
#line 1428 "parser.cpp"
    break;

  case 18: /* VarDecl: BaseType VarDefs SEMICOLON  */
#line 267 "parser.y"
                                   {
         (yyval.varDecl) = new VarDecl();
         (yyval.varDecl) -> addType((yyvsp[-2].type));
         (yyval.varDecl) -> addVarDefs(VarDefsPtr((yyvsp[-1].varDefs)));
        printf("VarDecl Find\n");
    }
#line 1439 "parser.cpp"
    break;

  case 19: /* VarDefs: VarDef  */
#line 274 "parser.y"
                {
        (yyval.varDefs) = new VarDefs();
        (yyval.varDefs) -> addVarDef(VarDefPtr((yyvsp[0].varDef)));
        printf("VarDefs Find\n");
    }
#line 1449 "parser.cpp"
    break;

  case 20: /* VarDefs: VarDefs COMMA VarDef  */
#line 279 "parser.y"
                           {
        (yyval.varDefs) = (yyvsp[-2].varDefs);
        (yyval.varDefs) -> addVarDef(VarDefPtr((yyvsp[0].varDef))); 
        printf("VarDefs Find\n");
    }
#line 1459 "parser.cpp"
    break;

  case 21: /* VarDef: IDENTIFIER  */
#line 287 "parser.y"
                   {
        // cout<<*($1)<<endl;
        (yyval.varDef) = new VarDef();
        (yyval.varDef) -> addIdentifier((yyvsp[0].identifier));
        (yyval.varDef) -> addInit(false);
        (yyval.varDef) -> addArray(false);
        printf("VarDef Find\n");
    }
#line 1472 "parser.cpp"
    break;

  case 22: /* VarDef: IDENTIFIER ASSIGN Exp  */
#line 295 "parser.y"
                           {
        (yyval.varDef) = new VarDef();
        (yyval.varDef) -> addIdentifier((yyvsp[-2].identifier));
        (yyval.varDef) -> addInit(true);
        (yyval.varDef) -> addInitVal(ExpPtr((yyvsp[0].exp)));
        (yyval.varDef) -> addArray(false);
        printf("VarDef Find\n");
    }
#line 1485 "parser.cpp"
    break;

  case 23: /* VarDef: IDENTIFIER ArrayDim  */
#line 303 "parser.y"
                          {
        (yyval.varDef) = new VarDef();
        (yyval.varDef) -> addIdentifier((yyvsp[-1].identifier));
        (yyval.varDef) -> addArrayDim(ArrayDimPtr((yyvsp[0].arrayDim)));
        (yyval.varDef) -> addInit(false);
        (yyval.varDef) -> addArray(true);
        printf("VarDef Find\n");
    }
#line 1498 "parser.cpp"
    break;

  case 24: /* VarDef: IDENTIFIER ArrayDim ASSIGN ArrayInitVal  */
#line 311 "parser.y"
                                             {
        (yyval.varDef) = new VarDef();
        (yyval.varDef) -> addIdentifier((yyvsp[-3].identifier));
        (yyval.varDef) -> addArrayDim(ArrayDimPtr((yyvsp[-2].arrayDim)));
        (yyval.varDef) -> addArrayInitVal(ArrayInitValPtr((yyvsp[0].arrayInitVal)));
        (yyval.varDef) -> addInit(true);
        (yyval.varDef) -> addArray(true);
        printf("VarDef Find\n");
    }
#line 1512 "parser.cpp"
    break;

  case 25: /* InitVals: Exp  */
#line 330 "parser.y"
              {
        (yyval.initVals) = new InitVals();
        (yyval.initVals) -> addExp(ExpPtr((yyvsp[0].exp)));
        printf("InitVals Find\n");  
    }
#line 1522 "parser.cpp"
    break;

  case 26: /* InitVals: ArrayInitVal  */
#line 335 "parser.y"
                   {
        (yyval.initVals) = new InitVals();
        (yyval.initVals) -> addExp(ExpPtr((yyvsp[0].arrayInitVal)));
        printf("InitVals Find\n");
    }
#line 1532 "parser.cpp"
    break;

  case 27: /* InitVals: InitVals COMMA Exp  */
#line 340 "parser.y"
                         {
        (yyval.initVals) = (yyvsp[-2].initVals);
        (yyval.initVals) -> addExp(ExpPtr((yyvsp[0].exp)));
        printf("InitVals Find\n");
        
    }
#line 1543 "parser.cpp"
    break;

  case 28: /* InitVals: InitVals COMMA ArrayInitVal  */
#line 346 "parser.y"
                                  {
        (yyval.initVals) = (yyvsp[-2].initVals);
        (yyval.initVals) -> addExp(ExpPtr((yyvsp[0].arrayInitVal)));
        printf("InitVals Find\n");
    }
#line 1553 "parser.cpp"
    break;

  case 29: /* ArrayInitVal: LEFT_BRACES InitVals RIGHT_BRACES  */
#line 353 "parser.y"
                                                {
        (yyval.arrayInitVal) = new ArrayInitVal();
        (yyval.arrayInitVal) -> addDimVal(InitValsPtr((yyvsp[-1].initVals)));
        (yyval.arrayInitVal) -> addType(ExpType::ET_DIM);
        printf("ArrayInitVal Find\n");
    }
#line 1564 "parser.cpp"
    break;

  case 30: /* ArrayInitVal: LEFT_BRACES RIGHT_BRACES  */
#line 359 "parser.y"
                               {
        (yyval.arrayInitVal) = new ArrayInitVal();
        (yyval.arrayInitVal) -> addDimVal(InitValsPtr(nullptr));
        (yyval.arrayInitVal) -> addType(ExpType::ET_DIM);
        printf("ArrayInitVal Find\n");
    }
#line 1575 "parser.cpp"
    break;

  case 31: /* FuncDef: BaseType IDENTIFIER LEFT_PARENTHESES FuncFParams RIGHT_PARENTHESES Block  */
#line 367 "parser.y"
                                                                                 {
        (yyval.funcDef) = new FuncDef();
        (yyval.funcDef) -> _node_type = NodeType::NT_FUNC;
        (yyval.funcDef) -> addReturnType((yyvsp[-5].type));
        (yyval.funcDef) -> addIdentifier((yyvsp[-4].identifier));
        (yyval.funcDef) -> addParam(true);
        (yyval.funcDef) -> addFuncFParams(FuncFParamsPtr((yyvsp[-2].funcFParams)));
        (yyval.funcDef) -> addBlock(BlockPtr((yyvsp[0].block)));
        printf("FuncDef Find\n");
    }
#line 1590 "parser.cpp"
    break;

  case 32: /* FuncDef: BaseType IDENTIFIER LEFT_PARENTHESES RIGHT_PARENTHESES Block  */
#line 377 "parser.y"
                                                                  {
        (yyval.funcDef) = new FuncDef();
        (yyval.funcDef) -> _node_type = NodeType::NT_FUNC;
        (yyval.funcDef) -> addReturnType((yyvsp[-4].type));
        (yyval.funcDef) -> addIdentifier((yyvsp[-3].identifier));
        (yyval.funcDef) -> addParam(false);
        (yyval.funcDef) -> addBlock(BlockPtr((yyvsp[0].block)));
        (yyval.funcDef) -> addFuncFParams(nullptr);
        printf("FuncDef Find\n");
    }
#line 1605 "parser.cpp"
    break;

  case 33: /* FuncFParams: FuncFParam  */
#line 391 "parser.y"
                        {
        (yyval.funcFParams) = new FuncFParams();
        (yyval.funcFParams) -> addFuncFParam(FuncFParamPtr((yyvsp[0].funcFParam)));
        printf("FuncFParams Find\n");
    }
#line 1615 "parser.cpp"
    break;

  case 34: /* FuncFParams: FuncFParams COMMA FuncFParam  */
#line 396 "parser.y"
                                  {
        (yyval.funcFParams) = (yyvsp[-2].funcFParams);
        (yyval.funcFParams) -> addFuncFParam(FuncFParamPtr((yyvsp[0].funcFParam)));
        printf("FuncFParams Find\n");
    }
#line 1625 "parser.cpp"
    break;

  case 35: /* FuncFParam: BaseType IDENTIFIER  */
#line 403 "parser.y"
                                {
        (yyval.funcFParam) = new FuncFParam();
        (yyval.funcFParam) -> addType((yyvsp[-1].type));
        (yyval.funcFParam) -> addIdentifier((yyvsp[0].identifier));
        (yyval.funcFParam) -> addArray(false);
        printf("FuncFParam Find\n");
    }
#line 1637 "parser.cpp"
    break;

  case 36: /* FuncFParam: BaseType IDENTIFIER ParamArrayDim  */
#line 410 "parser.y"
                                        {
        (yyval.funcFParam) = new FuncFParam();
        (yyval.funcFParam) -> addType((yyvsp[-2].type));
        (yyval.funcFParam) -> addIdentifier((yyvsp[-1].identifier));
        (yyval.funcFParam) -> addArray(true);
        (yyval.funcFParam) -> addArrayDim(ParamArrayDimPtr((yyvsp[0].paramArrayDim)));
        printf("FuncFParam Find\n");
    }
#line 1650 "parser.cpp"
    break;

  case 37: /* ParamArrayDim: LEFT_BRACKETS RIGHT_BRACKETS  */
#line 419 "parser.y"
                                            {
        (yyval.paramArrayDim) = new ParamArrayDim();
        (yyval.paramArrayDim) -> addDim(nullptr);
        printf("ParamArrayDim Find\n");
    }
#line 1660 "parser.cpp"
    break;

  case 38: /* ParamArrayDim: ParamArrayDim LEFT_BRACKETS Exp RIGHT_BRACKETS  */
#line 424 "parser.y"
                                                     {
        (yyval.paramArrayDim) = (yyvsp[-3].paramArrayDim);
        (yyval.paramArrayDim) -> addDim(ExpPtr((yyvsp[-1].exp)));
        printf("ParamArrayDim Find\n");
    }
#line 1670 "parser.cpp"
    break;

  case 39: /* Block: LEFT_BRACES RIGHT_BRACES  */
#line 431 "parser.y"
                                {
        (yyval.block) = new Block();
        (yyval.block) -> addBlockItem(BlockItemsPtr(nullptr));
        printf("Empty Block Find\n");
    }
#line 1680 "parser.cpp"
    break;

  case 40: /* Block: LEFT_BRACES BlockItems RIGHT_BRACES  */
#line 436 "parser.y"
                                         {
        (yyval.block) = new Block();
        (yyval.block) -> addBlockItem(BlockItemsPtr((yyvsp[-1].blockItems)));
        printf("Block Find\n");
    }
#line 1690 "parser.cpp"
    break;

  case 41: /* BlockItems: Decl  */
#line 442 "parser.y"
                 {
        (yyval.blockItems) = new BlockItems();
        (yyval.blockItems) -> addDecl(DeclPtr((yyvsp[0].decl)));
        printf("BlockItems Find\n");
    }
#line 1700 "parser.cpp"
    break;

  case 42: /* BlockItems: Stmt  */
#line 447 "parser.y"
           {
        (yyval.blockItems) = new BlockItems();
        (yyval.blockItems) -> addStmt(StmtPtr((yyvsp[0].stmt)));
        printf("BlockItems Find\n");
    }
#line 1710 "parser.cpp"
    break;

  case 43: /* BlockItems: BlockItems Decl  */
#line 452 "parser.y"
                      {
        (yyval.blockItems) = (yyvsp[-1].blockItems);
        (yyval.blockItems) -> addDecl(DeclPtr((yyvsp[0].decl)));
        printf("BlockItems Find\n");
    }
#line 1720 "parser.cpp"
    break;

  case 44: /* BlockItems: BlockItems Stmt  */
#line 457 "parser.y"
                      {
        (yyval.blockItems) = (yyvsp[-1].blockItems);
        (yyval.blockItems) -> addStmt(StmtPtr((yyvsp[0].stmt)));
        printf("BlockItems Find\n");
    }
#line 1730 "parser.cpp"
    break;

  case 45: /* BlockItems: BlockItems SEMICOLON  */
#line 462 "parser.y"
                           {
        (yyval.blockItems) = (yyvsp[-1].blockItems);
        printf("BlockItems Find\n");
    }
#line 1739 "parser.cpp"
    break;

  case 46: /* Stmt: LVal ASSIGN Exp SEMICOLON  */
#line 475 "parser.y"
                                {
        AssignStmt* assign = new AssignStmt();
        assign -> addLVal(LValPtr((yyvsp[-3].lVal)));
        assign -> addExp(ExpPtr((yyvsp[-1].exp)));
        (yyval.stmt) = (Stmt*)(assign);
        (yyval.stmt) -> addType(StmtType::ST_ASSIGN);
        (yyval.stmt) -> _node_type = NodeType::NT_STMT;
        printf("Assign Stmt Find\n");
    }
#line 1753 "parser.cpp"
    break;

  case 47: /* Stmt: Exp SEMICOLON  */
#line 484 "parser.y"
                    {
        ExpStmt* exp = new ExpStmt();
        exp -> addExp(ExpPtr((yyvsp[-1].exp)));
        (yyval.stmt) = (Stmt*)(exp);
        (yyval.stmt) -> addType(StmtType::ST_EXP);
        (yyval.stmt) -> _node_type = NodeType::NT_STMT;
        printf("Exp Stmt Find\n");
    }
#line 1766 "parser.cpp"
    break;

  case 48: /* Stmt: SEMICOLON  */
#line 492 "parser.y"
                {
        (yyval.stmt) = new Stmt();
        (yyval.stmt) -> addType(StmtType::ST_BLANK);
        (yyval.stmt) -> _node_type = NodeType::NT_STMT;
        printf("Blank Stmt Find\n");
    }
#line 1777 "parser.cpp"
    break;

  case 49: /* Stmt: Block  */
#line 498 "parser.y"
            {
        BlockStmt* block = new BlockStmt();
        block -> addBlock(BlockPtr((yyvsp[0].block)));
        (yyval.stmt) = (Stmt*)(block);
        (yyval.stmt) -> addType(StmtType::ST_BLOCK);
        (yyval.stmt) -> _node_type = NodeType::NT_STMT;
        printf("Block Stmt Find\n");
    }
#line 1790 "parser.cpp"
    break;

  case 50: /* Stmt: IF LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt  */
#line 506 "parser.y"
                                                        {
        IfElseStmt* ifelsestmt = new IfElseStmt();
        ifelsestmt -> addCond(ExpPtr((yyvsp[-2].lOrExp)));
        ifelsestmt -> addThenStmt(StmtPtr((yyvsp[0].stmt)));
        ifelsestmt -> addElseStmt(StmtPtr(nullptr));
        (yyval.stmt) = (Stmt*)(ifelsestmt);
        (yyval.stmt) -> addType(StmtType::ST_IF);
        (yyval.stmt) -> _node_type = NodeType::NT_STMT;
        printf("If Stmt Find\n");
    }
#line 1805 "parser.cpp"
    break;

  case 51: /* Stmt: IF LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt ELSE Stmt  */
#line 516 "parser.y"
                                                                  {
        IfElseStmt* ifelsestmt = new IfElseStmt();
        ifelsestmt -> addCond(ExpPtr((yyvsp[-4].lOrExp)));
        ifelsestmt -> addThenStmt(StmtPtr((yyvsp[-2].stmt)));
        ifelsestmt -> addElseStmt(StmtPtr((yyvsp[0].stmt)));
        (yyval.stmt) = (Stmt*)(ifelsestmt);
        (yyval.stmt) -> addType(StmtType::ST_IF);
        (yyval.stmt) -> _node_type = NodeType::NT_STMT;
        printf("If Else Stmt Find\n");
    }
#line 1820 "parser.cpp"
    break;

  case 52: /* Stmt: WHILE LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt  */
#line 526 "parser.y"
                                                           {
        WhileStmt* whilestmt = new WhileStmt();
        whilestmt -> addCond(ExpPtr((yyvsp[-2].lOrExp)));
        whilestmt -> addStmt(StmtPtr((yyvsp[0].stmt)));
        (yyval.stmt) = (Stmt*)(whilestmt);
        (yyval.stmt) -> addType(StmtType::ST_WHILE);
        (yyval.stmt) -> _node_type = NodeType::NT_STMT;
        printf("While Stmt Find\n");
    }
#line 1834 "parser.cpp"
    break;

  case 53: /* Stmt: BREAK SEMICOLON  */
#line 535 "parser.y"
                     {
        (yyval.stmt) = new Stmt();
        (yyval.stmt) -> addType(StmtType::ST_BREAK);
        (yyval.stmt) -> _node_type = NodeType::NT_STMT;
        printf("Break Stmt Find\n");
    }
#line 1845 "parser.cpp"
    break;

  case 54: /* Stmt: CONTINUE SEMICOLON  */
#line 541 "parser.y"
                         {
        (yyval.stmt) = new Stmt();
        (yyval.stmt) -> addType(StmtType::ST_CONTINUE);
        (yyval.stmt) -> _node_type = NodeType::NT_STMT;
        printf("Continue Stmt Find\n");
    }
#line 1856 "parser.cpp"
    break;

  case 55: /* Stmt: RETURN SEMICOLON  */
#line 547 "parser.y"
                       {
        ReturnStmt* returnstmt = new ReturnStmt();
        returnstmt -> addExp(nullptr);
        (yyval.stmt) = (Stmt*)(returnstmt);
        (yyval.stmt) -> addType(StmtType::ST_RETURN);
        (yyval.stmt) -> _node_type = NodeType::NT_STMT;
        printf("Return Stmt Find\n");
    }
#line 1869 "parser.cpp"
    break;

  case 56: /* Stmt: RETURN Exp SEMICOLON  */
#line 555 "parser.y"
                           {
        ReturnStmt* returnstmt = new ReturnStmt();
        returnstmt -> addExp(ExpPtr((yyvsp[-1].exp)));
        (yyval.stmt) = (Stmt*)(returnstmt);
        (yyval.stmt) -> addType(StmtType::ST_RETURN);
        (yyval.stmt) -> _node_type = NodeType::NT_STMT;
        printf("Return Stmt Find\n");
    }
#line 1882 "parser.cpp"
    break;

  case 57: /* Exp: AddExp  */
#line 565 "parser.y"
            {
        (yyval.exp) = (yyvsp[0].addExp);
        printf("Exp Find\n");
    }
#line 1891 "parser.cpp"
    break;

  case 58: /* LVal: IDENTIFIER  */
#line 573 "parser.y"
                 {
        (yyval.lVal) = new LVal();
        (yyval.lVal) -> addIdentifier((yyvsp[0].identifier));
        (yyval.lVal) -> addIsArray(false);
        (yyval.lVal) -> addType(ExpType::ET_LVAL);
        printf("LVal Find\n");
    }
#line 1903 "parser.cpp"
    break;

  case 59: /* LVal: LVal LEFT_BRACKETS Exp RIGHT_BRACKETS  */
#line 580 "parser.y"
                                            {
        (yyval.lVal) = (yyvsp[-3].lVal);
        (yyval.lVal) -> addIsArray(true);
        (yyval.lVal) -> addDims(ExpPtr((yyvsp[-1].exp)));
        (yyval.lVal) -> addType(ExpType::ET_LVAL);
        printf("LVal Find\n");
    }
#line 1915 "parser.cpp"
    break;

  case 60: /* Number: INTVAL  */
#line 600 "parser.y"
                {
        (yyval.number) = new Number(0, 0, false);
        (yyval.number) -> addIntVal((yyvsp[0].intVal));
        (yyval.number) -> addFloatVal(float((yyvsp[0].intVal)));
        (yyval.number) -> addIsFloat(false);
        (yyval.number) -> addType(ExpType::ET_INT);
        printf("%d, %f, Number Find\n", (yyval.number) -> getIntVal(), (yyval.number) -> getFloatVal());
    }
#line 1928 "parser.cpp"
    break;

  case 61: /* Number: FLOATVAL  */
#line 608 "parser.y"
               {
        (yyval.number) = new Number(0, 0, false);
        (yyval.number) -> addFloatVal((yyvsp[0].floatVal));
        (yyval.number) -> addIntVal(int((yyvsp[0].floatVal)));
        (yyval.number) -> addIsFloat(true);
        (yyval.number) -> addType(ExpType::ET_FLOAT);
        printf("%d, %f, Number Find\n", (yyval.number) -> getIntVal(), (yyval.number) -> getFloatVal());
        
    }
#line 1942 "parser.cpp"
    break;

  case 62: /* UnaryExp: LEFT_PARENTHESES Exp RIGHT_PARENTHESES  */
#line 620 "parser.y"
                                                 {
        (yyval.unaryExp) = (yyvsp[-1].exp);
        printf("UnaryExp Find\n");
    }
#line 1951 "parser.cpp"
    break;

  case 63: /* UnaryExp: LVal  */
#line 624 "parser.y"
           {
        (yyval.unaryExp) = (Exp*)((yyvsp[0].lVal));
        printf("UnaryExp Find\n");
    }
#line 1960 "parser.cpp"
    break;

  case 64: /* UnaryExp: Number  */
#line 628 "parser.y"
             {
        (yyval.unaryExp) = (Exp*)((yyvsp[0].number));
        printf("UnaryExp Find\n");
    }
#line 1969 "parser.cpp"
    break;

  case 65: /* UnaryExp: IDENTIFIER LEFT_PARENTHESES RIGHT_PARENTHESES  */
#line 632 "parser.y"
                                                    {
        auto tmp = new FuncCall();
        tmp -> addIdentifier((yyvsp[-2].identifier));
        (yyval.unaryExp) = (Exp*)(tmp);
        (yyval.unaryExp) -> addType(ExpType::ET_FUNC); 

        
        printf("UnaryExp Find\n");
    }
#line 1983 "parser.cpp"
    break;

  case 66: /* UnaryExp: IDENTIFIER LEFT_PARENTHESES FuncRParams RIGHT_PARENTHESES  */
#line 641 "parser.y"
                                                               {
        auto tmp = new FuncCall();
        tmp -> addIdentifier((yyvsp[-3].identifier));
        tmp -> addArgs(FuncRParamsPtr((yyvsp[-1].funcRParams)));
        (yyval.unaryExp) = (Exp*)(tmp); 
        (yyval.unaryExp) -> addType(ExpType::ET_FUNC); 
        printf("UnaryExp Find\n");
    }
#line 1996 "parser.cpp"
    break;

  case 67: /* UnaryExp: ADD UnaryExp  */
#line 649 "parser.y"
                  {
        (yyval.unaryExp) = (yyvsp[0].unaryExp);
        printf("UnaryExp Find\n");
    }
#line 2005 "parser.cpp"
    break;

  case 68: /* UnaryExp: SUB UnaryExp  */
#line 653 "parser.y"
                  {
        (yyval.unaryExp) = (yyvsp[0].unaryExp);
        (yyval.unaryExp) -> addNeg();
        printf("UnaryExp Find\n");
        
    }
#line 2016 "parser.cpp"
    break;

  case 69: /* UnaryExp: NOT UnaryExp  */
#line 659 "parser.y"
                  {
        (yyval.unaryExp) = (yyvsp[0].unaryExp);
        (yyval.unaryExp) -> addNot();
        printf("UnaryExp Find\n");
    }
#line 2026 "parser.cpp"
    break;

  case 70: /* FuncRParams: Exp  */
#line 680 "parser.y"
                 {
        (yyval.funcRParams) = new FuncRParams();
        (yyval.funcRParams) -> addArgs(ExpPtr((yyvsp[0].exp)));
        printf("FuncRParams Find\n");
    }
#line 2036 "parser.cpp"
    break;

  case 71: /* FuncRParams: FuncRParams COMMA Exp  */
#line 685 "parser.y"
                            {
        (yyval.funcRParams) = (yyvsp[-2].funcRParams);
        (yyval.funcRParams) -> addArgs(ExpPtr((yyvsp[0].exp)));
        printf("FuncRParams Find\n");
    }
#line 2046 "parser.cpp"
    break;

  case 72: /* MulExp: UnaryExp  */
#line 692 "parser.y"
                 {
        (yyval.mulExp) = (yyvsp[0].unaryExp);
        printf("MulExp Find\n");
    }
#line 2055 "parser.cpp"
    break;

  case 73: /* MulExp: MulExp MUL UnaryExp  */
#line 696 "parser.y"
                          {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].mulExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].unaryExp)));
        tmp -> addOp(BinOpType::OP_MUL);
        tmp -> addType(ExpType::ET_BIN);
        (yyval.mulExp) = (Exp*)(tmp);
        printf("MulExp Find\n");
    }
#line 2069 "parser.cpp"
    break;

  case 74: /* MulExp: MulExp DIV UnaryExp  */
#line 705 "parser.y"
                          {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].mulExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].unaryExp)));
        tmp -> addOp(BinOpType::OP_DIV);
        (yyval.mulExp) = (Exp*)(tmp);
        (yyval.mulExp) -> addType(ExpType::ET_BIN);
        printf("MulExp Find\n");
    }
#line 2083 "parser.cpp"
    break;

  case 75: /* MulExp: MulExp MOD UnaryExp  */
#line 714 "parser.y"
                          {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].mulExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].unaryExp)));
        tmp -> addOp(BinOpType::OP_MOD);
        (yyval.mulExp) = (Exp*)(tmp);
        (yyval.mulExp) -> addType(ExpType::ET_BIN);
        printf("MulExp Find\n");
    }
#line 2097 "parser.cpp"
    break;

  case 76: /* AddExp: MulExp  */
#line 725 "parser.y"
               {
         (yyval.addExp) = (yyvsp[0].mulExp);
    }
#line 2105 "parser.cpp"
    break;

  case 77: /* AddExp: AddExp ADD MulExp  */
#line 728 "parser.y"
                        {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].addExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].mulExp)));
        tmp -> addOp(BinOpType::OP_ADD);
        (yyval.addExp) = (Exp*)(tmp);
        (yyval.addExp) -> addType(ExpType::ET_BIN);
        printf("AddExp Find\n");
    }
#line 2119 "parser.cpp"
    break;

  case 78: /* AddExp: AddExp SUB MulExp  */
#line 737 "parser.y"
                        {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].addExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].mulExp)));
        tmp -> addOp(BinOpType::OP_SUB);
        (yyval.addExp) = (Exp*)(tmp);
        (yyval.addExp) -> addType(ExpType::ET_BIN);
        printf("AddExp Find\n");
    }
#line 2133 "parser.cpp"
    break;

  case 79: /* RelExp: AddExp  */
#line 748 "parser.y"
               {
        (yyval.relExp) = (yyvsp[0].addExp);
        printf("RelExp Find\n");
    }
#line 2142 "parser.cpp"
    break;

  case 80: /* RelExp: RelExp LT AddExp  */
#line 752 "parser.y"
                       {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].relExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].addExp)));
        tmp -> addOp(BinOpType::OP_LT);
        (yyval.relExp) = (Exp*)(tmp);
        (yyval.relExp) -> addType(ExpType::ET_BIN);
        printf("RelExp Find\n");
    }
#line 2156 "parser.cpp"
    break;

  case 81: /* RelExp: RelExp GT AddExp  */
#line 761 "parser.y"
                       {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].relExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].addExp)));
        tmp -> addOp(BinOpType::OP_GT);
        (yyval.relExp) = (Exp*)(tmp);
        (yyval.relExp) -> addType(ExpType::ET_BIN);
        printf("RelExp Find\n");
    }
#line 2170 "parser.cpp"
    break;

  case 82: /* RelExp: RelExp LTE AddExp  */
#line 770 "parser.y"
                        {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].relExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].addExp)));
        tmp -> addOp(BinOpType::OP_LTE);
        (yyval.relExp) = (Exp*)(tmp);
        (yyval.relExp) -> addType(ExpType::ET_BIN);
        printf("RelExp Find\n");
    }
#line 2184 "parser.cpp"
    break;

  case 83: /* RelExp: RelExp GTE AddExp  */
#line 779 "parser.y"
                        {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].relExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].addExp)));
        tmp -> addOp(BinOpType::OP_GTE);
        (yyval.relExp) = (Exp*)(tmp);
        (yyval.relExp) -> addType(ExpType::ET_BIN);
        printf("RelExp Find\n");
    }
#line 2198 "parser.cpp"
    break;

  case 84: /* EqExp: RelExp  */
#line 790 "parser.y"
              {
        (yyval.eqExp) = (yyvsp[0].relExp);
        printf("EqExp Find\n");
    }
#line 2207 "parser.cpp"
    break;

  case 85: /* EqExp: EqExp EQ RelExp  */
#line 794 "parser.y"
                      {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].eqExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].relExp)));
        tmp -> addOp(BinOpType::OP_EQ);
        (yyval.eqExp) = (Exp*)(tmp);
        (yyval.eqExp) -> addType(ExpType::ET_BIN);
        printf("EqExp Find\n");
    }
#line 2221 "parser.cpp"
    break;

  case 86: /* EqExp: EqExp NEQ RelExp  */
#line 803 "parser.y"
                       {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].eqExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].relExp)));
        tmp -> addOp(BinOpType::OP_NEQ);
        (yyval.eqExp) = (Exp*)(tmp);
        (yyval.eqExp) -> addType(ExpType::ET_BIN);
        printf("EqExp Find\n");
    }
#line 2235 "parser.cpp"
    break;

  case 87: /* LAndExp: EqExp  */
#line 814 "parser.y"
               {
        (yyval.lAndExp) = (yyvsp[0].eqExp);
        printf("LAndExp Find\n");
    }
#line 2244 "parser.cpp"
    break;

  case 88: /* LAndExp: LAndExp AND EqExp  */
#line 818 "parser.y"
                        {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].lAndExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].eqExp)));
        tmp -> addOp(BinOpType::OP_AND);
        (yyval.lAndExp) = (Exp*)(tmp);
        (yyval.lAndExp) -> addType(ExpType::ET_BIN);
        printf("LAndExp Find\n");
    }
#line 2258 "parser.cpp"
    break;

  case 89: /* LOrExp: LAndExp  */
#line 829 "parser.y"
                {
        (yyval.lOrExp) = (yyvsp[0].lAndExp);
        printf("LOrExp Find\n");
    }
#line 2267 "parser.cpp"
    break;

  case 90: /* LOrExp: LOrExp OR LAndExp  */
#line 833 "parser.y"
                        {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].lOrExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].lAndExp)));
        tmp -> addOp(BinOpType::OP_OR);
        (yyval.lOrExp) = (Exp*)(tmp);
        (yyval.lOrExp) -> addType(ExpType::ET_BIN);
        printf("LOrExp Find\n");
    }
#line 2281 "parser.cpp"
    break;

  case 91: /* ConstExp: AddExp  */
#line 844 "parser.y"
                 {
        (yyval.constExp) = new ConstExp();
        (yyval.constExp) -> addExp(ExpPtr((yyvsp[0].addExp)));
        printf("ConstExp Find\n");
    }
#line 2291 "parser.cpp"
    break;


#line 2295 "parser.cpp"

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

#line 849 "parser.y"



/* int main(int argc, char *argv[]){
    ++ argv;
    if (argc > 0) yyin = fopen(argv[0], "r");
    else {
        printf("No input file\n");
        return 0;
    }
    yyparse();
    std::cout << root << std::endl;
    return 0;
} */

CompUnit* parse(char *filename) {
    yyin = fopen(filename, "r");
    yyparse();
    return root;
}

void yyerror(const char* s) {
    printf("line:%d\tcolumn:%d\n", yylloc.first_line, yylloc.first_column);
    /* char line[1024]={0};
    for (int i=1;i<=yylloc.first_line;i++) {
        fgets(line, 1024, yyin);
    }
    printf("%s\n", line); */
    printf("ERROR: %s\n", s);
}








