// Listp.h
// Mara Kim
//
// A tree object that stores a list
// a la Lisp

#include "ListpCons.h"
#include <memory>
#include <string>
#include <ostream>

template <class T>
class Listp {
public:
    typedef T Atom;
    typedef std::unique_ptr<Listp<T> > ptr;
    Listp():
    _head() {}
    Listp(Listp<T>::ptr list):
    _head(std::move(list->_head)) {}
    Listp(typename ListpCons<T>::ptr head):
    _head(std::move(head)) {}
    Listp(const Atom& atom):
    _head(new ListpCons<T>(atom)) {}

    ptr copy() const {
        return ptr(new Listp<T>(_head->copy()));
    }

    typename ListpCons<T>::ptr copy_head() const {
        return _head->copy();
    }

    friend std::ostream& operator<<(std::ostream& out, const Listp<T>& list) {
        if(!list._head->isAtom())
            out << '{';
        out << *list._head;
        if(!list._head->isAtom())
            out << '}';
        return out;
    }

    std::string print(std::string delim = ",", std::string openbr = "{", std::string closebr = "}") const {
        std::stringstream ss;
        if(!_head->isAtom())
            ss << openbr;
        ss << _head->print(delim,openbr,closebr);
        if(!_head->isAtom())
            ss << closebr;
        return ss.str();
    }

    size_t size() const {
        return _head->size();
    }

    void push_back(const Listp<T>& list) {
        push_back(list._head->copy()->copy());
    }

    void push_back(typename ListpCons<T>::ptr cons) {
        if(_head)
            _head->push_back(std::move(cons));
        else
            _head = std::move(cons);
    }

    void push_back(Atom atom) {
        if(_head)
            _head->push_back(atom);
        else
            _head = typename ListpCons<T>::ptr(new ListpCons<T>(typename ListpCons<T>::ptr(new ListpCons<T>(atom)),nullptr));
    }

    // apply a scalar transformation to each atom
    // Func should take a const Listp::Atom& and return an Listp::Atom
    template<typename Func> void transform(Func func) {
        return _head->transform(func);
    }
    // map each atom against a list
    // Func should take an const Listp::Atom& and return a ListpCons
    template<typename Func> void map(const Func &func) {
        return _head->map(func);
    }
private:
    typename ListpCons<T>::ptr _head;
};
