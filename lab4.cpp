#include "stack.h"
#include <string>
#include<iostream>


bool check_para(std::string first, std::string end){

	if(first[0] == '(' && end == ")"){
		return true;	
	}else if(first[0] == '[' && end == "]"){
		return true;
	}else if(first[0] == '{' && end == "}"){
		return true;
	}
	return false;
}	

bool bracketCheck(const std::string& s){

	Stack<std::string> stack;

	for(int i = 0; i < s.length(); i++){
	
		if( s[i] == '('){
			stack.push(&s[i]);
		}else if(s[i] == '{'){
			stack.push(&s[i]);
		}else if(s[i] == '['){
			stack.push(&s[i]);
		}else if(s[i] == ')'){
			if(stack.empty() ||  !check_para(stack.top(),")") == true){
				return false;
			}else{
				stack.pop();
			}
		}else if(s[i] == '}'){
			if(stack.empty() || !check_para(stack.top(),"}")){
				return false;
			}else{
				stack.pop();
			}
		}else if(s[i] == ']'){
			if(stack.empty() || !check_para(stack.top(),"]")){
				return false;
			}else{

					stack.pop();
			}
		}
	}	
	
	return stack.empty();

}


