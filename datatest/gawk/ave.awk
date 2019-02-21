BEGIN{
	sum=0;
	num=0;

}
{
	if(length($4)>0)
	{sum+=$4;
	num++;
	}
	
	
}
END{
	
	printf("average: %f\n",1.0*sum/num);
}
