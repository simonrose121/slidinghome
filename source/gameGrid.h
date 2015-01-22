#if !defined(__GAMEGRID_H__)
#define __GAMEGRID_H__

template<typename T, int width, int height>
class Grid {
    public:
        T data[width * height];

        class iterator {
            public:
                iterator(const iterator &other) :
                    ptr(other.ptr)
                {
                }

                iterator &left() const {
                    return iterator(ptr - 1);
                }

                iterator &right() const {
                    return iterator(ptr + 1);
                }

                iterator &up() const {
                    return iterator(ptr - width);
                }

                iterator &down() const {
                    return iterator(ptr + width);
                }

                iterator &operator++() {
                    ++ptr;
                    return *this;
                }

                iterator &operator--() {
                    --ptr;
                    return *this;
                }

                iterator operator++(int) {
                    ++*this;
                    return iterator(ptr + 1);
                }

                iterator operator--(int) {
                    --*this;
                    return iterator(ptr - 1);
                }

                T operator*() const {
                    return *ptr;
                }

            private:
                iterator();
                iterator(T *ptr_) :
                    ptr(ptr_)
                {
                }

                T *ptr;

                friend class Grid;
        };

		iterator begin() {
			return iterator(data);
		}

		iterator end() {
			return iterator(data + width * height);
		}
};


#endif