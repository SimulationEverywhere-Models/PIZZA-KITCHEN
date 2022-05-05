[top]
components : pizzero@Pizzero
out 	: out outHorno outPedidos
in 	: in inHorno
link 	: outSalida@pizzero out 
link	: in inPedidos@pizzero
link	: outPedidos@pizzero outPedidos
link	: outHorno@pizzero outHorno
link	: inHorno inHorno@pizzero

[pizzero]
