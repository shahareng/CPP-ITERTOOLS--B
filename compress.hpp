#pragma once

namespace itertools
{
    template<typename T1, typename T2>
    class compress
    {
        const T1& temp1;
        const T2& temp2;

        public:
            class iterator
            {
            private:
                // iterator begin, iterator end <or> accumulate&
                const compress& com;
                decltype(temp1.begin()) iter1; // for pass over the container. type = (iterator)
                decltype(temp2.begin()) iter2; // for pass over the container. type = (iterator)

            public:
                iterator(const compress& a1, decltype(temp1.begin()) i1, decltype(temp2.begin()) i2) : com(a1), iter1(i1), iter2(i2) { }

                auto operator*() const
                {
                //    while(!(*iter2))
                //     {
                //         iter1++;
                //         iter2++;
                //     }
                    return *iter1;
                }

                //++iBegin
                iterator &operator++()
                {
                    ++iter1;
                    ++iter2;
                    while (iter1 != com.temp1.end() && !(*iter2))
                    {
                        ++iter1;
                        ++iter2;
                    }
                    return *this;
                }

                //iBegin++
                const iterator operator++(int) 
                {
                    iterator copy = *this;
                    ++iter1;
                    ++iter2;
                    while (iter1 != com.temp1.end() && !(*iter2))
                    {
                        iter1++;
                        iter2++;
                    }
                    return copy;
                }

                bool operator==(const iterator &other) const 
                {
                    return iter1 == other.iter1;
                }

                bool operator!=(const iterator &other) const
                {
                    return iter1 != other.iter1;
                }
            };

            compress(const T1& a, const T2& b) : temp1(a), temp2(b) {  }

            iterator begin() const
            {
                return iterator(*this, temp1.begin(), temp2.begin());
            }

            iterator end() const
            {
                return iterator(*this, temp1.end(), temp2.end());
            }
    };
};