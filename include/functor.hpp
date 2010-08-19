#ifndef FUNCTOR_HPP_INCLUDED
#define FUNCTOR_HPP_INCLUDED

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
