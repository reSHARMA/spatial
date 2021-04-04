#ifndef GRAPH_H
#define GRAPH_H

#include "iostream"
#include "map"
#include "set"
#include "vector"

namespace spatial {

template <typename Node> class Graph {
private:
  std::map<Node *, std::set<Node *>> GraphBase;

public:
  using GraphType = std::map<Node *, std::set<Node *>>;
  using iterator = typename GraphType::iterator;

  bool hasEdgeBetween(Node *, Node *);
  void insert(Node *, Node *, int, int);
  bool insert(Node *, Node *);
  void insert(Node *, std::set<Node *>);
  std::set<Node *> getPointee(Node *);
  Node *getUniquePointee(Node *);
  void merge(std::vector<Graph<Node>> Graphs);
  void erase(Node *);
  iterator begin() { return GraphBase.begin(); }
  iterator end() { return GraphBase.end(); }
  bool operator==(const Graph<Node> &TheGarph) const;
  bool operator<(const Graph<Node> &TheGarph) const;
  template <typename GraphNode>
  friend std::ostream &operator<<(std::ostream &OS, const Graph<GraphNode> &G);
};

/** Implementation ---- **/

/// hasEdgeBetween - Returns true if there is a edge between \p Src and \p Dest
template <typename Node>
bool Graph<Node>::hasEdgeBetween(Node *Src, Node *Dest) {
  if (GraphBase.find(Src) == GraphBase.end())
    return false;
  auto Pointee = this->getPointee(Src);
  return (Pointee.find(Dest) != Pointee.end());
}

/// insert - Inserts an edge between \p Src and \p Dest based on \p Left and \p
/// Right. \p Left and \p Right denotes the level of redirection in LHS and RHS
/// respectively example a = b is denoted by (1, 1) and a = &b by (1, 0).
/// Only a = b, a = &b, a = *b and *a = b supported right now, TODO support more
template <typename Node>
void Graph<Node>::insert(Node *Src, Node *Dest, int Left, int Right) {
  if (Left == 1 && Right == 1) {
    for (auto P : this->getPointee(Dest)) {
      this->insert(Src, P);
    }
  } else if (Left == 2 && Right == 1) {
    for (auto Src : this->getPointee(Src)) {
      for (auto Dest : this->getPointee(Dest)) {
        this->insert(Src, Dest);
      }
    }
  } else if (Left == 1 && Right == 0) {
    this->insert(Src, Dest);
  } else if (Left == 1 && Right == 2) {
    for (auto Dest : this->getPointee(Dest)) {
      for (auto DestDest : this->getPointee(Dest)) {
        this->insert(Src, DestDest);
      }
    }
  }
}

/// insert - Inserts an direct edge between \p Src andp Dest. Returns false if
/// the edge already existed
template <typename Node> bool Graph<Node>::insert(Node *Src, Node *Dest) {
  if (this->hasEdgeBetween(Src, Dest))
    return false;
  this->GraphBase[Src].insert(Dest);
  return true;
}

/// insert - Directly inserts pointee set \p Pointee for node \p Node
template <typename Node>
void Graph<Node>::insert(Node *N, std::set<Node *> Pointee) {
  if (this->GraphBase.find(N) == this->GraphBase.end()) {
    this->GraphBase[N] = Pointee;
  } else {
    this->GraphBase[N].insert(Pointee.begin(), Pointee.end());
  }
}

/// getPointee - Returns a set of pointee for a given \p Node. Returns an empty
/// set if \p Node does not point to anyone
template <typename Node> std::set<Node *> Graph<Node>::getPointee(Node *N) {
  std::set<Node *> PointeeSet;
  if (this->GraphBase.find(N) != this->GraphBase.end())
    PointeeSet = this->GraphBase[N];
  return PointeeSet;
}

/// getUniquePointee - Returns the unique pointee for a given \p Node. Returns
/// null set if \p Node does not point to anyone or points to more than one node
template <typename Node> Node *Graph<Node>::getUniquePointee(Node *N) {
  Node *Pointee = nullptr;
  if (this->GraphBase.find(N) != this->GraphBase.end())
    if (this->GraphBase[N].size() == 1)
      Pointee = *((this->GraphBase[N]).begin());
  return Pointee;
}

template <typename Node>
bool Graph<Node>::operator==(const Graph<Node> &TheGraph) const {
  return this->GraphBase.size() == TheGraph.GraphBase.size() &&
         std::equal(this->GraphBase.begin(), this->GraphBase.end(),
                    TheGraph.GraphBase.begin());
}

template <typename Node>
bool Graph<Node>::operator<(const Graph<Node> &TheGraph) const {
  return this->GraphBase.size() < TheGraph.GraphBase.size();
}

template <typename Node>
std::ostream &operator<<(std::ostream &OS, const Graph<Node> &G) {
  for (auto X : G.GraphBase) {
    OS << *(X.first) << " -> {";
    for (auto Y : X.second) {
      OS << *(Y) << ", ";
    }
    OS << "}\n";
  }
  return OS;
}

/// erase - Erases the node \p Node
template <typename Node> void Graph<Node>::erase(Node *N) {
  this->GraphBase[N].clear();
}

/// merge - Merges the Graphs from \p Graphs
template <typename Node>
void Graph<Node>::merge(std::vector<Graph<Node>> Maps) {
  for (auto Map : Maps) {
    for (auto N : Map.GraphBase) {
      if (this->GraphBase.find(N.first) == this->GraphBase.end()) {
        this->GraphBase[N.first] = N.second;
      } else {
        this->GraphBase[N.first].insert(N.second.begin(), N.second.end());
      }
    }
  }
}

} // namespace spatial
#endif
