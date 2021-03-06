grammar Main;

prog: direct* (funct)*;

direct : '#' include;
include : 'include' (STR | LIB);

funct : deffunc | declarfunc;

	
expr: execfunc		# exfunc
	| elemrv		# elemarray
	| 'sizeof' '(' TYPE ')' # sizeof
	| VAR ('++'|'--')	# postop
	| ('++'|'--') VAR	# preop 
	| expr ('*'|'/'|'%') expr # multdivmod
	| expr ('+'|'-') expr # addsub
	| INT			# const
	| VAR			# var
	| CHAR 		# char
	| '(' expr ')'  	# par
	| expr compare expr 	# cmp
	| expr '&' expr         # etBin
	| expr '^' expr         # ouExBin
	| expr '|' expr         # ouBin
	| (VAR|elemlv) ('*='|'/='|'+='|'-='|'%='|'&='|'^='|'|='|'=') expr # Assignement
	;

compare: ('<'|'>') '='?
	| ('!'|'=') '='
	;

elemlv : VAR '[' expr ']'
	;

elemrv : VAR '[' expr ']'
	;

ifins: 'if' '(' expr ')' (statement|block) elseifins* elseins?;

elseifins : 'else if' '(' expr ')' (statement|block) ;

elseins: 'else' (statement|block) ; 

whileins : 'while' '(' expr ')' (statement|block) ;

forins : 'for' '(' expr? ';' expr? ';' expr? ')' (statement|block) ;

declarvar: TYPE VAR (',' VAR)* ';'
	;

declararray: TYPE VAR '[' INT ']' ';' 
	;

defvar : TYPE VAR '=' expr ';' #defWithDeclar
	;

deffunc : TYPE VAR '(' paramdec? ')' block #defFuncNormal
	| 'void' VAR '(' paramdec? ')' block #defFuncVoid
	;

declarfunc : TYPE VAR '(' paramdec? ')' ';' #declarFuncNormal
	| 'void' VAR '(' paramdec? ')' ';' #declarFuncVoid
	;  

execfunc : 'putchar' '(' expr ')' #putchar
	| 'getchar' '(' ')' #getchar
	| VAR '(' param? ')' #normalExec
	;

block : '{' statement* '}';

exprstat : expr ';';

statement : ret
	| defvar
	| exprstat 
	| declarvar
	| declararray
	| ifins
	| whileins
	| forins
	;

ret : 'return' expr? ';';

paramdec : TYPE VAR (',' TYPE VAR)*;

param :  expr (',' expr)*;

TYPE: 'int'
	| 'char'
	| 'int64_t'
	;

INT : [0-9]+ ;
VAR : [a-zA-Z][a-zA-Z0-9]*;
CHAR : '\'\\'CHARESC '\''
	| '\'' ~['\\\r\n\t] '\'';
CHARESC : [abefnrtv'"?\\];
STR : '"' FILENAME '"';
LIB : '<' FILENAME '>';
FILENAME : [a-zA-Z0-9]+('.'[a-zA-Z0-9]+)+;
WS : [\t\r\n ] -> skip;


