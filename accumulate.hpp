#pragma once

#include <iostream>
#include <vector>
#include <iterator>

namespace itertools
{

    typedef struct 
    {
        template <typename P>
        P operator()(P a, P b) const
        {
            return a + b;
        }
    } plus;


    template<typename T, typename F = plus>
    class accumulate
    {        
        const T& temp;
        const F& func;

        public:
            class iterator
            {
            private:
                const accumulate& ac;
                decltype(temp.begin()) iter; // for pass over the temp. type = (iterator)
                typename std::decay<decltype(*(temp.begin()))>::type valIter;
                // decltype(*(temp.begin())) valIter; // *iter. type = (*iterator)

            public:
                iterator(const accumulate& a, decltype(temp.begin()) i) : ac(a), iter(i) { if (i != ac.temp.end()) valIter = *i; }

                auto operator*() const
                {
                   return valIter;
                }

                //++iBegin
                iterator &operator++()
                {
                    ++iter;
                    if (iter != ac.temp.end())
                    {
                        valIter = ac.func(valIter, *iter);
                    }
                    return *this;
                }

                //iBegin++
                const iterator operator++(int) 
                {
                    iterator copy = *this;
                    iter++;
                    if (iter != ac.temp.end())
                    {
                        valIter = ac.func(valIter, *iter);
                    }
                    return copy;
                }

                // iterator& operator=(const iterator& other)
                // {
                //     if (valIter != other.valIter)
                //     {
                //         this->valIter = other.valIter;
                //     }
                //     return *this;
                // }

                bool operator==(const iterator &other) const 
                {
                    return iter == other.iter;
                }

                bool operator!=(const iterator &other) const
                {
                    return iter != other.iter;
                }
            };
            
            accumulate(const T& a, const F& lambda = plus()) : temp(a), func(lambda) { }

            iterator begin() const
            {
                return iterator(*this, temp.begin());
            }

            iterator end() const
            {
                return iterator(*this, temp.end());
            }
    };
};