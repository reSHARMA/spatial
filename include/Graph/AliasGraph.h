#ifndef ALIASGRAPH_H
#define ALIASGRAPH_H

#include "iostream"
#include "map"
#include "set"
#include "vector"

namespace spatial {

template <typename AliasNode> class AliasGraph {
private:
  std::map<AliasNode *, std::set<AliasNode *>> Graph;

public:
  using GraphType = std::map<AliasNode *, std::set<AliasNode *>>;
  using iterator = typename GraphType::iterator;

  bool hasEdgeBetween(AliasNode *, AliasNode *);
  void insert(AliasNode *, AliasNode *, int, int);
  bool insert(AliasNode *, AliasNode *);
  void insert(AliasNode *, std::set<AliasNode *>);
  std::set<AliasNode *> getPointee(AliasNode *);
  AliasNode *getUniquePointee(AliasNode *);
  void merge(std::vector<AliasGraph<AliasNode>> Graphs);
  void erase(AliasNode *);
  iterator begin() { return Graph.begin(); }
  iterator end() { return Graph.end(); }
  bool operator==(const AliasGraph<AliasNode> &TheAliasGarph) const;
  bool operator<(const AliasGraph<AliasNode> &TheAliasGarph) const;
  template <typename Node>
  friend std::ostream &operator<<(std::ostream &OS, const AliasGraph<Node> &G);
};

/** Implementation ---- **/

/// hasEdgeBetween - Returns true if there is a edge between \p Src and \p Dest
template <typename AliasNode>
bool AliasGraph<AliasNode>::hasEdgeBetween(AliasNode *Src, AliasNode *Dest) {
  if (Graph.find(Src) == Graph.end())
    return false;
  auto Pointee = this->getPointee(Src);
  return (Pointee.find(Dest) != Pointee.end());
}

/// insert - Inserts an edge between \p Src and \p Dest based on \p Left and \p
/// Right. \p Left and \p Right denotes the level of redirection in LHS and RHS
/// respectively example a = b is denoted by (1, 1) and a = &b by (1, 0).
/// Only a = b, a = &b, a = *b and *a = b supported right now, TODO support more
template <typename AliasNode>
void AliasGraph<AliasNode>::insert(AliasNode *Src, AliasNode *Dest, int Left,
                                   int Right) {
  if (Left == 1 && Right == 1) {
    for (auto Alias : this->getPointee(Dest)) {
      this->insert(Src, Alias);
    }
  } else if (Left == 2 && Right == 1) {
    for (auto AliasSrc : this->getPointee(Src)) {
      for (auto AliasDest : this->getPointee(Dest)) {
        this->insert(AliasSrc, AliasDest);
      }
    }
  } else if (Left == 1 && Right == 0) {
    this->insert(Src, Dest);
  } else if (Left == 1 && Right == 2) {
    for (auto AliasDest : this->getPointee(Dest)) {
      for (auto AliasDestDest : this->getPointee(AliasDest)) {
        this->insert(Src, AliasDestDest);
      }
    }
  }
}

/// insert - Inserts an direct edge between \p Src andp Dest. Returns false if
/// the edge already existed
template <typename AliasNode>
bool AliasGraph<AliasNode>::insert(AliasNode *Src, AliasNode *Dest) {
  if (this->hasEdgeBetween(Src, Dest))
    return false;
  this->Graph[Src].insert(Dest);
  return true;
}

/// insert - Directly inserts pointee set \p Pointee for node \p Node
template <typename AliasNode>
void AliasGraph<AliasNode>::insert(AliasNode *Node,
                                   std::set<AliasNode *> Pointee) {
  if (this->Graph.find(Node) == this->Graph.end()) {
    this->Graph[Node] = Pointee;
  } else {
    this->Graph[Node].insert(Pointee.begin(), Pointee.end());
  }
}

/// getPointee - Returns a set of pointee for a given \p Node. Returns an empty
/// set if \p Node does not point to anyone
template <typename AliasNode>
std::set<AliasNode *> AliasGraph<AliasNode>::getPointee(AliasNode *Node) {
  std::set<AliasNode *> PointeeSet;
  if (this->Graph.find(Node) != this->Graph.end())
    PointeeSet = this->Graph[Node];
  return PointeeSet;
}

/// getUniquePointee - Returns the unique pointee for a given \p Node. Returns
/// null set if \p Node does not point to anyone or points to more than one node
template <typename AliasNode>
AliasNode *AliasGraph<AliasNode>::getUniquePointee(AliasNode *Node) {
  AliasNode *Pointee = nullptr;
  if (this->Graph.find(Node) != this->Graph.end())
    if (this->Graph[Node].size() == 1)
      Pointee = *((this->Graph[Node]).begin());
  return Pointee;
}

template <typename AliasNode>
bool AliasGraph<AliasNode>::operator==(
    const AliasGraph<AliasNode> &TheAliasGraph) const {
  return this->Graph.size() == TheAliasGraph.Graph.size() &&
         std::equal(this->Graph.begin(), this->Graph.end(),
                    TheAliasGraph.Graph.begin());
}

template <typename AliasNode>
bool AliasGraph<AliasNode>::operator<(
    const AliasGraph<AliasNode> &TheAliasGraph) const {
  return this->Graph.size() < TheAliasGraph.Graph.size();
}

template <typename AliasNode>
std::ostream &operator<<(std::ostream &OS, const AliasGraph<AliasNode> &G) {
  for (auto X : G.Graph) {
    OS << *(X.first) << " -> {";
    for (auto Y : X.second) {
      OS << *(Y) << ", ";
    }
    OS << "}\n";
  }
  return OS;
}

/// erase - Erases the node \p Node
template <typename AliasNode>
void AliasGraph<AliasNode>::erase(AliasNode *Node) {
  this->Graph[Node].clear();
}

/// merge - Merges the AliasGraphs from \p Graphs
template <typename AliasNode>
void AliasGraph<AliasNode>::merge(
    std::vector<AliasGraph<AliasNode>> AliasMaps) {
  for (auto AliasMap : AliasMaps) {
    for (auto Node : AliasMap.Graph) {
      if (this->Graph.find(Node.first) == this->Graph.end()) {
        this->Graph[Node.first] = Node.second;
      } else {
        this->Graph[Node.first].insert(Node.second.begin(), Node.second.end());
      }
    }
  }
}

} // namespace spatial
#endif
