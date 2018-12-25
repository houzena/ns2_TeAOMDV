

#ifndef __aomdv_rtable_h__
#define __aomdv_rtable_h__

#include <assert.h>
#include <sys/types.h>
#include <config.h>
#include <lib/bsd-list.h>
#include <scheduler.h>

#define CURRENT_TIME    Scheduler::instance().clock()
#define INFINITY2        0xff

/*
   AOMDV Neighbor Cache Entry
*/
class AOMDV_Neighbor {
        friend class AOMDV;
        friend class aomdv_rt_entry;
 public:
        AOMDV_Neighbor(u_int32_t a) ;
        /**********以下为修改内容**************/
        void set_TV();
        double get_TV();

        /**ŒÆËãÖ±œÓÐÅÈÎ**/
        void set_direct_trust();

        void add_control_forward_corrects(){control_forward_corrects++;}
        void add_control_forward_alls(){control_forward_alls++;}

        void add_data_forward_corrects(){data_forward_corrects++;}
        void add_data_forward_alls(){data_forward_alls++;}


        /**ŒÆËãÍÆŒöÐÅÈÎ**/
        void set_recommen_trust();

        /**ŒÆËã×ª·¢œ»»õÂÊ**/
        void set_fdr();

        /**ŒÆËã»î¶¯¶È**/
        void set_ad();
        void add_cn_rt(){ cn_rt++; }
        void add_cn_ar(){ cn_ar++; }

        /**********以上为修改内容**************/

protected:
        LIST_ENTRY(AOMDV_Neighbor) nb_link;
        nsaddr_t        nb_addr;
        double          nb_expire;      // ALLOWED_HELLO_LOSS * HELLO_INTERVAL
    /**********以下为修改内容**************/
        static double  TrustThreshold;  //信任阈值
        bool black_list;    //信任黑名单标志
        double TV;
        /*计算直接信任**/

        double direct_trust;      //直接信任

        double control_forward_rate;     //控制包正确转发率
        int control_forward_corrects;   //累积正确转发控制包数
        int control_forward_alls;   //累积总转发控制包数

        double data_forward_rate;     //控制包正确转发率
        int data_forward_corrects;   //累积正确转发控制包数
        int data_forward_alls;   //累积总转发控制包数


        /**计算推荐信任**/

        double recommen_trust;
        double fenzi;	//计算时所需要的分子分母
        double fenmu;

        /**ŒÆËã×ª·¢œ»»õÂÊ**/

        double fdr;   //×ª·¢œ»»õÂÊ
        double fdr_period;  //Ìœ²â·¢ËÍÖÜÆÚ

        /**ŒÆËã»î¶¯¶È**/

        double ad;      //»î¶¯¶È
        int cn_rt;      //ÀÛ»ý±»ÐÅÈÎœÚµã
        int cn_ar;      //ÀÛŒÆœÓŽ¥œÚµã
        double ac;      //ÈÎÒâŽóÓÚ0³£Á¿£¬¿ØÖÆÒ»žöº¯ÊýµÄÇ÷ÓÚ1µÄËÙ¶È
    /**********ÒÔÉÏÊÇÐÞžÄÄÚÈÝ**************/

};

LIST_HEAD(aomdv_ncache, AOMDV_Neighbor);

 // AOMDV code
/*
   AOMDV Path list data structure
*/
class AOMDV_Path {
        friend class AOMDV;
        friend class aomdv_rt_entry;
 public:
        AOMDV_Path(nsaddr_t nh, u_int16_t h, double expire_time, nsaddr_t lh=0) {
           nexthop = nh;
           hopcount = h;
           expire = expire_time;
           ts = Scheduler::instance().clock();
           lasthop = lh;
           // CHANGE
           error = false;
           // CHANGE
        }
	void printPath() {
	  printf("                        %6d  %6d  %6d\n", nexthop, hopcount, lasthop);
	}
	void printPaths() {
	  AOMDV_Path *p = this;
	  for (; p; p = p->path_link.le_next) {
	    p->printPath();
	  }
	}

