

#ifndef __teaomdv_rtable_h__
#define __teaomdv_rtable_h__

#include <assert.h>
#include <sys/types.h>
#include <config.h>
#include <lib/bsd-list.h>
#include <scheduler.h>
#include <vector>
#define CURRENT_TIME    Scheduler::instance().clock()
#define INFINITY2        0xff
#define TRUST_TIME 2.1	//刷新信任值的时间间隔，也当作计算信任值时的窗口大小
#define PROB_T 0.2 //发送探测包的时间间隔
/*
   TEAOMDV Neighbor Cache Entry
*/
struct node1{
	int uid;		//包的id
	double time;	//包的发出时间
	bool ok;		//包是否已被成功转发
};
class TEAOMDV_Neighbor {
        friend class TEAOMDV;
        friend class teaomdv_rt_entry;
 public:
        TEAOMDV_Neighbor(u_int32_t a) ;
        /**********以下为修改内容**************/
        void set_TV();
        double get_TV();
        void TV_init();
        /**1、计算直接信任**/
        void set_direct_trust();

        void add_control_forward_corrects(){control_forward_corrects++;}
        void add_control_forward_alls(){control_forward_alls++;}

        void add_data_forward_corrects(){data_forward_corrects++;}
        void add_data_forward_alls(){data_forward_alls++;}


        /**2、计算推荐信任**/
        void set_recommen_trust();

        /**3、计算交货率**/
        void set_delivery_ratio();

        /**4、计算活动度**/
        void set_activity_degree();
        /**********以上为修改内容**************/

protected:
        LIST_ENTRY(TEAOMDV_Neighbor) nb_link;
        nsaddr_t        nb_addr;
        double          nb_expire;      // ALLOWED_HELLO_LOSS * HELLO_INTERVAL
    /**********以下为修改内容**************/
        static double  TrustThreshold;  //信任阈值
        bool black_list;    //信任黑名单标志
        double TV; //对该邻居的综合信任度
        /*1、计算直接信任**/

        double direct_trust;      //直接信任

        double control_forward_rate;     //控制包正确转发率
        int control_forward_corrects;   //累积正确转发控制包数
        int control_forward_alls;   //累积总转发控制包数


        double data_forward_rate;     //控制包正确转发率
        int data_forward_corrects;   //累积正确转发控制包数
        int data_forward_alls;   //累积总转发控制包数
        struct node1 cbr_f[1000];
        struct node1 ptteaomdv_f[100];
        int cbr_num;
        int ptteaomdv_num;
        /**2、计算推荐信任**/

        double recommen_trust;
        double fenzi;	//计算时所需要的分子分母
        double fenmu;

       /**3、计算交货率**/

        double delivery_ratio; //交货率
        double prob_recvs;	//收到的探测包数
        double prob_stime;

        /**4、计算活动度**/

        double activity_degree; //活动度
        double trusted_nbs;	//被信任的邻居数
        double interact_nbs; //接触的邻居数
        static double a_constant; //一个常量，控制计算活动度的函数趋于1的速度


    /**********以下为修改内容**************/

};

LIST_HEAD(teaomdv_ncache, TEAOMDV_Neighbor);

 // TEAOMDV code
/*
   TEAOMDV Path list data structure
*/
class TEAOMDV_Path {
        friend class TEAOMDV;
        friend class teaomdv_rt_entry;
 public:
        TEAOMDV_Path(nsaddr_t nh, u_int16_t h, double expire_time, nsaddr_t lh,double fpt,double rpt) {
           nexthop = nh;
           hopcount = h;
           expire = expire_time;
           ts = Scheduler::instance().clock();
           lasthop = lh;
           // CHANGE
           error = false;
           // CHANGE
           FPT = fpt;
           RPT = rpt;
        }
	void printPath() {
	  printf("                        %6d  %6d  %6d\n", nexthop, hopcount, lasthop);
	}
	void printPaths() {
	  TEAOMDV_Path *p = this;
	  for (; p; p = p->path_link.le_next) {
	    p->printPath();
	  }
	}

 protected:
        LIST_ENTRY(TEAOMDV_Path) path_link;
        nsaddr_t        nexthop;    // nexthop address
        u_int16_t       hopcount;   // hopcount through this nexthop
        double          expire;     // expiration timeout
        double          ts;         // time when we saw this nexthop
        nsaddr_t        lasthop;    // lasthop address
        // CHANGE
        bool            error;
        // new filed
        double			FPT;    // forward path trust
        double			RPT; 	// reverse path trust
};

LIST_HEAD(teaomdv_paths, TEAOMDV_Path);

