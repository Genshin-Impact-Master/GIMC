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
  YYSYMBOL_ParamArrayDim = 57,             /* ParamArrayDim  */
  YYSYMBOL_Block = 58,                     /* Block  */
  YYSYMBOL_BlockItems = 59,                /* BlockItems  */
  YYSYMBOL_Stmt = 60,                      /* Stmt  */
  YYSYMBOL_Exp = 61,                       /* Exp  */
  YYSYMBOL_LVal = 62,                      /* LVal  */
  YYSYMBOL_Number = 63,                    /* Number  */
  YYSYMBOL_UnaryExp = 64,                  /* UnaryExp  */
  YYSYMBOL_FuncRParams = 65,               /* FuncRParams  */
  YYSYMBOL_MulExp = 66,                    /* MulExp  */
  YYSYMBOL_AddExp = 67,                    /* AddExp  */
  YYSYMBOL_RelExp = 68,                    /* RelExp  */
  YYSYMBOL_EqExp = 69,                     /* EqExp  */
  YYSYMBOL_LAndExp = 70,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 71,                    /* LOrExp  */
  YYSYMBOL_ConstExp = 72                   /* ConstExp  */
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
#define YYLAST   287

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  185

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
       0,   128,   128,   133,   138,   144,   151,   156,   163,   170,
     175,   181,   185,   189,   196,   203,   212,   217,   229,   234,
     240,   245,   250,   257,   264,   271,   276,   284,   292,   300,
     308,   327,   332,   339,   344,   349,   356,   363,   372,   384,
     389,   396,   403,   412,   416,   422,   427,   433,   438,   443,
     448,   453,   466,   474,   481,   486,   493,   502,   511,   519,
     524,   529,   536,   545,   553,   559,   578,   584,   593,   600,
     608,   617,   627,   638,   644,   651,   673,   678,   685,   689,
     698,   707,   718,   721,   730,   741,   745,   754,   763,   772,
     783,   787,   796,   807,   811,   822,   826,   837
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
  "FuncFParam", "ParamArrayDim", "Block", "BlockItems", "Stmt", "Exp",
  "LVal", "Number", "UnaryExp", "FuncRParams", "MulExp", "AddExp",
  "RelExp", "EqExp", "LAndExp", "LOrExp", "ConstExp", YY_NULLPTR
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
      99,    75,   -91,   -91,   -91,    81,   -91,   -91,    23,   -91,
     -91,    29,   -91,   -91,   -91,    32,    34,   -91,     9,   108,
     -91,   249,    84,   249,    33,    39,   -91,   249,    47,    29,
     -91,   249,   249,   249,   249,     3,   -91,   -91,   -91,    49,
     -91,   -91,    78,   141,    57,    76,    -9,   -91,   141,    -8,
      62,   249,    48,   -91,   -91,    88,   -91,   -91,   -91,   -91,
     102,   201,   249,   249,   249,   249,   249,   249,   137,   -91,
     118,    57,    75,   -91,    54,   -91,   140,   175,   -91,   -91,
     -91,   -91,    -7,   151,   -91,   -91,   -91,    78,    78,   122,
     169,   133,   171,   206,   -91,   -91,   -91,    39,   -91,   163,
     -91,   189,    58,   194,   172,   -91,   -91,   -91,   113,   192,
     -91,   -91,   -91,   119,   193,   -91,   -91,   249,   -91,   249,
     249,   -91,   -91,   -91,   196,   -91,   -91,   -91,   -91,   -91,
     249,   -91,   249,   -91,   218,   249,   -91,   244,   249,   -91,
     141,   116,   167,   213,    -5,     0,   -91,   197,   202,   203,
     -91,   160,   207,   -91,   181,   249,   249,   249,   249,   249,
     249,   249,   249,    15,    15,   -91,   -91,   -91,   -91,   249,
     -91,   -91,   249,   141,   141,   141,   141,   116,   116,   167,
     213,   226,   -91,    15,   -91
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    11,    13,    12,     0,     4,     6,     0,     7,
       5,     0,     1,     2,     3,    27,     0,    25,     0,     0,
       9,     0,     0,     0,    29,     0,    24,     0,     0,     0,
       8,     0,     0,     0,     0,    64,    66,    67,    28,    69,
      70,    78,    82,    63,     0,     0,     0,    39,    97,     0,
       0,     0,    27,    26,    14,     0,    10,    73,    74,    75,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
      41,     0,     0,    16,     0,    30,     0,     0,    15,    68,
      71,    76,     0,     0,    79,    80,    81,    83,    84,     0,
       0,     0,     0,     0,    45,    54,    47,     0,    55,     0,
      48,     0,    69,     0,    42,    37,    40,    34,     0,     0,
      31,    17,    21,     0,     0,    18,    72,     0,    65,     0,
       0,    59,    60,    61,     0,    46,    51,    49,    50,    53,
       0,    43,     0,    33,     0,     0,    20,     0,     0,    77,
      85,    90,    93,    95,     0,     0,    62,     0,     0,     0,
      32,     0,     0,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    52,    44,    35,    36,     0,
      22,    23,     0,    86,    88,    87,    89,    91,    92,    94,
      96,    56,    58,     0,    57
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -91,   -91,    -4,   -91,   -91,     4,   220,   233,   120,   -70,
     -91,   -91,   232,   124,   -64,   255,   -91,   190,   -91,   -29,
     -91,   -90,   -13,   -65,   -91,   -19,   -91,   150,   -23,    60,
     103,   101,   145,   -21
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,    19,     8,    20,    24,   113,    78,
       9,    16,    17,   108,    75,    10,    46,    47,   104,    98,
      99,   100,   101,    39,    40,    41,    82,    42,    43,   141,
     142,   143,   144,   115
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      48,    13,    49,   102,    48,    11,    54,   114,    38,   128,
     109,   162,    57,    58,    59,    69,   162,    27,    31,    32,
      71,    60,   116,    73,   163,    72,    45,   117,    48,   164,
      76,    61,    33,    89,   102,    90,    91,    92,    93,    23,
      21,    50,   105,    34,    84,    85,    86,    68,    81,    83,
      95,    35,    36,    37,    48,    55,    21,    31,    32,    15,
      22,   110,    23,    51,    96,    18,   130,   152,    25,    26,
     149,    33,    97,   181,   182,    52,    45,    51,    23,    62,
     124,    12,    34,    63,    64,    65,    74,   107,    62,    68,
      35,    36,    37,   184,    74,   127,   140,   140,   102,   102,
       2,     3,     4,    97,   139,     1,     2,     3,     4,     2,
       3,     4,    70,    44,    48,    48,   153,   147,   102,   148,
      77,   150,   110,     1,     2,     3,     4,   155,   156,   157,
     158,    79,   173,   174,   175,   176,   140,   140,   140,   140,
      31,    32,    29,    30,    66,    67,   133,   134,   103,    48,
     119,   153,   136,   137,    33,    89,   150,    90,    91,    92,
      93,     1,     2,     3,     4,    34,    31,    32,   121,    68,
      94,   111,    95,    35,    36,    37,   159,   160,    31,    32,
      33,    89,   118,    90,    91,    92,    93,     1,     2,     3,
       4,    34,    33,   168,   169,    68,   125,   120,   126,    35,
      36,    37,   132,    34,    31,    32,   122,    77,   112,    31,
      32,    35,    36,    37,   171,   172,    87,    88,    33,   177,
     178,    31,    32,    33,   129,   131,   135,   138,   161,    34,
      80,   146,   165,   166,    34,    33,   167,    35,    36,    37,
     170,   123,    35,    36,    37,   183,    34,    31,    32,    56,
      74,    28,    31,    32,    35,    36,    37,    53,   154,   151,
      14,    33,   106,   180,   179,   145,    33,     0,     0,     0,
       0,     0,    34,     0,     0,     0,    77,    34,     0,     0,
      35,    36,    37,     0,     0,    35,    36,    37
};

