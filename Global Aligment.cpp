#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
struct protein
{
	string identifier;
	string sequence;	
};
template<class T>
class BTNode
{
	private :
		T Data;
		BTNode<T>*LChild;
		BTNode<T>*RChild;	
	public :
		BTNode() :LChild(0),RChild(0)
		{
		
		}
		BTNode(T d,BTNode<T> * L=0, BTNode<T> * R=0) 
		{
			Data.identifier=d.identifier;
			Data.sequence=d.sequence;
			LChild=L;
			RChild=R;
		}
		~BTNode() 
		{
			LChild=0;
			RChild=0;
		}
		BTNode(const BTNode<T> * rhs)
		{
			Data.identifier=rhs->Data.identifier;
			Data.sequence=rhs->Data.sequence;
			LChild=new BTNode<T>;
			LChild=rhs->LChild;
			RChild=new BTNode<T>;
			RChild=rhs->RChild;
		}
		BTNode<T>& operator=(const BTNode<T> &rhs)
		{
			if(this!=&rhs)
			{
				LChild=new BTNode<T>;
				RChild=new BTNode<T>;
				Data.identifier=rhs->Data.identifier;
				Data.sequence=rhs->Data.sequence;
				LChild=rhs.LChild;
				RChild=rhs.RChild;
			}
			return(*this);
		}
		void setLChild(BTNode<T> * L)
		{
			LChild=L;
		}
		void setRChild(BTNode<T> * R)
		{
			RChild =R;
		}
		BTNode<T>* getLChild()
		{
			return(LChild);
		}
		BTNode<T> * getRChild()
		{
			return(RChild);
		}	
		void setData(T d)
		{			
			Data.identifier=d.Data.identifier;
			Data.sequence=d.Data.sequence;
		}
		T& getData()
		{
			return(Data);
		}
};


template<class T>
class BSTree
{
	private :
		BTNode<T>*root;
		BTNode<T>*current;
		void deltree(BTNode<T>*p=0)
		{
			if(p!=0)
			{
				deltree(p->getLChild());
				deltree(p->getRChild());
				p->setLChild(0);
				p->setRChild(0);
				delete p;
				p=0;
			}
		}	
	public  :
		
		BSTree():root(0),current(0)
		{
			
		}
		BSTree(T d)
		{
			root=new BTNode<T> (d);
		}
		void visit(BTNode<T>*p)
		{
			cout<<p->getData().identifier<<endl;
			cout<<p->getData().sequence<<endl;
		}
		void Recursive_Inorder(BTNode<T>*p)
		{
			if(p!=0)
			{
				Recursive_Inorder(p->getLChild());
				visit(p);
				Recursive_Inorder(p->getRChild());
			}
		}

		~BSTree()
		{
			if(this->root!=0)
			{
				deltree();
				root=0;	
			}	
		}
		BTNode<T>* deepcopy(BTNode<T>*rhs)
		{
			if(rhs==0)
			{
				return(rhs);
			}
			BTNode<T>*temp=new BTNode<T>(rhs->getData());
			temp->setLChild(deepcopy(rhs->getLChild()));
			temp->setRChild(deepcopy(rhs->getRChild()));
			return (temp);
		}
		BSTree(const BSTree<T>&rhs)
		{
			root=deepcopy(rhs.root);
		}	
		BSTree<T>& operator=(const BSTree<T>&rhs)
		{
			if(this!=&rhs)
			{
				deltree();
				root=0;
				root=new BTNode<T>;
				root=deepcopy(rhs.root);
				return(*this);
			}
		}		
		void setroot(BTNode<T> * r)
		{
			root=r;
		}
		BTNode<T>* getroot()
		{
			return(root);
		}

		void insert(T  d)
		{
			current=root;
			BTNode<T>*prev=0;
			
			while(current!=0)
			{
				prev=current;
				if(d.identifier<current->getData().identifier)
				current=current->getLChild();
				else
				current=current->getRChild();
			}
			
			if(root==0)
			{
				root=new BTNode<T>(d);
			}
			
			else if(d.identifier<prev->getData().identifier)
			{
				BTNode<T> *temp=new BTNode<T>(d);
				prev->setLChild(temp);
				
			}
			
			else
			{
				BTNode<T> *temp=new BTNode<T>(d);
				prev->setRChild(temp);
			}
			
		}	

		bool search(BTNode<T> *p ,T &d) const
		{
			while(p!=0)
			{
				if(d.identifier<p->getData().identifier)
				p=p->getLChild();
				else if(d.identifier>p->getData().identifier)
				p=p->getRChild();
				else
				{
					d.sequence=p->getData().sequence;
					return true;
				}
			}
			cout<<"Name not found in data set "<<endl;
			return false;
		}
		

};

