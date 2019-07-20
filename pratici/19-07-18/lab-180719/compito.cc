#include <iostream>
#include <fstream>
#include <string.h>
    #include <unistd.h>

using namespace std;

#include "grafi.h"
#include "node.h"
#include "coda.h"

graph read_graph(string file_name)
{
    ifstream f(file_name);
    int num_nodi;
    f >> num_nodi;
    graph g = new_graph(num_nodi);

    int n1, n2;
    while ((f >> n1) && (f >> n2))
        add_arc(g, n1, n2, 1);

    f.close();
    return g;
}

void stampa(graph g)
{
    for (int i = 1; i < get_dim(g) + 1; i++)
    {
        adj_list l = get_adjlist(g, i);
        while (l != NULL)
        {
            int n = get_adjnode(l);
            cout << i << " -> " << n << endl;
            l = get_nextadj(l);
        }
    }
}

node *read_nodes(string file_name, int num_nodi)
{
    ifstream f(file_name);

    node *nodes = new node[num_nodi];

    char tipo[2];
    char cont[81];
    int i = 0;

    while ((f.getline(cont, 81)) && (f.getline(tipo, 2)))
    {
        strcpy(nodes[i].cont, cont);
        nodes[i].tipo = tipo[0];
        /* int j = 0;
        char c;
        cout<<"sto leggendo: ";
        while ( (c=cont[j])!='\0'){
            cout<<c;
            j++;
        }
        cout<<endl; */
        i++;
    }
    f.close();
    return nodes;
}

void stampa(graph g, node *nodes)
{
    for (int i = 1; i < get_dim(g) + 1; i++)
    {
        adj_list l = get_adjlist(g, i);
        while (l != NULL)
        {
            int j = get_adjnode(l);

            cout << nodes[i - 1].cont << " ";
            if (nodes[i - 1].tipo == 'T')
                cout << "OWNER";
            else if (nodes[j - 1].tipo == 'T')
                cout << "LIKE";
            else
                cout << "FOLLOW";

            cout << " " << nodes[j - 1].cont << endl;
            l = get_nextadj(l);
        }

        cout << endl;
    }
}

int getOwner(graph g, node *nodes, int tweet)
{
    for (int i = 1; i < get_dim(g) + 1; i++)
    {
        adj_list l = get_adjlist(g, i);
        while (l != NULL)
        {
            int j = get_adjnode(l);
            //cout<<"is "<<nodes[i-1].cont<<" owner of \""<<nodes[tweet-1].cont<<"\"?"<<endl;
            if (nodes[j - 1].tipo == 'U' && (i) == tweet)
            {
                //cout<<"yes"<<endl;
                return j;
            }
            //cout<<"no"<<endl;
            l = get_nextadj(l);
        }
    }
    return -1;
}

int *totalLike(graph g, node *nodes)
{
    int n = get_dim(g);
    int *likes = new int[n];
    for (int i = 0; i < n; i++)
        likes[i] = 0;

    for (int i = 1; i < n + 1; i++)
    {
        adj_list l = get_adjlist(g, i);
        while (l != NULL)
        {
            int j = get_adjnode(l);

            if (nodes[i - 1].tipo == 'U' && nodes[j - 1].tipo == 'T')
            {
                likes[getOwner(g, nodes, j) - 1]++;
                //cout<<"owner of \""<<nodes[j-1].cont<<"\" : "<<nodes[getOwner(g, nodes, j)-1].cont<<endl;
            }

            l = get_nextadj(l);
        }
    }

    return likes;
}

void stampa_max(node *nodes, int *likes, int num_nodi)
{
    int max = 0;
    for (int i = 0; i < num_nodi; i++)
    {
        if (max < likes[i])
            max = likes[i];
    }
    //cout<<"max: "<<max<<endl;
    for (int i = 0; i < num_nodi; i++)
    {
        //cout<<"likes: "<<likes[i]<<", type: "<<nodes[i].tipo<<endl;
        if (likes[i] == max && nodes[i].tipo == 'U')
            cout << nodes[i].cont << endl;
    }
}

int getNodeByName(graph g, node* nodes, char* name){
    for (int i = 1; i < get_dim(g) + 1; i++)
    {
        if (strcmp(nodes[i-1].cont, name) == 0) return i;
    }
    return -1;
}

void follow(graph g, node *nodes, char* name)
{
    int U = getNodeByName(g,nodes,name);
    
    int n = get_dim(g);
    if (U<=0 || U>n) {
        cout<<"utente non valido"<<endl;   
        return;
    }

    bool *visited = new bool[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;
    coda c = newQueue();
    
    c = enqueue(c,U);
    //cout<<"queue empty? "<<isEmpty(c)<<endl;
    while (!isEmpty(c))
    {
        int user = dequeue(c);
        //cout<<"user: "<<user<<endl;
        adj_list l = get_adjlist(g, user);
        while (l != NULL)
        {
            int j = get_adjnode(l);
            //cout<<nodes[user-1].cont<<" -> "<<nodes[j-1].cont<<endl;
            if (j!=U && !visited[j - 1] && nodes[j - 1].tipo == 'U')
            {
                //cout<<"yes!"<<endl;
                visited[j - 1] = true;
                c = enqueue(c,j);
            }
            l = get_nextadj(l);
        }
    }

    cout<<nodes[U-1].cont<<" segue:"<<endl;
    for (int i = 1; i < n + 1; i++)
    {
        if (visited[i - 1])
            cout << nodes[i - 1].cont << endl;
    }
}


int main()
{
    //punto 1
    graph g = read_graph("graph");
    stampa(g);

    //punto 2
    node *nodes = read_nodes("node", get_dim(g));
    stampa(g, nodes);

    //punto 3.a
    int *likes = totalLike(g, nodes);
    stampa_max(nodes, likes, get_dim(g));

    //punto 3.b
    char *in = new char[81];
    cout<<"inserisci nome utente: ";
    cin.getline(in,81);
    follow(g,nodes,in);
}