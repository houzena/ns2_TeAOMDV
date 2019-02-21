
#ifndef __teaomdv_packet_h__
#define __teaomdv_packet_h__

//#include <config.h>
//#include "teaomdv.h"
#define TEAOMDV_MAX_ERRORS 100


/* =====================================================================
   Packet Formats...
   ===================================================================== */
#define TEAOMDVTYPE_HELLO  	0x01
#define TEAOMDVTYPE_RREQ   	0x02
#define TEAOMDVTYPE_RREP   	0x04
#define TEAOMDVTYPE_RERR   	0x08
#define TEAOMDVTYPE_RREP_ACK  	0x10
//新增包
#define TEAOMDVTYPE_RCOM     0x03
#define TEAOMDVTYPE_PROB    0x05
#define TEAOMDVTYPE_PTA    0x09

/*
 * TEAOMDV Routing Protocol Header Macros
 */
#define HDR_TEAOMDV(p)		((struct hdr_teaomdv*)hdr_teaomdv::access(p))
#define HDR_TEAOMDV_REQUEST(p)  	((struct hdr_teaomdv_request*)hdr_teaomdv::access(p))
#define HDR_TEAOMDV_REPLY(p)	((struct hdr_teaomdv_reply*)hdr_teaomdv::access(p))
#define HDR_TEAOMDV_ERROR(p)	((struct hdr_teaomdv_error*)hdr_teaomdv::access(p))
#define HDR_TEAOMDV_RREP_ACK(p)	((struct hdr_teaomdv_rrep_ack*)hdr_teaomdv::access(p))
//新增包
#define HDR_TEAOMDV_RCOM(p)	((struct hdr_teaomdv_recommen*)hdr_teaomdv::access(p))
#define HDR_TEAOMDV_PROB(p)  ((struct hdr_teaomdv_probe*)hdr_teaomdv::access(p))
#define HDR_TEAOMDV_PTA(p)  ((struct hdr_teaomdv_pta*)hdr_teaomdv::access(p))
/*
 * General TEAOMDV Header - shared by all formats
 */
struct hdr_teaomdv {
        u_int8_t        ah_type;
	/*
        u_int8_t        ah_reserved[2];
        u_int8_t        ah_hopcount;
	*/
		// Header access methods
	static int offset_; // required by PacketHeaderManager
	inline static int& offset() { return offset_; }
	inline static hdr_teaomdv* access(const Packet* p) {
		return (hdr_teaomdv*) p->access(offset_);
	}
};

struct hdr_teaomdv_request {
        u_int8_t        rq_type;	// Packet Type
        u_int8_t        reserved[2];
        u_int8_t        rq_hop_count;   // Hop Count
        u_int32_t       rq_bcast_id;    // Broadcast ID

        nsaddr_t        rq_dst;         // Destination IP Address
        u_int32_t       rq_dst_seqno;   // Destination Sequence Number
        nsaddr_t        rq_src;         // Source IP Address
        u_int32_t       rq_src_seqno;   // Source Sequence Number

        double          rq_timestamp;   // when REQUEST sent;
					// used to compute route discovery latency
// TEAOMDV code
        nsaddr_t        rq_first_hop;  // First Hop taken by the RREQ
        double			RT;		// required trust
        double			FPT;    // forward path trust
        double			RPT; 	// reverse path trust

  // This define turns on gratuitous replies- see aodv.cc for implementation contributed by
  // Anant Utgikar, 09/16/02.
  //#define RREQ_GRAT_RREP	0x80

  inline int size() { 
  int sz = 0;
  /*
  	sz = sizeof(u_int8_t)		// rq_type
	     + 2*sizeof(u_int8_t) 	// reserved
	     + sizeof(u_int8_t)		// rq_hop_count
	     + sizeof(double)		// rq_timestamp
	     + sizeof(u_int32_t)	// rq_bcast_id
	     + sizeof(nsaddr_t)		// rq_dst
	     + sizeof(u_int32_t)	// rq_dst_seqno
	     + sizeof(nsaddr_t)		// rq_src
	     + sizeof(u_int32_t);	// rq_src_seqno
  */
  	sz = 7*sizeof(u_int32_t);
// TEAOMDV code
   sz += sizeof(nsaddr_t);    // rq_first_hop 
   sz += 3*sizeof(double);
  	assert (sz >= 0);
	return sz;
  }
};

