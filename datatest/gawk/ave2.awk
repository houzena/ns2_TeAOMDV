BEGIN{
	sum=0;
	num=0;

}
{
	if(length($1)>0)
	{sum+=$1;
	num++;
	}
	
	
}
END{
	
	printf("latency average: %f\n",1.0*sum/num);
}
