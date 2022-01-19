define(AUTHOR, William Shakespeare)dnl
A Midsummer Night's Dream
by AUTHOR
`AUTHOR' here is from quoting.  # -> W. Shakespeare
define(newline,`line
break')
a newline here
define(`Version2', A - 1)99Version2:Version2_  Version22
Version2(arg1, arg2) Version2 (junk) garbage(trash)Version2()
define(`definenum', `define(`num',`99')')
num
definenum num
define(`definenum', define(`num',`99'))
num
definenum
define(`definedefineX',`define(`defineX',`define(`X',`xxx')')')
defineX X
definedefineX X
defineX X
define(`stmt',``define(`Y',`yyy')'')
stmt
Y
define(`plus',`+')
plus
plus()plus
define(`oper',`plus')
oper()oper
oper`'oper
define(`Bye',`Byer world.')
Bye.
Hello.
define(`args', ``NAME',`Marie'')
define(args)
NAME
args(define(`args',`Rachel'))
args
define(`msg',`undefine(`msg')Secret message.')
msg
msg
I said, ``Quote me.''

define(`VERSION',`A1')
VERSION # VERSION `quote' unmatched`
`#' VERSION
#changecom(/*,*/)
#VERSION `quote' /* VERSION
#`quote' ` */ VERSION
#changecom()
dnl These two lines will not result
dnl in any output
ifelse(`
This is a comment
spanning more than
one line.
')dnl
define(`def')
`def' is ifdef(`def',,not )defined.
ifelse(a,b,c,d)
eval(7*6)
eval(7/3+100)
len(`hello')
substr(`hello',1,3)
index(`hello',`llo')
define(`ALPHA', `abcdefghijklmnopqrstuvwxyz')
define(`ALPHA_UPR',`ABCDEFGHIJKLMNOPQRSTUVWXYZ')
define(`ROT13',`nopqrstuvwxyzabcdefghijklm')
translit(`abc ebg13', ALPHA, ALPHA_UPR)
translit(`abc ebg13', ALPHA, ROT13)
define(`eng',`engineering')
substr(`engineer',0,3)
translit(`rat',ALPHA,ROT13)
define(`len',`ifelse($1,,0,`eval(1+len(substr($1,1)))')')
define(`count',``$0': $# arguments')
count
count()
count(1)
count(2)
define(`list',`$`'*: $*; $`'@: $@')
list(len(`abc'),`len(`abc')')
shift(1,2,`abc',4)
shift(one)
define(`echolast',`ifelse(eval($#<2),1,`$1`'',`echolast(shift($@))')')
echolast(one,two,three)
dnl pushing and popping
define(`USED',1)
define(`proc',
`pushdef(`USED',10)pushdef(`UNUSED',20)dnl
`'`USED' = USED, `UNUSED' = UNUSED`'dnl
`'popdef(`USED',`UNUSED')')
proc
USED
define(`reverse',`ifelse($1,,,
`reverse(substr($1,1))`'substr($1,0,1)')')
reverse drawer: reverse(`drawer')
define(`reverse',`ifelse($#,0,``$0'',$1,,,
`reverse(substr($1,1))`'substr($1,0,1)')')
reverse drawer: reverse(`drawer')
dnl ========
dnl Loops
dnl ========
dnl Loops example, x is a holding place, pushdef define the value of x
define(`for',`ifelse($#,0,``$0'',`ifelse(eval($2<=$3),1,
`pushdef(`$1',$2)$4`'popdef(`$1')$0(`$1',incr($2),$3,`$4')')')')
for n = for(`x',1,5,`x-')...
for(`x',1,3,`for(`x',0,4,`eval(5-x)')__')
dnl ==============
dnl foreach macro
dnl ==============
define(`foreach',`ifelse(eval($#>2),1,
`pushdef(`last_$1',eval($#==3))dnl
`'pushdef(`$1',`$3')$2`'popdef(`$1')dnl
`'popdef(`last_$1')dnl
`'ifelse(eval($#>3),1,`$0(`$1',`$2',shift(shift(shift($@))))')')')
define(`everyone',``Tom',`Dick',`Harry'')
foreach(`one',`one`'ifelse(last_one,0,`| and |')',everyone)
dnl =============
dnl while macro
dnl =============
define(`while',`ifelse($#,0,``$0'',eval($1+0),1,`$2`'$0($@)')')
define(`POW2',2)
The starting value of `POW2' is POW2.
while(`POW2<=1000',`define(`POW2',eval(POW2*2))')
The answer is POW2`'.
dnl ========================
dnl Buffers and redirection
dnl ========================
divert(1)
zzz
divert
define(`z',9)
undivert(1)
dnl =====================
dnl aliasing and renaming
dnl =====================
define(`strlen',`len($@)')
strlen(`hello')
dnl ====================
dnl literal quotes
dnl ====================
define(`LQ',`changequote(<,>)`dnl'
changequote`'')
define(`RQ',`changequote(<,>)dnl`
'changequote`'')
define(myne,`It`'RQ()s mine!')
LQ()RQ()myne''
indir(`define',`SIZE',78)
SIZE
indir(`SIZE')
define(do,$1($2,$3,$4,$5))
do(`define',``x'',4)
x
dnl =====================
dnl recursion
dnl =====================
define(`sigma',`ifelse(eval($1<=1),1,$1,`eval($1+sigma(decr($1)))')')
sigma(3)
define(`sigma',`ifelse(eval($1<1),1,$2,`sigma(decr($1),eval($2+$1))')')
sigma(100)
dnl ==================
dnl arrays and hashes
dnl ==================
define(`my var',`a strange one')
my var is defn(`my var').
define(`_set',`define(`$1[$2]',`$3')')
define(`_get',`defn(`$1[$2]')')
_set(`myarray',1,`alpha')
_get(`myarray',1)
_set(`myarray',`alpha',`omega')
_get(`myarray',_get(`myarray',1))
defn(`myarray[alpha]')
dnl ===========
dnl  new subsr ( substry one character at a time )
dnl ===========
define(`substr',`ifelse($#,0,``$0'',
$#,2,`substr($@,eval(len(`$1')-$2))',
`ifelse(eval($3<=0),1,,
`builtin(`substr',`$1',$2,1)`'substr(
`$1',eval($2+1),eval($3-1))')')')
define(`eng',`engineering')
substr(`engineer',0,3)




