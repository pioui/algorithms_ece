#include<iostream>
#include <bits/stdc++.h> 
using namespace std;
class car 
{ 
   int cost; 
   int capacity; 
public: 
   car(int x, int y) 
   { 
      cost = x; 
      capacity = y; 
   } 
   int get_cost() const { return cost; } 
   int get_capacity() const { return capacity; } 
}; 



int main()
{
	// Read input
	int N,K,D,T;

	cin >> N;
	cin >> K;
	cin >> D;
	cin >> T;

	//Use a list for cars.
	list <car> cars;
	
	for(int i=0;i<N;i++)
	{
		int p,c;
		cin >> p;
		cin >> c;
		cars.push_back(car(p,c));

	}

	//Use a list for station 
	list <int> stations;

	int s=0;

    stations.push_back(s); 
	for(int i=0;i<K;i++)
	{
	    cin >> s;
	    stations.push_back(s); 
	}
	stations.push_back(D); 

	//sort it 
	stations.sort();

	//calculate distances and put it in the list
	list<int>::iterator it = stations.begin();
	int s1=*it ;
	std::advance(it, 1);
	int s2=*it;
	list <int> distances;
	for(int i=0;i<K+1;i++)
	{
	    distances.push_back(s2-s1); 
	    s1=s2;
	    std::advance(it, 1);
	    s2=*it;
	}

	int Ts,Cs,Tf,Cf;
	cin >> Ts;
	cin >> Cs;
	cin >> Tf;
	cin >> Cf;

	int a=(Tf-Ts)/(Cf-Cs);
	int b=(Cf*Ts-Cs*Tf)/(Cf-Cs);



    //Find the biggest distance 
    list<int>::iterator d = distances.begin();
    int dmax=*d;
    while(d!=distances.end())
    {
       	advance(d,1);
    	if (*d>dmax) dmax=*d;
    }




    //Calculate the minimun capacitance inorder to drive slow the biggest distance
    int cmin=dmax*Cs;

    //Seperate the distances in two categories:
    //sport: all diastances shorter than d that also can be done with sports driving
    //mix: all distances larger than d that can be done with mix driving(sports+efficiecnt)
   	list <int> sport;

   	list <int> mix = distances;
    int st=0; //sum of distances with sport driving
    int L=K+1; // number of diastances with mix driving
    int mt=std::accumulate(mix.begin(),mix.end(),0); // sum of distances with mix driving

 	int dmaxf; // maximun distance that can been done with sport driving 
 	unsigned long long int t=0; // total time
    int cm=cmin;
	int cm_;


 	dmaxf=cm/Cf;
	for (it=mix.begin(); it != mix.end(); ++it)
	{
		if (*it<dmaxf)
		{
			sport.push_back(*it);
			st=st+(*it);
			mt=mt-(*it);
			L--;
			it=mix.erase(it);
		}
	}

	t=Tf*st+L*a*cm+mt*b;


 	while (t>T)
 	{
 		cm_=(T-Tf*st-b*mt)/L*a;


 		if (cm==cm_) 
 		{
 			break;
 		}

 		else
 		{
 			cm=cm_;
 			dmaxf=cm/Cf;
			for (it=mix.begin(); it != mix.end(); ++it)
			{

				if (*it<=dmaxf)
				{
					sport.push_back(*it);
					st=st+(*it);
					mt=mt-(*it);
					L--;
					it=mix.erase(it);
				}

			}
			t=Tf*st+L*a*cm+mt*b;


		}
 	}


 	list<car>::iterator c=cars.begin();

 	int mincost=-1;


	for (c=cars.begin(); c != cars.end(); c++)
	{
		if (c->get_capacity() >= cm)
		{
			if (c->get_cost()<mincost || mincost==-1)
				mincost=c->get_cost();
		}

	}


	cout << mincost << "\n";

    return 0;
}


