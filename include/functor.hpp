#ifndef FUNCTOR_HPP_INCLUDED
#define FUNCTOR_HPP_INCLUDED

/*
Recruit0: Not sure how to use boost::function and if it is compatible with the
current design of the API. If it is then this object is redundant.
*/

namespace cp
{

class functor
{
public:
    virtual void run();
private:
};

namespace dummy
{
extern cp::functor dummy_functor;
}

}

#endif // FUNCTOR_HPP_INCLUDED
