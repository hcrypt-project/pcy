/*
 * pcy.c
 *
 *  Created on: 02.12.2013
 *      Author: michaelbrenner
 */

#include <stdio.h>
#include <stdlib.h>
#include "pcy.h"

extern int optind;
extern char *optarg;

void usage();

int main(int argc, char **argv)
{
	FILE *f;
	int i,flags,opt,opt_force;
	long l,opt_uid,uid;
	char *opt_file;
	struct index_header header;
	struct index_record record;

	opt_force=0;
	opt_uid=-1;

	while ((opt = getopt(argc, argv, "fu:h")) != EOF) 
	{
       		switch (opt) 
		{
       		case 'f': /* force processing file */
            		opt_force=1;
			break;

        	case 'u':
            		opt_uid = atoi(optarg);
            		break;

		case 'h':
        	default:
                	usage();
        	}
    	}	
	
	if(optind>=argc)
		usage();
	if(opt_uid==0)
	{
		printf("ERROR: option -u requires an argument\n");
		usage();
	}

	printf("pcy 0.1; %s\n",argv[optind]);

	if((f=fopen(argv[optind],"rb"))==NULL)
	{
		printf("ERROR: can't open index file\n");
		exit(8);
	}

	fread(&header,128,1,f);
	
	l=ntohl(header.last_appenddate);

	if(!opt_force&&(l<0x51000000L||l>0x53000000L))
	{
		printf("doesn't look much like a cyrus index file (use -f switch to force processing)\n");
		exit(1);
	}
	
	for(i=0;i<ntohl(header.num_records);i++)
	{
		fread(&record,96,1,f);

		uid=ntohl(record.uid);

		if(opt_uid==-1||(opt_uid>0&&opt_uid==uid))
		{
			printf("record %ld: ",uid);

			flags=ntohl(record.system_flags);
			printf("flags (%08x) ",flags);

			printf("%s%s%s%s%s%s%s\n",
				flags&FLAG_ANSWERED?"ANSWERED ":"",
				flags&FLAG_FLAGGED?"FLAGGED ":"",
				flags&FLAG_DELETED?"DELETED ":"",
				flags&FLAG_DRAFT?"DRAFT ":"",
				flags&FLAG_SEEN?"SEEN ":"",
				flags&FLAG_UNLINKED?"UNLINKED ":"",
				flags&FLAG_EXPUNGED?"EXPUNGED ":"");
		}
	}

	printf("mails in mailbox: %d\n",ntohl(header.num_records));

	fclose(f);
}

void usage()
{
	printf("Cyrus index-file flag parser\nusage: pcy [-f -u uid] index-file\n");
	printf("  -f force processing\n");
	printf("  -u process single uid\n");
	exit(0);
}
