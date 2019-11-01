#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll ra = 880301,rb = 53, rm = 20020607;
ll rn = 97;
int random () {
    return rn = (rn*ra+rb) % rm;
}


struct Node {
    Node *l,*r;
    ll key,val,tag;
    int sz,pri;
    Node (ll k,ll v) {
        l = r = 0;
        pri = random();
        key = k;
        tag = val = v;
        sz = 1;
    }

    void pull() {
        sz = 1;
        tag = val;
        if (l) {
            tag = max(tag,l->tag);
            sz += l->sz;
        }
        if (r) {
            tag = max(tag,r->tag);
            sz += r->sz;
        }
    }
};
Node *root;

int SIZ(Node *nd) {
    return nd ? nd->sz : 0;
}

Node *mrg(Node *a,Node *b) {
    if (!a || !b) {
        return a ? a : b;
    }
    if (a->pri > b->pri) {
        a->r = mrg(a->r,b);
        a->pull();
        return a;
    } else {
        b->l = mrg(a,b->l);
        b->pull();
        return b; 
    }
}

// max a key <= key
void split_key(Node *o,Node *&a,Node *&b,ll key) {
    if (!o) {
        a = b = 0;
        return;
    }
    if (o->key <= key) {
        a = o;
        split_key(o->r,a->r,b,key);
        a->pull();
    } else {
        b = o;
        split_key(o->l,a,b->l,key);
        b->pull();
    }
}

// size of a equals sz
void split_sz(Node *o,Node *&a,Node *&b,ll sz) {
    if (!o) {
        a = b = 0;
        return;
    }
    if (SIZ(o->l)+1 <= sz) {
        a = o;
        split_sz(o->r,a->r,b,sz-SIZ(o->l)-1);
        a->pull();
    } else {
        b = o;
        split_sz(o->l,a,b->l,sz);
        b->pull();
    }
}

void ins(ll key,ll val) {
    Node *nw = new Node(key,val);
    if (!root) {
        root = nw;
    } else {
        Node *l,*r;
        split_key(root,l,r,key);
        root = mrg(l,mrg(nw,r));
    }
}

// static rmq on treap lol
ll query(ll l,ll r) {
    Node *a,*b,*c;
    split_sz(root,a,b,l-1);
    split_sz(b,b,c,r-l+1);
    ll ret = b->tag;
    root = mrg(a,mrg(b,c));
    return ret;
}