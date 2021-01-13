#Karishma Sinha 
#2018339


import re
import subprocess
p = subprocess.run(['ping', '-c', '100', '192.168.1.3'], stdout=subprocess.PIPE).stdout.decode('utf-8')
#print p.communicate()[0]
#timestr = re.compile("time=[0-9]+ms").findall(str(p.communicate()[0]))
#print(p.stdout)
ping_output= p
print(p)
timestr=ping_output.split("time=");
#print(timestr)
aList=[]
for time in timestr:
	aList.append(time.split()[0])

#print(aList)
s=len(aList)
bList=[]
for n in range(1,s):
	bList.append(float(aList[n]))


print("the rtt for the packets sent are:")
print(bList)
bList.sort()
print("********************************************")
print("the sorted rtt are:")
print(bList)
print("********************************************")

#t=len(cList)
print("the median latency is:", (bList[49]+bList[50])/2)

print("the 90th percentile latency is:", bList[89])
print("the 99th percentile latency is:", bList[98])


# int size=timestr.size();
# int a
# for(int i=2; i<=size;i++)
# {
	
# }
# string s
# while(s)