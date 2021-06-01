#include"fixedfile.hpp"


namespace Vec_Template
{
    template<typename T>
    class Vec_text
    {
    public:
        Vec_text():element(nullptr),first_free(nullptr),cap(nullptr){}
        Vec_text(const Vec_text&s);
        Vec_text &operator =(const Vec_text& rhs);
        T operator [](const size_t & i);
        ~Vec_text();
        void Vec_push_back(const T &s);
        size_t Vec_size() const{
            return first_free-element;
        }
        size_t Vec_capacity() const{
            return cap-element;
        }

        void show() const;

        T * V_begin() const {return element;}
        T * V_end() const {return first_free;}
    private:
        std::allocator<T> alloc;
        void chk_n_alloc(){
            if(Vec_size()==Vec_capacity())
                reallocate_case();
        }

        void f_free();
        void reallocate_case();
        pair<T*,T*> alloc_n_copy(const T* b,const T* e);
        T *element;
        T *first_free;
        T *cap;
    };

    template<typename T>
    void Vec_text<T>::Vec_push_back(const T &s)
    {
        chk_n_alloc();
        alloc.construct(first_free++,s);
    }

    template<typename T>
    pair<T*,T*> Vec_text<T>::alloc_n_copy(const T* b,const T* e)
    {
        auto data=alloc.allocate(e-b);
        return {data,std::uninitialized_copy(b,e,data)};
    }

    template<typename T>
    void Vec_text<T>::f_free()
    {
        if(element){
            for(auto p=first_free;p!=element;)
                alloc.destroy(--p);
            alloc.deallocate(element,cap-element);
        }
    }

    template<typename T>
    Vec_text<T>::~Vec_text(){f_free();}

    template<typename T>
    Vec_text<T>::Vec_text(const Vec_text&s)
    {
        auto newdata=alloc_n_copy(s.V_begin(),s.V_end());
        element=newdata.first;
        first_free=cap=newdata.second;
    }


    template<typename T>
    Vec_text<T>& Vec_text<T>::operator=(const Vec_text<T> &rhs)
    {
        auto data=alloc_n_copy(rhs.V_begin(),rhs.V_end());
        f_free();
        element=data.first;
        first_free=cap=data.second;
        return *this;
    }

    template<typename T>
    T Vec_text<T>::operator [](const size_t & i)
    {
        if(i>=this->Vec_size())
        {
            cout<<"[]运算符调用错误空间"<<endl;
            exit(-1);
        }

        auto temp=element;
        for(int count=0;count!=i;++count)
            ++temp;
        return *temp;
    }

    template<typename T>
    void Vec_text<T>::reallocate_case()
    {
        auto newcapacity=Vec_size()? Vec_size()*2:1;
        auto newdata=alloc.allocate(newcapacity);

        auto dest=newdata;
        auto elem=this->element;
        for(size_t i=0;i!=Vec_size();++i)
            alloc.construct(dest++,std::move(*elem++));
        f_free();
        element=newdata;
        first_free=dest;
        cap=element+newcapacity;
    }

    template<typename T>
    void Vec_text<T>::show() const
    {
        if(element){
            for(auto p=element;p!=first_free;)
            {
                cout<<*p<<" ";
                ++p;
            }
            cout<<endl;
        }
    }
}   



/*
    main演示
    using namespace Vec_Template;
    Vec_text<int> newone;
    newone.Vec_push_back(16);
    newone.Vec_push_back(20);
    newone.Vec_push_back(30);

    Vec_text<char> newonwe1;
    newonwe1.Vec_push_back('1');
    newonwe1.Vec_push_back('a');
    newonwe1.Vec_push_back('5');
    newonwe1.Vec_push_back('A');
    newonwe1.Vec_push_back('B');

    newone.show();
    newonwe1.show();
*/