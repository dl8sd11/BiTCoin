struct Node{
    Node *L=0, *R=0, *P=0; // lc, rc, splay parent
    bool rev=0;
    int val;
    inline bool isL(){return P && P->L == this;}
    inline bool isR(){return P && P->R == this;}
    inline bool isRoot(){return !isL() && !isR();}
    Node*& ch(bool d){return d?R:L;} // 0 is left child, 1 is right child
    void push(){
        if (rev) {
            if (L) L->rev ^= 1;
            if (R) R -> rev ^= 1;
            swap(L,R);
            rev = 0;
        }
    }
    void rotate() {
        bool d = isR(); // 0 is left, 1 is right
        Node* x = ch(d^1), *g = P->P;
        if (x) x -> P = P;
        P -> ch(d) = x;
        this->ch(d^1) = P;
        if (!P->isRoot()) { // very important! Just because g exists doesn't mean you should rotate it
            g->ch(P->isR()) = this;
        }
        P->P = this;
        P = g;
    }
    void allpush(){
        if (!isRoot()) P->allpush(); push();
    }
    void splay(){
        allpush();
        while (!isRoot()){
            if (!P->isRoot()) (isL() ^ (P->isL()) ? this:P) -> rotate(); // different (xor is 1): zig zag, else zig zig
            rotate();
        }
    }
    Node* access(){
        Node *at = this, *prev = 0;
        while (at) {
            at->splay();
            at->R = prev;
            prev = at;
            at = at->P;
        }
        return prev;
    }
    Node* getroot(){
        Node* at = access();
        while (at->L) at = at->L;
        at->splay();
        return at;
    }
    void makeroot(){
        access();
        splay();
        rev ^= 1;
    }
    void cut() {
        access();
        splay();
        L = L->P = 0;
    }
    void link(Node* oth){
        oth->makeroot();
        oth->P = this;
    }
    Node(int x){val=x;}
    Node(){}
};
