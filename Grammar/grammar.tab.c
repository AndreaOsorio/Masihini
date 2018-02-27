/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "grammar.y" /* yacc.c:339  */

    #include <stdio.h>
    #include <stdlib.h>
    int yylex (void);
    void yyerror (char const *);

#line 73 "grammar.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "grammar.tab.h".  */
#ifndef YY_YY_GRAMMAR_TAB_H_INCLUDED
# define YY_YY_GRAMMAR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    FLOAT = 258,
    INT = 259,
    ID = 260,
    STRING = 261,
    TRUE = 262,
    FALSE = 263,
    IF = 264,
    ELSE = 265,
    WHILE = 266,
    VAR = 267,
    FUNC = 268,
    TYPE_INT = 269,
    TYPE_FLOAT = 270,
    TYPE_BOOLEAN = 271,
    TYPE_STRING = 272,
    L_BRACE = 273,
    R_BRACE = 274,
    L_PARENTHESIS = 275,
    R_PARENTHESIS = 276,
    L_BRACKET = 277,
    R_BRACKET = 278,
    ADD = 279,
    SUBS = 280,
    MULT = 281,
    DIV = 282,
    EQ = 283,
    NE = 284,
    GT = 285,
    LT = 286,
    LE = 287,
    GE = 288,
    COMPARE = 289,
    AND = 290,
    OR = 291,
    NOT = 292,
    SEMICOLON = 293,
    COLON = 294,
    COMMA = 295,
    RETURN = 296,
    STATIC = 297,
    RUN = 298,
    SPEAK = 299,
    ACCEL = 300,
    ROT = 301,
    STOP = 302,
    JUMP = 303,
    VOID = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GRAMMAR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 174 "grammar.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   185

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  181

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    66,    66,    69,    70,    73,    76,    77,    80,    83,
      86,    87,    88,    91,    94,    95,    96,   100,   101,   102,
     103,   107,   108,   111,   114,   115,   116,   119,   123,   126,
     127,   128,   129,   130,   131,   134,   139,   140,   141,   142,
     143,   147,   150,   153,   154,   159,   161,   162,   165,   166,
     169,   173,   174,   177,   178,   181,   182,   186,   187,   188,
     189,   190,   193,   196,   197,   201,   203,   204,   207,   208,
     211,   216,   219,   220,   221,   224,   227,   228,   229,   233,
     234,   235,   236,   239,   243,   244,   245,   246,   247,   248,
     249,   252,   253,   256,   257
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FLOAT", "INT", "ID", "STRING", "TRUE",
  "FALSE", "IF", "ELSE", "WHILE", "VAR", "FUNC", "TYPE_INT", "TYPE_FLOAT",
  "TYPE_BOOLEAN", "TYPE_STRING", "L_BRACE", "R_BRACE", "L_PARENTHESIS",
  "R_PARENTHESIS", "L_BRACKET", "R_BRACKET", "ADD", "SUBS", "MULT", "DIV",
  "EQ", "NE", "GT", "LT", "LE", "GE", "COMPARE", "AND", "OR", "NOT",
  "SEMICOLON", "COLON", "COMMA", "RETURN", "STATIC", "RUN", "SPEAK",
  "ACCEL", "ROT", "STOP", "JUMP", "VOID", "$accept", "global_declaration",
  "global_declaration_1", "run", "func", "func_1", "func_2", "func_3",
  "block", "block_1", "type", "expression", "expression_1", "expression_2",
  "expression_3", "relation", "relation_1", "relation_2", "statement",
  "cycle", "condition", "condition_1", "declaration", "declaration_1",
  "declaration_2", "declaration_3", "func_call", "func_call_1",
  "func_call_2", "system_func", "system_func_1", "system_func_2",
  "assignment", "assignment_1", "assignment_2", "assignment_3", "exp",
  "exp_1", "term", "term_1", "factor", "factor_1", "var_cte", "var_cte_1",
  "var_cte_2", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF -120

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-120)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -12,    16,    36,    44,    69,   -12,  -120,    33,  -120,    37,
    -120,    57,   127,    60,  -120,  -120,  -120,  -120,    -9,    82,
     115,  -120,  -120,  -120,   105,   107,     0,   124,     4,    59,
     118,   119,   133,   133,   133,   133,   133,  -120,    22,  -120,
    -120,  -120,   117,  -120,  -120,    23,  -120,   150,  -120,  -120,
      65,    87,    14,    14,    97,  -120,  -120,    18,  -120,  -120,
     103,    40,    79,    87,    87,    67,  -120,  -120,  -120,  -120,
    -120,  -120,    87,  -120,  -120,   151,   151,   134,    97,  -120,
      31,    78,  -120,   136,  -120,  -120,   -14,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,  -120,    97,    97,  -120,    97,    97,
      97,    97,    97,  -120,    97,    97,  -120,    97,    97,  -120,
     138,   139,  -120,   140,  -120,   125,   142,  -120,  -120,   126,
     144,  -120,    87,  -120,  -120,    73,    65,    87,  -120,  -120,
    -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,  -120,   105,   105,  -120,   147,   162,  -120,    31,
      87,  -120,  -120,   145,    -3,  -120,  -120,   130,  -120,  -120,
     148,   152,   105,  -120,  -120,   127,    87,    87,  -120,   132,
      35,  -120,   149,  -120,   105,   162,  -120,  -120,   124,  -120,
    -120
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     0,     0,     4,     1,     0,     2,     0,
       3,     0,     0,     0,    17,    18,    19,    20,     0,     0,
       0,    50,    45,    47,     0,     0,     0,     0,     0,    82,
       0,     0,     0,     0,     0,     0,     0,    13,     0,    40,
      38,    39,     0,    51,    37,     0,     5,     0,    46,    49,
      82,    82,     0,     0,    82,    70,    22,    26,    65,    67,
      34,    74,    78,    82,    82,    82,    61,    57,    58,    59,
      60,    16,    82,    14,    36,     0,     0,     0,    82,    54,
       0,    26,    52,     0,    86,    85,    94,    87,    89,    88,
      84,    80,    83,    81,    21,    82,    82,    23,    82,    82,
      82,    82,    82,    28,    82,    82,    71,    82,    82,    75,
       0,     0,    64,     0,    62,     0,     0,     7,     6,     0,
       0,    56,    82,    53,    79,    82,    82,    82,    90,    92,
      24,    27,    25,    29,    35,    30,    32,    31,    33,    72,
      73,    76,    77,     0,     0,    63,     0,     0,    48,     0,
      82,    66,    69,     0,     0,    41,    15,     0,     8,    55,
       0,    93,     0,    44,    42,     0,    82,    82,    91,     0,
       0,    68,     0,    43,     0,     0,     9,    93,    12,    10,
      11
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -120,  -120,   168,  -120,    -2,    99,     2,  -120,  -119,   141,
     -45,   -49,   128,  -120,    84,   -46,  -120,    46,  -120,  -120,
    -120,  -120,   177,  -120,  -120,   -25,    56,  -120,    32,  -120,
     116,  -120,  -120,  -120,  -120,  -115,    27,  -120,     8,  -120,
    -120,   131,  -120,  -120,    24
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     8,    46,   117,   158,   176,    27,    37,
      18,    55,    56,    97,   130,    57,   103,   133,    38,    39,
      40,   164,    41,    22,    48,    23,    42,    82,   123,    43,
      66,   114,    44,    58,   151,    59,    60,   106,    61,   109,
      62,    91,    92,   128,   129
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      76,    80,    83,    49,    81,    29,   126,   162,   127,    30,
     152,    31,     4,    20,   110,   111,   113,    84,    85,    86,
      87,    88,    89,   115,   154,   155,    47,    29,     4,    21,
       1,    30,   120,    31,     4,   163,     6,    14,    15,    16,
      17,    71,    21,   169,    32,    33,    34,    35,    36,   131,
     131,   171,   121,    95,    96,   178,   174,     7,    32,    33,
      34,    35,    36,    72,   104,   105,    32,    33,    34,    35,
      36,   122,    75,   149,     9,   175,    12,    80,   153,    50,
      19,    51,    11,    52,    53,    78,    79,    78,   112,    52,
      53,    52,    53,    78,   148,   150,    54,    52,    53,   124,
      13,   160,    54,    24,    54,   107,   108,    78,    90,    90,
      54,    52,    53,    95,    96,   141,   142,    78,   172,    25,
     170,    52,    53,    26,    54,   134,   134,   134,   134,   134,
      28,   139,   140,    98,    99,   100,   101,    45,    63,    64,
     102,    14,    15,    16,    17,   135,   136,   137,   138,    67,
      68,    69,    70,    65,    77,    74,   116,   119,   125,   143,
     144,   145,   147,   146,    21,   124,   156,   157,   161,   165,
     173,   166,   177,    10,   167,   118,   180,   179,     5,    73,
     132,   159,    94,     0,    93,   168
};