static const yytype_int16 yycheck[] =
{
      23,     5,    23,    68,    27,     1,    27,    77,    21,    99,
      74,    16,    31,    32,    33,    44,    16,     8,     3,     4,
      29,    34,    29,    31,    29,    34,    22,    34,    51,    29,
      51,    28,    17,    18,    99,    20,    21,    22,    23,    30,
       8,     8,    71,    28,    63,    64,    65,    32,    61,    62,
      35,    36,    37,    38,    77,     8,     8,     3,     4,    36,
      28,    74,    30,    30,    68,    36,     8,   137,    34,    35,
     134,    17,    68,   163,   164,    36,    72,    30,    30,    30,
      93,     0,    28,     5,     6,     7,    32,    33,    30,    32,
      36,    37,    38,   183,    32,    99,   119,   120,   163,   164,
      25,    26,    27,    99,   117,    24,    25,    26,    27,    25,
      26,    27,    36,    29,   137,   138,   137,   130,   183,   132,
      32,   134,   135,    24,    25,    26,    27,    11,    12,    13,
      14,    29,   155,   156,   157,   158,   159,   160,   161,   162,
       3,     4,    34,    35,     3,     4,    33,    34,    30,   172,
      28,   172,    33,    34,    17,    18,   169,    20,    21,    22,
      23,    24,    25,    26,    27,    28,     3,     4,    35,    32,
      33,    31,    35,    36,    37,    38,     9,    10,     3,     4,
      17,    18,    31,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    17,    33,    34,    32,    33,    28,    35,    36,
      37,    38,    30,    28,     3,     4,    35,    32,    33,     3,
       4,    36,    37,    38,    33,    34,    66,    67,    17,   159,
     160,     3,     4,    17,    35,    31,    34,    34,    15,    28,
      29,    35,    35,    31,    28,    17,    33,    36,    37,    38,
      33,    35,    36,    37,    38,    19,    28,     3,     4,    29,
      32,    18,     3,     4,    36,    37,    38,    25,   138,   135,
       5,    17,    72,   162,   161,   120,    17,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    32,    28,    -1,    -1,
      36,    37,    38,    -1,    -1,    36,    37,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    24,    25,    26,    27,    40,    41,    42,    44,    49,
      54,    44,     0,    41,    54,    36,    50,    51,    36,    43,
      45,     8,    28,    30,    46,    34,    35,     8,    46,    34,
      35,     3,     4,    17,    28,    36,    37,    38,    61,    62,
      63,    64,    66,    67,    29,    44,    55,    56,    67,    72,
       8,    30,    36,    51,    72,     8,    45,    64,    64,    64,
      61,    28,    30,     5,     6,     7,     3,     4,    32,    58,
      36,    29,    34,    31,    32,    53,    72,    32,    48,    29,
      29,    61,    65,    61,    64,    64,    64,    66,    66,    18,
      20,    21,    22,    23,    33,    35,    41,    44,    58,    59,
      60,    61,    62,    30,    57,    58,    56,    33,    52,    53,
      61,    31,    33,    47,    48,    72,    29,    34,    31,    28,
      28,    35,    35,    35,    61,    33,    35,    41,    60,    35,
       8,    31,    30,    33,    34,    34,    33,    34,    34,    61,
      67,    68,    69,    70,    71,    71,    35,    61,    61,    53,
      61,    52,    48,    72,    47,    11,    12,    13,    14,     9,
      10,    15,    16,    29,    29,    35,    31,    33,    33,    34,
      33,    33,    34,    67,    67,    67,    67,    68,    68,    69,
      70,    60,    60,    19,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    40,    40,    40,    41,    41,    42,    43,
      43,    44,    44,    44,    45,    45,    46,    46,    47,    47,
      48,    48,    48,    48,    49,    50,    50,    51,    51,    51,
      51,    52,    52,    53,    53,    53,    53,    54,    54,    55,
      55,    56,    56,    57,    57,    58,    58,    59,    59,    59,
      59,    59,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    61,    62,    62,    63,    63,    64,    64,
      64,    64,    64,    64,    64,    64,    65,    65,    66,    66,
      66,    66,    67,    67,    67,    68,    68,    68,    68,    68,
      69,    69,    69,    70,    70,    71,    71,    72
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     1,     4,     1,
       3,     1,     1,     1,     3,     4,     3,     4,     1,     3,
       3,     2,     5,     5,     3,     1,     3,     1,     3,     2,
       4,     1,     3,     3,     2,     5,     5,     6,     5,     1,
       3,     2,     3,     2,     4,     2,     3,     1,     1,     2,
       2,     2,     4,     2,     1,     1,     5,     7,     5,     2,
       2,     2,     3,     1,     1,     4,     1,     1,     3,     1,
       1,     3,     4,     2,     2,     2,     1,     3,     1,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     1,     3,     1
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
#line 128 "parser.y"
                       {
        (yyval.compUnit) = (yyvsp[-1].compUnit);
        (yyvsp[-1].compUnit) -> addDecl(DeclPtr((yyvsp[0].decl)));
        printf("CompUnit Decl Find\n");
    }
#line 1289 "parser.cpp"
    break;

  case 3: /* CompUnit: CompUnit FuncDef  */
#line 133 "parser.y"
                      {
        (yyval.compUnit) = (yyvsp[-1].compUnit);
        (yyvsp[-1].compUnit) -> addFuncDef(FuncDefPtr((yyvsp[0].funcDef)));
        printf("CompUnit FuncDef Find\n");
    }
#line 1299 "parser.cpp"
    break;

  case 4: /* CompUnit: Decl  */
#line 138 "parser.y"
          {
        root = new CompUnit();
        (yyval.compUnit) = root;
        (yyval.compUnit) -> addDecl(DeclPtr((yyvsp[0].decl)));
        printf("Decl Find\n");
    }
#line 1310 "parser.cpp"
    break;

  case 5: /* CompUnit: FuncDef  */
#line 144 "parser.y"
             {
        root = new CompUnit();
        (yyval.compUnit) = root;
        (yyval.compUnit) -> addFuncDef(FuncDefPtr((yyvsp[0].funcDef)));
        printf("FuncDef Find\n");
    }
#line 1321 "parser.cpp"
    break;

  case 6: /* Decl: ConstDecl  */
#line 151 "parser.y"
               {
        (yyval.decl) = new Decl();
        (yyval.decl) -> addConstDecl(ConstDeclPtr((yyvsp[0].constDecl)));
        printf("ConstDecl Find\n");
    }
#line 1331 "parser.cpp"
    break;

  case 7: /* Decl: VarDecl  */
#line 156 "parser.y"
              {
        (yyval.decl) = new Decl();
        (yyval.decl) -> addVarDecl(VarDeclPtr((yyvsp[0].varDecl)));
        printf("VarDecl Find\n");
    }
#line 1341 "parser.cpp"
    break;

  case 8: /* ConstDecl: CONST BaseType ConstDefs SEMICOLON  */
#line 163 "parser.y"
                                             {
        (yyval.constDecl) = new ConstDecl();
        (yyval.constDecl) -> addType((yyvsp[-2].type));
        (yyval.constDecl) -> addConstDef(ConstDefsPtr((yyvsp[-1].constDefs)));
        printf("ConstDecl Find\n");
    }
#line 1352 "parser.cpp"
    break;

  case 9: /* ConstDefs: ConstDef  */
#line 170 "parser.y"
                    {
        (yyval.constDefs) = new ConstDefs();
        (yyval.constDefs)->addConstDef(ConstDefPtr((yyvsp[0].constDef)));
        printf("ConstDefs Find\n");
    }
#line 1362 "parser.cpp"
    break;

  case 10: /* ConstDefs: ConstDefs COMMA ConstDef  */
#line 175 "parser.y"
                               {
        (yyval.constDefs) = (yyvsp[-2].constDefs);
        (yyvsp[-2].constDefs) -> addConstDef(ConstDefPtr((yyvsp[0].constDef)));
        printf("ConstDefs Find\n");
    }
#line 1372 "parser.cpp"
    break;

  case 11: /* BaseType: INT  */
#line 181 "parser.y"
             {
        (yyval.type) = BaseType::B_INT;
        printf("INT Token Find\n");
    }
#line 1381 "parser.cpp"
    break;

  case 12: /* BaseType: FLOAT  */
#line 185 "parser.y"
           {
        (yyval.type) = BaseType::B_FLOAT;
        printf("FLOAT Token Find\n");
    }
#line 1390 "parser.cpp"
    break;

  case 13: /* BaseType: VOID  */
#line 189 "parser.y"
           {
        (yyval.type) = BaseType::B_VOID;
        printf("VOID Token Find\n");

    }
#line 1400 "parser.cpp"
    break;

  case 14: /* ConstDef: IDENTIFIER ASSIGN ConstExp  */
#line 196 "parser.y"
                                    {
        (yyval.constDef) = new ConstDef();
        (yyval.constDef) -> addIdentifier((yyvsp[-2].identifier));
        (yyval.constDef) -> addArray(false);
        (yyval.constDef) -> addInitVal(ConstExpPtr((yyvsp[0].constExp)));
        printf("ConstDef Find\n");
    }
#line 1412 "parser.cpp"
    break;

  case 15: /* ConstDef: IDENTIFIER ArrayDim ASSIGN ConstArrayInitVal  */
#line 203 "parser.y"
                                                   {
        (yyval.constDef) = new ConstDef();
        // $$ -> addIdentifier($1);
        (yyval.constDef) -> addArray(true);
        (yyval.constDef) -> addArrayDim(ArrayDimPtr((yyvsp[-2].arrayDim)));
        // $$ -> addArrayInitVal(ConstArrayInitValPtr($4));
        printf("ConstDef Find\n");
    }
#line 1425 "parser.cpp"
    break;

  case 16: /* ArrayDim: LEFT_BRACKETS ConstExp RIGHT_BRACKETS  */
#line 212 "parser.y"
                                                {
        (yyval.arrayDim) = new ArrayDim();
        (yyval.arrayDim) -> addDim (ConstExpPtr((yyvsp[-1].constExp)));
        printf("ArrayDim Find\n");
    }
#line 1435 "parser.cpp"
    break;

  case 17: /* ArrayDim: ArrayDim LEFT_BRACKETS ConstExp RIGHT_BRACKETS  */
#line 217 "parser.y"
                                                     {
        (yyval.arrayDim) = (yyvsp[-3].arrayDim);
        (yyval.arrayDim) -> addDim(ConstExpPtr((yyvsp[-1].constExp)));
        printf("ArrayDim Find\n");
    }
#line 1445 "parser.cpp"
    break;

  case 18: /* ConstInitVals: ConstExp  */
#line 229 "parser.y"
                        {
        (yyval.constInitVals) = new ConstInitVals();
        (yyval.constInitVals) -> addConstExp(ConstExpPtr((yyvsp[0].constExp)));
        printf("ConstInitVals Find\n");
    }
#line 1455 "parser.cpp"
    break;

  case 19: /* ConstInitVals: ConstInitVals COMMA ConstExp  */
#line 234 "parser.y"
                                   {
        (yyval.constInitVals) = (yyvsp[-2].constInitVals);
        (yyval.constInitVals) -> addConstExp(ConstExpPtr((yyvsp[0].constExp)));
        printf("ConstInitVals Find\n");
    }
#line 1465 "parser.cpp"
    break;

  case 20: /* ConstArrayInitVal: LEFT_BRACES ConstInitVals RIGHT_BRACES  */
#line 240 "parser.y"
                                                          {
        (yyval.constArrayInitVal) = new ConstArrayInitVal();
        (yyval.constArrayInitVal) -> addDimVal(ConstInitValsPtr((yyvsp[-1].constInitVals)));
        printf("ConsttInitVal Find\n");
    }
#line 1475 "parser.cpp"
    break;

  case 21: /* ConstArrayInitVal: LEFT_BRACES RIGHT_BRACES  */
#line 245 "parser.y"
                               {
        (yyval.constArrayInitVal) = new ConstArrayInitVal();
        (yyval.constArrayInitVal) -> addDimVal(ConstInitValsPtr(nullptr));
        printf("ConstArrayInitVal Find\n");
    }
#line 1485 "parser.cpp"
    break;

  case 22: /* ConstArrayInitVal: LEFT_BRACES ConstInitVals COMMA ConstArrayInitVal RIGHT_BRACES  */
#line 250 "parser.y"
                                                                     {
        (yyval.constArrayInitVal) = new ConstArrayInitVal();
        (yyval.constArrayInitVal) -> addDimVal(ConstInitValsPtr((yyvsp[-3].constInitVals)));
        auto tmp = (yyvsp[-1].constArrayInitVal) -> getDimVal();
        for (auto initvals: tmp) (yyval.constArrayInitVal) -> addDimVal(initvals);
        printf("ConstArrayInitVal Find\n");
    }
#line 1497 "parser.cpp"
    break;

  case 23: /* ConstArrayInitVal: LEFT_BRACES ConstArrayInitVal COMMA ConstInitVals RIGHT_BRACES  */
#line 257 "parser.y"
                                                                     {
        (yyval.constArrayInitVal) = (yyvsp[-3].constArrayInitVal);
        (yyvsp[-3].constArrayInitVal) -> addDimVal(ConstInitValsPtr((yyvsp[-1].constInitVals)));
        printf("ConstArrayInitVal Find\n");
    }
#line 1507 "parser.cpp"
    break;

  case 24: /* VarDecl: BaseType VarDefs SEMICOLON  */
#line 264 "parser.y"
                                   {
         (yyval.varDecl) = new VarDecl();
         (yyval.varDecl) -> addType((yyvsp[-2].type));
         (yyval.varDecl) -> addVarDefs(VarDefsPtr((yyvsp[-1].varDefs)));
        printf("VarDecl Find\n");
    }
#line 1518 "parser.cpp"
    break;

  case 25: /* VarDefs: VarDef  */
#line 271 "parser.y"
                {
        (yyval.varDefs) = new VarDefs();
        (yyval.varDefs) -> addVarDef(VarDefPtr((yyvsp[0].varDef)));
        printf("VarDefs Find\n");
    }
#line 1528 "parser.cpp"
    break;

  case 26: /* VarDefs: VarDefs COMMA VarDef  */
#line 276 "parser.y"
                           {
        (yyval.varDefs) = (yyvsp[-2].varDefs);
        (yyval.varDefs) -> addVarDef(VarDefPtr((yyvsp[0].varDef))); 
        printf("VarDefs Find\n");
    }
#line 1538 "parser.cpp"
    break;

  case 27: /* VarDef: IDENTIFIER  */
#line 284 "parser.y"
                   {
        // cout<<*($1)<<endl;
        (yyval.varDef) = new VarDef();
        (yyval.varDef) -> addIdentifier((yyvsp[0].identifier));
        (yyval.varDef) -> addInit(false);
        (yyval.varDef) -> addArray(false);
        printf("VarDef Find\n");
    }
#line 1551 "parser.cpp"
    break;

  case 28: /* VarDef: IDENTIFIER ASSIGN Exp  */
#line 292 "parser.y"
                           {
        (yyval.varDef) = new VarDef();
        (yyval.varDef) -> addIdentifier((yyvsp[-2].identifier));
        (yyval.varDef) -> addInit(true);
        (yyval.varDef) -> addInitVal(ExpPtr((yyvsp[0].exp)));
        (yyval.varDef) -> addArray(false);
        printf("VarDef Find\n");
    }
#line 1564 "parser.cpp"
    break;

  case 29: /* VarDef: IDENTIFIER ArrayDim  */
#line 300 "parser.y"
                          {
        (yyval.varDef) = new VarDef();
        (yyval.varDef) -> addIdentifier((yyvsp[-1].identifier));
        (yyval.varDef) -> addArrayDim(ArrayDimPtr((yyvsp[0].arrayDim)));
        (yyval.varDef) -> addInit(false);
        (yyval.varDef) -> addArray(true);
        printf("VarDef Find\n");
    }
#line 1577 "parser.cpp"
    break;

  case 30: /* VarDef: IDENTIFIER ArrayDim ASSIGN ArrayInitVal  */
#line 308 "parser.y"
                                             {
        (yyval.varDef) = new VarDef();
        (yyval.varDef) -> addIdentifier((yyvsp[-3].identifier));
        (yyval.varDef) -> addArrayDim(ArrayDimPtr((yyvsp[-2].arrayDim)));
        (yyval.varDef) -> addArrayInitVal(ArrayInitValPtr((yyvsp[0].arrayInitVal)));
        (yyval.varDef) -> addInit(true);
        (yyval.varDef) -> addArray(true);
        printf("VarDef Find\n");
    }
#line 1591 "parser.cpp"
    break;

  case 31: /* InitVals: Exp  */
#line 327 "parser.y"
              {
        (yyval.initVals) = new InitVals();
        (yyval.initVals) -> addExp(ExpPtr((yyvsp[0].exp)));
        printf("InitVals Find\n");  
    }
#line 1601 "parser.cpp"
    break;

  case 32: /* InitVals: InitVals COMMA Exp  */
#line 332 "parser.y"
                         {
        (yyval.initVals) = (yyvsp[-2].initVals);
        (yyval.initVals) -> addExp(ExpPtr((yyvsp[0].exp)));
        printf("InitVals Find\n");
    }
#line 1611 "parser.cpp"
    break;

  case 33: /* ArrayInitVal: LEFT_BRACES InitVals RIGHT_BRACES  */
#line 339 "parser.y"
                                                {
        (yyval.arrayInitVal) = new ArrayInitVal();
        (yyval.arrayInitVal) -> addDimVal(InitValsPtr((yyvsp[-1].initVals)));
        printf("ArrayInitVal Find\n");
    }
#line 1621 "parser.cpp"
    break;

  case 34: /* ArrayInitVal: LEFT_BRACES RIGHT_BRACES  */
#line 344 "parser.y"
                               {
        (yyval.arrayInitVal) = new ArrayInitVal();
        (yyval.arrayInitVal) -> addDimVal(InitValsPtr(nullptr));
        printf("ArrayInitVal Find\n");
    }
#line 1631 "parser.cpp"
    break;

  case 35: /* ArrayInitVal: LEFT_BRACES InitVals COMMA ArrayInitVal RIGHT_BRACES  */
#line 349 "parser.y"
                                                           {
        (yyval.arrayInitVal) = new ArrayInitVal();
        (yyval.arrayInitVal) -> addDimVal(InitValsPtr((yyvsp[-3].initVals)));
        auto tmp = (yyvsp[-1].arrayInitVal) -> getDimVal();
        for (auto initvals: tmp) (yyval.arrayInitVal) -> addDimVal(initvals);
        printf("ArrayInitVal Find\n");
    }
#line 1643 "parser.cpp"
    break;

  case 36: /* ArrayInitVal: LEFT_BRACES ArrayInitVal COMMA InitVals RIGHT_BRACES  */
#line 356 "parser.y"
                                                           {
        (yyval.arrayInitVal) = (yyvsp[-3].arrayInitVal);
        (yyvsp[-3].arrayInitVal) -> addDimVal(InitValsPtr((yyvsp[-1].initVals)));
        printf("ArrayInitVal Find\n");
    }
#line 1653 "parser.cpp"
    break;

  case 37: /* FuncDef: BaseType IDENTIFIER LEFT_PARENTHESES FuncFParams RIGHT_PARENTHESES Block  */
#line 363 "parser.y"
                                                                                 {
        (yyval.funcDef) = new FuncDef();
        (yyval.funcDef) -> addReturnType((yyvsp[-5].type));
        (yyval.funcDef) -> addIdentifier((yyvsp[-4].identifier));
        (yyval.funcDef) -> addParam(true);
        (yyval.funcDef) -> addFuncFParams(FuncFParamsPtr((yyvsp[-2].funcFParams)));
        (yyval.funcDef) -> addBlock(BlockPtr((yyvsp[0].block)));
        printf("FuncDef Find\n");
    }
#line 1667 "parser.cpp"
    break;

  case 38: /* FuncDef: BaseType IDENTIFIER LEFT_PARENTHESES RIGHT_PARENTHESES Block  */
#line 372 "parser.y"
                                                                  {
        (yyval.funcDef) = new FuncDef();
        (yyval.funcDef) -> addReturnType((yyvsp[-4].type));
        (yyval.funcDef) -> addIdentifier((yyvsp[-3].identifier));
        (yyval.funcDef) -> addParam(false);
        (yyval.funcDef) -> addBlock(BlockPtr((yyvsp[0].block)));
        printf("FuncDef Find\n");
    }
#line 1680 "parser.cpp"
    break;

  case 39: /* FuncFParams: FuncFParam  */
#line 384 "parser.y"
                        {
        (yyval.funcFParams) = new FuncFParams();
        (yyval.funcFParams) -> addFuncFParam(FuncFParamPtr((yyvsp[0].funcFParam)));
        printf("FuncFParams Find\n");
    }
#line 1690 "parser.cpp"
    break;

  case 40: /* FuncFParams: FuncFParams COMMA FuncFParam  */
#line 389 "parser.y"
                                  {
        (yyval.funcFParams) = (yyvsp[-2].funcFParams);
        (yyval.funcFParams) -> addFuncFParam(FuncFParamPtr((yyvsp[0].funcFParam)));
        printf("FuncFParams Find\n");
    }
#line 1700 "parser.cpp"
    break;

  case 41: /* FuncFParam: BaseType IDENTIFIER  */
#line 396 "parser.y"
                                {
        (yyval.funcFParam) = new FuncFParam();
        (yyval.funcFParam) -> addType((yyvsp[-1].type));
        (yyval.funcFParam) -> addIdentifier((yyvsp[0].identifier));
        (yyval.funcFParam) -> addArray(false);
        printf("FuncFParam Find\n");
    }
#line 1712 "parser.cpp"
    break;

  case 42: /* FuncFParam: BaseType IDENTIFIER ParamArrayDim  */
#line 403 "parser.y"
                                        {
        (yyval.funcFParam) = new FuncFParam();
        (yyval.funcFParam) -> addType((yyvsp[-2].type));
        (yyval.funcFParam) -> addIdentifier((yyvsp[-1].identifier));
        (yyval.funcFParam) -> addArray(true);
        (yyval.funcFParam) -> addArrayDim(ParamArrayDimPtr((yyvsp[0].paramArrayDim)));
        printf("FuncFParam Find\n");
    }
#line 1725 "parser.cpp"
    break;

  case 43: /* ParamArrayDim: LEFT_BRACKETS RIGHT_BRACKETS  */
#line 412 "parser.y"
                                            {
        (yyval.paramArrayDim) -> addDim(nullptr);
        printf("ParamArrayDim Find\n");
    }
#line 1734 "parser.cpp"
    break;

  case 44: /* ParamArrayDim: ParamArrayDim LEFT_BRACKETS Exp RIGHT_BRACKETS  */
#line 416 "parser.y"
                                                     {
        (yyval.paramArrayDim) -> addDim(ExpPtr((yyvsp[-1].exp)));
        printf("ParamArrayDim Find\n");
    }
#line 1743 "parser.cpp"
    break;

  case 45: /* Block: LEFT_BRACES RIGHT_BRACES  */
#line 422 "parser.y"
                                {
        (yyval.block) = new Block();
        (yyval.block) -> addBlockItem(BlockItemsPtr(nullptr));
        printf("Empty Block Find\n");
    }
#line 1753 "parser.cpp"
    break;

  case 46: /* Block: LEFT_BRACES BlockItems RIGHT_BRACES  */
#line 427 "parser.y"
                                         {
        (yyval.block) = new Block();
        (yyval.block) -> addBlockItem(BlockItemsPtr((yyvsp[-1].blockItems)));
        printf("Block Find\n");
    }
#line 1763 "parser.cpp"
    break;

  case 47: /* BlockItems: Decl  */
#line 433 "parser.y"
                 {
        (yyval.blockItems) = new BlockItems();
        (yyval.blockItems) -> addDecl(DeclPtr((yyvsp[0].decl)));
        printf("BlockItems Find\n");
    }
#line 1773 "parser.cpp"
    break;

  case 48: /* BlockItems: Stmt  */
#line 438 "parser.y"
           {
        (yyval.blockItems) = new BlockItems();
        (yyval.blockItems) -> addStmt(StmtPtr((yyvsp[0].stmt)));
        printf("BlockItems Find\n");
    }
#line 1783 "parser.cpp"
    break;

  case 49: /* BlockItems: BlockItems Decl  */
#line 443 "parser.y"
                      {
        (yyval.blockItems) = (yyvsp[-1].blockItems);
        (yyval.blockItems) -> addDecl(DeclPtr((yyvsp[0].decl)));
        printf("BlockItems Find\n");
    }
#line 1793 "parser.cpp"
    break;

  case 50: /* BlockItems: BlockItems Stmt  */
#line 448 "parser.y"
                      {
        (yyval.blockItems) = (yyvsp[-1].blockItems);
        (yyval.blockItems) -> addStmt(StmtPtr((yyvsp[0].stmt)));
        printf("BlockItems Find\n");
    }
#line 1803 "parser.cpp"
    break;

  case 51: /* BlockItems: BlockItems SEMICOLON  */
#line 453 "parser.y"
                           {
        (yyval.blockItems) = (yyvsp[-1].blockItems);
        printf("BlockItems Find\n");
    }
#line 1812 "parser.cpp"
    break;

  case 52: /* Stmt: LVal ASSIGN Exp SEMICOLON  */
#line 466 "parser.y"
                                {
        AssignStmt* assign = new AssignStmt();
        assign -> addLVal(LValPtr((yyvsp[-3].lVal)));
        assign -> addExp(ExpPtr((yyvsp[-1].exp)));
        (yyval.stmt) = (Stmt*)(assign);
        (yyval.stmt) -> addType(StmtType::ST_ASSIGN);
        printf("Assign Stmt Find\n");
    }
#line 1825 "parser.cpp"
    break;

  case 53: /* Stmt: Exp SEMICOLON  */
#line 474 "parser.y"
                    {
        ExpStmt* exp = new ExpStmt();
        exp -> addExp(ExpPtr((yyvsp[-1].exp)));
        (yyval.stmt) = (Stmt*)(exp);
        (yyval.stmt) -> addType(StmtType::ST_EXP);
        printf("Exp Stmt Find\n");
    }
#line 1837 "parser.cpp"
    break;

  case 54: /* Stmt: SEMICOLON  */
#line 481 "parser.y"
                {
        (yyval.stmt) = new Stmt();
        (yyval.stmt) -> addType(StmtType::ST_BLANK);
        printf("Blank Stmt Find\n");
    }
#line 1847 "parser.cpp"
    break;

  case 55: /* Stmt: Block  */
#line 486 "parser.y"
            {
        BlockStmt* block = new BlockStmt();
        block -> addBlock(BlockPtr((yyvsp[0].block)));
        (yyval.stmt) = (Stmt*)(block);
        (yyval.stmt) -> addType(StmtType::ST_BLOCK);
        printf("Block Stmt Find\n");
    }
#line 1859 "parser.cpp"
    break;

  case 56: /* Stmt: IF LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt  */
#line 493 "parser.y"
                                                        {
        IfElseStmt* ifelsestmt = new IfElseStmt();
        ifelsestmt -> addCond(ExpPtr((yyvsp[-2].lOrExp)));
        ifelsestmt -> addThenStmt(StmtPtr((yyvsp[0].stmt)));
        ifelsestmt -> addElseStmt(StmtPtr(nullptr));
        (yyval.stmt) = (Stmt*)(ifelsestmt);
        (yyval.stmt) -> addType(StmtType::ST_IF);
        printf("If Stmt Find\n");
    }
#line 1873 "parser.cpp"
    break;

  case 57: /* Stmt: IF LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt ELSE Stmt  */
#line 502 "parser.y"
                                                                  {
        IfElseStmt* ifelsestmt = new IfElseStmt();
        ifelsestmt -> addCond(ExpPtr((yyvsp[-4].lOrExp)));
        ifelsestmt -> addThenStmt(StmtPtr((yyvsp[-2].stmt)));
        ifelsestmt -> addElseStmt(StmtPtr((yyvsp[0].stmt)));
        (yyval.stmt) = (Stmt*)(ifelsestmt);
        (yyval.stmt) -> addType(StmtType::ST_IF);
        printf("If Else Stmt Find\n");
    }
#line 1887 "parser.cpp"
    break;

  case 58: /* Stmt: WHILE LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt  */
#line 511 "parser.y"
                                                           {
        WhileStmt* whilestmt = new WhileStmt();
        whilestmt -> addCond(ExpPtr((yyvsp[-2].lOrExp)));
        whilestmt -> addStmt(StmtPtr((yyvsp[0].stmt)));
        (yyval.stmt) = (Stmt*)(whilestmt);
        (yyval.stmt) -> addType(StmtType::ST_WHILE);
        printf("While Stmt Find\n");
    }
#line 1900 "parser.cpp"
    break;

  case 59: /* Stmt: BREAK SEMICOLON  */
#line 519 "parser.y"
                     {
        (yyval.stmt) = new Stmt();
        (yyval.stmt) -> addType(StmtType::ST_BREAK);
        printf("Break Stmt Find\n");
    }
#line 1910 "parser.cpp"
    break;

  case 60: /* Stmt: CONTINUE SEMICOLON  */
#line 524 "parser.y"
                         {
        (yyval.stmt) = new Stmt();
        (yyval.stmt) -> addType(StmtType::ST_CONTINUE);
        printf("Continue Stmt Find\n");
    }
#line 1920 "parser.cpp"
    break;

  case 61: /* Stmt: RETURN SEMICOLON  */
#line 529 "parser.y"
                       {
        ReturnStmt* returnstmt = new ReturnStmt();
        returnstmt -> addExp(nullptr);
        (yyval.stmt) = (Stmt*)(returnstmt);
        (yyval.stmt) -> addType(StmtType::ST_RETURN);
        printf("Return Stmt Find\n");
    }
#line 1932 "parser.cpp"
    break;

  case 62: /* Stmt: RETURN Exp SEMICOLON  */
#line 536 "parser.y"
                           {
        ReturnStmt* returnstmt = new ReturnStmt();
        returnstmt -> addExp(ExpPtr((yyvsp[-1].exp)));
        (yyval.stmt) = (Stmt*)(returnstmt);
        (yyval.stmt) -> addType(StmtType::ST_RETURN);
        printf("Return Stmt Find\n");
    }
#line 1944 "parser.cpp"
    break;

  case 63: /* Exp: AddExp  */
#line 545 "parser.y"
            {
        (yyval.exp) = (yyvsp[0].addExp);
        printf("Exp Find\n");
    }
#line 1953 "parser.cpp"
    break;

  case 64: /* LVal: IDENTIFIER  */
#line 553 "parser.y"
                 {
        (yyval.lVal) = new LVal();
        (yyval.lVal) -> addIdentifier((yyvsp[0].identifier));
        (yyval.lVal) -> addIsArray(false);
        printf("LVal Find\n");
    }
#line 1964 "parser.cpp"
    break;

  case 65: /* LVal: LVal LEFT_BRACKETS Exp RIGHT_BRACKETS  */
#line 559 "parser.y"
                                            {
        (yyval.lVal) = (yyvsp[-3].lVal);
        (yyval.lVal) -> addIsArray(true);
        (yyval.lVal) -> addDims(ExpPtr((yyvsp[-1].exp)));
        printf("LVal Find\n");
    }
#line 1975 "parser.cpp"
    break;

  case 66: /* Number: INTVAL  */
#line 578 "parser.y"
                {
        (yyval.number) = new Number();
        (yyval.number) -> addIntVal((yyvsp[0].intVal));
        (yyval.number) -> addIsFloat(false);
        printf("Number Find\n");
    }
#line 1986 "parser.cpp"
    break;

  case 67: /* Number: FLOATVAL  */
#line 584 "parser.y"
               {
        (yyval.number) = new Number();
        (yyval.number) -> addFloatVal((yyvsp[0].floatVal));
        (yyval.number) -> addIsFloat(true);
        printf("Number Find\n");
    }
#line 1997 "parser.cpp"
    break;

  case 68: /* UnaryExp: LEFT_PARENTHESES Exp RIGHT_PARENTHESES  */
#line 593 "parser.y"
                                                 {
        auto tmp = new UnaryExp();
        tmp -> addExp(ExpPtr((yyvsp[-1].exp)));
        tmp -> addOp(UnaryOpType::UO_POS);
        (yyval.unaryExp) = (Exp*)(tmp);
        printf("UnaryExp Find\n");
    }
#line 2009 "parser.cpp"
    break;

  case 69: /* UnaryExp: LVal  */
#line 600 "parser.y"
           {
        auto tmp = new UnaryExp();
        tmp -> addExp(ExpPtr((yyvsp[0].lVal)));
        tmp -> addOp(UnaryOpType::UO_POS);
        tmp -> addType(ExpType::ET_LVAL);
        (yyval.unaryExp) = (Exp*)(tmp);
        printf("UnaryExp Find\n");
    }
#line 2022 "parser.cpp"
    break;

  case 70: /* UnaryExp: Number  */
#line 608 "parser.y"
             {
        auto tmp = new UnaryExp();
        tmp -> addExp(ExpPtr((yyvsp[0].number)));
        tmp -> addOp(UnaryOpType::UO_POS);
        if ((yyvsp[0].number) -> getIsFloat()) tmp -> addType(ExpType::ET_FLOAT);
        else tmp -> addType(ExpType::ET_INT);
        (yyval.unaryExp) = (Exp*)(tmp);
        printf("UnaryExp Find\n");
    }
#line 2036 "parser.cpp"
    break;

  case 71: /* UnaryExp: IDENTIFIER LEFT_PARENTHESES RIGHT_PARENTHESES  */
#line 617 "parser.y"
                                                    {
        auto tmp = new FuncCall();
        tmp -> addIdentifier((yyvsp[-2].identifier));
        auto tmp2 = new UnaryExp();
        tmp2 -> addExp(ExpPtr(tmp));
        tmp2 -> addOp(UnaryOpType::UO_POS);
        tmp2 -> addType(ExpType::ET_FUNC); 
        (yyval.unaryExp) = (Exp*)(tmp2);
        printf("UnaryExp Find\n");
    }
#line 2051 "parser.cpp"
    break;

  case 72: /* UnaryExp: IDENTIFIER LEFT_PARENTHESES FuncRParams RIGHT_PARENTHESES  */
#line 627 "parser.y"
                                                               {
        auto tmp = new FuncCall();
        tmp -> addIdentifier((yyvsp[-3].identifier));
        tmp -> addArgs(FuncRParamsPtr((yyvsp[-1].funcRParams)));
        auto tmp2 = new UnaryExp();
        tmp2 -> addExp(ExpPtr(tmp));
        tmp2 -> addOp(UnaryOpType::UO_POS);
        tmp2 -> addType(ExpType::ET_FUNC); 
        (yyval.unaryExp) = (Exp*)(tmp2);
        printf("UnaryExp Find\n");
    }
#line 2067 "parser.cpp"
    break;

  case 73: /* UnaryExp: ADD UnaryExp  */
#line 638 "parser.y"
                  {
        auto tmp = (UnaryExp*) (yyvsp[0].unaryExp);
        tmp -> addOp(UnaryOpType::UO_POS);
        (yyval.unaryExp) = (Exp*)(tmp);
        printf("UnaryExp Find\n");
    }
#line 2078 "parser.cpp"
    break;

  case 74: /* UnaryExp: SUB UnaryExp  */
#line 644 "parser.y"
                  {
        auto tmp = (UnaryExp*) (yyvsp[0].unaryExp);
        tmp -> addOp(UnaryOpType::UO_NEG);
        (yyval.unaryExp) = (Exp*)(tmp);
        printf("UnaryExp Find\n");
        
    }
#line 2090 "parser.cpp"
    break;

  case 75: /* UnaryExp: NOT UnaryExp  */
#line 651 "parser.y"
                  {
        auto tmp = (UnaryExp*) (yyvsp[0].unaryExp);
        tmp -> addOp(UnaryOpType::UO_NOT);
        (yyval.unaryExp) = (Exp*)(tmp);
        printf("UnaryExp Find\n");
    }
#line 2101 "parser.cpp"
    break;

  case 76: /* FuncRParams: Exp  */
#line 673 "parser.y"
                 {
        (yyval.funcRParams) = new FuncRParams();
        (yyval.funcRParams) -> addArgs(ExpPtr((yyvsp[0].exp)));
        printf("FuncRParams Find\n");
    }
#line 2111 "parser.cpp"
    break;

  case 77: /* FuncRParams: FuncRParams COMMA Exp  */
#line 678 "parser.y"
                            {
        (yyval.funcRParams) = (yyvsp[-2].funcRParams);
        (yyval.funcRParams) -> addArgs(ExpPtr((yyvsp[0].exp)));
        printf("FuncRParams Find\n");
    }
#line 2121 "parser.cpp"
    break;

  case 78: /* MulExp: UnaryExp  */
#line 685 "parser.y"
                 {
        (yyval.mulExp) = (yyvsp[0].unaryExp);
        printf("MulExp Find\n");
    }
#line 2130 "parser.cpp"
    break;

  case 79: /* MulExp: MulExp MUL UnaryExp  */
#line 689 "parser.y"
                          {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].mulExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].unaryExp)));
        tmp -> addOp(BinOpType::OP_MUL);
        tmp -> addType(ExpType::ET_BIN);
        (yyval.mulExp) = (Exp*)(tmp);
        printf("MulExp Find\n");
    }
