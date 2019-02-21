BEGIN{
	fsDROPS=0;
	numfs=0;
	numfr=0;

}
{
	event = $1;
	time = $2;
	node = $3;
	ip1 = $14;
	ip2 = $15;
	len = length(node);

	if(len == 3)
	{
		node_ = substr(node,2,1);
		
	}
	if(len == 4)
	{
		node_ = substr(node,2,2);
		
	}

	

		trace_type = $4;
		flag = $5;
		uid = $6;
		pkt_type = $7;
		pkt_size = $8;	
	

	
		if(event=="s"&&trace_type=="AGT"&&pkt_type=="cbr")
			numfs++;
		if(event=="r"&&trace_type=="AGT"&&pkt_type=="cbr")
			numfr++;
	
}
END{
	if(numfs==0) numfs=1;
	printf("s:%d r:%d ratio: %f\n",numfs,numfr,1.0*numfr/numfs);
}
