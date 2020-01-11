#include <iterator>
#include <memory>

namespace Containers {

//????? ????????? "???????"
	template<class T>
    class Queue {
	private:
		struct element;
        size_t size = 0;//???? ??????, ?????????? ????? ????????? ? ?????????
	public:
        Queue() = default;//??????????? ?? ?????????

        class forward_iterator//????? ?????????
        {
		public:
            //???????? ????????? ???????????
            using value_type = T;
			using reference = T&;
            using pointer = T*;
			using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

			explicit forward_iterator(element* ptr);
			T& operator*();
			forward_iterator& operator++();
			forward_iterator operator++(int);
			bool operator== (const forward_iterator& other) const;
			bool operator!= (const forward_iterator& other) const;
		private:
			element* it_ptr;
            friend class Queue;
		};

		forward_iterator begin();
		forward_iterator end();
		void push(const T& value);
		T& top();
		T& bottom();
		void pop();
		size_t length();
		void delete_by_it(forward_iterator d_it);
        void delete_by_index(size_t N);//???????? ?? ???????
		void insert_by_it(forward_iterator ins_it, T& value);
        void insert_by_index(size_t N, T& value);//?????????? ?? ???????
        Queue& operator=(Queue& other);
	private:
        struct element
        {
			T value;
			std::unique_ptr<element> next_element = nullptr;
			forward_iterator next();
		};

        void push_impl(std::unique_ptr<element>& cur, const T& value);
        std::unique_ptr<element> pop_impl(std::unique_ptr<element> cur);
		std::unique_ptr<element> first = nullptr;
	};



	template<class T>
    typename Queue<T>::forward_iterator Queue<T>::begin() {
		return forward_iterator(first.get());
	}

	template<class T>
    typename Queue<T>::forward_iterator Queue<T>::end() {
		return forward_iterator(nullptr);
	}
	


	template<class T>
    size_t Queue<T>::length() {//?????????? ????? ?????????, ?????????? ? ?????????
        return this->size;
	}

	template<class T>
    void Queue<T>::push(const T& value)//?????????? ???????? ? ?????????
    {
        push_impl(this->first, value);
		size++;
	}

	template<class T>
    void Queue<T>::push_impl(std::unique_ptr<element>& cur, const T& value)
    {
        if (cur == nullptr)
        {
            cur = std::unique_ptr<element>(new element{value});
            return;
        }
        else
            push_impl(cur->next_element, value);
    }

    template<class T>
    void Queue<T>::pop()
    {
        if (size == 0)
            throw std::logic_error("Queue is empty");
        first = std::move(first->next_element);
		size--;
	}


	template<class T>
    std::unique_ptr<typename Queue<T>::element> Queue<T>::pop_impl(std::unique_ptr<element> cur)
    {
        if (cur->next_element != nullptr)
        {
			cur->next_element = pop_impl(std::move(cur->next_element));
			return cur;
		}
        else
            return nullptr;
	}

	template<class T>
    T& Queue<T>::bottom()
    {
        if (size == 0)
            throw std::logic_error("Queue is empty");
		forward_iterator i = this->begin();
		while (i.it_ptr->next() != this->end()) {
			i++;
		}
		return *i;
	}

	template<class T>
    T& Queue<T>::top()
    {
		return first->value;
	}
	
	template<class T>
    Queue<T>& Queue<T>::operator=(Queue<T>& other)//???????? ???????????? ??? ?????????
    {
		size = other.size;
		first = std::move(other.first);
	}

	template<class T>
    void Queue<T>::delete_by_it(Containers::Queue<T>::forward_iterator d_it)
    {
		forward_iterator i = this->begin(), end = this->end();
        if (d_it == end)
            throw std::logic_error("Out of borders");
        if (d_it == this->begin())
        {
			std::unique_ptr<element> tmp;
			tmp = std::move(first->next_element);
			first = std::move(tmp);
			return;
		}
		while ((i.it_ptr != nullptr) && (i.it_ptr->next() != d_it)) {
			++i;
		}
        if (i.it_ptr == nullptr) throw std::logic_error("Out of borders");
		i.it_ptr->next_element = std::move(d_it.it_ptr->next_element);
		size--;
	}

	template<class T>
    void Queue<T>::delete_by_index(size_t N)
    {
        if (N >= this->size)
            return;
		forward_iterator it = this->begin();
        for (size_t i = 0; i < N; ++i)
			++it;
		this->delete_by_it(it);
	}

	template<class T>
    void Queue<T>::insert_by_it(Containers::Queue<T>::forward_iterator ins_it, T& value)
    {
		auto tmp = std::unique_ptr<element>(new element{ value });
		forward_iterator i = this->begin();
		if (ins_it == this->begin()) {
			tmp->next_element = std::move(first);
			first = std::move(tmp);
			size++;
			return;
		}
		while ((i.it_ptr != nullptr) && (i.it_ptr->next() != ins_it)) {
			++i;
		}
        if (i.it_ptr == nullptr) throw std::logic_error("Out of borders");
		tmp->next_element = std::move(i.it_ptr->next_element);
		i.it_ptr->next_element = std::move(tmp);
		size++;
	}


	template<class T>
    void Queue<T>::insert_by_index(size_t N, T& value) {
		forward_iterator it = this->begin();
		if (N >= this->length())
			it = this->end();
		else
		for (size_t i = 1; i <= N; ++i) {
			++it;
		}
		this->insert_by_it(it, value);
	}

	template<class T>
    typename Queue<T>::forward_iterator Queue<T>::element::next()
    {
		return forward_iterator(this->next_element.get());
	}

	template<class T>
    Queue<T>::forward_iterator::forward_iterator(Containers::Queue<T>::element* ptr) {
		it_ptr = ptr;
	}

	template<class T>
    T& Queue<T>::forward_iterator::operator*() {
		return this->it_ptr->value;
	}

	template<class T>
    typename Queue<T>::forward_iterator& Queue<T>::forward_iterator::operator++() {
        if (it_ptr == nullptr) throw std::logic_error("Out of queue");
		*this = it_ptr->next();
		return *this;
	}

	template<class T>
    typename Queue<T>::forward_iterator Queue<T>::forward_iterator::operator++(int) {
		forward_iterator old = *this;
        ++*this;
		return old;
	}

	template<class T>
    bool Queue<T>::forward_iterator::operator==(const forward_iterator& other) const {
		return it_ptr == other.it_ptr;
	}

	template<class T>
    bool Queue<T>::forward_iterator::operator!=(const forward_iterator& other) const {
		return it_ptr != other.it_ptr;
	}

}
