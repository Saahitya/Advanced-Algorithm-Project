#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <limits.h>
#include<time.h>

using namespace std;

void sendupdate(int sender, int skip);

struct vertex {
  int no_of_edges;
  map<int, int> edges;  //from, cost
};

struct globalObjects{
  int **distances;
  int **hops;
  int numnodes;
  vector <vector <int>> neighbours;
};

struct globalObjects gob;
bool maintainsymmetry;
bool changed=true;

double time_elapsed(struct timespec *start, struct timespec *end){
    double t;
    t=(end->tv_sec -  start->tv_sec);
    t+=(end->tv_nsec - start->tv_nsec)*0.000000001;
    return t;
}

int pathLeft(){
	if(changed==false){
		return 0;
	}
	return 1;

	for(int i=0;i<gob.numnodes;i++){
		for(int j=0;j<gob.numnodes;j++){
			if(gob.hops[i][j]==-1){
				return 1;
			}
		}
	}
	return 0;
}

void display(string msg){
  cout<<"\n";
  cout<<"---"<<msg<<"---";
  cout<<"\n";
  cout<<"Distances\n";

  int i,j;
  for(i = 0; i < gob.numnodes; i++) {
    for(j = 0; j < gob.numnodes; j++) {if(gob.distances[i][j]==INT_MAX){cout<<"- ";}else{cout << gob.distances[i][j] << " ";}}
    cout << endl;
  }
  cout<<"\nHops\n";
  for(i = 0; i < gob.numnodes; i++) {
	  for(j = 0; j < gob.numnodes; j++) cout << gob.hops[i][j] << " ";
	  cout << endl;
  }
}

void gengraph(int num){
	gob.numnodes=num;
	int i,j,weight;

	gob.distances=(int**)malloc(sizeof(int*)*num);
	gob.hops=(int**)malloc(sizeof(int*)*num);

	for(i=0; i<num; i++){
		gob.distances[i]=(int*)malloc(sizeof(int)*num);
	    gob.hops[i]=(int*)malloc(sizeof(int)*num);
	    vector <int> neighboursofi;
	    gob.neighbours.push_back(neighboursofi);
	}
	for(i=0; i<num;i++){
	    
	    gob.distances[i][i]=0;
	    gob.hops[i][i]=i;

		for(j=i+1; j<num;j++){
			weight=rand()%100+1;

			if(weight<50){
				gob.distances[i][j]=weight;
				gob.distances[j][i]=weight;
				gob.hops[i][j]=j;
				gob.hops[j][i]=i;
				gob.neighbours[i].push_back(j);
				gob.neighbours[j].push_back(i);
			}
			else{
				gob.distances[i][j]=INT_MAX;
				gob.distances[j][i]=INT_MAX;
				gob.hops[i][j]=-1;
				gob.hops[j][i]=-1;
			}
		}
	}
}

void read_graph(FILE *fp) {
	int N;
	int i, j, temp;

	fscanf(fp,"%d",&N);

	gob.distances=(int**)malloc(sizeof(int*)*N);
	gob.hops=(int**)malloc(sizeof(int*)*N);

	for(i = 0; i < N; i++) {
	    gob.distances[i]=(int*)malloc(sizeof(int)*N);
	    gob.hops[i]=(int*)malloc(sizeof(int)*N);
	    vector <int> neighboursofi;
	    gob.neighbours.push_back(neighboursofi);

	    for(j = 0; j < N; j++){
	        fscanf(fp,"%d",&temp);
	        if(i==j) {gob.distances[i][j] = 0; gob.hops[i][j]=-1;}
	        else if(temp == 0) {gob.distances[i][j] = INT_MAX; gob.hops[i][j]=-1;}
	        else {gob.distances[i][j] = temp; gob.hops[i][j]=j; gob.neighbours[i].push_back(j);}
	    }
	}
	gob.numnodes=N;

	return;
}

void receiveupdate(int receiver, int sender){
	int rec2senderDist=gob.distances[receiver][sender];

	for(int dest=0; dest<gob.numnodes; dest++){
		if(dest==sender){continue;}
		if( gob.hops[sender][dest]!=-1 ){
			if( gob.distances[receiver][dest] > gob.distances[sender][dest]+rec2senderDist){
			//	cout<<"\n*1*"<<receiver<<"-"<<dest<<" from "<<gob.distances[receiver][dest]<<" to ";
				gob.distances[receiver][dest] = gob.distances[sender][dest]+rec2senderDist;
				gob.hops[receiver][dest] = sender;
			//	cout<<gob.distances[receiver][dest];

				changed=true;
			}
			else if(gob.hops[receiver][dest] == sender && (gob.distances[sender][dest]+rec2senderDist) > gob.distances[receiver][dest]){
				//The route through the sender has increased cost. Update it here
			//	cout<<"\n*2*"<<receiver<<"-"<<dest<<" from "<<gob.distances[receiver][dest]<<" to ";
				gob.distances[receiver][dest] = gob.distances[sender][dest]+rec2senderDist;
			//	cout<<gob.distances[receiver][dest];
				changed=true;
			}
		}
	}
}

void sendupdate(int sender){
	int receiver, index;

	for(index=0; index < gob.neighbours[sender].size(); index++){
		receiver=gob.neighbours[sender][index];
		if(gob.hops[sender][receiver]!=-1){
			  if(receiver!=sender) {
			  	receiveupdate(receiver, sender);
			  }
		}
	}
}

void changewt(){
	int src, dest, newwt;
	cout<<"Enter src, dest, new weight: ";

	scanf("%d",&src);
	scanf("%d",&dest);
	scanf("%d",&newwt);

	printf("src: %d",src);
	printf("dest: %d",dest);
	printf("newwt: %d",newwt);
	gob.distances[src][dest]=newwt;
	if(maintainsymmetry) gob.distances[dest][src]=newwt;

	sendupdate(src);
	display("AFTER WEIGHT CHANGE");
}

int main(int argc, char *argv[]) 
{
	struct timespec begin,end;
	int i,j,choice=1,n,cnt=0;

	if(argc>1){
		FILE *fp=fopen(argv[1],"r");
		read_graph(fp);
		fclose(fp);
	}
	else{
		cout<<"\nGenerating random graph\nEnter number of nodes in graph: ";
		scanf("%d",&n);
		gengraph(n);
	}
	
	display("BEFORE");

	//cout<<"\n\nGraph built\nThe graph is unidirectional? ";
	//scanf("%d",&choice);
	choice==1?maintainsymmetry=true:maintainsymmetry=false;
	//cout<<"\n\nBuilding routing table using link state routing...\n";

	clock_gettime(CLOCK_REALTIME, &begin);
	while(changed){
		changed=false;
		for(int sender=0;sender<gob.numnodes;sender++){
			sendupdate(sender);
		//	printf("\r\tProgress: %f%%",(float)sender/gob.numnodes*100);
		//	fflush(stdout);
		}
	}

	clock_gettime(CLOCK_REALTIME, &end);
	cout<<"\n"<<time_elapsed(&begin,&end) <<"\n";
//	changewt();
	display("AFTER");
	return 0;
}