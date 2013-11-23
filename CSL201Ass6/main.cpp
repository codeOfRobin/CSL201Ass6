//
//  main.cpp
//  CSL201Ass6
//
//  Created by Robin Malhotra on 10/11/13.
//  Copyright (c) 2013 Robin's code kitchen. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <map>
#include <queue>
#include <curses.h>
using namespace std;

class city;

class edge
{
    
public:
    
    city *orig;
    city *dest;
    int depart;
    int arrive;
    string flightID;
    int cost;
    
    
    edge (city *first, city *second)//cost
    {
        orig=first;
        dest=second;
    }

};


class city
{
    public:
    
    string name;
    vector<edge>adjcities;
    
    bool visited;
    
    city (string id)
    {
        name=id;
    }
    
    edge* searchflightID(city *c1, city *c2)
    {
        edge *newedge=new edge(NULL,NULL);
        for (int i=0; i<c1->adjcities.size(); i++)
        {
            if (c1->adjcities[i].dest==c2)
            {
                newedge=&c1->adjcities[i];
                return newedge;
            }
        }
        
        return NULL;
    }
    city *search(string id)
    {
        for (int i=0; i<adjcities.size(); i++)
        {
            if (adjcities[i].dest->name==id)
            {
                return adjcities[i].dest;
            }
            
        }
        
        return NULL;
    }
    
    void Addadjnode(city *adj, int cost,string flightID,int arrive, int depart)//cost
    {
        edge newedge(this,adj);
        newedge.arrive=arrive;
        newedge.depart=depart;
        newedge.cost=cost;
        newedge.flightID=flightID;
        adjcities.push_back(newedge);
    
    }
};


class graph
{
public:
    vector<city*>citylist;
    
    void clearvisited()
    {
        for (int i=0; i<citylist.size(); i++)
        {
            citylist.at(i)->visited=false;
        }
    }
    
    void addewcity(city *temp)
    {
        citylist.push_back(temp);
    }
    
    city *findcity(string id)
    {
        for (int i=0; i<citylist.size(); i++)
        {
            if (citylist[i]->name==id)
            {
                return citylist[i];
            }
            
        }
        
        return NULL;
    }
    
    
    
   
};

graph G;

class compare
{
public:
    bool operator()(std::pair<city*, int>a,std::pair<city*, int>b)
    {
        return a.second>b.second;
    }
};

void dijikstra(city *src,city *dest)
{
    map<city *, int> dist;
    city *v;
    map<city*, city*> parent;
    priority_queue<std::pair<city*,int>,std::vector<std::pair<city*, int> >, compare> q1,q2;
    vector<city *> previous;
    
    for (int i=0; i<G.citylist.size(); i++)
    {
        dist[G.citylist[i]]=2500;
        q1.push(make_pair(G.citylist[i], dist[G.citylist[i]]));
        
    }
    
    
    
    dist[src]=0;
    parent[src]=NULL;
    q1.push(make_pair(src, 0));
    
    while (!q1.empty())
    {
        city *min=q1.top().first;
       
        q1.pop();
        
        if (dest==min)
        {
            break;
        }
        
        
        for (int i=0; i<min->adjcities.size(); i++)
        {
            v=min->adjcities[i].dest;
            edge crawl=min->adjcities[i];
            
            if (dist[min]!=2500 && dist[v]>crawl.cost+dist[min])
            {
                dist[v]=dist[min]+crawl.cost;
                
                q1.push(make_pair(v, dist[v]));
                
                
                parent[v]=min;
                
            }
        }
        
        
    }
    v=dest;
    while (parent[v]!=NULL)
    {
        edge *x=v->searchflightID(parent[v],v);
        cout<<x->flightID<<'\n';
        v=parent[v];
    }
    cout<<endl<<endl;
    
    
    
    
}

void dijikstrapart2(city *src,city *dest,int time)
{
    map<city *, int> dist;
    city *v;
    map<city*, city*> parent;
    priority_queue<std::pair<city*,int>,std::vector<std::pair<city*, int> >, compare> q1,q2;
    vector<city *> previous;
    
    for (int i=0; i<G.citylist.size(); i++)
    {
        dist[G.citylist[i]]=2500;
        q1.push(make_pair(G.citylist[i], dist[G.citylist[i]]));
        
    }
    
    
    
    dist[src]=0;
    parent[src]=NULL;
    q1.push(make_pair(src, 0));
    
    while (!q1.empty())
    {
        city *min=q1.top().first;
        
        q1.pop();
        
        if (dest==min)
        {
            break;
        }
        
        
        for (int i=0; i<min->adjcities.size(); i++)
        {
            v=min->adjcities[i].dest;
            edge crawl=min->adjcities[i];
            
            if (dist[min]!=2500 && dist[v]>crawl.arrive)
            {
                dist[v]=crawl.arrive;
                
                q1.push(make_pair(v, dist[v]));
                
                
                parent[v]=min;
                
            }
        }
        
        
    }
    v=dest;
    edge *x;
    int time1=0, time2=0;
    while (parent[v]!=NULL)
    {
        x=v->searchflightID(parent[v],v);
                
        cout<<x->flightID<<'\n';
        v=parent[v];
    }
    
    
    if (x->arrive>time)
    {
        
        system("clear");
        cout<<"no path found";
    }
    
    cout<<endl<<endl;
    
    
    
    
    
}
void unifiedadd(city *c1, city *c2, int cost,string flightID, int arrive, int depart)
{
    c1->Addadjnode(c2,cost,flightID,arrive,depart);
    
    if (G.findcity(c1->name)==NULL)
    {
        G.addewcity(c1);
    }
   
    if (G.findcity(c2->name)==NULL)
    {
        G.addewcity(c2);
    }
}


fstream f1;
int main()
{
    
    string ID,orig,dest,s;
    int arrive,depart;
    city *c1=new city("");
    city *c2=new city("");
    f1.open("/Users/robinmalhotra2/Desktop/CSL201Ass6.txt");
    while (!f1.eof() && f1.good())
    {
        f1>>ID;
        f1>>orig;
        f1>>s;
        depart=atoi(s.c_str());
        f1>>dest;
        f1>>s;
        arrive=atoi(s.c_str());
        
        if (G.findcity(orig)==NULL)
        {
            c1=new city(orig);
        }
        
        else
        {
            c1=G.findcity(orig);
        }
        
        
        if (G.findcity(dest)==NULL)
        {
            c2=new city(dest);
        }
        
        else
        {
            c2=G.findcity(dest);
        }
        
        
        unifiedadd(c1, c2, arrive-depart, ID,arrive,depart);
        
    }
    f1.close();
    
    f1.open("/Users/robinmalhotra2/Desktop/CSL201ass6query.txt");
    
    while (!f1.eof() &&f1.good())
    {
        string src,dest,s;
        int time;
        f1>>src;
        f1>>dest;
        f1>>s;
        time=atoi(s.c_str());
        dijikstra(G.findcity(src), G.findcity(dest));
        dijikstrapart2(G.findcity(src), G.findcity(dest), time);
        
    }
    
    f1.close();
    return 1;
}