#line 2144 "parser.cpp"
    break;

  case 80: /* MulExp: MulExp DIV UnaryExp  */
#line 698 "parser.y"
                          {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].mulExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].unaryExp)));
        tmp -> addOp(BinOpType::OP_DIV);
        (yyval.mulExp) = (Exp*)(tmp);
        (yyval.mulExp) -> addType(ExpType::ET_BIN);
        printf("MulExp Find\n");
    }
#line 2158 "parser.cpp"
    break;

  case 81: /* MulExp: MulExp MOD UnaryExp  */
#line 707 "parser.y"
                          {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].mulExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].unaryExp)));
        tmp -> addOp(BinOpType::OP_MOD);
        (yyval.mulExp) = (Exp*)(tmp);
        (yyval.mulExp) -> addType(ExpType::ET_BIN);
        printf("MulExp Find\n");
    }
#line 2172 "parser.cpp"
    break;

  case 82: /* AddExp: MulExp  */
#line 718 "parser.y"
               {
         (yyval.addExp) = (yyvsp[0].mulExp);
    }
#line 2180 "parser.cpp"
    break;

  case 83: /* AddExp: AddExp ADD MulExp  */
#line 721 "parser.y"
                        {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].addExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].mulExp)));
        tmp -> addOp(BinOpType::OP_ADD);
        (yyval.addExp) = (Exp*)(tmp);
        (yyval.addExp) -> addType(ExpType::ET_BIN);
        printf("AddExp Find\n");
    }
