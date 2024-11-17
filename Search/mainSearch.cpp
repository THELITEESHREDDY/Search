#include <iostream>
#include<algorithm>//where all other inbuilt ready to use functions are used
#include<fstream>//
#include<cctype>//to lower functions
#include<string>
#include<sstream>//string stream-> convert string to words 
#include<vector>
#include<limits>//input error
#include<cstdlib>//for exit()
#include<unordered_map>
using namespace std;

class searchEngine {
private:
	struct Node {
		string s;
		Node* next;
		Node* prev;
		Node(string str):s(str),next(NULL),prev(NULL) {};
	};
	Node* historyHead;
	Node* historyTail;
	vector<string>data;
	unordered_map<string,vector<string>>invertedIndex;
public:
	searchEngine(vector<string>d) {
		data.resize(d.size());
		data=d;
		historyTail=NULL;
		historyHead=NULL;
		for(int i=0; i<data.size(); i++) {
			transform(data[i].begin(),data[i].end(),data[i].begin(),::tolower);
			stringstream strea(data[i]);
			string word;
			while(strea>>word) {
				invertedIndex[word].push_back(data[i]);
			}
		}
	}
	void deleteSearch() {
		if(historyHead==NULL) {
			cout<<"Nothing to delete"<<endl;
			return;
		}
		Node* temp= historyHead;
		Node* prev=NULL;
		while(temp!=NULL) {
			prev=temp;
			temp=temp->next;
			delete prev;
		}
		historyHead=NULL;
		cout<<"History Cleared"<<endl;
	}
	void addToHistory(string s) {

		Node* newNode= new Node(s);
		if(historyHead==NULL) {
			historyHead=newNode;
			historyTail=newNode;
		} else {
			historyTail->next=newNode;
			newNode->prev=historyTail;
			historyTail=newNode;
		}
	}
	void history() {
		if(historyHead==NULL) {
			cout<<"Nothing in History"<<endl;
			return;
		}
		cout<<"Your History"<<endl;
		Node* temp =historyHead;
		while(temp!=NULL) {
			cout<<temp->s<<endl;
			if(temp->next==NULL) {
				break;
			}
			temp=temp->next;
		}
        

	}
	vector<string> tokenization(string query) {
		stringstream stream(query);

		string word;
		vector<string>v;                                 // to collect and send the search results;
		while(stream>>word) {                            // Extract words from query
			transform(word.begin(),word.end(),word.begin(),::tolower);
			v.insert(v.end(),invertedIndex[word].begin(),invertedIndex[word].end());
		}
		return v;
	}
	void search(int i) {
		string query;
		cout<<"Looking for something ?";
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		getline(cin,query);


		if(i) {
			addToHistory(query);
		}
		vector<string>res=tokenization(query);
		cout<<"Searching for "<<query<<" "<<endl;
		if(res.size()>1) {
			if(res.size()==2) {
				cout<<res[0]<<endl;
			}
			for(int i=1; i<res.size(); i++) {
				if(res[i-1]!=res[i]) {
					cout<<res[i]<<endl;
				}
			}
		} else {
			if(res.size()==0) {
				cout<<"Searrrrrrrrrrrrrching"<<endl;
			} else {
				cout<<res[0]<<endl;
			}
		}

	}
};
void printMenu() {
	cout<<1<<" to search"<<endl;
	cout<<2<<" go to History"<<endl;
	cout<<3<<" search in private"<<endl;
	cout<<4<<" delete History"<<endl;
	cout<<-1<<" to exit program"<<endl;
}
int main() {
	vector<string>data= {"The Liteesh Reddy","The magic world","The Rowdy","gemini","Open Ai","Legend","Google","Amazon","Shyam Singh Roy","Arjun Reddy"};
	searchEngine Search(data);
	cout<<"Search"<<endl;


	while(1) {
		printMenu();
		int c;
		if(!(cin>>c)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout<<"Please enter a valid choice"<<endl;
			continue;
		}

		switch(c) {
		case 1:
			Search.search(1);
			break;
		case 2:
			Search.history();
			break;
		case 3:
			Search.search(0);
			break;
		case 4:
			Search.deleteSearch();
			break;
		case -1:
			exit(0);//search.sure();
			break;
		default:
			cout<<"Please enter a valid choice"<<endl;
			break;
		}
	}



	return 0;
}