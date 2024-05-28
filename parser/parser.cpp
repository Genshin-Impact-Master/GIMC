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
#line 4 "paser.y"

    #include "../include/AST.hpp"
    #define m_s make_shared
    // #include <cstdio>
    extern int yylex(void);
    extern void yyerror(const char *s);
    extern FILE *yyin;

#line 80 "parser.cpp"

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
  YYSYMBOL_ConstInitVals = 47,             /* ConstInitVals  */
  YYSYMBOL_ConstArrayInitVal = 48,         /* ConstArrayInitVal  */
  YYSYMBOL_VarDecl = 49,                   /* VarDecl  */
  YYSYMBOL_VarDefs = 50,                   /* VarDefs  */
  YYSYMBOL_VarDef = 51,                    /* VarDef  */
  YYSYMBOL_InitVals = 52,                  /* InitVals  */
  YYSYMBOL_ArrayInitVal = 53,              /* ArrayInitVal  */
  YYSYMBOL_FuncDef = 54,                   /* FuncDef  */
  YYSYMBOL_FuncFParams = 55,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 56,                /* FuncFParam  */
  YYSYMBOL_Block = 57,                     /* Block  */
  YYSYMBOL_BlockItems = 58,                /* BlockItems  */
  YYSYMBOL_BlockItem = 59,                 /* BlockItem  */
  YYSYMBOL_Stmt = 60,                      /* Stmt  */
  YYSYMBOL_Exp = 61,                       /* Exp  */
  YYSYMBOL_Cond = 62,                      /* Cond  */
  YYSYMBOL_LVal = 63,                      /* LVal  */
  YYSYMBOL_PrimaryExp = 64,                /* PrimaryExp  */
  YYSYMBOL_Number = 65,                    /* Number  */
  YYSYMBOL_UnaryExp = 66,                  /* UnaryExp  */
  YYSYMBOL_UnaryOp = 67,                   /* UnaryOp  */
  YYSYMBOL_FuncRParams = 68,               /* FuncRParams  */
  YYSYMBOL_MulExp = 69,                    /* MulExp  */
  YYSYMBOL_AddExp = 70,                    /* AddExp  */
  YYSYMBOL_RelExp = 71,                    /* RelExp  */
  YYSYMBOL_EqExp = 72,                     /* EqExp  */
  YYSYMBOL_LAndExp = 73,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 74,                    /* LOrExp  */
  YYSYMBOL_ConstExp = 75                   /* ConstExp  */
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
#define YYLAST   261

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  172

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
       0,   124,   124,   129,   134,   139,   145,   150,   157,   164,
     169,   175,   179,   183,   190,   197,   206,   211,   223,   228,
     234,   239,   244,   252,   259,   266,   271,   279,   287,   295,
     303,   322,   327,   332,   337,   342,   350,   357,   361,   369,
     372,   377,   382,   385,   388,   393,   396,   405,   408,   411,
     414,   417,   420,   423,   426,   429,   432,   437,   442,   447,
     452,   455,   458,   463,   466,   472,   475,   478,   481,   486,
     489,   492,   497,   500,   505,   508,   511,   514,   519,   522,
     525,   530,   533,   536,   539,   542,   547,   550,   553,   558,
     561,   566,   569,   574
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
  "ArrayDim", "ConstInitVals", "ConstArrayInitVal", "VarDecl", "VarDefs",
  "VarDef", "InitVals", "ArrayInitVal", "FuncDef", "FuncFParams",
  "FuncFParam", "Block", "BlockItems", "BlockItem", "Stmt", "Exp", "Cond",
  "LVal", "PrimaryExp", "Number", "UnaryExp", "UnaryOp", "FuncRParams",
  "MulExp", "AddExp", "RelExp", "EqExp", "LAndExp", "LOrExp", "ConstExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-134)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     213,   116,  -134,  -134,  -134,   199,  -134,  -134,   -11,  -134,
    -134,    19,  -134,  -134,  -134,     3,   -18,  -134,    10,    17,
    -134,   193,   207,   193,    49,    22,  -134,   193,    67,    19,
    -134,  -134,  -134,  -134,   193,    38,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,   193,   209,    99,   -19,    47,   -15,  -134,
      99,    43,    58,   193,    70,  -134,  -134,    61,  -134,    78,
      44,  -134,    59,   193,   193,   193,   193,   154,  -134,  -134,
     -19,   116,  -134,    32,  -134,   106,    81,  -134,  -134,  -134,
    -134,    16,  -134,  -134,  -134,   209,   209,   111,   119,   124,
     127,   166,  -134,  -134,    22,  -134,   128,  -134,  -134,  -134,
     165,  -134,  -134,  -134,   100,   159,  -134,  -134,  -134,   134,
     161,  -134,  -134,   193,   193,   193,  -134,  -134,  -134,   185,
    -134,  -134,   193,  -134,    84,   193,  -134,   181,   193,  -134,
     171,    99,   194,   178,   220,   206,   216,  -134,   211,   214,
    -134,   208,   215,  -134,   210,     6,   193,   193,   193,   193,
     193,   193,   193,   193,     6,  -134,  -134,  -134,   193,  -134,
    -134,   193,  -134,    99,    99,    99,    99,   194,   194,   178,
     220,  -134
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    11,    13,    12,     0,     4,     6,     0,     7,
       5,     0,     1,     2,     3,    27,     0,    25,     0,     0,
       9,     0,     0,     0,    29,     0,    24,     0,     0,     0,
       8,    69,    70,    71,     0,    59,    63,    64,    28,    61,
      65,    62,    74,     0,    78,    57,     0,     0,     0,    39,
      93,     0,     0,     0,    27,    26,    14,     0,    10,     0,
       0,    68,     0,     0,     0,     0,     0,     0,    38,    41,
       0,     0,    16,     0,    30,     0,     0,    15,    60,    66,
      72,     0,    75,    76,    77,    79,    80,     0,     0,     0,
       0,     0,    48,    45,     0,    50,     0,    43,    46,    49,
      61,    37,    40,    34,     0,     0,    31,    17,    21,     0,
       0,    18,    67,     0,     0,     0,    53,    54,    55,     0,
      42,    44,     0,    33,     0,     0,    20,     0,     0,    73,
       0,    81,    86,    89,    91,    58,     0,    56,     0,     0,
      32,     0,     0,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    47,    35,    36,     0,    22,
      23,     0,    51,    82,    84,    83,    85,    87,    88,    90,
      92,    52
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -134,  -134,    89,  -134,  -134,     0,   221,   231,   123,   -73,
    -134,  -134,   227,   129,   -68,   248,  -134,   184,   -31,  -134,
     160,  -133,   -14,   142,   -59,  -134,  -134,    72,   196,  -134,
     146,   -23,    77,   107,   108,  -134,   -21
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,    93,     7,    19,     8,    20,    24,   109,    77,
       9,    16,    17,   104,    74,    10,    48,    49,    95,    96,
      97,    98,    99,   130,    39,    40,    41,    42,    43,    81,
      44,    45,   132,   133,   134,   135,   111
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      50,    11,    51,   110,    50,   105,    56,    38,   100,    31,
      32,    21,   162,    67,    70,    68,    25,    26,    27,    71,
      59,   171,    47,    33,    87,    15,    88,    89,    90,    91,
      50,    22,    75,    23,    34,    31,    32,   100,    67,   101,
      23,    92,    35,    36,    37,   112,    80,    31,    32,    33,
     113,    29,    30,    50,   142,    18,   139,    52,    54,   106,
      34,    33,    31,    32,    73,   103,    60,    94,    35,    36,
      37,    47,    34,    79,    72,    57,    33,   119,    21,    53,
      35,    36,    37,    69,    31,    32,   100,    31,    32,     6,
      73,   131,   131,    76,    13,   100,    94,    53,    33,   129,
      23,    33,    65,    66,    50,    50,   143,    78,   138,    34,
     140,   106,    34,    76,   108,    61,    73,    35,    36,    37,
      35,    36,    37,   163,   164,   165,   166,   131,   131,   131,
     131,    31,    32,   123,   124,    83,    84,   107,    50,   114,
     143,     2,     3,     4,   140,    33,    87,   115,    88,    89,
      90,    91,     1,     2,     3,     4,    34,    31,    32,   116,
      67,   120,   117,    92,    35,    36,    37,   126,   127,    31,
      32,    33,    87,   122,    88,    89,    90,    91,     1,     2,
       3,     4,    34,    33,    31,    32,    67,   150,   151,    92,
      35,    36,    37,   125,    34,   128,    31,    32,    33,    12,
     145,   118,    35,    36,    37,   146,   147,   148,   149,    34,
      33,    85,    86,    76,    62,    63,    64,    35,    36,    37,
     137,    34,   153,     1,     2,     3,     4,   167,   168,    35,
      36,    37,     2,     3,     4,   152,    46,     1,     2,     3,
       4,   157,   158,   160,   161,   154,   155,   156,   159,    28,
      58,   144,    55,    14,   141,   102,   121,   136,    82,   169,
       0,   170
};

