fp=open("bitcoinotc.csv","r")

graph=[[0 for i in range(6005)] for j in range(6005)]

for line in fp:
	print(line)
	l=[int(i) for i in line.split(',')[:3]]
	
	graph[l[0]-1][l[1]-1]=abs(l[2])

fp2=open("bitcoin.txt","w")
for l in graph:
	for j in l:
		fp2.write(str(j)+" ")
	fp2.write("\n")
