%{
#include <string>
#include "parser.hpp"

// Typedef for token type
#define YYSTYPE std::string

// Declare the lexer function
extern int yylex();
%}

%%

[ \t\n]             ; // Skip whitespace
[0-9]+(\.[0-9]+)?   { yylval = yytext; return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval = yytext; return IDENTIFIER; }
"+"                 { return VERB_MONADIC; }
"-"                 { return VERB_MONADIC; }
"*"                 { return VERB_MONADIC; }
"%"                 { return VERB_MONADIC; }
"|"                 { return VERB_MONADIC; }
"^"                 { return VERB_MONADIC; }
"="                 { return VERB_DYADIC; }
"~:"                { return VERB_DYADIC; }
"<"                 { return VERB_DYADIC; }
">"                 { return VERB_DYADIC; }
"<."                { return VERB_DYADIC; }
">."                { return VERB_DYADIC; }
"/"                 { return ADVERB; }
"\\"                 { return ADVERB; }
"@"                 { return CONJUNCTION; }
"&"                 { return CONJUNCTION; }
"("                 { return PARENTHESES_OPEN; }
")"                 { return PARENTHESES_CLOSE; }
.                   { /* Handle unknown characters */ }

%%

// Additional C++ code
int yywrap() {
    return 1;
}