#line 2194 "parser.cpp"
    break;

  case 84: /* AddExp: AddExp SUB MulExp  */
#line 730 "parser.y"
                        {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].addExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].mulExp)));
        tmp -> addOp(BinOpType::OP_SUB);
        (yyval.addExp) = (Exp*)(tmp);
        (yyval.addExp) -> addType(ExpType::ET_BIN);
        printf("AddExp Find\n");
    }
#line 2208 "parser.cpp"
    break;

  case 85: /* RelExp: AddExp  */
#line 741 "parser.y"
               {
        (yyval.relExp) = (yyvsp[0].addExp);
        printf("RelExp Find\n");
    }
#line 2217 "parser.cpp"
    break;

  case 86: /* RelExp: RelExp LT AddExp  */
#line 745 "parser.y"
                       {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].relExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].addExp)));
        tmp -> addOp(BinOpType::OP_LT);
        (yyval.relExp) = (Exp*)(tmp);
        (yyval.relExp) -> addType(ExpType::ET_BIN);
        printf("RelExp Find\n");
    }
#line 2231 "parser.cpp"
    break;

  case 87: /* RelExp: RelExp GT AddExp  */
#line 754 "parser.y"
                       {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].relExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].addExp)));
        tmp -> addOp(BinOpType::OP_GT);
        (yyval.relExp) = (Exp*)(tmp);
        (yyval.relExp) -> addType(ExpType::ET_BIN);
        printf("RelExp Find\n");
    }