 protected:
        LIST_ENTRY(AOMDV_Path) path_link;
        nsaddr_t        nexthop;    // nexthop address
        u_int16_t       hopcount;   // hopcount through this nexthop
        double          expire;     // expiration timeout
        double          ts;         // time when we saw this nexthop
        nsaddr_t        lasthop;    // lasthop address
        // CHANGE
        bool            error;
        // CHANGE
};

LIST_HEAD(aomdv_paths, AOMDV_Path);

/*
   AOMDV Precursor list data structure
*/
class AOMDV_Precursor {
        friend class AOMDV;
        friend class aomdv_rt_entry;
 public:
        AOMDV_Precursor(u_int32_t a) { pc_addr = a; }

 protected:
        LIST_ENTRY(AOMDV_Precursor) pc_link;
        nsaddr_t        pc_addr;	// precursor address
};

LIST_HEAD(aomdv_precursors, AOMDV_Precursor);


/*
  Route Table Entry
*/

class aomdv_rt_entry {
        friend class aomdv_rtable;
        friend class AOMDV;
	friend class LocalRepairTimer;
 public:
        aomdv_rt_entry();
        ~aomdv_rt_entry();

        void            nb_insert(nsaddr_t id);
        AOMDV_Neighbor*  nb_lookup(nsaddr_t id);

 // AOMDV code
        AOMDV_Path*   path_insert(nsaddr_t nexthop, u_int16_t hopcount, double expire_time, nsaddr_t lasthop=0);

        AOMDV_Path*   path_lookup(nsaddr_t id);  // lookup path by nexthop

        AOMDV_Path*   disjoint_path_lookup(nsaddr_t nexthop, nsaddr_t lasthop);
        bool         new_disjoint_path(nsaddr_t nexthop, nsaddr_t lasthop);

        AOMDV_Path*   path_lookup_lasthop(nsaddr_t id);   // lookup path by lasthop
        void         path_delete(nsaddr_t id);           // delete path by nexthop
        void         path_delete(void);                  // delete all paths
        void         path_delete_longest(void);          // delete longest path
        bool         path_empty(void);                   // is the path list empty?
        AOMDV_Path*   path_find(void);                    // find the path that we got first
        AOMDV_Path*   path_findMinHop(void);              // find the shortest path
        u_int16_t    path_get_max_hopcount(void);
        u_int16_t    path_get_min_hopcount(void);
        double       path_get_max_expiration_time(void);
        void         path_purge(void);
        void            pc_insert(nsaddr_t id);
        AOMDV_Precursor* pc_lookup(nsaddr_t id);
        void 		pc_delete(nsaddr_t id);
        void 		pc_delete(void);
        bool 		pc_empty(void);

        double          rt_req_timeout;         // when I can send another req
        u_int8_t        rt_req_cnt;             // number of route requests

		  // AOMDV code
        u_int8_t        rt_flags;
 protected:
        LIST_ENTRY(aomdv_rt_entry) rt_link;

        nsaddr_t        rt_dst;
        u_int32_t       rt_seqno;
	/* u_int8_t 	rt_interface; */
 // AOMDV code
        u_int16_t       rt_hops;             // hop count
        u_int16_t       rt_advertised_hops;  // advertised hop count
	int 		rt_last_hop_count;	// last valid hop count
 // AOMDV code
        aomdv_paths      rt_path_list;     // list of paths
        u_int32_t       rt_highest_seqno_heard;
        int             rt_num_paths_;
	bool rt_error;

	/* list of precursors */
        aomdv_precursors rt_pclist;
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
        aomdv_ncache          rt_nblist;
};


/*
  The Routing Table
*/

class aomdv_rtable {
 public:
	aomdv_rtable() { LIST_INIT(&rthead); }

        aomdv_rt_entry*       head() { return rthead.lh_first; }

        aomdv_rt_entry*       rt_add(nsaddr_t id);
        void                 rt_delete(nsaddr_t id);
        aomdv_rt_entry*       rt_lookup(nsaddr_t id);
 // AOMDV code
	void                 rt_dumptable();
	bool                 rt_has_active_route();

 private:
        LIST_HEAD(aomdv_rthead, aomdv_rt_entry) rthead;
};

#endif /* _aomdv__rtable_h__ */
