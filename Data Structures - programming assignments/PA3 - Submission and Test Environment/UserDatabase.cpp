#include "UserDatabase.h"

// IMPLEMENT THESE
UserDatabase::UserDatabase(): _userTable(11, NULL), _size(0),_load_factor(0.75),_dummy(new UserNode("DUMMY"))
{}

UserDatabase::UserDatabase(size_t s, double load): _userTable(s, NULL),_size(0),_load_factor(load), _dummy(new UserNode("DUMMY")) 
{}

UserDatabase::~UserDatabase()
{
   
    for(size_t i = 0 ; i<_userTable.size();i++)
    {
        if(_userTable[i] != NULL && _userTable[i] != _dummy)
            delete _userTable[i];
             _userTable[i] = NULL;
    }
    delete _dummy;
    _dummy = NULL;
    
	// TODO
}

size_t UserDatabase::size() const
{
    size_t sizee = 0;
    for(size_t i = 0; i<_userTable.size(); i++)
    {
        if(_userTable[i] != NULL && _userTable[i] != _dummy) sizee++;
    }
    
    return sizee;
}    
    
    
size_t UserDatabase::capacity() const
{
    size_t capacityy = _userTable.size();
	return capacityy;
}

bool UserDatabase::isEmpty() const
{
	for(size_t i = 0; i<_userTable.size(); i++)
    {
        if(_userTable[i] != NULL && _userTable[i] != _dummy) return false;
    }
	return true;
}

void UserDatabase::addUser(string username) {
    
    if((double)size()/capacity() >= _load_factor)
    {
        resize(2*capacity()+1);
    }
    
    int hash = hashFunction(username,capacity());
    int h = hash;
    int j = 1;
    
    while(_userTable[h] != NULL && _userTable[h] != _dummy && _userTable[h]->username != username)
    {
        h = (hash + j) % capacity();
        j++;
    }
    if (_userTable[h] != NULL && _userTable[h] != _dummy && _userTable[h]->username == username) throw UsernameTakenException(username);
    
    UserNode * new_user = new UserNode(username);
    _userTable[h] = new_user;
    _size++;
	// TODO

}


void UserDatabase::removeUser(string username)
{
    int hash = hashFunction(username, capacity());
    int h = hash;
    int j = 1;
    bool is_exist=false;
    while (_userTable[h] != NULL) 
    {
        if (_userTable[h] != _dummy && _userTable[h]->username == username) 
        {
            delete _userTable[h];
            _userTable[h] = _dummy;
            _size--;
            is_exist =true;
            break;
        }
        h = (hash + j) % capacity();
        j++;
        if(j > capacity()) break;
    }

    if(is_exist == false) throw UserDoesNotExistException(username);
    else{
        
        for (size_t i = 0; i < capacity(); i++) 
        {
            if (_userTable[i] == NULL || _userTable[i] == _dummy) continue;
    
            vector<string>& follows = _userTable[i]->follows;
            for (size_t j = 0; j < follows.size(); ) 
            {
                if (follows[j] == username) 
                {
                    follows.erase(follows.begin() + j); // Remove the username
                    break;
                } 
                
                else 
                {
                    j++;
                }
            }
        }
    }
}

UserNode* UserDatabase::getUser(string username) const
{
    int hash = hashFunction(username,capacity());
    int h = hash;
    int j = 1;
    
    while(_userTable[h] != NULL && _userTable[h] != _dummy && _userTable[h]->username != username)
    {
        h = (hash + j) % capacity();
        j++;
    }
    if (_userTable[h] != NULL && _userTable[h] != _dummy && _userTable[h]->username == username) return  _userTable[h];
    else throw UserDoesNotExistException(username);
}

void UserDatabase::resize(size_t size)
{

    vector<UserNode*> temp_vec = _userTable;
    _userTable.clear();
    _userTable.resize(size, NULL);

    for(size_t i = 0; i < temp_vec.size(); i++) {
        if(temp_vec[i] != NULL && temp_vec[i] != _dummy) 
        {
            int hash = hashFunction(temp_vec[i]->username, capacity());
            int h = hash;
            int j = 1;

            while (_userTable[h] != NULL) {
                h = (hash + j) % capacity();
                j++;
            }

            _userTable[h] = temp_vec[i];
        }
    }
	// TODO
}

void UserDatabase::follow(string username1, string username2)
{
    try
    {        
        UserNode * user2 = getUser(username2);
    }
    catch (UserDoesNotExistException)
    {
        throw UserDoesNotExistException(username2);
    }
    
    try{
        UserNode * user1 = getUser(username1);
        
        for(size_t i = 0;i< user1->follows.size(); i++)
        {
            if(user1->follows[i] == username2) throw RedundantActionException(username1,username2,true);
        }
        user1->follows.push_back(username2);
        
    }
    catch (UserDoesNotExistException)
    {
        throw UserDoesNotExistException(username1);
    }
    
	// TODO
}


