/*
 * pcy.h
 *
 *  Created on: 02.12.2013
 *      Author: michaelbrenner
 */

/*
 * die structs sind aus cyrus/imap/mailbox.h uebernommen
 */
#ifndef PCY_H_
#define PCY_H_

#define MAX_USER_FLAGS (16*8)  //aus cyrus/imap/mailbox.h
#define NUM_CACHE_FIELDS 10
#define FLAG_ANSWERED (1<<0)
#define FLAG_FLAGGED (1<<1)
#define FLAG_DELETED (1<<2)
#define FLAG_DRAFT (1<<3)
#define FLAG_SEEN (1<<4)
#define FLAG_UNLINKED (1<<30)
#define FLAG_EXPUNGED (1U<<31)

typedef unsigned long long int modseq_t; //aus cyrus/lib/util.h
typedef unsigned long long int uquota_t; //aus cyrus/imap/quota.h

#include <time.h>

struct cacheitem {
    unsigned offset;
    unsigned len;
};

struct cacherecord {
    struct buf *base;
    unsigned offset;
    unsigned len;
    struct cacheitem item[NUM_CACHE_FIELDS];
};

struct index_record {
    unsigned int uid;							//00 00 00 a8 = 168
    unsigned int internaldate;						//52 0b 46 a6
    unsigned int sentdate;						//52 0b 55 20
    unsigned int size;							//00 00 13 8c = 5004
    unsigned int header_size;						//00 00 09 e7 = 2535
    unsigned int gmtime;						//52 0b 46 a6
    unsigned int cache_offset;						//00 00 00 04
    unsigned int last_updated;						//52 8d e0 b9
    unsigned int system_flags;						//00 00 00 14
    unsigned int user_flags[MAX_USER_FLAGS/32];				//00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    unsigned int content_lines;						//00 00 00 60
    unsigned int cache_version;						//00 00 00 03
    char guid[20];//struct message_guid guid;	//4f 2b .. 90 7f
    modseq_t modseq;							//00 00 00 00 00 00 04 25
    unsigned int cache_crc;						//81 cd b6 f8
    unsigned int record_crc;						//78 68 50 95

    /* metadata */
    //uint32_t recno;
    //int silent;
    //struct cacherecord crec;
};

struct index_header {
    /* track if it's been changed */
    //int dirty;  //brauchen wir hier nicht

    /* header fields */
	unsigned int generation_no;				//00 00 00 28
    int format;							//00 00 00 00
    int minor_version;						//00 00 00 0c
    unsigned int start_offset;					//00 00 00 80
    unsigned int record_size;					//00 00 00 60
    unsigned int num_records;					//00 00 00 be
    unsigned int last_appenddate;				//52 9c 9e 96
    unsigned int last_uid;					//00 00 01 75 = 373
    uquota_t quota_mailbox_used;				//00 00 00 00 03 63 e4 ae
    time_t pop3_last_login;					//00 00 00 00 = never
    unsigned int uidvalidity;					//51 62 96 90

    unsigned int deleted;					//00 00 00 a7 = 167
    unsigned int answered;					//00 00 00 0b = 11
    unsigned int flagged;					//00 00 00 00

    unsigned int options;					//00 00 00 01
    unsigned int leaked_cache_records;
    modseq_t highestmodseq;
    modseq_t deletedmodseq;
    unsigned int exists;
    time_t first_expunged;
    time_t last_repack_time;

    unsigned int header_file_crc;
    unsigned int sync_crc;

    unsigned int recentuid;
    time_t recenttime;

    unsigned int header_crc;
};

#endif /* PCY_H_ */
