/*
 * Copyright (c) 2008, Marcello Caleffi, <marcello.caleffi@unina.it>,
 * http://wpage.unina.it/marcello.caleffi
 *
 * The AOMDV code has been developed at DIET, Department of Electronic
 * and Telecommunication Engineering, University of Naples "Federico II"
 *
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 *
 * The copyright of this module includes the following
 * linking-with-specific-other-licenses addition:
 *
 * In addition, as a special exception, the copyright holders of
 * this module give you permission to combine (via static or
 * dynamic linking) this module with free software programs or
 * libraries that are released under the GNU LGPL and with code
 * included in the standard release of ns-2 under the Apache 2.0
 * license or under otherwise-compatible licenses with advertising
 * requirements (or modified versions of such code, with unchanged
 * license).  You may copy and distribute such a system following the
 * terms of the GNU GPL for this module and the licenses of the
 * other code concerned, provided that you include the source code of
 * that other code when and as the GNU GPL requires distribution of
 * source code.
 *
 * Note that people who make modified versions of this module
 * are not obligated to grant this special exception for their
 * modified versions; it is their choice whether to do so.  The GNU
 * General Public License gives permission to release a modified
 * version without this exception; this exception also makes it
 * possible to release a modified version which carries forward this
 * exception.
 *
 */



/*
Copyright (c) 1997, 1998 Carnegie Mellon University.  All Rights
Reserved. 

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The AODV code developed by the CMU/MONARCH group was optimized and tuned by Samir Das and Mahesh Marina, University of Cincinnati. The work was partially done in Sun Microsystems.
*/



#include <aomdv/aomdv_rtable.h>
#include <aomdv/aomdv.h>
#include <cmath>
//#include <cmu/aodv/aodv.h>

/*
  The Routing Table
*/

aomdv_rt_entry::aomdv_rt_entry()
{
int i;

 rt_req_timeout = 0.0;
 rt_req_cnt = 0;

 rt_dst = 0;
 rt_seqno = 0;
 // AOMDV code
 rt_last_hop_count = INFINITY2;
 rt_advertised_hops = INFINITY2;
 LIST_INIT(&rt_path_list);
 rt_highest_seqno_heard = 0;
 rt_num_paths_ = 0;
 rt_error = false;

 LIST_INIT(&rt_pclist);
 rt_expire = 0.0;
 rt_flags = RTF_DOWN;

 /*
 rt_errors = 0;
 rt_error_time = 0.0;
 */


 for (i=0; i < MAX_HISTORY; i++) {
   rt_disc_latency[i] = 0.0;
 }
 hist_indx = 0;
 rt_req_last_ttl = 0;

 LIST_INIT(&rt_nblist);

}


aomdv_rt_entry::~aomdv_rt_entry()
{
AOMDV_Neighbor *nb;

 while((nb = rt_nblist.lh_first)) {
   LIST_REMOVE(nb, nb_link);
   delete nb;
 }

 // AOMDV code
AOMDV_Path *path;

 while((path = rt_path_list.lh_first)) {
   LIST_REMOVE(path, path_link);
   delete path;
 }

AOMDV_Precursor *pc;

 while((pc = rt_pclist.lh_first)) {
   LIST_REMOVE(pc, pc_link);
   delete pc;
 }

}


void
aomdv_rt_entry::nb_insert(nsaddr_t id)
{
AOMDV_Neighbor *nb = new AOMDV_Neighbor(id);

 assert(nb);
 nb->nb_expire = 0;
 LIST_INSERT_HEAD(&rt_nblist, nb, nb_link);
printf("<#message#>");
}


AOMDV_Neighbor*
aomdv_rt_entry::nb_lookup(nsaddr_t id)
{
AOMDV_Neighbor *nb = rt_nblist.lh_first;

 for(; nb; nb = nb->nb_link.le_next) {
   if(nb->nb_addr == id)
     break;
 }
 return nb;

}

