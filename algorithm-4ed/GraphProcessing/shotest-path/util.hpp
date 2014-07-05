#ifndef __UTIL_HPP

#define __UTIL_HPP

#include <deque>
#include <vector>


/* edge weighted digraph cycle detection*/
class ewdirected_cycle{

        public:
                ewdirected_cycle(ewdigraph g);
                bool hascycle(){return !m_cycle.empty();};
                std::vector<diedge> cycle(){return std::vector<diedge>(m_cycle.begin(),m_cycle.end());};
        private:
                ewdigraph m_g;
                std::deque<diedge> m_cycle;
                std::vector<bool> marked; //vertex has been checked?
                std::vector<bool> onstack;//vertex now is on stack?
                std::vector<diedge> edge;   //the dfs-access tree

        private:
                void cyclic_dfs(int v);
};

/* do depth first in edge weighted digraph*/
class ewdigraph_depthfirstorder{

        private:
                ewdigraph m_g;
                std::vector<bool> marked;
                std::deque<int> m_pre;
                std::deque<int> m_post;
                std::deque<int> m_reversepost;
        public:
                ewdigraph_depthfirstorder(ewdigraph g);
                std::vector<int> pre(){return std::vector<int>(m_pre.begin(),m_pre.end());};
                std::vector<int> post(){return std::vector<int>(m_post.begin(),m_post.end());};
                std::vector<int> reversepost(){return std::vector<int>(m_reversepost.begin(),m_reversepost.end());};
        private:
                void dfs(int v);

};

class ewdigraph_topological{

        public:
                ewdigraph_topological(ewdigraph g);
                bool isDAG(){return m_order.empty();};//DAG:Directed acyclic graph 
                std::vector<int> order(){return m_order;};
        private:
                ewdigraph m_g;
                std::vector<int> m_order;

};

#endif
