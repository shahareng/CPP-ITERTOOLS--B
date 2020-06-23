#pragma once

namespace itertools
{
    template<typename F, typename T>
    class filterfalse
    {
        const T& temp;
        const F& func;

        public:
            class iterator
            {
            private:
                const filterfalse& ff;
                decltype(temp.begin()) iter; // for pass over the temp. type = (iterator)

            public:
                iterator(const filterfalse& f, decltype(temp.begin()) i) : ff(f), iter(i) {
                    if (iter == ff.temp.begin() && ff.func(*iter))
                        ++(*this);
                }

                auto operator*() const
                {
                    return *iter;
                }

                //++iBegin
                iterator &operator++()
                {
                    ++iter;
                    while (iter != ff.temp.end() && ff.func(*iter))
                    {
                        ++iter;
                    }
                    return *this;
                }

                //iBegin++
                const iterator operator++(int) 
                {
                    iterator copy = *this;
                    iter++;
                    while (iter != ff.temp.end() && ff.func(*iter))
                    {
                        iter++;
                    }
                    return copy;
                }

                bool operator==(const iterator &other) const 
                {
                    return iter == other.iter;
                }

                bool operator!=(const iterator &other) const
                {
                    return iter != other.iter;
                }
            };

            filterfalse(const F& lambda, const T& a) : func(lambda), temp(a) { } // struct, vector

            iterator begin()
            {
                return iterator(*this, temp.begin());
            }

            iterator end()
            {
                return iterator(*this, temp.end());
            }
    };
};