// AOMDV code
AOMDV_Path*
aomdv_rt_entry::path_insert(nsaddr_t nexthop, u_int16_t hopcount, double expire_time, nsaddr_t lasthop,double fpt,double rpt) {
AOMDV_Path *path = new AOMDV_Path(nexthop, hopcount, expire_time, lasthop,fpt,rpt);

   assert(path);
#ifdef DEBUG
   fprintf(stderr, "%s: (%d\t%d)\n", __FUNCTION__, path->nexthop, path->hopcount);
#endif // DEBUG

   /*
    * Insert path at the end of the list
    */
AOMDV_Path *p = rt_path_list.lh_first;
   if (p) {
      for(; p->path_link.le_next; p = p->path_link.le_next)
	/* Do nothing */;
      LIST_INSERT_AFTER(p, path, path_link);
   }
   else {
      LIST_INSERT_HEAD(&rt_path_list, path, path_link);
   }
   rt_num_paths_ += 1;

   return path;
}

AOMDV_Path*
aomdv_rt_entry::path_lookup(nsaddr_t id)
{
AOMDV_Path *path = rt_path_list.lh_first;

 for(; path; path = path->path_link.le_next) {
   if (path->nexthop == id)
      return path;
 }
 return NULL;

}

AOMDV_Path*
aomdv_rt_entry::disjoint_path_lookup(nsaddr_t nexthop, nsaddr_t lasthop)
{
AOMDV_Path *path = rt_path_list.lh_first;

 for(; path; path = path->path_link.le_next) {
   if ( (path->nexthop == nexthop) && (path->lasthop == lasthop) )
      return path;
 }
 return NULL;

}

/* Returns true if no path exists (for this route entry) which has 'nexthop' as next hop or 'lasthop' as last hop.*/
bool
aomdv_rt_entry::new_disjoint_path(nsaddr_t nexthop, nsaddr_t lasthop)
{
  AOMDV_Path *path = rt_path_list.lh_first;

  for(; path; path = path->path_link.le_next) {
    if ( (path->nexthop == nexthop) || (path->lasthop == lasthop) )
      return false;
  }
  return true;

}


AOMDV_Path*
aomdv_rt_entry::path_lookup_lasthop(nsaddr_t id)
{
AOMDV_Path *path = rt_path_list.lh_first;

 for(; path; path = path->path_link.le_next) {
   if (path->lasthop == id)
      return path;
 }
 return NULL;

}


void
aomdv_rt_entry::path_delete(nsaddr_t id) {
AOMDV_Path *path = rt_path_list.lh_first;

 for(; path; path = path->path_link.le_next) {
   if(path->nexthop == id) {
     LIST_REMOVE(path,path_link);
     delete path;
     rt_num_paths_ -= 1;
     break;
   }
 }

}

void
aomdv_rt_entry::path_delete(void) {
AOMDV_Path *path;

 while((path = rt_path_list.lh_first)) {
   LIST_REMOVE(path, path_link);
   delete path;
 }
 rt_num_paths_ = 0;
}

void
aomdv_rt_entry::path_delete_longest(void) {
AOMDV_Path *p = rt_path_list.lh_first;
AOMDV_Path *path = NULL;
u_int16_t max_hopcount = 0;

 for(; p; p = p->path_link.le_next) {
   if(p->hopcount > max_hopcount) {
      assert (p->hopcount != INFINITY2);
      path = p;
      max_hopcount = p->hopcount;
   }
 }

 if (path) {
     LIST_REMOVE(path, path_link);
     delete path;
     rt_num_paths_ -= 1;
 }
}

bool
aomdv_rt_entry::path_empty(void) {
AOMDV_Path *path;

 if ((path = rt_path_list.lh_first)) {
    assert (rt_num_paths_ > 0);
    return false;
 }
 else {
    assert (rt_num_paths_ == 0);
    return true;
 }
}

AOMDV_Path*
aomdv_rt_entry::path_findMinHop(void)
{
AOMDV_Path *p = rt_path_list.lh_first;
AOMDV_Path *path = NULL;
u_int16_t min_hopcount = 0xffff;

 for (; p; p = p->path_link.le_next) {
   if (p->hopcount < min_hopcount) {
      path = p;
      min_hopcount = p->hopcount;
   }
 }

 return path;
}

AOMDV_Path*
aomdv_rt_entry::path_find(void) {
AOMDV_Path *p = rt_path_list.lh_first;

   return p;
}

u_int16_t
aomdv_rt_entry::path_get_max_hopcount(void)
{
AOMDV_Path *path = rt_path_list.lh_first;
u_int16_t max_hopcount = 0;

 for(; path; path = path->path_link.le_next) {
   if(path->hopcount > max_hopcount) {
      max_hopcount = path->hopcount;
   }
 }
 if (max_hopcount == 0) return INFINITY2;
 else return max_hopcount;
}

