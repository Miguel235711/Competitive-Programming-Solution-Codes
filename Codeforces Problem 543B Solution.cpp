#include <bits/stdc++.h>
#define loop(beg,end) for(int i = beg ; i <= end ; i ++ )///defining for that receives two parameters, first one indicates the begin of the for and second one indicates the end of the for
#define length 3008///max number of nodes(cities) + 8

using namespace std;

/**
Code solution by: Miguel Angel Munoz Vazquez
Github repository path: https://github.com/Miguel235711/Competitive-Programming-Solution-Codes
Problem link: http://codeforces.com/problemset/problem/543/B
Solved on: 10/06/2018
**/

///edge = road
///in this problem, all edges are bidirectional
///node = city

int cost [ length ] [ length ] ;///it stores the minimum cost (# of edges) to go from a to b (cost[a][b])
vector < int > graph [ length ] ;/// array of vectors that stores the edges connected to each node a (graph[a])
int A , B , C , D ;///A = s1 , B = t1 , C = t2 and D = t2
int maxCost1 , maxCost2 ;///maxCost1 = l1 and maxCost2 = l2
int N , M ;///N is the number of cities and M is the number of roads

int findBestPaths(){
    int ans = -1 ;
    for ( int begIn = 1 ; begIn <= N ; begIn ++ ) {///loop from 1 to N, begIn indicates an auxiliar starting point
        for ( int endIn = 1 ; endIn <= N ; endIn ++ ) {///loop from 1 to N, endIn indicates an auxiliar finishing point
            int costA = cost [ A ] [ begIn ] + cost [ begIn ] [ endIn ] + cost [ endIn ] [ B ] ;///cost of going from A to begIn + cost of going from begIn to endIn + cost of going from endIn to B (by transitive property this sum is a cost of going from A to B)
            int costC = cost [ C ] [ begIn ] + cost [ begIn ] [ endIn ] + cost [ endIn ] [ D ] ;///cost of going from C to begIn + cost of going from begIn to endIn + cost of going from endIn to D (by transitive property this sum is a cost of going from C to D)
            int costB = cost [ B ] [ begIn ] + cost [ begIn ] [ endIn ] + cost [ endIn ] [ A ] ;///cost of going from A to begIn + cost of going from begIn to endIn + cost of going from endIn to B (by transitive property this sum is a cost of going from A to B)
            int costD = cost [ D ] [ begIn ] + cost [ begIn ] [ endIn ] + cost [ endIn ] [ C ] ;///cost of going from D to begIn + cost of going from begIn to endIn + cost of going from endIn to C (by transitive property this sum is a cost of going from D to C)
            ///first, calculate the #of edges of traveling path(a,b) and path (c,d) sharing one or more nodes in the middle of the paths
            ///a , c; path(a,b) and path (c,d)
            int occuppiedEdges = cost [ A ] [ begIn ] + cost [ C ] [ begIn ] + cost [ begIn ] [ endIn ] + cost [ endIn ] [ D ] + cost [ endIn ] [ B ] ;///cost[A][begIn] + cost[C][begIn] is when these two paths don't share edges  and then they share the nodes from begIn to endIn and they separate again with cost [ endIn ] [ D ] + cost [ endIn ] [ B ]
            int destroyEdges = M - occuppiedEdges ;///calculate the edges that weren't used in this possibility(so if they weren't occupied we can destroy them (totalNumberOfEdges-NumberOfOccupiedEdges)
            if ( costA <= maxCost1 && costC <= maxCost2){///check if individual costs are less or equal to maxCosti(li)
                ans = max ( ans,destroyEdges);///check if current destroyEdges is the best answer until now
            }
            ///a , d ; path(a,b) and path (d,c)
            occuppiedEdges = cost [ A ] [ begIn ] + cost [ D ] [ begIn ] + cost [ begIn ] [ endIn ] + cost [ endIn ] [ C ] + cost [ endIn ] [ B ] ;///cost[A][begIn] + cost[D][begIn] is when these two paths don't share edges  and then they share the nodes from begIn to endIn and they separate again with cost [ endIn ] [ C ] + cost [ endIn ] [ B ]
            destroyEdges = M - occuppiedEdges ;///calculate the edges that weren't used in this possibility(so if they weren't occupied we can destroy them (totalNumberOfEdges-NumberOfOccupiedEdges)
            if ( costA <= maxCost1 && costD <= maxCost2){///check if individual costs are less or equal to maxCosti(li)
                ans = max ( ans,destroyEdges);///check if current destroyEdges is the best answer until now
            }
            ///b,c ; path(b,a) and path (c,d)
            occuppiedEdges = cost [ B ] [ begIn ] + cost [ C ] [ begIn ] + cost [ begIn ] [ endIn ] + cost [ endIn ] [ A ] + cost [ endIn ] [ D ] ;///cost[B][begIn] + cost[C][begIn] is when these two paths don't share edges  and then they share the nodes from begIn to endIn and they separate again with cost [ endIn ] [ A ] + cost [ endIn ] [ D ]
            destroyEdges = M - occuppiedEdges ;///calculate the edges that weren't used in this possibility(so if they weren't occupied we can destroy them (totalNumberOfEdges-NumberOfOccupiedEdges)
            if ( costB <= maxCost1 && costC <= maxCost2){///check if individual costs are less or equal to maxCosti(li)
                ans = max ( ans,destroyEdges);///check if current destroyEdges is the best answer until now
            }
            ///b,d ; path(b,a) and path (d,c)
            occuppiedEdges = cost [ B ] [ begIn ] + cost [ D ] [ begIn ] + cost [ begIn ] [ endIn ] + cost [ endIn ] [ A ] + cost [ endIn ] [ C ] ;///cost[B][begIn] + cost[D][begIn] is when these two paths don't share edges  and then they share the nodes from begIn to endIn and they separate again with cost [ endIn ] [ A ] + cost [ endIn ] [ C ]
            destroyEdges = M - occuppiedEdges ;///calculate the edges that weren't used in this possibility(so if they weren't occupied we can destroy them (totalNumberOfEdges-NumberOfOccupiedEdges)
            if ( costB <= maxCost1 && costD <= maxCost2){///check if individual costs are less or equal to maxCosti(li)
                ans = max ( ans,destroyEdges);///check if current destroyEdges is the best answer until now
            }
        }
    }
    ///finally, calculate the #of edges of traveling path(a,b) and path (c,d) sharing NO edges in the middle of the paths
    int costA = cost [ A ][ B ] ;///cost of going from A to B
    int costC = cost [ C ][ D ] ;///cost of going from C to D
    int occuppiedEdges = costA + costC ;///occupied edges is the sum of both costs
    int destroyEdges = M - occuppiedEdges ;///calculate the edges that weren't used in this possibility(so if they weren't occupied we can destroy them (totalNumberOfEdges-NumberOfOccupiedEdges)
    if ( costA <= maxCost1 && costC <= maxCost2 ){///check if individual costs are less or equal to maxCosti(li)
        ans = max ( ans , destroyEdges ) ;///check if current destroyEdges is the best answer until now
    }
    return ans ;///this function returns the maximum number of destroyed edges
}

