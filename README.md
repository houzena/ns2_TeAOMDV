# ns2_TeAOMDV

一个基于ns2网络模拟，对AOMDV协议进行修改，形成的带信任评估、按需、多路径协议的小课题，基于elsevier期刊https://www.sciencedirect.com/science/article/pii/S1084804515002982

1，模拟机制<br>
每个节点都仿佛是一个独立的线程，节点与其它节点的接触，无非发包和收包。<br>
顺着时间轴，模拟各种事件的发生。<br>
<br>
2，代码模拟过程<br>
仅看AODV所在的层，收到一个包都会经历以下流程（如果自己是源点，那么会收到来自应用层的数据包）:<br>
最先是Recv函数收到包，Recv函数收到一个指向一个包的指针作为实参，如果是控制包（PT_AODV），则交给RecvAODV()；是数据包就交给Resolve()去解析。<br>
在Resolve()中，会判断是否会有可用的路由，有的话会将包传给forward()（下面转发包都是调用这个函数），接着进入调度队列；没有的话，则先将包放入缓存队列中，然后调用sendRequest()，然后就会向周围广播请求包，请求建立到目的节点的路由。<br>
在RecvAODV()中，还会根据控制包的类型，进一步调用不同的函数，常用的包类型有Request请求包，Reply答复包。如果收到Request包，如果自己不是目的地，也没有通向目的地的路由，那么就接着广播转发Request包；反之，则发送Reply包到<b>上一跳</b>(发给它Request包的节点)，表示已经找到目的节点了，就这样上一跳又以单播发Reply给上上一跳...直到源点收到Reply，便建立了路由。<br>
<br>
当然，收包的时候会做一系列判断，不接受过期的包（ttl为0），重复的包？不能让包的发送形成环路。<br>
<br>
除了应用层发包，在AODV里也可以设置定时器，自己定时发送包，比如hello包就可以当作一个模板，发包事件最后会放到调度队列，最好设置一个随机delay，不然同一时刻有很多事件要执行，而会发生有一部分事件不会被执行，还需要注意的是，放入调度队列的包不要调用free()，不然会引发段错误。<br>
<br>
3，混杂监听<br>
tap监测（本来如果某个单播包的接收节点不是自己，那么这个包不会来到AODV所在的层次来，加了这个就能来了）<br>
<br>
4，测数据，调参数<br>
  /datatest<br>
  
  有相关问题可以直接给我发邮件

