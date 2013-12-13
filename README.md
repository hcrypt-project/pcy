pcy
===

Display Flags in a Cyrus index file (cyrus.index)


cyrus@mailhost:/imap/user/micha$ pcy 
Cyrus index-file flag parser
usage: pcy [-f -u uid] index-file
  -f force processing
  -u process single uid
  
  
  
  

cyrus@mailhost:/imap/user/micha$ pcy cyrus.index
pcy 0.1; cyrus.index
...
record 17460: flags (00000010) SEEN 
record 17461: flags (00000010) SEEN 
record 17464: flags (00000011) ANSWERED SEEN 
record 17466: flags (80000014) DELETED SEEN EXPUNGED 
record 17467: flags (00000014) DELETED SEEN 
record 17468: flags (00000010) SEEN 
...
mails in mailbox: 77
