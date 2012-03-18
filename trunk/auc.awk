{
if(NR==1){
	y=y0=P;
	auc=dx=0;
	th=$3
}
else if(th!=$3){
	th=$3;
	auc+=dx*(y+y0);
	y0=y;
	dx=0;
}
dx+=$2-$1;
y-=$1;
}
END{
	auc+=dx*(y+y0);
	auc/=(2*P*N);
	print auc
}