u_int16_t
aomdv_rt_entry::path_get_min_hopcount(void)
{
AOMDV_Path *path = rt_path_list.lh_first;
u_int16_t min_hopcount = INFINITY2;

 for(; path; path = path->path_link.le_next) {
   if(path->hopcount < min_hopcount) {
      min_hopcount = path->hopcount;
   }
 }
 return min_hopcount;
}

double
aomdv_rt_entry::path_get_max_expiration_time(void) {
AOMDV_Path *path = rt_path_list.lh_first;
double max_expire_time = 0;

 for(; path; path = path->path_link.le_next) {
   if(path->expire > max_expire_time) {
      max_expire_time = path->expire;
   }
 }
 return max_expire_time;
}

void
aomdv_rt_entry::path_purge(void) {
double now = Scheduler::instance().clock();
bool cond;

 do {
 AOMDV_Path *path = rt_path_list.lh_first;
  cond = false;
  for(; path; path = path->path_link.le_next) {
    if(path->expire < now) {
      cond = true;
      LIST_REMOVE(path, path_link);
      delete path;
      rt_num_paths_ -= 1;
      break;
    }
  }
 } while (cond);
}

void
aomdv_rt_entry::pc_insert(nsaddr_t id)
{
	if (pc_lookup(id) == NULL) {
	AOMDV_Precursor *pc = new AOMDV_Precursor(id);

 		assert(pc);
 		LIST_INSERT_HEAD(&rt_pclist, pc, pc_link);
	}
}


AOMDV_Precursor*
aomdv_rt_entry::pc_lookup(nsaddr_t id)
{
AOMDV_Precursor *pc = rt_pclist.lh_first;

 for(; pc; pc = pc->pc_link.le_next) {
   if(pc->pc_addr == id)
   	return pc;
 }
 return NULL;

}

void
aomdv_rt_entry::pc_delete(nsaddr_t id) {
AOMDV_Precursor *pc = rt_pclist.lh_first;

 for(; pc; pc = pc->pc_link.le_next) {
   if(pc->pc_addr == id) {
     LIST_REMOVE(pc,pc_link);
     delete pc;
     break;
   }
 }

}

void
aomdv_rt_entry::pc_delete(void) {
AOMDV_Precursor *pc;

 while((pc = rt_pclist.lh_first)) {
   LIST_REMOVE(pc, pc_link);
   delete pc;
 }
}

bool
aomdv_rt_entry::pc_empty(void) {
AOMDV_Precursor *pc;

 if ((pc = rt_pclist.lh_first)) return false;
 else return true;
}

/*
  The Routing Table
*/

aomdv_rt_entry*
aomdv_rtable::rt_lookup(nsaddr_t id)
{
aomdv_rt_entry *rt = rthead.lh_first;

 for(; rt; rt = rt->rt_link.le_next) {
   if(rt->rt_dst == id)
     break;
 }
 return rt;

}

void
aomdv_rtable::rt_delete(nsaddr_t id)
{
aomdv_rt_entry *rt = rt_lookup(id);

 if(rt) {
   LIST_REMOVE(rt, rt_link);
   delete rt;
 }

}

aomdv_rt_entry*
aomdv_rtable::rt_add(nsaddr_t id)
{
aomdv_rt_entry *rt;

 assert(rt_lookup(id) == 0);
 rt = new aomdv_rt_entry;
 assert(rt);
 rt->rt_dst = id;
 LIST_INSERT_HEAD(&rthead, rt, rt_link);
 return rt;
}

// AOMDV code
void aomdv_rtable::rt_dumptable() {
  aomdv_rt_entry *rt = rthead.lh_first;
  while(rt != 0) {
    printf("%6s  %6s  ", "Dest", "Seq#");
    printf("%6s  %6s  %6s  %6s\n", "Advhop", "Nxthop", "Hopcnt", "Lsthop");
    printf("%6d  %6d  ", rt->rt_dst, rt->rt_seqno);
    printf("%6d\n", rt->rt_advertised_hops);
    /* Print path list for this route entry. */
    AOMDV_Path *paths = rt->rt_path_list.lh_first;
    paths->printPaths();
    printf("\n");
    rt = rt->rt_link.le_next;
  }
}