static const yytype_int16 yycheck[] =
{
      45,    50,    51,    28,    50,     5,    20,    10,    22,     9,
     125,    11,    12,    22,    63,    64,    65,     3,     4,     5,
       6,     7,     8,    72,   143,   144,    22,     5,    12,    38,
      42,     9,    78,    11,    12,    38,     0,    14,    15,    16,
      17,    19,    38,   162,    44,    45,    46,    47,    48,    95,
      96,   166,    21,    35,    36,   174,    21,    13,    44,    45,
      46,    47,    48,    41,    24,    25,    44,    45,    46,    47,
      48,    40,    49,   122,     5,    40,    39,   126,   127,    20,
      20,    22,    49,    24,    25,    20,    21,    20,    21,    24,
      25,    24,    25,    20,   119,    22,    37,    24,    25,    21,
      43,   150,    37,    21,    37,    26,    27,    20,    52,    53,
      37,    24,    25,    35,    36,   107,   108,    20,   167,     4,
     165,    24,    25,    18,    37,    98,    99,   100,   101,   102,
      23,   104,   105,    30,    31,    32,    33,    13,    20,    20,
      37,    14,    15,    16,    17,    99,   100,   101,   102,    33,
      34,    35,    36,    20,     4,    38,     5,    23,    22,    21,
      21,    21,    20,    38,    38,    21,    19,     5,    23,    39,
      38,    23,    23,     5,    22,    76,   178,   175,     1,    38,
      96,   149,    54,    -1,    53,   161
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    42,    51,    52,    12,    72,     0,    13,    53,     5,
      52,    49,    39,    43,    14,    15,    16,    17,    60,    20,
      22,    38,    73,    75,    21,     4,    18,    58,    23,     5,
       9,    11,    44,    45,    46,    47,    48,    59,    68,    69,
      70,    72,    76,    79,    82,    13,    54,    22,    74,    75,
      20,    22,    24,    25,    37,    61,    62,    65,    83,    85,
      86,    88,    90,    20,    20,    20,    80,    80,    80,    80,
      80,    19,    41,    59,    38,    49,    60,     4,    20,    21,
      61,    65,    77,    61,     3,     4,     5,     6,     7,     8,
      76,    91,    92,    91,    62,    35,    36,    63,    30,    31,
      32,    33,    37,    66,    24,    25,    87,    26,    27,    89,
      61,    61,    21,    61,    81,    61,     5,    55,    55,    23,
      65,    21,    40,    78,    21,    22,    20,    22,    93,    94,
      64,    65,    64,    67,    86,    67,    67,    67,    67,    86,
      86,    88,    88,    21,    21,    21,    38,    20,    75,    61,
      22,    84,    85,    61,    58,    58,    19,     5,    56,    78,
      61,    23,    10,    38,    71,    39,    23,    22,    94,    58,
      60,    85,    61,    38,    21,    40,    57,    23,    58,    56,
      54
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    54,    54,    55,    56,
      57,    57,    57,    58,    59,    59,    59,    60,    60,    60,
      60,    61,    61,    62,    63,    63,    63,    64,    65,    66,
      66,    66,    66,    66,    66,    67,    68,    68,    68,    68,
      68,    69,    70,    71,    71,    72,    73,    73,    74,    74,
      75,    76,    76,    77,    77,    78,    78,    79,    79,    79,
      79,    79,    80,    81,    81,    82,    83,    83,    84,    84,
      85,    86,    87,    87,    87,    88,    89,    89,    89,    90,
      90,    90,    90,    91,    92,    92,    92,    92,    92,    92,
      92,    93,    93,    94,    94
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     0,     7,     3,     3,     3,     4,
       2,     3,     2,     2,     2,     5,     2,     1,     1,     1,
       1,     2,     1,     2,     2,     2,     0,     1,     2,     2,
       2,     2,     2,     2,     0,     1,     2,     1,     1,     1,
       1,     5,     6,     3,     1,     5,     4,     1,     4,     1,
       1,     1,     3,     2,     1,     3,     1,     2,     2,     2,
       2,     2,     2,     2,     1,     2,     4,     1,     4,     1,
       1,     2,     2,     2,     0,     2,     2,     2,     0,     3,
       2,     2,     0,     1,     1,     1,     1,     1,     1,     1,
       2,     4,     1,     3,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 66 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1387 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 69 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1393 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 70 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1399 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 73 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1405 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 76 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1411 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 77 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1417 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 80 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1423 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 83 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1429 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 86 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1435 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 87 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1441 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 88 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1447 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 91 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1453 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 94 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1459 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 95 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1465 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 96 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1471 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 100 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1477 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 101 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1483 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 102 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1489 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 103 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1495 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 107 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1501 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 108 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1507 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 111 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1513 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 114 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1519 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 115 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1525 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 119 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1531 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 126 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1537 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 127 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1543 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 128 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1549 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 129 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1555 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 130 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1561 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 131 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1567 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 134 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1573 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 139 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1579 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 140 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1585 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 141 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1591 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 142 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1597 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 143 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1603 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 147 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1609 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 150 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1615 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 153 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1621 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 154 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1627 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 159 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1633 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 161 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1639 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 162 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1645 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 165 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1651 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 166 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1657 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 169 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1663 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 173 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1669 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 174 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1675 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 177 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1681 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 178 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1687 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 181 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1693 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 182 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1699 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 186 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1705 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 187 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1711 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 188 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1717 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 189 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1723 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 190 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1729 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 193 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1735 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 196 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1741 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 197 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1747 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 201 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1753 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 203 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1759 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 204 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1765 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 207 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1771 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 208 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1777 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 211 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1783 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 216 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1789 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 219 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1795 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 220 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1801 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 221 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1807 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 224 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1813 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 227 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1819 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 228 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1825 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 229 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1831 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 233 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1837 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 234 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1843 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 235 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1849 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 236 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1855 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 239 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1861 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 243 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1867 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 244 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1873 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 245 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1879 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 246 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1885 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 247 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1891 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 248 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1897 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 249 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1903 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 252 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1909 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 253 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1915 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 256 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1921 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 257 "grammar.y" /* yacc.c:1646  */
    {;}
#line 1927 "grammar.tab.c" /* yacc.c:1646  */
    break;


#line 1931 "grammar.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 260 "grammar.y" /* yacc.c:1906  */


void yyerror(char const *x)
{
    printf("Error %s\n", x);
    exit(1);
}
