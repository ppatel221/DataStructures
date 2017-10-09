#include <iostream>

template <typename T>
class SList{
	struct Node{
		T data_;
		Node* next_;
		Node(const T& data = T() , Node* next=nullptr){
			data_=data;
			next_=next;
		}
	};
	Node* front_;
	Node* back_;
public:
	SList(){
		front_=nullptr;
		back_=nullptr;
	}
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
	~SList();
};

template <typename T>
void SList<T>::push_front(const T& data){


	Node* nn = new Node(data,front_);
	if(front_ == NULL)
	{
		back_ = nn;
	}
	front_ = nn;

}


template <typename T>
void SList<T>::push_back(const T& data){



	Node* nn = new Node(data);

	if(front_ == NULL)
	{
		front_ = nn;
		back_ = nn;;
	}else{
		back_->next_=nn;
		back_=nn;
	}



}
template <typename T>
void SList<T>::pop_front(){


	if(front_){
		Node* curr = front_;
		if(front_ != back_)
		{
			front_ = front_ -> next_;
		}else{
			front_ = NULL;
			back_ = NULL;
		}

		delete curr;
	}

}
template <typename T>
void SList<T>::pop_back(){


	if(front_)
	{
		if(front_ != back_)
		{
			Node* prev = front_;
			while(prev->next_ != back_)
			{
				prev = prev -> next_;
			}
			prev->next_ = NULL;
			delete back_;
			back_ = prev;

		}else{

			delete back_;
			back_ = front_ = NULL;
		}
	}

}

template <typename T>
void SList<T>::print() const{
	Node* curr=front_;
	while(curr){
		std::cout << curr->data_ << " ";
		curr=curr->next_;
	}
	std::cout << std::endl;
}
template <typename T>
SList<T>::~SList(){
	Node* curr=front_;
	while(curr){
		Node* rm=curr;
		curr=curr->next_;
		delete rm;
	}
}

template <typename T>
class Sentinel{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T() , Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	Sentinel(){
		front_=new Node();
		back_=new Node();
		front_->next_=back_;
		back_->prev_=front_;
	}
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
	void reversePrint() const;
	~Sentinel();
};


template <typename T>
void Sentinel<T>::push_front(const T& data){

	Node* front = front_ ->next_;
	Node* nn = new Node(data,front,front_);
	front_->next_ = nn;
	front->prev_ = nn;

}
template <typename T>
void Sentinel<T>::push_back(const T& data){



	Node* temp = back_->prev_;
	Node* nn = new Node(data,back_,temp);

	temp->next_ = nn;
	back_->prev_ = nn;

}
template <typename T>
void Sentinel<T>::pop_front(){

	if(front_->next_ != back_)
	{
		Node* rm = front_->next_;
		front_ -> next_ = rm->next_;
		Node* temp = rm->next_;
		temp-> prev_ = front_;
		delete rm;
	}
}
template <typename T>
void Sentinel<T>::pop_back(){



	if(front_->next_ != back_)
	{
		Node* rm = back_->prev_;
		Node* temp = rm -> prev_;
		back_ ->prev_ = temp;
		temp -> next_ = back_;
		delete rm;
	}

}
template <typename T>
void Sentinel<T>::print() const{
	Node* curr=front_->next_;
	while(curr!=back_){
		std::cout << curr->data_ << " ";
		curr=curr->next_;
	}
	std::cout << std::endl;
}
template <typename T>
void Sentinel<T>::reversePrint() const{
	Node* curr=back_->prev_;
	while(curr!=front_){
		std::cout << curr->data_ << " ";
		curr=curr->prev_;
	}
	std::cout << std::endl;
}
template <typename T>
Sentinel<T>::~Sentinel(){
	Node* curr=front_;
	while(curr){
		Node* rm=curr;
		curr=curr->next_;
		delete rm;
	}
}
