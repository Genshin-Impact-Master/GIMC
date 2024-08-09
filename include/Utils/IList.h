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
  INode<Owner> *next_;        // 下一个链接域结点
  INode<Owner> *pre_;         // 上一个链接域结点
  Owner *owner_;              // 该链接域结点的拥有者
public:
  INode<Owner>(INode<Owner> *next, INode<Owner> *pre, Owner *owner) : next_(next), pre_(pre), owner_(owner) {}

  // 设置下一个结点指针
  void setNext(INode<Owner> *next) {
    next_ = next;
  }

  // 设置上一个结点指针
  void setPre(INode<Owner> *pre) {
    pre_ = pre;
  }

  // 修改结点拥有者
  void setOwner(Owner *owner) {
    owner_ = owner;
  }

  // 返回下一个结点指针
  INode<Owner> *getNext() {
    return next_;
  }

  // 返回上一个结点指针
  INode<Owner> *getPre() {
    return pre_;
  }

  // 判断是否到达链表尾部
  bool isEnd() {
    return next_ == nullptr;
  }

  // 获取拥有者
  Owner *getOwner() {
    return owner_;
  }

  // 添加在 node 前
  void addBefore(INode<Owner> *node) {
    pre_ = node->getPre();
    next_ = node;
    pre_->setNext(this);
    node->setPre(this);
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
  int size_;                            // 计数器，初始化为 0
public:
  IList<ListOwner, NodeOwner>(INode<NodeOwner> *rear, ListOwner *listOwner)
                       : rear_(rear), listOwner_(listOwner), head_(nullptr, nullptr), size_(0) {}

  IList<ListOwner, NodeOwner>(ListOwner *listOwner) : listOwner_(listOwner), rear_(nullptr), head_(nullptr, nullptr, nullptr) {
                                clear();
                              }

  void clear() {
    rear_ = &head_; // 链表尾部等于头部
    size_ = 0;
  }

  // 添加一个结点到链表结尾
  void append(INode<NodeOwner> &node) {
    rear_->setNext(&node);
    node.setPre(rear_);
    rear_ = &node;
    size_++;
  }

  // 添加一个结点到链表头部
  void add2Head(INode<NodeOwner> &node) {
    INode<NodeOwner> *next = head_.getNext();
    node.setNext(head_.getNext());
    node.setPre(&head_);
    if (next) {
      next->setPre(&node); 
    }
    head_.setNext(&node);
    size_++;
  }

  // 删除结点
  void remove(INode<NodeOwner> &node) {
    INode<NodeOwner> *pre = node.getPre();
    INode<NodeOwner> *next = node.getNext();
    if (pre) {
      pre->setNext(next);
    }
    if (next) {
      next->setPre(pre);
    }
  }

  // 获取头结点指针
  INode<NodeOwner> *getHeadPtr() {
    return &head_;
  }

  // 判断链表是否为空
  bool isEmpty() {
    return size_ == 0;
  }

  // 获取最后一个结点
  INode<NodeOwner> *getRearPtr() {
    if (isEmpty())
      return nullptr;
    return rear_;
  }

  // 获取链表元素个数
  int getSize() {return size_;}
};

GIMC_NAMESPACE_END

#endif // IList_H