/*
   TEAOMDV Precursor list data structure
*/
class TEAOMDV_Precursor {
        friend class TEAOMDV;
        friend class teaomdv_rt_entry;
 public:
        TEAOMDV_Precursor(u_int32_t a) { pc_addr = a; }

 protected:
        LIST_ENTRY(TEAOMDV_Precursor) pc_link;
        nsaddr_t        pc_addr;	// precursor address
};

LIST_HEAD(teaomdv_precursors, TEAOMDV_Precursor);


/*
  Route Table Entry
*/

class teaomdv_rt_entry {
        friend class teaomdv_rtable;
        friend class TEAOMDV;
	friend class LocalRepairTimer;
 public:
        teaomdv_rt_entry();
        ~teaomdv_rt_entry();

        void            nb_insert(nsaddr_t id);
        TEAOMDV_Neighbor*  nb_lookup(nsaddr_t id);

 // TEAOMDV code
        TEAOMDV_Path*   path_insert(nsaddr_t nexthop, u_int16_t hopcount, double expire_time, nsaddr_t lasthop,double fpt,double rpt);

        TEAOMDV_Path*   path_lookup(nsaddr_t id);  // lookup path by nexthop

        TEAOMDV_Path*   disjoint_path_lookup(nsaddr_t nexthop, nsaddr_t lasthop);
        bool         new_disjoint_path(nsaddr_t nexthop, nsaddr_t lasthop);

        TEAOMDV_Path*   path_lookup_lasthop(nsaddr_t id);   // lookup path by lasthop
        void         path_delete(nsaddr_t id);           // delete path by nexthop
        void         path_delete(void);                  // delete all paths
        void         path_delete_longest(void);          // delete longest path
        bool         path_empty(void);                   // is the path list empty?
        TEAOMDV_Path*   path_find(void);                    // find the path that we got first
        TEAOMDV_Path*   path_findMinHop(void);              // find the shortest path
        u_int16_t    path_get_max_hopcount(void);
        u_int16_t    path_get_min_hopcount(void);
        double       path_get_max_expiration_time(void);
        void         path_purge(void);
        void            pc_insert(nsaddr_t id);
        TEAOMDV_Precursor* pc_lookup(nsaddr_t id);
        void 		pc_delete(nsaddr_t id);
        void 		pc_delete(void);
        bool 		pc_empty(void);

        double          rt_req_timeout;         // when I can send another req
        u_int8_t        rt_req_cnt;             // number of route requests

		  // TEAOMDV code
        u_int8_t        rt_flags;
 protected:
        LIST_ENTRY(teaomdv_rt_entry) rt_link;

        nsaddr_t        rt_dst;
        u_int32_t       rt_seqno;
	/* u_int8_t 	rt_interface; */
 // TEAOMDV code
        u_int16_t       rt_hops;             // hop count
        u_int16_t       rt_advertised_hops;  // advertised hop count
	int 		rt_last_hop_count;	// last valid hop count
 // TEAOMDV code
        teaomdv_paths      rt_path_list;     // list of paths
        u_int32_t       rt_highest_seqno_heard;
        int             rt_num_paths_;
	bool rt_error;

	/* list of precursors */
        teaomdv_precursors rt_pclist;
        double          rt_expire;     		// when entry expires

#define RTF_DOWN 0
#define RTF_UP 1
#define RTF_IN_REPAIR 2

        /*
         *  Must receive 4 errors within 3 seconds in order to mark
         *  the route down.
        u_int8_t        rt_errors;      // error count
        double          rt_error_time;
#define MAX_RT_ERROR            4       // errors
#define MAX_RT_ERROR_TIME       3       // seconds
         */

#define MAX_HISTORY	3
	double 		rt_disc_latency[MAX_HISTORY];
	char 		hist_indx;
        int 		rt_req_last_ttl;        // last ttl value used
	// last few route discovery latencies
	// double 		rt_length [MAX_HISTORY];
	// last few route lengths

        /*
         * a list of neighbors that are using this route.
         */
        teaomdv_ncache          rt_nblist;
};


/*
  The Routing Table
*/

class teaomdv_rtable {
 public:
	teaomdv_rtable() { LIST_INIT(&rthead); }

        teaomdv_rt_entry*       head() { return rthead.lh_first; }

        teaomdv_rt_entry*       rt_add(nsaddr_t id);
        void                 rt_delete(nsaddr_t id);
        teaomdv_rt_entry*       rt_lookup(nsaddr_t id);
 // TEAOMDV code
	void                 rt_dumptable();
	bool                 rt_has_active_route();

 private:
        LIST_HEAD(teaomdv_rthead, teaomdv_rt_entry) rthead;
};

#endif /* _teaomdv__rtable_h__ */