struct hdr_teaomdv_reply {
        u_int8_t        rp_type;        // Packet Type
        u_int8_t        reserved[2];
        u_int8_t        rp_hop_count;           // Hop Count
        nsaddr_t        rp_dst;                 // Destination IP Address
        u_int32_t       rp_dst_seqno;           // Destination Sequence Number
        nsaddr_t        rp_src;                 // Source IP Address
        double	         rp_lifetime;            // Lifetime
	
        double          rp_timestamp;           // when corresponding REQ sent;
						// used to compute route discovery latency
// TEAOMDV code
        u_int32_t       rp_bcast_id;           // Broadcast ID of the corresponding RREQ
        nsaddr_t        rp_first_hop;
        double			RT;		// required trust
        double			FPT;    // forward path trust
        double			RPT; 	// reverse path trust
						
  inline int size() { 
  int sz = 0;

  	sz = 6*sizeof(u_int32_t);
// TEAOMDV code
   if (rp_type == TEAOMDVTYPE_RREP) {
      sz += sizeof(u_int32_t);   // rp_bcast_id
      sz += sizeof(nsaddr_t);    // rp_first_hop
      sz += 3*sizeof(double);
   }
  	assert (sz >= 0);
	return sz;
  }

};
/**************以下为修改内容**************/
const int MAX_NB = 50;
//推荐信任包
struct hdr_teaomdv_recommen {
        u_int8_t        rc_type;        // Packet Type


        nsaddr_t		nb_No[MAX_NB];		 //�ھӵ�ַ
        double          nb_dt[MAX_NB];		 //�����߶Ը��ھӵ�ֱ������ֵ
        int 			nb_num;				//�ھӸ���
        int				it_num;

  inline int size() {
  int sz = 0;

  	sz = sizeof(u_int8_t);

// TEAOMDV code
   if (rc_type == TEAOMDVTYPE_RCOM) {

      sz += sizeof(nsaddr_t)*nb_num+sizeof(double)*nb_num+sizeof(int)*2;
   }
  	assert (sz >= 0);
	return sz;
  }

};
//探测包
struct hdr_teaomdv_probe {
        u_int8_t        rp_type;        // Packet Type

  inline int size() {
  int sz = 0;

  	sz = sizeof(u_int8_t);
// TEAOMDV code
   if (rp_type == TEAOMDVTYPE_PROB) {

   }
  	assert (sz >= 0);
	return sz;
  }

};
//汇报不信任节点的PTA包
struct hdr_teaomdv_pta {
    u_int8_t        re_type;                // Type

    nsaddr_t        unreachable_dst;
    nsaddr_t		unreachable_lasthop;
    u_int32_t       unreachable_dst_seqno;
//debug
    nsaddr_t		sender;

inline int size() {
int sz = 0;

	sz = sizeof(u_int8_t)+sizeof(u_int32_t)+3*sizeof(nsaddr_t);
assert(sz);
    return sz;
}

};
/***************以上为修改内容*************/

struct hdr_teaomdv_error {
        u_int8_t        re_type;                // Type
        u_int8_t        reserved[2];            // Reserved
        u_int8_t        DestCount;                 // DestCount
        // List of Unreachable destination IP addresses and sequence numbers
        nsaddr_t        unreachable_dst[TEAOMDV_MAX_ERRORS];   
        u_int32_t       unreachable_dst_seqno[TEAOMDV_MAX_ERRORS];   

  inline int size() { 
  int sz = 0;
  /*
  	sz = sizeof(u_int8_t)		// type
	     + 2*sizeof(u_int8_t) 	// reserved
	     + sizeof(u_int8_t)		// length
	     + length*sizeof(nsaddr_t); // unreachable destinations
  */
  	sz = (DestCount*2 + 1)*sizeof(u_int32_t);
	assert(sz);
        return sz;
  }

};

struct hdr_teaomdv_rrep_ack {
	u_int8_t	rpack_type;
	u_int8_t	reserved;
};

// for size calculation of header-space reservation
union hdr_all_teaomdv {
  hdr_teaomdv          ah;
  hdr_teaomdv_request  rreq;
  hdr_teaomdv_reply    rrep;
  hdr_teaomdv_error    rerr;
  hdr_teaomdv_rrep_ack rrep_ack;
  hdr_teaomdv_recommen rcom;
  hdr_teaomdv_probe prob;
  hdr_teaomdv_pta pta;
};

#endif /* __teaomdv_packet_h__ */
