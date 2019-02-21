BEGIN{
	deav=0.0;
	laav=0.0;
	flag=0.0;
	num=0;

}
{

	if($1=="2"&&$2=="m") flag=1;
	if(flag==1)
	{
		
		if($1=="average:") deav+=$2;
		if($1=="latency") {laav+=$3;num++;}	
	}
	if(num==3)
	{
		printf("average: %f  %f\n",deav/3.0,laav/3.0);
		deav=0;laav=0;
		num=0;	
	}
}
END{
	
	
}
