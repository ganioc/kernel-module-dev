divert(-1)
# HTML utility macro
define(`H2_COUNT',0)
# The H2_COUNT macro is redefined every time the H2 macro is used:
define(`H2',
	`define(`H2_COUNT',incr(H2_COUNT))<h2>H2_COUNT. $1</h2>')
divert(1)dnl
dnl
dnl The dnl macro causes m4 to discard the rest of the line
dnl
H2(First Section)
H2(Second Section)
H2(Conclusion)
dnl
divert(0)dnl
dnl
<HTML>
undivert(1)dnl One of the queues is being pushed to output.
<HTML>

