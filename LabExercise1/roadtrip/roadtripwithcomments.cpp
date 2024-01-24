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





void showlist(list <int> g) 
{ 
    list <int> :: iterator it; 
    for(it = g.begin(); it != g.end(); ++it) 
        cout << '\t' << *it; 
    cout << '\n'; 
} 





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

	cout << "Ts=" << Ts << "\n";
	cout << "Cs=" << Cs << "\n";
	cout << "Tf=" << Tf << "\n";
	cout << "Cf=" << Cf << "\n";

	int a=(Tf-Ts)/(Cf-Cs);
	int b=(Cf*Ts-Cs*Tf)/(Cf-Cs);

	cout << "a=" << a << "\n";
	cout << "b=" << b << "\n";

	cout << "distances:\n";
    showlist(distances);

    //Find the biggest distance 
    list<int>::iterator d = distances.begin();
    int dmax=*d;
    while(d!=distances.end())
    {
       	advance(d,1);
    	if (*d>dmax) dmax=*d;
    }
    cout << "Maximun distance is: " << dmax << "\n";




    //Calculate the minimun capacitance inorder to drive slow the biggest distance
    int cmin=dmax*Cs;
    cout << "Cmin= " << cmin << "\n\n";

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
 	cout<< "dmaxf=" << dmaxf << "\n";
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

	cout << "sports: ";
	showlist(sport);
	cout << "mix: ";
	showlist(mix);

	t=Tf*st+L*a*cm+mt*b;

	cout << "cm= " << cm << "\n";
	cout << "a= " << a << "\n";
	cout << "b= " << b << "\n";
	cout << "L= " << L << "\n";
	cout << "st= " << st << "\n";
	cout << "mt= " << mt << "\n";
	cout << "Total time: " << t << "\n";

	cout << "\n";




 	while (t>T)
 	{
 		cm_=(T-Tf*st-b*mt)/L*a;
 		cout << "cm_=" << cm_ << "\n";
 		cout << "cm=" << cm << "\n";

 		if (cm==cm_) 
 		{
 			cout << "HERE\n";
 			break;
 		}

 		else
 		{
 			cm=cm_;
 			dmaxf=cm/Cf;
 			cout<< "dmaxf=" << dmaxf << "\n";
			for (it=mix.begin(); it != mix.end(); ++it)
			{
				cout << "current it= " << *it << "\n";

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

			cout << "sports: ";
			showlist(sport);
			cout << "mix: ";
			showlist(mix);

			cout << "L= " << L << "\n";
			cout << "st= " << st << "\n";
			cout << "mt= " << mt << "\n";
			cout << "Total time: " << t << "\n";
		}
		cout << "\n";
 	}

 	cout << "Minimun gasoline: " << cm << "\n";

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


	cout << "Minimum cost: " << mincost << "\n";

    return 0;
}


/*

2 1 1000000000 2000000000
111 999999998
101 999999998
1
2 1 1 2

-1




3 1 8 10
10 8
5 7
11 9
3
2 1 1 2

10



2 1 1000000000 2000000000
111 1000000000
101 1000000000
5
2 1 1 2


101

*/