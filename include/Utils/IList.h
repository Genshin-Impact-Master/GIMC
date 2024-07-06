#ifndef IList_H
#define IList_H

#include "../Config.h"

USING_GIMC_NAMESPACE
GIMC_NAMESPACE_BEGIN
/**
 * Owner 表示该结点的拥有者类型
 * */
template<class Owner>
class INode {
private:
  INode<Owner> *next_;       // 下一个链接域结点
  Owner *owner_;             // 该链接域结点的拥有者
public:
  INode<Owner>(INode<Owner> *next, Owner *owner) : next_(next), owner_(owner) {}

  // 设置下一个结点指针
  void setNext(INode<Owner> *next) {
    next_ = next;
  }

  // 修改结点拥有者
  void setOwner(Owner *owner) {
    owner_ = owner;
  }

  // 返回下一个结点指针
  INode<Owner> *getNext() {
    return next_;
  }

  // 判断是否到达链表尾部
  bool isEnd() {
    return next_ == nullptr;
  }

  // 获取拥有者
  Owner *getOwner() {
    return owner_;
  }
};

/**
 * ListOwner 表示该结点链表拥有者类型
 * NodeOwner 表示结点链表中的结点的拥有者类型
 */
template<class ListOwner, class NodeOwner>
class IList {
private:
  INode<NodeOwner> head_;             // 侵入式链表头结点
  INode<NodeOwner> *rear_;            // 链表尾部
  ListOwner *listOwner_;              // 该侵入式链表的拥有者
public:
  IList<ListOwner, NodeOwner>(INode<NodeOwner> *rear, ListOwner *listOwner)
                       : rear_(rear), listOwner_(listOwner), head_(nullptr, nullptr) {}

  IList<ListOwner, NodeOwner>(ListOwner *listOwner) : listOwner_(listOwner), rear_(nullptr), head_(nullptr, nullptr) {
                                clear();
                              }

  void clear() {
    rear_ = &head_; // 链表尾部等于头部
  }

  // 添加一个结点到链表结尾
  void append(INode<NodeOwner> &node) {
    rear_->setNext(&node);
    rear_ = &node;
  }

  // 获取头结点指针
  INode<NodeOwner> *getHeadPtr() {
    return &head_;
  }
};

GIMC_NAMESPACE_END

#endif // IList_H