#pragma once

namespace itertools
{
    class range
    {
        int iBegin;
        int iEnd;

        public:
            class iterator
            {
                friend class range;
                private:
                    int index;

                public:
                    iterator(int i) { index = i; }

                    int operator*() const
                    {
                        return index;
                    }

                    iterator& operator++()
                    {
                        ++index;
                        return (*this);
                    }

                    iterator operator++(int) 
                    {
                        iterator copy = *this;
                        ++index;
                        return copy;
                    }

                    bool operator==(const iterator &other) const 
                    {
                        return index == other.index; 
                    }

                    bool operator!=(const iterator &other) const
                    {
                        return index != other.index;
                    }
            };

            range(int a, int b) : iBegin(a), iEnd(b) {  }

            iterator begin() const
            {
                return iBegin;
            }

            iterator end() const
            {
                return iEnd;
            }            
    };
};