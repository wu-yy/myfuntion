Operator: 相关的重载函数
1. std::ostream & operator <<(std::ostream & out ,const half_t &x){
             out<<(float)x; 
             return out;
}     
2. bool operator >=(const half_t & other) const{
                return float(*this) >= float(other);
}
3. half_t & operator +=(const half_t &rhs){
                *this =half_t(float(*this)+float(rhs));
                reuturn &=*this;
}
4. operator float() const{
                uint32_t f =0;
                return *reinterpret_cast<float const *>(&f);
}
5. operator __half()const{
            Return reinterpret_cast<const __half &>(__x);
}
6. ++ 重载
self_type &operator++(){
    if(pos){
        //首先确保不是空的迭代器，再查看有没有右子树
        if(pos->right){
            //定位到右子树的最左节点
            pos=pos->right;
            while (pos->left)pos=pos->left;
        }else{
            //定位到尚未访问过的祖先节点
            while ((pos->parent)&&(pos->parent->right==pos))pos=pos->parent;
            pos=pos->parent;
        }
    }
    return *this;
}
7. 指针重载
reference_type & operator *()const throw(std::runtime_error){
    if(pos)return pos->value;
    else {
        throw  std::runtime_error("dereference null iterator!");
    }
}
8. !=  重载
template <typename N>
bool operator !=(tree_iterator<N>const & left,tree_iterator<N> const & right){
    return !(left==right);
}