#line 2245 "parser.cpp"
    break;

  case 88: /* RelExp: RelExp LTE AddExp  */
#line 763 "parser.y"
                        {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].relExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].addExp)));
        tmp -> addOp(BinOpType::OP_LTE);
        (yyval.relExp) = (Exp*)(tmp);
        (yyval.relExp) -> addType(ExpType::ET_BIN);
        printf("RelExp Find\n");
    }
#line 2259 "parser.cpp"
    break;

  case 89: /* RelExp: RelExp GTE AddExp  */
#line 772 "parser.y"
                        {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].relExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].addExp)));
        tmp -> addOp(BinOpType::OP_GTE);
        (yyval.relExp) = (Exp*)(tmp);
        (yyval.relExp) -> addType(ExpType::ET_BIN);
        printf("RelExp Find\n");
    }
#line 2273 "parser.cpp"
    break;

  case 90: /* EqExp: RelExp  */
#line 783 "parser.y"
              {
        (yyval.eqExp) = (yyvsp[0].relExp);
        printf("EqExp Find\n");
    }
#line 2282 "parser.cpp"
    break;

  case 91: /* EqExp: EqExp EQ RelExp  */
#line 787 "parser.y"
                      {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].eqExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].relExp)));
        tmp -> addOp(BinOpType::OP_EQ);
        (yyval.eqExp) = (Exp*)(tmp);
        (yyval.eqExp) -> addType(ExpType::ET_BIN);
        printf("EqExp Find\n");
    }