// function to find out the minimum penalty 
int min(int a,int b,int c)
{
	int min=a;
	if(min>b)
	{
		min=b;
	}
	if(min>c)
	min=c;
	return(min);
	
}
void Wunch_align(string a1,string b1,int pxy, int pgap,int match)  //here pxy is dismatch and pgap is gap value
{
//above worok print two array	
    int m = a1.length(); // length of a1 
    int n = b1.length(); // length of b1   
    // table for storing optimal substructure answers 
    int scoringMatrix[n+m+1][n+m+1] = {0};                //initilize all table with zero

 // intialising the table  
    for (int i = 0; i <= (n+m); i++) 
    { 
        scoringMatrix[i][0] = i * pgap;         //initilize all row with increment with gap 
        scoringMatrix[0][i] = i * pgap;         //initilize all colum with increment with gap
    }     
//now find out min penalty consider three case diagonal ,upwar and downard
    for (int i = 1; i <= m; i++) 
    { 
        for (int j = 1; j <= n; j++) 
        { 
            if (a1[i - 1] == b1[j - 1]) //if it match then simply write it 
            { 
                scoringMatrix[i][j] = scoringMatrix[i - 1][j - 1]+match; //another case when match is given we simply add match
			  } 
            else
            { 
                scoringMatrix[i][j] = min(scoringMatrix[i - 1][j - 1] + pxy ,  
                                scoringMatrix[i - 1][j] + pgap    ,  
                                scoringMatrix[i][j - 1] + pgap    );   //find our min penalty
            } 
        } 
    } 
//main working
 // Reconstructing the solution 
    int l = n + m; // maximum possible length 
      
   int r = m; //string one lenth
   int c = n; //string two lenth 
      
    int A1pos = l; 
    int B1pos = l; 
  
    // Final answers for the respective strings 
    int A1ans[l+1], B1ans[l+1]; 
      
    while ( !(r == 0 || c == 0)) 
    { 
        if (a1[r - 1] == b1[c - 1]) 
        { 
            A1ans[A1pos--] = (int)a1[r - 1]; 
            B1ans[B1pos--] = (int)b1[c - 1]; 
            r--; c--; 
        } 
        else if (scoringMatrix[r - 1][c - 1] + pxy == scoringMatrix[r][c]) 
        { 
            A1ans[A1pos--] = (int)a1[r - 1]; 
            B1ans[B1pos--] = (int)b1[c - 1]; 
            r--; c--; 
        } 
        else if (scoringMatrix[r - 1][c] + pgap == scoringMatrix[r][c]) 
        { 
            A1ans[A1pos--] = (int)a1[r - 1]; 
            B1ans[B1pos--] = (int)'_'; 
            r--; 
        } 
        else if (scoringMatrix[r][c - 1] + pgap == scoringMatrix[r][c]) 
        { 
            A1ans[A1pos--] = (int)'_'; 
            B1ans[B1pos--] = (int)b1[c - 1]; 
            c--; 
        } 
    } 
    while (A1pos > 0) 
    { 
        if (r > 0) A1ans[A1pos--] = (int)a1[--r]; 
        else A1ans[A1pos--] = (int)'_'; 
    } 
    while (B1pos > 0) 
    { 
        if (c > 0) B1ans[B1pos--] = (int)b1[--c]; 
        else B1ans[B1pos--] = (int)'_'; 
    } 
    // Since we have assumed the answer to be n+m long,  
    // we need to remove the extra gaps in the starting  
    // id represents the index from which the arrays 
    // A1ans, B1ans are useful 
    int id = 1; 
    for (int i = l; i >= 1; i--) 
    { 
        if ((char)B1ans[i] == '_' && (char)A1ans[i] == '_') 
        { 
            id = i + 1; 
            break; 
        } 
    } 
    // Printing the final answer 
    cout <<endl<< "The aligned Protiens are :\n"; 
    
for(int k=1,i=id,j=id,m=id;i<=l&&j<=l;k++)
{
	
    for (; i <= l&&i<k*100; i++) 
    { 
        cout<<(char)A1ans[i]; 
    } 
    cout << "\n"; 
    
    for(;m<=l&&m<k*100;m++)
    {
   	if(A1ans[m]=='_'||B1ans[m]=='_')
	cout<<' ';
	else if(A1ans[m]==B1ans[m])
	cout<<'*';
	else
	cout<<'|';
	}
    cout << "\n";
    for (; j <= l&&j<k*100; j++) 
    { 
        cout << (char)B1ans[j]; 
    } 
    cout<<endl<<endl<<endl;
}
    
    
return ;
}
string output_1,output_2;
void hirschberg(string a,string b,int **matrix,int i,int j)
{
if(i==0 && j==0)
{
		return;
}
else if( (i!=0)  && (j!=0) && (matrix[i][j]==(matrix[i-1][j-1]-1)   && (a[i-1]!=b[j-1])  ))
{

	hirschberg(a,b,matrix,i-1,j-1);
	output_1=output_1 +a[i-1];
	output_2=output_2 + b[j-1];			
}
 else if( (i!=0) && (j!=0) && (a[i-1]==b[j-1]) && (matrix[i][j]==matrix[i-1][j-1]+1)  )
{
	hirschberg(a,b,matrix,i-1,j-1);
	output_1=output_1+a[i-1];
	output_2=output_2+b[j-1];
}
else if(  (matrix[i][j]==((matrix[i][j-1]))-2)) 
{
	hirschberg(a,b,matrix,i,j-1);
	output_2=output_2+b[j-1];
	output_1=output_1 + "_"; 	
}
else if ( (i!=0) && (matrix[i][j]==(matrix[i-1][j]-2))  )
{

	hirschberg(a,b,matrix,i-1,j);
	output_2=output_2+"_";
	output_1=output_1 + a[i-1]; 		
}
}
void printresult(string output_1,string output_2,int** matrix,int ii,int jj)
{
	cout<<endl<<"Score is "<<matrix[ii][jj];
	cout<<endl<<endl;
	for(int i=0,j=0,l=0,k=1;i<output_1.length();k++)
{

for(;i<k*100&&i<output_1.length();i++)
{
	cout<<output_1[i];
}
cout<<endl;

for(;l<k*100&&l<output_1.length();l++)
{
	if(output_1[l]=='_'||output_2[l]=='_')
	cout<<' ';
	else if(output_1[l]==output_2[l])
	cout<<'*';
	else
	cout<<'|';
}
cout<<endl;
for(;j<k*100&&j<output_1.length();j++)
{
	cout<<output_2[j];
}
cout<<endl<<endl<<endl<<endl;

}
}
void generatematrix(string first,string second,int **matrix)
{
		for(int i=0; i<first.length()+1; i++)
	{
		for(int j=0; j<second.length()+1; j++)
		{
			if(i==0 || j==0) 
{
		if(i==0)
		{
			matrix[i][j]=(-2)*j;
		}
		else if(j==0)
		{
			matrix[i][j]=(-2)*i;
		}
}

	else if(first[i-1]!=second[j-1])
{

	matrix[i][j]=(max(max(matrix[i-1][j-1]-1,matrix[i-1][j]-2),matrix[i][j-1]-2));

}
else if(first[i-1]==second[j-1])
{
	matrix[i][j]=matrix[i-1][j-1]+1;

}
		}	
	}

}