void UserDatabase::unfollow(string username1, string username2)
{
    try
    {        
        UserNode * user2 = getUser(username2);
    }
    catch (UserDoesNotExistException)
    {
        throw UserDoesNotExistException(username2);
    }
    
    try{
        UserNode * user1 = getUser(username1);
        
        for(size_t i = 0;i< user1->follows.size(); i++)
        {
            if(user1->follows[i] == username2) 
            {
                user1->follows.erase(user1->follows.begin() + i);
                return;
            }
        }
        throw RedundantActionException(username1,username2,false);
        
    }
    catch (UserDoesNotExistException)
    {
        throw UserDoesNotExistException(username1);
    }
	// TODO
}

bool UserDatabase::userExists(string username) const
{
    try
    {
        UserNode* temp = getUser(username);
        if(temp) return true;
    }
    catch (UserDoesNotExistException)
    {
        return false;
    }
}

bool UserDatabase::userFollows(string username1, string username2) const
{
	 try
    {        
        UserNode * user2 = getUser(username2);
    }
    catch (UserDoesNotExistException)
    {
        throw UserDoesNotExistException(username2);
    }
    
    try{
        UserNode * user1 = getUser(username1);
        
        for(size_t i = 0;i< user1->follows.size(); i++)
        {
            if(user1->follows[i] == username2) 
            {
                return true;
 
            }
        }
        return false;
    }
    catch (UserDoesNotExistException)
    {
        throw UserDoesNotExistException(username1);
    }
}

size_t UserDatabase::userFollowerCount(string username) const
{

    try {
        getUser(username); 
    } catch (const UserDoesNotExistException&) {
        throw UserDoesNotExistException(username);
    }

    size_t count = 0;

    for (size_t i = 0; i < _userTable.size(); i++) {
        if (_userTable[i] == NULL || _userTable[i] == _dummy) {
            continue; 
        }

        for (size_t j = 0; j < _userTable[i]->follows.size(); j++) {
            if (_userTable[i]->follows[j] == username) {
                count++; 
                break; 
            }
        }
    }

    return count; // Return the total follower count
}

size_t UserDatabase::userFollowsCount(string username) const
{
	// TODO
    try{
        UserNode * temp = getUser(username);
        return temp->follows.size();
    }
    catch (UserDoesNotExistException)
    {
        throw UserDoesNotExistException(username);
    }
}


vector<string> UserDatabase::getUserList() const
{
    vector<string> users;
    for(size_t i = 0; i<_userTable.size(); i++)
    {
        if(_userTable[i] == NULL || _userTable[i] == _dummy) continue;
        
        users.push_back(_userTable[i]->username);
    }
    return users;
}


void UserDatabase::printAdjacencyMatrix() const
{
    vector<string> users = getUserList();
    UserNode* current_user;
    
    int user_number = size();
    for(int i = 0;i<user_number;i++ )
    {
        for(int j=0 ; j<user_number;j++)
        {
            try
            {
                if(i == j)
                {
    
                    cout << '0' << ' ';
                    continue;
                }
                if(userFollows(users[i],users[j]))
                {
                     cout << '1' << ' ';
                }
                else
                {
                    cout << '0' << ' ';
                }
            }
            catch(const UserDoesNotExistException&) 
            {
                cout << "0 ";
            }
        }
        cout << '\n';
    }
	// TODO
}

void  UserDatabase::markVisited(const string& username, vector<bool> &visited,vector<string> &users)
{
    for (size_t i = 0; i < users.size(); ++i) 
    {
        if (users[i] == username) 
        {
            visited[i] = true;
            break;
        }
    }
}
bool  UserDatabase::isVisited(const string& username, vector<bool> &visited,vector<string> &users)
{
    for (size_t i = 0; i < users.size(); ++i) 
    {
        if (users[i] == username) 
        {
            return visited[i];
        }
    }
    return false;
}

void UserDatabase::setDistance(const string& username, int dist, vector<int> &distances, vector<string> &users) 
{
    for (size_t i = 0; i < users.size(); ++i) 
    {
        if (users[i] == username) 
        {
            distances[i] = dist;
            break;
        }
    }
}

int UserDatabase::getDistance(const string& username, vector<int> &distances, vector<string> &users) 
{
    for (size_t i = 0; i < users.size(); ++i) 
    {
        if (users[i] == username) 
        {
            return distances[i];
        }
    }
    return -1; 
}

