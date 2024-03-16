grammar J;

start : expression EOF;

expression
    : array
    | monad
    | dyad
    | fork;

array
    : '{' (NUMBER (',' NUMBER)*)? '}'
    ;

monad
    : VERB array
    ;

dyad
    : array VERB array
    ;

fork 
    : (VERB | expression) (VERB | expression) (VERB : expression)
    ;

VERB
    : '+'
    | '-'
    | '*'
    | '%'
    | '+/'
    | '*/'
    | '|.'
    | '|:'
    | ',.'
    | '$.'
    | '<.'
    | '>.'
    | '='
    | '~:'
    | '<'
    | '>'
    | '|'
    | '^'
    ;

NUMBER : [0-9]+('.'[0-9]+)?;
WS : [ \t\r\n]+ -> skip;
