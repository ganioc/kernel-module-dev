len(`hello')
substr(`hello',2)
define(`ALPHA',`abcdefg')
define(`ALPHA_UPR',`ABCDEFG')
define(`ROT13',`defgabc')
translit(`abc',ALPHA,ALPHA_UPR)
translit(`abc',ALPHA,ROT13)
define(`eng',`engineering')
engineer
substr(`engineer',0,3)
substr(`engineer',1,3)