#line 2296 "parser.cpp"
    break;

  case 92: /* EqExp: EqExp NEQ RelExp  */
#line 796 "parser.y"
                       {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].eqExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].relExp)));
        tmp -> addOp(BinOpType::OP_NEQ);
        (yyval.eqExp) = (Exp*)(tmp);
        (yyval.eqExp) -> addType(ExpType::ET_BIN);
        printf("EqExp Find\n");
    }
#line 2310 "parser.cpp"
    break;

  case 93: /* LAndExp: EqExp  */
#line 807 "parser.y"
               {
        (yyval.lAndExp) = (yyvsp[0].eqExp);
        printf("LAndExp Find\n");
    }
#line 2319 "parser.cpp"
    break;

  case 94: /* LAndExp: LAndExp AND EqExp  */
#line 811 "parser.y"
                        {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].lAndExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].eqExp)));
        tmp -> addOp(BinOpType::OP_AND);
        (yyval.lAndExp) = (Exp*)(tmp);
        (yyval.lAndExp) -> addType(ExpType::ET_BIN);
        printf("LAndExp Find\n");
    }
#line 2333 "parser.cpp"
    break;

  case 95: /* LOrExp: LAndExp  */
#line 822 "parser.y"
                {
        (yyval.lOrExp) = (yyvsp[0].lAndExp);
        printf("LOrExp Find\n");
    }
#line 2342 "parser.cpp"
    break;

  case 96: /* LOrExp: LOrExp OR LAndExp  */
#line 826 "parser.y"
                        {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr((yyvsp[-2].lOrExp)));
        tmp -> addExp2(ExpPtr((yyvsp[0].lAndExp)));
        tmp -> addOp(BinOpType::OP_OR);
        (yyval.lOrExp) = (Exp*)(tmp);
        (yyval.lOrExp) -> addType(ExpType::ET_BIN);
        printf("LOrExp Find\n");
    }
#line 2356 "parser.cpp"
    break;

  case 97: /* ConstExp: AddExp  */
#line 837 "parser.y"
                 {
        (yyval.constExp) = new ConstExp();
        (yyval.constExp) -> addExp(ExpPtr((yyvsp[0].addExp)));
        printf("ConstExp Find\n");
    }
#line 2366 "parser.cpp"
    break;


#line 2370 "parser.cpp"

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

#line 842 "parser.y"



int main(int argc, char *argv[]){
    /* int c; */
    ++ argv;
    if (argc > 0) yyin = fopen(argv[0], "r");
    else {
        printf("No input file\n");
        return 0;
    }
    yyparse();
    std::cout << root << std::endl;
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