// AOMDV code
bool aomdv_rtable::rt_has_active_route() {
  /* Go through list of route entries to see if there exists
     any valid route entry */
  aomdv_rt_entry *rt = rthead.lh_first;
  while(rt != 0) {
    if (rt->rt_flags == RTF_UP)
      return true;
    rt = rt->rt_link.le_next;
  }
  return false;
}
/***********here are the changes***********/
AOMDV_Neighbor::AOMDV_Neighbor(u_int32_t a)
{
	nb_addr = a;
	TV= 1;
	data_forward_corrects = 0;
	data_forward_alls = 0;
	TV_init();
	cbr_num = 0;
	ptaomdv_num = 0;
	black_list=0;
}

double AOMDV_Neighbor::TrustThreshold = 0.70;	//设置阈值
double AOMDV_Neighbor::a_constant = 0.1;

void AOMDV_Neighbor::TV_init()
{

    control_forward_corrects = 0;   //累积正确转发控制包数
    control_forward_alls = 0;   //累积总转发控制包数
    if(data_forward_alls >= 5)
    {
    	data_forward_corrects = 0;   //累积正确转发控制包数
    	data_forward_alls = 0;   //累积总转发控制包数
   }
    fenzi = 0;	//计算时所需要的分子分母
    fenmu = 0;

    prob_recvs = 0;
    prob_stime = CURRENT_TIME;

    trusted_nbs = 2;
    interact_nbs = 2;

}
void AOMDV_Neighbor::set_TV()
{
	set_direct_trust();
    set_recommen_trust();
    set_delivery_ratio();
    set_activity_degree();

    TV=0.35*direct_trust+0.1*recommen_trust+0.2*TV+0.225*delivery_ratio+0.125*activity_degree;
}
double AOMDV_Neighbor::get_TV()
{
    return TV;
}
void AOMDV_Neighbor::set_direct_trust()
{
	int tot=0;
	for(int i=0;i<ptaomdv_num;i++)
	{
		if(ptaomdv_f[i].ok == true)
		    	{
		    		control_forward_corrects++;
		    		control_forward_alls++;
		    	}
		    	else if(ptaomdv_f[i].time+1.5<CURRENT_TIME)
		    	{
		    		control_forward_alls++;
		    	}
		    	else
		    	{
		    		ptaomdv_f[tot].ok = false;
		    		ptaomdv_f[tot].uid = ptaomdv_f[i].uid;
		    		ptaomdv_f[tot].time = ptaomdv_f[i].time;
		    		tot++;
		    	}
	}
	ptaomdv_num = tot;
	if(control_forward_alls >= 2)
    control_forward_rate = 1.0*control_forward_corrects/control_forward_alls;
	else control_forward_rate = 0.9;

    tot=0;
    for(int i=0; i<cbr_num ;i++)
    {
    	if(cbr_f[i].ok == true)
    	{
    		data_forward_corrects++;
    		data_forward_alls++;
    	}
    	else if(cbr_f[i].time+1.5<CURRENT_TIME)
    	{
    		data_forward_alls++;
    	}
    	else
    	{
    		cbr_f[tot].ok = false;
    		cbr_f[tot].uid = cbr_f[i].uid;
    		cbr_f[tot].time = cbr_f[i].time;
    		tot++;
    	}
    }
    cbr_num = tot;
    if(data_forward_alls >= 5)
    data_forward_rate = 1.0*data_forward_corrects/data_forward_alls;
    else data_forward_rate = 0.9;

    direct_trust = 0.2*control_forward_rate+0.8*data_forward_rate;
}
void AOMDV_Neighbor::set_recommen_trust()
{
	if(fabs(fenmu)>=0.1)
	recommen_trust=fenzi/fenmu;
	else  recommen_trust = 0.8;

}
void AOMDV_Neighbor::set_delivery_ratio()
{
	if(CURRENT_TIME - prob_stime > 1.5)
		delivery_ratio = prob_recvs/( (CURRENT_TIME - prob_stime)/PROB_T );
	else delivery_ratio = 0.8;
}
void AOMDV_Neighbor::set_activity_degree()
{
	activity_degree = 0.5*(1-(1/trusted_nbs + a_constant))+0.5*(1-(1/interact_nbs + a_constant));
}
/**************end***************/