static const yytype_int16 yycheck[] =
{
      23,     1,    23,    76,    27,    73,    27,    21,    67,     3,
       4,     8,   145,    32,    29,    46,    34,    35,     8,    34,
      34,   154,    22,    17,    18,    36,    20,    21,    22,    23,
      53,    28,    53,    30,    28,     3,     4,    96,    32,    70,
      30,    35,    36,    37,    38,    29,    60,     3,     4,    17,
      34,    34,    35,    76,   127,    36,   124,     8,    36,    73,
      28,    17,     3,     4,    32,    33,    28,    67,    36,    37,
      38,    71,    28,    29,    31,     8,    17,    91,     8,    30,
      36,    37,    38,    36,     3,     4,   145,     3,     4,     0,
      32,   114,   115,    32,     5,   154,    96,    30,    17,   113,
      30,    17,     3,     4,   127,   128,   127,    29,   122,    28,
     124,   125,    28,    32,    33,    43,    32,    36,    37,    38,
      36,    37,    38,   146,   147,   148,   149,   150,   151,   152,
     153,     3,     4,    33,    34,    63,    64,    31,   161,    28,
     161,    25,    26,    27,   158,    17,    18,    28,    20,    21,
      22,    23,    24,    25,    26,    27,    28,     3,     4,    35,
      32,    33,    35,    35,    36,    37,    38,    33,    34,     3,
       4,    17,    18,     8,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    17,     3,     4,    32,     9,    10,    35,
      36,    37,    38,    34,    28,    34,     3,     4,    17,     0,
      29,    35,    36,    37,    38,    11,    12,    13,    14,    28,
      17,    65,    66,    32,     5,     6,     7,    36,    37,    38,
      35,    28,    16,    24,    25,    26,    27,   150,   151,    36,
      37,    38,    25,    26,    27,    15,    29,    24,    25,    26,
      27,    33,    34,    33,    34,    29,    35,    33,    33,    18,
      29,   128,    25,     5,   125,    71,    96,   115,    62,   152,
      -1,   153
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    24,    25,    26,    27,    40,    41,    42,    44,    49,
      54,    44,     0,    41,    54,    36,    50,    51,    36,    43,
      45,     8,    28,    30,    46,    34,    35,     8,    46,    34,
      35,     3,     4,    17,    28,    36,    37,    38,    61,    63,
      64,    65,    66,    67,    69,    70,    29,    44,    55,    56,
      70,    75,     8,    30,    36,    51,    75,     8,    45,    61,
      28,    66,     5,     6,     7,     3,     4,    32,    57,    36,
      29,    34,    31,    32,    53,    75,    32,    48,    29,    29,
      61,    68,    67,    66,    66,    69,    69,    18,    20,    21,
      22,    23,    35,    41,    44,    57,    58,    59,    60,    61,
      63,    57,    56,    33,    52,    53,    61,    31,    33,    47,
      48,    75,    29,    34,    28,    28,    35,    35,    35,    61,
      33,    59,     8,    33,    34,    34,    33,    34,    34,    61,
      62,    70,    71,    72,    73,    74,    62,    35,    61,    53,
      61,    52,    48,    75,    47,    29,    11,    12,    13,    14,
       9,    10,    15,    16,    29,    35,    33,    33,    34,    33,
      33,    34,    60,    70,    70,    70,    70,    71,    71,    72,
      73,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    40,    40,    40,    41,    41,    42,    43,
      43,    44,    44,    44,    45,    45,    46,    46,    47,    47,
      48,    48,    48,    48,    49,    50,    50,    51,    51,    51,
      51,    52,    52,    53,    53,    53,    53,    54,    54,    55,
      55,    56,    57,    58,    58,    59,    59,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    61,    62,    63,
      64,    64,    64,    65,    65,    66,    66,    66,    66,    67,
      67,    67,    68,    68,    69,    69,    69,    69,    70,    70,
      70,    71,    71,    71,    71,    71,    72,    72,    72,    73,
      73,    74,    74,    75
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     1,     4,     1,
       3,     1,     1,     1,     3,     4,     3,     4,     1,     3,
       3,     2,     5,     5,     3,     1,     3,     1,     3,     2,
       4,     1,     3,     3,     2,     5,     5,     6,     5,     1,
       3,     2,     3,     1,     2,     1,     1,     4,     1,     1,
       1,     5,     5,     2,     2,     2,     3,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     3,     4,     2,     1,
       1,     1,     1,     3,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1
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
#line 124 "paser.y"
                       {
        (yyval.compUnit) = (yyvsp[-1].compUnit);
        (yyvsp[-1].compUnit) -> addDecl(DeclPtr((yyvsp[0].decl)));
        printf("CompUnit Decl Find\n");
    }
#line 1282 "parser.cpp"
    break;

  case 3: /* CompUnit: CompUnit FuncDef  */
#line 129 "paser.y"
                      {
        (yyval.compUnit) = (yyvsp[-1].compUnit);
        (yyvsp[-1].compUnit) -> addFuncDef(FuncDefPtr((yyvsp[0].funcDef)));
        printf("CompUnit FuncDef Find\n");
    }
#line 1292 "parser.cpp"
    break;

  case 4: /* CompUnit: Decl  */
#line 134 "paser.y"
          {
        (yyval.compUnit) = new CompUnit();
        (yyval.compUnit) -> addDecl(DeclPtr((yyvsp[0].decl)));
        printf("Decl Find\n");
    }
#line 1302 "parser.cpp"
    break;

  case 5: /* CompUnit: FuncDef  */
#line 139 "paser.y"
             {
        (yyval.compUnit) = new CompUnit();
        (yyval.compUnit) -> addFuncDef(FuncDefPtr((yyvsp[0].funcDef)));
        printf("FuncDef Find\n");
    }
#line 1312 "parser.cpp"
    break;

  case 6: /* Decl: ConstDecl  */
#line 145 "paser.y"
               {
        (yyval.decl) = new Decl();
        (yyval.decl) -> addConstDecl(ConstDeclPtr((yyvsp[0].constDecl)));
        printf("ConstDecl Find\n");
    }
#line 1322 "parser.cpp"
    break;

  case 7: /* Decl: VarDecl  */
#line 150 "paser.y"
              {
        (yyval.decl) = new Decl();
        (yyval.decl) -> addVarDecl(VarDeclPtr((yyvsp[0].varDecl)));
        printf("VarDecl Find\n");
    }
#line 1332 "parser.cpp"
    break;

  case 8: /* ConstDecl: CONST BaseType ConstDefs SEMICOLON  */
#line 157 "paser.y"
                                             {
        (yyval.constDecl) = new ConstDecl();
        (yyval.constDecl) -> addType((yyvsp[-2].type));
        (yyval.constDecl) -> addConstDef(ConstDefsPtr((yyvsp[-1].constDefs)));
        printf("ConstDecl Find\n");
    }
#line 1343 "parser.cpp"
    break;

  case 9: /* ConstDefs: ConstDef  */
#line 164 "paser.y"
                    {
        (yyval.constDefs) = new ConstDefs();
        (yyval.constDefs)->addConstDef(ConstDefPtr((yyvsp[0].constDef)));
        printf("ConstDefs Find\n");
    }
#line 1353 "parser.cpp"
    break;

  case 10: /* ConstDefs: ConstDefs COMMA ConstDef  */
#line 169 "paser.y"
                               {
        (yyval.constDefs) = (yyvsp[-2].constDefs);
        (yyvsp[-2].constDefs) -> addConstDef(ConstDefPtr((yyvsp[0].constDef)));
        printf("ConstDefs Find\n");
    }
#line 1363 "parser.cpp"
    break;

  case 11: /* BaseType: INT  */
#line 175 "paser.y"
             {
        (yyval.type) = BaseType::B_INT;
        printf("INT Token Find\n");
    }
#line 1372 "parser.cpp"
    break;

  case 12: /* BaseType: FLOAT  */
#line 179 "paser.y"
           {
        (yyval.type) = BaseType::B_FLOAT;
        printf("FLOAT Token Find\n");
    }
#line 1381 "parser.cpp"
    break;

  case 13: /* BaseType: VOID  */
#line 183 "paser.y"
           {
        (yyval.type) = BaseType::B_VOID;
        printf("VOID Token Find\n");

    }
#line 1391 "parser.cpp"
    break;

  case 14: /* ConstDef: IDENTIFIER ASSIGN ConstExp  */
#line 190 "paser.y"
                                    {
        (yyval.constDef) = new ConstDef();
        (yyval.constDef) -> addIdentifier((yyvsp[-2].identifier));
        (yyval.constDef) -> addArray(false);
        (yyval.constDef) -> addInitVal(ConstExpPtr((yyvsp[0].constExp)));
        printf("ConstDef Find\n");
    }
#line 1403 "parser.cpp"
    break;

  case 15: /* ConstDef: IDENTIFIER ArrayDim ASSIGN ConstArrayInitVal  */
#line 197 "paser.y"
                                                   {
        (yyval.constDef) = new ConstDef();
        // $$ -> addIdentifier($1);
        (yyval.constDef) -> addArray(true);
        (yyval.constDef) -> addArrayDim(ArrayDimPtr((yyvsp[-2].arrayDim)));
        // $$ -> addArrayInitVal(ConstArrayInitValPtr($4));
        printf("ConstDef Find\n");
    }
#line 1416 "parser.cpp"
    break;

  case 16: /* ArrayDim: LEFT_BRACKETS ConstExp RIGHT_BRACKETS  */
#line 206 "paser.y"
                                                {
        (yyval.arrayDim) = new ArrayDim();
        (yyval.arrayDim) -> addDim (ConstExpPtr((yyvsp[-1].constExp)));
        printf("ArrayDim Find\n");
    }
#line 1426 "parser.cpp"
    break;

  case 17: /* ArrayDim: ArrayDim LEFT_BRACKETS ConstExp RIGHT_BRACKETS  */
#line 211 "paser.y"
                                                     {
        (yyval.arrayDim) = (yyvsp[-3].arrayDim);
        (yyval.arrayDim) -> addDim(ConstExpPtr((yyvsp[-1].constExp)));
        printf("ArrayDim Find\n");
    }
#line 1436 "parser.cpp"
    break;

  case 18: /* ConstInitVals: ConstExp  */
#line 223 "paser.y"
                        {
        (yyval.constInitVals) = new ConstInitVals();
        (yyval.constInitVals) -> addConstExp(ConstExpPtr((yyvsp[0].constExp)));
        printf("ConstInitVals Find\n");
    }
#line 1446 "parser.cpp"
    break;

  case 19: /* ConstInitVals: ConstInitVals COMMA ConstExp  */
#line 228 "paser.y"
                                   {
        (yyval.constInitVals) = (yyvsp[-2].constInitVals);
        (yyval.constInitVals) -> addConstExp(ConstExpPtr((yyvsp[0].constExp)));
        printf("ConstInitVals Find\n");
    }
#line 1456 "parser.cpp"
    break;

  case 20: /* ConstArrayInitVal: LEFT_BRACES ConstInitVals RIGHT_BRACES  */
#line 234 "paser.y"
                                                          {
        (yyval.constArrayInitVal) = new ConstArrayInitVal();
        (yyval.constArrayInitVal) -> addDimVal(ConstInitValsPtr((yyvsp[-1].constInitVals)));
        printf("ConsttInitVal Find\n");
    }
#line 1466 "parser.cpp"
    break;

  case 21: /* ConstArrayInitVal: LEFT_BRACES RIGHT_BRACES  */
#line 239 "paser.y"
                               {
        (yyval.constArrayInitVal) = new ConstArrayInitVal();
        (yyval.constArrayInitVal) -> addDimVal(ConstInitValsPtr(nullptr));
        printf("ConstArrayInitVal Find\n");
    }
#line 1476 "parser.cpp"
    break;

  case 22: /* ConstArrayInitVal: LEFT_BRACES ConstInitVals COMMA ConstArrayInitVal RIGHT_BRACES  */
#line 244 "paser.y"
                                                                     {
        (yyval.constArrayInitVal) = new ConstArrayInitVal();
        (yyval.constArrayInitVal) -> addDimVal(ConstInitValsPtr((yyvsp[-3].constInitVals)));
        auto tmp = (yyvsp[-1].constArrayInitVal) -> getDimVal();
        for (auto initvals: tmp) (yyval.constArrayInitVal) -> addDimVal(initvals);
        delete (yyvsp[-1].constArrayInitVal);
        printf("ConstArrayInitVal Find\n");
    }
#line 1489 "parser.cpp"
    break;

  case 23: /* ConstArrayInitVal: LEFT_BRACES ConstArrayInitVal COMMA ConstInitVals RIGHT_BRACES  */
#line 252 "paser.y"
                                                                     {
        (yyval.constArrayInitVal) = (yyvsp[-3].constArrayInitVal);
        (yyvsp[-3].constArrayInitVal) -> addDimVal(ConstInitValsPtr((yyvsp[-1].constInitVals)));
        printf("ConstArrayInitVal Find\n");
    }
#line 1499 "parser.cpp"
    break;

  case 24: /* VarDecl: BaseType VarDefs SEMICOLON  */
#line 259 "paser.y"
                                   {
         (yyval.varDecl) = new VarDecl();
         (yyval.varDecl) -> addType((yyvsp[-2].type));
         (yyval.varDecl) -> addVarDefs(VarDefsPtr((yyvsp[-1].varDefs)));
        printf("VarDecl Find\n");
    }
#line 1510 "parser.cpp"
    break;

  case 25: /* VarDefs: VarDef  */
#line 266 "paser.y"
                {
        (yyval.varDefs) = new VarDefs();
        (yyval.varDefs) -> addVarDef(VarDefPtr((yyvsp[0].varDef)));
        printf("VarDefs Find\n");
    }
#line 1520 "parser.cpp"
    break;

  case 26: /* VarDefs: VarDefs COMMA VarDef  */
#line 271 "paser.y"
                           {
        (yyval.varDefs) = (yyvsp[-2].varDefs);
        (yyval.varDefs) -> addVarDef(VarDefPtr((yyvsp[0].varDef))); 
        printf("VarDefs Find\n");
    }
#line 1530 "parser.cpp"
    break;

  case 27: /* VarDef: IDENTIFIER  */
#line 279 "paser.y"
                   {
        cout<<*((yyvsp[0].identifier))<<endl;
        (yyval.varDef) = new VarDef();
        (yyval.varDef) -> addIdentifier((yyvsp[0].identifier));
        (yyval.varDef) -> addInit(false);
        (yyval.varDef) -> addArray(false);
        printf("VarDef Find\n");
    }
#line 1543 "parser.cpp"
    break;

  case 28: /* VarDef: IDENTIFIER ASSIGN Exp  */
#line 287 "paser.y"
                           {
        (yyval.varDef) = new VarDef();
        (yyval.varDef) -> addIdentifier((yyvsp[-2].identifier));
        (yyval.varDef) -> addInit(true);
        (yyval.varDef) -> addInitVal(ExpPtr((yyvsp[0].exp)));
        (yyval.varDef) -> addArray(false);
        printf("VarDef Find\n");
    }
#line 1556 "parser.cpp"
    break;

  case 29: /* VarDef: IDENTIFIER ArrayDim  */
#line 295 "paser.y"
                          {
        (yyval.varDef) = new VarDef();
        (yyval.varDef) -> addIdentifier((yyvsp[-1].identifier));
        (yyval.varDef) -> addArrayDim(ArrayDimPtr((yyvsp[0].arrayDim)));
        (yyval.varDef) -> addInit(false);
        (yyval.varDef) -> addArray(true);
        printf("VarDef Find\n");
    }
#line 1569 "parser.cpp"
    break;

  case 30: /* VarDef: IDENTIFIER ArrayDim ASSIGN ArrayInitVal  */
#line 303 "paser.y"
                                             {
        (yyval.varDef) = new VarDef();
        (yyval.varDef) -> addIdentifier((yyvsp[-3].identifier));
        (yyval.varDef) -> addArrayDim(ArrayDimPtr((yyvsp[-2].arrayDim)));
        (yyval.varDef) -> addArrayInitVal(ArrayInitValPtr((yyvsp[0].arrayInitVal)));
        (yyval.varDef) -> addInit(true);
        (yyval.varDef) -> addArray(true);
        printf("VarDef Find\n");
    }
#line 1583 "parser.cpp"
    break;

  case 31: /* InitVals: Exp  */
#line 322 "paser.y"
              {
        (yyval.initVals) = new InitVals();
        (yyval.initVals) -> addExp(ExpPtr((yyvsp[0].exp)));
        printf("InitVals Find\n");  
    }
#line 1593 "parser.cpp"
    break;

  case 32: /* InitVals: InitVals COMMA Exp  */
#line 327 "paser.y"
                         {
        (yyval.initVals) = (yyvsp[-2].initVals);
        (yyval.initVals) -> addExp(ExpPtr((yyvsp[0].exp)));
        printf("InitVals Find\n");
    }
#line 1603 "parser.cpp"
    break;

  case 33: /* ArrayInitVal: LEFT_BRACES InitVals RIGHT_BRACES  */
#line 332 "paser.y"
                                                {
        (yyval.arrayInitVal) = new ArrayInitVal();
        (yyval.arrayInitVal) -> addDimVal(InitValsPtr((yyvsp[-1].initVals)));
        printf("ArrayInitVal Find\n");
    }
#line 1613 "parser.cpp"
    break;

  case 34: /* ArrayInitVal: LEFT_BRACES RIGHT_BRACES  */
#line 337 "paser.y"
                               {
        (yyval.arrayInitVal) = new ArrayInitVal();
        (yyval.arrayInitVal) -> addDimVal(InitValsPtr(nullptr));
        printf("ArrayInitVal Find\n");
    }
#line 1623 "parser.cpp"
    break;

  case 35: /* ArrayInitVal: LEFT_BRACES InitVals COMMA ArrayInitVal RIGHT_BRACES  */
#line 342 "paser.y"
                                                           {
        (yyval.arrayInitVal) = new ArrayInitVal();
        (yyval.arrayInitVal) -> addDimVal(InitValsPtr((yyvsp[-3].initVals)));
        auto tmp = (yyvsp[-1].arrayInitVal) -> getDimVal();
        for (auto initvals: tmp) (yyval.arrayInitVal) -> addDimVal(initvals);
        delete (yyvsp[-1].arrayInitVal);
        printf("ArrayInitVal Find\n");
    }
#line 1636 "parser.cpp"
    break;

  case 36: /* ArrayInitVal: LEFT_BRACES ArrayInitVal COMMA InitVals RIGHT_BRACES  */
#line 350 "paser.y"
                                                           {
        (yyval.arrayInitVal) = (yyvsp[-3].arrayInitVal);
        (yyvsp[-3].arrayInitVal) -> addDimVal(InitValsPtr((yyvsp[-1].initVals)));
        printf("ArrayInitVal Find\n");
    }
#line 1646 "parser.cpp"
    break;

  case 37: /* FuncDef: BaseType IDENTIFIER LEFT_PARENTHESES FuncFParams RIGHT_PARENTHESES Block  */
#line 357 "paser.y"
                                                                                 {
        (yyval.funcDef) = new FuncDef();
        printf("FuncDef Find\n");
    }
#line 1655 "parser.cpp"
    break;

  case 38: /* FuncDef: BaseType IDENTIFIER LEFT_PARENTHESES RIGHT_PARENTHESES Block  */
#line 361 "paser.y"
                                                                  {
        (yyval.funcDef) = new FuncDef();
        printf("FuncDef Find\n");
    }
#line 1664 "parser.cpp"
    break;

  case 39: /* FuncFParams: FuncFParam  */
#line 369 "paser.y"
                        {
        printf("FuncFParams Find\n");
    }
#line 1672 "parser.cpp"
    break;

  case 40: /* FuncFParams: FuncFParams COMMA FuncFParam  */
#line 372 "paser.y"
                                  {
        printf("FuncFParams Find\n");
    }
#line 1680 "parser.cpp"
    break;

  case 41: /* FuncFParam: BaseType IDENTIFIER  */
#line 377 "paser.y"
                                {
        printf("FuncFParam Find\n");
    }
#line 1688 "parser.cpp"
    break;

  case 42: /* Block: LEFT_BRACES BlockItems RIGHT_BRACES  */
#line 382 "paser.y"
                                          {
        printf("Block Find\n");
    }
#line 1696 "parser.cpp"
    break;

  case 43: /* BlockItems: BlockItem  */
#line 385 "paser.y"
                      {
        printf("BlockItems Find\n");
    }
#line 1704 "parser.cpp"
    break;

  case 44: /* BlockItems: BlockItems BlockItem  */
#line 388 "paser.y"
                           {
        printf("BlockItems Find\n");
    }
#line 1712 "parser.cpp"
    break;

  case 45: /* BlockItem: Decl  */
#line 393 "paser.y"
                {
        printf("Block Item Find\n");
    }
#line 1720 "parser.cpp"
    break;

  case 46: /* BlockItem: Stmt  */
#line 396 "paser.y"
           {
        printf("Block Item Find\n");
    }
#line 1728 "parser.cpp"
    break;

  case 47: /* Stmt: LVal ASSIGN Exp SEMICOLON  */
#line 405 "paser.y"
                                {
        printf("Stmt Find\n");
    }
#line 1736 "parser.cpp"
    break;

  case 48: /* Stmt: SEMICOLON  */
#line 408 "paser.y"
                {
        printf("Stmt Find\n");
    }
#line 1744 "parser.cpp"
    break;

  case 49: /* Stmt: Exp  */
#line 411 "paser.y"
          {
        printf("Stmt Find\n");
    }
#line 1752 "parser.cpp"
    break;

  case 50: /* Stmt: Block  */
#line 414 "paser.y"
            {
        printf("Stmt Find\n");
    }
#line 1760 "parser.cpp"
    break;

  case 51: /* Stmt: IF LEFT_PARENTHESES Cond RIGHT_PARENTHESES Stmt  */
#line 417 "paser.y"
                                                      {
        printf("Stmt Find\n");
    }
#line 1768 "parser.cpp"
    break;

  case 52: /* Stmt: WHILE LEFT_PARENTHESES Cond RIGHT_PARENTHESES Stmt  */
#line 420 "paser.y"
                                                         {
        printf("Stmt Find\n");
    }
#line 1776 "parser.cpp"
    break;

  case 53: /* Stmt: BREAK SEMICOLON  */
#line 423 "paser.y"
                     {
        printf("Stmt Find\n");
    }
#line 1784 "parser.cpp"
    break;

  case 54: /* Stmt: CONTINUE SEMICOLON  */
#line 426 "paser.y"
                         {
        printf("Stmt Find\n");
    }
#line 1792 "parser.cpp"
    break;

  case 55: /* Stmt: RETURN SEMICOLON  */
#line 429 "paser.y"
                       {
        printf("Stmt Find\n");
    }
#line 1800 "parser.cpp"
    break;

  case 56: /* Stmt: RETURN Exp SEMICOLON  */
#line 432 "paser.y"
                           {
        printf("Stmt Find\n");
    }
#line 1808 "parser.cpp"
    break;

  case 57: /* Exp: AddExp  */
#line 437 "paser.y"
            {
        printf("Exp Find\n");
    }
#line 1816 "parser.cpp"
    break;

  case 58: /* Cond: LOrExp  */
#line 442 "paser.y"
            {
        printf("Cond Find\n");
    }
#line 1824 "parser.cpp"
    break;

  case 59: /* LVal: IDENTIFIER  */
#line 447 "paser.y"
                 {
        printf("Identifier Find\n");
    }
#line 1832 "parser.cpp"
    break;

  case 60: /* PrimaryExp: LEFT_PARENTHESES Exp RIGHT_PARENTHESES  */
#line 452 "paser.y"
                                                   {
        printf("PrimaryExp Find\n");
    }
#line 1840 "parser.cpp"
    break;

  case 61: /* PrimaryExp: LVal  */
#line 455 "paser.y"
           {
        printf("PrimaryExp Find\n");
    }
#line 1848 "parser.cpp"
    break;

  case 62: /* PrimaryExp: Number  */
#line 458 "paser.y"
             {
        printf("PrimaryExp Find\n");
    }
#line 1856 "parser.cpp"
    break;

  case 63: /* Number: INTVAL  */
#line 463 "paser.y"
                {
        printf("Number Find\n");
    }
#line 1864 "parser.cpp"
    break;

  case 64: /* Number: FLOATVAL  */
#line 466 "paser.y"
               {
        printf("Number Find\n");
    }
#line 1872 "parser.cpp"
    break;

  case 65: /* UnaryExp: PrimaryExp  */
#line 472 "paser.y"
                     {
        printf("UnaryExp Find\n");
    }
#line 1880 "parser.cpp"
    break;

  case 66: /* UnaryExp: IDENTIFIER LEFT_PARENTHESES RIGHT_PARENTHESES  */
#line 475 "paser.y"
                                                    {
        printf("UnaryExp Find\n");
    }
#line 1888 "parser.cpp"
    break;

  case 67: /* UnaryExp: IDENTIFIER LEFT_PARENTHESES FuncRParams RIGHT_PARENTHESES  */
#line 478 "paser.y"
                                                               {
        printf("UnaryExp Find\n");
    }
#line 1896 "parser.cpp"
    break;

  case 68: /* UnaryExp: UnaryOp UnaryExp  */
#line 481 "paser.y"
                      {
        printf("UnaryExp Find\n");
    }
#line 1904 "parser.cpp"
    break;

  case 69: /* UnaryOp: ADD  */
#line 486 "paser.y"
             {
        printf("UnaryOp Find\n");
    }
#line 1912 "parser.cpp"
    break;

  case 70: /* UnaryOp: SUB  */
#line 489 "paser.y"
          {
        printf("UnaryOp Find\n");
    }
#line 1920 "parser.cpp"
    break;

  case 71: /* UnaryOp: NOT  */
#line 492 "paser.y"
          {
        printf("UnaryOp Find\n");
    }
#line 1928 "parser.cpp"
    break;

  case 72: /* FuncRParams: Exp  */
#line 497 "paser.y"
                 {
        printf("FuncRParams Find\n");
    }
#line 1936 "parser.cpp"
    break;

  case 73: /* FuncRParams: FuncRParams COMMA Exp  */
#line 500 "paser.y"
                            {
        printf("FuncRParams Find\n");
    }
#line 1944 "parser.cpp"
    break;

  case 74: /* MulExp: UnaryExp  */
#line 505 "paser.y"
                 {
        printf("UnaryExp Find\n");
    }
#line 1952 "parser.cpp"
    break;

  case 75: /* MulExp: MulExp MUL UnaryOp  */
#line 508 "paser.y"
                         {
        printf("MulExp Find\n");
    }
#line 1960 "parser.cpp"
    break;

  case 76: /* MulExp: MulExp DIV UnaryExp  */
#line 511 "paser.y"
                          {
        printf("MulExp Find\n");
    }
#line 1968 "parser.cpp"
    break;

  case 77: /* MulExp: MulExp MOD UnaryExp  */
#line 514 "paser.y"
                          {
        printf("MulExp Find\n");
    }
#line 1976 "parser.cpp"
    break;

  case 78: /* AddExp: MulExp  */
#line 519 "paser.y"
               {
        printf("AddExp Find\n");
    }
#line 1984 "parser.cpp"
    break;

  case 79: /* AddExp: AddExp ADD MulExp  */
#line 522 "paser.y"
                        {
        printf("MulExp Find\n");
    }
#line 1992 "parser.cpp"
    break;

  case 80: /* AddExp: AddExp SUB MulExp  */
#line 525 "paser.y"
                        {
        printf("MulExp Find\n");
    }
#line 2000 "parser.cpp"
    break;

  case 81: /* RelExp: AddExp  */
#line 530 "paser.y"
               {
        printf("RelExp Find\n");
    }
#line 2008 "parser.cpp"
    break;

  case 82: /* RelExp: RelExp LT AddExp  */
#line 533 "paser.y"
                       {
        printf("RelExp Find\n");
    }
#line 2016 "parser.cpp"
    break;

  case 83: /* RelExp: RelExp GT AddExp  */
#line 536 "paser.y"
                       {
        printf("RelExp Find\n");
    }
#line 2024 "parser.cpp"
    break;

  case 84: /* RelExp: RelExp LTE AddExp  */
#line 539 "paser.y"
                        {
        printf("RelExp Find\n");
    }
#line 2032 "parser.cpp"
    break;

  case 85: /* RelExp: RelExp GTE AddExp  */
#line 542 "paser.y"
                        {
        printf("RelExp Find\n");
    }
#line 2040 "parser.cpp"
    break;

  case 86: /* EqExp: RelExp  */
#line 547 "paser.y"
              {
        printf("EqExp Find\n");
    }
#line 2048 "parser.cpp"
    break;

  case 87: /* EqExp: EqExp EQ RelExp  */
#line 550 "paser.y"
                      {
        printf("EqExp Find\n");
    }
#line 2056 "parser.cpp"
    break;

  case 88: /* EqExp: EqExp NEQ RelExp  */
#line 553 "paser.y"
                       {
        printf("EqExp Find\n");
    }
#line 2064 "parser.cpp"
    break;

  case 89: /* LAndExp: EqExp  */
#line 558 "paser.y"
               {
        printf("LAndExp Find\n");
    }
#line 2072 "parser.cpp"
    break;

  case 90: /* LAndExp: LAndExp AND EqExp  */
#line 561 "paser.y"
                        {
        printf("LAndExp Find\n");
    }
#line 2080 "parser.cpp"
    break;

  case 91: /* LOrExp: LAndExp  */
#line 566 "paser.y"
                {
        printf("LOrExp Find\n");
    }
#line 2088 "parser.cpp"
    break;

  case 92: /* LOrExp: LOrExp OR LAndExp  */
#line 569 "paser.y"
                        {
        printf("LOrExp Find\n");
    }
#line 2096 "parser.cpp"
    break;

  case 93: /* ConstExp: AddExp  */
#line 574 "paser.y"
                 {
        printf("ConstExp Find\n");
    }
#line 2104 "parser.cpp"
    break;


#line 2108 "parser.cpp"

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

#line 577 "paser.y"


void yyerror(const char* s) {
    printf("ERROR: %s\n", s);
}

int main(int argc, char *argv[]){
    /* int c; */
    ++argv;
    if (argc>0){yyin=fopen(argv[0], "r");}
    return yyparse();
}











