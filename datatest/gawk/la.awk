BEGIN{
	for(i=1;i<=25000;i++)
		l[i]=-1;
	for(i=1;i<=25000;i++)
		r[i]=-1;

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
		{
			if(uid>=1&&uid<25000)
			{
				l[uid] = time;
			}
		}
			
		if(event=="r"&&trace_type=="AGT"&&pkt_type=="cbr")
		{
			if(uid>=1&&uid<25000)
			{
				r[uid] = time;
			}
		}
	
}
END{
	num = 0.0;
	sum = 0.0;
	for(i=1;i<=25000;i++)
	{
		if(l[i]!=-1&&r[i]!=-1)
		{
			num = num + 1;
			sum = sum + r[i]-l[i];
			
		}
	}
	printf("%f\n",sum*1.0/num);
}
