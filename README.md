pcy
===

Display Flags in a Cyrus index file (cyrus.index)


cyrus@mailhost:/imap/user/micha$ pcy <br>
Cyrus index-file flag parser<br>
usage: pcy [-f -u uid] index-file<br>
  -f force processing<br>
  -u process single uid<p>
  
  
  

cyrus@mailhost:/imap/user/micha$ pcy cyrus.index<br>
pcy 0.1; cyrus.index<br>
...<br>
record 1: flags (00000010) SEEN <br>
record 4: flags (00000011) ANSWERED SEEN <br>
record 6: flags (80000014) DELETED SEEN EXPUNGED <br>
record 7: flags (00000014) DELETED SEEN <br>
record 8: flags (00000010) SEEN <br>
...<br>
mails in mailbox: 77<br>