template<class T>
void makebstree(BSTree<T>& b,ifstream &in)
{
	T temp;
	while(!in.eof())
	{
		in>>temp.identifier;
		in>>temp.sequence;
		b.insert(temp);
	}	
}
int main()
{
	int  option;
	char input='c';
	BSTree<protein> b;
	ifstream in;
	in.open("names.txt");			
	makebstree(b,in);
	in.close();
	while(option!=7&&(input=='c'||input=='C'))
	{
	cout<<"Enter 1 for Global Alligment of two sequences "<<endl;
	cout<<"Enter 2 for Global Alligment of two sequences using protein name "<<endl;
	cout<<"Enter 3 for Global Alligment of two sequences using protein ID "<<endl;
	cout<<"Enter 4 for Global Alligment of one sequence with Data set "<<endl;
	cout<<"Enter 5 for Global Alligment of one protein with data set using protein name "<<endl;
	cout<<"Enter 6 for Global Alligment of one protein with data set using protein ID "<<endl;	
	cout<<"Enter 7 to Exit \n";
	cout<<"Enter your option number : ";
	cin>>option;
	
	
	if(option==1)
	{
		system("cls");
		protein pn1,pn2,pn3;
		cout<<"Enter first sequence : ";
		cin>>pn1.sequence;
		cout<<"Enter second sequence : ";
		cin>>pn2.sequence;
		int misMatchPenalty = 3; // fix mismatch is  3 
        int gapPenalty = 2; // fix gap 2
        int match=2;
		Wunch_align(pn1.sequence,pn2.sequence,misMatchPenalty,gapPenalty,match);
		cout<<"\n Press C To Continue \n";
		input=getch();
	if(input=='c' || input=='C')
		system("cls");
	}
	
	else if(option==2)
	{
		system("cls");
		protein pn1,pn2;
		cout<<"Enter first protein name : ";
		cin>>pn1.identifier;
		cout<<"Enter second protein name : ";
		cin>>pn2.identifier;		
		if(!(b.search(b.getroot(),pn1)  && b.search(b.getroot(),pn2)))
		{
			cout<<"\n Protein Not Found \n";
			
		}
	
	else
	{
		
			
		int **matrix=new int*[pn1.sequence.length()+1];
		for(int k=0; k<(pn1.sequence.length()+1); k++)
		{
			matrix[k]=new int[pn2.sequence.length()+1];
		}
		generatematrix(pn1.sequence,pn2.sequence,matrix);
		hirschberg(pn1.sequence,pn2.sequence,matrix,pn1.sequence.length(),pn2.sequence.length());
		printresult(output_1,output_2,matrix,pn1.sequence.length(),pn2.sequence.length());	
}
	cout<<"\n Press C to Continue \n";
	input=getch();
	if(input=='c'  || input=='C')
	{
		system("cls");
	}
	}
	
	else if(option==3)
	{
		system("cls");
		protein pn1,pn2,pn3;
		cout<<"Enter first protein ID : ";
		cin>>pn1.identifier;
		cout<<"Enter second protein ID : ";
		cin>>pn2.identifier;		
		ifstream in;
		in.open("kaggle.txt");		
		bool p1=false,p2=false;
		while(!in.eof())
		{
			in>>pn3.identifier;
			in>>pn3.sequence;
			if(!p1&&pn1.identifier==pn3.identifier)
			{
				p1=true;
				pn1.sequence=pn3.sequence;
			}
			if(!p2&&pn2.identifier==pn3.identifier)
			{
				p2=true;
				pn2.sequence=pn3.sequence;
			}
			if(p1&&p2)
			break;
		}
		in.close();
		if(!p1||!p2)
		{
			cout<<"Protein ID not found in data set "<<endl;
		
		}
		else 
		{
		int **matrix=new int*[pn1.sequence.length()+1];
		for(int k=0; k<(pn1.sequence.length()+1); k++)
		{
			matrix[k]=new int[pn2.sequence.length()+1];
		}
		generatematrix(pn1.sequence,pn2.sequence,matrix);
		hirschberg(pn1.sequence,pn2.sequence,matrix,pn1.sequence.length(),pn2.sequence.length());
		printresult(output_1,output_2,matrix,pn1.sequence.length(),pn2.sequence.length());			
	}
	cout<<"\n Press C to Continue \n";
input=getch();
if(input=='c'  || input=='C')
{
	system("cls");
}
	}
	
	else if(option==4)
	{
		system("cls");
		protein pn1,pn2,bestmatchp;
		int bestscore=INT_MIN;
		cout<<"Enter Sequence : ";
		cin>>pn1.sequence;
		ifstream in;
		in.open("names.txt");
		int **matrix=new int*[pn1.sequence.length()+1];
		while(!in.eof())
		{
			in>>pn2.identifier;
			in>>pn2.sequence;
			for(int k=0; k<(pn1.sequence.length()+1); k++)
			{
				matrix[k]=new int[pn2.sequence.length()+1];
			}
			generatematrix(pn1.sequence,pn2.sequence,matrix);
			hirschberg(pn1.sequence,pn2.sequence,matrix,pn1.sequence.length(),pn2.sequence.length());
			if(bestscore<matrix[pn1.sequence.length()][pn2.sequence.length()])
			{
				bestscore=matrix[pn1.sequence.length()][pn2.sequence.length()];
				bestmatchp.identifier=pn2.identifier;
				bestmatchp.sequence=pn2.sequence;
			}
			output_1="";
			output_2="";
		}
		in.close();
		cout<<endl<<"Sequence has best alligment with "<<bestmatchp.identifier<<" and score is "<<bestscore<<endl;
		for(int k=0; k<(pn1.sequence.length()+1); k++)
		{
			matrix[k]=new int[bestmatchp.sequence.length()+1];
		}
		generatematrix(pn1.sequence,bestmatchp.sequence,matrix);
		hirschberg(pn1.sequence,bestmatchp.sequence,matrix,pn1.sequence.length(),bestmatchp.sequence.length());
		printresult(output_1,output_2,matrix,pn1.sequence.length(),bestmatchp.sequence.length());	
		cout<<"\n Press C to Continue \n";
input=getch();
if(input=='c'  || input=='C')
{
	system("cls");
}		
	}
	
	else if(option==5)
	{
		system("cls");
		protein pn1,pn2,bestmatchp;
		cout<<"Enter protein name : ";
		cin>>pn1.identifier;	
		
		if(!(b.search(b.getroot(),pn1)))
		{
			cout<<"Protein name not found in data set. "<<endl;
		}
		
		else
		{
		int bestscore=INT_MIN;
		in.open("names.txt");
		int **matrix=new int*[pn1.sequence.length()+1];
		while(!in.eof())
		{
			in>>pn2.identifier;
			in>>pn2.sequence;
			if(pn1.identifier==pn2.identifier)
			continue;
			for(int k=0; k<(pn1.sequence.length()+1); k++)
			{
				matrix[k]=new int[pn2.sequence.length()+1];
			}
			generatematrix(pn1.sequence,pn2.sequence,matrix);
			hirschberg(pn1.sequence,pn2.sequence,matrix,pn1.sequence.length(),pn2.sequence.length());
			if(bestscore<matrix[pn1.sequence.length()][pn2.sequence.length()])
			{
				bestscore=matrix[pn1.sequence.length()][pn2.sequence.length()];
				bestmatchp.identifier=pn2.identifier;
				bestmatchp.sequence=pn2.sequence;
			}
			output_1="";
			output_2="";
		}
		in.close();
		cout<<endl<<"Sequence has best alligment with "<<bestmatchp.identifier<<" and score is "<<bestscore<<endl;
		for(int k=0; k<(pn1.sequence.length()+1); k++)
		{
			matrix[k]=new int[bestmatchp.sequence.length()+1];
		}
		generatematrix(pn1.sequence,bestmatchp.sequence,matrix);
		hirschberg(pn1.sequence,bestmatchp.sequence,matrix,pn1.sequence.length(),bestmatchp.sequence.length());
		printresult(output_1,output_2,matrix,pn1.sequence.length(),bestmatchp.sequence.length());				
	}
	cout<<"\n Press C to Continue \n";
input=getch();
if(input=='c'  || input=='C')
{
	system("cls");
}	
}
	else if(option==6)
	{
		system("cls");
		protein pn,pn1,pn2,bestmatchp;
		cout<<"Enter protein ID : ";
		cin>>pn.identifier;	
		ifstream in;
		in.open("kaggle.txt");
		while(!in.eof()&&pn.identifier!=pn1.identifier)
		{
			in>>pn1.identifier;
			in>>pn1.sequence;
		}
		if(pn.identifier!=pn1.identifier)
		{
			cout<<"Protein ID is not found in data set ."<<endl;	
		}
		else
		{
		in.close();
		int bestscore=INT_MIN;
		in.open("names.txt");
		int **matrix=new int*[pn1.sequence.length()+1];
		while(!in.eof())
		{
			in>>pn2.identifier;
			in>>pn2.sequence;
			for(int k=0; k<(pn1.sequence.length()+1); k++)
			{
				matrix[k]=new int[pn2.sequence.length()+1];
			}
			generatematrix(pn1.sequence,pn2.sequence,matrix);
			hirschberg(pn1.sequence,pn2.sequence,matrix,pn1.sequence.length(),pn2.sequence.length());
			if(bestscore<matrix[pn1.sequence.length()][pn2.sequence.length()])
			{
				bestscore=matrix[pn1.sequence.length()][pn2.sequence.length()];
				bestmatchp.identifier=pn2.identifier;
				bestmatchp.sequence=pn2.sequence;
			}
			output_1="";
			output_2="";
		}
		in.close();
		cout<<endl<<"Sequence has best alligment with "<<bestmatchp.identifier<<" and score is "<<bestscore<<endl;
		for(int k=0; k<(pn1.sequence.length()+1); k++)
		{
			matrix[k]=new int[bestmatchp.sequence.length()+1];
		}
		generatematrix(pn1.sequence,bestmatchp.sequence,matrix);
		hirschberg(pn1.sequence,bestmatchp.sequence,matrix,pn1.sequence.length(),bestmatchp.sequence.length());
		printresult(output_1,output_2,matrix,pn1.sequence.length(),bestmatchp.sequence.length());				
	
	}
		cout<<"\n Press C to Continue \n";
input=getch();
if(input=='c'  || input=='C')
{
	system("cls");
}
}
else if(option==7)
system("exit");
	
}
}