int vis [ length ] ;///array that indicates is node (vis[node]) has been visited during the current BFS

struct state {///struct that contains the variables that indicate in which node we are during the BFS and what is the current cost of getting there
    int node , cost ;
    state(){}///empty constructor
    state(int n , int c ) {///constructor
        node = n ;
        cost = c ;
    }
};

void BreathFirstSearch(int beg , int color ){///beg indicates the node from which we are going to start the BFS (Breath First Search), color indicates the ID of the current BFS
    queue < state > myQueue ;///a queue containing the states of the BFS
    myQueue.push(state(beg,0));///push the initial state of the BFS, node is beg and cost is 0
    vis [ beg ] = color ;///visit node beg
    cost [ beg ] [ beg ] = 0 ;///because getting from a node A to a node A has a cost of 0
    while ( !myQueue.empty()){///while we have a element in the queue
        state act = myQueue.front();///get the element in the front of the queue
        myQueue.pop();///pop the element in the front of the queue
        act.cost ++ ;///increase the cost for the next states in 1 (the cost of crossing the edge)
        for ( int son: graph [ act.node ] ){///navigate through all edges connected to current state node
            if ( vis [ son ] != color ) {///check if this node (son of act.node) has not been yet visited during this BFS
                state next = act ;///state next takes act attributes
                next.node = son ;///next.node is now son
                myQueue.push(next);///push this new state into queue
                vis [ next.node ] = color ;///visit this new node
                cost [ beg ] [ next.node ] = next.cost ;///assign next.cost to the cost of going from beg to next.node
            }
        }
    }
}

void calculateCosts(){
    loop(1,N){///loop from to 1 to N
        BreathFirstSearch(i,i);///call BFS with begin node as i and color as i
    }
}

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> N >> M ;///read number of nodes(cities) and number of roads(edges)
    loop(1,M){///loop from to 1 to M (M=number of edges)
        int a , b ;///
        cin >> a >> b ;///read two number that indicate an edge between them
        graph [ a ] . push_back ( b ) ;///push b into vector a, to indicate an edge from a to b
        graph [ b ] . push_back ( a ) ;///push a into vector b, to indicate an edge from b to a
    }
    cin >> A >> B >> maxCost1 ;///read s1,t1 and l1
    cin >> C >> D >> maxCost2 ;///read s2,t2 and l2
    calculateCosts();///calL calculateCosts() function that calculates minimum cost (# of edges) to go from a to b (cost[a][b]) between all pairs a,b (1<=a,b<=N)
    cout << findBestPaths() << "\n" ;///print result of function findBestPaths()
    return 0;
}
