#include "util.hpp"

// class ewdirected_cycle
ewdirected_cycle::ewdirected_cycle(ewdigraph g):m_g(g){
        marked.assign(m_g.V(),false);
        onstack.assign(m_g.V(),false);
        edge.assign(m_g.V(),diedge(0,0,0.0));
        for(int v=0;v<m_g.V();++v){
                if(!marked[v])
                        cyclic_dfs(v);
        }
};

void ewdirected_cycle::cyclic_dfs(int v){ //we are done,when we've already detect a cycle
                        //call hascycle() here can be better?
        marked[v]=true;
        onstack[v]=true;
        const ewdigraph::ADJLIST& v_adj=m_g.adj(v);
        for(int i=0;i<v_adj.size();++i){
		diedge e=v_adj[i];
                int w=e.to();
                if(hascycle()) //the point to call hascycle() is considerable
                        return;
                else if(!marked[w]){
                        edge[w]=e;
                        cyclic_dfs(w);
                }
                else if(onstack[w]){ //w has been checked,then check weather it's alreadly on stack now
			diedge x(e);
                        for( ;x.from()!=w;x=edge[x.from()]){
                                m_cycle.push_front(x);
                        }
                        m_cycle.push_front(x);
                }
        }
        onstack[v]=false;
};

//class ewdigraph_depthfirstorder

ewdigraph_depthfirstorder::ewdigraph_depthfirstorder(ewdigraph g):m_g(g){
        marked.assign(m_g.V(),false);
        for(int v=0;v<m_g.V();++v){
                if(!marked[v])
                        dfs(v);
        }
};

void ewdigraph_depthfirstorder::dfs(int v){
        marked[v]=true;
        m_pre.push_back(v);
        const ewdigraph::ADJLIST& v_adj=m_g.adj(v);
        for(int i=0;i<v_adj.size();++i){
                int w=v_adj[i].to();
                if(!marked[w])
                        dfs(w);
        }
        m_post.push_back(v);
        m_reversepost.push_front(v);

};


//class ewdigraph_topological
ewdigraph_topological::ewdigraph_topological(ewdigraph g):m_g(g){
        ewdirected_cycle dc(m_g);
        if(!dc.hascycle()){
                ewdigraph_depthfirstorder dfo(m_g);
                m_order=dfo.reversepost();
        }
};

