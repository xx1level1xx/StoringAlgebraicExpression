//Writer:Simon Lee
//Date: 04/10/2020
//Time: 1:16pm
//Title: Derivative of an algebraic expression
//Explanation: Uses the string, exp, and puts the entire algebraic expression into a m-ary tree. Need more hours into graph theory and functions recursion for computer programming.
//Accomplished: Iteratively print out the m-ary tree and checked the pointers of the tree. Can the tree be more complicated and the relationship to the graph theory for algebraic manipulation?
//Thank you about the graph theory
#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;
const int SIZE1=100;
const int SIZE2=100;
struct node{
	node(int);
	int type;
	int beginning;
	int end;
	int** var;
	int** deg;
	int* coeff;
	int* numVar;
	int num;
	node* nextLevelofNodesPtr[100];
	int numNextLevel;
	node* prevNodePtr;
	void print();
};

//+(0), -(1), *(2), /(3), ^(4)
void readIn(string exp, string variables, int& numLevel, int*& numNodeEachLevel,node***& allTreePtr);
void readInOneExp(string, node*&);
//void truncate();
void print(node* head);
int power10(int);
double convert(string);
int main(){
	string exp="((x+y)+ln(x+y))+(exp(x^2+y)+(y^2))";
	//string exp="((x+y^3)+exp(2*x^2+y))";
	string variables="x,y";//algebraic variables in the expression

	//Listing out the array position of each character for debugging purposes
	for(int i=0;i<exp.length();i++){
		cout<<exp[i]<<' ';
	}
	cout<<endl;
	for(int i=0;i<exp.length();i++){
		if(i<10){
			cout<<i<<' ';
		}
		else{
			cout<<i;
		}
	}
	cout<<endl;

	//Declaring the C++ variables to store the expression into a tree
	//node* head=new node(0);
	int numLevel=0;
	int* ptr;
	node*** treePtr;
	ptr=new int[SIZE1];
	treePtr=new node**[SIZE1];
	for(int i=0;i<SIZE1;i++){
		treePtr[i]=new node*[SIZE2];
	}
	readIn(exp,variables,numLevel,ptr,treePtr);
	/*cout<<numLevel<<endl;
	cout<<ptr[0]<<endl;
	cout<<ptr[1]<<endl;
	cout<<ptr[2]<<endl;
	cout<<ptr[3]<<endl;*/

	/*cout<<numLevel<<endl;
	for(int i=0;i<numLevel;i++){
		cout<<ptr[i]<<endl;
	}
	for(int i=0;i<numLevel;i++){
		for(int j=0;j<ptr[i];j++){
			treePtr[i][j]->print();
			cout<<endl;
		}
		cout<<endl;
	}*/
	//Checking for the first exp
	//1.
	/*cout<<endl;
	treePtr[0][0]->print();
	cout<<endl;
	treePtr[0][0]->nextLevelofNodesPtr[0]->print();
	cout<<endl;
	treePtr[1][0]->print();
	cout<<endl;
	treePtr[0][0]->nextLevelofNodesPtr[1]->print();
	cout<<endl;
	treePtr[1][1]->print();
	cout<<endl;
	treePtr[0][0]->nextLevelofNodesPtr[0]->nextLevelofNodesPtr[0]->print();
	cout<<endl;
	treePtr[1][0]->nextLevelofNodesPtr[0]->print();
	cout<<endl;
	treePtr[2][0]->print();
	cout<<endl;
	treePtr[0][0]->nextLevelofNodesPtr[0]->nextLevelofNodesPtr[1]->print();
	cout<<endl;
	treePtr[1][0]->nextLevelofNodesPtr[1]->print();
	cout<<endl;
	treePtr[2][1]->print();
	cout<<endl;
	treePtr[0][0]->nextLevelofNodesPtr[1]->nextLevelofNodesPtr[0]->print();
	cout<<endl;
	treePtr[1][1]->nextLevelofNodesPtr[0]->print();
	cout<<endl;
	treePtr[2][2]->print();
	cout<<endl;
	treePtr[0][0]->nextLevelofNodesPtr[1]->nextLevelofNodesPtr[1]->print();
	cout<<endl;
	treePtr[1][1]->nextLevelofNodesPtr[1]->print();
	cout<<endl;
	treePtr[2][3]->print();
	cout<<endl;
	cout<<"Previous Level of the Tree"<<endl;
	//2.
	//1st level
	treePtr[0][0]->print();
	cout<<endl;
	treePtr[1][0]->prevNodePtr->print();
	cout<<endl;
	treePtr[1][1]->prevNodePtr->print();
	cout<<endl;
	cout<<endl;
	//2nd level
	treePtr[1][0]->print();
	cout<<endl;
	treePtr[2][0]->prevNodePtr->print();
	cout<<endl;
	treePtr[2][1]->prevNodePtr->print();
	cout<<endl;
	cout<<endl;
	treePtr[1][1]->print();
	cout<<endl;
	treePtr[2][2]->prevNodePtr->print();
	cout<<endl;
	treePtr[2][3]->prevNodePtr->print();
	cout<<endl;*/

	//Deallocating
	for(int i=0;i<numLevel;i++){
		for(int j=0;j<ptr[i];j++){
			if(treePtr[i][j]->type==0){
				for(int k=0;k<treePtr[i][j]->num;k++){
					delete[] treePtr[i][j]->var[k];
					delete[] treePtr[i][j]->deg[k];
				}
				delete[] treePtr[i][j]->numVar;
				delete[] treePtr[i][j]->coeff;
			}
		}
		delete[] treePtr[i];
	}
	delete[] treePtr;//deleted everything
	delete[] ptr;
	system("pause");
	return 0;
}
node::node(int t){
	type=t;
	prevNodePtr=NULL;
}
void node::print(){
	if(type==0){
		if(num==0){
			cout<<'0';
		}
		else if(num==1&&numVar[0]==0){
			cout<<coeff[0];
		}
		else{
			for(int i=0;i<num;i++){
				if(coeff[i]!=1){
					cout<<coeff[i]<<'*';
				}
				for(int j=0;j<numVar[i];j++){
					if(j!=0){
						cout<<'*';
					}
					cout<<(char)(var[i][j]+'a');
					if(deg[i][j]!=1){
						cout<<'^'<<deg[i][j];
					}
				}
				if(i!=num-1){
					cout<<" + ";
				}
			}
		}
	}
	else if(type==1){
		cout<<"() beginning "<<beginning<<" end "<<end;
	}
	else if(type==3){
		cout<<"exp beginning "<<beginning<<" end "<<end;
	}
	else if(type==4){
		cout<<"ln beginning "<<beginning<<" end "<<end;
	}
}
//fcns: 0.expression, 1.(), 2.abs, 3.exp, 4.ln, 5.log(log10), 6.cos, 7.sin, 8.tan, 9.sec, 10.csc, 11.cot
void readIn(string exp, string variables, int& numLevel, int*& numNodeEachLevel,node***& allTreePtr){
	//head=new node(0);
	int count=0;
	for(int i=0;i<variables.length();i++){
		if(variables[i]==','){
			count++;
		}
	}
	count++;
	string* var=new string[count];
	int* varLength=new int[count];
	int beginning=0;
	bool first=true;
	string temp="";
	count=0;
	for(int i=0;i<variables.length();i++){
		if(first){
			beginning=i;
			first=false;
			temp="";
		}
		if(variables[i]==','){
			for(int j=beginning;j<i;j++){
				temp+=variables[j];
			}
			var[count]=temp;
			varLength[count]=i-beginning;
			first=true;
			count++;
		}
		else if(i+1==variables.length()){
			for(int j=beginning;j<i+1;j++){
				temp+=variables[j];
			}
			var[count]=temp;
			varLength[count]=i-beginning+1;
			count++;
		}
	}
	int varCount=count;
	node* currentPtr=new node(0);
	allTreePtr[numLevel][0]=currentPtr;
	numNodeEachLevel[0]=1;
	count=0;
	int end;
	int numNode;
	int prevNumNextLevel;
	int count2;

	while(true){
		count2=0;
		prevNumNextLevel=0;
		if(numLevel==0){
			numNode=1;
		}
		else{
			numNode=numNodeEachLevel[numLevel-1];
		}
		for(int i=0;i<numNode;i++){
			if(numLevel==0){
				beginning=-1;
				end=exp.length();
				prevNumNextLevel=0;
			}
			else{
				beginning=allTreePtr[numLevel-1][i]->beginning;
				end=allTreePtr[numLevel-1][i]->end;
			}
			count2=0;
			for(int j=beginning+1;j<end;j++){
				if(exp[j]=='('){
					currentPtr=new node(1);
					count=1;
					currentPtr->beginning=j;
					j++;
					while(j<end&&count!=0){
						if(exp[j]=='('){
							count++;
						}
						else if(exp[j]==')'){
							count--;
						}
						//TODO: need to add paranthesis into the expression?
						if(count==0&&numLevel==0&&exp[j]==')'&&j<exp.length()-1){
							int len=exp.length();
							exp+=' ';
							for(int k=len;k>=1;k--){
								exp[k]=exp[k-1];//
							}
							exp[0]='(';
							exp+=')';
							j=-1;
							numLevel--;
						}
						j++;
					}
					j--;
					currentPtr->end=j;
					if(numLevel==0){
						allTreePtr[numLevel][0]=currentPtr;
					}
					else if(numLevel>0){
						allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;//prevLoopVariable
						//TODO
						//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
						//or
						//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
						allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
						allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
						count2++;
					}
				}
				else if(exp[j]=='a'){
					if(exp[j+1]=='b'){
						if(exp[j+2]=='s'){
							if(exp[j+3]=='('){
								j+=3;
								currentPtr=new node(2);
								count=1;
								currentPtr->beginning=j;
								j++;
								while(j<end&&count!=0){
									if(exp[j]=='('){
										count++;
									}
									else if(exp[j]==')'){
										count--;
									}
									j++;
								}
								j--;
								currentPtr->end=j;
								if(numLevel==0){
									allTreePtr[numLevel][0]=currentPtr;
								}
								else{
									allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;
									//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
									//or
									//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
									allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
									allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
									count2++;
								}
							}
						}
					}
				}
				else if(exp[j]=='e'){
					if(exp[j+1]=='x'){
						if(exp[j+2]=='p'){
							if(exp[j+3]=='('){
								j+=3;
								currentPtr=new node(3);
								count=1;
								currentPtr->beginning=j;
								j++;
								while(j<end&&count!=0){
									if(exp[j]=='('){
										count++;
									}
									else if(exp[j]==')'){
										count--;
									}
									j++;
								}
								j--;
								currentPtr->end=j;
								if(numLevel==0){
									allTreePtr[numLevel][0]=currentPtr;
								}
								else{
									allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;
									//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
									//or
									//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
									allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
									allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
									count2++;
								}
							}
						}
					}
				}
				else if(exp[j]=='l'){
					if(exp[j+1]=='n'){
						if(exp[j+2]=='('){
							j+=2;
							currentPtr=new node(4);
							count=1;
							currentPtr->beginning=j;
							j++;
							while(j<end&&count!=0){
								if(exp[j]=='('){
									count++;
								}
								else if(exp[j]==')'){
									count--;
								}
								j++;
							}
							j--;
							currentPtr->end=j;
							if(numLevel==0){
									allTreePtr[numLevel][0]=currentPtr;
								}
								else{
									allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;
									//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
									//or
									//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
									allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
									allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
									count2++;
								}
						}
					}
				}
				else if(exp[j]=='l'){
					if(exp[j+1]=='o'){
						if(exp[j+2]=='g'){
							if(exp[j+3]=='('){
								j+=3;
							}
						}
					}
				}
				else if(exp[j]=='+'){
					//sameLevelArithmeticRelationshipBetweenNodes[numLevel][i]=0;
				}
				else if(exp[j]=='-'){
					//sameLevelArithmeticRelationshipBetweenNodes[numLevel][i]=1;
				}
				else if(exp[j]=='*'){
					//sameLevelArithmeticRelationshipBetweenNodes[numLevel][i]=2;
				}
				else if(exp[j]=='/'){
					//sameLevelArithmeticRelationshipBetweenNodes[numLevel][i]=3;
				}
				else if(numLevel>0){
					//type in random words or error, that is all I can for error checking for now
					for(int k=0;k<varCount;k++){
						count=0;
						if(exp[j]==var[k][0]){
							count++;
							for(int l=1;l<varLength[k];l++){
								if(j+l<end&&exp[j+l]==var[k][l]){
									count++;
								}
								//else if(j+l>end){

								//}
							}
							if(count==varLength[k]){
								currentPtr=new node(0);
								readInOneExp(exp.substr(beginning+1,end-beginning-1),currentPtr);
								allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;
								//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
								//or
								//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
								allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
								allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
								count2++;
								//currentPtr->print();
								//cout<<endl;
								j=end-1;
								break;
							}
						}
					}
				}
			}
			prevNumNextLevel+=count2;
			if(numLevel>0){
				allTreePtr[numLevel-1][i]->numNextLevel=count2;
			}
		}
		if(numLevel>0){
			numNodeEachLevel[numLevel]=prevNumNextLevel;
		}
		numLevel++;
		if(numLevel==4){
			//for the 1st exp //numLevel==3 for the commented out 2nd exp
			break;
		}
	}

	//Saving memory
	int* tempNumNodeEachLevelPtr=new int[numLevel];
	for(int i=0;i<numLevel;i++){
		tempNumNodeEachLevelPtr[i]=numNodeEachLevel[i];
	}
	delete[] numNodeEachLevel;
	//or just point, not allocate, assign, and delete the temp one
	numNodeEachLevel=new int[numLevel];
	for(int i=0;i<numLevel;i++){
		numNodeEachLevel[i]=tempNumNodeEachLevelPtr[i];
	}
	delete[] tempNumNodeEachLevelPtr;

	/*node*** tempAllTreePtr=new node**[numLevel];
	for(int i=0;i<numLevel;i++){
		tempAllTreePtr[i]=new node*[numNodeEachLevel[i]];
	}
	for(int i=0;i<numLevel;i++){
		for(int j=0;j<numNodeEachLevel[i];j++){
			tempAllTreePtr[i][j]=allTreePtr[i][j];
		}
	}
	tempAllTreePtr[0][0]->print();
	tempAllTreePtr[0][0]->print();*/
	for(int i=0;i<numLevel;i++){
		for(int j=0;j<numNodeEachLevel[i];j++){
			if(allTreePtr[i][j]->type==0){
				for(int k=0;k<allTreePtr[i][j]->num;k++){
					delete[] allTreePtr[i][j]->var[k];
					delete[] allTreePtr[i][j]->deg[k];
				}
				delete[] allTreePtr[i][j]->numVar;
				delete[] allTreePtr[i][j]->coeff;
			}
		}
		delete[] allTreePtr[i];
	}
	delete[] allTreePtr;//deleted everything

	allTreePtr=new node**[numLevel];
	for(int i=0;i<numLevel;i++){
		allTreePtr[i]=new node*[numNodeEachLevel[i]];
	}
	/*for(int i=0;i<numLevel;i++){
		for(int j=0;j<numNodeEachLevel[i];j++){
			allTreePtr[i][j]=tempAllTreePtr[i][j];
		}
	}
	for(int i=0;i<numLevel;i++){
		delete[] tempAllTreePtr[i];
	}
	delete[] tempAllTreePtr;*/
	
	/*for(int i=0;i<numLevel;i++){
		for(int j=0;j<numNodeEachLevel[i];j++){
			allTreePtr[i][j]->print();
			cout<<endl;
		}
	}*/

	for(int i=0;i<numLevel;i++){
		numNodeEachLevel[i]=0;
	}
	numLevel=0;
	currentPtr=new node(0);
	allTreePtr[numLevel][0]=currentPtr;
	numNodeEachLevel[0]=1;
	while(true){
		count2=0;
		prevNumNextLevel=0;
		if(numLevel==0){
			numNode=1;
		}
		else{
			numNode=numNodeEachLevel[numLevel-1];
		}
		for(int i=0;i<numNode;i++){
			if(numLevel==0){
				beginning=-1;
				end=exp.length();
				prevNumNextLevel=0;
			}
			else{
				beginning=allTreePtr[numLevel-1][i]->beginning;
				end=allTreePtr[numLevel-1][i]->end;
			}
			count2=0;
			for(int j=beginning+1;j<end;j++){
				if(exp[j]=='('){
					currentPtr=new node(1);
					count=1;
					currentPtr->beginning=j;
					j++;
					while(j<end&&count!=0){
						if(exp[j]=='('){
							count++;
						}
						else if(exp[j]==')'){
							count--;
						}
						//TODO: need to add paranthesis into the expression?
						if(count==0&&numLevel==0&&exp[j]==')'&&j<exp.length()-1){
							int len=exp.length();
							exp+=' ';
							for(int k=len;k>=1;k--){
								exp[k]=exp[k-1];//
							}
							exp[0]='(';
							exp+=')';
							j=-1;
							numLevel--;
						}
						j++;
					}
					j--;
					currentPtr->end=j;
					if(numLevel==0){
						allTreePtr[numLevel][0]=currentPtr;
					}
					else if(numLevel>0){
						allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;//prevLoopVariable
						//TODO
						//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
						//or
						//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
						allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
						allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
						count2++;
					}
				}
				else if(exp[j]=='a'){
					if(exp[j+1]=='b'){
						if(exp[j+2]=='s'){
							if(exp[j+3]=='('){
								j+=3;
								currentPtr=new node(2);
								count=1;
								currentPtr->beginning=j;
								j++;
								while(j<end&&count!=0){
									if(exp[j]=='('){
										count++;
									}
									else if(exp[j]==')'){
										count--;
									}
									j++;
								}
								j--;
								currentPtr->end=j;
								if(numLevel==0){
									allTreePtr[numLevel][0]=currentPtr;
								}
								else{
									allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;
									//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
									//or
									//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
									allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
									allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
									count2++;
								}
							}
						}
					}
				}
				else if(exp[j]=='e'){
					if(exp[j+1]=='x'){
						if(exp[j+2]=='p'){
							if(exp[j+3]=='('){
								j+=3;
								currentPtr=new node(3);
								count=1;
								currentPtr->beginning=j;
								j++;
								while(j<end&&count!=0){
									if(exp[j]=='('){
										count++;
									}
									else if(exp[j]==')'){
										count--;
									}
									j++;
								}
								j--;
								currentPtr->end=j;
								if(numLevel==0){
									allTreePtr[numLevel][0]=currentPtr;
								}
								else{
									allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;
									//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
									//or
									//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
									allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
									allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
									count2++;
								}
							}
						}
					}
				}
				else if(exp[j]=='l'){
					if(exp[j+1]=='n'){
						if(exp[j+2]=='('){
							j+=2;
							currentPtr=new node(4);
							count=1;
							currentPtr->beginning=j;
							j++;
							while(j<end&&count!=0){
								if(exp[j]=='('){
									count++;
								}
								else if(exp[j]==')'){
									count--;
								}
								j++;
							}
							j--;
							currentPtr->end=j;
							if(numLevel==0){
									allTreePtr[numLevel][0]=currentPtr;
								}
								else{
									allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;
									//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
									//or
									//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
									allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
									allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
									count2++;
								}
						}
					}
				}
				else if(exp[j]=='l'){
					if(exp[j+1]=='o'){
						if(exp[j+2]=='g'){
							if(exp[j+3]=='('){
								j+=3;
							}
						}
					}
				}
				else if(exp[j]=='+'){
					//sameLevelArithmeticRelationshipBetweenNodes[numLevel][i]=0;
				}
				else if(exp[j]=='-'){
					//sameLevelArithmeticRelationshipBetweenNodes[numLevel][i]=1;
				}
				else if(exp[j]=='*'){
					//sameLevelArithmeticRelationshipBetweenNodes[numLevel][i]=2;
				}
				else if(exp[j]=='/'){
					//sameLevelArithmeticRelationshipBetweenNodes[numLevel][i]=3;
				}
				else if(numLevel>0){
					//type in random words or error, that is all I can for error checking for now
					for(int k=0;k<varCount;k++){
						count=0;
						if(exp[j]==var[k][0]){
							count++;
							for(int l=1;l<varLength[k];l++){
								if(j+l<end&&exp[j+l]==var[k][l]){
									count++;
								}
								//else if(j+l>end){

								//}
							}
							if(count==varLength[k]){
								currentPtr=new node(0);
								readInOneExp(exp.substr(beginning+1,end-beginning-1),currentPtr);
								allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;
								//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
								//or
								//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
								allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
								allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
								count2++;
								//currentPtr->print();
								//cout<<endl;
								j=end-1;
								break;
							}
						}
					}
				}
			}
			prevNumNextLevel+=count2;
			if(numLevel>0){
				allTreePtr[numLevel-1][i]->numNextLevel=count2;
			}
		}
		if(numLevel>0){
			numNodeEachLevel[numLevel]=prevNumNextLevel;
		}
		numLevel++;
		if(numLevel==4){
			//for the 1st exp //numLevel==3 for the commented out 2nd exp
			break;
		}
	}

	/*for(int i=0;i<numLevel;i++){
		for(int j=0;j<numNodeEachLevel[i];j++){
			allTreePtr[i][j]->print();
			cout<<endl;
		}
	}*/

	delete[] var;
	delete[] varLength;
}
//From my previous work which I got no response
void readInOneExp(string exp, node*& oneExp){
	oneExp->num=0;
	oneExp->var = new int*[100];
	oneExp->deg = new int*[100];
	for(int i=0;i<100;i++){
		oneExp->var[i] = new int[100];
		oneExp->deg[i] = new int[100];
	}
	oneExp->coeff = new int[100];
	oneExp->numVar = new int[100];
	int counter=-1;
	string temp;
	int time=0;
	int temp2=-1;
	int neg=1;
	bool constant=false;
	
	for(int i=0;i<exp.length();i++){
		time=0;
		if(exp[i]=='+'){
			for(int k=counter+1;k<i;k++){
				//if(num==0){
				neg = 1;
						if(exp[k]=='-'){
							neg = -1;
							k++;
						}
					if(exp[k]>='0'&&exp[k]<='9'||time==1){
						
						/*cout<<"hi"<<endl;
						neg = 1;
						if(k-1>=0&&exp[k-1]=='-'){
							neg = -1;
							cout<<"wassup"<<endl;
						}*/
						if(time==1){
							k=temp2;
						}
						else{
							//cout<<num<<endl;
							oneExp->numVar[oneExp->num]=0;
						}
						temp="";
						while(k<=i&&exp[k]>='0'&&exp[k]<='9'){//k<=i, just a decimal number
							temp+=exp[k];
							k++;
						}
						if(time==0){
							oneExp->coeff[oneExp->num]=convert(temp);
							oneExp->coeff[oneExp->num] *= neg;
							//coeff[num] *= neg;//negative number
							//cout<<coeff[num]<<endl;

						}
						//cout<<coeff[0]<<endl;
						
						
						if(exp[k+1]>='a'&&exp[k+1]<='z'){
							//cout<<"done"<<endl;
							//cout<<numVar[num]<<endl;
							oneExp->var[oneExp->num][oneExp->numVar[oneExp->num]]=(exp[k+1]-'a');
						}
						k++;
						//cout<<exp[k]<<endl;
						k++;
						if(k+1<i&&exp[k+1]>='2'&&exp[k+1]<='9'){//need to account for degree of 1
							temp=exp[k+1];
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else if(k>=i){
							//cout<<"hi"<<endl;
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else{
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
							k--;
						}
						k++;
						//cout<<exp[k]<<endl;
						temp2=k;
						//if(k>i){
						//	num++;
						//}
						time=1;
					}
					else{//no coeff
						//cout<<"wassup"<<endl;
						//cout<<k<<endl;
						//cout<<i<<endl;
						oneExp->coeff[oneExp->num]=1;
						k--;
						if(time==1){
							k=temp2;
						}
						else{
							oneExp->numVar[oneExp->num]=0;
						}
						if(exp[k+1]>='a'&&exp[k+1]<='z'){
							//cout<<"done"<<endl;
							//cout<<numVar[num]<<endl;
							oneExp->var[oneExp->num][oneExp->numVar[oneExp->num]]=(exp[k+1]-'a');
						}
						k++;
						//cout<<exp[k]<<endl;
						k++;
						//cout<<k<<endl;
						//cout<<i<<endl;
						if(k+1<i&&exp[k+1]>='2'&&exp[k+1]<='9'){//need to account for degree of 1
							temp=exp[k+1];
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else if(k>=i){
							//cout<<"wassup"<<endl;
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else{
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
							k--;
						}
						k++;
						//cout<<exp[k]<<endl;
						temp2=k;
						//if(k>i){
						//	num++;
						//}
						time=1;
					}
				//}
			}
			oneExp->num++;
			//if(neg==1){
				counter=i;
			//}
			//else{
		//		counter=i-1;
			//}
		}
		else if(i+1==exp.length()){
			//cout<<"hi"<<endl;
			//cout<<exp[counter+1]<<endl;
			//cout<<num<<endl;
			//cout<<time<<endl;
			//cout<<i<<endl;
			for(int k=counter+1;k<=i;k++){//This time is before '+' so equal sign is required
				//if(num==0){
				//
				//cout<<exp[k]<<endl;
				neg = 1;
						if(exp[k]=='-'){
							neg = -1;
							k++;
						}
					if(exp[k]>='0'&&exp[k]<='9'||time==1){
						//cout<<"hiagain"<<endl;
						//neg = 1;
						//if(k-1>=0&&exp[k-1]=='-'){
					//		neg = -1;
					//	}
						//cout<<exp[k]<<endl;
						//neg = 1;
						//if(k-1>=0&&exp[k-1]=='-'){
						//	neg = -1;
					//		cout<<"wassup"<<endl;
					///	}
						if(time==1){
							
							k=temp2;
						}
						else{
							//cout<<"wassup"<<endl;
							oneExp->numVar[oneExp->num]=0;
						}
						temp="";
						while(k<=i&&exp[k]>='0'&&exp[k]<='9'){//k<=i, just a decimal number
							temp+=exp[k];
							k++;
						}
						if(time==0){
							oneExp->coeff[oneExp->num]=convert(temp);
							oneExp->coeff[oneExp->num] *= neg;//negative number
							//cout<<coeff[num]<<endl;
						}
						//cout<<coeff[0]<<endl;
						constant = false;
						if(k==exp.length()){//no variable, just a constant
							//cout<<coeff[num]<<endl;
							oneExp->numVar[oneExp->num]=0;
							oneExp->num++;
							constant = true;
							break;
						}
						else if(exp[k+1]>='a'&&exp[k+1]<='z'){//need to account for the multiplication sign
							//cout<<"done"<<endl;
							//cout<<numVar[num]<<endl;
							oneExp->var[oneExp->num][oneExp->numVar[oneExp->num]]=(exp[k+1]-'a');
						}
						k++;
						//cout<<exp[k]<<endl;
						k++;
						if(k+1<exp.length()&&exp[k+1]>='2'&&exp[k+1]<='9'){//need to account for degree of 1
							temp=exp[k+1];
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else if(k>i){
							//cout<<"hi"<<endl;
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else{
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
							k--;
						}
						k++;
						//cout<<exp[k]<<endl;
						temp2=k;
						//if(k>i){
						//	num++;
						//}
						time=1;
					}
					else{//no coeff
						oneExp->coeff[oneExp->num]=1;
						k--;
						if(time==1){
							k=temp2;
						}
						else{
							oneExp->numVar[oneExp->num]=0;
						}
						if(exp[k+1]>='a'&&exp[k+1]<='z'){
							//cout<<"done"<<endl;
							//cout<<numVar[num]<<endl;
							oneExp->var[oneExp->num][oneExp->numVar[oneExp->num]]=(exp[k+1]-'a');
						}
						k++;
						//cout<<exp[k]<<endl;
						k++;
						if(k+1<exp.length()&&exp[k+1]>='2'&&exp[k+1]<='9'){//need to account for degree of 1
							temp=exp[k+1];
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else if(k>i){
							//cout<<"hi"<<endl;
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else{
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
							k--;
						}
						k++;
						//cout<<exp[k]<<endl;
						temp2=k;
						//if(k>i){
						//	num++;
						//}
						time=1;
					}
				//}
			}
			if(!constant){
				oneExp->num++;
				counter=i;
			}
		}
	}
	int** tempVar=new int*[oneExp->num];
	int** tempDeg=new int*[oneExp->num];
	for(int i=0;i<oneExp->num;i++){
		tempVar[i]=new int[oneExp->numVar[i]];
		tempDeg[i]=new int[oneExp->numVar[i]];
	}
	int* tempCoeff=new int[oneExp->num];
	int* tempNumVar=new int[oneExp->num];
	for(int i=0;i<oneExp->num;i++){
		tempCoeff[i]=oneExp->coeff[i];
		tempNumVar[i]=oneExp->numVar[i];

	}
	for(int i=0;i<oneExp->num;i++){
		for(int j=0;j<tempNumVar[i];j++){
			tempVar[i][j]=oneExp->var[i][j];
			tempDeg[i][j]=oneExp->deg[i][j];
		}
	}
	//Deallocating
	for(int i=0;i<oneExp->num;i++){
		delete[] oneExp->var[i];
		delete[] oneExp->deg[i];
	}
	delete[] oneExp->var;
	delete[] oneExp->deg;
	delete[] oneExp->coeff;
	delete[] oneExp->numVar;
	//Allocating and assigning
	oneExp->coeff=new int[oneExp->num];
	oneExp->numVar=new int[oneExp->num];
	for(int i=0;i<oneExp->num;i++){
		oneExp->coeff[i]=tempCoeff[i];
		oneExp->numVar[i]=tempNumVar[i];

	}

	oneExp->var=new int*[oneExp->num];
	oneExp->deg=new int*[oneExp->num];
	for(int i=0;i<oneExp->num;i++){
		oneExp->var[i]=new int[oneExp->numVar[i]];
		oneExp->deg[i]=new int[oneExp->numVar[i]];
	}
	
	for(int i=0;i<oneExp->num;i++){
		for(int j=0;j<oneExp->numVar[i];j++){
			oneExp->var[i][j]=tempVar[i][j];
			oneExp->deg[i][j]=tempDeg[i][j];
		}
	}
	//oneExp->print();

	//Deallocating
	for(int i=0;i<oneExp->num;i++){
		delete[] tempVar[i];
		delete[] tempDeg[i];
	}
	delete[] tempVar;
	delete[] tempDeg;
	delete[] tempCoeff;
	delete[] tempNumVar;
}
void print(node* head){

}
int power10(int num)
{
    int factor = 10;
    int result = 1;
    if (num == 0)
    {
        return 1;
    }
    for (int i = 0; i < num; i++)
    {
        result *= factor;
    }
    return result;
}
double convert(string num)
{
    int total = 0;
	for (int i = num.length(); i > 0; i--)
    {
		total += power10(i - 1) * (num[num.length() - i] - '0');
    }
    return total;
}

	/*while(true){
		count2=0;
		prevNumNextLevel=0;
		if(numLevel==0){
			numNode=1;
		}
		else{
			numNode=numNodeEachLevel[numLevel-1];
		}
		for(int i=0;i<numNode;i++){
			if(numLevel==0){
				beginning=-1;
				end=exp.length();
				prevNumNextLevel=0;
			}
			else{
				beginning=allTreePtr[numLevel-1][i]->beginning;
				end=allTreePtr[numLevel-1][i]->end;
			}
			count2=0;
			for(int j=beginning+1;j<end;j++){
				if(exp[j]=='('){
					currentPtr=new node(1);
					count=1;
					currentPtr->beginning=j;
					j++;
					while(j<end&&count!=0){
						if(exp[j]=='('){
							count++;
						}
						else if(exp[j]==')'){
							count--;
						}
						//TODO: need to add paranthesis into the expression?
						if(count==0&&numLevel==0&&exp[j]==')'&&j<exp.length()-1){
							int len=exp.length();
							exp+=' ';
							for(int k=len;k>=1;k--){
								exp[k]=exp[k-1];//
							}
							exp[0]='(';
							exp+=')';
							j=-1;
							numLevel--;
						}
						j++;
					}
					j--;
					currentPtr->end=j;
					if(numLevel==0){
						allTreePtr[numLevel][0]=currentPtr;
					}
					else if(numLevel>0){
						allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;//prevLoopVariable
						//TODO
						//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
						//or
						//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
						allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
						allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
						count2++;
					}
				}
				else if(exp[j]=='a'){
					if(exp[j+1]=='b'){
						if(exp[j+2]=='s'){
							if(exp[j+3]=='('){
								j+=3;
								currentPtr=new node(2);
								count=1;
								currentPtr->beginning=j;
								j++;
								while(j<end&&count!=0){
									if(exp[j]=='('){
										count++;
									}
									else if(exp[j]==')'){
										count--;
									}
									j++;
								}
								j--;
								currentPtr->end=j;
								if(numLevel==0){
									allTreePtr[numLevel][0]=currentPtr;
								}
								else{
									allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;
									//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
									//or
									//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
									allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
									allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
									count2++;
								}
							}
						}
					}
				}
				else if(exp[j]=='e'){
					if(exp[j+1]=='x'){
						if(exp[j+2]=='p'){
							if(exp[j+3]=='('){
								j+=3;
								currentPtr=new node(3);
								count=1;
								currentPtr->beginning=j;
								j++;
								while(j<end&&count!=0){
									if(exp[j]=='('){
										count++;
									}
									else if(exp[j]==')'){
										count--;
									}
									j++;
								}
								j--;
								currentPtr->end=j;
								if(numLevel==0){
									allTreePtr[numLevel][0]=currentPtr;
								}
								else{
									allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;
									//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
									//or
									//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
									allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
									allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
									count2++;
								}
							}
						}
					}
				}
				else if(exp[j]=='l'){
					if(exp[j+1]=='n'){
						if(exp[j+2]=='('){
							j+=2;
							currentPtr=new node(4);
							count=1;
							currentPtr->beginning=j;
							j++;
							while(j<end&&count!=0){
								if(exp[j]=='('){
									count++;
								}
								else if(exp[j]==')'){
									count--;
								}
								j++;
							}
							j--;
							currentPtr->end=j;
							if(numLevel==0){
									allTreePtr[numLevel][0]=currentPtr;
								}
								else{
									allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;
									//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
									//or
									//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
									allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
									allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
									count2++;
								}
						}
					}
				}
				else if(exp[j]=='l'){
					if(exp[j+1]=='o'){
						if(exp[j+2]=='g'){
							if(exp[j+3]=='('){
								j+=3;
							}
						}
					}
				}
				else if(exp[j]=='+'){
					sameLevelArithmeticRelationshipBetweenNodes[numLevel][i]=0;
				}
				else if(exp[j]=='-'){
					sameLevelArithmeticRelationshipBetweenNodes[numLevel][i]=1;
				}
				else if(exp[j]=='*'){
					sameLevelArithmeticRelationshipBetweenNodes[numLevel][i]=2;
				}
				else if(exp[j]=='/'){
					sameLevelArithmeticRelationshipBetweenNodes[numLevel][i]=3;
				}
				else if(numLevel>0){
					//type in random words or error
					for(int k=0;k<varCount;k++){
						count=0;
						if(exp[j]==var[k][0]){
							count++;
							for(int l=1;l<varLength[k];l++){
								if(j+l<end&&exp[j+l]==var[k][l]){
									count++;
								}
								//else if(j+l>end){

								//}
							}
							if(count==varLength[k]){
								currentPtr=new node(0);
								readInOneExp(exp.substr(beginning+1,end-beginning-1),currentPtr);
								allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;
								//allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];
								//or
								//currentPtr->prevNodePtr=allTreePtr[numLevel-1][i]
								allTreePtr[numLevel][prevNumNextLevel+count2]->prevNodePtr=allTreePtr[numLevel-1][i];//this choice for now
								allTreePtr[numLevel-1][i]->nextLevelofNodesPtr[count2]=currentPtr;
								count2++;
								//currentPtr->print();
								//cout<<endl;
								j=end-1;
								break;
							}
						}
					}
				}
			}
			prevNumNextLevel+=count2;
			if(numLevel>0){
				allTreePtr[numLevel-1][i]->numNextLevel=count2;
			}
		}
		if(numLevel>0){
			numNodeEachLevel[numLevel]=prevNumNextLevel;
		}
		numLevel++;
		if(numLevel==4){
			//for the 1st exp //numLevel==3 for the commented out 2nd exp
			break;
		}
	}*/
	/*for(int i=0;i<numLevel;i++){
		for(int j=0;j<numNodeEachLevel[i];j++){
			allTreePtr[i][j]->print();
			cout<<endl;
		}
	}*/
	/*delete[] var;
	delete[] varLength;
}
//From my previous work which I got no response
void readInOneExp(string exp, node* oneExp){
	oneExp->num=0;
	oneExp->var = new int*[100];
	oneExp->deg = new int*[100];
	for(int i=0;i<100;i++){
		oneExp->var[i] = new int[100];
		oneExp->deg[i] = new int[100];
	}
	oneExp->coeff = new int[100];
	oneExp->numVar = new int[100];
	int counter=-1;
	string temp;
	int time=0;
	int temp2=-1;
	int neg=1;
	bool constant=false;
	
	for(int i=0;i<exp.length();i++){
		time=0;
		if(exp[i]=='+'){
			for(int k=counter+1;k<i;k++){
				//if(num==0){
				neg = 1;
						if(exp[k]=='-'){
							neg = -1;
							k++;
						}
					if(exp[k]>='0'&&exp[k]<='9'||time==1){*/
						
						/*cout<<"hi"<<endl;
						neg = 1;
						if(k-1>=0&&exp[k-1]=='-'){
							neg = -1;
							cout<<"wassup"<<endl;
						}*/
						/*if(time==1){
							k=temp2;
						}
						else{
							//cout<<num<<endl;
							oneExp->numVar[oneExp->num]=0;
						}
						temp="";
						while(k<=i&&exp[k]>='0'&&exp[k]<='9'){//k<=i, just a decimal number
							temp+=exp[k];
							k++;
						}
						if(time==0){
							oneExp->coeff[oneExp->num]=convert(temp);
							oneExp->coeff[oneExp->num] *= neg;
							//coeff[num] *= neg;//negative number
							//cout<<coeff[num]<<endl;

						}
						//cout<<coeff[0]<<endl;
						
						
						if(exp[k+1]>='a'&&exp[k+1]<='z'){
							//cout<<"done"<<endl;
							//cout<<numVar[num]<<endl;
							oneExp->var[oneExp->num][oneExp->numVar[oneExp->num]]=(exp[k+1]-'a');
						}
						k++;
						//cout<<exp[k]<<endl;
						k++;
						if(k+1<i&&exp[k+1]>='2'&&exp[k+1]<='9'){//need to account for degree of 1
							temp=exp[k+1];
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else if(k>=i){
							//cout<<"hi"<<endl;
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else{
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
							k--;
						}
						k++;
						//cout<<exp[k]<<endl;
						temp2=k;
						//if(k>i){
						//	num++;
						//}
						time=1;
					}
					else{//no coeff
						//cout<<"wassup"<<endl;
						//cout<<k<<endl;
						//cout<<i<<endl;
						oneExp->coeff[oneExp->num]=1;
						k--;
						if(time==1){
							k=temp2;
						}
						else{
							oneExp->numVar[oneExp->num]=0;
						}
						if(exp[k+1]>='a'&&exp[k+1]<='z'){
							//cout<<"done"<<endl;
							//cout<<numVar[num]<<endl;
							oneExp->var[oneExp->num][oneExp->numVar[oneExp->num]]=(exp[k+1]-'a');
						}
						k++;
						//cout<<exp[k]<<endl;
						k++;
						//cout<<k<<endl;
						//cout<<i<<endl;
						if(k+1<i&&exp[k+1]>='2'&&exp[k+1]<='9'){//need to account for degree of 1
							temp=exp[k+1];
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else if(k>=i){
							//cout<<"wassup"<<endl;
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else{
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
							k--;
						}
						k++;
						//cout<<exp[k]<<endl;
						temp2=k;
						//if(k>i){
						//	num++;
						//}
						time=1;
					}
				//}
			}
			oneExp->num++;
			//if(neg==1){
				counter=i;
			//}
			//else{
		//		counter=i-1;
			//}
		}
		else if(i+1==exp.length()){
			//cout<<"hi"<<endl;
			//cout<<exp[counter+1]<<endl;
			//cout<<num<<endl;
			//cout<<time<<endl;
			//cout<<i<<endl;
			for(int k=counter+1;k<=i;k++){//This time is before '+' so equal sign is required
				//if(num==0){
				//
				//cout<<exp[k]<<endl;
				neg = 1;
						if(exp[k]=='-'){
							neg = -1;
							k++;
						}
					if(exp[k]>='0'&&exp[k]<='9'||time==1){
						//cout<<"hiagain"<<endl;
						//neg = 1;
						//if(k-1>=0&&exp[k-1]=='-'){
					//		neg = -1;
					//	}
						//cout<<exp[k]<<endl;
						//neg = 1;
						//if(k-1>=0&&exp[k-1]=='-'){
						//	neg = -1;
					//		cout<<"wassup"<<endl;
					///	}
						if(time==1){
							
							k=temp2;
						}
						else{
							//cout<<"wassup"<<endl;
							oneExp->numVar[oneExp->num]=0;
						}
						temp="";
						while(k<=i&&exp[k]>='0'&&exp[k]<='9'){//k<=i, just a decimal number
							temp+=exp[k];
							k++;
						}
						if(time==0){
							oneExp->coeff[oneExp->num]=convert(temp);
							oneExp->coeff[oneExp->num] *= neg;//negative number
							//cout<<coeff[num]<<endl;
						}
						//cout<<coeff[0]<<endl;
						constant = false;
						if(k==exp.length()){//no variable, just a constant
							//cout<<coeff[num]<<endl;
							oneExp->numVar[oneExp->num]=0;
							oneExp->num++;
							constant = true;
							break;
						}
						else if(exp[k+1]>='a'&&exp[k+1]<='z'){//need to account for the multiplication sign
							//cout<<"done"<<endl;
							//cout<<numVar[num]<<endl;
							oneExp->var[oneExp->num][oneExp->numVar[oneExp->num]]=(exp[k+1]-'a');
						}
						k++;
						//cout<<exp[k]<<endl;
						k++;
						if(k+1<exp.length()&&exp[k+1]>='2'&&exp[k+1]<='9'){//need to account for degree of 1
							temp=exp[k+1];
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else if(k>i){
							//cout<<"hi"<<endl;
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else{
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
							k--;
						}
						k++;
						//cout<<exp[k]<<endl;
						temp2=k;
						//if(k>i){
						//	num++;
						//}
						time=1;
					}
					else{//no coeff
						oneExp->coeff[oneExp->num]=1;
						k--;
						if(time==1){
							k=temp2;
						}
						else{
							oneExp->numVar[oneExp->num]=0;
						}
						if(exp[k+1]>='a'&&exp[k+1]<='z'){
							//cout<<"done"<<endl;
							//cout<<numVar[num]<<endl;
							oneExp->var[oneExp->num][oneExp->numVar[oneExp->num]]=(exp[k+1]-'a');
						}
						k++;
						//cout<<exp[k]<<endl;
						k++;
						if(k+1<exp.length()&&exp[k+1]>='2'&&exp[k+1]<='9'){//need to account for degree of 1
							temp=exp[k+1];
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else if(k>i){
							//cout<<"hi"<<endl;
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
						}
						else{
							temp="1";
							oneExp->deg[oneExp->num][oneExp->numVar[oneExp->num]]=convert(temp);
							oneExp->numVar[oneExp->num]++;
							k--;
						}
						k++;
						//cout<<exp[k]<<endl;
						temp2=k;
						//if(k>i){
						//	num++;
						//}
						time=1;
					}
				//}
			}
			if(!constant){
				oneExp->num++;
				counter=i;
			}
		}
	}
}
void print(node* head){

}
int power10(int num)
{
    int factor = 10;
    int result = 1;
    if (num == 0)
    {
        return 1;
    }
    for (int i = 0; i < num; i++)
    {
        result *= factor;
    }
    return result;
}
double convert(string num)
{
    int total = 0;
	for (int i = num.length(); i > 0; i--)
    {
		total += power10(i - 1) * (num[num.length() - i] - '0');
    }
    return total;
}*/