int UserDatabase::BFS(string username1, string username2, bool printPath) 
{
    UserNode* user1 = getUser(username1);
    UserNode* user2 = getUser(username2);
    
    vector<string> usernames = getUserList();
    vector<bool> visited(usernames.size(), false);
    vector<int> distances(usernames.size(), -1);
    
    queue<string> user_queue;
    

    markVisited(username1, visited, usernames);
    setDistance(username1, 0, distances, usernames);
    user_queue.push(username1);
    
    if (printPath) cout << username1 << " ";
    
    while (!user_queue.empty()) {
        string current_username = user_queue.front();
        user_queue.pop();
        
        UserNode* current = getUser(current_username);
        

        for (size_t i = 0; i < current->follows.size(); i++) 
        {
            string neighbor = current->follows[i];
            
            if (!isVisited(neighbor, visited, usernames)) 
            {
                if (printPath) cout << neighbor << " ";
                
                markVisited(neighbor, visited, usernames);
                setDistance(neighbor, getDistance(current_username, distances, usernames) + 1, distances, usernames);
                user_queue.push(neighbor);
                
                if (neighbor == username2) {
                    if(printPath) cout << endl;  
                    return getDistance(neighbor, distances, usernames);
                }
            }
        }
    }
    
    if (printPath) cout << endl; 
    
    return -1;
}

int UserDatabase::DFS(string username1, string username2, bool printPath) 
{
    UserNode* user1 = getUser(username1);
    UserNode* user2 = getUser(username2);

    vector<string> usernames = getUserList();
    vector<bool> visited(usernames.size(), false);
    vector<int> distances(usernames.size(), -1);

    vector<string> user_stack;

    markVisited(username1, visited, usernames);
    setDistance(username1, 0, distances, usernames);
    user_stack.push_back(username1);

    if (printPath) {
        cout << username1 << " ";
    }

    while (!user_stack.empty()) {
        string current_username = user_stack.back();
        UserNode* current = getUser(current_username);

        bool foundUnvisited = false;

        for (size_t i = 0; i < current->follows.size(); ++i) {
            string neighbor = current->follows[i];

            if (!isVisited(neighbor, visited, usernames)) {
                foundUnvisited = true;

                markVisited(neighbor, visited, usernames);
                setDistance(neighbor, getDistance(current_username, distances, usernames) + 1, distances, usernames);

                if (printPath) {
                    cout << neighbor << " ";
                }

                user_stack.push_back(neighbor);

                if (neighbor == username2) {
                    
                    if(printPath) cout << endl;
                    return getDistance(neighbor, distances, usernames);
                }

                break; 
            }
        }

        if (!foundUnvisited) {
            user_stack.pop_back();
        }
    }

    if (printPath) {
        cout << endl;
    }
    return -1;
}




double UserDatabase::averageBFS()
{
    double total = 0.0;
    int current_cost;
    vector<string> usernames = getUserList();
    int user_count = 0;
    
    for(int i = 0; i<usernames.size() ; i++)
    {
        
        for(int j = 0;j<usernames.size();j++)
        {   
            if(i != j)
            {
                current_cost = BFS(usernames[i],usernames[j],false);
                if(current_cost != -1)
                {
                    total += current_cost;
                    user_count ++;
                }
            }
        }
    }
    if (user_count == 0) {
        return 0.0;
    }
	// TODO
	return total/user_count;
}

double UserDatabase::averageDFS()
{
    double total = 0.0;
    int current_cost;
    vector<string> usernames = getUserList();
    int user_count = 0;
    
    for(int i = 0; i<usernames.size() ; i++)
    {
        
        for(int j = 0;j<usernames.size();j++)
        {
            if(i != j)
            {
                current_cost = DFS(usernames[i],usernames[j],false);
                if(current_cost != -1)
                {
                    total += current_cost;
                    user_count ++;
                }
            }
        }
    }
    if (user_count == 0) {
        return 0.0;
    }
	// TODO
	return total/ user_count;
}

vector<string> UserDatabase::getSharedNeighbourhood(string username1, string username2, size_t k)
{
    UserNode* user1 = getUser(username1);
    UserNode* user2 = getUser(username2);
    
    vector<string> usernames = getUserList();
    vector<string>result;
    
    for(int i = 0;i<usernames.size();i++)
    {
        if(usernames[i] == username1) 
        {
            int dist = BFS(username2, username1, false);
            if(dist != -1 && dist < k) result.push_back(usernames[i]);
        }
        
        else if(usernames[i] == username2) {
            int dist = BFS(username1, username2, false);
            if(dist != -1 && dist < k) result.push_back(usernames[i]);
        }
        else
        {
            int dist1 = BFS(username1,usernames[i],false);
            int dist2 = BFS(username2,usernames[i],false);
            if(dist1 != -1 and dist1<k and dist2!=-1 and dist2<k)
            {
                result.push_back(usernames[i]);
            }
        }
    }
	// TODO
	return result;
}

// ADD YOUR HELPER FUCTIONS HERE
