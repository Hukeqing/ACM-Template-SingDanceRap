template<class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
struct my_node_update {
    typedef int metadata_type;

    inline int _sum(int x) {
        metadata_type ans = 0;
        Node_CItr iter = node_begin();
        while (iter != node_end()) {
            Node_CItr l = iter.get_l_child(), r = iter.get_r_child();
            if (Cmp_Fn()(x, (*iter)->first)) iter = l;
            else {
                if (l != node_end()) {
                    ans += (*iter)->second;
                    ans += l.get_metadata();
                } else {
                    ans += iter.get_metadata();
                }
                iter = r;
            }
        }
        return ans;
    }

    inline int sum(int l, int r) {
        return _sum(r) - _sum(l - 1);
    }

    void update(int x, int value) {
        Node_CItr iter = node_begin();
        while (iter != node_end()) {
            Node_CItr l = iter.get_l_child(), r = iter.get_r_child();
            const_cast<int &>(iter.get_metadata()) += value;
            if (Cmp_Fn()(x, (*iter)->first)) iter = l;
            else iter = r;
        }
    }

    void operator()(Node_Itr it, Node_CItr end_it) {
        Node_Itr l = it.get_l_child();
        Node_Itr r = it.get_r_child();
        int left = 0, right = 0;
        if (l != end_it) left = l.get_metadata();
        if (r != end_it) right = r.get_metadata();
        const_cast<int &>(it.get_metadata()) = left + right + (**it).second;
    }

    virtual Node_CItr node_begin() const = 0;

    virtual Node_CItr node_end() const = 0;
};

tree<int, int, less<int>, rb_tree_tag, my_node_update> me;
