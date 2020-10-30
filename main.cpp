//TODO: tigther memory allocation
//Time: 7:22am
#include<iostream>
#include<string>
#include<cstdlib>
#include<cctype>
using namespace std;
int SIZE1=100;
int SIZE2=100;
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
	void print();
};

//void readIn(string exp, string variables, int& numLevel, int*& numNodeEachLevel,node***& allTreePtr, int**& numNextLevelConnections, node****& nextLevelConnections, node***& prevLevelConnections);
void readIn(string exp, string variables, int& numLevel, int*& numNodeEachLevel, int**& allTreePtrType, int**& allTreePtrBeginning, int**& allTreePtrEnd, int****& allTreePtrVar, int****& allTreePtrDeg, int***& allTreePtrCoeff, int***& allTreePtrNumVar, int**& allTreePtrNum, int**& numNextLevelConnections, node****& nextLevelConnections, node***& prevLevelConnections);
void readInEachExp(string exp, int**& var, double**& deg, int**& degNumerator, int**& degDenominator, double*& coeff, int*& coeffNumerator, int*& coeffDenominator, int*& numVar, int& num);
void printOneExp(int**& var, int**& deg, double*& coeff, int*& numVar, int& num);
int power10(int num);
int convert(string num);
double convertFract(string num);	
double convertDeci(string num);
double tenthFract(int num);
bool isFunc(string func);
int main(){
	string exp="((x+y)+ln(x+y+cos(y+ln(x))))+(exp(x^2+y)+(y^2))";
	//string exp="((x+y^3)+exp(2*x^2+y))";
	string variables="x,y";//algebraic variables in the expression

	cout<< convertFract("1/5") << endl;

	exp="cos(2*x+y+y)";
	//int i=5;
	//cout<<"bool "<<exp.substr(i,2)<<" "<<(exp.substr(i,2)=="+y")<<endl;
	variables="x,y";
	


	system("pause");
	return 0;
}
void readIn(string exp, string variables, int& numLevel, int*& numNodeEachLevel, 
int**& allTreePtrType, int**& allTreePtrBeginning, int**& allTreePtrEnd, int****& allTreePtrVar, int****& allTreePtrDeg, int***& allTreePtrCoeff, int***& allTreePtrNumVar, int**& allTreePtrNum, 
int**& numNextLevelConnections, int***& nextLevelConnectionsRow, int***& nextLevelConnectionsCol, int**& prevLevelConnectionsRow, int**& prevLevelConnectionsCol){//sinh, cosh
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
	bool finished;
	int varCount=count;
	count=0;
	bool notAFunc=true;
	for(int i=0;i<exp.size();i++){
		notAFunc=true;
		if(i+2<exp.size()&&exp.substr(i,3)=="abs"){
			notAFunc = false;
			i += 2;
		}
		else if(i+2<exp.size()&&exp.substr(i,3)=="exp"){
			notAFunc = false;
			i += 2;
		}
		else if(i+1<exp.size()&&exp.substr(i,2)=="ln"){
			notAFunc = false;
			i += 1;
		}
		else if(i+2<exp.size()&&exp.substr(i,3)=="log"){
			notAFunc = false;
			i += 2;
		}
		else if(i+2<exp.size()&&exp.substr(i,3)=="cos"){
			//cout<<"pos "<<i<<endl;
			notAFunc = false;
			i += 2;
		}
		else if(i+2<exp.size()&&exp.substr(i,3)=="sin"){
			notAFunc = false;
			i += 2;
		}
		else if(i+2<exp.size()&&exp.substr(i,3)=="tan"){
			notAFunc = false;
			i += 2;
		}
		else if(i+2<exp.size()&&exp.substr(i,3)=="sec"){
			notAFunc = false;
			i += 2;
		}
		else if(i+2<exp.size()&&exp.substr(i,3)=="csc"){
			notAFunc = false;
			i += 2;
		}
		else if(i+2<exp.size()&&exp.substr(i,3)=="cot"){
			notAFunc = false;
			i += 2;
		}
		if(notAFunc&&isalpha(exp[i])){ //ow that character is not part of a string of characters from the "variables" list
			for(int j=0;j<varCount;j++){
				finished=false;
				for(int k=0;exp[i]==var[j][k];k++,i++){
					if(k+1==varLength[j]){
						finished=true;
						break;
					}
				}
				if(finished==true){
					count++;
					break;
				}
				//if(j+1==varCount&&finished==false){
				//	break;
				//}
			}
			if(finished==false){//should be true to continue for next match otherwise no match for this exp[i] and so on
				break;
			}
		}
	}
	int count2 = 0;
	int numMatched = 0;
	bool matched=false;
	for(int i=0;i<exp.size();i++){
		count2=0;
		matched=false;
		if(isalpha(exp[i])){
			for(int j=0;j<varCount;j++){
				while(count2<var[j].size()&&exp[i]==var[j][count2]){
					if(count2 + 1 == var[j].size()){
						matched = true;
					}
					count2++;
				}
				if(matched){
					break;
				}
			}
		}
		if(matched){
			numMatched++;
		}
	}
	if(numMatched!=count){
		cout<<"no matching variables from the list in the expression"<<endl;
		system("pause");
		exit(1);
	}

	count=0;
	for(int i=0;i<exp.length();i++){
		if(exp[i]=='('){
			count++;
		}
	}
	int numLevel=0;
	int maxLevel=0;
	count=0;
	for(int i=0;i<exp.length();i++){
		if(exp[i]=='('){
			if(numLevel>maxLevel){
				maxLevel = numLevel;
			}
			numLevel++;
			count++;
		}
		else if(exp[i]==')'){
			numLevel--;
		}
	}
	//cout<<"max "<<maxLevel<<endl;

	//node* currentPtr = new node(0);
	//allTreePtr[numLevel][0] = currentPtr;
	numNodeEachLevel[0]=1;
	count=0;
	int end;
	int numNode;
	int prevNumNextLevel;
	int count2;
	int fcn;
	int col;
	//need to add a paranthesis to all expressions
	for(int i=0;i<=maxLevel;i++){
		count2=0;
		prevNumNextLevel=0;
		if(i==0){
			numNode=1;
		}
		else{
			numNode=numNodeEachLevel[i-1];
		}
		for(int j=0;j<numNode;j++){
			if(i==0){
				beginning=-1;
				end=exp.length();
				prevNumNextLevel=0;
			}
			else{
				beginning = allTreePtrBeginning[i-1][j];
				end = allTreePtrEnd[i-1][j];
			}
			count2=0;
			for(int k=beginning+1;k<end;k++){
				fcn = 1;
				if(exp[k]=='a'){
					if(exp[k+1]=='b'){
						if(exp[k+2]=='s'){
							fcn = 2;
							k+=3;
						}
					}
				}
				else if(exp[k]=='e'){
					if(exp[k+1]=='x'){
						if(exp[k+2]=='p'){
							fcn = 3;
							k+=3;
						}
					}
			    }
				else if(exp[k]=='l'){
					if(exp[k+1]=='n'){
						fcn = 4;
						k+=2;
					}
				}
				else if(exp[k]=='l'){
					if(exp[k+1]=='o'){
						if(exp[k+2]=='g'){
							fcn = 5;
							k+=3;
						}
					}
				}
				else if(exp[k]=='c'){
					if(exp[k+1]=='o'){
						if(exp[k+2]=='s'){
							fcn = 6;
							k+=3;
						}
					}
				}
				else if(exp[k]=='s'){
					if(exp[k+1]=='i'){
						if(exp[k+2]=='n'){
							fcn = 7;
							k+=3;
						}
					}
				}
				else if(exp[k]=='t'){
					if(exp[k+1]=='a'){
						if(exp[k+2]=='n'){
							fcn = 8;
							k+=3;
						}
					}
				}
				else if(exp[k]=='s'){
					if(exp[k+1]=='e'){
						if(exp[k+2]=='c'){
							fcn = 9;
							k+=3;
						}
					}
				}
				else if(exp[k]=='c'){
					if(exp[k+1]=='s'){
						if(exp[k+2]=='c'){
							fcn = 10;
							k+=3;
						}
					}
				}
				else if(exp[k]=='c'){
					if(exp[k+1]=='o'){
						if(exp[k+2]=='t'){
							fcn = 11;
							k+=3;
						}
					}
				}

				if(exp[j]=='('){
					if(i==0){
						col = 0;
					}
					else{
						col = prevNumNextLevel + count2;
					}
					if(fcn==1){
						allTreePtrType[i][col] = 1;
					}
					else if(fcn==2){
						allTreePtrType[i][col] = 2;
					}
					else if(fcn==3){
						allTreePtrType[i][col] = 3;
					}
					else if(fcn==4){
						allTreePtrType[i][col] = 4;
					}
					else if(fcn==5){
						allTreePtrType[i][col] = 5;
					}
					else if(fcn==6){
						allTreePtrType[i][col] = 6;
					}
					else if(fcn==7){
						allTreePtrType[i][col] = 7;
					}
					else if(fcn==8){
						allTreePtrType[i][col] = 8;
					}
					else if(fcn==9){
						allTreePtrType[i][col] = 9;
					}
					else if(fcn==10){
						allTreePtrType[i][col] = 10;
					}
					else if(fcn==11){
						allTreePtrType[i][col] = 11;
					}
					count = 1;
					allTreePtrBeginning[i][col] = k;
					k++;
					while(k<end&&count!=0){
						if(exp[k]=='('){
							count++;
						}
						else if(exp[k]==')'){ 
							count--;
						}
						//TODO: need to add paranthesis into the expression? no, if no yes//////////////////////////////////////
						if(count==0&&numLevel==0&&exp[k]==')'&&j<exp.length()-1){
							int len=exp.length();
							exp+=' ';
							for(int l=len;l>=1;l--){
								exp[l]=exp[l-1];//
							}
							exp[0]='(';
							exp+=')';
							k=-1;
							numLevel--;
						}
						k++;
					}
					k--;
					allTreePtrEnd[i][col] = k;
					if(numLevel>0){
						//allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;//prevLoopVariable
						prevLevelConnectionsRow[i][col] = i-1;
						prevLevelConnectionsCol[i][col] = j;//need to double check
						nextLevelConnectionsRow[i-1][j][count2] = i;
						nextLevelConnectionsCol[i-1][j][count2] = col;
						count2++;
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
				else{
					//type = 0;
					while(k<end&&(exp[k]!='('||exp[k]!=')'||(i+2<exp.size()&&exp.substr(i,3)!="abs")||(i+2<exp.size()&&exp.substr(i,3)!="exp")||(i+1<exp.size()&&exp.substr(i,2)=="ln")||(i+2<exp.size()&&exp.substr(i,3)!="log")||(i+2<exp.size()&&exp.substr(i,3)!="cos")||(i+2<exp.size()&&exp.substr(i,3)!="sin")||(i+2<exp.size()&&exp.substr(i,3)!="tan")||(i+2<exp.size()&&exp.substr(i,3)!="sec")||(i+2<exp.size()&&exp.substr(i,3)!="csc")||(i+2<exp.size()&&exp.substr(i,3)!="cot"))){
						k++;
					}
					k--;
					
					if(numLevel>0){
						//allTreePtr[numLevel][prevNumNextLevel+count2]=currentPtr;//prevLoopVariable
						readInEachExp(exp.substr(beginning+1,end-beginning-1),int**& allTreePtrType, int**& allTreePtrBeginning, int**& allTreePtrEnd, int****& allTreePtrVar, int****& allTreePtrDeg, int***& allTreePtrCoeff, int***& allTreePtrNumVar, int**& allTreePtrNum);
						prevLevelConnectionsRow[i][col] = i-1;
						prevLevelConnectionsCol[i][col] = j;//need to double check
						nextLevelConnectionsRow[i-1][j][count2] = i;
						nextLevelConnectionsCol[i-1][j][count2] = col;
						count2++;
					}
				}
			}
			prevNumNextLevel+=count2;
			numNextLevelConnections[numLevel-1][j] = count2;
		}
		if(numLevel>0){
			numNodeEachLevel[numLevel]=prevNumNextLevel;
		}
	}
}
void readInEachExp(string exp, int**& var, double**& deg, int**& degNumerator, int**& degDenominator, double*& coeff, int*& coeffNumerator, int*& coeffDenominator, int*& numVar, int& num){
	var = new int*[SIZE1];
	deg = new double*[SIZE1];
	degNumerator = new int*[SIZE1];
	degDenominator = new int*[SIZE1];
	for(int i=0;i<SIZE1;i++){
		var[i] = new int[SIZE2];
		deg[i] = new double[SIZE2];
		degNumerator[i] = new int[SIZE2];
		degDenominator[i] = new int[SIZE2];
	}
	coeff = new double[SIZE1];
	coeffNumerator = new int[SIZE1];
	coeffDenominator = new int[SIZE1];
	numVar = new int[SIZE1];

	int startPos = 0;
	int prevStartPos = 0;
	num=0;
	string c;
	int count=0;
	numVar[num] = 0;
	int i;
	int neg =  1;
	int fractOrDeci = 0;
	for(i=0;i<exp.length();i++){//changed the structure from the previous version, that's what I am talking about, need to rethink
		if(exp[i]=='+'){
			neg = 1;
			startPos = prevStartPos;
			c = "";
			if(exp[startPos] == '-'){
				neg=-1;
				startPos++;
			}
			if(exp[startPos] == '('){
				fractOrDeci = 0 ;
				startPos++;
				while((startPos<exp.size()||exp[startPos]!=')')&&(isdigit(exp[startPos])||exp[startPos]=='/')){/////////////////////////////////////////////////////////////////{//Right here need to rethink
					c+=exp[startPos];
					startPos++;
				}
				startPos++;
			}
			else{
				fractOrDeci = 1;
				while(startPos<exp.size()&&(isdigit(exp[startPos])||exp[startPos]=='.')){
					c+=exp[startPos];
					startPos++;
				}
			}
			
			if(c!=""&&fractOrDeci==1){
				coeff[num]=convertDeci(c);
			}
			else if(c!=""){
				coeff[num]=convertFract(c);
			}
			else{//no coeff
				coeff[num]=1;
			}
			coeff[num]*=neg;
			c="";
			count=0;
			numVar[num]=0;
			//cout<<"test "<<startPos<<" "<<i<<endl;
			while(startPos<i){
				if(count!=0&&exp[startPos]=='*'){
					if(c==""){
						deg[num][numVar[num]]=1;
					}
					c="";
					count=0;
					numVar[num]++;
				}
				else if(isalpha(exp[startPos])){
					var[num][numVar[num]]=(exp[startPos]-'a');
					//cout<<"test "<<(char)(var[num][numVar[num]]+'a')<<endl;
					c="";
					count++;
				}
				else if(isdigit(exp[startPos])){
					while(isdigit(exp[startPos])){
						c+=exp[startPos];
						startPos++;
					}
					startPos--;
					deg[num][numVar[num]]=convert(c);
				}
				startPos++;
				//cout<<"startPos "<<startPos<<endl;
			}
			if(count!=0&&startPos==i){
				if(c==""){
					deg[num][numVar[num]]=1;
				}
				c="";
				numVar[num]++;
			}
			count=0;
			num++;
			prevStartPos=i+1;
		}
	}
	i = exp.size();
	startPos=prevStartPos;
	c="";
	neg=1;
	if(exp[startPos]=='-'){
		neg=-1;
		startPos++;
	}
	while(startPos<exp.size()&&(isdigit(exp[startPos])||exp[startPos]=='.')){
		c+=exp[startPos];
		startPos++;
	}
	if(c!=""){
		coeff[num]=convertDeci(c);
	}
	else{
		coeff[num]=1;
	}
	coeff[num]*=neg;
	c="";
	count=0;
	numVar[num]=0;
	while(startPos<i){
		if(count!=0&&exp[startPos]=='*'){
			if(c==""){
				deg[num][numVar[num]]=1;
			}
			numVar[num]++;
		}
		else if(isalpha(exp[startPos])){
			var[num][numVar[num]]=(exp[startPos]-'a');
			c="";
			count++;
		}
		else if(isdigit(exp[startPos])){
			while(startPos<i&&isdigit(exp[startPos])){
				c+=exp[startPos];
				startPos++;
			}
			startPos--;
			deg[num][numVar[num]]=convert(c);
		}
		startPos++;
	}
	if(count!=0&&startPos==i){
		if(c==""){
			deg[num][numVar[num]]=1;
		}
		c="";
		numVar[num]++;
	}
	count=0;
	num++;
	//Saving memory
	//allocating just enough to save
	int* numVarTemp=new int[num];
	double* coeffTemp=new double[num];
	int** varTemp=new int*[num];
	int** degTemp=new int*[num];
	for(int i=0;i<num;i++){	
		varTemp[i]=new int[numVar[i]];
		degTemp[i]=new int[numVar[i]];
	}
	//copying
	for(int i=0;i<num;i++){
		numVarTemp[i]=numVar[i];
		coeffTemp[i]=coeff[i];
		for(int j=0;j<numVar[i];j++){
			varTemp[i][j]=var[i][j];
			degTemp[i][j]=deg[i][j];
		}
	}
	//deallocating
	delete[] numVar;
	delete[] coeff;
	for(int i=0;i<num;i++){
		delete[] var[i];
		delete[] deg[i];
	}
	delete[] var;
	delete[] deg;
	//allocating
	numVar=new int[num];
	coeff=new double[num];
	var=new int*[num];
	deg=new double*[num];
	for(int i=0;i<num;i++){
		var[i]=new int[numVar[i]];
		deg[i]=new double[numVar[i]];
	}
	//copying
	for(int i=0;i<num;i++){
		numVar[i]=numVarTemp[i];
		coeff[i]=coeffTemp[i];
		for(int j=0;j<numVar[i];j++){
			var[i][j]=varTemp[i][j];
			deg[i][j]=degTemp[i][j];
		}
	}
	//deallocating
	delete[] numVarTemp;
	delete[] coeffTemp;
	for(int i=0;i<num;i++){
		delete[] varTemp[i];
		delete[] degTemp[i];
	}
	delete[] varTemp;
	delete[] degTemp;
}
int power10(int num)
{
    int factor = 10;
    int result = 1;
    if (num==0)
    {
        return 1;
    }
    for (int i=0;i<num;i++)
    {
        result*=factor;
    }
    return result;
}
int convert(string num)
{
    int total = 0;
	for (int i=num.size();i>0;i--)
    {
		total+=power10(i-1)*(num[num.size()-i]-'0');
    }
    return total;
}
double convertDeci(string num){
	double total = 0;
	int count=0;
	count=num.size();
	for(int i=0;i<num.size();i++){
		if(num[i]=='.'){
			count=i;
			break;
		}
	}
	for (int i = num.size()-1; i > count; i--)
    {
		total+=tenthFract(i-count)*(num[i]-'0');
		//cout<<tenthFract(i-count)*(num[i]-'0')<<endl;
	}
	//cout<<total<<endl;
	/*cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(num.size()-count-1);*/
	//cout<<total<<endl;
	//total+=1000;
	//cout<<total<<endl;
	for (int i = count; i > 0; i--)
    {
		total += power10(i - 1) * (num[count - i] - '0');
		//cout<<power10(i - 1) * (num[count - i] - '0')<<endl;
	}
	//cout<<total<<endl;
    return total;
}
double convertFract(string num){
	double numerator = 0;
	double denominator = 0;
	int count=0;
	count=num.size();
	for(int i=0;i<num.size();i++){
		if(num[i]=='/'){
			count=i;
			break;
		}
	}
	cout<<count<<endl;
	cout<<num.size()<<endl;
	for (int i = num.size()-1; i > count; i--)
    {		
		//cout<<"no"<<endl;
		denominator += power10((num.size() - 1) - i) * (num[i]-'0');
			//cout<<power10(i - (count+1))<<endl;
		//cout<<tenthFract(i-count)*(num[i]-'0')<<endl;
	}
	cout<<denominator<<endl;
	for (int i = count; i > 0; i--)
    {	
		numerator += power10(i - 1) * (num[count - i] - '0');
		//cout<<power10(i - 1) * (num[count - i] - '0')<<endl;
	}
	cout<<numerator<<endl;

	return numerator/denominator;
}
double tenthFract(int num){
	double factor = 0.1;
    double result = 1;
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
void printOneExp(int**& var, int**& deg, double*& coeff, int*& numVar, int& num){

}
