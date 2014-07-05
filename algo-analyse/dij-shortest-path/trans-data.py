#!/usr/bin/python
import sys
fp= open (sys.argv[1],'r')
outfile='trans-' + sys.argv[1]
fpout=open(outfile,'w')
for line in fp:
    adj_list=line.strip().split()
    s=int(adj_list[0])-1
    for record in adj_list[1: ]:
        i=record.find(',')
        to=int(record[0:i])-1
        weight=record[i+1 :]
        fpout.write(str(s)+' '+str(to)+' '+weight+'\n')
        fpout.write(str(to)+' '+str(s)+' '+weight+'\n')
fpout.close()
fp.close()

